
## Subsetting an Rcpp::List by a range?

# library(Rcpp)
#
# cppFunction(
#   code = '
#     Rcpp::List subset_list( Rcpp::List l ) {
#       Rcpp::Range rng(0,1);
#       return l[rng];
#     }
#   '
# )
#
# lst <- list(1,2,3)
# subset_list( lst )

# Nested RLEID: to tell me th elist element, and the level of nesting

# df <- data.frame(
#   id1 = c(1,1,1,2,2,2,3,3,3,4,4)
#   , id2 = c(1,1,2,1,1,1,1,1,2,1,1)
#   , id3 = c(1,1,1,1,2,2,1,2,3,1,1)
#   , x = 1
#   , y = 2
# )
# df
#
# geometries:::rcpp_nested_rleid( df, c(1), c(3,4))
# geometries:::rcpp_nested_rleid( df, c(0,1,2), c(3,4))
#
#
# ## iff we're on the last ID col, do the subsetting also
# ## iff we're on teh first ID col keep track of the number of unique elements
# ## which will be the res( n ) list size
# ##
# ## in each one, keep track of n_unique elements
#
#
# #
# #
# df <- data.frame(
#   id1 = c(1,1,1,2,2,2,2,3,3,4,4)
#   , id2 = c(1,1,2,1,1,2,2,1,1,1,1)
#   , x = 1:11
#   , y = 1:11
# )
# df
#
# geometries:::rcpp_nested_rleid( df, c(0,1) )


# #
# # geometries:::rcpp_nest2( df, c("id1","id2"), 2)
# # rl <- geometries:::rcpp_rleid( df, c(0,1) )
# #
# #
# # n <- 1e2
# # df <- data.frame(
# #   id1 = sample( 1:20, size = n, replace = T )
# #   , id2 = sample( 1:3, size = n, replace = T)
# # )
# #
# # library(data.table)
# # dt <- as.data.table( df )
# # setorder(dt, id1, id2)  ## nest2 requries ordered data
# #
# # nest <- geometries:::rcpp_nest2( dt, c("id1","id2"), 2)
# # rl <- geometries:::rcpp_rleid( dt, c(0,1) )
# #
# # microbenchmark::microbenchmark(
# #   nest = { geometries:::rcpp_nest2( dt, c("id1","id2"), 2) },
# #   rleid = { geometries:::rcpp_rleid( dt, c(0,1) ) }
# # )
# # ## These are pretty close
# # ## so does this suggest my while loop is actually not a bad way to go
# # ## and only my subsetting is slowing it down?
# #
# #
# # ## design changes??
# #
# # df <- data.frame(
# #   id1 = c(1,1,1,2,2,2,2,3)
# #   , id2 = c(1,1,1,1,1,2,2,1)
# #   , x = 1:8
# #   , y = 1:8
# # )
# #
# # # geometries:::id_positions( df$id1 )
# # # geometries:::id_positions( df$id2 )
# #
# #
# # # mat_ids <- as.matrix( df[, c("id1","id2")])
# # # geometries:::rcpp_rleid( mat_ids )
# #
# #
# # geometries:::rcpp_rleid( df, c(0,1) )
# #
# # library(data.table)
# #
# # n <- 1e3
# # df <- data.frame(
# #   id1 = sample( 1:20, size = n, replace = T )
# #   , id2 = sample( 1:3, size = n, replace = T)
# # )
# #
# #
# # me <- geometries:::rcpp_rleid( df, c(0,1))
# #
# # dt <- as.data.table( df )
# #
# # me <- geometries:::rcpp_rleid( df, c(0,1) )
# # DT <- dt[, rleid(id1, id2) ]
# #
# # all.equal( me, DT )
# #
# # library(microbenchmark)
# #
# # microbenchmark(
# #   me = { geometries:::rcpp_rleid( df, c(0,1) ) },
# #   dt = { dt[, rleid(id1, id2) ] }
# # )
# #
# #
# # ## Is there a difference between my nest2 which creates the correct list structure
# # ## and the RLEID code?
# #
# #
# #
# #

# library(wk)
#
# states_df <- ggplot2::map_data("state")
# states_df$region <- factor(states_df$region)
#
# microbenchmark::microbenchmark(
#   wk = {
#     wk <- coords_polygon_translate_wkb(
#       states_df$long,
#       states_df$lat,
#       feature_id = states_df$region,
#       ring_id = states_df$group
#     )
#   },
#
#   wk_sxp = {
#     wk_sxp <- coords_polygon_translate_wksxp(
#       states_df$long,
#       states_df$lat,
#       feature_id = states_df$region,
#       ring_id = states_df$group
#     )
#   },
#
#   geom = {
#     g <- geometries:::rcpp_nested_rleid(
#       states_df
#       , c( 4, 5 )
#     )
#   }
# )
