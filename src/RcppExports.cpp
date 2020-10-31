// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// rcpp_calculate_bbox
SEXP rcpp_calculate_bbox(SEXP x, SEXP geometry_cols);
RcppExport SEXP _geometries_rcpp_calculate_bbox(SEXP xSEXP, SEXP geometry_colsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type x(xSEXP);
    Rcpp::traits::input_parameter< SEXP >::type geometry_cols(geometry_colsSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_calculate_bbox(x, geometry_cols));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_close_matrix
SEXP rcpp_close_matrix(Rcpp::List x);
RcppExport SEXP _geometries_rcpp_close_matrix(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::List >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_close_matrix(x));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_other_columns
SEXP rcpp_other_columns(SEXP x, SEXP id_cols, SEXP id_col2, SEXP id_col3);
RcppExport SEXP _geometries_rcpp_other_columns(SEXP xSEXP, SEXP id_colsSEXP, SEXP id_col2SEXP, SEXP id_col3SEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type x(xSEXP);
    Rcpp::traits::input_parameter< SEXP >::type id_cols(id_colsSEXP);
    Rcpp::traits::input_parameter< SEXP >::type id_col2(id_col2SEXP);
    Rcpp::traits::input_parameter< SEXP >::type id_col3(id_col3SEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_other_columns(x, id_cols, id_col2, id_col3));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_column_positions
SEXP rcpp_column_positions(SEXP x, SEXP cols);
RcppExport SEXP _geometries_rcpp_column_positions(SEXP xSEXP, SEXP colsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type x(xSEXP);
    Rcpp::traits::input_parameter< SEXP >::type cols(colsSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_column_positions(x, cols));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_geometry_dimensions
SEXP rcpp_geometry_dimensions(SEXP geometries);
RcppExport SEXP _geometries_rcpp_geometry_dimensions(SEXP geometriesSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type geometries(geometriesSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_geometry_dimensions(geometries));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_coordinates
SEXP rcpp_coordinates(SEXP& geometries);
RcppExport SEXP _geometries_rcpp_coordinates(SEXP geometriesSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP& >::type geometries(geometriesSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_coordinates(geometries));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_make_geometries
SEXP rcpp_make_geometries(SEXP x, SEXP id_cols, SEXP geometry_cols, Rcpp::List attributes, bool close);
RcppExport SEXP _geometries_rcpp_make_geometries(SEXP xSEXP, SEXP id_colsSEXP, SEXP geometry_colsSEXP, SEXP attributesSEXP, SEXP closeSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type x(xSEXP);
    Rcpp::traits::input_parameter< SEXP >::type id_cols(id_colsSEXP);
    Rcpp::traits::input_parameter< SEXP >::type geometry_cols(geometry_colsSEXP);
    Rcpp::traits::input_parameter< Rcpp::List >::type attributes(attributesSEXP);
    Rcpp::traits::input_parameter< bool >::type close(closeSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_make_geometries(x, id_cols, geometry_cols, attributes, close));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_id_positions
SEXP rcpp_id_positions(SEXP x, SEXP i);
RcppExport SEXP _geometries_rcpp_id_positions(SEXP xSEXP, SEXP iSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type x(xSEXP);
    Rcpp::traits::input_parameter< SEXP >::type i(iSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_id_positions(x, i));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_rleid
Rcpp::IntegerVector rcpp_rleid(Rcpp::DataFrame df, Rcpp::IntegerVector ids);
RcppExport SEXP _geometries_rcpp_rleid(SEXP dfSEXP, SEXP idsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::DataFrame >::type df(dfSEXP);
    Rcpp::traits::input_parameter< Rcpp::IntegerVector >::type ids(idsSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_rleid(df, ids));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_rleid_indices
Rcpp::IntegerVector rcpp_rleid_indices(SEXP x);
RcppExport SEXP _geometries_rcpp_rleid_indices(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_rleid_indices(x));
    return rcpp_result_gen;
END_RCPP
}
// test_attributes
void test_attributes(SEXP& obj, Rcpp::List& attributes);
RcppExport SEXP _geometries_test_attributes(SEXP objSEXP, SEXP attributesSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP& >::type obj(objSEXP);
    Rcpp::traits::input_parameter< Rcpp::List& >::type attributes(attributesSEXP);
    test_attributes(obj, attributes);
    return R_NilValue;
END_RCPP
}
// test_to_geometry_matrix_cols
SEXP test_to_geometry_matrix_cols(SEXP x, SEXP cols);
RcppExport SEXP _geometries_test_to_geometry_matrix_cols(SEXP xSEXP, SEXP colsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type x(xSEXP);
    Rcpp::traits::input_parameter< SEXP >::type cols(colsSEXP);
    rcpp_result_gen = Rcpp::wrap(test_to_geometry_matrix_cols(x, cols));
    return rcpp_result_gen;
END_RCPP
}
// test_to_geometry_matrix_cols_names
SEXP test_to_geometry_matrix_cols_names(Rcpp::DataFrame x, Rcpp::IntegerVector cols, bool keep_names);
RcppExport SEXP _geometries_test_to_geometry_matrix_cols_names(SEXP xSEXP, SEXP colsSEXP, SEXP keep_namesSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::DataFrame >::type x(xSEXP);
    Rcpp::traits::input_parameter< Rcpp::IntegerVector >::type cols(colsSEXP);
    Rcpp::traits::input_parameter< bool >::type keep_names(keep_namesSEXP);
    rcpp_result_gen = Rcpp::wrap(test_to_geometry_matrix_cols_names(x, cols, keep_names));
    return rcpp_result_gen;
END_RCPP
}
// test_to_geometry_matrix_single
SEXP test_to_geometry_matrix_single(SEXP x);
RcppExport SEXP _geometries_test_to_geometry_matrix_single(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(test_to_geometry_matrix_single(x));
    return rcpp_result_gen;
END_RCPP
}
// tm
SEXP tm(SEXP x);
RcppExport SEXP _geometries_tm(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(tm(x));
    return rcpp_result_gen;
END_RCPP
}
// test_sexp_col_int
Rcpp::IntegerVector test_sexp_col_int(SEXP x, SEXP v);
RcppExport SEXP _geometries_test_sexp_col_int(SEXP xSEXP, SEXP vSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type x(xSEXP);
    Rcpp::traits::input_parameter< SEXP >::type v(vSEXP);
    rcpp_result_gen = Rcpp::wrap(test_sexp_col_int(x, v));
    return rcpp_result_gen;
END_RCPP
}
// test_sexp_col_names
Rcpp::StringVector test_sexp_col_names(SEXP x);
RcppExport SEXP _geometries_test_sexp_col_names(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(test_sexp_col_names(x));
    return rcpp_result_gen;
END_RCPP
}
// test_sexp_n_col
R_xlen_t test_sexp_n_col(SEXP x);
RcppExport SEXP _geometries_test_sexp_n_col(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(test_sexp_n_col(x));
    return rcpp_result_gen;
END_RCPP
}
// test_sexp_n_row
R_xlen_t test_sexp_n_row(SEXP x);
RcppExport SEXP _geometries_test_sexp_n_row(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(test_sexp_n_row(x));
    return rcpp_result_gen;
END_RCPP
}
// test_sexp_length
R_xlen_t test_sexp_length(SEXP x);
RcppExport SEXP _geometries_test_sexp_length(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(test_sexp_length(x));
    return rcpp_result_gen;
END_RCPP
}
// test_column_check
void test_column_check(SEXP x, SEXP cols);
RcppExport SEXP _geometries_test_column_check(SEXP xSEXP, SEXP colsSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type x(xSEXP);
    Rcpp::traits::input_parameter< SEXP >::type cols(colsSEXP);
    test_column_check(x, cols);
    return R_NilValue;
END_RCPP
}
// test_other_columns_impl
SEXP test_other_columns_impl();
RcppExport SEXP _geometries_test_other_columns_impl() {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    rcpp_result_gen = Rcpp::wrap(test_other_columns_impl());
    return rcpp_result_gen;
END_RCPP
}
// test_other_columns
SEXP test_other_columns(SEXP x, SEXP y, SEXP z);
RcppExport SEXP _geometries_test_other_columns(SEXP xSEXP, SEXP ySEXP, SEXP zSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type x(xSEXP);
    Rcpp::traits::input_parameter< SEXP >::type y(ySEXP);
    Rcpp::traits::input_parameter< SEXP >::type z(zSEXP);
    rcpp_result_gen = Rcpp::wrap(test_other_columns(x, y, z));
    return rcpp_result_gen;
END_RCPP
}
// test_column_positions
SEXP test_column_positions(SEXP x, SEXP cols);
RcppExport SEXP _geometries_test_column_positions(SEXP xSEXP, SEXP colsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type x(xSEXP);
    Rcpp::traits::input_parameter< SEXP >::type cols(colsSEXP);
    rcpp_result_gen = Rcpp::wrap(test_column_positions(x, cols));
    return rcpp_result_gen;
END_RCPP
}
// test_make_dataframe
SEXP test_make_dataframe(Rcpp::List lst, R_xlen_t n_rows, Rcpp::CharacterVector col_names);
RcppExport SEXP _geometries_test_make_dataframe(SEXP lstSEXP, SEXP n_rowsSEXP, SEXP col_namesSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::List >::type lst(lstSEXP);
    Rcpp::traits::input_parameter< R_xlen_t >::type n_rows(n_rowsSEXP);
    Rcpp::traits::input_parameter< Rcpp::CharacterVector >::type col_names(col_namesSEXP);
    rcpp_result_gen = Rcpp::wrap(test_make_dataframe(lst, n_rows, col_names));
    return rcpp_result_gen;
END_RCPP
}
// test_unique_ids
SEXP test_unique_ids(SEXP x, SEXP id_col);
RcppExport SEXP _geometries_test_unique_ids(SEXP xSEXP, SEXP id_colSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type x(xSEXP);
    Rcpp::traits::input_parameter< SEXP >::type id_col(id_colSEXP);
    rcpp_result_gen = Rcpp::wrap(test_unique_ids(x, id_col));
    return rcpp_result_gen;
END_RCPP
}
// test_unique_sort
SEXP test_unique_sort(SEXP x);
RcppExport SEXP _geometries_test_unique_sort(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(test_unique_sort(x));
    return rcpp_result_gen;
END_RCPP
}
// test_as_list
SEXP test_as_list(SEXP x);
RcppExport SEXP _geometries_test_as_list(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(test_as_list(x));
    return rcpp_result_gen;
END_RCPP
}
// tests
SEXP tests();
RcppExport SEXP _geometries_tests() {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    rcpp_result_gen = Rcpp::wrap(tests());
    return rcpp_result_gen;
END_RCPP
}
// rcpp_concatenate_vectors
SEXP rcpp_concatenate_vectors(SEXP vec_1, SEXP vec_2);
RcppExport SEXP _geometries_rcpp_concatenate_vectors(SEXP vec_1SEXP, SEXP vec_2SEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type vec_1(vec_1SEXP);
    Rcpp::traits::input_parameter< SEXP >::type vec_2(vec_2SEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_concatenate_vectors(vec_1, vec_2));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_where_is
int rcpp_where_is(Rcpp::String to_find, Rcpp::StringVector sv);
RcppExport SEXP _geometries_rcpp_where_is(SEXP to_findSEXP, SEXP svSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::String >::type to_find(to_findSEXP);
    Rcpp::traits::input_parameter< Rcpp::StringVector >::type sv(svSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_where_is(to_find, sv));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_get_ids
SEXP rcpp_get_ids(SEXP x, SEXP id_col);
RcppExport SEXP _geometries_rcpp_get_ids(SEXP xSEXP, SEXP id_colSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type x(xSEXP);
    Rcpp::traits::input_parameter< SEXP >::type id_col(id_colSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_get_ids(x, id_col));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_geometries_rcpp_calculate_bbox", (DL_FUNC) &_geometries_rcpp_calculate_bbox, 2},
    {"_geometries_rcpp_close_matrix", (DL_FUNC) &_geometries_rcpp_close_matrix, 1},
    {"_geometries_rcpp_other_columns", (DL_FUNC) &_geometries_rcpp_other_columns, 4},
    {"_geometries_rcpp_column_positions", (DL_FUNC) &_geometries_rcpp_column_positions, 2},
    {"_geometries_rcpp_geometry_dimensions", (DL_FUNC) &_geometries_rcpp_geometry_dimensions, 1},
    {"_geometries_rcpp_coordinates", (DL_FUNC) &_geometries_rcpp_coordinates, 1},
    {"_geometries_rcpp_make_geometries", (DL_FUNC) &_geometries_rcpp_make_geometries, 5},
    {"_geometries_rcpp_id_positions", (DL_FUNC) &_geometries_rcpp_id_positions, 2},
    {"_geometries_rcpp_rleid", (DL_FUNC) &_geometries_rcpp_rleid, 2},
    {"_geometries_rcpp_rleid_indices", (DL_FUNC) &_geometries_rcpp_rleid_indices, 1},
    {"_geometries_test_attributes", (DL_FUNC) &_geometries_test_attributes, 2},
    {"_geometries_test_to_geometry_matrix_cols", (DL_FUNC) &_geometries_test_to_geometry_matrix_cols, 2},
    {"_geometries_test_to_geometry_matrix_cols_names", (DL_FUNC) &_geometries_test_to_geometry_matrix_cols_names, 3},
    {"_geometries_test_to_geometry_matrix_single", (DL_FUNC) &_geometries_test_to_geometry_matrix_single, 1},
    {"_geometries_tm", (DL_FUNC) &_geometries_tm, 1},
    {"_geometries_test_sexp_col_int", (DL_FUNC) &_geometries_test_sexp_col_int, 2},
    {"_geometries_test_sexp_col_names", (DL_FUNC) &_geometries_test_sexp_col_names, 1},
    {"_geometries_test_sexp_n_col", (DL_FUNC) &_geometries_test_sexp_n_col, 1},
    {"_geometries_test_sexp_n_row", (DL_FUNC) &_geometries_test_sexp_n_row, 1},
    {"_geometries_test_sexp_length", (DL_FUNC) &_geometries_test_sexp_length, 1},
    {"_geometries_test_column_check", (DL_FUNC) &_geometries_test_column_check, 2},
    {"_geometries_test_other_columns_impl", (DL_FUNC) &_geometries_test_other_columns_impl, 0},
    {"_geometries_test_other_columns", (DL_FUNC) &_geometries_test_other_columns, 3},
    {"_geometries_test_column_positions", (DL_FUNC) &_geometries_test_column_positions, 2},
    {"_geometries_test_make_dataframe", (DL_FUNC) &_geometries_test_make_dataframe, 3},
    {"_geometries_test_unique_ids", (DL_FUNC) &_geometries_test_unique_ids, 2},
    {"_geometries_test_unique_sort", (DL_FUNC) &_geometries_test_unique_sort, 1},
    {"_geometries_test_as_list", (DL_FUNC) &_geometries_test_as_list, 1},
    {"_geometries_tests", (DL_FUNC) &_geometries_tests, 0},
    {"_geometries_rcpp_concatenate_vectors", (DL_FUNC) &_geometries_rcpp_concatenate_vectors, 2},
    {"_geometries_rcpp_where_is", (DL_FUNC) &_geometries_rcpp_where_is, 2},
    {"_geometries_rcpp_get_ids", (DL_FUNC) &_geometries_rcpp_get_ids, 2},
    {NULL, NULL, 0}
};

RcppExport void R_init_geometries(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
