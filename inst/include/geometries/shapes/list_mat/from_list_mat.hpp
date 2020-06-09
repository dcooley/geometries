#ifndef R_GEOMETRIES_SHAPES_FROM_LIST_MAT_H
#define R_GEOMETRIES_SHAPES_FROM_LIST_MAT_H

// converts nested list[[ matrix ]] structure into a list

#include <Rcpp.h>

#include "geometries/utils/lists/collapse.hpp"

namespace geometries {
namespace shapes {

  // template< int RTYPE >
  // inline Rcpp::List matrix_to_list(
  //     Rcpp::Matrix< RTYPE >& mat,
  //     R_xlen_t& geometry_rows
  //   ) {
  //   R_xlen_t n_col = mat.ncol();
  //   Rcpp::List res( n_col );
  //   R_xlen_t i;
  //   for( i = 0; i < n_col; ++i ) {
  //     res[ i ] = mat( Rcpp::_, i );
  //   }
  //   geometry_rows += mat.nrow();
  //   return res;
  // }


  // /*
  //  * Takes a list of matrices and converts to a single list object
  //  */
  // template< int RTYPE >
  // inline Rcpp::List from_listMat(
  //     Rcpp::List& lst,
  //     R_xlen_t& geometry_rows
  //   ) {
  //
  //   R_xlen_t n = lst.size();
  //   R_xlen_t i;
  //   Rcpp::List res( n );
  //   for( i = 0; i < n; ++i ) {
  //     Rcpp::Matrix< RTYPE > mat = Rcpp::as< Rcpp::Matrix< RTYPE > >( lst[ i ] );
  //     res[ i ] = matrix_to_list< RTYPE >( mat, geometry_rows );
  //   }
  //   res = geometries::utils::collapse_list< RTYPE >( res, geometry_rows );
  //   return res;
  // }



} // shapes
} // geometries

#endif
