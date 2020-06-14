#
#
# df <- data.frame(
#   id1 = c(1,1,1,2,2,2,2)
#   , id2 = c(1,1,2,1,1,2,2)
#   , x = 1:7
#   , y = 1:7
# )
#
# geometries:::rcpp_nest2( df, c("id1","id2"), 2)
#
#
#
# ## design changes??
#
# df <- data.frame(
#   id1 = c(1,1,1,2,2,2,2,3)
#   , id2 = c(1,1,1,1,1,2,2,1)
#   , x = 1:8
#   , y = 1:8
# )
#
# # geometries:::id_positions( df$id1 )
# # geometries:::id_positions( df$id2 )
#
#
# # mat_ids <- as.matrix( df[, c("id1","id2")])
# # geometries:::rcpp_rleid( mat_ids )
#
#
# geometries:::rcpp_rleid( df, c(0,1) )
#
# library(data.table)
#
# n <- 1e5
# df <- data.frame(
#   id1 = sample( 1:20, size = n, replace = T )
#   , id2 = sample( 1:3, size = n, replace = T)
# )
#
# me <- geometries:::rcpp_rleid( df, c(0,1))
#
# dt <- as.data.table( df )
#
# me <- geometries:::rcpp_rleid( df, c(0,1) )
# DT <- dt[, rleid(id1, id2) ]
#
# all.equal( me, DT )
#
# library(microbenchmark)
#
# microbenchmark(
#   me = { geometries:::rcpp_rleid( df, c(0,1) ) },
#   dt = { dt[, rleid(id1, id2) ] }
# )
#
#
#
#
