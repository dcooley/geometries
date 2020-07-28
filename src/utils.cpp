#include <Rcpp.h>
#include "geometries/utils/utils.hpp"



// // [[Rcpp::export]]
// Rcpp::DataFrame rcpp_subset_dataframe(
//   Rcpp::DataFrame df,
//   Rcpp::StringVector cols,
//   int start,
//   int end
// ) {
//   return geometries::utils::subset_dataframe(df, cols, start, end);
// }

// [[Rcpp::export]]
SEXP rcpp_concatenate_vectors(
    SEXP vec_1,
    SEXP vec_2
) {
  return geometries::utils::concatenate_vectors( vec_1, vec_2 );
}

/*
 * Given a matrix with names, and columns, returns the integer-index
 * of those columsn
 */
// [[Rcpp::export]]
Rcpp::IntegerVector rcpp_column_positions(
    SEXP m,
    Rcpp::StringVector cols
) {
  return geometries::utils::column_positions( m, cols );
}

// [[Rcpp::export]]
int rcpp_where_is(
    Rcpp::String to_find,
    Rcpp::StringVector sv
) {
  return geometries::utils::where_is( to_find, sv );
}

// [[Rcpp::export]]
SEXP rcpp_get_ids(
    SEXP x,
    SEXP id_col
) {
  return geometries::utils::get_ids( x, id_col );
}
