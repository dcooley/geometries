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
// rcpp_get_vec
SEXP rcpp_get_vec(SEXP x, SEXP cols);
RcppExport SEXP _geometries_rcpp_get_vec(SEXP xSEXP, SEXP colsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type x(xSEXP);
    Rcpp::traits::input_parameter< SEXP >::type cols(colsSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_get_vec(x, cols));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_to_mat
SEXP rcpp_to_mat(SEXP x, SEXP cols);
RcppExport SEXP _geometries_rcpp_to_mat(SEXP xSEXP, SEXP colsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type x(xSEXP);
    Rcpp::traits::input_parameter< SEXP >::type cols(colsSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_to_mat(x, cols));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_get_list_mat
SEXP rcpp_get_list_mat(SEXP x, SEXP cols, SEXP id);
RcppExport SEXP _geometries_rcpp_get_list_mat(SEXP xSEXP, SEXP colsSEXP, SEXP idSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type x(xSEXP);
    Rcpp::traits::input_parameter< SEXP >::type cols(colsSEXP);
    Rcpp::traits::input_parameter< SEXP >::type id(idSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_get_list_mat(x, cols, id));
    return rcpp_result_gen;
END_RCPP
}
// rcpp_coordinates
SEXP rcpp_coordinates(Rcpp::List& sfc);
RcppExport SEXP _geometries_rcpp_coordinates(SEXP sfcSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::List& >::type sfc(sfcSEXP);
    rcpp_result_gen = Rcpp::wrap(rcpp_coordinates(sfc));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_geometries_rcpp_calculate_bbox", (DL_FUNC) &_geometries_rcpp_calculate_bbox, 2},
    {"_geometries_rcpp_get_vec", (DL_FUNC) &_geometries_rcpp_get_vec, 2},
    {"_geometries_rcpp_to_mat", (DL_FUNC) &_geometries_rcpp_to_mat, 2},
    {"_geometries_rcpp_get_list_mat", (DL_FUNC) &_geometries_rcpp_get_list_mat, 3},
    {"_geometries_rcpp_coordinates", (DL_FUNC) &_geometries_rcpp_coordinates, 1},
    {NULL, NULL, 0}
};

RcppExport void R_init_geometries(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
