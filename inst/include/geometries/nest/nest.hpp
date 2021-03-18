#ifndef R_GEOMETRIES_SHAPES_NEST_H
#define R_GEOMETRIES_SHAPES_NEST_H

#include <Rcpp.h>
#include "geometries/utils/utils.hpp"

namespace geometries {
namespace nest {

  inline SEXP nest( SEXP x, int depth ) {
    if( depth < 1 ) {
      return x;
    }

    Rcpp::List res(1);
    res[0] = x;   // first level

    while( depth > 0 ) {
      return nest( res, depth - 1 );
      depth--;
    }
    return res;
  }

  inline SEXP unnest( SEXP x, int depth ) {
    // inside this function the dimension of x should already be known
    // And it will only work on nested list objects
    if( !Rf_isNewList( x ) ) {
      Rcpp::stop("geometries - can only unnest list objects");
    }

    Rcpp::List lst = Rcpp::as< Rcpp::List >( x );
    if( lst.length() != 1 ) {
      Rcpp::stop("geometries - error trying to unnest the object");
    }
    SEXP res = lst[0];

    // depth will be a positive number
    // because it's the depth we need to get to, so can only be positive (or 0)
    while( depth > 1 ) {
      return unnest( res, depth - 1 );
      depth--;
    }
    return res;
  }


}
} // geometries


#endif
