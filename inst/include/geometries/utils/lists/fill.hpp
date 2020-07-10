#ifndef R_SFHEADERS_LIST_FILL_H
#define R_SFHEADERS_LIST_FILL_H

namespace geometries {
namespace utils {

  // collapse a vector into a list
  // where line_ids gives the start and end indexes of v to use
  template < int RTYPE >
  inline Rcpp::List fill_list(
      Rcpp::Vector< RTYPE >& v,
      Rcpp::IntegerMatrix& line_positions
  ) {
    R_xlen_t n = line_positions.nrow();  // nrow should also be the row of the final df object we are creating
    Rcpp::List res( n );
    R_xlen_t i;

    for( i = 0; i < n; ++i ) {
      R_xlen_t start = line_positions(i, 0);
      R_xlen_t end = line_positions(i, 1);
      Rcpp::IntegerVector elements = Rcpp::seq( start, end );
      res[ i ] = v[ elements ];
    }
    return res;
  }

  // TODO - handle dates and factors??
  inline Rcpp::List fill_list(
      SEXP& v,
      Rcpp::IntegerMatrix& line_positions
  ) {
    switch( TYPEOF( v ) ) {
      case LGLSXP: {
        Rcpp::LogicalVector lv = Rcpp::as< Rcpp::LogicalVector >( v );
        return fill_list( lv, line_positions );
      }
      case INTSXP: {
        Rcpp::IntegerVector iv = Rcpp::as< Rcpp::IntegerVector >( v );
        return fill_list( iv, line_positions );
      }
      case REALSXP: {
        Rcpp::NumericVector nv = Rcpp::as< Rcpp::NumericVector >( v );
        return fill_list( nv, line_positions );
      }
      case STRSXP: {
        Rcpp::StringVector sv = Rcpp::as< Rcpp::StringVector >( v );
        return fill_list( sv, line_positions );
      }
      default: {
        Rcpp::stop("geometries - unknown column type");
      }
    }
    return Rcpp::List::create(); // #nocov never reaches
  }

} // utils
} // geometries

#endif
