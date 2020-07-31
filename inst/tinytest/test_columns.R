
df <- data.frame(x = 1:5, y = 1:5)
expect_error( geometries:::.test_column_positions(df, 1L), "geometries - expecting matrix when finding column positions")

m <- as.matrix( df )
expect_equal( geometries:::.test_column_positions( m, c("x","y") ), c(0L, 1L) )
expect_equal( geometries:::.test_column_positions( m, c("y", "x") ), c(1L, 0L) )
expect_error( geometries:::.test_column_positions( m, c("x","z") ), "geometries - could not find column" )
