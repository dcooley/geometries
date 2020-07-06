

df <- data.frame(x = 1:5, y = 5:1 )
res <- geometries:::rcpp_calculate_bbox(df, c(0,1))
expect_equal( res, c( 1,1,5,5 ) )




expect_error(
  geometries:::rcpp_calculate_bbox( df, c(1))
  , "geometries - incorrect size of bounding box"
)

