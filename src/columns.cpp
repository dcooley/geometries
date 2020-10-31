#include "geometries/utils/columns/columns.hpp"

// [[Rcpp::export]]
SEXP rcpp_other_columns(
    SEXP x,
    SEXP id_cols,
    SEXP id_col2,
    SEXP id_col3
) {
  return geometries::utils::other_columns( x, id_cols, id_col2, id_col3 );
}


// [[Rcpp::export]]
SEXP rcpp_column_positions(
  SEXP x,
  SEXP cols
) {
  return geometries::utils::column_positions( x, cols );
}

// /*
//  * Given a matrix with names, and columns, returns the integer-index
//  * of those columsn
//  */
// // [[Rcpp::export]]
// Rcpp::IntegerVector rcpp_column_positions(
//     SEXP m,
//     Rcpp::StringVector cols
// ) {
//   return geometries::utils::column_positions( m, cols );
// }
