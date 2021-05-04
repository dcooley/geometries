#
# ## Multipolygon structure
# lst <- list(
#   list(
#     list(
#       1:5, 10:15
#     )
#     , list(
#       20:30
#     )
#   )
# )
#
# lst
#
#
# geometries:::gm_dimensions( lst )
# geometries:::rcpp_nest( lst, 2 )
#
#
#
# df <- data.frame(
#   x = 1:20
#   , y = 1:20
#   , val = 1:20
#   , id1 = rep(1,20)
#   , id2 = c(rep(1,10),rep(2,10))
#   , id3 = c(rep(1,5), rep(2,5), rep(1,5), rep(2,5))
#   )
#
# df
#
# sf <- sfheaders::sf_multipolygon(
#   obj = df
#   , x = "x"
#   , y = "y"
#   , multipolygon_id = "id1"
#   , polygon_id = "id2"
#   , linestring_id = "id3"
#   , keep = TRUE
#   , list_columns = "val"
# )
#
# library(sf)
#
# geometries:::gm_dimensions( sf[1, ]$val )
# geometries:::rcpp_nest( sf[1, ]$val, 2 )
#
#
# nc <- sf::st_read(system.file("./shape/nc.shp", package = "sf"))
#
# for( i in 1:nrow(nc) ) {
#
#   res <- geometries:::rcpp_nest( nc[i, ]$geometry, 2 )
#
# }
#
# sf_line <- sfheaders::sf_cast( nc, "LINESTRING" )
#
# nc[3, ]$geometry[[1]][[]]
#
# geometries:::gm_dimensions( nc[4, ]$geometry )
# geometries:::rcpp_nest( nc[4, ]$geometry, 5 )
# geometries:::rcpp_nest( nc[4, ]$geometry, 4 )
# geometries:::rcpp_nest( nc[4, ]$geometry, 3 )
# geometries:::rcpp_nest( nc[4, ]$geometry, 2 )
# geometries:::rcpp_nest( nc[4, ]$geometry, 1 )
#
#
#
#
# df <- data.frame(
#   x = 1:20
#   , y = 1:20
#   , val = 1:20
#   , id1 = rep(1,20)
#   , id2 = c(rep(1,10),rep(2,10))
#   , id3 = c(rep(1,5), rep(2,5), rep(1,5), rep(2,5))
# )
#
# df
#
# sf <- sfheaders::sf_multipolygon(
#   obj = df
#   , x = "x"
#   , y = "y"
#   , multipolygon_id = "id1"
#   , polygon_id = "id2"
#   , linestring_id = "id3"
#   , keep = TRUE
#   , list_columns = "val"
# )
#
# geometries:::rcpp_nest( sf$val, 2 )  ## MP to LINESTRING
# sfheaders:::sfc_cast( sf$geometry, "LINESTRING" )
#
# geometries:::rcpp_nest( sf$val, 3 )  ## MP to POLYGON
# sfheaders:::sfc_cast( sf$geometry, "POLYGON" )
#
#
# sf <- sfheaders::sf_polygon(
#   obj = df
#   , x = "x"
#   , y = "y"
# #  , multipolygon_id = "id1"
#   , polygon_id = "id2"
#   , linestring_id = "id3"
#   , keep = TRUE
#   , list_columns = "val"
# )
#
# geometries:::rcpp_nest( sf$val, 1 )  ## POLYGON to LINESTRING
# sfheaders:::sfc_cast( sf$geometry, "LINESTRING" )
#
# geometries:::rcpp_nest( sf$val, 3 )  ## POLYGON to MULTIPOLYGON
# sfheaders:::sfc_cast( sf$geometry, "MULTIPOLYGON" )
#
#
#
#
#
#
#
#
