#include <Rcpp.h>
#include "geometries/geometries/list_mat.hpp"


// [[Rcpp::export]]
SEXP list_mat( SEXP x, SEXP geometry_cols, SEXP id_col ) {
  return geometries::geom::geom_list_mat( x, geometry_cols, id_col );
}
