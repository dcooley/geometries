

df <- data.frame(
  x = 1:5
  , y = 1:5
  , z = 1:5
)
m <- as.matrix( df )
ldf <- as.list( df )

expect_equal( geometries:::.test_to_geometry_matrix( df, NULL ), unname( m ) )
expect_equal( geometries:::.test_to_geometry_matrix( df, c(0L,1L,2L) ), unname( m ) )
expect_equal( geometries:::.test_to_geometry_matrix( df, c(1L,2L) ), unname( m[, 2:3] ) )
expect_equal( geometries:::.test_to_geometry_matrix( df, c("x","y","z") ), unname( m ) )
expect_equal( geometries:::.test_to_geometry_matrix( df, c("z","x") ), unname( m[, c(3,1)] ) )

expect_equal( geometries:::.test_to_geometry_matrix( m, NULL ), m )  ## a named matrix keeps its names
expect_equal( geometries:::.test_to_geometry_matrix( m, c(0L,1L,2L) ), unname( m ) )
expect_equal( geometries:::.test_to_geometry_matrix( m, c(1L,2L) ), unname( m[, 2:3] ) )
expect_equal( geometries:::.test_to_geometry_matrix( m, c("x","y","z") ), unname( m ) )
expect_equal( geometries:::.test_to_geometry_matrix( m, c("z","x") ), unname( m[, c(3,1)] ) )


expect_equal( geometries:::.test_to_geometry_matrix( ldf, NULL ), unname( m ) )
expect_equal( geometries:::.test_to_geometry_matrix( ldf, c(0L,1L,2L) ), unname( m ) )
expect_equal( geometries:::.test_to_geometry_matrix( ldf, c(1L,2L) ), unname( m[, 2:3] ) )
expect_equal( geometries:::.test_to_geometry_matrix( ldf, c("x","y","z") ), unname( m ) )
expect_equal( geometries:::.test_to_geometry_matrix( ldf, c("z","x") ), unname( m[, c(3,1)] ) )
