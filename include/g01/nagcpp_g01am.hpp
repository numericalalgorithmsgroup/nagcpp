// Header for nagcpp::stat::quantiles (g01am)

// Copyright 2024, Numerical Algorithms Group Ltd, Oxford, UK.
// Generated by cpp-ft-wrapper.xsl
// Version 30.3.0.0
#ifndef NAGCPP_G01AM_HPP
#define NAGCPP_G01AM_HPP

#include "utility/nagcpp_consts.hpp"
#include "utility/nagcpp_data_handling.hpp"
#include "utility/nagcpp_engine_routines.hpp"
#include "utility/nagcpp_engine_types.hpp"
#include "utility/nagcpp_error_handler.hpp"
#include "utility/nagcpp_utility_optional.hpp"

namespace nagcpp {
  namespace stat {
    // quantiles (g01am)
    // Find quantiles of an unordered vector, real numbers.
    // stat::quantiles (g01am) finds specified quantiles from a vector of unsorted
    // data.

    // parameters:
    //   n: types::f77_integer, scalar
    //     The number of elements in the input vector rv
    //   rv: double, array, shape(n)
    //     On entry: the vector whose quantiles are to be determined
    //     On exit: the order of the elements in rv is not, in general, preserved
    //   nq: types::f77_integer, scalar
    //     The number of quantiles requested
    //   q: double, array, shape(nq)
    //     The quantiles to be calculated, in ascending order
    //   qv: double, array, shape(nq)
    //     On exit, if not null on entry: qv[i-1] contains the quantile specified by
    //     the value provided in q[i-1], or an interpolated value if the quantile
    //     falls between two data values
    //   opt: stat::OptionalG01AM
    //     Optional parameter container, derived from utility::Optional.
    //     contains:
    //       fail: error_handler::ErrorHandler

    // error_handler::ErrorException
    //   (errorid 1)
    //     On entry, n = <value>.
    //     Constraint: n > 0.
    //   (errorid 2)
    //     On entry, nq = <value>.
    //     Constraint: nq > 0.
    //   (errorid 3)
    //     On entry, an element of q was less than 0.0 or greater than 1.0.
    //   (errorid 4)
    //     On entry, q was not in ascending order.
    //   (errorid 10601)
    //     On entry, argument <value> must be a vector of size <value> array.
    //     Supplied argument has <value> dimensions.
    //   (errorid 10601)
    //     On entry, argument <value> must be a vector of size <value> array.
    //     Supplied argument was a vector of size <value>.
    //   (errorid 10601)
    //     On entry, argument <value> must be a vector of size <value> array.
    //     The size for the supplied array could not be ascertained.
    //   (errorid 10602)
    //     On entry, the raw data component of <value> is null.
    //   (errorid 10603)
    //     On entry, unable to ascertain a value for <value>.
    //   (errorid -99)
    //     An unexpected error has been triggered by this routine.
    //   (errorid -399)
    //     Your licence key may have expired or may not have been installed correctly.
    //   (errorid -999)
    //     Dynamic memory allocation failed.

    extern "C" {
#if defined(_WIN32) && defined(USE_STDCALL)
#define g01amft_(en_data, n, rv, nq, q, qv, errbuf, ifail, errbuf_length) \
  G01AMFT(en_data, n, rv, nq, q, qv, errbuf, errbuf_length, ifail)
#elif defined(_WIN32) || defined(_WIN64)
#define g01amft_ G01AMFT
#else
#define G01AMFT g01amft_
#endif
    extern void NAG_CALL
      G01AMFT(types::engine_data &en_data, const types::f77_integer &n,
              double rv[], const types::f77_integer &nq, const double q[],
              double qv[], char *errbuf NAG_STDCALL_LEN(errbuf_length),
              types::f77_integer &ifail NAG_NSTDCALL_LEN(errbuf_length));
    }

    class OptionalG01AM : public utility::Optional {
    public:
      OptionalG01AM() : Optional() {}
      template <typename RV, typename Q, typename QV>
      friend void quantiles(RV &&rv, const Q &q, QV &&qv,
                            stat::OptionalG01AM &opt);
    };

    template <typename RV, typename Q, typename QV>
    void quantiles(RV &&rv, const Q &q, QV &&qv, stat::OptionalG01AM &opt) {
      opt.fail.prepare("stat::quantiles (g01am)");
      types::engine_data en_data;
      engine_routines::y90haan_(en_data);
      en_data.allocate_workspace = constants::NAG_ED_YES;
      data_handling::RawData<double, data_handling::ArgIntent::IntentINOUT,
                             typename std::remove_reference<RV>::type>
        local_rv(rv);
      data_handling::RawData<double, data_handling::ArgIntent::IntentIN,
                             typename std::remove_reference<Q>::type>
        local_q(q);

      types::f77_integer local_n =
        data_handling::get_size(opt.fail, "n", local_rv, 1);
      if (opt.fail.error_thrown) {
        return;
      }
      types::f77_integer local_nq =
        data_handling::get_size(opt.fail, "nq", local_q, 1);
      if (opt.fail.error_thrown) {
        return;
      }
      data_handling::RawData<double, data_handling::ArgIntent::IntentOUT,
                             typename std::remove_reference<QV>::type>
        local_qv(qv);
      local_qv.resize(qv, local_nq);

      local_qv.check(opt.fail, "qv", true, local_nq);
      if (opt.fail.error_thrown) {
        return;
      }
      local_q.check(opt.fail, "q", true, local_nq);
      if (opt.fail.error_thrown) {
        return;
      }
      local_rv.check(opt.fail, "rv", true, local_n);
      if (opt.fail.error_thrown) {
        return;
      }

      g01amft_(en_data, local_n, local_rv.data, local_nq, local_q.data,
               local_qv.data, opt.fail.errbuf, opt.fail.errorid,
               opt.fail.errbuf_length);

      if (!(opt.fail.initial_error_handler(en_data))) {
        if (opt.fail.ierr == 1 && opt.fail.ifmt == 1) {
          opt.fail.set_errorid(1, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(true, "On entry, n = ", 1, ".");
          opt.fail.append_msg(false, "Constraint: n > 0.");
        } else if (opt.fail.ierr == 2 && opt.fail.ifmt == 2) {
          opt.fail.set_errorid(2, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(true, "On entry, nq = ", 1, ".");
          opt.fail.append_msg(false, "Constraint: nq > 0.");
        } else if (opt.fail.ierr == 3 && opt.fail.ifmt == 3) {
          opt.fail.set_errorid(3, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "On entry, an element of q was less than "
                                     "0.0 or greater than 1.0.");
        } else if (opt.fail.ierr == 4 && opt.fail.ifmt == 4) {
          opt.fail.set_errorid(4, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "On entry, q was not in ascending order.");
        } else {
          opt.fail.set_unexpected_error();
        }
        opt.fail.throw_error();
      }
      if (opt.fail.error_thrown) {
        return;
      }

      local_qv.copy_back(qv);
      opt.fail.throw_warning();
    }

    // alt-1
    template <typename RV, typename Q, typename QV>
    void quantiles(RV &&rv, const Q &q, QV &&qv) {
      stat::OptionalG01AM local_opt;

      quantiles(rv, q, qv, local_opt);
    }
  }
}
#define g01am stat::quantiles
#endif
