
m <- matrix(c(1,1,2,2,3,3), ncol = 2, byrow = T)
l <- list(m)
res <- geometries:::rcpp_close_matrix(l)
expect_equal( res[[1]], rbind(m, c(1,1) ) )

## Too few rows
m <- matrix(c(1,1,2,2), ncol = 2, byrow = T)
l <- list(m)
expect_error( geometries:::rcpp_close_matrix(l), "geometries - closed shapes must have at least 4 rows" )

## already closed
m <- matrix(c(1,1,2,2,3,3,1,1), ncol = 2, byrow = T)
l <- list(m)
res <- geometries:::rcpp_close_matrix(l)
expect_equal( res[[1]], m )
