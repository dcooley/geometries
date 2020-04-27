#ifndef R_GEOMETRIES_UTILS_H
#define R_GEOMETRIES_UTILS_H

#include <Rcpp.h>
#include "geometries/utils/columns/columns.hpp"
#include "geometries/utils/lines/lines.hpp"
#include "geometries/utils/matrix/matrix.hpp"
#include "geometries/utils/sexp/sexp.hpp"
#include "geometries/utils/subset/subset.hpp"
#include "geometries/utils/unique/unique_ids.hpp"
#include "geometries/utils/vectors/vectors.hpp"

namespace geometries {
namespace utils {

  inline void geometry_column_check( SEXP x ) {
    R_xlen_t n = geometries::utils::get_sexp_length( x );
    if( n < 2 || n > 4) {
      Rcpp::stop("geometries - incorrect number of geometry columns");
    }
  }

  inline void column_check( SEXP x, SEXP cols ) {
    R_xlen_t n_col = geometries::utils::get_sexp_n_col( x );
    R_xlen_t n = geometries::utils::get_sexp_length( cols );
    if( n > n_col ) {
      Rcpp::stop("geometries - number of columns requested is greater than those available");
    }

    if( TYPEOF( cols ) == INTSXP ) {
      Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( cols );
      int m = Rcpp::max( iv );
      if( m > ( n_col - 1 ) ) {
        Rcpp::stop("geometries - invalid geometry column index");
      }
    }

  }

  // checks if an integer column index exists
  inline void column_exists( SEXP x, int& id_col ) {
    R_xlen_t n_col = geometries::utils::get_sexp_n_col( x );
    if( id_col > ( n_col - 1 ) ) {
      Rcpp::stop("geometries - id column index doesn't exist");
    }
  }

  // inline bool is_null_geometry( Rcpp::IntegerVector& iv, std::string geom_type ) {
  //   int n = iv.length();
  //   if( geom_type == "POINT" ) {
  //     if ( iv[0] == NA_INTEGER || iv[1] == NA_INTEGER ) {
  //       return true;
  //     }
  //   } else if ( n == 0 ) { // #nocov
  //     return true;         // #nocov
  //   }
  //   return false;
  // }
  //
  // inline bool is_null_geometry( Rcpp::NumericVector& nv, std::string geom_type ) {
  //   int n = nv.length();
  //   if( geom_type == "POINT" ) {
  //
  //     if (ISNAN( nv[0] ) || ISNAN( nv[1] ) ) {
  //       return true;
  //     }
  //   } else if ( n == 0 ) { // #nocov
  //     return true;         // #nocov
  //   }
  //   return false;
  // }
  //
  // inline bool is_null_geometry( SEXP& sfg, std::string geom_type ) {
  //   int n = get_sexp_length( sfg );
  //   if( geom_type == "POINT" ) {
  //     Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( sfg );
  //     if (ISNAN( nv[0] ) ) {
  //       return true;
  //     }
  //   } else if ( n == 0 ) {   // #nocov
  //     return true;           // #nocov
  //   }
  //   return false;
  // }

} // namespace utils
} // namespace geometries

#endif
