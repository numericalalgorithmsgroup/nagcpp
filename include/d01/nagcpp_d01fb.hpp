// Header for nagcpp::quad::md_gauss (d01fb)

// Copyright 2019, Numerical Algorithms Group Ltd, Oxford, UK.
// Generated by cpp-ft-wrapper.xsl
// Version 27.0.0.1
#ifndef NAGCPP_D01FB_HPP
#define NAGCPP_D01FB_HPP

#include "utility/nagcpp_callback_handling.hpp"
#include "utility/nagcpp_consts.hpp"
#include "utility/nagcpp_data_handling.hpp"
#include "utility/nagcpp_engine_routines.hpp"
#include "utility/nagcpp_engine_types.hpp"
#include "utility/nagcpp_error_handler.hpp"
#include "utility/nagcpp_utility_optional.hpp"
#include <limits>

namespace nagcpp {
  namespace quad {
    // md_gauss (d01fb)
    // Multidimensional Gaussian quadrature over hyper-rectangle.
    // quad::md_gauss (d01fb) computes an estimate of a multidimensional integral
    // (from 1 to 20 dimensions), given the analytic form of the integrand and
    // suitable Gaussian weights and abscissae.

    // parameters:
    //   ndim: types::f77_integer, scalar
    //     n, the number of dimensions of the integral
    //   nptvec: types::f77_integer, array, shape(ndim)
    //     nptvec[j-1] must specify the number of points in the jth dimension of the
    //     summation, for j = 1,2,...,n
    //   lwa: types::f77_integer, scalar
    //     The dimension of the arrays weight and abscis.
    //   weight: double, array, shape(lwa)
    //     Must contain in succession the weights for the various dimensions, i.e.,
    //     weight[k-1] contains the ith weight for the jth dimension, with
    //     k = nptvec[0]+nptvec[1]+...+nptvec[j-2]+i.
    //   abscis: double, array, shape(lwa)
    //     Must contain in succession the abscissae for the various dimensions, i.e.,
    //     abscis[k-1] contains the ith abscissa for the jth dimension, with
    //     k = nptvec[0]+nptvec[1]+...+nptvec[j-2]+i.
    //   f: double, function
    //     f must return the value of the integrand at a given point

    //     parameters:
    //       x: double, array, shape(ndim)
    //         The coordinates of the point at which the integrand f must be evaluated
    //     returns: double, scalar
    //       The value of f(x) evaluated at x
    //   opt: quad::OptionalD01FB
    //     Optional parameter container, derived from utility::Optional.
    //     contains:
    //       fail: error_handler::ErrorHandler

    // returns: double, scalar
    //   The estimate of the integral

    // error_handler::ErrorException
    //   (errorid 1)
    //     On entry, lwa is too small.
    //     lwa = <value>.
    //     Minimum possible dimension: <value>.
    //   (errorid 1)
    //     On entry, ndim = <value>.
    //     Constraint: ndim <= 20.
    //   (errorid 1)
    //     On entry, ndim = <value>.
    //     Constraint: ndim >= 1.
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

    // error_handler::CallbackException
    //   (errorid 10701)
    //     An exception was thrown in a callback.
    //   (errorid 10702)
    //     The memory address for an array in a callback has changed.

    extern "C" {
#ifndef D01FBFT_F
#define D01FBFT_F                                                   \
  std::function<double(                                             \
    const data_handling::CallbackAddresses *, types::engine_data &, \
    const utility::array1D<double, data_handling::ArgIntent::IN> &)>
#endif

#ifndef D01FBFT_FH
#define D01FBFT_FH                                                          \
  void(NAG_CALL * fh)(const D01FBFT_F &, void *, types::engine_data &,      \
                      const types::f77_integer &, const double[], double &, \
                      void *, void *)
#endif

#if defined(_WIN32) && defined(USE_STDCALL)
#define d01fbft_(en_data, ndim, nptvec, lwa, weight, abscis, f, fsub, fh, \
                 mdint, iuser, ruser, errbuf, ifail, errbuf_length)       \
  D01FBFT(en_data, ndim, nptvec, lwa, weight, abscis, f, fsub, fh, mdint, \
          iuser, ruser, errbuf, errbuf_length, ifail)
#elif defined(_WIN32) || defined(_WIN64)
#define d01fbft_ D01FBFT
#else
#define D01FBFT d01fbft_
#endif
    extern void NAG_CALL
      D01FBFT(types::engine_data &en_data, const types::f77_integer &ndim,
              const types::f77_integer nptvec[], const types::f77_integer &lwa,
              const double weight[], const double abscis[], const D01FBFT_F &,
              void *fsub, D01FBFT_FH, double &mdint, void *iuser, void *ruser,
              char *errbuf NAG_STDCALL_LEN(errbuf_length),
              types::f77_integer &ifail NAG_NSTDCALL_LEN(errbuf_length));
    }

    class OptionalD01FB : public utility::Optional {
    public:
      OptionalD01FB() : Optional() {}
      template <typename NPTVEC, typename WEIGHT, typename ABSCIS, typename F>
      friend double md_gauss(const NPTVEC &nptvec, const WEIGHT &weight,
                             const ABSCIS &abscis, F f,
                             quad::OptionalD01FB &opt);
    };

    void d01fb_fh(const D01FBFT_F &f, void *fsub, types::engine_data &en_data,
                  const types::f77_integer &ndim, const double *x,
                  double &retval, void *iuser, void *ruser) {
      error_handler::ExceptionPointer *ep =
        static_cast<error_handler::ExceptionPointer *>(en_data.wrapptr1);
      utility::array1D<double, data_handling::ArgIntent::IN> local_x(x, ndim);
      data_handling::CallbackAddresses *callbacks =
        static_cast<data_handling::CallbackAddresses *>(en_data.wrapptr2);

      try {
        retval = f(callbacks, en_data, local_x);

      } catch (...) {
        // callback threw an exception
        en_data.hlperr = error_handler::HLPERR_USER_EXCEPTION;
        ep->eptr = std::current_exception();
      }

      if ((x != local_x.data())) {
        // address of an array changed
        en_data.hlperr = error_handler::HLPERR_ARRAY_POINTER_CHANGED;
        return;
      }
    }

    template <typename F_X, typename F>
    struct d01fb_f_cs {
      static double
        run(const data_handling::CallbackAddresses *callbacks,
            types::engine_data &en_data,
            const utility::array1D<double, data_handling::ArgIntent::IN> &x) {
        F f =
          *((typename std::remove_reference<F>::type *)(*callbacks).address[0]);

        auto local_x = data_handling::convert_nag_array_to_user<
          const utility::array1D<double, data_handling::ArgIntent::IN>,
          data_handling::ArgIntent::IN, F_X>(x);

        double local_retval = f(local_x.get());

        return local_retval;
      }
    };

    template <>
    struct d01fb_f_cs<std::nullptr_t, std::nullptr_t> {
      static double
        run(const data_handling::CallbackAddresses *callbacks,
            types::engine_data &en_data,
            const utility::array1D<double, data_handling::ArgIntent::IN> &x) {
        return 0;
      }
    };

    template <typename NPTVEC, typename WEIGHT, typename ABSCIS, typename F>
    double md_gauss(const NPTVEC &nptvec, const WEIGHT &weight,
                    const ABSCIS &abscis, F f, quad::OptionalD01FB &opt) {
      opt.fail.prepare("quad::md_gauss (d01fb)");
      types::engine_data en_data;
      engine_routines::y90haan_(en_data);
      en_data.allocate_workspace = constants::NAG_ED_YES;
      error_handler::ExceptionPointer ep;
      en_data.wrapptr1 = &ep;
      data_handling::RawData<types::f77_integer, data_handling::ArgIntent::IN,
                             typename std::remove_reference<NPTVEC>::type>
        local_nptvec(nptvec);
      data_handling::RawData<double, data_handling::ArgIntent::IN,
                             typename std::remove_reference<WEIGHT>::type>
        local_weight(weight);
      data_handling::RawData<double, data_handling::ArgIntent::IN,
                             typename std::remove_reference<ABSCIS>::type>
        local_abscis(abscis);
      data_handling::CallbackAddresses callbacks(1);
      en_data.wrapptr2 = static_cast<void *>(std::addressof(callbacks));
      static_assert(!(std::is_same<std::nullptr_t, F>::value),
                    "nullptr is not a valid input as no default function is "
                    "available for f");
      callbacks.address[0] = callback_handling::function_to_void_pointer(f);

      types::f77_integer local_ndim =
        data_handling::get_size(opt.fail, "ndim", local_nptvec, 1);
      if (opt.fail.error_thrown) {
        return std::numeric_limits<double>::quiet_NaN();
      }
      types::f77_integer local_lwa =
        data_handling::get_size(opt.fail, "lwa", local_weight, 1, local_abscis,
                                1);
      if (opt.fail.error_thrown) {
        return std::numeric_limits<double>::quiet_NaN();
      }
      using local_f_x_t = callback_handling::get_argument_type_t<
        0, callback_handling::argument_type_of_t<F>>;
      auto local_f = d01fb_f_cs<local_f_x_t, F>::run;
      void *local_fsub = nullptr;
      double local_mdint;
      void *local_iuser = nullptr;
      void *local_ruser = nullptr;

      local_abscis.check(opt.fail, "abscis", true, local_lwa);
      if (opt.fail.error_thrown) {
        return std::numeric_limits<double>::quiet_NaN();
      }
      local_weight.check(opt.fail, "weight", true, local_lwa);
      if (opt.fail.error_thrown) {
        return std::numeric_limits<double>::quiet_NaN();
      }
      local_nptvec.check(opt.fail, "nptvec", true, local_ndim);
      if (opt.fail.error_thrown) {
        return std::numeric_limits<double>::quiet_NaN();
      }

      d01fbft_(en_data, local_ndim, local_nptvec.data, local_lwa,
               local_weight.data, local_abscis.data, local_f, local_fsub,
               d01fb_fh, local_mdint, local_iuser, local_ruser, opt.fail.errbuf,
               opt.fail.errorid, opt.fail.errbuf_length);

      if (!(opt.fail.initial_error_handler(en_data))) {
        if (opt.fail.ierr == 1 && opt.fail.ifmt == 99997) {
          opt.fail.set_errorid(1, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "On entry, lwa is too small.");
          opt.fail.append_msg(false, "lwa = ", 1, ".");
          opt.fail.append_msg(false, "Minimum possible dimension: ", 2, ".");
        } else if (opt.fail.ierr == 1 && opt.fail.ifmt == 99998) {
          opt.fail.set_errorid(1, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(true, "On entry, ndim = ", 1, ".");
          opt.fail.append_msg(false, "Constraint: ndim <= 20.");
        } else if (opt.fail.ierr == 1 && opt.fail.ifmt == 99999) {
          opt.fail.set_errorid(1, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(true, "On entry, ndim = ", 1, ".");
          opt.fail.append_msg(false, "Constraint: ndim >= 1.");
        } else {
          opt.fail.set_unexpected_error();
        }
        opt.fail.throw_error();
      }
      if (opt.fail.error_thrown) {
        return std::numeric_limits<double>::quiet_NaN();
      }
      opt.fail.throw_warning(local_mdint);

      return local_mdint;
    }

    // alt-1
    template <typename NPTVEC, typename WEIGHT, typename ABSCIS, typename F>
    double md_gauss(const NPTVEC &nptvec, const WEIGHT &weight,
                    const ABSCIS &abscis, F f) {
      quad::OptionalD01FB local_opt;

      double local_mdint = md_gauss(nptvec, weight, abscis, f, local_opt);

      return local_mdint;
    }
  }
}
#define d01fb quad::md_gauss
#endif
