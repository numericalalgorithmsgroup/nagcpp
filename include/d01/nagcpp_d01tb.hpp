// Header for nagcpp::quad::dim1_gauss_wres (d01tb)

// Copyright 2021, Numerical Algorithms Group Ltd, Oxford, UK.
// Generated by cpp-ft-wrapper.xsl
// Version 27.3.0.0
#ifndef NAGCPP_D01TB_HPP
#define NAGCPP_D01TB_HPP

#include "utility/nagcpp_consts.hpp"
#include "utility/nagcpp_data_handling.hpp"
#include "utility/nagcpp_engine_routines.hpp"
#include "utility/nagcpp_engine_types.hpp"
#include "utility/nagcpp_error_handler.hpp"
#include "utility/nagcpp_utility_optional.hpp"

namespace nagcpp {
  namespace quad {
    // dim1_gauss_wres (d01tb)
    // Pre-computed weights and abscissae for Gaussian quadrature rules, restricted
    // choice of rule.
    // quad::dim1_gauss_wres (d01tb) returns the weights and abscissae appropriate
    // to a Gaussian quadrature formula with a specified number of abscissae.
    // The formulae provided are for Gauss--Legendre, rational Gauss,
    // Gauss--Laguerre and Gauss--Hermite.

    // parameters:
    //   key: types::f77_integer, scalar
    //     Indicates the quadrature formula
    //   a: double, scalar
    //     The parameters a and b which occur in the quadrature formulae described in
    //     Description
    //   b: double, scalar
    //     The parameters a and b which occur in the quadrature formulae described in
    //     Description
    //   n: types::f77_integer, scalar
    //     n, the number of weights and abscissae to be returned
    //   weight: double, array, shape(n)
    //     On exit, if not null on entry: the n weights
    //   abscis: double, array, shape(n)
    //     On exit, if not null on entry: the n abscissae
    //   opt: quad::OptionalD01TB
    //     Optional parameter container, derived from utility::Optional.
    //     contains:
    //       fail: error_handler::ErrorHandler

    // error_handler::WarningException
    //   (errorid 1)
    //     The n-point rule is not among those stored.
    //     On entry: n = <value>.
    //     n-rule used: n = <value>.
    //   (errorid 2)
    //     Underflow occurred in calculation of normal weights.
    //     Reduce n or use adjusted weights: n = <value>.
    //   (errorid 3)
    //     No nonzero weights were generated for the provided parameters.

    // error_handler::ErrorException
    //   (errorid 11)
    //     On entry, key = <value>.
    //     Constraint: key = 0, 3, -3, 4, -4 or -5.
    //   (errorid 12)
    //     The value of a and/or b is invalid for Gauss-Laguerre quadrature.
    //     On entry, key = <value>.
    //     On entry, a = <value> and b = <value>.
    //     Constraint: abs(b) > 0.0.
    //   (errorid 12)
    //     The value of a and/or b is invalid for Gauss-Hermite quadrature.
    //     On entry, key = <value>.
    //     On entry, a = <value> and b = <value>.
    //     Constraint: b > 0.0.
    //   (errorid 12)
    //     The value of a and/or b is invalid for rational Gauss quadrature.
    //     On entry, key = <value>.
    //     On entry, a = <value> and b = <value>.
    //     Constraint: abs(a+b) > 0.0.
    //   (errorid 14)
    //     On entry, n = <value>.
    //     Constraint: n > 0.
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
#define d01tbft_(en_data, key, a, b, n, weight, abscis, errbuf, ifail, \
                 errbuf_length)                                        \
  D01TBFT(en_data, key, a, b, n, weight, abscis, errbuf, errbuf_length, ifail)
#elif defined(_WIN32) || defined(_WIN64)
#define d01tbft_ D01TBFT
#else
#define D01TBFT d01tbft_
#endif
    extern void NAG_CALL
      D01TBFT(types::engine_data &en_data, const types::f77_integer &key,
              const double &a, const double &b, const types::f77_integer &n,
              double weight[], double abscis[],
              char *errbuf NAG_STDCALL_LEN(errbuf_length),
              types::f77_integer &ifail NAG_NSTDCALL_LEN(errbuf_length));
    }

    class OptionalD01TB : public utility::Optional {
    public:
      OptionalD01TB() : Optional() {}
      template <typename WEIGHT, typename ABSCIS>
      friend void dim1_gauss_wres(const types::f77_integer key, const double a,
                                  const double b, const types::f77_integer n,
                                  WEIGHT &&weight, ABSCIS &&abscis,
                                  quad::OptionalD01TB &opt);
    };

    template <typename WEIGHT, typename ABSCIS>
    void dim1_gauss_wres(const types::f77_integer key, const double a,
                         const double b, const types::f77_integer n,
                         WEIGHT &&weight, ABSCIS &&abscis,
                         quad::OptionalD01TB &opt) {
      opt.fail.prepare("quad::dim1_gauss_wres (d01tb)");
      types::engine_data en_data;
      engine_routines::y90haan_(en_data);
      en_data.allocate_workspace = constants::NAG_ED_YES;

      data_handling::RawData<double, data_handling::ArgIntent::OUT,
                             typename std::remove_reference<WEIGHT>::type>
        local_weight(weight);
      local_weight.resize(weight, n);
      data_handling::RawData<double, data_handling::ArgIntent::OUT,
                             typename std::remove_reference<ABSCIS>::type>
        local_abscis(abscis);
      local_abscis.resize(abscis, n);

      local_abscis.check(opt.fail, "abscis", true, n);
      if (opt.fail.error_thrown) {
        return;
      }
      local_weight.check(opt.fail, "weight", true, n);
      if (opt.fail.error_thrown) {
        return;
      }

      d01tbft_(en_data, key, a, b, n, local_weight.data, local_abscis.data,
               opt.fail.errbuf, opt.fail.errorid, opt.fail.errbuf_length);

      if (!(opt.fail.initial_error_handler(en_data))) {
        if (opt.fail.ierr == 1 && opt.fail.ifmt == 1001) {
          opt.fail.set_errorid(1, error_handler::ErrorCategory::Warning,
                               error_handler::ErrorType::GeneralWarning);
          opt.fail.append_msg(true, "The n-point rule is not among those "
                                    "stored.");
          opt.fail.append_msg(true, "On entry: n = ", 1, ".");
          opt.fail.append_msg(false, "n-rule used: n = ", 2, ".");
        } else if (opt.fail.ierr == 2 && opt.fail.ifmt == 1002) {
          opt.fail.set_errorid(2, error_handler::ErrorCategory::Warning,
                               error_handler::ErrorType::GeneralWarning);
          opt.fail.append_msg(true, "Underflow occurred in calculation of "
                                    "normal weights.");
          opt.fail.append_msg(false,
                              "Reduce n or use adjusted weights: n = ", 1, ".");
        } else if (opt.fail.ierr == 3 && opt.fail.ifmt == 1004) {
          opt.fail.set_errorid(3, error_handler::ErrorCategory::Warning,
                               error_handler::ErrorType::GeneralWarning);
          opt.fail.append_msg(false, "No nonzero weights were generated for "
                                     "the provided parameters.");
        } else if (opt.fail.ierr == 11 && opt.fail.ifmt == 1011) {
          opt.fail.set_errorid(11, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(true, "On entry, key = ", 1, ".");
          opt.fail.append_msg(false, "Constraint: key = 0, 3, -3, 4, -4 or "
                                     "-5.");
        } else if (opt.fail.ierr == 12 && opt.fail.ifmt == 1201) {
          opt.fail.set_errorid(12, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(true, "The value of a and/or b is invalid for "
                                    "Gauss-Laguerre quadrature.");
          opt.fail.append_msg(true, "On entry, key = ", 1, ".");
          opt.fail.append_msg(true, "On entry, a = ", 2, " and b = ", 3, ".");
          opt.fail.append_msg(false, "Constraint: abs(b) > 0.0.");
        } else if (opt.fail.ierr == 12 && opt.fail.ifmt == 1202) {
          opt.fail.set_errorid(12, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(true, "The value of a and/or b is invalid for "
                                    "Gauss-Hermite quadrature.");
          opt.fail.append_msg(true, "On entry, key = ", 1, ".");
          opt.fail.append_msg(true, "On entry, a = ", 2, " and b = ", 3, ".");
          opt.fail.append_msg(false, "Constraint: b > 0.0.");
        } else if (opt.fail.ierr == 12 && opt.fail.ifmt == 1203) {
          opt.fail.set_errorid(12, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(true, "The value of a and/or b is invalid for "
                                    "rational Gauss quadrature.");
          opt.fail.append_msg(true, "On entry, key = ", 1, ".");
          opt.fail.append_msg(true, "On entry, a = ", 2, " and b = ", 3, ".");
          opt.fail.append_msg(false, "Constraint: abs(a+b) > 0.0.");
        } else if (opt.fail.ierr == 14 && opt.fail.ifmt == 1015) {
          opt.fail.set_errorid(14, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(true, "On entry, n = ", 1, ".");
          opt.fail.append_msg(false, "Constraint: n > 0.");
        } else {
          opt.fail.set_unexpected_error();
        }
        opt.fail.throw_error();
      }
      if (opt.fail.error_thrown) {
        return;
      }

      local_weight.copy_back(weight);
      local_abscis.copy_back(abscis);
      opt.fail.throw_warning();
    }

    // alt-1
    template <typename WEIGHT, typename ABSCIS>
    void dim1_gauss_wres(const types::f77_integer key, const double a,
                         const double b, const types::f77_integer n,
                         WEIGHT &&weight, ABSCIS &&abscis) {
      quad::OptionalD01TB local_opt;

      dim1_gauss_wres(key, a, b, n, weight, abscis, local_opt);
    }
  }
}
#define d01tb quad::dim1_gauss_wres
#endif
