#ifndef R_GEOMETRIES_GEOMETRIES_COORDINATES_H
#define R_GEOMETRIES_GEOMETRIES_COORDINATES_H

#include "geometries/utils/sexp/sexp.hpp"

namespace geometries {
namespace coordinates {

  inline void count_coordinates(
      SEXP& sfg,
      R_xlen_t& sfg_count
  ) {

    switch( TYPEOF( sfg ) ) {
    case INTSXP: {}
    case REALSXP: {
      if( !Rf_isMatrix( sfg ) ) {
      //Rcpp::stop("sfheaders - unsupported coordinate type");
      // it's a vector, right?
      sfg_count += 1;
    } else {
      sfg_count += geometries::utils::sexp_n_row( sfg );
    }
    break;
    }
    case VECSXP: {
      if( Rf_inherits( sfg, "data.frame" ) ) {
      Rcpp::stop("geometries - unsupported coordinate type");  // #nocov
    }
      Rcpp::List lst = Rcpp::as< Rcpp::List >( sfg );
      //if (lst.size() == 0 ) {
      //return 0; // ?
      //}
      R_xlen_t n = lst.size();
      R_xlen_t i;
      Rcpp::IntegerVector res( n );
      for( i = 0; i < n; ++i ) {
        SEXP tmp_sfg = lst[i];
        count_coordinates( tmp_sfg, sfg_count );  // recurse
      }
      break;
    }
    default: {
      Rcpp::stop("geometries - unsupported coordinate type");  // #nocov
    }
    }
  }

} // coordinates
} // geometriees

#endif
