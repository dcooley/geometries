#ifndef R_GEOMETRIES_SHAPES_NEST_H
#define R_GEOMETRIES_SHAPES_NEST_H

#include <Rcpp.h>
#include "geometries/utils/utils.hpp"
#include "geometries/coordinates/dimensions.hpp"

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

    // Will only work on nested list objects
    if( !Rf_isNewList( x ) ) {
      Rcpp::stop("geometries - can only unnest list objects");
    }

    Rcpp::List lst = Rcpp::as< Rcpp::List >( x );

    // Rcpp::Rcout << "lst length: " << lst.length() << std::endl;
    //
    // if( lst.length() != 1 ) {
    //   Rcpp::stop("geometries - error trying to unnest the object");
    // }

    // TODO:
    // count the number of inner-elements
    // create a new object

    //SEXP res = lst[0];

    R_xlen_t n = lst.size();
    Rcpp::List inner_elements( n );
    R_xlen_t n_counter = 0; // will udpate each iteration
    R_xlen_t i, j;

    for( i = 0; i < n; ++i ) {
      Rcpp::List inner_list = lst[ i ];
      n_counter = n_counter + inner_list.size();
      inner_elements[ i ] = inner_list;
    }


    // unpack
    Rcpp::List res( n_counter );
    n_counter = 0;
    for( i = 0; i < n; ++i ) {
      Rcpp::List inner_list = inner_elements[ i ];
      for( j = 0; j < inner_list.size(); ++j ) {
        res[ n_counter ] = inner_list[ j ];
        ++n_counter;
      }
    }

    // depth will be a positive number
    // because it's the depth we need to get to, so can only be positive (or 0)
    while( depth > 1 ) {
      return unnest( res, depth - 1 );
      depth--;
    }
    return res;
  }

  inline SEXP nest_impl( SEXP x, int depth ) {
    // Need to know the depth of the current item, in order to know how deep to go
    Rcpp::List dimension = geometries::coordinates::geometry_dimensions( x );
    int current_depth = dimension["max_nest"];

    if( current_depth == depth ) {
      // already at the right depth
      return x;
    }

    if( current_depth > depth ) {
      // need to unnest
      int unnest_depth = current_depth - depth;
      return geometries::nest::unnest( x, unnest_depth );
    }

    int nest_depth = depth - current_depth;
    return geometries::nest::nest( x, nest_depth );
    // if current_depth > depth, need to unnest
    // if current_dept < depth, need to nest further
  }

}
} // geometries


#endif
