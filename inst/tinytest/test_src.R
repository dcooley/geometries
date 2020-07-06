
l <- geometries:::.tests()

expect_true( is.integer( l$test_bbox$INTSXP ) )
expect_true( !is.integer( l$test_bbox$REALSXP ) )
expect_true( is.numeric( l$test_bbox$REALSXP ) )

# Rcpp::NumericVector x = {1,1,2,2,2,3};
# Rcpp::NumericVector y = {1,1,1,2,2,2};
# Rcpp::NumericVector z = {1,2,3,4,5,6};

expect_equal( l$test_rleid$x, c(1,1,2,2,2,3))
expect_equal( l$test_rleid$y, c(1,1,2,3,3,4))
expect_equal( l$test_rleid$z, c(1,2,3,4,5,6))



