#ifndef R_GEOMETRIES_SHAPES_TO_LIST_MAT_H
#define R_GEOMETRIES_SHAPES_TO_LIST_MAT_H

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
  template< int RTYPE >
  inline SEXP to_listMat(
    Rcpp::Matrix< RTYPE >& m
  ) {
    Rcpp::List lst(1);
    lst[0] = m;
    return lst;
  }

  inline SEXP to_listMat(
    Rcpp::DataFrame& df
  ) {
    Rcpp::NumericMatrix nm = geometries::utils::df_to_matrix( df );
    return to_listMat( nm );
  }

  inline SEXP to_listMat(
      Rcpp::DataFrame& df,
      Rcpp::StringVector& geometry_cols,
      int& start,
      int& end
  ) {
    geometries::utils::column_check( df, geometry_cols );
    R_xlen_t i;
    R_xlen_t n_col = geometry_cols.length();
    int line_rows = end - start + 1;

    Rcpp::NumericMatrix a_line( line_rows, ( n_col) );

    for( i = 0; i < n_col; ++i ) {
      Rcpp::String this_col = geometry_cols[ i ];
      Rcpp::NumericVector v = Rcpp::as< Rcpp::NumericVector >( df[ this_col ] );
      a_line( Rcpp::_, i ) = v[ Rcpp::Range(start, end) ];
    }
    return a_line;
  }

  inline SEXP to_listMat(
      Rcpp::DataFrame& df,
      Rcpp::IntegerVector& geometry_cols,
      int& start,
      int& end
  ) {

    geometries::utils::column_check( df, geometry_cols );
    R_xlen_t i;
    R_xlen_t n_col = geometry_cols.length();
    int line_rows = end - start + 1;
    Rcpp::NumericMatrix a_line( line_rows, ( n_col) );

    for( i = 0; i < n_col; ++i ) {
      int this_col = geometry_cols[ i ];
      Rcpp::NumericVector v = Rcpp::as< Rcpp::NumericVector >( df[ this_col ] );
      a_line( Rcpp::_, i ) = v[ Rcpp::Range(start, end) ];
    }
    return a_line;
  }


  // gets lines from data.farme
  // when the start & end rows are known
  // where geometry_cols are ordered?
  template < int RTYPE >
  inline SEXP to_listMat(
      Rcpp::Matrix< RTYPE >& m,
      Rcpp::IntegerVector& geometry_cols,
      int& start,
      int& end
  ) {
    geometries::utils::column_check( m, geometry_cols );
    R_xlen_t n_col = geometry_cols.length();

    if( n_col <= 1 ) {
      Rcpp::stop("geometries - need at least 2 columns");
    }

    // matrix can just be subset by cols and rows
    Rcpp::Range rows = Rcpp::Range( start, end );
    Rcpp::Range cols = Rcpp::Range( geometry_cols[0], geometry_cols[ ( n_col - 1 ) ] );
    Rcpp::Matrix< RTYPE > a_line = m( rows, cols );
    return a_line;
  }

  template < int RTYPE >
  inline SEXP to_listMat(
      Rcpp::Matrix< RTYPE >& m,
      Rcpp::StringVector& geometry_cols,
      int& start,
      int& end
  ) {
    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( m );
    return to_listMat( df, geometry_cols, start, end );
  }

  inline SEXP to_listMat(
    Rcpp::DataFrame& df,
    Rcpp::IntegerVector& geometry_cols
  ) {
    Rcpp::List lst(1);
    lst[0] = geometries::shapes::to_mat( df, geometry_cols );
    return lst;
  }

  inline SEXP to_listMat(
      Rcpp::DataFrame& df,
      Rcpp::StringVector& geometry_cols,
      SEXP& line_ids
  ) {

    Rcpp::IntegerMatrix line_positions = geometries::utils::id_positions( line_ids );

    R_xlen_t n_lines = line_positions.nrow();

    Rcpp::List mls( n_lines );

    // now iterate through the data.frame and get the matrices of lines
    R_xlen_t i;
    for( i = 0; i < n_lines; ++i ) {

      int start = line_positions(i, 0);
      int end = line_positions(i, 1);
      mls( i ) = to_listMat( df, geometry_cols, start, end );  // this version returns a matrix
    }

    return mls;
  }

  inline SEXP to_listMat(
      Rcpp::DataFrame& df,
      Rcpp::IntegerVector& geometry_cols,
      SEXP& line_ids
  ) {

    Rcpp::IntegerMatrix line_positions = geometries::utils::id_positions( line_ids );

    R_xlen_t n_lines = line_positions.nrow();

    Rcpp::List mls( n_lines );

    // now iterate through the data.frame and get the matrices of lines
    R_xlen_t i;
    for( i = 0; i < n_lines; ++i ) {

      int start = line_positions(i, 0);
      int end = line_positions(i, 1);
      mls( i ) = to_listMat( df, geometry_cols, start, end );  // this version returns a matrix
    }

    return mls;
  }

  inline SEXP to_listMat(
      Rcpp::DataFrame& df,
      Rcpp::IntegerVector& geometry_cols,
      Rcpp::NumericVector& line_ids
  ) {

    Rcpp::IntegerMatrix line_positions = geometries::utils::id_positions( line_ids );

    R_xlen_t n_lines = line_positions.nrow();

    Rcpp::List mls( n_lines );

    int start;
    int end;
    if( n_lines == 1 ) {
      //mls( 0 ) = to_listMat( df, geometry_cols );
      //return mls;
      mls( 0 ) = geometries::shapes::to_mat( df, geometry_cols );
      return mls;
    }

    // now iterate through the data.frame and get the matrices of lines
    R_xlen_t i;
    for( i = 0; i < n_lines; ++i ) {

      start = line_positions(i, 0);
      end = line_positions(i, 1);

      mls( i ) = to_listMat( df, geometry_cols, start, end );
    }

    return mls;
  }

  // now we know where the columns are, we need to get teh vector of line_ids
  // then we can start subsetting
  inline SEXP to_listMat(
    Rcpp::DataFrame& df,
    Rcpp::IntegerVector& cols,
    int& id_col
  ) {
    geometries::utils::column_exists( df, id_col );

    SEXP line_ids = df[ id_col ];
    return to_listMat( df, cols, line_ids );
  }


  inline SEXP to_listMat(
    Rcpp::DataFrame& df,
    Rcpp::StringVector& cols,
    Rcpp::String& id_col
  ) {
    SEXP line_ids = df[ id_col ];
    return to_listMat( df, cols, line_ids );
  }

  template< int RTYPE >
  inline SEXP to_listMat(
    Rcpp::Matrix< RTYPE >& m,
    Rcpp::StringVector& cols,
    Rcpp::String& id_col
  ) {
    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( m );
    return to_listMat( df, cols, id_col );
  }

  template< int RTYPE >
  inline SEXP to_listMat(
      Rcpp::Matrix< RTYPE >& m,
      Rcpp::IntegerVector& cols,
      int& id_col
  ) {
    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( m );
    return to_listMat( df, cols, id_col );
  }

  inline SEXP to_listMat(
    SEXP& x,
    SEXP& cols
  ) {
    Rcpp::NumericMatrix nm = geometries::shapes::to_mat( x, cols );
    return to_listMat( nm );
  }

  inline SEXP to_listMat(
      SEXP& x,
      Rcpp::StringVector& cols,
      Rcpp::String& id_col
  ){
    switch( TYPEOF( x ) ) {
    case INTSXP: {
      if( !Rf_isMatrix( x ) ) {
        Rcpp::stop("geometries - lines need to be matrices or data.frames");
      } else {
        Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
        return to_listMat( im, cols, id_col );
      }
    }
    case REALSXP: {
      if( !Rf_isMatrix( x ) ) {
        Rcpp::stop("geometries - lines need to be matrices or data.frames");
      } else {
        Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
        return to_listMat( nm, cols, id_col );
      }
    }
    case VECSXP: {
      if( Rf_inherits( x, "data.frame" ) ) {
        Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
        return to_listMat( df, cols, id_col );
      } // else default
    }
    default: {
      Rcpp::stop("geometries - unknown lines types");
    }
    }
    return Rcpp::List::create(); // never reaches
  }

  inline SEXP to_listMat(
    SEXP& x,
    Rcpp::IntegerVector& cols,
    int& id_col
  ){
    switch( TYPEOF( x ) ) {
    case INTSXP: {
    if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("geometries - lines need to be matrices or data.frames");
    } else {
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
      return to_listMat( im, cols, id_col );
    }
    }
    case REALSXP: {
    if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("geometries - lines need to be matrices or data.frames");
    } else {
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
      return to_listMat( nm, cols, id_col );
    }
    }
    case VECSXP: {
    if( Rf_inherits( x, "data.frame" ) ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return to_listMat( df, cols, id_col );
    } // else default
    }
    default: {
      Rcpp::stop("geometries - unknown lines types");
    }
    }
    return Rcpp::List::create(); // never reaches
  }

  // inline SEXP to_listMat(
  //     SEXP& x,
  //     SEXP& cols,
  //     Rcpp::StringVector& id_col
  // ){
  //
  // }

  inline SEXP to_listMat(
    SEXP& x,
    SEXP& cols,  // stringvector or integervector
    SEXP& id_col // stringvector or integervector
  ) {

    if( TYPEOF( id_col ) != TYPEOF( cols ) ) {
      Rcpp::stop("geometries - different column types detected");
    }

    switch( TYPEOF( id_col ) ) {
    case REALSXP: {}
    case INTSXP: {
      Rcpp::IntegerVector iv_id_col = Rcpp::as< Rcpp::IntegerVector >( id_col );
      int i_id_col = iv_id_col[0];
      Rcpp::IntegerVector iv_cols = Rcpp::as< Rcpp::IntegerVector >( cols );
      return to_listMat( x, iv_cols, i_id_col );
    }
    case STRSXP: {
      Rcpp::StringVector sv_id_col = Rcpp::as< Rcpp::StringVector >( id_col );
      Rcpp::String s_id_col = sv_id_col[0];
      Rcpp::StringVector sv_cols = Rcpp::as< Rcpp::StringVector >( cols );
      return to_listMat( x, sv_cols, s_id_col );
    }
    default: {
      Rcpp::stop("geometries - unknown id column types");
    }
    }
    return Rcpp::List::create(); // never reaches
  }

  // #nocov end

}
} // geometries


#endif
