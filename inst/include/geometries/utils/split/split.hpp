#ifndef R_GEOMETRIES_UTILS_SPLIT_H
#define R_GEOMETRIES_UTILS_SPLIT_H

#include "geometries/shapes/mat/to_mat.hpp"

namespace geometries {
namespace utils {

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
      Rcpp::Nullable< Rcpp::StringVector > class_attribute
  ) {

    bool has_class = !Rf_isNull( class_attribute );

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

          // Rcpp::Rcout << " set class? " << std::endl;
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

      // Rcpp::Rcout << " set class? " << std::endl;
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

} // utils
} // geoemtries


#endif
