#ifndef R_GEOMETRIES_GEOMETRIES_COORDINATES_H
#define R_GEOMETRIES_GEOMETRIES_COORDINATES_H

#include "geometries/utils/sexp/sexp.hpp"

namespace geometries {
namespace coordinates {

  /*
   * Count Coordinates
   *
   * counts the number of coordinates in a single geometry
   * If the input is a List, it returns the total number of coordinates
   * in each geometry inside the list
   */
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
   * in a geometry.
   *
   * If the geometry is a list of three matrices, it will return 3x2 matrix
   * Where column 0 is the start index, and column 1 is the end index
   *
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



  /*
   * Returns a matrix giving the start and end indices of each coordinate
   * in a geometry.
   *
   * If the input is a non-list
   * the result matrix is 1x2
   *
   */
  inline Rcpp::IntegerMatrix coordinate_indices(
    SEXP& geometries
  ) {

    if( Rf_isMatrix( geometries ) ) {
      Rcpp::IntegerMatrix im(1,2);
      im(0,1) = geometries::utils::sexp_n_row( geometries );
      return im;
    } else if( Rf_isNewList( geometries ) ) {
      Rcpp::List lst = Rcpp::as< Rcpp::List >( geometries );
      return coordinate_indices( lst );
    }

    // TODO - handle a vector input
    Rcpp::stop("geometries - unsupported type for counting coordinates");
    Rcpp::IntegerMatrix res;
    return res;
  }

} // coordinates
} // geometriees

#endif
