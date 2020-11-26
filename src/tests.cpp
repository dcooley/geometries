#include <Rcpp.h>

#include "geometries/utils/attributes/attributes.hpp"
#include "geometries/bbox/bbox.hpp"
#include "geometries/matrix/to_mat.hpp"
#include "geometries/utils/sexp/sexp.hpp"
#include "geometries/utils/columns/columns.hpp"
#include "geometries/utils/rleid/rleid.hpp"
#include "geometries/utils/lists/as_list.hpp"
#include "geometries/utils/lists/fill.hpp"
#include "geometries/utils/dataframe/dataframe.hpp"
#include "geometries/utils/unique/unique_ids.hpp"
#include "geometries/utils/split/split.hpp"
#include "geometries/coordinates/coordinates_impl.hpp"


// ----------------------------
// attributes.hpp
// [[Rcpp::export(.test_attributes)]]
void test_attributes( SEXP& obj, Rcpp::List& attributes ) {
  geometries::utils::attach_attributes( obj, attributes );
}

// ----------------------------
// bbox.hpp

/*
 * testing Numeric and Integer bboxes are created
 */
SEXP test_bbox() {

  Rcpp::NumericVector nv(4);  // xmin, ymin, xmax, ymax
  nv(0) = nv(1) = nv(2) = nv(3) = 0;

  Rcpp::NumericVector nx = {1,2,3,4};
  Rcpp::NumericVector ny = {1,2,3,4};
  geometries::bbox::make_bbox( nv, nx, ny );

  Rcpp::IntegerVector iv(4);  // xmin, ymin, xmax, ymax
  iv(0) = iv(1) = iv(2) = iv(3) = 0;

  Rcpp::IntegerVector ix = {1,2,3,4};
  Rcpp::IntegerVector iy = {1,2,3,4};
  geometries::bbox::make_bbox( iv, ix, iy );

  return Rcpp::List::create(
    Rcpp::_["REALSXP"] = nv,
    Rcpp::_["INTSXP"] = iv
  );

}

// ----------------------------
// coordinates.hpp

// geometries::coordinates::coordinates_impl() also tested as part of gm_coordinates()

// //[[Rcpp::export(.test_coordinates)]]
// SEXP test_coordinates(
//     SEXP geometries
//   ) {
//   Rcpp::List res;
//   geometries::coordinates::coordinates( geometries );
//
// }

// ----------------------------
// matrix.hpp

// test various objects make matrix
// [[Rcpp::export(.test_to_geometry_matrix_cols)]]
SEXP test_to_geometry_matrix_cols( SEXP x, SEXP cols ) {
  return geometries::matrix::to_geometry_matrix( x, cols );
}

// [[Rcpp::export(.test_to_geometry_matrix_cols_names)]]
SEXP test_to_geometry_matrix_cols_names( Rcpp::DataFrame x, Rcpp::IntegerVector cols, bool keep_names ) {
  return geometries::matrix::to_geometry_matrix( x, cols, keep_names );
}

// [[Rcpp::export(.test_to_geometry_matrix_single)]]
SEXP test_to_geometry_matrix_single( SEXP x ) {
  SEXP x2 = Rcpp::clone( x );
  return geometries::matrix::to_geometry_matrix( x2 );
}

SEXP test_matrix() {

  Rcpp::NumericVector x = {1,2,3,4};
  Rcpp::NumericVector y = {1,2,3,4};

  Rcpp::NumericMatrix nmxy( 4, 2 );
  nmxy( Rcpp::_, 0 ) = x;
  nmxy( Rcpp::_, 1 ) = y;

  Rcpp::List lst = Rcpp::List::create(
    Rcpp::_["x"] = x,
    Rcpp::_["y"] = y
  );

  Rcpp::StringVector scols = {"x"};
  Rcpp::IntegerVector icols = {0};

  Rcpp::NumericMatrix nm1 = geometries::matrix::to_geometry_matrix( lst );
  Rcpp::NumericMatrix nm2 = geometries::matrix::to_geometry_matrix( lst, scols );
  Rcpp::NumericMatrix nm3 = geometries::matrix::to_geometry_matrix( lst, icols );

  Rcpp::NumericMatrix nm4 = geometries::matrix::to_geometry_matrix( lst, scols, true );
  //Rcpp::NumericMatrix nm5 = geometries::matrix::to_geometry_matrix( lst, icols, true );  // integer subset doen't keep names

  Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( lst );

  Rcpp::NumericMatrix nm5 = geometries::matrix::to_geometry_matrix( df );
  Rcpp::NumericMatrix nm6 = geometries::matrix::to_geometry_matrix( df, scols );
  Rcpp::NumericMatrix nm7 = geometries::matrix::to_geometry_matrix( df, icols );

  Rcpp::NumericMatrix nm8 = geometries::matrix::to_geometry_matrix( df, scols, true );

  Rcpp::NumericMatrix nm9 = geometries::matrix::to_geometry_matrix( nmxy, icols );

  Rcpp::NumericMatrix nm10 = geometries::matrix::to_geometry_matrix( df, true );
  Rcpp::NumericVector nm11 = geometries::matrix::to_geometry_matrix( x );
  Rcpp::NumericMatrix nm12 = geometries::matrix::to_geometry_matrix( lst, true );
  Rcpp::NumericVector nm13 = geometries::matrix::to_geometry_matrix( x, icols );

  return Rcpp::List::create(
    Rcpp::_["nm1"] = nm1,
    Rcpp::_["nm2"] = nm2,
    Rcpp::_["nm3"] = nm3,
    Rcpp::_["nm4"] = nm4,
    Rcpp::_["nm5"] = nm5,
    Rcpp::_["nm6"] = nm6,
    Rcpp::_["nm7"] = nm7,
    Rcpp::_["nm8"] = nm8,
    Rcpp::_["nm9"] = nm9,
    Rcpp::_["nm10"] = nm10,
    Rcpp::_["nm11"] = nm11,
    Rcpp::_["nm12"] = nm12,
    Rcpp::_["nm13"] = nm13
  );

}

//[[Rcpp::export]]
SEXP tm( SEXP x ) {
  return geometries::matrix::to_geometry_matrix( x );
}


// ----------------------------
// sexp.hpp
// [[Rcpp::export(.test_sexp_col_int)]]
Rcpp::IntegerVector test_sexp_col_int( SEXP x, SEXP v ) {
  return geometries::utils::sexp_col_int( x, v );
}

// [[Rcpp::export(.test_sexp_col_names)]]
Rcpp::StringVector test_sexp_col_names( SEXP x ) {
  return geometries::utils::sexp_col_names( x );
}

// [[Rcpp::export(.test_sexp_n_col)]]
R_xlen_t test_sexp_n_col( SEXP x ) {
  return geometries::utils::sexp_n_col( x );
}

// [[Rcpp::export(.test_sexp_n_row)]]
R_xlen_t test_sexp_n_row( SEXP x ) {
  return geometries::utils::sexp_n_row( x );
}

// [[Rcpp::export(.test_sexp_length)]]
R_xlen_t test_sexp_length( SEXP x ) {
  return geometries::utils::sexp_length( x );
}


Rcpp::List test_sexp() {

  Rcpp::NumericVector x = {1,2,3,4};
  Rcpp::NumericVector y = {1,2,3,4};

  Rcpp::List lst = Rcpp::List::create(
    Rcpp::_["x"] = x,
    Rcpp::_["y"] = y
  );

  // col_int
  Rcpp::StringVector x_col = {"x"};
  Rcpp::StringVector y_col = {"y"};
  Rcpp::StringVector lst_names = lst.names();
  Rcpp::IntegerVector ix_col = geometries::utils::sexp_col_int( lst_names, x_col );
  Rcpp::IntegerVector iy_col = geometries::utils::sexp_col_int( lst_names, y_col );

  return Rcpp::List::create(
    Rcpp::_["x_col"] = ix_col,
    Rcpp::_["y_col"] = iy_col
  );


}

// ----------------------------
// columns.hpp

// [[Rcpp::export(.test_column_check)]]
void test_column_check( SEXP x, SEXP cols ) {
  geometries::utils::column_check( x, cols );
}

// [[Rcpp::export]]
SEXP test_other_columns_impl() {

  //Rcpp::IntegerVector na = { R_NilValue, R_NilValue };

  Rcpp::NumericVector x = {1,1,2,2,2,3};
  Rcpp::NumericVector y = {1,1,1,2,2,2};
  Rcpp::NumericVector z = {1,2,3,4,5,6};

  Rcpp::List l = Rcpp::List::create(
    Rcpp::_["x"] = x,
    Rcpp::_["y"] = y,
    Rcpp::_["z"] = z
  );
  SEXP df = Rcpp::as< Rcpp::DataFrame >( l );

  SEXP x_col_int = Rf_ScalarInteger( 0 );
  SEXP y_col_int = Rf_ScalarInteger( 1 );
  //SEXP z_col_int = Rf_ScalarInteger( 2 );

  // SEXP x_col_dbl = Rf_ScalarReal( 0 );
  // SEXP y_col_dbl = Rf_ScalarReal( 1 );
  // //SEXP z_col_dbl = Rf_ScalarReal( 2 );

  SEXP x_col_str = Rf_mkString( "x" );
  SEXP y_col_str = Rf_mkString( "y" );
  //SEXP z_col_str = Rf_mkString( "z" );

  SEXP other_yz_int = geometries::utils::other_columns( df, x_col_int );
  SEXP other_xz_int = geometries::utils::other_columns( df, y_col_int );
  SEXP other_z_int = geometries::utils::other_columns( df, x_col_int, y_col_int );

  // SEXP other_yz_dbl = geometries::utils::other_columns( df, x_col_dbl );
  // SEXP other_xz_dbl = geometries::utils::other_columns( df, y_col_dbl );
  // SEXP other_z_dbl = geometries::utils::other_columns( df, x_col_dbl, y_col_dbl );

  SEXP other_yz_str = geometries::utils::other_columns( df, x_col_str );
  SEXP other_xz_str = geometries::utils::other_columns( df, y_col_str );
  SEXP other_z_str = geometries::utils::other_columns( df, x_col_str, y_col_str );

  return Rcpp::List::create(
    Rcpp::_["other_yz_int"] = other_yz_int,
    Rcpp::_["other_zx_int"] = other_xz_int,
    Rcpp::_["other_z_int"] = other_z_int,
    // Rcpp::_["other_yz_dbl"] = other_yz_dbl,
    // Rcpp::_["other_zx_dbl"] = other_xz_dbl,
    // Rcpp::_["other_z_dbl"] = other_z_dbl,
    Rcpp::_["other_yz_str"] = other_yz_str,
    Rcpp::_["other_zx_str"] = other_xz_str,
    Rcpp::_["other_z_str"] = other_z_str
  );

}

//[[Rcpp::export(.test_other_columns)]]
SEXP test_other_columns( SEXP x, SEXP y, SEXP z ) {
  return geometries::utils::other_columns( x, y, z );
}

// //[[Rcpp::export(.test_column_positions)]]
// SEXP test_column_positions( SEXP x, Rcpp::StringVector cols ) {
//   return geometries::utils::column_positions( x, cols );
// }

// [[Rcpp::export(.test_column_positions)]]
SEXP test_column_positions( SEXP x, SEXP cols ) {
  return geometries::utils::column_positions( x, cols );
}

// ----------------------------
// dataframe.hpp
//[[Rcpp::export(.test_make_dataframe)]]
SEXP test_make_dataframe( Rcpp::List lst, R_xlen_t n_rows, Rcpp::CharacterVector col_names ) {
  return geometries::utils::make_dataframe( lst, n_rows, col_names );
}

// ----------------------------
// unique.hpp

//[[Rcpp::export(.test_unique_ids)]]
SEXP test_unique_ids( SEXP x, SEXP id_col ) {
  return geometries::utils::get_ids( x, id_col );
}

//[[Rcpp::export(.test_unique_sort)]]
SEXP test_unique_sort( SEXP x ) {
  return geometries::utils::get_sexp_unique( x );
}


// ----------------------------
// rleid.hpp

SEXP test_rleid() {

  Rcpp::NumericVector x = {1,1,2,2,2,3};
  Rcpp::NumericVector y = {1,1,1,2,2,2};
  Rcpp::NumericVector z = {1,2,3,4,5,6};

  Rcpp::List l = Rcpp::List::create(
    Rcpp::_["x"] = x,
    Rcpp::_["y"] = y,
    Rcpp::_["z"] = z
  );
  Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( l );

  Rcpp::IntegerVector id1 = {0};
  Rcpp::IntegerVector id2 = {0,1};
  Rcpp::IntegerVector id3 = {0,1,2};

  Rcpp::IntegerVector xx = geometries::utils::rleid( df, id1 );
  Rcpp::IntegerVector xy = geometries::utils::rleid( df, id2 );
  Rcpp::IntegerVector xyz = geometries::utils::rleid( df, id3 );

  // id positions
  Rcpp::IntegerVector id_idx = geometries::utils::rleid_indices( df, id1 );


  return Rcpp::List::create(
    Rcpp::_["x"] = xx,
    Rcpp::_["y"] = xy,
    Rcpp::_["z"] = xyz,
    Rcpp::_["idx"] = id_idx
  );

}

// -------------------------------
// split.hpp
// [[Rcpp::export(.test_split_by_id)]]
SEXP test_split_by_id(
  Rcpp::List lst,
  Rcpp::IntegerVector ids,
  Rcpp::IntegerVector geometry_cols,
  bool last,
  Rcpp::List attributes,
  bool close,
  bool closed_attribute
) {
  return geometries::utils::split_by_id( lst, ids, geometry_cols, last, attributes, close, closed_attribute );
}

// ----------------------------
// fill.hpp

SEXP test_fill_list() {
  Rcpp::NumericVector x = {1,2,3,4};
  Rcpp::IntegerVector line_positions = {0,2};
  Rcpp::List lst = geometries::utils::fill_list( x, line_positions );
  return lst;
}

// ----------------------------
// list.hpp

//[[Rcpp::export(.test_as_list)]]
SEXP test_as_list( SEXP x ) {
  return geometries::utils::as_list( x );
}

SEXP test_list() {
  // test various objects converted to list
  // how are names handled?

  Rcpp::NumericVector x = {1,2,3,4};
  Rcpp::NumericVector y = {4,3,2,1};
  Rcpp::StringVector z(4);
  z[0] = "a";
  z[1] = "b";
  z[2] = "c";
  z[3] = "d";

  Rcpp::NumericMatrix mat(4,2);
  mat( Rcpp::_, 0 ) = x;
  mat( Rcpp::_, 1 ) = y;

  SEXP lst = Rcpp::List::create(
    Rcpp::_["x"] = x,
    Rcpp::_["y"] = z
  );

  SEXP df = Rcpp::as< Rcpp::DataFrame >( lst );

  Rcpp::DataFrame df2 = Rcpp::as< Rcpp::DataFrame >( lst );
  Rcpp::IntegerVector geom_cols = {0};
  Rcpp::NumericMatrix mat_names = geometries::matrix::to_geometry_matrix( df2, geom_cols, true );

  Rcpp::List lst_mat = geometries::utils::as_list( mat );
  Rcpp::List lst_mat_names = geometries::utils::as_list( mat_names );
  Rcpp::List lst_lst_mat = geometries::utils::as_list( lst_mat );
  Rcpp::List lst_df = geometries::utils::as_list( df );
  Rcpp::List lst_lst = geometries::utils::as_list( lst );

  return Rcpp::List::create(
    Rcpp::_["list_mat"] = lst_mat,
    Rcpp::_["list_mat_names"] = lst_mat_names,
    Rcpp::_["list_list_mat"] = lst_lst_mat,
    Rcpp::_["list_df"] = lst_df,
    Rcpp::_["list_lst"] = lst_lst
  );

}

// [[Rcpp::export(.tests)]]
SEXP tests() {
  Rcpp::List mb = test_bbox();
  Rcpp::List rleid = test_rleid();
  Rcpp::List to_matrix = test_matrix();
  Rcpp::List int_col = test_sexp();
  Rcpp::List other_col = test_other_columns_impl();
  Rcpp::List list = test_list();
  Rcpp::List fill = test_fill_list();

  return Rcpp::List::create(
    Rcpp::_["test_bbox"] = mb,
    Rcpp::_["test_rleid"] = rleid,
    Rcpp::_["test_colint"] = int_col,
    Rcpp::_["test_matrix"] = to_matrix,
    Rcpp::_["other_col"] = other_col,
    Rcpp::_["test_list"] = list,
    Rcpp::_["test_fill_list"] = fill
  );
}

