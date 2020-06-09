#ifndef R_GEOMETRIES_SHAPES_NEST_H
#define R_GEOMETRIES_SHAPES_NEST_H

#include <Rcpp.h>
#include "geometries/utils/utils.hpp"
#include "geometries/shapes/mat/to_mat.hpp"

namespace geometries {
namespace shapes {

// #nocov start
/*
 * to_listMat
 *
 * Converts various inputs into a list[[ matrix ]] structure
 */
// template< int RTYPE >
// inline SEXP to_listMat(
//     Rcpp::Matrix< RTYPE >& m
// ) {
//   Rcpp::List lst(1);
//   lst[0] = m;
//   return lst;
// }
//
// inline SEXP to_listMat(
//     Rcpp::DataFrame& df
// ) {
//   Rcpp::NumericMatrix nm = geometries::utils::df_to_matrix( df );
//   return to_listMat( nm );
// }
//
// inline SEXP to_listMat(
//     Rcpp::DataFrame& df,
//     Rcpp::StringVector& geometry_cols,
//     int& start,
//     int& end
// ) {
//   geometries::utils::column_check( df, geometry_cols );
//   R_xlen_t i;
//   R_xlen_t n_col = geometry_cols.length();
//   int line_rows = end - start + 1;
//
//   Rcpp::NumericMatrix a_line( line_rows, ( n_col) );
//
//   for( i = 0; i < n_col; ++i ) {
//     Rcpp::String this_col = geometry_cols[ i ];
//     Rcpp::NumericVector v = Rcpp::as< Rcpp::NumericVector >( df[ this_col ] );
//     a_line( Rcpp::_, i ) = v[ Rcpp::Range(start, end) ];
//   }
//   return a_line;
// }
//
// inline SEXP to_listMat(
//     Rcpp::DataFrame& df,
//     Rcpp::IntegerVector& geometry_cols,
//     int& start,
//     int& end
// ) {
//
//   geometries::utils::column_check( df, geometry_cols );
//   R_xlen_t i;
//   R_xlen_t n_col = geometry_cols.length();
//   int line_rows = end - start + 1;
//   Rcpp::NumericMatrix a_line( line_rows, ( n_col) );
//
//   for( i = 0; i < n_col; ++i ) {
//     int this_col = geometry_cols[ i ];
//     Rcpp::NumericVector v = Rcpp::as< Rcpp::NumericVector >( df[ this_col ] );
//     a_line( Rcpp::_, i ) = v[ Rcpp::Range(start, end) ];
//   }
//   return a_line;
// }
//
//
// // gets lines from data.farme
// // when the start & end rows are known
// // where geometry_cols are ordered?
// template < int RTYPE >
// inline SEXP to_listMat(
//     Rcpp::Matrix< RTYPE >& m,
//     Rcpp::IntegerVector& geometry_cols,
//     int& start,
//     int& end
// ) {
//   geometries::utils::column_check( m, geometry_cols );
//   R_xlen_t n_col = geometry_cols.length();
//
//   if( n_col <= 1 ) {
//     Rcpp::stop("geometries - need at least 2 columns");
//   }
//
//   // matrix can just be subset by cols and rows
//   Rcpp::Range rows = Rcpp::Range( start, end );
//   Rcpp::Range cols = Rcpp::Range( geometry_cols[0], geometry_cols[ ( n_col - 1 ) ] );
//   Rcpp::Matrix< RTYPE > a_line = m( rows, cols );
//   return a_line;
// }
//
// template < int RTYPE >
// inline SEXP to_listMat(
//     Rcpp::Matrix< RTYPE >& m,
//     Rcpp::StringVector& geometry_cols,
//     int& start,
//     int& end
// ) {
//   Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( m );
//   return to_listMat( df, geometry_cols, start, end );
// }
//
// inline SEXP to_listMat(
//     Rcpp::DataFrame& df,
//     Rcpp::IntegerVector& geometry_cols
// ) {
//   Rcpp::List lst(1);
//   lst[0] = geometries::shapes::to_mat( df, geometry_cols );
//   return lst;
// }
//
// inline SEXP to_listMat(
//     Rcpp::DataFrame& df,
//     Rcpp::StringVector& geometry_cols,
//     SEXP& line_ids
// ) {
//
//   Rcpp::IntegerMatrix line_positions = geometries::utils::id_positions( line_ids );
//
//   R_xlen_t n_lines = line_positions.nrow();
//
//   Rcpp::List mls( n_lines );
//
//   // now iterate through the data.frame and get the matrices of lines
//   R_xlen_t i;
//   for( i = 0; i < n_lines; ++i ) {
//
//     int start = line_positions(i, 0);
//     int end = line_positions(i, 1);
//     mls( i ) = to_listMat( df, geometry_cols, start, end );  // this version returns a matrix
//   }
//
//   return mls;
// }
//
// inline SEXP to_listMat(
//     Rcpp::DataFrame& df,
//     Rcpp::IntegerVector& geometry_cols,
//     SEXP& line_ids
// ) {
//
//   Rcpp::IntegerMatrix line_positions = geometries::utils::id_positions( line_ids );
//
//   R_xlen_t n_lines = line_positions.nrow();
//
//   Rcpp::List mls( n_lines );
//
//   // now iterate through the data.frame and get the matrices of lines
//   R_xlen_t i;
//   for( i = 0; i < n_lines; ++i ) {
//
//     int start = line_positions(i, 0);
//     int end = line_positions(i, 1);
//     mls( i ) = to_listMat( df, geometry_cols, start, end );  // this version returns a matrix
//   }
//
//   return mls;
// }
//
// inline SEXP to_listMat(
//     Rcpp::DataFrame& df,
//     Rcpp::IntegerVector& geometry_cols,
//     Rcpp::NumericVector& line_ids
// ) {
//
//   Rcpp::IntegerMatrix line_positions = geometries::utils::id_positions( line_ids );
//
//   R_xlen_t n_lines = line_positions.nrow();
//
//   Rcpp::List mls( n_lines );
//
//   int start;
//   int end;
//   if( n_lines == 1 ) {
//     //mls( 0 ) = to_listMat( df, geometry_cols );
//     //return mls;
//     mls( 0 ) = geometries::shapes::to_mat( df, geometry_cols );
//     return mls;
//   }
//
//   // now iterate through the data.frame and get the matrices of lines
//   R_xlen_t i;
//   for( i = 0; i < n_lines; ++i ) {
//
//     start = line_positions(i, 0);
//     end = line_positions(i, 1);
//
//     mls( i ) = to_listMat( df, geometry_cols, start, end );
//   }
//
//   return mls;
// }
//
// // now we know where the columns are, we need to get teh vector of line_ids
// // then we can start subsetting
// inline SEXP to_listMat(
//     Rcpp::DataFrame& df,
//     Rcpp::IntegerVector& cols,
//     int& id_col
// ) {
//   geometries::utils::column_exists( df, id_col );
//
//   SEXP line_ids = df[ id_col ];
//   return to_listMat( df, cols, line_ids );
// }
//
//
// inline SEXP to_listMat(
//     Rcpp::DataFrame& df,
//     Rcpp::StringVector& cols,
//     Rcpp::String& id_col
// ) {
//   SEXP line_ids = df[ id_col ];
//   return to_listMat( df, cols, line_ids );
// }
//
// template< int RTYPE >
// inline SEXP to_listMat(
//     Rcpp::Matrix< RTYPE >& m,
//     Rcpp::StringVector& cols,
//     Rcpp::String& id_col
// ) {
//   Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( m );
//   return to_listMat( df, cols, id_col );
// }
//
// template< int RTYPE >
// inline SEXP to_listMat(
//     Rcpp::Matrix< RTYPE >& m,
//     Rcpp::IntegerVector& cols,
//     int& id_col
// ) {
//   Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( m );
//   return to_listMat( df, cols, id_col );
// }
//
// inline SEXP to_listMat(
//     SEXP& x,
//     SEXP& cols
// ) {
//   Rcpp::NumericMatrix nm = geometries::shapes::to_mat( x, cols );
//   return to_listMat( nm );
// }
//
// inline SEXP to_listMat(
//     SEXP& x,
//     Rcpp::StringVector& cols,
//     Rcpp::String& id_col
// ){
//   switch( TYPEOF( x ) ) {
//   case INTSXP: {
//     if( !Rf_isMatrix( x ) ) {
//     Rcpp::stop("geometries - lines need to be matrices or data.frames");
//   } else {
//     Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
//     return to_listMat( im, cols, id_col );
//   }
//   }
//   case REALSXP: {
//     if( !Rf_isMatrix( x ) ) {
//     Rcpp::stop("geometries - lines need to be matrices or data.frames");
//   } else {
//     Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
//     return to_listMat( nm, cols, id_col );
//   }
//   }
//   case VECSXP: {
//     if( Rf_inherits( x, "data.frame" ) ) {
//     Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
//     return to_listMat( df, cols, id_col );
//   } // else default
//   }
//   default: {
//     Rcpp::stop("geometries - unknown lines types");
//   }
//   }
//   return Rcpp::List::create(); // never reaches
// }
//
// inline SEXP to_listMat(
//     SEXP& x,
//     Rcpp::IntegerVector& cols,
//     int& id_col
// ){
//   switch( TYPEOF( x ) ) {
//   case INTSXP: {
//     if( !Rf_isMatrix( x ) ) {
//     Rcpp::stop("geometries - lines need to be matrices or data.frames");
//   } else {
//     Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
//     return to_listMat( im, cols, id_col );
//   }
//   }
//   case REALSXP: {
//     if( !Rf_isMatrix( x ) ) {
//     Rcpp::stop("geometries - lines need to be matrices or data.frames");
//   } else {
//     Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
//     return to_listMat( nm, cols, id_col );
//   }
//   }
//   case VECSXP: {
//     if( Rf_inherits( x, "data.frame" ) ) {
//     Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
//     return to_listMat( df, cols, id_col );
//   } // else default
//   }
//   default: {
//     Rcpp::stop("geometries - unknown lines types");
//   }
//   }
//   return Rcpp::List::create(); // never reaches
// }
//
// inline SEXP to_listMat(
//     SEXP& x,
//     SEXP& cols,  // stringvector or integervector
//     SEXP& id_col // stringvector or integervector
// ) {
//
//   if( TYPEOF( id_col ) != TYPEOF( cols ) ) {
//     Rcpp::stop("geometries - different column types detected");
//   }
//
//   switch( TYPEOF( id_col ) ) {
//   case REALSXP: {}
//   case INTSXP: {
//     Rcpp::IntegerVector iv_id_col = Rcpp::as< Rcpp::IntegerVector >( id_col );
//     int i_id_col = iv_id_col[0];
//     Rcpp::IntegerVector iv_cols = Rcpp::as< Rcpp::IntegerVector >( cols );
//     return to_listMat( x, iv_cols, i_id_col );
//   }
//   case STRSXP: {
//     Rcpp::StringVector sv_id_col = Rcpp::as< Rcpp::StringVector >( id_col );
//     Rcpp::String s_id_col = sv_id_col[0];
//     Rcpp::StringVector sv_cols = Rcpp::as< Rcpp::StringVector >( cols );
//     return to_listMat( x, sv_cols, s_id_col );
//   }
//   default: {
//     Rcpp::stop("geometries - unknown id column types");
//   }
//   }
//   return Rcpp::List::create(); // never reaches
// }

// #nocov end


inline Rcpp::List nest( SEXP& x ) {
  Rcpp::List res(1);
  res[0] = x;
  return res;
}

inline Rcpp::List nest(
  Rcpp::List& lst,
  int depth
) {
  int i;
  Rcpp::List res(1);
  for( i = 0; i < depth; ++i ) {
    res[0] = nest( lst, depth - 1 );
  }
  return res;
}

// template< int RTYPE >
// inline Rcpp::List nest(
//   Rcpp::Matrix< RTYPE >& x,
//   int& depth
// ) {
//   // loop over 'depth' times to create that many list elements
//   int i;
//   Rcpp::List res(1);
//   res[0] = x;
//
//   for( i = 0; i < depth; ++i ) {
//     res[0] = nest( res, depth - 1 );
//   }
//   return res;
// }



// rather than specifying each id column,
// have one 'id' vector, and a 'depth' argument
// the 'id's
// inline SEXP nest(
//   SEXP& x,
//   SEXP& geometry_cols,
//   SEXP& id_cols, // 1...n id cols
//   int& depth // how nested the geometry is.
// ) {
//   // logic
//   // -
// }

//
// inline SEXP to_listListMat(
//     SEXP& x,
//     SEXP& geometry_cols,  // IntegerVector or StringVector
//     SEXP& group_id_col_1, // the outer-most ID column; e.g. multipolygon_id
//     SEXP& group_id_col_2,  // the second-outer-most ID column; e.g. polygon_id
//     SEXP& group_id_col_3  // the inner-most ID column; e.g. line_id
// ) {
//
//   if( ( TYPEOF( group_id_col_1 ) != TYPEOF( group_id_col_2 ) ) ||
//       ( TYPEOF( geometry_cols ) != TYPEOF( group_id_col_1 ) ) ||
//       ( TYPEOF( geometry_cols ) != TYPEOF( group_id_col_3 ) ) ) {
//     Rcpp::stop("geometries - different column types detected");
//   }
//
//   switch( TYPEOF( geometry_cols ) ) {
//   case REALSXP: {}
//   case INTSXP: {
//     Rcpp::IntegerVector iv_geometry_cols = Rcpp::as< Rcpp::IntegerVector >( geometry_cols );
//     Rcpp::IntegerVector iv_group_id_col_1 = Rcpp::as< Rcpp::IntegerVector >( group_id_col_1 );
//     Rcpp::IntegerVector iv_group_id_col_2 = Rcpp::as< Rcpp::IntegerVector >( group_id_col_2 );
//     Rcpp::IntegerVector iv_group_id_col_3 = Rcpp::as< Rcpp::IntegerVector >( group_id_col_3 );
//     int i_group_id_col_1 = iv_group_id_col_1[0];
//     int i_group_id_col_2 = iv_group_id_col_2[0];
//     int i_group_id_col_3 = iv_group_id_col_3[0];
//
//     //Rcpp::stop("stopping");
//     return to_listListMat( x, iv_geometry_cols, i_group_id_col_1, i_group_id_col_2, i_group_id_col_3 );
//   }
//   case STRSXP: {
//     Rcpp::StringVector sv_geometry_cols = Rcpp::as< Rcpp::StringVector >( geometry_cols );
//     Rcpp::StringVector sv_group_id_col_1 = Rcpp::as< Rcpp::StringVector >( group_id_col_1 );
//     Rcpp::StringVector sv_group_id_col_2 = Rcpp::as< Rcpp::StringVector >( group_id_col_2 );
//     Rcpp::StringVector sv_group_id_col_3 = Rcpp::as< Rcpp::StringVector >( group_id_col_3 );
//     Rcpp::String s_group_id_col_1 = sv_group_id_col_1[0];
//     Rcpp::String s_group_id_col_2 = sv_group_id_col_2[0];
//     Rcpp::String s_group_id_col_3 = sv_group_id_col_3[0];
//     return to_listListMat( x, sv_geometry_cols, s_group_id_col_1, s_group_id_col_2, s_group_id_col_3 );
//   }
//   default: {
//     Rcpp::stop("geometries - unknown id column types");
//   }
//   }


}
} // geometries


#endif
