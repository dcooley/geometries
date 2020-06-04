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
  // of coordinates and ids

  inline Rcpp::List coordinates( SEXP& geometry, R_xlen_t& geometry_rows );  // forward declaration

  // vectors - no need for an id column
  template< int RTYPE, typename T >
  inline Rcpp::List coordinates(
    Rcpp::Vector< RTYPE >& geometry,
    R_xlen_t& geometry_rows,
    T& id
  ) {
    R_xlen_t n_col = geometry.length();
    R_xlen_t n_row = 1;
    R_xlen_t i;
    Rcpp::List res( n_col + 1 );
    Rcpp::Vector< RTYPE > idv = Rcpp::rep( id, n_row );
    res[0] = idv;
    for( i = 0; i < n_col; ++i ) {
      res[i + 1] = geometry[i];
    }
    geometry_rows = 1;
    return res;
  }

  template< int RTYPE >
  inline Rcpp::List coordinates(
    Rcpp::Vector< RTYPE >& geometry,
    R_xlen_t& geometry_rows
  ) {
    typedef typename Rcpp::traits::storage_type< RTYPE >::type T;
    T id = 1;
    return coordinates( geometry, geometry_rows, id );
  }

  template< int RTYPE, typename T >
  inline Rcpp::List coordinates(
    Rcpp::Matrix< RTYPE >& geometry,
    R_xlen_t& geometry_rows,
    T& id
  ) {
    R_xlen_t n_col = geometry.ncol();
    R_xlen_t n_row = geometry.nrow();
    R_xlen_t i;
    Rcpp::List res( n_col + 1 );
    Rcpp::Vector< RTYPE > idv = Rcpp::rep( id, n_row );
    res[0] = idv;
    for( i = 0; i < n_col; ++i ) {
      res[ i + 1 ] = geometry( Rcpp::_, i );
    }
    geometry_rows = geometry.nrow();
    return res;
  }

  template< int RTYPE >
  inline Rcpp::List coordinates(
    Rcpp::Matrix< RTYPE >& geometry,
    R_xlen_t& geometry_rows
  ) {
    typedef typename Rcpp::traits::storage_type< RTYPE >::type T;
    T id = 1;
    return coordinates( geometry, geometry_rows, id );
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
    Rcpp::List res( n );
    for(i = 0; i < n; ++i ) {
      R_xlen_t total_rows = 0;
      SEXP inner_geometry = geometry[ i ];
      res[ i ] = coordinates( inner_geometry, total_rows );
      geometry_rows += total_rows;
    }
    // geometry_rows is required because 'collapse_list' needs to know how long
    // each vector needs to be
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
      }
    }
    default: {
      Rcpp::stop("geometries - can't access coordinates for this object");
    }
    }
    return Rcpp::List::create(); // #nocov never reaches
  }


} // coordinates
} // geometries

#endif
