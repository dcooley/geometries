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




// [[Rcpp::export]]
SEXP rcpp_rleid( Rcpp::DataFrame l, Rcpp::IntegerVector ids, Rcpp::IntegerVector geometry_cols, bool last ) {

  // TODO:
  // - Convert the geometry columns into a matrix
  // - subset matrix rather than subset_df
  // -

  // reference: data.table
  // https://github.com/Rdatatable/data.table/blob/8b93bb22715b45d38acf185f40d573bda8748cb4/src/uniqlist.c#L164

  Rcpp::StringVector df_names = l.names();

  Rcpp::NumericMatrix nm = geometries::shapes::to_mat( l, geometry_cols );

  //Rcpp::Rcout << "mat: " << nm << std::endl;

  R_xlen_t i;
  R_xlen_t n_rows = l.nrow(); //geometries::utils::sexp_n_row( l );
  //R_xlen_t n_cols = Rf_length( l );
  R_xlen_t n_id_cols = Rf_length( ids );
  //Rcpp::IntegerVector ians( n_rows );  // I don't actually need to keep the rleid values

  Rcpp::IntegerVector nelems( n_rows );
  Rcpp::IntegerVector sums( n_rows );

  //int grp = 1;

  // values for keeping track of the indexes of 'l' (rows) which form the individual geometries;
  int start = 0;
  int end = 0;
  Rcpp::List res( n_rows ); // arbitrarily start it at the max possible?
  R_xlen_t res_counter = 0;
  R_xlen_t n_elements = 1;
  R_xlen_t cumulative_size = 0;

  for( i = 1; i < n_rows; ++i ) {
    bool same = true;
    int j = n_id_cols;
    while( --j >= 0 && same ) {
      SEXP jcol = VECTOR_ELT( l, ids[ j ] );
      switch( TYPEOF( jcol ) ) {
        case LGLSXP: {}
        case INTSXP: {
          same = INTEGER( jcol )[ i ] == INTEGER( jcol )[ i - 1 ];
          break;
        }
        case REALSXP: {
          long long *ll = (long long *)REAL( jcol );
          same = ll[ i ] == ll[ i - 1 ];
          break;
        }
        case STRSXP: {
          same = STRING_ELT( jcol, i ) == STRING_ELT( jcol, i - 1 );
          break;
        }
        default: {
          Rcpp::stop("geometries - unsupported id column type");
        }
      }
    }  // while end

    // at this point we now have a run-length-encoded vector
    //ians[ i ] = ( grp += !same );
    n_elements += same;
    // at the point where same == 0 we have a new rleid

    if( !same ) {

      nelems[ res_counter ] = n_elements;

      cumulative_size = n_elements + cumulative_size;

      sums[ res_counter ] = cumulative_size;
      n_elements = 1;

      if( last ) {
        end = i - 1;

        // Rcpp::List subset_df = geometries::utils::subset_dataframe( l, df_names, start, end );
        // res[ res_counter ] = subset_df;

        Rcpp::Range row_rng( start, end );

        // Rcpp::Rcout << "row_rng: " << start << " - " << end << std::endl;
        Rcpp::NumericMatrix res_mat = nm( row_rng, Rcpp::_ );
        // Rcpp::Rcout << "res_mat: " << res_mat << std::endl;

        res[ res_counter ] = res_mat;

        start = i;
      }
      res_counter++;
    }
  }

  nelems[ res_counter ] = n_elements;

  cumulative_size = n_elements + cumulative_size;
  sums[ res_counter ] = cumulative_size;

  Rcpp::Range rng( 0, res_counter );

  if( last ) {
    end = i - 1;

    // Rcpp::List subset_df = geometries::utils::subset_dataframe( l, df_names, start, end );
    // res[ res_counter ] = subset_df;

    Rcpp::Range row_rng( start, end );

    Rcpp::Rcout << "row_rng: " << start << " - " << end << std::endl;
    Rcpp::NumericMatrix res_mat = nm( row_rng, Rcpp::_ );
    Rcpp::Rcout << "res_mat: " << res_mat << std::endl;

    res[ res_counter ] = res_mat;

    // we can remove any res elements AFTER res_counter
    // because by this point we've filled everything
    //Rcpp::Range coord_rng( 0, res_counter );

    return Rcpp::List::create(
      Rcpp::_["nelems"] = nelems[ rng ],
      Rcpp::_["sums"] = sums[ rng ],
      Rcpp::_["coords"] = res
    );
  }

  return Rcpp::List::create(
    Rcpp::_["nelems"] = nelems[ rng ],
    Rcpp::_["sums"] = sums[ rng ]
  );

}

// [[Rcpp::export]]
SEXP rcpp_nested_rleid( Rcpp::DataFrame l, Rcpp::IntegerVector ids, Rcpp::IntegerVector geometry_cols ) {

  R_xlen_t i, j, k;
  //R_xlen_t n_rows = l.nrow(); //geometries::utils::sexp_n_row( l );
  //R_xlen_t n_cols = Rf_length( l );
  R_xlen_t n_id_cols = Rf_length( ids );

  Rcpp::List rleid( n_id_cols );

  for( i = n_id_cols - 1; i >= 0; --i ) {

    Rcpp::Range rng(0, i);
    Rcpp::IntegerVector rle_ids = ids[ rng ];

    bool last = i == n_id_cols - 1;
    rleid( i ) = rcpp_rleid( l, rle_ids, geometry_cols, last );

    // here the rleid(i) tells us which elements of rleid(i+1)
    // belong in which "package"
    Rcpp::List curr = rleid( i );
    Rcpp::IntegerVector nelems = curr["nelems"];
    Rcpp::IntegerVector curr_sums = curr["sums"];

    if( !last ) {
      Rcpp::List prev = rleid( i + 1 );
      Rcpp::IntegerVector prev_sums = prev["sums"];
      Rcpp::List prev_res = prev["res"];

      Rcpp::List curr_res( nelems.size() );
      R_xlen_t prev_idx = 0;
      R_xlen_t out_size;

      for( j = 0; j < nelems.size(); ++j ) {
        R_xlen_t curr_sum = curr_sums[ j ];
        R_xlen_t start_prev_idx = prev_idx;
        R_xlen_t prev_sum = prev_sums[ prev_idx ];
        out_size = 1;

        while( prev_sum != curr_sum ) { // prev_sum will always start <= to curr_sum
          prev_idx++;
          out_size++;
          prev_sum = prev_sums[ prev_idx ];
        }
        prev_idx++;

        //Rcpp::List inner_list( out_size );

        // and fill?
        // Rcpp::Rcout << "fill with previous list from " << start_prev_idx << ", to " << prev_idx - 1 << std::endl;
        // Rcpp::Rcout << "prev_res size: " << prev_res.size() << std::endl;
        // R_xlen_t idx = prev_idx - 1;
        // for( k = 0; k < out_size; ++k ) {
        //   Rcpp::List inner_coords = prev_res[ start_prev_idx + k ];
        //   inner_list[ k ] = inner_coords;
        //   idx++;
        // }
        //curr_res( j ) = inner_list;

        Rcpp::Range inner_rng( start_prev_idx, prev_idx - 1);
        curr_res( j ) = prev_res[ inner_rng ];

      }
      rleid( i ) = Rcpp::List::create(
        Rcpp::_["nelems"] = nelems,
        Rcpp::_["sums"] = curr_sums,
        Rcpp::_["res"] = curr_res
      );
    } else {
      // need to fill with the coordinates inside ["coords"]
      // it gets here first, because it works from the inside out

      SEXP coords = curr["coords"];

      rleid( i ) = Rcpp::List::create(
        Rcpp::_["nelems"] = nelems,
        Rcpp::_["sums"] = curr_sums,
        Rcpp::_["res"] = coords
      );
    }
  }

  //return rleid;
  Rcpp::List out = rleid[0];
  return out["res"];
}

// need to know how many unique elements are in the id-column to the right...
// so do the rleid from right-to-left
// and return the rleid, plus another vector giving the number of unique elements for each group

// // this is basically the rleid()
// // [[Rcpp::export]]
// Rcpp::IntegerMatrix id_positions( Rcpp::IntegerVector ids ) {
//   R_xlen_t n = ids.length();
//   if( n == 0 ) {
//     Rcpp::stop("geometries - not enough id values");
//   }
//   R_xlen_t i;
//   Rcpp::IntegerMatrix res( Rcpp::no_init( n, 2 ) ); // start with n-rows, then filter the rows based on number of id values
//
//   // set up the first one
//   int current_id = ids[ 0 ];
//   R_xlen_t n_ids = 0;  // keeps count of the number of different IDs.
//   res( 0, 0 ) = 0;
//   R_xlen_t counter = 0;
//   for( i = 1; i < n; ++i ) {
//     int this_id = ids[ i ];
//     if( this_id != current_id ) {
//       res( counter, 1 ) = i;
//       counter++;
//       res( counter, 0 ) = i + 1;
//       current_id = this_id;
//     }
//   }
//   // we can now remove the non-used rows
//   Rcpp::IntegerMatrix indices = res( Rcpp::Range(0, counter - 1 ), Rcpp::_ );
//
// }



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








