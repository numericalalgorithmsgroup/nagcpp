// Header for nagcpp::interp::dim1_spline (e01ba)

// Copyright 2025, Numerical Algorithms Group Ltd, Oxford, UK.
// Generated by cpp-ft-wrapper.xsl
// Version 31.1.0.0
#ifndef NAGCPP_E01BA_HPP
#define NAGCPP_E01BA_HPP

#include "utility/nagcpp_consts.hpp"
#include "utility/nagcpp_data_handling.hpp"
#include "utility/nagcpp_engine_routines.hpp"
#include "utility/nagcpp_engine_types.hpp"
#include "utility/nagcpp_error_handler.hpp"
#include "utility/nagcpp_utility_optional.hpp"

namespace nagcpp {
  namespace interp {
    // dim1_spline (e01ba)
    // Interpolating functions, cubic spline interpolant, one variable.
    // interp::dim1_spline (e01ba) determines a cubic spline interpolant to a given
    // set of data.

    // parameters:
    //   m: types::f77_integer, scalar
    //     m, the number of data points
    //   x: double, array, shape(m)
    //     x[i-1] must be set to x_i, the ith data value of the independent variable
    //     x, for i = 1,2,...,m
    //   y: double, array, shape(m)
    //     y[i-1] must be set to y_i, the ith data value of the dependent variable y,
    //     for i = 1,2,...,m
    //   lamda: double, array, shape(m+4)
    //     On exit, if not null on entry: the value of lambda_i, the ith knot, for i
    //     = 1,2,...,m+4
    //   c: double, array, shape(m+4)
    //     On exit, if not null on entry: the coefficient c_i of the B-spline N_i(x),
    //     for i = 1,2,...,m
    //   opt: interp::OptionalE01BA
    //     Optional parameter container, derived from utility::Optional.
    //     contains:
    //       fail: error_handler::ErrorHandler

    // error_handler::ErrorException
    //   (errorid 1)
    //     On entry, lck = <value> and m = <value>.
    //     Constraint: lck >= m+4.
    //   (errorid 1)
    //     On entry, m = <value>.
    //     Constraint: m >= 4.
    //   (errorid 2)
    //     On entry, I = <value>, x[I-1] = <value>
    //     and x[I-2] = <value>.
    //     Constraint: x[I-1] > x[I-2].
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
#define e01baft_(en_data, iemode, m, x, y, lamda, c, lck, wrk, lwrk, errbuf, \
                 ifail, errbuf_length)                                       \
  E01BAFT(en_data, iemode, m, x, y, lamda, c, lck, wrk, lwrk, errbuf,        \
          errbuf_length, ifail)
#elif defined(_WIN32) || defined(_WIN64)
#define e01baft_ E01BAFT
#else
#define E01BAFT e01baft_
#endif
    extern void NAG_CALL
      E01BAFT(types::engine_data &en_data, const types::f77_integer &iemode,
              const types::f77_integer &m, const double x[], const double y[],
              double lamda[], double c[], const types::f77_integer &lck,
              double wrk[], const types::f77_integer &lwrk,
              char *errbuf NAG_STDCALL_LEN(errbuf_length),
              types::f77_integer &ifail NAG_NSTDCALL_LEN(errbuf_length));
    }

    class OptionalE01BA : public utility::Optional {
    public:
      OptionalE01BA() : Optional() {}
      template <typename X, typename Y, typename LAMDA, typename C>
      friend void dim1_spline(const X &x, const Y &y, LAMDA &&lamda, C &&c,
                              interp::OptionalE01BA &opt);
    };

    template <typename X, typename Y, typename LAMDA, typename C>
    void dim1_spline(const X &x, const Y &y, LAMDA &&lamda, C &&c,
                     interp::OptionalE01BA &opt) {
      opt.fail.prepare("interp::dim1_spline (e01ba)");
      types::engine_data en_data;
      engine_routines::y90haan_(en_data);
      en_data.allocate_workspace = constants::NAG_ED_YES;
      data_handling::RawData<double, data_handling::ArgIntent::IntentIN,
                             typename std::remove_reference<X>::type>
        local_x(x);
      data_handling::RawData<double, data_handling::ArgIntent::IntentIN,
                             typename std::remove_reference<Y>::type>
        local_y(y);

      types::f77_integer local_iemode = 0;
      types::f77_integer local_m =
        data_handling::get_size(opt.fail, "m", local_x, 1, local_y, 1);
      if (opt.fail.error_thrown) {
        return;
      }
      types::f77_integer local_lck = local_m + 4;
      data_handling::RawData<double, data_handling::ArgIntent::IntentOUT,
                             typename std::remove_reference<LAMDA>::type>
        local_lamda(lamda);
      local_lamda.resize(lamda, local_m + 4);
      data_handling::RawData<double, data_handling::ArgIntent::IntentOUT,
                             typename std::remove_reference<C>::type>
        local_c(c);
      local_c.resize(c, local_m + 4);
      data_handling::RawData<double, data_handling::ArgIntent::IntentOUT>
        local_wrk(static_cast<types::f77_integer>(0));
      types::f77_integer local_lwrk = 0;

      local_c.check(opt.fail, "c", true, local_m + 4);
      if (opt.fail.error_thrown) {
        return;
      }
      local_lamda.check(opt.fail, "lamda", true, local_m + 4);
      if (opt.fail.error_thrown) {
        return;
      }
      local_y.check(opt.fail, "y", true, local_m);
      if (opt.fail.error_thrown) {
        return;
      }
      local_x.check(opt.fail, "x", true, local_m);
      if (opt.fail.error_thrown) {
        return;
      }

      e01baft_(en_data, local_iemode, local_m, local_x.data, local_y.data,
               local_lamda.data, local_c.data, local_lck, local_wrk.data,
               local_lwrk, opt.fail.errbuf, opt.fail.errorid,
               opt.fail.errbuf_length);

      if (!(opt.fail.initial_error_handler(en_data))) {
        if (opt.fail.ierr == 1 && opt.fail.ifmt == 99997) {
          opt.fail.set_errorid(1, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(true, "On entry, lck = ", 1, " and m = ", 2, ".");
          opt.fail.append_msg(false, "Constraint: lck >= m+4.");
        } else if (opt.fail.ierr == 1 && opt.fail.ifmt == 99998) {
          opt.fail.set_errorid(1, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(true, "On entry, m = ", 1, ".");
          opt.fail.append_msg(false, "Constraint: m >= 4.");
        } else if (opt.fail.ierr == 2 && opt.fail.ifmt == 99996) {
          opt.fail.set_errorid(2, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "On entry, I = ", 1, ", x[I-1] = ", 2);
          opt.fail.append_msg(true, "and x[I-2] = ", 3, ".");
          opt.fail.append_msg(false, "Constraint: x[I-1] > x[I-2].");
        } else {
          opt.fail.set_unexpected_error();
        }
        opt.fail.throw_error();
      }
      if (opt.fail.error_thrown) {
        return;
      }

      local_lamda.copy_back(lamda);
      local_c.copy_back(c, local_m);
      opt.fail.throw_warning();
    }

    // alt-1
    template <typename X, typename Y, typename LAMDA, typename C>
    void dim1_spline(const X &x, const Y &y, LAMDA &&lamda, C &&c) {
      interp::OptionalE01BA local_opt;

      dim1_spline(x, y, lamda, c, local_opt);
    }
  }
}
#define e01ba interp::dim1_spline
#endif
