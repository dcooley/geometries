
expect_equal( geometries:::rcpp_calculate_bbox( 1L:4L, NULL ), c(1L,2L,1L,2L) )
expect_equal( geometries:::rcpp_calculate_bbox( 1L:4L, c(2L,3L) ), c(3L,4L,3L,4L) )

expect_equal( geometries:::rcpp_calculate_bbox( c(1,2,3,4.4), NULL ), c(1,2,1,2) )
expect_equal( geometries:::rcpp_calculate_bbox( c(1,2,3,4.4), c(2L,3L) ), c(3,4.4,3,4.4) )

m <- matrix(1L:4L, ncol = 2, byrow = T)
expect_equal( geometries:::rcpp_calculate_bbox( m, NULL ), c(1L:4L) )

m <- matrix(1:4, ncol = 2, byrow = T)
expect_true( !is.integer( geometries:::rcpp_calculate_bbox( m, NULL ) ) )
expect_equal( geometries:::rcpp_calculate_bbox( m, NULL ), c(1:4) )

m <- matrix(c(1,2,3,4.1), ncol = 2, byrow = T)
expect_true( !is.integer( geometries:::rcpp_calculate_bbox( m, NULL ) ) )
expect_equal( geometries:::rcpp_calculate_bbox( m, NULL ), c(1,2,3,4.1) )

df <- data.frame(x = 1:5, y = 5:1 )
res <- geometries:::rcpp_calculate_bbox(df, NULL )
expect_equal( res, c( 1,1,5,5 ) )

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

l <- list()
expect_equal( geometries:::rcpp_calculate_bbox( l, NULL ), c(NA_real_,NA,NA,NA) )

x <- c(T,F,T,F)
expect_error( geometries:::rcpp_calculate_bbox( x, NULL ), "geometries - can't calculate bounding box for this type")
expect_error( geometries:::rcpp_calculate_bbox( x, c(0L,1L) ), "geometries - can't calculate bounding box for this type")

expect_error(
  geometries:::rcpp_calculate_bbox( df, c(1))
  , "geometries - incorrect size of bounding box"
)

