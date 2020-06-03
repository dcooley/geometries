
## Dimensions

x <- 1L:3L
res <- geometries::gm_dimensions( x )

expect_true( ncol(res$dimensions) == 5)
expect_true( all(names(res) == c("dimensions", "max_dimension","max_nest")))

dims <- res$dimensions
expect_true( dims[1,1] == 0 ) ## always starts at index 0
expect_true( dims[1,2] == 0 ) ## vector only has 1 row
expect_true( dims[1,3] == 3 ) ## dimension (3 values in a coordinate)
expect_true( dims[1,4] == 0 ) ## nest - a vector is not nested in a list
expect_true( dims[1,5] == 13 ) ## integer

l <- list( x )
res <- geometries::gm_dimensions( l )

dims <- res$dimensions
expect_true( dims[1,1] == 0 ) ## always starts at index 0
expect_true( dims[1,2] == 0 ) ## vector only has 1 row
expect_true( dims[1,3] == 3 ) ## dimension (3 values in a coordinate)
expect_true( dims[1,4] == 1 ) ## nest - inside a list
expect_true( dims[1,5] == 13 ) ## integer

m <- matrix(1:6, ncol = 2)
res <- geometries::gm_dimensions( m )

dims <- res$dimensions
expect_true( dims[1,1] == 0 ) ## always starts at index 0
expect_true( dims[1,2] == 2 )
expect_true( dims[1,3] == 2 ) ## dimension (3 values in a coordinate)
expect_true( dims[1,4] == 0 ) ## nest - inside a list
expect_true( dims[1,5] == 13 ) ## integer


l <- list(
  1:3 ## point XYZ
  , matrix(1:6, ncol = 2) #line XY
  , list(
    matrix(1:6, ncol = 3) ## polygon XYZM
  )
  , matrix(1:8, ncol = 4) ## line XYZM
)

res <- geometries::gm_dimensions( l )
dims <- res$dimensions
expect_true( all(dims[, 3] == c(3,2,3,4)))
expect_true( all(dims[, 4] == c(1,1,2,1)))


# res <- geometries::gm_dimensions( mapdeck::roads$geometry )

