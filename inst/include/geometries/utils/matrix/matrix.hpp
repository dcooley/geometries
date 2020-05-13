#ifndef R_GEOMETRIES_UTILS_MATRIX_H
#define R_GEOMETRIES_UTILS_MATRIX_H

#include <Rcpp.h>

namespace geometries {
namespace utils {

  // #nocov start
  inline Rcpp::StringVector matrix_names(
      Rcpp::List& m_attr
  ) {
    if( m_attr.size() < 2 ) {
      Rcpp::stop("geometries - could not find matrix names. Perhaps your matrix does not have names");
    }
    Rcpp::StringVector matrix_names = m_attr[1];
    return matrix_names;
  }

  template < int RTYPE >
  inline Rcpp::StringVector matrix_names(
      Rcpp::Matrix< RTYPE >& m
  ) {
    Rcpp::List m_attr = m.attr("dimnames");
    return matrix_names( m_attr );
  }

  inline Rcpp::NumericMatrix df_to_matrix(
      Rcpp::DataFrame& df
  ) {
    int i;
    int n_cols = df.cols();
    int n_rows = df.rows();
    Rcpp::StringVector df_names = df.names();
    Rcpp::NumericMatrix nm( n_rows, n_cols );
    for( i = 0; i < n_cols; ++i ) {
      Rcpp::NumericVector this_column = Rcpp::as< Rcpp::NumericVector >( df[ i ] );
      nm( Rcpp::_, i ) = this_column;
    }

    Rcpp::List m_attr(2);
    m_attr(1) = df_names;

    nm.attr("dimnames") = m_attr;
    return nm;
  }

  inline Rcpp::NumericMatrix df_to_matrix(
      Rcpp::DataFrame& df,
      Rcpp::IntegerVector& cols // may only want a subset of columns
  ) {
    int i;
    int n_cols = cols.size();
    int n_rows = df.rows();

    if( n_cols > df.ncol() ) {
      Rcpp::stop("geometries - number of columns requested is greater than those available");
    }

    int max_idx = Rcpp::max( cols );
    if( max_idx > ( df.ncol() - 1 ) ) {
      Rcpp::stop("geometries - invalid column index");
    }

    Rcpp::StringVector df_names = df.names();
    Rcpp::StringVector m_names( n_cols );
    Rcpp::NumericMatrix nm( n_rows, n_cols );
    for( i = 0; i < n_cols; ++i ) {
      int this_col = cols[i];
      m_names[i] = df_names[ this_col ];
      Rcpp::NumericVector this_column = Rcpp::as< Rcpp::NumericVector >( df[ this_col ] );
      nm( Rcpp::_, i ) = this_column;
    }

    Rcpp::List m_attr(2);
    m_attr(1) = m_names;

    nm.attr("dimnames") = m_attr;
    return nm;
  }

  inline Rcpp::NumericMatrix df_to_matrix(
      Rcpp::DataFrame& df,
      Rcpp::StringVector& cols // may only want a subset of columns
  ) {
    int i;
    int n_cols = cols.size();
    int n_rows = df.rows();
    if( n_cols > df.ncol() ) {
      Rcpp::stop("geometries - number of columns requested is greater than those available");
    }
    Rcpp::StringVector df_names = df.names();
    Rcpp::StringVector m_names( n_cols );
    Rcpp::NumericMatrix nm( n_rows, n_cols );
    for( i = 0; i < n_cols; ++i ) {
      Rcpp::String this_col = cols[ i ];
      m_names[i] = this_col;
      Rcpp::NumericVector this_column = Rcpp::as< Rcpp::NumericVector >( df[ this_col ] );
      nm( Rcpp::_, i ) = this_column;
    }

    Rcpp::List m_attr(2);
    m_attr(1) = m_names;

    nm.attr("dimnames") = m_attr;
    return nm;
  }

  template< int RTYPE >
  inline Rcpp::Matrix< RTYPE > matrix_row_to_matrix(
    Rcpp::Matrix< RTYPE >& m,
    R_xlen_t& i
  ) {
    Rcpp::Vector< RTYPE > this_row = m( i, Rcpp::_ );
    R_xlen_t n_col = m.ncol();
    Rcpp::Matrix< RTYPE > m2( 1, n_col );
    m2( 0, Rcpp::_ ) = this_row;
    return m2;
  }
  // #nocov end


} // utils
} // geometries

#endif
