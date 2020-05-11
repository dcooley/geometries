
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
