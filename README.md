
<!-- README.md is generated from README.Rmd. Please edit that file -->

# geometries

<!-- badges: start -->

<!-- badges: end -->

Have you every wanted to generate geometric structures from data.frames,
but independant of any R classes, attributes or libraries?

No? Ok, this library isn’t for you.

But if you answered ‘yes’, this might be of interest.

## Shapes

When one thinks of data structures of ‘shapes’ in R, the current
standard / typical structures are

  - **Point** - a vector of x, y values
  - **Line** - a matrix of x, y columns
  - **Polygon** - a list of matrices of x, y columns
  - **MultiPolygon** - a list of list of matrices of x, y columns

(in reality you can have more than just x & y columns)

But constructing these can sometimes be a bit fiddly.

So you can use the **shapes** API to build these structures from tabular
data (e.g. data.frames)

``` r

df <- data.frame(
  x = 1:10
  , y = 10:1
  , z = 21:30
  , m = 30:21
  , val = letters[1:10]
  , id = c( rep(1,5), rep(2,5) )
)

df
#     x  y  z  m val id
# 1   1 10 21 30   a  1
# 2   2  9 22 29   b  1
# 3   3  8 23 28   c  1
# 4   4  7 24 27   d  1
# 5   5  6 25 26   e  1
# 6   6  5 26 25   f  2
# 7   7  4 27 24   g  2
# 8   8  3 28 23   h  2
# 9   9  2 29 22   i  2
# 10 10  1 30 21   j  2

library(Rcpp)

cppFunction(
  depends = "geometries"
  , includes = '#include "geometries/shapes/shapes.hpp"'
  , code = '
    SEXP line( SEXP df, SEXP geometry_cols ) {
      return geometries::shapes::get_mat( df, geometry_cols );
    }
  '
)

line( df, c("x","y") )
#       [,1] [,2]
#  [1,]    1   10
#  [2,]    2    9
#  [3,]    3    8
#  [4,]    4    7
#  [5,]    5    6
#  [6,]    6    5
#  [7,]    7    4
#  [8,]    8    3
#  [9,]    9    2
# [10,]   10    1


cppFunction(
  depends = "geometries"
  , includes = '#include "geometries/shapes/shapes.hpp"'
  , code = '
    SEXP polygon( SEXP df, SEXP geometry_cols, SEXP line_id ) {
      return geometries::shapes::get_listMat( df, geometry_cols, line_id );
    }
  '
)

polygon( df, c("x","y"), c("id") )
# [[1]]
#      [,1] [,2]
# [1,]    1   10
# [2,]    2    9
# [3,]    3    8
# [4,]    4    7
# [5,]    5    6
# 
# [[2]]
#      [,1] [,2]
# [1,]    6    5
# [2,]    7    4
# [3,]    8    3
# [4,]    9    2
# [5,]   10    1

cppFunction(
  depends = "geometries"
  , includes = '#include "geometries/shapes/shapes.hpp"'
  , code = '
    SEXP multipolygon( SEXP df, SEXP geometry_cols, SEXP polygon_id, SEXP line_id ) {
      return geometries::shapes::get_listListMat( df, geometry_cols, polygon_id, line_id );
    }
  '
)

multipolygon( df, c("x","y"), c("id"),  c("id") )
# [[1]]
# [[1]][[1]]
#      [,1] [,2]
# [1,]    1   10
# [2,]    2    9
# [3,]    3    8
# [4,]    4    7
# [5,]    5    6
# 
# 
# [[2]]
# [[2]][[1]]
#      [,1] [,2]
# [1,]    6    5
# [2,]    7    4
# [3,]    8    3
# [4,]    9    2
# [5,]   10    1
```

## Collections

## Interleaving

## Utilities

``` r

library(Rcpp)

## calculate_bbox
## returns the xmin, ymin, xmax and ymax of various objects

cppFunction(
  depends = "geometries"
  , includes = '#include "geometries/bbox/bbox.hpp"'
  , code = '
    Rcpp::NumericVector calculate_bbox( SEXP x, SEXP geometry ) {
      return geometries::bbox::calculate_bbox( x, geometry );
    }
  '
)

## of a data.frame
df <- data.frame(
  x = 1:10
  , y = 21:30
  , z = 31:40
)

calculate_bbox(df, c("x","y"))
# [1]  1 21 10 30
calculate_bbox(df, c("x","z"))
# [1]  1 31 10 40
calculate_bbox(df, c("z","y"))
# [1] 31 21 40 30

## If using a list, 
l <- list(
  matrix(1:6, ncol = 2 )
  , matrix(6:1, ncol = 2)
)

calculate_bbox( l, NULL )
# [1] 1 1 6 6

l <- list(
  matrix(1:6, ncol = 3 )
  , matrix(6:1, ncol = 3)
)

calculate_bbox( l, c(0,1) )
# [1] 1 3 6 4
calculate_bbox( l, c(1,2) )
# [1] 3 1 4 6

## of an sf object
sf <- sfheaders::sf_linestring(
  obj = df
  , x = "x"
  , y = "y"
)

calculate_bbox(sf$geometry, NULL )
# [1]  1 21 10 30
```

``` r

## Count Coordinates
##
## either counts the number of coordinates in a given geometry,
library(Rcpp)

cppFunction(
  depends = 'geometries'
  , includes = '#include "geometries/geometries/coordinates.hpp"'
  , code = '
    R_xlen_t count_coordinates( SEXP x ) {
      R_xlen_t count = 0;
      geometries::coordinates::count_coordinates( x, count );
      return count;
    }
  '
)

df <- data.frame(
  x = 1:10
  , y = 10:1
  , z = 21:30
  , m = 30:21
  , val = letters[1:10]
  , id = c( rep(1,5), rep(2,5) )
)

poly <- polygon( df, c("x","y"), c("id") )

count_coordinates( poly )
# [1] 10
```

``` r

## Coordinate indices
## 
## gives the start and end indices of geometries
cppFunction(
  depends = 'geometries'
  , includes = '#include "geometries/geometries/coordinates.hpp"'
  , code = '
    Rcpp::IntegerMatrix coordinate_indices( Rcpp::List x ) {
      return geometries::coordinates::coordinate_indices( x );
    }
  '
)

l <- list(
  matrix(1:20, ncol = 2 )
  , matrix(1:6, ncol = 2)
  , matrix(1:10, ncol = 2)
)

coordinate_indices( l )
#      [,1] [,2]
# [1,]    0    9
# [2,]   10   12
# [3,]   13   17
```

``` r

## id positions
## 
## takes a sorted vector and returns the start & end indices of each unique element
cppFunction(
  depends = 'geometries'
  , includes = '#include "geometries/utils/lines/lines.hpp"'
  , code = '
    Rcpp::IntegerMatrix id_positions( SEXP x ) {
      return geometries::utils::id_positions( x );
    }
  '
)

x <- c( rep(1, 5), rep(2, 10), rep(3, 6), rep(4, 2) )
id_positions( x )
#      [,1] [,2]
# [1,]    0    4
# [2,]    5   14
# [3,]   15   20
# [4,]   21   22
```
