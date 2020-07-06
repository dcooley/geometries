#ifndef R_GEOMETRIES_SHAPES_TO_MAT_H
#define R_GEOMETRIES_SHAPES_TO_MAT_H

#include <Rcpp.h>
#include "geometries/utils/utils.hpp"

namespace geometries {
namespace matrix {

  /*
   * to_listMat
   *
   * Converts various inputs into a matrix structure
   */
  template< int RTYPE >
  inline SEXP to_mat(
    Rcpp::Matrix< RTYPE >& m
  ) {
    return m;
  }

  inline SEXP to_mat(
    Rcpp::DataFrame& df
  ) {
    Rcpp::NumericMatrix nm = geometries::utils::df_to_matrix( df );
    return nm;
  }

  template< int RTYPE >
  inline SEXP to_mat(
      Rcpp::Matrix< RTYPE >& m,
      Rcpp::IntegerVector& geometry_cols
  ) {
    geometries::utils::column_check( m, geometry_cols );
    R_xlen_t n_row = m.nrow();
    R_xlen_t n_col = geometry_cols.size();
    R_xlen_t i;
    Rcpp::Matrix< RTYPE > m2( n_row, n_col );
    for( i = 0; i < n_col; ++i ) {
      int this_col = geometry_cols[ i ];
      m2( Rcpp::_, i ) = m( Rcpp::_, this_col );
    }
    return m2;
  }

  inline SEXP to_mat(
      Rcpp::DataFrame& df,
      Rcpp::StringVector& geometry_cols
  ) {
    geometries::utils::column_check( df, geometry_cols );
    R_xlen_t n_col = geometry_cols.size();
    if( df.ncol() < n_col ) {
      Rcpp::stop("geometries - incorrect number of columns");
    }
    R_xlen_t n_row = df.nrow();
    Rcpp::NumericMatrix nm( n_row, n_col );
    R_xlen_t i;

    for( i = 0; i < n_col; ++i ) {
      Rcpp::String this_col = geometry_cols[i];
      Rcpp::NumericVector this_vec = df[ this_col ];
      nm( Rcpp::_, i ) = this_vec;
    }
    return nm;
  }

  template< int RTYPE >
  inline SEXP to_mat(
    Rcpp::Matrix< RTYPE >& m,
    Rcpp::StringVector& geometry_cols
  ) {
    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( m );
    return to_mat( df, geometry_cols );
  }

  inline SEXP to_mat(
    Rcpp::DataFrame& df,
    Rcpp::IntegerVector& geometry_cols
  ) {
    Rcpp::NumericMatrix nm = geometries::utils::df_to_matrix( df, geometry_cols );
    return to_mat( nm );
  }


  inline SEXP to_mat(
      SEXP& x,
      Rcpp::StringVector& geometry_cols
  ) {
    switch( TYPEOF( x ) ) {
    case INTSXP: {
      if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("geometries - lines need to be matrices or data.frames");
    } else {
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
      return to_mat( im, geometry_cols );
    }
    case REALSXP: {
      if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("geometries - lines need to be matrices or data.frames");
    } else {
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
      return to_mat( nm, geometry_cols );
    }
    }
    case VECSXP: {
      if( Rf_inherits( x, "data.frame" ) ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return to_mat( df, geometry_cols );
    } // else default
    }
    default: {
      Rcpp::stop("geometries - lines need to be matrices or data.frames");
    }
    }
    }
    return Rcpp::List::create(); // never reaches
  }

  inline SEXP to_mat(
      SEXP& x,
      Rcpp::IntegerVector& geometry_cols
  ) {
    switch( TYPEOF( x ) ) {
    case INTSXP: {
      if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("geometries - lines need to be matrices or data.frames");
    } else {
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
      return to_mat( im, geometry_cols );
    }
    case REALSXP: {
      if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("geometries - lines need to be matrices or data.frames");
    } else {
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
      return to_mat( nm, geometry_cols );
    }
    }
    case VECSXP: {
      if( Rf_inherits( x, "data.frame" ) ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return to_mat( df, geometry_cols );
    } // else default
    }
    default: {
      Rcpp::stop("geometries - lines need to be matrices or data.frames");
    }
    }
    }
    return Rcpp::List::create(); // never reaches
  }

  inline SEXP to_mat(
      SEXP& x
  ) {
    switch( TYPEOF( x ) ) {
    case INTSXP: {
    if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("geometries - lines need to be matrices or data.frames");
    } else {
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
      return to_mat( im );
    }
    case REALSXP: {
    if( !Rf_isMatrix( x ) ) {
      Rcpp::stop("geometries - lines need to be matrices or data.frames");
    } else {
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
      return to_mat( nm );
    }
    }
    case VECSXP: {
    if( Rf_inherits( x, "data.frame" ) ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return to_mat( df );
    } // else default
    }
    default: {
      Rcpp::stop("geometries - lines need to be matrices or data.frames");
    }
    }
    }
    return Rcpp::List::create(); // never reaches
  }

  inline SEXP to_mat(
      SEXP& x,
      SEXP& geometry_cols
  ) {
    if( Rf_isNull( geometry_cols ) ) {
      return to_mat( x );
    }

    switch( TYPEOF( geometry_cols ) ) {
    case REALSXP: {}
    case INTSXP: {
      Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( geometry_cols );
      if( iv.length() == 0 ) {
        return to_mat( x );
      } else {
        return to_mat( x, iv );
      }
    }
    case STRSXP: {
      Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( geometry_cols );
      if( sv.length() == 0 ) {
        return to_mat( x );
      } else {
        return to_mat( x, sv );
      }
    }
    default: {
      Rcpp::stop("geometries - unknown column types");
    }
    }
  }

} // shapes
} // geometries


#endif
