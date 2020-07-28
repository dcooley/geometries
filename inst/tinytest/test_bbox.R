
expect_equal( geometries:::rcpp_calculate_bbox( 1L:4L, NULL ), c(1L,2L,1L,2L) )
expect_equal( geometries:::rcpp_calculate_bbox( 1L:4L, c(2L,3L) ), c(3L,4L,3L,4L) )

m <- matrix(1L:4L, ncol = 2, byrow = T)
expect_equal( geometries:::rcpp_calculate_bbox( m, NULL ), c(1L:4L) )

m <- matrix(1:4, ncol = 2, byrow = T)
expect_true( !is.integer( geometries:::rcpp_calculate_bbox( m, NULL ) ) )
expect_equal( geometries:::rcpp_calculate_bbox( m, NULL ), c(1:4) )

df <- data.frame(x = 1:5, y = 5:1 )
res <- geometries:::rcpp_calculate_bbox(df, c(0,1))
expect_equal( res, c( 1,1,5,5 ) )

res <- geometries:::rcpp_calculate_bbox(df, c("x","y"))
expect_equal( res, c( 1,1,5,5 ) )

res <- geometries:::rcpp_calculate_bbox(df, c("y", "x"))
expect_equal( res, c( 1,1,5,5 ) )

m <- as.matrix( df )
res <- geometries:::rcpp_calculate_bbox(m, c("y", "x"))
expect_equal( res, c( 1,1,5,5 ) )


expect_error(
  geometries:::rcpp_calculate_bbox( df, c(1))
  , "geometries - incorrect size of bounding box"
)

