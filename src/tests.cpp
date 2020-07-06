#include <Rcpp.h>

#include "geometries/bbox/bbox.hpp"

// ----------------------------
// bbox.hpp

/*
 * testing Numeric and Integer bboxes are created
 */
SEXP make_box() {

  Rcpp::NumericVector nv(4);  // xmin, ymin, xmax, ymax
  nv(0) = nv(1) = nv(2) = nv(3) = 0;

  Rcpp::NumericVector nx = {1,2,3,4};
  Rcpp::NumericVector ny = {1,2,3,4};
  geometries::bbox::make_bbox( nv, nx, ny );

  Rcpp::IntegerVector iv(4);  // xmin, ymin, xmax, ymax
  iv(0) = iv(1) = iv(2) = iv(3) = 0;

  Rcpp::IntegerVector ix = {1,2,3,4};
  Rcpp::IntegerVector iy = {1,2,3,4};
  geometries::bbox::make_bbox( iv, ix, iy );

  return Rcpp::List::create(
    Rcpp::_["REALSXP"] = nv,
    Rcpp::_["INTSXP"] = iv
  );

}

// [[Rcpp::export(.tests)]]
SEXP tests() {
  Rcpp::List mb = make_box();
  return Rcpp::List::create(
    Rcpp::_["make_box"] = mb
  );
}

