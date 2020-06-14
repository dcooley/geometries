#include <Rcpp.h>

#include "geometries/shapes/shapes.hpp"

#include "geometries/coordinates/dimensions.hpp"

// POINTS -----------
// [[Rcpp::export]]
SEXP rcpp_get_vec(
    SEXP x,
    SEXP cols
) {
  return geometries::shapes::to_vec( x, cols );
}

// LINE ----------
// [[Rcpp::export]]
SEXP rcpp_to_mat(
    SEXP x,
    SEXP cols
) {
  return geometries::shapes::to_mat( x, cols );
}

// LINES -----------
// [[Rcpp::export]]
SEXP rcpp_get_list_mat(
    SEXP x,
    SEXP cols,
    SEXP id
) {
  return geometries::shapes::to_listMat( x, cols, id );
}


// // [[Rcpp::export]]
// SEXP rcpp_from_listMat( Rcpp::List lst ) {
//   R_xlen_t geometry_rows = 0;
//   return geometries::shapes::from_listMat< REALSXP >( lst, geometry_rows );
// }



SEXP unnest( SEXP x, int depth ) {
  // inside this function the dimension of x shoudl already be known
  // And it will only work on nested list objects
  if( !Rf_isNewList( x ) ) {
    Rcpp::stop("geometries - can only unnest list objects");
  }

  Rcpp::List lst = Rcpp::as< Rcpp::List >( x );
  if( lst.length() != 1 ) {
    Rcpp::stop("geometries - error trying to unnest the object");
  }
  SEXP res = lst[0];

  // depth will be a positive number
  // because it's the depth we need to get to, so can only be positive (or 0)
  while( depth > 1 ) {
    return unnest( res, depth - 1 );
    depth--;
  }
  return res;
}


#include "geometries/utils/dataframe/dataframe.hpp"

// Nest to accept a vector of ids
// if id.length() == depth
// then subset & for-loop over the ids
// and run nest() on the inner objects (with one less id column)


SEXP nest2(
    Rcpp::DataFrame& df,
    Rcpp::StringVector& id_cols,
    int depth
) {
  if( depth < 1  ) {
    Rcpp::Rcout << "returning < 1 " << std::endl;
    return df;
  }

  // using 'int' because I don't think nesting would every likley go more than 4/5 elements

  int i, j;
  int n_ids = id_cols.length();

  Rcpp::StringVector inner_ids;

  if( n_ids > 1 ) {
    Rcpp::Range idx = Rcpp::seq( 1, n_ids - 1 );
    inner_ids =  id_cols[ idx ];  // subset from 1:end
  }

  Rcpp::Rcout << "n_ids: " << n_ids << std::endl;
  Rcpp::Rcout << "depth: " << depth << std::endl;
  Rcpp::Rcout << "inner_ids: " << inner_ids << std::endl;

  if( n_ids > depth ) {
    // stop - can't do this
    Rcpp::stop("geometries - too many id columns supplied for the level of nesting required");
  }

  Rcpp::List res(1);
  // TODO
  // - when depth > n_ids
  // - need to enter a while loop of nesting
  if( depth > n_ids ) {

    res[0] = nest2( df, id_cols, depth - 1 );

  } else if ( n_ids == depth ) {

    for( j = 0; j < n_ids; ++j ) {
      Rcpp::Rcout << "j: " << j << std::endl;
      Rcpp::Rcout << "id_cols: " << id_cols << std::endl;
      Rcpp::String id_col = id_cols[ j ];
      Rcpp::Rcout << "id_col: " << id_col.get_cstring() << std::endl;
      Rcpp::NumericVector group_ids = df[ id_col ];

      Rcpp::Rcout << "group_ids: " << group_ids << std::endl;

      Rcpp::IntegerMatrix line_positions = geometries::utils::id_positions( group_ids );
      Rcpp::Rcout << "line_positions: " << std::endl;
      Rcpp::Rcout << line_positions << std::endl;

      R_xlen_t n_lines = line_positions.nrow();
      Rcpp::Rcout << "n_lines: " << n_lines << std::endl;

      Rcpp::List inner_res( n_lines );
      Rcpp::StringVector df_names = df.names();

      for( i = 0; i < n_lines; ++i ) {

        int start = line_positions(i, 0);
        int end = line_positions(i, 1);

        Rcpp::Range rng( start, end );
        Rcpp::DataFrame df_subset = geometries::utils::subset_dataframe( df, df_names, start, end );

        int inner_depth = depth;

        while( inner_depth > 0 ) {
          inner_res[i] = nest2( df_subset, inner_ids, inner_depth - 1 );
          inner_depth--;
        }
      }
      res[0] = inner_res;
      //return inner_res;
    }
  }

  return res;
  //return mpl;
}


// while n_id_columns > 1
// - get next id column
// - get line positions
// - subset df
// - depth--;
// if n_id_columns == 1
// - loop line_positions.nrow();
// -- Rcpp::List res( n_row );
// -- res[ i ] = subset_df();
// - return res;
//

SEXP nest3( Rcpp::DataFrame df, Rcpp::StringVector id_cols, int depth ) {
  int id_counter = id_cols.length();

  Rcpp::StringVector df_names = df.names();

  R_xlen_t i;

  Rcpp::List res(1);

  // if id_counter == 0;
  // there are no id columns
  if( id_counter == 0 ) {
    // no more ids, so we're at the lowest-level object
    res[0] = df;
  }

  Rcpp::String id_col = id_cols[0];

  // iff id_counter == 1
  // there's only 1 id column
  // so we can't go any lower either
  // but there are multiple shapes which need nesting
  // so need to loop over them and put in a list
  if( id_counter == 1 ) {
    // need to subset teh data.frame and send it in to be nested
    Rcpp::NumericVector group_ids = df[ id_col ];
    Rcpp::IntegerMatrix line_positions = geometries::utils::id_positions( group_ids );
    R_xlen_t n_lines = line_positions.nrow();

    Rcpp::List inner_res( n_lines );
    // need to loop over each line
    for( i = 0; i < n_lines; ++i ) {
      int start = line_positions(i, 0);
      int end = line_positions(i, 1);

      Rcpp::Range rng( start, end );
      Rcpp::DataFrame df_subset = geometries::utils::subset_dataframe( df, df_names, start, end );
      inner_res( i ) = df_subset;
    }

    res[0] = inner_res;
  }

  while( id_counter > 1 ) {
    Rcpp::Range idx = Rcpp::seq( 1, id_counter - 1 );
    Rcpp::StringVector inner_ids =  id_cols[ idx ];  // subset from 1:end

    // need to subset teh data.frame and send it in to be nested
    Rcpp::NumericVector group_ids = df[ id_col ];
    Rcpp::IntegerMatrix line_positions = geometries::utils::id_positions( group_ids );
    R_xlen_t n_lines = line_positions.nrow();

    Rcpp::List inner_res( n_lines );
    // need to loop over each line
    for( i = 0; i < n_lines; ++i ) {
      int start = line_positions(i, 0);
      int end = line_positions(i, 1);

      Rcpp::Range rng( start, end );
      Rcpp::DataFrame df_subset = geometries::utils::subset_dataframe( df, df_names, start, end );
      inner_res( i ) = nest3( df_subset, inner_ids, depth );
    }

    res[0] = inner_res;
    id_counter--;
  }

  return res;
  // res[0] = nest3( df, inner_ids, depth );


}


// [[Rcpp::export]]
SEXP rcpp_nest2( Rcpp::DataFrame df, Rcpp::StringVector id_cols, int depth ) {
  return nest3( df, id_cols, depth );
}

SEXP nest( SEXP x, int depth ) {
  if( depth < 1 ) {
    return x;
  }

  Rcpp::List res(1);
  res[0] = x;   // first level
  //depth = depth - 1;
  while( depth > 0 ) {
    return nest( res, depth - 1 );
    depth--;
  }
  return res;
}

// [[Rcpp::export]]
SEXP rcpp_nest( SEXP x, int depth ) {
  // extract each inner-list element
  // designed to work on nested lists

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
    return unnest( x, unnest_depth );
  }

  int nest_depth = depth - current_depth;
  return nest( x, nest_depth );
  // if current_depth > depth, need to unnest
  // if current_dept < depth, need to nest further
}








