
#include <Rcpp.h>
#include "geometries/coordinates/dimensions.hpp"

// [[Rcpp::export]]
SEXP rcpp_geometry_dimensions( SEXP geometries ) {
  return geometries::coordinates::geometry_dimensions( geometries );
}
