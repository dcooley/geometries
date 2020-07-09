
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

expect_equal( l$test_matrix$nm1, matrix(c(1:4, 1:4), ncol = 2) )
expect_equal( l$test_matrix$nm2, matrix(c(1:4), ncol = 1) )
expect_equal( l$test_matrix$nm3, matrix(c(1:4), ncol = 1) )
m <- matrix(c(1:4), ncol = 1)
colnames( m ) <- "x"
expect_equal( l$test_matrix$nm4, m)

expect_equal( l$test_matrix$nm5, l$test_matrix$nm1 )
expect_equal( l$test_matrix$nm6, l$test_matrix$nm2 )
expect_equal( l$test_matrix$nm7, l$test_matrix$nm3 )
expect_equal( l$test_matrix$nm8, l$test_matrix$nm4 )

expect_equal( l$test_matrix$nm9, l$test_matrix$nm2 )


### SEXP col_int
expect_true( l$test_colint$x_col == 0 )
expect_true( l$test_colint$y_col == 1 )
