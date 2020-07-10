#include <Rcpp.h>

#include "geometries/bbox/bbox.hpp"
#include "geometries/matrix/to_mat.hpp"
#include "geometries/utils/sexp/sexp.hpp"
#include "geometries/utils/columns/columns.hpp"
#include "geometries/utils/rleid/rleid.hpp"

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
// matrix.hpp

// test various objects make matrix

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

  Rcpp::NumericMatrix nm1 = geometries::matrix::to_matrix( lst );
  Rcpp::NumericMatrix nm2 = geometries::matrix::to_matrix( lst, scols );
  Rcpp::NumericMatrix nm3 = geometries::matrix::to_matrix( lst, icols );

  Rcpp::NumericMatrix nm4 = geometries::matrix::to_matrix( lst, scols, true );
  //Rcpp::NumericMatrix nm5 = geometries::matrix::to_matrix( lst, icols, true );  // integer subset doen't keep names

  Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( lst );

  Rcpp::NumericMatrix nm5 = geometries::matrix::to_matrix( df );
  Rcpp::NumericMatrix nm6 = geometries::matrix::to_matrix( df, scols );
  Rcpp::NumericMatrix nm7 = geometries::matrix::to_matrix( df, icols );

  Rcpp::NumericMatrix nm8 = geometries::matrix::to_matrix( df, scols, true );

  Rcpp::NumericMatrix nm9 = geometries::matrix::to_matrix( nmxy, icols );


  return Rcpp::List::create(
    Rcpp::_["nm1"] = nm1,
    Rcpp::_["nm2"] = nm2,
    Rcpp::_["nm3"] = nm3,
    Rcpp::_["nm4"] = nm4,
    Rcpp::_["nm5"] = nm5,
    Rcpp::_["nm6"] = nm6,
    Rcpp::_["nm7"] = nm7,
    Rcpp::_["nm8"] = nm8,
    Rcpp::_["nm9"] = nm9
  );

}


// ----------------------------
// sexp.hpp
Rcpp::List test_sexp() {

  Rcpp::NumericVector x = {1,2,3,4};
  Rcpp::NumericVector y = {1,2,3,4};

  Rcpp::List lst = Rcpp::List::create(
    Rcpp::_["x"] = x,
    Rcpp::_["y"] = y
  );

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

// [[Rcpp::export]]
SEXP test_other_columns_impl() {

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

  SEXP x_col_dbl = Rf_ScalarReal( 0 );
  SEXP y_col_dbl = Rf_ScalarReal( 1 );
  //SEXP z_col_dbl = Rf_ScalarReal( 2 );

  SEXP x_col_str = Rf_mkString( "x" );
  SEXP y_col_str = Rf_mkString( "y" );
  //SEXP z_col_str = Rf_mkString( "z" );

  SEXP other_yz_int = geometries::utils::other_columns( df, x_col_int );
  SEXP other_xz_int = geometries::utils::other_columns( df, y_col_int );
  SEXP other_z_int = geometries::utils::other_columns( df, x_col_int, y_col_int );

  SEXP other_yz_dbl = geometries::utils::other_columns( df, x_col_dbl );
  SEXP other_xz_dbl = geometries::utils::other_columns( df, y_col_dbl );
  SEXP other_z_dbl = geometries::utils::other_columns( df, x_col_dbl, y_col_dbl );

  SEXP other_yz_str = geometries::utils::other_columns( df, x_col_str );
  SEXP other_xz_str = geometries::utils::other_columns( df, y_col_str );
  SEXP other_z_str = geometries::utils::other_columns( df, x_col_str, y_col_str );

  return Rcpp::List::create(
    Rcpp::_["other_yz_int"] = other_yz_int,
    Rcpp::_["other_zx_int"] = other_xz_int,
    Rcpp::_["other_z_int"] = other_z_int,
    Rcpp::_["other_yz_dbl"] = other_yz_dbl,
    Rcpp::_["other_zx_dbl"] = other_xz_dbl,
    Rcpp::_["other_z_dbl"] = other_z_dbl,
    Rcpp::_["other_yz_str"] = other_yz_str,
    Rcpp::_["other_zx_str"] = other_xz_str,
    Rcpp::_["other_z_str"] = other_z_str
  );

}

//[[Rcpp::export(.other_columns)]]
SEXP test_other_columns( SEXP x, SEXP y, SEXP z ) {
  return geometries::utils::other_columns( x, y, z );
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

  return Rcpp::List::create(
    Rcpp::_["x"] = xx,
    Rcpp::_["y"] = xy,
    Rcpp::_["z"] = xyz
  );

}

// [[Rcpp::export(.tests)]]
SEXP tests() {
  Rcpp::List mb = test_bbox();
  Rcpp::List rleid = test_rleid();
  Rcpp::List to_matrix = test_matrix();
  Rcpp::List int_col = test_sexp();
  Rcpp::List other_col = test_other_columns_impl();

  return Rcpp::List::create(
    Rcpp::_["test_bbox"] = mb,
    Rcpp::_["test_rleid"] = rleid,
    Rcpp::_["test_colint"] = int_col,
    Rcpp::_["test_matrix"] = to_matrix,
    Rcpp::_["other_col"] = other_col
  );
}

