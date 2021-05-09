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

// [[Rcpp::export]]
SEXP rcpp_list_sizes( Rcpp::List lst ) {
  R_xlen_t total_size = 0;
  int existing_type = 10;
  return geometries::utils::list_size( lst, total_size, existing_type );
}

