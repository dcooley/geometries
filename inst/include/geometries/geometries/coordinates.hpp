#ifndef R_GEOMETRIES_GEOMETRIES_COORDINATES_H
#define R_GEOMETRIES_GEOMETRIES_COORDINATES_H

#include "geometries/utils/sexp/sexp.hpp"

namespace geometries {
namespace coordinates {

  inline void count_coordinates(
      SEXP& geom,
      R_xlen_t& geom_count
  ) {

    switch( TYPEOF( geom ) ) {
    case INTSXP: {}
    case REALSXP: {
      if( !Rf_isMatrix( geom ) ) {
      //Rcpp::stop("sfheaders - unsupported coordinate type");
      // it's a vector, right?
      geom_count += 1;
    } else {
      geom_count += geometries::utils::sexp_n_row( geom );
    }
    break;
    }
    case VECSXP: {
      if( Rf_inherits( geom, "data.frame" ) ) {
      Rcpp::stop("geometries - unsupported coordinate type");  // #nocov
    }
      Rcpp::List lst = Rcpp::as< Rcpp::List >( geom );
      //if (lst.size() == 0 ) {
      //return 0; // ?
      //}
      R_xlen_t n = lst.size();
      R_xlen_t i;
      Rcpp::IntegerVector res( n );
      for( i = 0; i < n; ++i ) {
        SEXP tmp_geom = lst[i];
        count_coordinates( tmp_geom, geom_count );  // recurse
      }
      break;
    }
    default: {
      Rcpp::stop("geometries - unsupported coordinate type");  // #nocov
    }
    }
  }

  /*
   * Returns a matrix giving the start and end indices of each coordinate
   * in a collection
   */
  inline Rcpp::IntegerMatrix coordinate_indices(
      Rcpp::List& geometries
  ) {

    // if I make this cumulative, it gives me a vector where the last element
    // is the size of any result, and each element
    // is the row index where a new element starts

    R_xlen_t cumulative_coords = 0;
    R_xlen_t n = geometries.size();
    Rcpp::IntegerMatrix res( n, 2 );
    R_xlen_t i;

    for( i = 0; i < n; ++i ) {
      R_xlen_t geom_counter = 0;
      SEXP geom = geometries[i];
      geometries::coordinates::count_coordinates( geom, geom_counter );

      res( i, 0 ) = cumulative_coords;
      cumulative_coords += geom_counter;
      res( i, 1 ) = cumulative_coords - 1;
    }
    return res;
  }

} // coordinates
} // geometriees

#endif
