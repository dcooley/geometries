#ifndef R_GEOMETRIES_SHAPES_TO_VEC_H
#define R_GEOMETRIES_SHAPES_TO_VEC_H

#include <Rcpp.h>
#include "geometries/utils/utils.hpp"

namespace geometries {
namespace shapes {

  // #nocov start
  template< int RTYPE >
  inline SEXP to_vec(
      Rcpp::Vector< RTYPE >& v
  ) {
    return v;
  }


  template< int RTYPE >
  inline SEXP to_vec(
      Rcpp::Matrix< RTYPE >& m
  ) {
    R_xlen_t n_row = m.nrow();
    if( n_row != 1 ) {
      Rcpp::stop("geometries - expecting single-row matrix");
    }
    Rcpp::Vector< RTYPE > v = m( 0, Rcpp::_ );
    return v;
  }

  template< int RTYPE >
  inline SEXP to_vec(
      Rcpp::Matrix< RTYPE >& m,
      Rcpp::IntegerVector& geometry_cols
  ) {
    geometries::utils::column_check( m, geometry_cols );
    R_xlen_t n_row = m.nrow();
    if( n_row != 1 ) {
      Rcpp::stop("geometries - expecting single-row matrix");
    }
    R_xlen_t n_col = geometry_cols.length();
    R_xlen_t i;
    Rcpp::Vector< RTYPE > v( n_col );
    for( i = 0; i < n_col; ++i ) {
      int this_col = geometry_cols[ i ];
      v[ i ] = m( 0, this_col );
    }
    return v;
  }

  inline SEXP to_vec(
      Rcpp::DataFrame& df
  ) {
    R_xlen_t n_row = df.nrow();
    if( n_row != 1 ) {
      Rcpp::stop("geometries - expecting single-row data.frame");
    }
    R_xlen_t n_col = df.ncol();
    Rcpp::NumericVector nv( n_col );
    R_xlen_t i;
    for( i = 0; i < n_col; ++i ) {
      nv[i] = df[i];
    }
    return nv;
  }

  inline SEXP to_vec(
      Rcpp::DataFrame& df,
      Rcpp::StringVector& geometry_cols
  ) {
    geometries::utils::column_check( df, geometry_cols );
    R_xlen_t n_col = geometry_cols.length();
    if( df.ncol() < n_col ) {
      Rcpp::stop("geometries - incorrect number of columns");
    }
    R_xlen_t n_row = df.nrow();
    if( n_row != 1 ) {
      Rcpp::stop("geometries - expecting single-row data.frame");
    }
    Rcpp::NumericVector nv( n_col );
    R_xlen_t i;
    for( i = 0; i < n_col; ++i ) {
      Rcpp::String this_col = geometry_cols[ i ];
      nv[i] = df[ this_col ];
    }
    return nv;
  }

  template< int RTYPE >
  inline SEXP to_vec(
      Rcpp::Matrix< RTYPE >& m,
      Rcpp::StringVector& geometry_cols
  ) {
    Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( m );
    return to_vec( df, geometry_cols );
  }

   inline SEXP to_vec(
      Rcpp::DataFrame& df,
      Rcpp::IntegerVector& geometry_cols
  ) {
    Rcpp::NumericMatrix nm = geometries::utils::df_to_matrix( df, geometry_cols );
    return to_vec( nm );
  }

  inline SEXP to_vec(
      SEXP& x,
      Rcpp::IntegerVector& geometry_cols
  ) {
    switch( TYPEOF( x ) ) {
    case INTSXP: {
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
      return to_vec( im, geometry_cols );
    }
    case REALSXP: {
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
      return to_vec( nm, geometry_cols );
    }
    case VECSXP: {
      if( Rf_inherits( x, "data.frame" ) ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return to_vec( df, geometry_cols );
    } // else default
    }
    default: {
      Rcpp::stop("geometries - unsupported type");
    }
    }
    return Rcpp::List::create(); // never reaches
  }

  inline SEXP to_vec(
      SEXP& x,
      Rcpp::StringVector& geometry_cols
  ) {
    switch( TYPEOF( x ) ) {
    case INTSXP: {
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
      return to_vec( im, geometry_cols );
    }
    case REALSXP: {
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
      return to_vec( nm, geometry_cols );
    }
    case VECSXP: {
    if( Rf_inherits( x, "data.frame" ) ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return to_vec( df, geometry_cols );
    } // else default
    }
    default: {
      Rcpp::stop("geometries - unsupported type");
    }
    }
    return Rcpp::List::create(); // never reaches
  }

  inline SEXP to_vec(
      SEXP& x
  ) {
    switch( TYPEOF( x ) ) {
    case INTSXP: {
      if( Rf_isMatrix( x ) ) {
      Rcpp::IntegerMatrix im = Rcpp::as< Rcpp::IntegerMatrix >( x );
      return to_vec( im );
    } else {
      Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( x );
      return to_vec( iv );
    }
    case REALSXP: {
      if( Rf_isMatrix( x ) ) {
      Rcpp::NumericMatrix nm = Rcpp::as< Rcpp::NumericMatrix >( x );
      return to_vec( nm );
    } else {
      Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( x );
      return to_vec( nv );
    }
    }
    case VECSXP: {
      if( Rf_inherits( x, "data.frame" ) ) {
      Rcpp::DataFrame df = Rcpp::as< Rcpp::DataFrame >( x );
      return to_vec( df );
    } // else default
    }
    default: {
      Rcpp::stop("geometries - unsupported type");
    }
    }
    }
    return Rcpp::List::create(); // never reaches
  }

  inline SEXP to_vec(
      SEXP& x,
      SEXP& geometry_cols
  ) {

    if( Rf_isNull( geometry_cols ) ) {
      return to_vec( x );
    }

    switch( TYPEOF( geometry_cols ) ) {
    case REALSXP: {}
    case INTSXP: {
      Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( geometry_cols );
      if( iv.length() == 0 ) {
        return to_vec( x );
      } else {
        return to_vec( x, iv );
      }
    }
    case STRSXP: {
      Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( geometry_cols );
      if( sv.length() == 0 ) {
        return to_vec( x );
      } else {
        return to_vec( x, sv );
      }
    }
    default: {
      Rcpp::stop("geometries - unknown column types");
    }
    }
  }
  // #nocov end
}
} // geometries


#endif
