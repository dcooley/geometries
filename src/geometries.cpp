
#include <Rcpp.h>
#include "geometries/geometries.hpp"


// [[Rcpp::export]]
SEXP rcpp_make_geometries(
    Rcpp::DataFrame df,
    Rcpp::IntegerVector id_cols,
    Rcpp::IntegerVector geometry_cols,
    Rcpp::Nullable< Rcpp::StringVector > class_attributes = R_NilValue
  ) {
  return geometries::make_geometries( df, id_cols, geometry_cols, class_attributes );
}
