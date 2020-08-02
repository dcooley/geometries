
<!-- README.md is generated from README.Rmd. Please edit that file -->

# geometries

[![R build
status](https://github.com/dcooley/geometries/workflows/R-CMD-check/badge.svg)](https://github.com/dcooley/geometries/actions)
[![Codecov test
coverage](https://codecov.io/gh/dcooley/geometries/branch/master/graph/badge.svg)](https://codecov.io/gh/dcooley/geometries?branch=master)

Have you every wanted to generate geometric structures from data.frames,
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

## What sort of things can I do with this package?
