
#include <Rcpp.h>
#include "geometries/bbox/bbox.hpp"

/*
 * calculate bbox
 *
 * assumes 2-column object, in the order x, y
 */
// [[Rcpp::export]]
SEXP rcpp_calculate_bbox( SEXP x, SEXP geometry_cols ) {
  Rcpp::NumericVector bbox(4);  // xmin, ymin, xmax, ymax
  bbox(0) = bbox(1) = bbox(2) = bbox(3) = NA_REAL;
  geometries::bbox::calculate_bbox( bbox, x, geometry_cols );
  return bbox;
}

