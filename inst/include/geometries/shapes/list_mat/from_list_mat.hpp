#ifndef R_GEOMETRIES_SHAPES_FROM_LIST_MAT_H
#define R_GEOMETRIES_SHAPES_FROM_LIST_MAT_H

// converts nested list[[ matrix ]] structure into a list

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
    geometry_rows = mat.nrow();
    return res;
  }

  template< int RTYPE >
  inline Rcpp::List from_listMat(
      Rcpp::List& lst,
      R_xlen_t& geometry_rows
    ) {

    R_xlen_t n = lst.size();
    R_xlen_t i;
    R_xlen_t res( n );
    R_xlen_t total_rows = 0;
    for( i = 0; i < n; ++i ) {
      Rcpp::Matrix< RTYPE > mat = lst[ i ];
      total_rows = total_rows + mat.nrow();
      res[ i ] = matrix_to_list< RTYPE >( mat, geometry_rows );
    }
    geometry_rows = total_rows;
    res = collapse_list< RTYPE >( res, geometry_rows );
    return res;
  }


} // shapes
} // geometries

#endif
