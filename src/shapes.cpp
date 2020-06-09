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


// // [[Rcpp::export]]
// SEXP rcpp_from_listMat( Rcpp::List lst ) {
//   R_xlen_t geometry_rows = 0;
//   return geometries::shapes::from_listMat< REALSXP >( lst, geometry_rows );
// }



SEXP nest( SEXP x, R_xlen_t depth ) {
  if( depth < 1 ) {
    return x;
  }

  Rcpp::List res(1);
  res[0] = x;   // first level
  //depth = depth - 1;
  while( depth > 0 ) {
    Rcpp::Rcout << "nesting depth: " << depth << std::endl;
    return nest( res, depth - 1 );
    depth--;
  }
  return res;
}

SEXP unnest( SEXP x, R_xlen_t depth ) {
  // inside this function the dimension of x shoudl already be known
  // And it will only work on nested list objects
  if( !Rf_isNewList( x ) ) {
    Rcpp::stop("geometries - can only unnest list objects");
  }

  Rcpp::List lst = Rcpp::as< Rcpp::List >( x );
  if( lst.length() != 1 ) {
    Rcpp::stop("geometries - error trying to unnest the object");
  }
  SEXP res = lst[0];

  // depth will be a positive number
  // because it's the depth we need to get to, so can only be positive (or 0)
  while( depth > 1 ) {
    return unnest( res, depth - 1 );
    depth--;
  }
  return res;
}

// [[Rcpp::export]]
SEXP rcpp_nest( SEXP x, R_xlen_t depth ) {
  // extract each inner-list element
  // designed to work on nested lists

  // Need to know the depth of the current item, in order to know how deep to go
  Rcpp::List dimension = geometries::coordinates::geometry_dimensions( x );
  R_xlen_t current_depth = dimension["max_nest"];
  Rcpp::Rcout << "current_depth: " << current_depth << std::endl;

  if( current_depth == depth ) {
    // already at the right depth
    return x;
  }

  //R_xlen_t depth_difference = (current_depth > depth) ? ( current_depth - depth ) : ( depth - current_depth );

  if( current_depth > depth ) {
    // need to unnest
    R_xlen_t unnest_depth = current_depth - depth;
    Rcpp::Rcout << "unnest_depth: " << unnest_depth << std::endl;
    return unnest( x, unnest_depth );
  }

  R_xlen_t nest_depth = depth - current_depth;
  Rcpp::Rcout << "nest_depth: " << nest_depth << std::endl;
  return nest( x, nest_depth );
  // if current_depth > depth, need to unnest
  // if current_dept < depth, need to nest further
}








