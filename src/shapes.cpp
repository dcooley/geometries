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


// // [[Rcpp::export]]
// SEXP rcpp_nest( SEXP x, int depth ) {
//
//   // Need to know the depth of the current item, in order to know how deep to go
//   Rcpp::List dimension = geometries::coordinates::geometry_dimensions( x );
//   int current_depth = dimension["max_nest"];
//
//   if( current_depth == depth ) {
//     // already at the right depth
//     return x;
//   }
//
//   if( current_depth > depth ) {
//     // need to unnest
//     int unnest_depth = current_depth - depth;
//     return geometries::nest::unnest( x, unnest_depth );
//   }
//
//   int nest_depth = depth - current_depth;
//   return geometries::nest::nest( x, nest_depth );
//   // if current_depth > depth, need to unnest
//   // if current_dept < depth, need to nest further
// }








