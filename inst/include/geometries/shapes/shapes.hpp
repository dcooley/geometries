#ifndef R_GEOMETRIES_SHAPES_H
#define R_GEOMETRIES_SHAPES_H

#include <Rcpp.h>
#include "geometries/shapes/vec/to_vec.hpp"
#include "geometries/shapes/mat/to_mat.hpp"

namespace geometries {
namespace shapes {

  // TODO
  // - If it's the first ID column,
  // - add the class_attribute
  // - don't add it to each individual matrix (unless only 1 id)
  // - so do it iff j == 0 ?
  // - does it get added to the list, or to the matrix?

  inline SEXP split_by_id(
      Rcpp::DataFrame& l,
      Rcpp::IntegerVector ids,
      Rcpp::IntegerVector geometry_cols,
      bool last,
      Rcpp::StringVector class_attribute
  ) {

    bool has_class = class_attribute.length() > 0;

    // reference: data.table
    // https://github.com/Rdatatable/data.table/blob/8b93bb22715b45d38acf185f40d573bda8748cb4/src/uniqlist.c#L164
    Rcpp::StringVector df_names = l.names();

    Rcpp::NumericMatrix nm = geometries::shapes::to_mat( l, geometry_cols );

    R_xlen_t i;
    R_xlen_t n_rows = l.nrow(); //geometries::utils::sexp_n_row( l );
    //R_xlen_t n_cols = Rf_length( l );
    R_xlen_t n_id_cols = Rf_length( ids );
    //Rcpp::IntegerVector ians( n_rows );  // I don't actually need to keep the rleid values

    Rcpp::IntegerVector nelems( n_rows );
    Rcpp::IntegerVector sums( n_rows );

    // values for keeping track of the indexes of 'l' (rows) which form the individual geometries;
    int start = 0;
    int end = 0;
    Rcpp::List res( n_rows ); // arbitrarily start it at the max possible?
    R_xlen_t res_counter = 0;
    R_xlen_t n_elements = 1;
    R_xlen_t cumulative_size = 0;

    for( i = 1; i < n_rows; ++i ) {
      bool same = true;
      int j = n_id_cols;
      while( --j >= 0 && same ) {
        SEXP jcol = VECTOR_ELT( l, ids[ j ] );
        switch( TYPEOF( jcol ) ) {
        case LGLSXP: {}
        case INTSXP: {
          same = INTEGER( jcol )[ i ] == INTEGER( jcol )[ i - 1 ];
          break;
        }
        case REALSXP: {
          long long *ll = (long long *)REAL( jcol );
          same = ll[ i ] == ll[ i - 1 ];
          break;
        }
        case STRSXP: {
          same = STRING_ELT( jcol, i ) == STRING_ELT( jcol, i - 1 );
          break;
        }
        default: {
          Rcpp::stop("geometries - unsupported id column type");
        }
        }
      }  // while end

      // at this point we now have a run-length-encoded vector
      //ians[ i ] = ( grp += !same );
      n_elements += same;
      // at the point where same == 0 we have a new rleid
      if( !same ) {

        // Rcpp::Rcout << "i: " << i << ", j: " << j << ", same: " << same << std::endl;
        nelems[ res_counter ] = n_elements;

        cumulative_size = n_elements + cumulative_size;

        sums[ res_counter ] = cumulative_size;
        n_elements = 1;

        if( last ) {
          end = i - 1;

          Rcpp::Rcout << " set class? " << std::endl;
          // Rcpp::List subset_df = geometries::utils::subset_dataframe( l, df_names, start, end );
          // res[ res_counter ] = subset_df;

          Rcpp::Range row_rng( start, end );
          Rcpp::NumericMatrix res_mat = nm( row_rng, Rcpp::_ );

          if( has_class && n_id_cols == 1 ) {
            Rcpp::StringVector cls = {"class"};
            Rf_setAttrib( res_mat, cls, class_attribute );
          }

          res[ res_counter ] = res_mat;

          start = i;
        }

        // if( j == -1 && has_class) {
        //   Rcpp::Rcout << "set class: " << std::endl;
        //   // Rcpp::StringVector cls = {"class"};
        //   // Rf_setAttrib( res, cls, class_attribute );
        // }
        res_counter++;
      }
    }

    nelems[ res_counter ] = n_elements;

    cumulative_size = n_elements + cumulative_size;
    sums[ res_counter ] = cumulative_size;

    Rcpp::Range rng( 0, res_counter );

    if( last ) {
      end = i - 1;

      // Rcpp::List subset_df = geometries::utils::subset_dataframe( l, df_names, start, end );
      // res[ res_counter ] = subset_df;

      Rcpp::Range row_rng( start, end );
      Rcpp::NumericMatrix res_mat = nm( row_rng, Rcpp::_ );

      Rcpp::Rcout << " set class? " << std::endl;
      if( has_class && n_id_cols == 1 ) {
        Rcpp::StringVector cls = {"class"};
        Rf_setAttrib( res_mat, cls, class_attribute );
      }

      res[ res_counter ] = res_mat;

      // we can remove any res elements AFTER res_counter
      // because by this point we've filled everything
      Rcpp::Range coord_rng( 0, res_counter );

      return Rcpp::List::create(
        Rcpp::_["nelems"] = nelems[ rng ],
        Rcpp::_["sums"] = sums[ rng ],
        Rcpp::_["coords"] = res[ coord_rng ]
      );
    }

    return Rcpp::List::create(
      Rcpp::_["nelems"] = nelems[ rng ],
      Rcpp::_["sums"] = sums[ rng ]
    );

  }


  // works on the assumption that every different outer-id is a different geometry
  // so any attributes are applied at the outer-id level
  inline SEXP make_geometry(
      Rcpp::DataFrame& l,
      Rcpp::IntegerVector ids,
      Rcpp::IntegerVector geometry_cols,
      Rcpp::StringVector class_attribute
  ) {

    bool has_class = class_attribute.length() > 0;
    //Rcpp::Rcout << "has_class: " << has_class << std::endl;

    R_xlen_t i, j;
    R_xlen_t n_id_cols = Rf_length( ids );

    Rcpp::List rleid( n_id_cols );

    for( i = n_id_cols - 1; i >= 0; --i ) {

      //Rcpp::Rcout << "i: " << i << std::endl;

      Rcpp::Range rng(0, i);
      Rcpp::IntegerVector rle_ids = ids[ rng ];

      bool last = i == n_id_cols - 1;
      bool first = i == 0;
      Rcpp::Rcout << "i: " << i << ", first; " << first << std::endl;

      // Iff there's only one ID coulmn, the attributes need to be assigned inside 'split'
      // because once back here, a single-id column split doesn't get packaged up
      // AND iff nesting == n_id_cols (1)

      rleid( i ) = split_by_id( l, rle_ids, geometry_cols, last, class_attribute );

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

          //Rcpp::Rcout << "j: " << j << std::endl;

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
            Rcpp::Rcout << "set class" << std::endl;
            Rcpp::StringVector cls = {"class"};
            Rf_setAttrib( obj, cls, class_attribute );
          }
          curr_res( j ) = obj;
        }

        if( first ) {
          Rcpp::Rcout << "first: " << std::endl;

        }

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

} // shapes
} // geometries


#endif
