#include <Rcpp.h>
#include "geometries/shapes/shapes.hpp"


// POINTS -----------
// [[Rcpp::export]]
SEXP rcpp_get_vec(
    SEXP x,
    SEXP cols
) {
  return geometries::shapes::get_vec( x, cols );
}

// LINE ----------
// [[Rcpp::export]]
SEXP rcpp_to_mat(
    SEXP x,
    SEXP cols
) {
  return geometries::shapes::to_mat( x, cols );
}

// LINES -----------
// [[Rcpp::export]]
SEXP rcpp_get_list_mat(
    SEXP x,
    SEXP cols,
    SEXP id
) {
  return geometries::shapes::to_listMat( x, cols, id );
}
