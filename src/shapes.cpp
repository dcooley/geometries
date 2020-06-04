#include <Rcpp.h>

#include "geometries/shapes/shapes.hpp"


#include "geometries/coordinates/dimensions.hpp"
#include "geometries/coordinates/coordinates.hpp"


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

// TODO:
// a 'coordinates()' function for lists, vectors, matrices etc.

/*
 * Returns the coordinates of a single geometry
 */
// [[Rcpp::export]]
Rcpp::List rcpp_geometry_coordinates(
  SEXP& geometry
) {
  R_xlen_t geometry_rows = 0;
  return geometries::coordinates::coordinates( geometry, geometry_rows );
}


// [[Rcpp::export]]
SEXP rcpp_coordinates(
    Rcpp::List& geometries
  ) {

  Rcpp::List dimensions = geometries::coordinates::geometry_dimensions( geometries );
  //return dimensions;

  // Rcpp::Rcout << "coordinates " << std::endl;

  // If I know max_nesting
  // and max dimeions
  // I then know the number of list elements

  Rcpp::IntegerMatrix dim = dimensions["dimensions"];
  R_xlen_t max_nest = dimensions["max_nest"];
  R_xlen_t max_dimension = dimensions["max_dimension"];

  R_xlen_t n_geometries = dim.nrow();
  R_xlen_t total_coordinates = dim( n_geometries - 1, 1 );
  total_coordinates = total_coordinates + 1;

  //R_xlen_t total_rows = 0;    // keeping track of total rows

  // set up result list
  R_xlen_t n_cols = max_nest + max_dimension + 1;  // +1 == the shape_id column
  Rcpp::List res( n_cols );
  R_xlen_t i, j;


  for( i = 0; i < n_cols; ++i ) {
    Rcpp::Vector< REALSXP > nv( total_coordinates, Rcpp::Vector< REALSXP >::get_na() );
    res[ i ] = nv;
  }

  // Rcpp::Rcout << "i loop " << std::endl;
  // Rcpp::NumericMatrix res( total_coordinates, max_nest + max_dimension );

  // iterate through each geometry
  // and fill the elements of the list
  R_xlen_t total_rows = 0;

  for( i = 0; i < n_geometries; ++i ) {
    // Rcpp::Rcout << "i: " << i << std::endl;

    R_xlen_t geometry_rows = 0; // reset for each geometry
    // based on the nes of the row, it will call one of the 'from_listMat()', 'from_listListMat()', etc?
    // or can I make this even more generic?
    //Rcpp::List geometry(1);
    SEXP geometry = geometries[ i ];
    // putting it into a list because...
    // it keeps / adds required nesting?
    //geometry[0] = geometries[i];
    Rcpp::IntegerVector dimension = dim( i, Rcpp::_ );

    // Rcpp::Rcout << "dimension: " << dimension << std::endl;


    // 0 = start index
    // 1 = end index
    // 2 = dimension
    // 3 = nest
    // 4 = RTYPE
    Rcpp::Rcout << dimension[0] << ", " << dimension[1] << ", " << dimension[2] << ", " << dimension[3] << ", " << dimension[4] << std::endl;
    // the 'nest' says which of the 'from_listMat()' tyep functions I Need to call.

    R_xlen_t start_row_idx = dimension[0];
    R_xlen_t end_row_idx = dimension[1];
    R_xlen_t dim = dimension[2];
    R_xlen_t nest = dimension[3];
    int rtype = dimension[4];
    R_xlen_t start_col_idx = max_nest - nest + 1;

    Rcpp::Rcout << "start_col_idx: " << start_col_idx << std::endl;
    Rcpp::Rcout << "max_nest: " << max_nest << std::endl;
    Rcpp::Rcout << "res_length: " << res.length() << std::endl;
    Rcpp::Rcout << "dim: " << dim << std::endl;

    // TODO
    // - can I put the coordinates directly into 'res',
    // - inside the 'coordinates()' routines?
    // - which means leave coordinates() as they are, as stand-alone modules
    // - but have a different set of void coodinates() functions, which take as input
    // - the output list, column idx, and they fill there and then.

    //Rcpp::List geom = geometries::coordinates::coordinates( geometry, geometry_rows );
    double id = 1;
    geometries::coordinates::coordinates(geometry, res, start_row_idx, start_col_idx, id );
    //total_rows += geometry_rows;
    //return geom;
    // Rcpp::Rcout << "total_rows: " << total_rows << std::endl;


    // R_xlen_t n_col = geom.length(); //dimension[2] + dimension[3];
    // R_xlen_t geometry_columns = dim + nest;
    // R_xlen_t vector_size = end_index - start_index + 1;
    //
    // // the nesting & dimension will tell us which column of 'res' this vector needs to go in
    // // col 0 == id
    // // col 1:(nest+1) = geometry ids
    // // col (nest+1+1) = coordinates
    // //R_xlen_t max_nest;  // start from the middle and fill-towards-left
    // R_xlen_t coord_start_index = max_nest + 1; // start from the middle and fill-towards-left

    // nest ids
    // only lists have nest values
    // Rcpp::Rcout << "nest columns " << std::endl;
    // for( j = 0; j < nest; ++j ) {
    //   // Rcpp::Rcout << "j: " << j << std::endl;
    //   // j is the 'nest col'
    //   Rcpp::Vector< REALSXP > new_vector = geom[ j ];
    //   R_xlen_t res_col = max_nest - ( max_nest - j ) + 1 ;
    //   //R_xlen_t res_col = 0;
    //   //R_xlen_t res_col = j;
    //
    //   // Rcpp::Rcout << "res_col: " << res_col << std::endl;
    //   // Rcpp::Rcout << "new_vector : " << new_vector << std::endl;
    //
    //   Rcpp::Vector< REALSXP > current_vector = res[ res_col ];
    //   // Rcpp::Rcout << "current_vector: " << current_vector << std::endl;
    //
    //   res[ res_col ] = geometries::utils::fill_vector( current_vector, new_vector, start_index );
    // }

    //coordinates
    // from 1 to <= dim, because inside ::coordinates(), I've shifted the coodinates one-column
    // to the right, to add on an extra id column
    // Rcpp::Vector< REALSXP > new_vector;
    // for( j = 0; j < dim; ++j ) {
    //
    //   // res( n_cols ) has already been defined with the right number of columns.
    //   // now all I need is to fill the vectors
    //   new_vector = geom[ j + nest ];
    //   // Rcpp::Rcout << "new_vector: " << new_vector << std::endl;
    //   R_xlen_t res_col = j + max_nest + 1;
    //   // Rcpp::Rcout << "res_col: " << res_col << std::endl;
    //   Rcpp::NumericVector current_vector = res[ res_col ];
    //   // Rcpp::Rcout << "current_vector: " << current_vector << std::endl;
    //   res[ res_col ] = geometries::utils::fill_vector( current_vector, new_vector, start_index );
    // }

    // shape id
    // double id = i;
    // Rcpp::Vector< REALSXP > current_id_vector = res[ 0 ];
    // Rcpp::NumericVector new_id_vector = Rcpp::rep( id, vector_size );
    //
    // res[ 0 ] = geometries::utils::fill_vector( current_id_vector, new_id_vector, start_index );
  } // ++i

  return res;


  //return dimensions;

}


// [[Rcpp::export]]
SEXP rcpp_from_listMat( Rcpp::List lst ) {
  R_xlen_t geometry_rows = 0;
  return geometries::shapes::from_listMat< REALSXP >( lst, geometry_rows );
}

