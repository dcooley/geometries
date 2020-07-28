
#include "geometries/utils/lines/lines.hpp"

// [[Rcpp::export]]
SEXP rcpp_id_positions( SEXP x, SEXP i) {
  return geometries::utils::id_positions( x, i );
}
