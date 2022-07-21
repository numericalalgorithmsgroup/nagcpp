// Header for nagcpp::roots::contfn_brent (c05ay)

// Copyright 2022, Numerical Algorithms Group Ltd, Oxford, UK.
// Generated by cpp-ft-wrapper.xsl
// Version 28.5.0.0
#ifndef NAGCPP_C05AY_HPP
#define NAGCPP_C05AY_HPP

#include "utility/nagcpp_callback_handling.hpp"
#include "utility/nagcpp_consts.hpp"
#include "utility/nagcpp_data_handling.hpp"
#include "utility/nagcpp_engine_routines.hpp"
#include "utility/nagcpp_engine_types.hpp"
#include "utility/nagcpp_error_handler.hpp"
#include "utility/nagcpp_utility_optional.hpp"
#include "x02/nagcpp_x02aj.hpp"

namespace nagcpp {
  namespace roots {
    // contfn_brent (c05ay)
    // Zero of continuous function in a given interval, Brent algorithm.
    // roots::contfn_brent (c05ay) locates a simple zero of a continuous function
    // in a given interval using Brent's method, which is a combination of
    // nonlinear interpolation, linear extrapolation and bisection.

    // parameters:
    //   a: double, scalar
    //     a, the lower bound of the interval
    //   b: double, scalar
    //     b, the upper bound of the interval
    //   f: double, function
    //     f must evaluate the function f whose zero is to be determined

    //     parameters:
    //       x: double, scalar
    //         The point at which the function must be evaluated
    //     returns: double, scalar
    //       The value of f evaluated at x
    //   x: double, scalar
    //     On exit: if the function exits successfully or ifail = 2, x is the final
    //     approximation to the zero
    //   opt: roots::OptionalC05AY
    //     Optional parameter container, derived from utility::Optional.
    //     contains:
    //       eps: double, scalar
    //         The termination tolerance on x (see Description)
    //         default value: 1000.0*machine precision
    //       eta: double, scalar
    //         A value such that if |f(x)| <= eta, x is accepted as the zero
    //         default value: 0.0
    //       fail: error_handler::ErrorHandler

    // error_handler::ErrorException
    //   (errorid 1)
    //     On entry, opt.eps = <value>.
    //     Constraint: opt.eps > 0.0.
    //   (errorid 1)
    //     On entry, a = <value> and b = <value>.
    //     Constraint: a != b.
    //   (errorid 1)
    //     On entry, f(a) and f(b) have the same sign with neither equalling 0.0:
    //     f(a) = <value> and f(b) = <value>.
    //   (errorid -99)
    //     An unexpected error has been triggered by this routine.
    //   (errorid -399)
    //     Your licence key may have expired or may not have been installed correctly.
    //   (errorid -999)
    //     Dynamic memory allocation failed.

    // error_handler::WarningException
    //   (errorid 2)
    //     No further improvement in the solution is possible.
    //     opt.eps is too small: opt.eps = <value>.
    //     The final value of x returned is an accurate approximation to the zero.
    //   (errorid 3)
    //     The function values in the interval [a,b] might contain
    //     a pole rather than a zero. Reducing opt.eps may help in distinguishing
    //     between
    //     a pole and a zero.

    // error_handler::CallbackException
    //   (errorid 10701)
    //     An exception was thrown in a callback.

    extern "C" {
#ifndef C05AYFT_F
#define C05AYFT_F                                                \
  std::function<double(const data_handling::CallbackAddresses *, \
                       types::engine_data &, const double)>
#endif

#ifndef C05AYFT_FH
#define C05AYFT_FH                                                     \
  void(NAG_CALL * fh)(const C05AYFT_F &, void *, types::engine_data &, \
                      const double &, double &, void *, void *)
#endif

#if defined(_WIN32) && defined(USE_STDCALL)
#define c05ayft_(en_data, a, b, eps, eta, f, fsub, fh, x, iuser, ruser,  \
                 errbuf, ifail, errbuf_length)                           \
  C05AYFT(en_data, a, b, eps, eta, f, fsub, fh, x, iuser, ruser, errbuf, \
          errbuf_length, ifail)
#elif defined(_WIN32) || defined(_WIN64)
#define c05ayft_ C05AYFT
#else
#define C05AYFT c05ayft_
#endif
    extern void NAG_CALL
      C05AYFT(types::engine_data &en_data, const double &a, const double &b,
              const double &eps, const double &eta, const C05AYFT_F &,
              void *fsub, C05AYFT_FH, double &x, void *iuser, void *ruser,
              char *errbuf NAG_STDCALL_LEN(errbuf_length),
              types::f77_integer &ifail NAG_NSTDCALL_LEN(errbuf_length));
    }

    class OptionalC05AY : public utility::Optional {
    private:
      double eps_value;
      utility::IsSet eps_set;
      double eta_value;

    public:
      OptionalC05AY()
        : Optional(), eps_set(utility::IsSet::No), eta_value(0.0) {}
      OptionalC05AY &eps(double value) {
        eps_set = utility::IsSet::Yes;
        eps_value = value;
        return (*this);
      }
      double get_eps(void) {
        if (eps_set == utility::IsSet::No) {
          fail.raise_error_value_not_available("eps");
          return std::numeric_limits<double>::quiet_NaN();
        }
        return eps_value;
      }
      OptionalC05AY &eta(double value) {
        eta_value = value;
        return (*this);
      }
      double get_eta(void) { return eta_value; }
      template <typename F>
      friend void contfn_brent(const double a, const double b, F &&f, double &x,
                               roots::OptionalC05AY &opt);
    };

    void c05ay_fh(const C05AYFT_F &f, void *fsub, types::engine_data &en_data,
                  const double &x, double &retval, void *iuser, void *ruser) {
      error_handler::ExceptionPointer *ep =
        static_cast<error_handler::ExceptionPointer *>(en_data.wrapptr1);
      data_handling::CallbackAddresses *callbacks =
        static_cast<data_handling::CallbackAddresses *>(en_data.wrapptr2);

      try {
        retval = f(callbacks, en_data, x);

      } catch (...) {
        // callback threw an exception
        en_data.hlperr = error_handler::HLPERR_USER_EXCEPTION;
        ep->eptr = std::current_exception();
      }
    }

    template <typename F>
    struct c05ay_f_cs {
      static double run(const data_handling::CallbackAddresses *callbacks,
                        types::engine_data &en_data, const double x) {
        F &f =
          *((typename std::remove_reference<F>::type *)(*callbacks).address[0]);

        double local_retval = f(x);

        return local_retval;
      }
    };

    template <>
    struct c05ay_f_cs<std::nullptr_t> {
      static double run(const data_handling::CallbackAddresses *callbacks,
                        types::engine_data &en_data, const double x) {
        return 0;
      }
    };

    template <typename F>
    void contfn_brent(const double a, const double b, F &&f, double &x,
                      roots::OptionalC05AY &opt) {
      opt.fail.prepare("roots::contfn_brent (c05ay)");
      double local_machpr = machine::precision();
      types::engine_data en_data;
      engine_routines::y90haan_(en_data);
      en_data.allocate_workspace = constants::NAG_ED_YES;
      error_handler::ExceptionPointer ep;
      en_data.wrapptr1 = &ep;
      data_handling::CallbackAddresses callbacks(1);
      en_data.wrapptr2 = static_cast<void *>(std::addressof(callbacks));
      static_assert(
        !(std::is_same<std::nullptr_t,
                       typename std::remove_reference<F>::type>::value),
        "nullptr is not a valid input as no default function is available for "
        "f");
      callbacks.address[0] = callback_handling::function_to_void_pointer(f);

      if (!(opt.eps_set == utility::IsSet::Yes)) {
        opt.eps_value = 1000.0 * local_machpr;
        opt.eps_set = utility::IsSet::Default;
      }
      double local_eps = opt.eps_value;
      double local_eta = opt.eta_value;
      auto local_f = c05ay_f_cs<typename std::remove_reference<F>::type>::run;
      void *local_fsub = nullptr;
      void *local_iuser = nullptr;
      void *local_ruser = nullptr;

      c05ayft_(en_data, a, b, local_eps, local_eta, local_f, local_fsub,
               c05ay_fh, x, local_iuser, local_ruser, opt.fail.errbuf,
               opt.fail.errorid, opt.fail.errbuf_length);

      if (!(opt.fail.initial_error_handler(en_data))) {
        if (opt.fail.ierr == 1 && opt.fail.ifmt == 1001) {
          opt.fail.set_errorid(1, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(true, "On entry, opt.eps = ", 1, ".");
          opt.fail.append_msg(false, "Constraint: opt.eps > 0.0.");
        } else if (opt.fail.ierr == 1 && opt.fail.ifmt == 1002) {
          opt.fail.set_errorid(1, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(true, "On entry, a = ", 1, " and b = ", 2, ".");
          opt.fail.append_msg(false, "Constraint: a != b.");
        } else if (opt.fail.ierr == 1 && opt.fail.ifmt == 1003) {
          opt.fail.set_errorid(1, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "On entry, f(a) and f(b) have the same "
                                     "sign with neither equalling 0.0:");
          opt.fail.append_msg(false, "f(a) = ", 1, " and f(b) = ", 2, ".");
        } else if (opt.fail.ierr == 2 && opt.fail.ifmt == 1004) {
          opt.fail.set_errorid(2, error_handler::ErrorCategory::Warning,
                               error_handler::ErrorType::GeneralWarning);
          opt.fail.append_msg(false, "No further improvement in the solution "
                                     "is possible.");
          opt.fail.append_msg(false, "opt.eps is too small: opt.eps = ", 1,
                              ".");
          opt.fail.append_msg(false, "The final value of x returned is an "
                                     "accurate approximation to the zero.");
        } else if (opt.fail.ierr == 3 && opt.fail.ifmt == 1005) {
          opt.fail.set_errorid(3, error_handler::ErrorCategory::Warning,
                               error_handler::ErrorType::GeneralWarning);
          opt.fail.append_msg(false, "The function values in the interval "
                                     "[a,b] might contain");
          opt.fail.append_msg(false, "a pole rather than a zero. Reducing "
                                     "opt.eps may help in distinguishing "
                                     "between");
          opt.fail.append_msg(false, "a pole and a zero.");
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
    template <typename F>
    void contfn_brent(const double a, const double b, F &&f, double &x) {
      roots::OptionalC05AY local_opt;

      contfn_brent(a, b, f, x, local_opt);
    }
  }
}
#define c05ay roots::contfn_brent
#endif
