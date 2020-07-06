#
# # library(Rcpp)
# #
# # cppFunction(
# #   includes = '#include "geometries/utils/rleid/rleid.hpp"'
# #   , code = '
# #     Rcpp::IntegerVector rcpp_rleid( Rcpp::DataFrame df, Rcpp::IntegerVector ids ) {
# #       return geometries::utils::rleid( df, ids );
# #     }
# #   '
# # )
# #
#
# #
# # df <- data.frame(
# #   id = 1:4
# #   , x = 1:4
# #   , y = 4:1
# # )
# #
# # gm_make_geometries( df, 1, c(2,3), c("XY","POINT","sfg"))
#
#
# library(Rcpp)
#
# cppFunction(
#   code = '
#     Rcpp::IntegerVector intNames( Rcpp::List x, Rcpp::StringVector s ) {
#       Rcpp::IntegerVector ians( s.length() );
#       Rcpp::StringVector nms = x.names();
#       R_xlen_t i, j;
#       for(i = 0; i < s.length(); ++i ) {
#         const char * id = s[ i ];
#         for(j = 0; j < nms.length(); ++j ) {
#           const char * n = nms[ j ];
#           if( strcmp( id, n ) == 0 ) {
#             ians[ i ] = j;
#             break;
#           }
#         }
#       }
#       return ians;
#     }
#   '
# )
#
# df <- data.frame(
#   id = 1
#   , id2 = 1
#   , x = 1
#   , y = 1
# )
#
# intNames( df, c("id","id2","y") )
#
#

# library(Rcpp)
#
# cppFunction(
#   code = '
#     Rcpp::List mat_to_list( Rcpp::NumericMatrix mat ) {
#       Rcpp::StringVector nms = Rcpp::colnames( mat );
#       Rcpp::Rcout << "nms: " << nms << std::endl;
#
#       return Rcpp::as< Rcpp::List >( mat );
#     }
#   '
# )
#
# m <- matrix(1:4, ncol =2 )
# dimnames(m) <- list(NULL, c("foo","bar"))
# mat_to_list( m )

