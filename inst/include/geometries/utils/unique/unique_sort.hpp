#ifndef R_GEOMETRIES_UTILS_UNIQUE_SORT_H
#define R_GEOMETRIES_UTILS_UNIQUE_SORT_H

#include <Rcpp.h>

namespace geometries {
namespace utils {

   // issue 27 (sfheaders)
  template < typename T, int RTYPE >
  inline SEXP sexp_unique( Rcpp::Vector< RTYPE > x ) {
    std::set< T > seen;
    auto newEnd = std::remove_if( x.begin(), x.end(), [&seen]( const T value ) {
      if ( seen.find( value ) != std::end( seen ) ) {
        return true;
      }
      seen.insert( value );
      return false;
    });
    x.erase( newEnd, x.end() );
    return x;
  }


  // returns unique values in their original input order
  inline SEXP get_sexp_unique( SEXP s ) {

    SEXP s2 = Rcpp::clone( s );

    switch( TYPEOF( s2 ) ) {
    case LGLSXP: {
      return sexp_unique< bool, LGLSXP >( s2 );
    }
    case REALSXP: {
      return sexp_unique< double, REALSXP >( s2 );
    }
    case INTSXP: {
      return sexp_unique< int, INTSXP >( s2 );
    }
    case STRSXP: {
      return sexp_unique< char* , STRSXP >( s2 );
    }
    default: Rcpp::stop("geometries - unknown vector type");
    }
    return 0;
  }

} // utils
} // geometries


#endif
