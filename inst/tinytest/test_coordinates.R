
## Dimensions

x <- 1L:3L
res <- geometries:::gm_dimensions( x )

expect_true( ncol(res$dimensions) == 5)
expect_true( all(names(res) == c("dimensions", "max_dimension","max_nest")))

dims <- res$dimensions
expect_true( dims[1,1] == 0 ) ## always starts at index 0
expect_true( dims[1,2] == 0 ) ## vector only has 1 row
expect_true( dims[1,3] == 3 ) ## dimension (3 values in a coordinate)
expect_true( dims[1,4] == 0 ) ## nest - a vector is not nested in a list
expect_true( dims[1,5] == 13 ) ## integer

l <- list( x )
res <- geometries:::gm_dimensions( l )

dims <- res$dimensions
expect_true( dims[1,1] == 0 ) ## always starts at index 0
expect_true( dims[1,2] == 0 ) ## vector only has 1 row
expect_true( dims[1,3] == 3 ) ## dimension (3 values in a coordinate)
expect_true( dims[1,4] == 1 ) ## nest - inside a list
expect_true( dims[1,5] == 13 ) ## integer

m <- matrix(1:6, ncol = 2)
res <- geometries:::gm_dimensions( m )

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

res <- geometries:::gm_dimensions( l )
dims <- res$dimensions
expect_true( all(dims[, 3] == c(3,2,3,4)))
expect_true( all(dims[, 4] == c(1,1,2,1)))


x <- 1:3
res <- gm_coordinates( x )
expect_true( ncol(res) == 4 )

m <- matrix(1:12, ncol = 3)
res <- gm_coordinates( m )
expect_true( ncol(res) == 4 )

l <- list(
  matrix(1:12, ncol = 2 )
)
res <- gm_coordinates( l )
expect_true( ncol( res ) == 4 )  ## nested in a list gets an id?

l <- list(
  matrix(1:12, ncol = 4 )
)
res <- gm_coordinates( l )
expect_true( ncol( res ) == 6 )

l <- list(
  list(
    matrix(1:12, ncol = 2)
  )
)
res <- gm_coordinates( l )
expect_true( ncol( res ) == 5 )

l <- list(
  list(
    matrix(1:12, ncol = 2)
    , matrix(1:4, ncol = 2)
  )
)
res <- gm_coordinates( l )
expect_true( ncol( res ) == 5 )
expect_true( unique( res$id ) == 1 )  ## first vector is id of the geometry
expect_equal( unique( res$id1 ), c(1,2) )  ## second vector is id of shape within the geometry

## nesting depth
l <- list(
  list(
    list(
      list(
        list(
          matrix(1:6, ncol = 2)
        )
      )
    )
  )
)
res <- gm_coordinates( l )
expect_equal( ncol( res ), 8 )

# ## and nesting works on dimenions
# res <- gm_dimensions( l )
# expect_equal( res$dimensions[, 3], 2 )
# expect_equal( res$dimensions[, 4], 5 )

l <- list(
  matrix(1:4, ncol = 2)
  , list(
    matrix(1:9, ncol = 3)
  )
)
res <- gm_coordinates( l )
expect_true( ncol( res ) == 6 )

expect_equal(
  l[[1]]
  , unname( as.matrix( res[1:2, c("c1","c2") ] ) )
)

expect_equal(
  l[[2]][[1]]
  , unname( as.matrix( res[3:5, c("c1","c2", "c3") ] ) )
)

## ID index starts at 1
expect_true( all( res[1:2, 1] == c(1,1) ) )

### coordinates.hpp

m <- matrix(1:4, ncol = 2)
df <- data.frame(
  x = 1:4
)







