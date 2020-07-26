
#include "geometries/utils/columns/columns.hpp"

// [[Rcpp::export]]
SEXP rcpp_other_columns( SEXP x ) {
  return geometries::utils::other_columns( x );
}
