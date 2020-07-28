
#include "geometries/utils/close/close.hpp"

// [[Rcpp::export]]
SEXP rcpp_close_matrix( Rcpp::List x ) {
  return geometries::utils::close_matrix( x );
}
