
#include <Rcpp.h>
#include "geometries/geometries.hpp"


// [[Rcpp::export]]
SEXP rcpp_make_geometries(
    SEXP x,
    SEXP id_cols,
    SEXP geometry_cols,
    Rcpp::List attributes,
    bool close
  ) {
  return geometries::make_geometries( x, id_cols, geometry_cols, attributes, close );
}
