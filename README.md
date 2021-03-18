
<!-- README.md is generated from README.Rmd. Please edit that file -->

# geometries

[![R build
status](https://github.com/dcooley/geometries/workflows/R-CMD-check/badge.svg)](https://github.com/dcooley/geometries/actions)
[![Codecov test
coverage](https://codecov.io/gh/dcooley/geometries/branch/master/graph/badge.svg)](https://codecov.io/gh/dcooley/geometries?branch=master)

Have you ever wanted to generate geometric structures from data.frames,
but independent of any R classes, attributes or libraries?

No? Ok, this library isn’t for you.

But if you answered ‘yes’, this might be of interest.

## What is the point?

When one thinks of ‘shape’ objects in R, the current standard / typical
structures are

  - **Point** - a vector of x, y values
  - **Line** - a matrix of x, y columns
  - **Polygon** - a list of matrices of x, y columns
  - **MultiPolygon** - a list of list of matrices of x, y columns

(in reality you can have more than just x & y columns)

But constructing these can sometimes be a bit fiddly.

So my **goal** of this package is to take away the pain of building
**shapes**. I want to accept **any** base R data object and convert it
into the required **shape**

## Some Examples

Take a `data.frame`

``` r
df <- data.frame(
  id = c(1,1,1,1,1,2,2,2,2,2)
  , x = 1:10
  , y = 10:1
)
df
#    id  x  y
# 1   1  1 10
# 2   1  2  9
# 3   1  3  8
# 4   1  4  7
# 5   1  5  6
# 6   2  6  5
# 7   2  7  4
# 8   2  8  3
# 9   2  9  2
# 10  2 10  1
```

You can make two “LINE”\* objects by splitting this into a list of
matrices

``` r
gm_geometries(
  obj = df
  , geometry_cols = c("x","y")
  , id_cols = c("id")
)
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

\*I’ve put “LINE” in quotes because this doesn’t *have* to be called a
LINE, it’s just that a LINE is typically represented by a matrix in R.

And if you send it a `class_attribute`, you can make it into whatever
type of object you want

``` r
gm_geometries(
  obj = df
  , geometry_cols = c("x","y")
  , id_cols = c("id")
  , class_attributes = list(class = "my_new_shape", other = "really_awesome_shape")
)
# [[1]]
#      [,1] [,2]
# [1,]    1   10
# [2,]    2    9
# [3,]    3    8
# [4,]    4    7
# [5,]    5    6
# attr(,"class")
# [1] "my_new_shape"
# attr(,"other")
# [1] "really_awesome_shape"
# 
# [[2]]
#      [,1] [,2]
# [1,]    6    5
# [2,]    7    4
# [3,]    8    3
# [4,]    9    2
# [5,]   10    1
# attr(,"class")
# [1] "my_new_shape"
# attr(,"other")
# [1] "really_awesome_shape"
```

And I’m building it as an **interface** package. That is, it’s all being
written in C++ header files, so you can link to these header files from
your own package.

## What do you mean, ‘link to’?

When you build a package, if you want to use C++ code from **another
package**, you have to let the compiler know. In an R package, you do
this by specifying a `LinkingTo` value in the DESCRIPTION.

Take for example, the
[LinkingTo](https://github.com/dcooley/geometries/blob/master/DESCRIPTION#L17)
section in the DESCRIPTION field of this package

``` yaml
SystemRequirements: C++11
LinkingTo: 
    Rcpp
Imports:
    Rcpp
```

This tells the compiler I want to link to Rcpp’s. Which means I can use
all the [Rcpp
code](https://github.com/RcppCore/Rcpp/tree/master/inst/include/Rcpp) by
including whichever header file I want.
