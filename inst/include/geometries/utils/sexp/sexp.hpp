
#ifndef R_GEOMETRIES_UTILS_SEXP_H
#define R_GEOMETRIES_UTILS_SEXP_H

#include <Rcpp.h>

namespace geometries{
namespace utils {

  template < int RTYPE >
  inline Rcpp::StringVector sexp_col_names( Rcpp::Matrix < RTYPE > m ) {
    return colnames( m );
  }

  inline Rcpp::StringVector sexp_col_names( SEXP x ) {
    switch( TYPEOF( x ) ) {
      case INTSXP: {
        return sexp_col_names< INTSXP >( x );
      }
      case REALSXP: {
        return sexp_col_names< REALSXP >( x );
      }
      case VECSXP: {
        if( Rf_inherits( x, "data.frame") || Rf_isNewList( x )) {
          Rcpp::StringVector attr({"names"});
          return Rf_getAttrib( x, attr ) ;
        }
      }
      default: {
        Rcpp::stop("geometries - expecting a data.frame or matrix when trying to get colnames");
      }
    }
  }


  inline R_xlen_t sexp_n_col( SEXP& x ) {

    if( Rf_isMatrix( x ) ) {
      return Rf_ncols( x );
    }

    // if( Rf_isNewList( x ) || Rf_inherits( x, "data.frame") ) {
    //   return Rf_length( x );
    // }
    return Rf_length( x );
  }

  inline R_xlen_t sexp_n_row( SEXP& x ) {

    if( Rf_isNewList( x ) || Rf_inherits( x, "data.frame" ) ) {
      if( Rf_length( x ) == 0 ) {
        return 0;
      } else {
        return Rf_length( VECTOR_ELT( x, 0 ) );
      }
    }

    return Rf_nrows( x );
  }

  template < int RTYPE >
  inline R_xlen_t sexp_length( Rcpp::Vector< RTYPE > v ) {
    return v.length();
  }

  inline R_xlen_t sexp_length( SEXP s ) {

    switch( TYPEOF(s) ) {
    case LGLSXP:
      return sexp_length< LGLSXP >( s );
    case REALSXP:
      return sexp_length< REALSXP >( s );
    case VECSXP:
      return sexp_length< VECSXP >( s );
    case INTSXP:
      return sexp_length< INTSXP >( s );
    case STRSXP:
      return sexp_length< STRSXP >( s );
    default: Rcpp::stop("geometries - unknown vector type");
    }
    return 0;
  }

  // finds the integer index position of column names
  inline Rcpp::IntegerVector sexp_col_int(
      Rcpp::StringVector& names,
      Rcpp::StringVector& s
  ) {

    Rcpp::IntegerVector ians( s.length() );

    R_xlen_t i, j;
    for(i = 0; i < s.length(); ++i ) {
      const char * id = s[ i ];
      for(j = 0; j < names.length(); ++j ) {
        const char * n = names[ j ];
        if( strcmp( id, n ) == 0 ) {
          ians[ i ] = j;
          break;
        }
      }
    }
    return ians;
  }

  inline Rcpp::IntegerVector sexp_col_int(
    Rcpp::DataFrame& df,
    SEXP& v
  ) {
    switch( TYPEOF( v ) ) {
      case INTSXP: {
        return Rcpp::as< Rcpp::IntegerVector >( v );
      }
      case STRSXP: {
        Rcpp::StringVector s = Rcpp::as< Rcpp::StringVector >( v );
        Rcpp::StringVector df_names = df.names();
        return sexp_col_int( df_names, s );
      }
      default: {
        Rcpp::stop("geometries - require either integer or string column indices");
      }
    }
  }

  inline Rcpp::IntegerVector sexp_col_int(
      Rcpp::List& lst,
      SEXP& v
  ) {
    switch( TYPEOF( v ) ) {
      case INTSXP: {
        return Rcpp::as< Rcpp::IntegerVector >( v );
      }
      case STRSXP: {
        Rcpp::StringVector s = Rcpp::as< Rcpp::StringVector >( v );
        Rcpp::StringVector lst_names = lst.names();
        return sexp_col_int( lst_names, s );
      }
      default: {
        Rcpp::stop("geometries - require either integer or string column indices");
      }
    }
  }

  inline Rcpp::IntegerVector sexp_col_int(
      SEXP& x,
      Rcpp::StringVector& s
  ) {
    Rcpp::StringVector names = geometries::utils::sexp_col_names( x );
    return sexp_col_int( names, s );
  }

  inline Rcpp::IntegerVector sexp_col_int(
      SEXP& x,
      SEXP& v
  ) {

    switch( TYPEOF( v ) ) {
      case INTSXP: {
        return Rcpp::as< Rcpp::IntegerVector >( v );
      }
      case STRSXP: {
        Rcpp::StringVector s = Rcpp::as< Rcpp::StringVector >( v );
        return sexp_col_int( x, s );
      }
      default: {
        Rcpp::stop("geometries - require either integer or string column indices");
      }
    }
    return Rcpp::IntegerVector(0);
  }

} // utils
} // geometries




#endif
