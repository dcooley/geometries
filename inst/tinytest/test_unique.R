
df <- data.frame(x = 1:5 )
expect_equal( geometries:::.test_unique_ids( df, NULL ), 1L )
expect_equal( geometries:::.test_unique_ids( df, "x" ), 1:5 )
expect_error( geometries:::.test_unique_ids( df, 1.3), "geometries - can't determine id column type" )
expect_error( geometries:::.test_unique_ids( df, -1L), "geometries - column index out of range")
expect_error( geometries:::.test_unique_ids( df, 3L), "geometries - column index out of range")

expect_error( geometries:::.test_unique_ids( list(), "x" ), "geometries - could not get id column")
