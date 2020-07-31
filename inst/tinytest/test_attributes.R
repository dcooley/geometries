
x <- 1:5
attr <- list(myClass = "myClassAttr")
geometries:::.test_attributes( x, attr )
expect_true( attr( x, "myClass" ) == "myClassAttr" )
