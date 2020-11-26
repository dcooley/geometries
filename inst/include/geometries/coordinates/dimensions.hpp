#ifndef R_GEOMETRIES_GEOMETRIES_COORDINATES_DIMENSIONS_H
#define R_GEOMETRIES_GEOMETRIES_COORDINATES_DIMENSIONS_H

#include "geometries/utils/sexp/sexp.hpp"

namespace geometries {
namespace coordinates {

  /*
   * Dimensions
   *
   * counts the number of coordinates in a single geometry
   * If the input is a List, it returns the total number of coordinates
   * in each geometry inside the list
   */
  inline void geometry_dimension(
      SEXP& geom,
      R_xlen_t& geom_count,
      R_xlen_t& geom_dimension,
      R_xlen_t& nest,
      R_xlen_t& max_dimension,
      R_xlen_t& max_nest,
      SEXPTYPE& rtype
  ) {

    // assuming the nesting level is the same for all matrices in a list,
    // we only need the 'last' nesting level,
    // and not the cumulative

    switch( TYPEOF( geom ) ) {
      case INTSXP: {}
      case REALSXP: {
        rtype = TYPEOF( geom );
        if( !Rf_isMatrix( geom ) ) {
          // it's a vector, right?
          geom_count += 1;
          geom_dimension = geometries::utils::sexp_length( geom );
        } else {
          geom_count += geometries::utils::sexp_n_row( geom );
          geom_dimension = geometries::utils::sexp_n_col( geom );
        }
      break;
      }
      case VECSXP: {
        if( Rf_inherits( geom, "data.frame" ) ) {
        Rcpp::stop("geometries - unsupported coordinate type");
      }
        Rcpp::List lst = Rcpp::as< Rcpp::List >( geom );
        //if (lst.size() == 0 ) {
        //return 0; // ?
        //}
        R_xlen_t n = lst.size();
        R_xlen_t i;
        nest += 1;
        Rcpp::IntegerVector res( n );
        for( i = 0; i < n; ++i ) {
          SEXP tmp_geom = lst[i];
          geometry_dimension( tmp_geom, geom_count, geom_dimension, nest, max_dimension, max_nest, rtype );  // recurse
        }
        break;
      }
      default: {
        Rcpp::stop("geometries - unsupported coordinate type");
      }
    }

    max_dimension = geom_dimension > max_dimension ? geom_dimension : max_dimension;
    max_nest = nest > max_nest ? nest : max_nest;

  }

  inline void geometry_dimension(
      SEXP& geom,
      R_xlen_t& geom_count
  ) {
    R_xlen_t dimension = 0;
    R_xlen_t nest = 1;
    R_xlen_t max_dimension = 0;
    R_xlen_t max_nest = 0;
    SEXPTYPE rtype;
    geometry_dimension( geom, geom_count, dimension, nest, max_dimension, max_nest, rtype );
  }

  /*
   * Returns a list
   *
   * one element is a matrix giving the start and end indices of each coordinate
   * in a geometry.
   *
   * If the geometry is a list of three matrices, it will return 3x2 matrix
   * Where column 0 is the start index, and column 1 is the end index
   *
   */
  inline SEXP geometry_dimensions(
      Rcpp::List& geometries
  ) {

    // if I make this cumulative, it gives me a vector where the last element
    // is the size of any result, and each element
    // is the row index where a new element starts

    R_xlen_t cumulative_coords = 0;
    R_xlen_t n = geometries.size();
    Rcpp::IntegerMatrix res( n, 5 );
    R_xlen_t i;

    R_xlen_t max_dimension = 0;
    R_xlen_t max_nest = 0;

    for( i = 0; i < n; ++i ) {
      R_xlen_t geom_counter = 0;
      R_xlen_t geom_dimension = 0;
      R_xlen_t nest = 1;
      SEXPTYPE rtype;
      SEXP geom = geometries[i];

      geometries::coordinates::geometry_dimension(
        geom, geom_counter, geom_dimension, nest, max_dimension, max_nest, rtype
        );

      res( i, 0 ) = cumulative_coords;
      cumulative_coords += geom_counter;
      res( i, 1 ) = cumulative_coords - 1;
      res( i, 2 ) = geom_dimension;
      res( i, 3 ) = nest;
      res( i, 4 ) = rtype;
    }

    //return res;
    return Rcpp::List::create(
      Rcpp::_["dimensions"] = res,
      Rcpp::_["max_dimension"] = max_dimension,
      Rcpp::_["max_nest"] = max_nest
    );

  }



  /*
   * Returns a matrix giving the start and end indices of each coordinate
   * in a geometry.
   *
   * If the input is a non-list
   * the result matrix is 1x2
   *
   */
  inline SEXP geometry_dimensions(
    SEXP& geometries
  ) {

    if( Rf_isMatrix( geometries ) ) {
      Rcpp::IntegerMatrix im(1, 5); // initialise a (0,0) matrix
      // one row, because it's only one geometry
      // column '0' will start with 0, so no need to fill it
      R_xlen_t max_nest = 0;
      R_xlen_t max_dimension = geometries::utils::sexp_n_col( geometries );

      im(0, 1) = geometries::utils::sexp_n_row( geometries ) - 1;
      im(0, 2) = max_dimension;
      im(0, 3) = max_nest; // level of nesting (a matrix is not nested in a list)
      im(0, 4) = TYPEOF( geometries );

      return Rcpp::List::create(
        Rcpp::_["dimensions"] = im,
        Rcpp::_["max_dimension"] = max_dimension,
        Rcpp::_["max_nest"] = max_nest
      );

    } else if( Rf_isNewList( geometries ) ) {

      Rcpp::List lst = Rcpp::as< Rcpp::List >( geometries );
      return geometry_dimensions( lst );

    } else if ( TYPEOF( geometries ) == INTSXP || TYPEOF( geometries ) == REALSXP ) {
      // vectors - start and end at the same place
      Rcpp::IntegerMatrix im(1, 5); // initialise (0,0) matrix

      R_xlen_t max_nest = 0;
      R_xlen_t max_dimension = geometries::utils::sexp_length( geometries );

      im(0, 2) = max_dimension;
      im(0, 3) = max_nest;
      im(0, 4) = TYPEOF( geometries );

      return Rcpp::List::create(
        Rcpp::_["dimensions"] = im,
        Rcpp::_["max_dimension"] = max_dimension,
        Rcpp::_["max_nest"] = max_nest
      );
    }

    Rcpp::stop("geometries - unsupported type for counting coordinates");
    Rcpp::IntegerMatrix res;  // #nocov never reaches
    return res;               // #nocov never reaches
  }

} // coordinates
} // geometriees

#endif
