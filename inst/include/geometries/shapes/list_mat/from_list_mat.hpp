#ifndef R_GEOMETRIES_SHAPES_FROM_LIST_MAT_H
#define R_GEOMETRIES_SHAPES_FROM_LIST_MAT_H

// converts nested list[[ matrix ]] structure into a list

#include <Rcpp.h>

#include "geometries/utils/lists/collapse.hpp"

namespace geometries {
namespace shapes {

  template< int RTYPE >
  inline Rcpp::List matrix_to_list(
      Rcpp::Matrix< RTYPE >& mat,
      R_xlen_t& geometry_rows
    ) {

    R_xlen_t n_col = mat.ncol();
    Rcpp::List res( n_col );
    R_xlen_t i;
    for( i = 0; i < n_col; ++i ) {
      res[ i ] = mat( Rcpp::_, i );
    }
    geometry_rows += mat.nrow();
    return res;
  }

  inline Rcpp::List matrix_to_list(
    SEXP& mat,
    R_xlen_t& geometry_rows
  ) {
    switch( TYPEOF( mat ) ) {
    case INTSXP: {
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( mat );
      return matrix_to_list( im, geometry_rows );
    }
    case REALSXP: {
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( mat );
      return matrix_to_list( nm, geometry_rows );
    }
    default: {
      Rcpp::stop("geometries - expecting a matrix" );
    }
    }
    return Rcpp::List::create(); // #nocov never reaches
  }

  template< int RTYPE >
  inline Rcpp::List from_listMat(
      Rcpp::List& lst,
      R_xlen_t& geometry_rows
    ) {

    R_xlen_t n = lst.size();
    R_xlen_t i;
    Rcpp::List res( n );
    //R_xlen_t total_rows = 0;
    for( i = 0; i < n; ++i ) {
      SEXP mat = lst[i];
      //total_rows = total_rows + mat.nrow();
      res[ i ] = matrix_to_list( mat, geometry_rows );
    }
    //geometry_rows = total_rows;
    res = geometries::utils::collapse_list< RTYPE >( res, geometry_rows );
    return res;
  }



} // shapes
} // geometries

#endif
