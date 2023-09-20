// Header for nagcpp::blas::dlange (f06ra)

// Copyright 2023, Numerical Algorithms Group Ltd, Oxford, UK.
// Generated by cpp-ft-wrapper.xsl
// Version 29.2.0.0
#ifndef NAGCPP_F06RA_HPP
#define NAGCPP_F06RA_HPP

#include "utility/nagcpp_consts.hpp"
#include "utility/nagcpp_data_handling.hpp"
#include "utility/nagcpp_engine_routines.hpp"
#include "utility/nagcpp_engine_types.hpp"
#include "utility/nagcpp_error_handler.hpp"
#include "utility/nagcpp_utility_functions.hpp"
#include "utility/nagcpp_utility_optional.hpp"
#include <algorithm>
#include <limits>

namespace nagcpp {
  namespace blas {
    // dlange (f06ra)
    // 1-norm, infinity-norm, Frobenius norm, largest absolute element, real
    // general matrix.
    // blas::dlange (f06ra) returns the value of the 1-norm, the infinity-norm, the
    // Frobenius norm, or the maximum absolute value of the elements of a real m*n
    // matrix.

    // parameters:
    //   norm: std::string, scalar
    //     Specifies the value to be returned
    //   m: types::f77_integer, scalar
    //     m, the number of rows of the matrix A
    //   n: types::f77_integer, scalar
    //     n, the number of columns of the matrix A
    //   a: double, array, shape(m, n)
    //     The m*n matrix A
    //   opt: blas::OptionalF06RA
    //     Optional parameter container, derived from utility::Optional.
    //     contains:
    //       fail: error_handler::ErrorHandler

    // returns: double, scalar
    //   The value of the 1-norm, the infinity-norm, the Frobenius norm, or the
    //   maximum absolute value of the elements of the real m*n matrix

    // error_handler::ErrorException
    //   (errorid 10601)
    //     On entry, argument <value> must be a <value> x <value> array.
    //     Supplied argument has <value> dimensions.
    //   (errorid 10601)
    //     On entry, argument <value> must be a <value> x <value> array.
    //     Supplied argument was a <value> x <value> array.
    //   (errorid 10601)
    //     On entry, argument <value> must be a <value> x <value> array.
    //     Not all of the sizes for the supplied array could be ascertained.
    //   (errorid 10602)
    //     On entry, the raw data component of <value> is null.
    //   (errorid 10603)
    //     On entry, unable to ascertain a value for <value>.
    //   (errorid 10604)
    //     On entry, the data in <value> is stored in <value> Major Order.
    //     The data was expected to be in <value> Major Order.
    //   (errorid -99)
    //     An unexpected error has been triggered by this routine.
    //   (errorid -999)
    //     Dynamic memory allocation failed.
    //   (errorid 1)
    //     On entry, error in parameter norm.
    //     Constraint: norm = "1", "O", "I", "F", "E" or "M".
    //   (errorid 2)
    //     On entry, error in parameter m.
    //     Constraint: m >= 0.
    //   (errorid 3)
    //     On entry, error in parameter n.
    //     Constraint: n >= 0.

    extern "C" {
#if defined(_WIN32) && defined(USE_STDCALL)
#define f06raft_(en_data, norm, m, n, a, lda, nrm, work, norm_length) \
  F06RAFT(en_data, norm, norm_length, m, n, a, lda, nrm, work)
#elif defined(_WIN32) || defined(_WIN64)
#define f06raft_ F06RAFT
#else
#define F06RAFT f06raft_
#endif
    extern void NAG_CALL F06RAFT(types::engine_data &en_data,
                                 const char *norm NAG_STDCALL_LEN(norm_length),
                                 const types::f77_integer &m,
                                 const types::f77_integer &n, const double a[],
                                 const types::f77_integer &lda, double &nrm,
                                 double work[] NAG_NSTDCALL_LEN(norm_length));
    }

    class OptionalF06RA : public utility::Optional {
    public:
      OptionalF06RA() : Optional() {}
      template <typename A>
      friend double dlange(const std::string norm, const A &a,
                           blas::OptionalF06RA &opt);
    };

    template <typename A>
    double dlange(const std::string norm, const A &a,
                  blas::OptionalF06RA &opt) {
      opt.fail.prepare("blas::dlange (f06ra)", false);
      types::engine_data en_data;
      engine_routines::y90haan_(en_data);
      en_data.allocate_workspace = constants::NAG_ED_YES;
      data_handling::RawData<double, data_handling::ArgIntent::IntentIN,
                             typename std::remove_reference<A>::type>
        local_a(a);

      data_handling::StringRawData<data_handling::ArgIntent::IntentIN>
        local_norm(norm);
      types::f77_integer local_m =
        data_handling::get_size(opt.fail, "m", local_a, 1);
      if (opt.fail.error_thrown) {
        return std::numeric_limits<double>::quiet_NaN();
      }
      types::f77_integer local_n =
        data_handling::get_size(opt.fail, "n", local_a, 2);
      if (opt.fail.error_thrown) {
        return std::numeric_limits<double>::quiet_NaN();
      }
      double local_nrm;
      data_handling::RawData<double, data_handling::ArgIntent::IntentOUT>
        local_work(static_cast<types::f77_integer>(0));
      types::f77_integer local_storage_order =
        data_handling::get_storage_order(opt.default_to_col_major, local_a);
      en_data.storage_order = local_storage_order;

      types::f77_integer local_lda =
        std::max(static_cast<types::f77_integer>(1),
                 local_a.get_LD(local_storage_order));
      local_a.check(opt.fail, "a", true, local_storage_order, local_m, local_n);
      if (opt.fail.error_thrown) {
        return std::numeric_limits<double>::quiet_NaN();
      }

      if (!((utility::streq(norm, "1", 1) || utility::streq(norm, "O", 1) ||
             utility::streq(norm, "I", 1) || utility::streq(norm, "F", 1) ||
             utility::streq(norm, "E", 1) || utility::streq(norm, "M", 1)))) {
        opt.fail.set_errorid(1, error_handler::ErrorCategory::Error,
                             error_handler::ErrorType::GeneralError);
        opt.fail.append_msg(true, "On entry, error in parameter norm.");
        opt.fail.append_msg(false, "Constraint: norm = \"1\", \"O\", \"I\", "
                                   "\"F\", \"E\" or \"M\".");
        opt.fail.throw_error();
      }
      if (!(local_m >= 0)) {
        opt.fail.set_errorid(2, error_handler::ErrorCategory::Error,
                             error_handler::ErrorType::GeneralError);
        opt.fail.append_msg(true, "On entry, error in parameter m.");
        opt.fail.append_msg(false, "Constraint: m >= 0.");
        opt.fail.throw_error();
      }
      if (!(local_n >= 0)) {
        opt.fail.set_errorid(3, error_handler::ErrorCategory::Error,
                             error_handler::ErrorType::GeneralError);
        opt.fail.append_msg(true, "On entry, error in parameter n.");
        opt.fail.append_msg(false, "Constraint: n >= 0.");
        opt.fail.throw_error();
      }

      f06raft_(en_data, local_norm.data, local_m, local_n, local_a.data,
               local_lda, local_nrm, local_work.data, local_norm.string_length);

      return local_nrm;
    }

    // alt-1
    template <typename A>
    double dlange(const std::string norm, const A &a) {
      blas::OptionalF06RA local_opt;

      double local_nrm = dlange(norm, a, local_opt);

      return local_nrm;
    }
  }
}
#define f06ra blas::dlange
#endif
