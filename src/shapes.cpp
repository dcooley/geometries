#include <Rcpp.h>

//#include "geometries/shapes/shapes.hpp"
//#include "geometries/utils/dataframe/dataframe.hpp"

#include "geometries/geometries.hpp"
#include "geometries/shapes/nest/nest.hpp"
#include "geometries/coordinates/dimensions.hpp"
//#include "geometries/shapes/shapes.hpp"

// Nest to accept a vector of ids
// if id.length() == depth
// then subset & for-loop over the ids
// and run nest() on the inner objects (with one less id column)


// SEXP nest2(
//     Rcpp::DataFrame& df,
//     Rcpp::StringVector& id_cols,
//     int depth
// ) {
//   if( depth < 1  ) {
//     Rcpp::Rcout << "returning < 1 " << std::endl;
//     return df;
//   }
//
//   // using 'int' because I don't think nesting would every likley go more than 4/5 elements
//
//   int i, j;
//   int n_ids = id_cols.length();
//
//   Rcpp::StringVector inner_ids;
//
//   if( n_ids > 1 ) {
//     Rcpp::Range idx = Rcpp::seq( 1, n_ids - 1 );
//     inner_ids =  id_cols[ idx ];  // subset from 1:end
//   }
//
//   Rcpp::Rcout << "n_ids: " << n_ids << std::endl;
//   Rcpp::Rcout << "depth: " << depth << std::endl;
//   Rcpp::Rcout << "inner_ids: " << inner_ids << std::endl;
//
//   if( n_ids > depth ) {
//     // stop - can't do this
//     Rcpp::stop("geometries - too many id columns supplied for the level of nesting required");
//   }
//
//   Rcpp::List res(1);
//   // TODO
//   // - when depth > n_ids
//   // - need to enter a while loop of nesting
//   if( depth > n_ids ) {
//
//     res[0] = nest2( df, id_cols, depth - 1 );
//
//   } else if ( n_ids == depth ) {
//
//     for( j = 0; j < n_ids; ++j ) {
//       Rcpp::Rcout << "j: " << j << std::endl;
//       Rcpp::Rcout << "id_cols: " << id_cols << std::endl;
//       Rcpp::String id_col = id_cols[ j ];
//       Rcpp::Rcout << "id_col: " << id_col.get_cstring() << std::endl;
//       Rcpp::NumericVector group_ids = df[ id_col ];
//
//       Rcpp::Rcout << "group_ids: " << group_ids << std::endl;
//
//       Rcpp::IntegerMatrix line_positions = geometries::utils::id_positions( group_ids );
//       Rcpp::Rcout << "line_positions: " << std::endl;
//       Rcpp::Rcout << line_positions << std::endl;
//
//       R_xlen_t n_lines = line_positions.nrow();
//       Rcpp::Rcout << "n_lines: " << n_lines << std::endl;
//
//       Rcpp::List inner_res( n_lines );
//       Rcpp::StringVector df_names = df.names();
//
//       for( i = 0; i < n_lines; ++i ) {
//
//         int start = line_positions(i, 0);
//         int end = line_positions(i, 1);
//
//         Rcpp::Range rng( start, end );
//         Rcpp::DataFrame df_subset = geometries::utils::subset_dataframe( df, df_names, start, end );
//
//         int inner_depth = depth;
//
//         while( inner_depth > 0 ) {
//           inner_res[i] = nest2( df_subset, inner_ids, inner_depth - 1 );
//           inner_depth--;
//         }
//       }
//       res[0] = inner_res;
//       //return inner_res;
//     }
//   }
//
//   return res;
//   //return mpl;
// }



// SEXP nest3( Rcpp::DataFrame df, Rcpp::StringVector id_cols, int depth ) {
//   int id_counter = id_cols.length();
//
//   Rcpp::StringVector df_names = df.names();
//
//   R_xlen_t i;
//
//   Rcpp::List res(1);
//
//   // if id_counter == 0;
//   // there are no id columns
//   if( id_counter == 0 ) {
//     // no more ids, so we're at the lowest-level object
//     res[0] = df;
//   }
//
//   Rcpp::String id_col = id_cols[0];
//
//   // iff id_counter == 1
//   // there's only 1 id column
//   // so we can't go any lower either
//   // but there are multiple shapes which need nesting
//   // so need to loop over them and put in a list
//   if( id_counter == 1 ) {
//     // need to subset teh data.frame and send it in to be nested
//     Rcpp::NumericVector group_ids = df[ id_col ];
//     Rcpp::IntegerMatrix line_positions = geometries::utils::id_positions( group_ids );
//     R_xlen_t n_lines = line_positions.nrow();
//
//     Rcpp::List inner_res( n_lines );
//     // need to loop over each line
//     for( i = 0; i < n_lines; ++i ) {
//       int start = line_positions(i, 0);
//       int end = line_positions(i, 1);
//
//       Rcpp::Range rng( start, end );
//       Rcpp::DataFrame df_subset = geometries::utils::subset_dataframe( df, df_names, start, end );
//       inner_res( i ) = df_subset;
//     }
//
//     res[0] = inner_res;
//   }
//
//   while( id_counter > 1 ) {
//     Rcpp::Range idx = Rcpp::seq( 1, id_counter - 1 );
//     Rcpp::StringVector inner_ids =  id_cols[ idx ];  // subset from 1:end
//
//     // need to subset teh data.frame and send it in to be nested
//     Rcpp::NumericVector group_ids = df[ id_col ];
//     Rcpp::IntegerMatrix line_positions = geometries::utils::id_positions( group_ids );
//     R_xlen_t n_lines = line_positions.nrow();
//
//     Rcpp::List inner_res( n_lines );
//     // need to loop over each line
//     for( i = 0; i < n_lines; ++i ) {
//       int start = line_positions(i, 0);
//       int end = line_positions(i, 1);
//
//       Rcpp::Range rng( start, end );
//       Rcpp::DataFrame df_subset = geometries::utils::subset_dataframe( df, df_names, start, end );
//       inner_res( i ) = nest3( df_subset, inner_ids, depth );
//     }
//
//     res[0] = inner_res;
//     id_counter--;
//   }
//
//   return res;
//   // res[0] = nest3( df, inner_ids, depth );
//
//
// }


// // [[Rcpp::export]]
// SEXP rcpp_nest2( Rcpp::DataFrame df, Rcpp::StringVector id_cols, int depth ) {
//   return nest3( df, id_cols, depth );
// }

#include "geometries/utils/rleid/rleid.hpp"

// [[Rcpp::export]]
Rcpp::IntegerVector rcpp_rleid( Rcpp::DataFrame df, Rcpp::IntegerVector ids ) {
  return geometries::utils::rleid( df, ids );
}


// [[Rcpp::export]]
SEXP rcpp_nest( SEXP x, int depth ) {

  // Need to know the depth of the current item, in order to know how deep to go
  Rcpp::List dimension = geometries::coordinates::geometry_dimensions( x );
  int current_depth = dimension["max_nest"];

  if( current_depth == depth ) {
    // already at the right depth
    return x;
  }

  if( current_depth > depth ) {
    // need to unnest
    int unnest_depth = current_depth - depth;
    return geometries::shapes::unnest( x, unnest_depth );
  }

  int nest_depth = depth - current_depth;
  return geometries::shapes::nest( x, nest_depth );
  // if current_depth > depth, need to unnest
  // if current_dept < depth, need to nest further
}








