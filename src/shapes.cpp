#include <Rcpp.h>

#include "geometries/shapes/shapes.hpp"

#include "geometries/coordinates/dimensions.hpp"


// POINTS -----------
// [[Rcpp::export]]
SEXP rcpp_get_vec(
    SEXP x,
    SEXP cols
) {
  return geometries::shapes::to_vec( x, cols );
}

// LINE ----------
// [[Rcpp::export]]
SEXP rcpp_to_mat(
    SEXP x,
    SEXP cols
) {
  return geometries::shapes::to_mat( x, cols );
}

// LINES -----------
// [[Rcpp::export]]
SEXP rcpp_get_list_mat(
    SEXP x,
    SEXP cols,
    SEXP id
) {
  return geometries::shapes::to_listMat( x, cols, id );
}


// converting objects to a single matrix/list/data.frame
// iterate and get all dimensions.
//

// [[Rcpp::export]]
SEXP rcpp_coordinates(
    Rcpp::List& geometries
  ) {

  Rcpp::List dimensions = geometries::coordinates::geometry_dimensions( geometries );

  // If I know max_nesting
  // and max dimeions
  // I then know the number of list elements

  Rcpp::IntegerMatrix dim = dimensions["dimensions"];
  R_xlen_t max_nest = dimensions["max_nest"];
  R_xlen_t max_dimension = dimensions["max_dimension"];

  R_xlen_t n_geometries = dim.nrow();
  R_xlen_t total_coordinates = dim( n_geometries - 1, 1 );
  total_coordinates = total_coordinates + 1;

  R_xlen_t geometry_rows = 0; // reset for each geometry
  R_xlen_t total_rows = 0;    // keeping track of total rows

  // set up result list
  R_xlen_t n_cols = max_nest + max_dimension;
  Rcpp::List res( n_cols );
  R_xlen_t i, j;
  for( i = 0; i < n_cols; ++i ) {
    Rcpp::NumericVector nv( total_coordinates, Rcpp::NumericVector::get_na() );
    res[ i ] = nv;
  }
  // Rcpp::NumericMatrix res( total_coordinates, max_nest + max_dimension );

  // iterate through each geometry
  // and fill the elements of the list
  for( i = 0; i < n_geometries; ++i ) {
    // based on the nes of the row, it will call one of the 'from_listMat()', 'from_listListMat()', etc?
    // or can I make this even more generic?
    SEXP geometry = geometries[ i ];
    Rcpp::IntegerVector dimension = dim( i, Rcpp::_ );
    // 0 = start index
    // 1 = end index
    // 2 = dimension
    // 3 = nest
    // 4 = RTYPE
    //Rcpp::Rcout << dimension[0] << ", " << dimension[1] << ", " << dimension[2] << ", " << dimension[3] << ", " << dimension[4] << std::endl;
    // the 'nest' says which of the 'from_listMat()' tyep functions I Need to call.

    R_xlen_t nest = dimension[3];
    int rtype = dimension[4];

    Rcpp::List geom;
    if( nest == 1 ) {
      Rcpp::List l = Rcpp::as< Rcpp::List >( geometry );  // we know, because it's a nested object
      geom = geometries::shapes::from_listMat< REALSXP >( l, geometry_rows );
    } else if ( nest == 2 ) {
      // geom = geometries::shapes::from_listListMat() :
    }

    R_xlen_t n_col = dimension[3];
    for( j = 0; j < n_col; ++j ) {
      // res( n_cols ) has already been defined with the right number of columns.
      // now all I need is to
      Rcpp::Vector< REALSXP > v = geom[ j ];
      Rcpp::Rcout << v << std::endl;

    }

    total_rows += geometry_rows;

  }

  return res;


  //return dimensions;

}


// [[Rcpp::export]]
SEXP rcpp_from_listMat( Rcpp::List lst ) {
  R_xlen_t geometry_rows = 0;
  return geometries::shapes::from_listMat< REALSXP >( lst, geometry_rows );
}

