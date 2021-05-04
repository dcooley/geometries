#include "geometries/utils/lists/unlist.hpp"

// [[Rcpp::export]]
SEXP rcpp_unlist_list( Rcpp::List lst ) {
  return geometries::utils::unlist_list( lst );
}
