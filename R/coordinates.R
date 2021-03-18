# gm_dimensions
#
# Calculates the dimensions of geometries.
#
# @return
# A list containing
# \itemize{
#   \item{dimensions - a 5-column matrix where \itemize{
#     \item{column 1 - the start-index of the geometry}
#     \item{column 2 - the end-index of the geometry}
#     \item{column 3 - the dimension of the geometry}
#     \item{column 4 - the nesting level of the geometry}
#     \item{column 5 - the SEXP type of the geometry}
#     }
#   }
#   \item{max_dimension - the maximum dimension in all the geometries}
#   \item{max_nest - the maximum nesting level in all the geometries}
# }
#
# @examples
#
# ## A vector (representing an POINT)
# x <- 1:2
# gm_dimensions( x )
#
# ## A matrix (representing a LINE)
# m <- matrix(1:6, ncol = 2 )
# gm_dimensions( m )
#
# ## A list (representing a POLYGON)
# l <- list( m )
# gm_dimensions( l )
#
# ## A list of lists (representing a MULTIPOLYGON)
# l <- list( l )
# gm_dimensions( l )
#
# ## A list of matrices, points and lists (representing multiple, mixed geometries)
# l <- list( x, m, list( m ) )
# gm_dimensions( l )
#
# @param x object representing a geometry shape (e.g., list of matrices)
#
gm_dimensions <- function( x ) {
  rcpp_geometry_dimensions( x )
}

#' gm_coordinates
#'
#' Converts all coordinates from various geometric shapes into a single data.frame.
#'
#' @details
#'
#' The data.frame returned will always have an 'id' column. Then will follow an
#' 'id+counter' column for every level of nesting the geometry is within.
#'
#' The coordinates always start in column 'c1', the first column after all the id columns.
#' Then there is a column 'c+counter' for every coordinate in the geometry.
#'
#' This function is designed to handle multiple and different nested of geometry structures.
#'
#' @param x object representing geometry shapes (e.g., list of matrices)
#'
#' @return a single data.frame representing all the values in the input lists and matrices.
#'
#' @examples
#'
#' x <- 1:3
#' gm_coordinates( x )
#'
#' m <- matrix(1:12, ncol = 3)
#' gm_coordinates( m )
#'
#' l <- list(
#'   matrix(1:12, ncol = 2 )
#' )
#' gm_coordinates( l )
#'
#' l <- list(
#'   matrix(1:12, ncol = 4 )
#' )
#' gm_coordinates( l )
#'
#' l <- list(
#'   list(
#'     matrix(1:12, ncol = 2)
#'   )
#' )
#' gm_coordinates( l )
#'
#' l <- list(
#'   list(
#'     matrix(1:12, ncol = 2)
#'     , matrix(1:4, ncol = 2)
#'   )
#' )
#' gm_coordinates( l )
#'
#' l <- list(
#'   list(
#'     matrix(1:12, ncol = 2)
#'     , matrix(1:4, ncol = 2)
#'   )
#'   , 1:5
#'   , 1:2
#'   , matrix(1:9, ncol = 3)
#' )
#' gm_coordinates( l )
#'
#' l <- list(
#'   matrix(1:4, ncol = 2)
#'   , list(
#'     matrix(1:9, ncol = 3)
#'   )
#' )
#' gm_coordinates( l )
#'
#' l <- list(
#'   list(
#'     list(
#'       matrix(1:12, ncol = 2)
#'     )
#'   )
#'   , list(
#'     list(
#'      matrix(1:24, ncol = 2)
#'    )
#'   )
#' )
#' gm_coordinates( l )
#'
#' l <- list(
#'   list(
#'     list(
#'       matrix(1:12, ncol = 2)
#'     )
#'   )
#'   , list(
#'     list(
#'       matrix(1:3, ncol = 3)
#'      , matrix(1:24, ncol = 2)
#'    )
#'   )
#' )
#' gm_coordinates( l )
#'
#'
#' @export
gm_coordinates <- function( x ) {
  rcpp_coordinates( x )
}






