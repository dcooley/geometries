#ifndef R_GEOMETRIES_UTILS_RLEID_H
#define R_GEOMETRIES_UTILS_RLEID_H

namespace geometries {
namespace utils {

  // from data.table
  // https://github.com/Rdatatable/data.table/blob/8b93bb22715b45d38acf185f40d573bda8748cb4/src/uniqlist.c#L164
  inline Rcpp::IntegerVector rleid( Rcpp::DataFrame l, Rcpp::IntegerVector ids ) {
    R_xlen_t i;
    R_xlen_t n_rows = l.nrow();
    //R_xlen_t n_cols = Rf_length( l );
    R_xlen_t n_id_cols = Rf_length( ids );

    Rcpp::IntegerVector ians( n_rows );  // I don't actually need to keep the rleid values
    int grp = 1;
    ians[0] = grp;

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
      ians[ i ] = ( grp += !same );
    }

    return ians;

  }

} // utils
} // geometries


#endif
