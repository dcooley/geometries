#include "geometries/utils/columns/columns.hpp"

// [[Rcpp::export]]
SEXP rcpp_other_columns( SEXP x, SEXP col1, SEXP col2 ) {
  return geometries::utils::other_columns( x, col1, col2 );
}
