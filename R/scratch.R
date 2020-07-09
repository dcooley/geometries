#
# df <- ggplot2::map_data("state")
#
# geom <- geometries::gm_geometries(df, c(5), c(1,2))
# geom[[8]]
# # [,1]     [,2]
# # [1,] -77.13731 38.94394
# # [2,] -77.06283 38.99551
# # [3,] -77.01699 38.97259
# # [4,] -76.93105 38.89238
# # [5,] -77.05136 38.80643
# # [6,] -77.05136 38.82935
# # [7,] -77.06283 38.86373
# # [8,] -77.07428 38.88664
# # [9,] -77.09720 38.90956
# # [10,] -77.13731 38.94394
#
# geom <- geometries::gm_geometries(df, c(5), c(1,2), "my_amazing_class")
# geom[[8]]
# # [,1]     [,2]
# # [1,] -77.13731 38.94394
# # [2,] -77.06283 38.99551
# # [3,] -77.01699 38.97259
# # [4,] -76.93105 38.89238
# # [5,] -77.05136 38.80643
# # [6,] -77.05136 38.82935
# # [7,] -77.06283 38.86373
# # [8,] -77.07428 38.88664
# # [9,] -77.09720 38.90956
# # [10,] -77.13731 38.94394
# # attr(,"class")
# # [1] "my_amazing_class"
#
#
# Rcpp::cppFunction(
#   depends = "geometries"
#   , includes = '#include "geometries/geometries.hpp"'
#   , code = '
#     SEXP make_geometry( SEXP x, SEXP id_cols, SEXP geometry_cols, Rcpp::Nullable< Rcpp::StringVector >  cls_attr ) {
#       return geometries::make_geometries( x, id_cols, geometry_cols, cls_attr );
#     }
#   '
# )
#
# geom <- make_geometry( df, c(4L), c(0L,1L), NULL )
# geom[[8]]
# # [,1]     [,2]
# # [1,] -77.13731 38.94394
# # [2,] -77.06283 38.99551
# # [3,] -77.01699 38.97259
# # [4,] -76.93105 38.89238
# # [5,] -77.05136 38.80643
# # [6,] -77.05136 38.82935
# # [7,] -77.06283 38.86373
# # [8,] -77.07428 38.88664
# # [9,] -77.09720 38.90956
# # [10,] -77.13731 38.94394
#
#
# geom <- make_geometry( df, c(4L), c(0L,1L), "my_line_class" )
# geom[[8]]
# # [,1]     [,2]
# # [1,] -77.13731 38.94394
# # [2,] -77.06283 38.99551
# # [3,] -77.01699 38.97259
# # [4,] -76.93105 38.89238
# # [5,] -77.05136 38.80643
# # [6,] -77.05136 38.82935
# # [7,] -77.06283 38.86373
# # [8,] -77.07428 38.88664
# # [9,] -77.09720 38.90956
# # [10,] -77.13731 38.94394
# # attr(,"class")
# # [1] "my_line_class"




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

