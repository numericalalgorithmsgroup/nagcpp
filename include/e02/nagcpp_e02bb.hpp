// Header for nagcpp::fit::dim1_spline_eval (e02bb)

// Copyright 2024, Numerical Algorithms Group Ltd, Oxford, UK.
// Generated by cpp-ft-wrapper.xsl
// Version 30.0.0.0
#ifndef NAGCPP_E02BB_HPP
#define NAGCPP_E02BB_HPP

#include "utility/nagcpp_consts.hpp"
#include "utility/nagcpp_data_handling.hpp"
#include "utility/nagcpp_engine_routines.hpp"
#include "utility/nagcpp_engine_types.hpp"
#include "utility/nagcpp_error_handler.hpp"
#include "utility/nagcpp_utility_optional.hpp"

namespace nagcpp {
  namespace fit {
    // dim1_spline_eval (e02bb)
    // Evaluation of fitted cubic spline, function only.
    // fit::dim1_spline_eval (e02bb) evaluates a cubic spline from its B-spline
    // representation.

    // parameters:
    //   ncap7: types::f77_integer, scalar
    //     n_+7, where n_ is the number of intervals (one greater than the number of
    //     interior knots, i.e., the knots strictly within the range lambda_4 to
    //     lambda_{n_+4}) over which the spline is defined
    //   lamda: double, array, shape(ncap7)
    //     lamda[j-1] must be set to the value of the jth member of the complete set
    //     of knots, lambda_j, for j = 1,2,...,n_+7
    //   c: double, array, shape(ncap7)
    //     The coefficient c_i of the B-spline N_i(x), for i = 1,2,...,n_+3
    //   x: double, scalar
    //     The argument x at which the cubic spline is to be evaluated
    //   s: double, scalar
    //     On exit: the value of the spline, s(x)
    //   opt: fit::OptionalE02BB
    //     Optional parameter container, derived from utility::Optional.
    //     contains:
    //       fail: error_handler::ErrorHandler

    // error_handler::ErrorException
    //   (errorid 1)
    //     On entry, x = <value>, ncap7 = <value>
    //     and lamda[ncap7-4] = <value>.
    //     Constraint: x <= lamda[ncap7-4].
    //   (errorid 1)
    //     On entry, x = <value> and
    //     lamda[3] = <value>.
    //     Constraint: x >= lamda[3].
    //   (errorid 2)
    //     On entry, ncap7 = <value>.
    //     Constraint: ncap7 >= 8.
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
#define e02bbft_(en_data, ncap7, lamda, c, x, s, errbuf, ifail, errbuf_length) \
  E02BBFT(en_data, ncap7, lamda, c, x, s, errbuf, errbuf_length, ifail)
#elif defined(_WIN32) || defined(_WIN64)
#define e02bbft_ E02BBFT
#else
#define E02BBFT e02bbft_
#endif
    extern void NAG_CALL
      E02BBFT(types::engine_data &en_data, const types::f77_integer &ncap7,
              const double lamda[], const double c[], const double &x,
              double &s, char *errbuf NAG_STDCALL_LEN(errbuf_length),
              types::f77_integer &ifail NAG_NSTDCALL_LEN(errbuf_length));
    }

    class OptionalE02BB : public utility::Optional {
    public:
      OptionalE02BB() : Optional() {}
      template <typename LAMDA, typename C>
      friend void dim1_spline_eval(const LAMDA &lamda, const C &c,
                                   const double x, double &s,
                                   fit::OptionalE02BB &opt);
    };

    template <typename LAMDA, typename C>
    void dim1_spline_eval(const LAMDA &lamda, const C &c, const double x,
                          double &s, fit::OptionalE02BB &opt) {
      opt.fail.prepare("fit::dim1_spline_eval (e02bb)");
      types::engine_data en_data;
      engine_routines::y90haan_(en_data);
      en_data.allocate_workspace = constants::NAG_ED_YES;
      data_handling::RawData<double, data_handling::ArgIntent::IntentIN,
                             typename std::remove_reference<LAMDA>::type>
        local_lamda(lamda);
      data_handling::RawData<double, data_handling::ArgIntent::IntentIN,
                             typename std::remove_reference<C>::type>
        local_c(c);

      types::f77_integer local_ncap7 =
        data_handling::get_size(opt.fail, "ncap7", local_lamda, 1, local_c, 1);
      if (opt.fail.error_thrown) {
        return;
      }

      local_c.check(opt.fail, "c", true, local_ncap7);
      if (opt.fail.error_thrown) {
        return;
      }
      local_lamda.check(opt.fail, "lamda", true, local_ncap7);
      if (opt.fail.error_thrown) {
        return;
      }

      e02bbft_(en_data, local_ncap7, local_lamda.data, local_c.data, x, s,
               opt.fail.errbuf, opt.fail.errorid, opt.fail.errbuf_length);

      if (!(opt.fail.initial_error_handler(en_data))) {
        if (opt.fail.ierr == 1 && opt.fail.ifmt == 99997) {
          opt.fail.set_errorid(1, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "On entry, x = ", 1, ", ncap7 = ", 2);
          opt.fail.append_msg(true, "and lamda[ncap7-4] = ", 3, ".");
          opt.fail.append_msg(false, "Constraint: x <= lamda[ncap7-4].");
        } else if (opt.fail.ierr == 1 && opt.fail.ifmt == 99998) {
          opt.fail.set_errorid(1, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "On entry, x = ", 1, " and");
          opt.fail.append_msg(true, "lamda[3] = ", 2, ".");
          opt.fail.append_msg(false, "Constraint: x >= lamda[3].");
        } else if (opt.fail.ierr == 2 && opt.fail.ifmt == 99999) {
          opt.fail.set_errorid(2, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(true, "On entry, ncap7 = ", 1, ".");
          opt.fail.append_msg(false, "Constraint: ncap7 >= 8.");
        } else {
          opt.fail.set_unexpected_error();
        }
        opt.fail.throw_error();
      }
      if (opt.fail.error_thrown) {
        return;
      }
      opt.fail.throw_warning();
    }

    // alt-1
    template <typename LAMDA, typename C>
    void dim1_spline_eval(const LAMDA &lamda, const C &c, const double x,
                          double &s) {
      fit::OptionalE02BB local_opt;

      dim1_spline_eval(lamda, c, x, s, local_opt);
    }
  }
}
#define e02bb fit::dim1_spline_eval
#endif
