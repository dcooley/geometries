
#' make geometries
#'
#' Converts a data.frame into a collection of geometries.
#'
#' @param df data.frame
#' @param id_cols vector of id columns (iether integer or string)
#' @param geometry_cols vector of geometry columns (either integer or string)
#' @param class_attributes class attributes to assign to each geometry
#'
#' @examples
#'
#' df <- data.frame(
#'   id = c(1,1,1,1,1,2,2,2,2,2)
#'   , x = 1:10
#'   , y = 10:1
#' )
#'
#' gm_make_geometries(df, id_cols = c(1), geometry_cols = c(2,3))
#'
#' ## Adding a class attribute
#' gm_make_geometries(df, id_cols = c(1), geometry_cols = c(2,3), "my_line_object")
#'
#' ## Adding a second ID column
#' df$id1 <- c(1,1,1,2,2,1,1,2,2,3)
#' gm_make_geometries(df, id_cols = c(1,4), geometry_cols = c(2,3), "my_multiline_object")
#'
#' ## Using character column names
#' gm_make_geometries(df, id_cols = c("id","id1"), geometry_cols = c("x","y") )
#'
#' @export
gm_make_geometries <- function( df, id_cols, geometry_cols, class_attributes = NULL ) {
  id_cols <- index_correct( df, id_cols )
  geometry_cols <- index_correct( df, geometry_cols )
  return( rcpp_make_geometries( df, id_cols, geometry_cols, class_attributes ) )
}


## convert R-index to c++-index integer
index_correct <- function( df, cols ) {
  if( is.numeric( cols ) ) {
    return( cols - 1 )
  }
  if( is.character( cols ) ) {
    return( which(names(df) %in% cols ) - 1 )
  }
  return( cols )
}
