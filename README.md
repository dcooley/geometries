
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

## other_columns
## - find the columns not specified by any combination of
## - col
## - col1, col2
## - col1, col2, col3
## for data.frames, matrices and numeric and string column values
library(Rcpp)

cppFunction(
  depends = "geometries"
  , includes = '#include "geometries/utils/columns/columns.hpp"'
  , code = '
    SEXP other_columns( SEXP x, SEXP col1, SEXP col2 ) {
      return geometries::utils::other_columns( x, col1, col2 );
    }
  '
)

df <- data.frame(
  x = 1:5
  , y = 1:5
  , z = 1:5
  , m = 1:5
  , id = 1:5
  , val = letters[1:5]
)

other_columns( df, "x", "y" )
# [1] "z"   "m"   "id"  "val"

other_columns( df, "x", c("z","m") )
# [1] "y"   "id"  "val"

other_columns( df, 0, 1 )
# [1] 2 3 4 5

other_columns( df, 0, c(1,2,3) )
# [1] 4 5

m <- as.matrix( df[, c("x","y","z","m","id")] ) ## droped the char to make matrix numeric
other_columns( m, c(2,3), 4 ) 
# [1] 0 1
```
