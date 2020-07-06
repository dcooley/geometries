#ifndef R_GEOMETRIES_UTILS_DATAFRAME_H
#define R_GEOMETRIES_UTILS_DATAFRAME_H

namespace geometries {
namespace utils {

  inline Rcpp::IntegerVector int_names( Rcpp::StringVector& df_names, Rcpp::StringVector& s ) {

    Rcpp::IntegerVector ians( s.length() );
    //Rcpp::StringVector nms = x.names();

    R_xlen_t i, j;
    for(i = 0; i < s.length(); ++i ) {
      const char * id = s[ i ];
      for(j = 0; j < df_names.length(); ++j ) {
        const char * n = df_names[ j ];
        if( strcmp( id, n ) == 0 ) {
          ians[ i ] = j;
          break;
        }
      }
    }
    return ians;
  }

  inline Rcpp::DataFrame make_dataframe(
      Rcpp::List& res,
      R_xlen_t& total_rows,
      Rcpp::CharacterVector& column_names
  ) {

    res.attr("class") = Rcpp::CharacterVector("data.frame");

    if( total_rows > 0 ) {
      Rcpp::IntegerVector rownames = Rcpp::seq( 1, total_rows );
      res.attr("row.names") = rownames;
    } else {
      res.attr("row.names") = Rcpp::IntegerVector(0);  // #nocov
    }

    res.attr("names") = column_names;
    return res;

  }

} // utils
} // geometries

#endif
