
#include <Rcpp.h>
#include "geometries/coordinates/coordinates_impl.hpp"

// [[Rcpp::export]]
SEXP rcpp_geometry_dimensions( SEXP geometries ) {
  return geometries::coordinates::geometry_dimensions( geometries );
}

/*
 * Returns the coordinates of a single geometry
 */
// [[Rcpp::export]]
SEXP rcpp_coordinates( SEXP& geometries ) {
  return geometries::coordinates::coordinates_impl( geometries );
}
