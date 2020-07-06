
# library(Rcpp)
#
# cppFunction(
#   includes = '#include "geometries/utils/rleid/rleid.hpp"'
#   , code = '
#     Rcpp::IntegerVector rcpp_rleid( Rcpp::DataFrame df, Rcpp::IntegerVector ids ) {
#       return geometries::utils::rleid( df, ids );
#     }
#   '
# )
#
