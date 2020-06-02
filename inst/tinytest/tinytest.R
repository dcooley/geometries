
l <- geometries:::.tests()

expect_true( is.integer( l$make_box$INTSXP ) )
expect_true( !is.integer( l$make_box$REALSXP ) )
expect_true( is.numeric( l$make_box$REALSXP ) )
