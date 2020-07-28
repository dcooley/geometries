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
