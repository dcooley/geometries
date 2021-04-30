#include <Rcpp.h>

#include "geometries/nest/nest.hpp"

// [[Rcpp::export]]
SEXP rcpp_nest( SEXP x, int depth ) {
  return geometries::nest::nest_impl( x, depth );
}
