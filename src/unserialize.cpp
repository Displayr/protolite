// [[Rcpp::interfaces(r, cpp)]]

#include "rexp.pb.h"
#include <Rcpp.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <limits>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include <google/protobuf/io/coded_stream.h>
using namespace google::protobuf;

Rcpp::NumericVector unrexp_real(rexp::REXP message){
  int len = message.realvalue_size();
  Rcpp::NumericVector out(len);
  for(int i = 0; i < len; i++)
    out[i] = message.realvalue(i);
  return out;
}

Rcpp::IntegerVector unrexp_int(rexp::REXP message){
  int len = message.intvalue_size();
  Rcpp::IntegerVector out(len);
  for(int i = 0; i < len; i++)
    out[i] = message.intvalue(i);
  return out;
}

Rcpp::LogicalVector unrexp_bool(rexp::REXP message){
  int len = message.booleanvalue_size();
  Rcpp::LogicalVector out(len);
  for(int i = 0; i < len; i++){
    rexp::REXP_RBOOLEAN val = message.booleanvalue(i);
    out[i] = (val == rexp::REXP_RBOOLEAN_NA) ? NA_LOGICAL : val;
  }
  return out;
}

Rcpp::StringVector unrexp_string(rexp::REXP message){
  int len = message.stringvalue_size();
  Rcpp::StringVector out(len);
  for(int i = 0; i < len; i++){
    rexp::STRING val = message.stringvalue(i);
    if(val.isna()){
      out[i] = NA_STRING;
    } else {
      Rcpp::String str(val.strval());
      str.set_encoding(CE_UTF8);
      out[i] = str;
    }
  }
  return out;
}

Rcpp::RawVector unrexp_raw(rexp::REXP message){
  std::string val = message.rawvalue();
  Rcpp::RawVector out(val.length());
  val.copy((char*) out.begin(), val.length());
  return out;
}

Rcpp::ComplexVector unrexp_complex(rexp::REXP message){
  int len = message.complexvalue_size();
  Rcpp::ComplexVector out(len);
  for(int i = 0; i < len; i++){
    rexp::CMPLX val = message.complexvalue(i);
    out[i].r = val.real();
    out[i].i = val.imag();
  }
  return out;
}

Rcpp::RObject unrexp_native(rexp::REXP message){
  if(!message.has_nativevalue())
    return R_NilValue;
  std::string val = message.nativevalue();
  Rcpp::RawVector buf(val.length());
  val.copy((char*) buf.begin(), val.length());
  Rcpp::Function unserialize = Rcpp::Environment::namespace_env("base")["unserialize"];
  return unserialize(buf);
}

bool is_invalid_class_assignment(Rcpp::RObject object, Rcpp::RObject val) {
  bool isfactor = false;
  for(int i=0; i < LENGTH(val); i++)
    if(!strcmp(CHAR(STRING_ELT(val, i)), "factor"))
      isfactor = true;

  if(isfactor && object.sexp_type() != INTSXP) {
    Rcpp::warning("ignoring invalid assignment of class 'factor'");
    return true;
  }

  return false;
}

Rcpp::RObject unrexp_object(rexp::REXP message);
Rcpp::List unrexp_list(rexp::REXP message){
  int len = message.rexpvalue_size();
  Rcpp::List out(len);
  for(int i = 0; i < len; i++){
    rexp::REXP obj = message.rexpvalue(i);
    out[i] = unrexp_object(obj);
  }
  return out;
}

Rcpp::RObject unrexp_any(rexp::REXP message){
  rexp::REXP_RClass type = message.rclass();
  switch(type){
    case rexp::REXP_RClass_NULLTYPE: return R_NilValue;
    case rexp::REXP_RClass_REAL: return unrexp_real(message);
    case rexp::REXP_RClass_INTEGER : return unrexp_int(message);
    case rexp::REXP_RClass_LOGICAL: return unrexp_bool(message);
    case rexp::REXP_RClass_STRING: return unrexp_string(message);
    case rexp::REXP_RClass_RAW: return unrexp_raw(message);
    case rexp::REXP_RClass_COMPLEX: return unrexp_complex(message);
    case rexp::REXP_RClass_NATIVE: return unrexp_native(message);
    case rexp::REXP_RClass_LIST: return unrexp_list(message);
    default: throw std::runtime_error("Unsupported rclass type");
  }
}

Rcpp::RObject unrexp_object(rexp::REXP message){
  Rcpp::RObject object = unrexp_any(message);
  int len = message.attrname_size();
  if(message.rclass() != rexp::REXP_RClass_NATIVE){
    for(int i = 0; i < len; i++){
      std::string name = message.attrname(i);
      Rcpp::RObject val = unrexp_object(message.attrvalue(i));

      if (name == "class" && is_invalid_class_assignment(object, val))
        break;

      object.attr(name) = val;
    }
  }
  return object;
}

// [[Rcpp::export]]
Rcpp::RObject cpp_unserialize_pb_file(std::string path) {
  rexp::REXP message;
  std::ifstream stream(path);
  if(!message.ParseFromIstream(&stream))
    throw std::runtime_error("Failed to parse protobuf message");
  stream.close();
  return unrexp_object(message);
}

// [[Rcpp::export]]
Rcpp::RObject cpp_unserialize_pb(Rcpp::RawVector x){
  rexp::REXP message;
  // We manually construct our own CodedInputStream because ParseFromArray() would
  // impose the 64MB limit on protobuf streams.  
  io::ArrayInputStream input_stream(x.begin(), x.size());
  io::CodedInputStream coded_stream(&input_stream);
  coded_stream.SetTotalBytesLimit(INT_MAX);
  if(!message.ParseFromCodedStream(&coded_stream))
    throw std::runtime_error("Failed to parse protobuf message");
  return unrexp_object(message);
}
