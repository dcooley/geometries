#include <Rcpp.h>

#include "geometries/shapes/shapes.hpp"

#include "geometries/coordinates/dimensions.hpp"


// POINTS -----------
// [[Rcpp::export]]
SEXP rcpp_get_vec(
    SEXP x,
    SEXP cols
) {
  return geometries::shapes::to_vec( x, cols );
}

// LINE ----------
// [[Rcpp::export]]
SEXP rcpp_to_mat(
    SEXP x,
    SEXP cols
) {
  return geometries::shapes::to_mat( x, cols );
}

// LINES -----------
// [[Rcpp::export]]
SEXP rcpp_get_list_mat(
    SEXP x,
    SEXP cols,
    SEXP id
) {
  return geometries::shapes::to_listMat( x, cols, id );
}


// converting objects to a single matrix/list/data.frame
// iterate and get all dimensions.
//

// [[Rcpp::export]]
SEXP rcpp_coordinates( Rcpp::List& sfc ) {

  Rcpp::IntegerMatrix dimensions = geometries::coordinates::geometry_dimensions( sfc );
  return dimensions;

}


