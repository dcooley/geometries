#include <Rcpp.h>

#include "geometries/bbox/bbox.hpp"

// ----------------------------
// bbox.hpp

/*
 * testing Numeric and Integer bboxes are created
 */
SEXP test_bbox() {

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

// ----------------------------
// rleid.hpp

#include "geometries/utils/rleid/rleid.hpp"

SEXP test_rleid() {

  Rcpp::NumericVector x = {1,1,2,2,2,3};
  Rcpp::NumericVector y = {1,1,1,2,2,2};
  Rcpp::NumericVector z = {1,2,3,4,5,6};

  Rcpp::List l = Rcpp::List::create(
    Rcpp::_["x"] = x,
    Rcpp::_["y"] = y,
    Rcpp::_["z"] = z
  );
  Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( l );

  Rcpp::IntegerVector id1 = {0};
  Rcpp::IntegerVector id2 = {0,1};
  Rcpp::IntegerVector id3 = {0,1,2};

  Rcpp::IntegerVector xx = geometries::utils::rleid( df, id1 );
  Rcpp::IntegerVector xy = geometries::utils::rleid( df, id2 );
  Rcpp::IntegerVector xyz = geometries::utils::rleid( df, id3 );

  return Rcpp::List::create(
    Rcpp::_["x"] = xx,
    Rcpp::_["y"] = xy,
    Rcpp::_["z"] = xyz
  );

}

// [[Rcpp::export(.tests)]]
SEXP tests() {
  Rcpp::List mb = test_bbox();
  Rcpp::List rleid = test_rleid();
  return Rcpp::List::create(
    Rcpp::_["test_bbox"] = mb,
    Rcpp::_["test_rleid"] = rleid
  );
}

