#ifndef R_GEOMETRIES_GEOMETRIES_COORDINATES_H
#define R_GEOMETRIES_GEOMETRIES_COORDINATES_H

#include "geometries/utils/lists/collapse.hpp"

namespace geometries {
namespace coordinates {

  /*
   * Each of these functions turn individual geometries
   * into list structures
   * list(
   *   x = c()
   *   , y = c()
   *   , z = c()
   *   , .... etc
   * )
   *
   *
   */

  // each of these functions turn the geometries into a list
  //

  inline Rcpp::List coordinates( SEXP& geometry, R_xlen_t& geometry_rows );  // forward declaration

  // vectors - no need for an id column
  template< int RTYPE >
  inline Rcpp::List coordinates(
    Rcpp::Vector< RTYPE >& geometry,
    R_xlen_t& geometry_rows
  ) {
    R_xlen_t n = geometry.length();
    R_xlen_t i;
    Rcpp::List res( n );
    for( i = 0; i < n; ++i ) {
      res[i] = geometry[i];
    }
    geometry_rows = 1;
    return res;
  }

  template< int RTYPE >
  inline Rcpp::List coordinates(
    Rcpp::Matrix< RTYPE >& geometry,
    R_xlen_t& geometry_rows
  ) {
    R_xlen_t n = geometry.ncol();
    R_xlen_t i;
    Rcpp::List res( n );
    for( i = 0; i < n; ++i ) {
      res[ i ] = geometry( Rcpp::_, i );
    }
    geometry_rows = geometry.nrow();
    return res;
  }

  // a single geometry which is in a list should
  // all be nested at the same level
  // and have the same diemensions
  inline Rcpp::List coordinates(
    Rcpp::List& geometry,
    R_xlen_t& geometry_rows
  ) {
    R_xlen_t i;
    R_xlen_t n = geometry.length();
    R_xlen_t total_rows = 0;
    Rcpp::List res( n );
    for(i = 0; i < n; ++i ) {
      SEXP inner_geometry = geometry[ i ];
      res[ i ] = coordinates( inner_geometry, total_rows );
    }
    geometry_rows += total_rows;
    Rcpp::Rcout << "geometry_rows: " << geometry_rows << std::endl;
    return geometries::utils::collapse_list< REALSXP >( res, geometry_rows );
  }

  inline Rcpp::List coordinates(
    SEXP& geometry,
    R_xlen_t& geometry_rows
  ) {
    switch( TYPEOF( geometry ) ) {
    case INTSXP: {
      if( Rf_isMatrix( geometry ) ) {
        Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( geometry );
        return coordinates( im, geometry_rows );
      } else {
        Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( geometry );
        return coordinates( iv, geometry_rows );
      }
    }
    case REALSXP: {
      if( Rf_isMatrix( geometry ) ) {
        Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( geometry );
        return coordinates( nm, geometry_rows );
      } else {
        Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( geometry );
        return coordinates( nv, geometry_rows );
      }
    }
    case VECSXP: {
      if( Rf_isNewList( geometry ) ) {
        Rcpp::List lst = Rcpp::as< Rcpp::List >( geometry );
        return coordinates( lst, geometry_rows );
      } else {
        Rcpp::stop("geometries - case not handled");
      }
    }
    }
  }


} // coordinates
} // geometries

#endif
