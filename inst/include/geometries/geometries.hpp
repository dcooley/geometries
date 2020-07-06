#ifndef R_GEOMETRIES_H
#define R_GEOMETRIES_H

#include "geometries/utils/split/split.hpp"

namespace geometries {


  // works on the assumption that every different outer-id is a different geometry
  // so any attributes are applied at the outer-id level
  inline SEXP make_geometries(
      Rcpp::DataFrame& l,
      Rcpp::IntegerVector ids,
      Rcpp::IntegerVector geometry_cols,
      Rcpp::Nullable< Rcpp::StringVector > class_attribute
  ) {

    bool has_class = !Rf_isNull( class_attribute );

    R_xlen_t i, j;
    R_xlen_t n_id_cols = Rf_length( ids );

    Rcpp::List rleid( n_id_cols );

    for( i = n_id_cols - 1; i >= 0; --i ) {

      Rcpp::Range rng(0, i);
      Rcpp::IntegerVector rle_ids = ids[ rng ];

      bool last = i == n_id_cols - 1;
      bool first = i == 0;
      // Rcpp::Rcout << "i: " << i << ", first; " << first << std::endl;

      // Iff there's only one ID coulmn, the attributes need to be assigned inside 'split'
      // because once back here, a single-id column split doesn't get packaged up
      // AND iff nesting == n_id_cols (1)

      rleid( i ) = geometries::utils::split_by_id( l, rle_ids, geometry_cols, last, class_attribute );

      // here the rleid(i) tells us which elements of rleid(i+1)
      // belong in which "package"
      Rcpp::List curr = rleid( i );

      Rcpp::IntegerVector nelems = curr["nelems"];
      Rcpp::IntegerVector curr_sums = curr["sums"];

      if( !last ) {
        Rcpp::List prev = rleid( i + 1 );
        Rcpp::IntegerVector prev_sums = prev["sums"];
        Rcpp::List prev_res = prev["res"];

        Rcpp::List curr_res( nelems.size() );
        R_xlen_t prev_idx = 0;
        R_xlen_t out_size;

        for( j = 0; j < nelems.size(); ++j ) {

          R_xlen_t curr_sum = curr_sums[ j ];
          R_xlen_t start_prev_idx = prev_idx;
          R_xlen_t prev_sum = prev_sums[ prev_idx ];
          out_size = 1;

          while( prev_sum != curr_sum ) { // prev_sum will always start <= to curr_sum
            prev_idx++;
            out_size++;
            prev_sum = prev_sums[ prev_idx ];
          }
          prev_idx++;

          Rcpp::Range inner_rng( start_prev_idx, prev_idx - 1);
          Rcpp::List obj = prev_res[ inner_rng ];

          if( first && has_class && n_id_cols != 1 ) {
            // Rcpp::Rcout << "set class" << std::endl;
            Rcpp::StringVector cls = {"class"};
            Rf_setAttrib( obj, cls, class_attribute );
          }
          curr_res( j ) = obj;
        }

        // if( first ) {
        //   Rcpp::Rcout << "first: " << std::endl;
        //
        // }

        rleid( i ) = Rcpp::List::create(
          Rcpp::_["nelems"] = nelems,
          Rcpp::_["sums"] = curr_sums,
          Rcpp::_["res"] = curr_res
        );
      } else {
        // need to fill with the coordinates inside ["coords"]
        // it gets here first, because it works from the inside out
        SEXP coords = curr["coords"];

        if( first && has_class && n_id_cols != 1  ) {
          //Rcpp::Rcout << "set class" << std::endl;
          Rcpp::StringVector cls = {"class"};
          Rf_setAttrib( coords, cls, class_attribute );
        }

        rleid( i ) = Rcpp::List::create(
          Rcpp::_["nelems"] = nelems,
          Rcpp::_["sums"] = curr_sums,
          Rcpp::_["res"] = coords
        );
      }
    } // for i

    Rcpp::List out = rleid[0];
    return out["res"];
  }

} // geometries

#endif
