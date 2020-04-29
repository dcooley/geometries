
<!-- README.md is generated from README.Rmd. Please edit that file -->

# geometries

<!-- badges: start -->

<!-- badges: end -->

Have you every wanted to generate geometric structures from data.frames,
but independant of any R classes, attributes or libraries?

No? Ok, this library isn’t for you.

But if you answered ‘yes’, this might be of interest.

``` r

library(Rcpp)

cppFunction(
  depends = "geometries"
  , includes = '#include "geometries/shapes/shapes.hpp"'
  , code = '
    SEXP polygon( SEXP df, SEXP geometry_cols, SEXP line_id ) {
      return geometries::shapes::get_listMat( df, geometry_cols, line_id );
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
```

### Utilities

``` r

library(Rcpp)

## calculate_bbox
## returns the xmin, ymin, xmax and ymax of various objects

cppFunction(
  depends = "geometries"
  , includes = '#include "geometries/bbox/bbox.hpp"'
  , code = '
    Rcpp::NumericVector calculate_bbox( SEXP x, SEXP geometry ) {
      Rcpp::NumericVector bbox(4);
      bbox(0) = bbox(1) = bbox(2) = bbox(3) = NA_REAL;
      geometries::bbox::calculate_bbox( bbox, x, geometry ) ;
      return bbox;
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
## gives the start and end indices 
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
