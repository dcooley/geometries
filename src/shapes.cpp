#include <Rcpp.h>


#include "geometries/geometries.hpp"
#include "geometries/nest/nest.hpp"
#include "geometries/coordinates/dimensions.hpp"


#include "geometries/utils/rleid/rleid.hpp"

// [[Rcpp::export]]
Rcpp::IntegerVector rcpp_rleid( Rcpp::DataFrame df, Rcpp::IntegerVector ids ) {
  return geometries::utils::rleid( df, ids );
}

// [[Rcpp::export]]
Rcpp::IntegerVector rcpp_rleid_indices( SEXP x ) {
  return geometries::utils::rleid_indices( x );
}


// [[Rcpp::export]]
SEXP rcpp_nest( SEXP x, int depth ) {
  return geometries::nest::nest_impl( x, depth );
}








