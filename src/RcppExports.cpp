// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// cpp_serialize_geobuf
RawVector cpp_serialize_geobuf(List x, int decimals);
RcppExport SEXP _protolite_cpp_serialize_geobuf(SEXP xSEXP, SEXP decimalsSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< List >::type x(xSEXP);
    Rcpp::traits::input_parameter< int >::type decimals(decimalsSEXP);
    rcpp_result_gen = Rcpp::wrap(cpp_serialize_geobuf(x, decimals));
    return rcpp_result_gen;
END_RCPP
}
// cpp_serialize_pb
Rcpp::RawVector cpp_serialize_pb(Rcpp::RObject x, bool skip_native);
RcppExport SEXP _protolite_cpp_serialize_pb(SEXP xSEXP, SEXP skip_nativeSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::RObject >::type x(xSEXP);
    Rcpp::traits::input_parameter< bool >::type skip_native(skip_nativeSEXP);
    rcpp_result_gen = Rcpp::wrap(cpp_serialize_pb(x, skip_native));
    return rcpp_result_gen;
END_RCPP
}
// cpp_unserialize_geobuf
List cpp_unserialize_geobuf(Rcpp::RawVector x);
RcppExport SEXP _protolite_cpp_unserialize_geobuf(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::RawVector >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(cpp_unserialize_geobuf(x));
    return rcpp_result_gen;
END_RCPP
}
// cpp_unserialize_pb
Rcpp::RObject cpp_unserialize_pb(Rcpp::RawVector x);
RcppExport SEXP _protolite_cpp_unserialize_pb(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::RawVector >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(cpp_unserialize_pb(x));
    return rcpp_result_gen;
END_RCPP
}
