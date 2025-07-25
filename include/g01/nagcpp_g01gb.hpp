// Header for nagcpp::stat::prob_students_t_noncentral (g01gb)

// Copyright 2025, Numerical Algorithms Group Ltd, Oxford, UK.
// Generated by cpp-ft-wrapper.xsl
// Version 31.1.0.0
#ifndef NAGCPP_G01GB_HPP
#define NAGCPP_G01GB_HPP

#include "utility/nagcpp_consts.hpp"
#include "utility/nagcpp_engine_routines.hpp"
#include "utility/nagcpp_engine_types.hpp"
#include "utility/nagcpp_error_handler.hpp"
#include "utility/nagcpp_utility_optional.hpp"
#include <limits>

namespace nagcpp {
  namespace stat {
    // prob_students_t_noncentral (g01gb)
    // Computes probabilities for the non-central Student's t-distribution.
    // stat::prob_students_t_noncentral (g01gb) returns the lower tail probability
    // for the noncentral Student's t-distribution.

    // parameters:
    //   t: double, scalar
    //     t, the deviate from the Student's t-distribution with nu degrees of freedom
    //   df: double, scalar
    //     nu, the degrees of freedom of the Student's t-distribution
    //   delta: double, scalar
    //     delta, the noncentrality parameter of the Students t-distribution
    //   opt: stat::OptionalG01GB
    //     Optional parameter container, derived from utility::Optional.
    //     contains:
    //       tol: double, scalar
    //         The absolute accuracy required by you in the results
    //         default value: 0.0
    //       maxit: types::f77_integer, scalar
    //         The maximum number of terms that are used in each of the summations
    //         default value: 100
    //       fail: error_handler::ErrorHandler

    // returns: double, scalar
    //   The lower tail probability for the noncentral Student's t-distribution

    // error_handler::ErrorException
    //   (errorid 1)
    //     On entry, df = <value>.
    //     Constraint: df >= 1.0.
    //   (errorid 2)
    //     On entry, opt.maxit = <value>.
    //     Constraint: opt.maxit >= 1.
    //   (errorid 4)
    //     Unable to calculate the probability as it is too close to zero or one.
    //   (errorid -99)
    //     An unexpected error has been triggered by this routine.
    //   (errorid -399)
    //     Your licence key may have expired or may not have been installed correctly.
    //   (errorid -999)
    //     Dynamic memory allocation failed.

    // error_handler::WarningException
    //   (errorid 3)
    //     One of the series has failed to converge with opt.maxit = <value>
    //     and opt.tol = <value>.
    //     Reconsider the requested tolerance and/or the maximum number of iterations.
    //   (errorid 4)
    //     The probability is too close to 0 or 1.
    //     The returned value should be a reasonable estimate of the true value.

    extern "C" {
#if defined(_WIN32) && defined(USE_STDCALL)
#define g01gbft_(en_data, t, df, delta, tol, maxit, p, errbuf, ifail, \
                 errbuf_length)                                       \
  G01GBFT(en_data, t, df, delta, tol, maxit, p, errbuf, errbuf_length, ifail)
#elif defined(_WIN32) || defined(_WIN64)
#define g01gbft_ G01GBFT
#else
#define G01GBFT g01gbft_
#endif
    extern void NAG_CALL G01GBFT(
      types::engine_data &en_data, const double &t, const double &df,
      const double &delta, const double &tol, const types::f77_integer &maxit,
      double &p, char *errbuf NAG_STDCALL_LEN(errbuf_length),
      types::f77_integer &ifail NAG_NSTDCALL_LEN(errbuf_length));
    }

    class OptionalG01GB : public utility::Optional {
    private:
      double tol_value;
      types::f77_integer maxit_value;

    public:
      OptionalG01GB() : Optional(), tol_value(0.0), maxit_value(100) {}
      OptionalG01GB &tol(double value) {
        tol_value = value;
        return (*this);
      }
      double get_tol(void) { return tol_value; }
      OptionalG01GB &maxit(types::f77_integer value) {
        maxit_value = value;
        return (*this);
      }
      types::f77_integer get_maxit(void) { return maxit_value; }
      friend double prob_students_t_noncentral(const double t, const double df,
                                               const double delta,
                                               stat::OptionalG01GB &opt);
    };

    double prob_students_t_noncentral(const double t, const double df,
                                      const double delta,
                                      stat::OptionalG01GB &opt) {
      opt.fail.prepare("stat::prob_students_t_noncentral (g01gb)");
      types::engine_data en_data;
      engine_routines::y90haan_(en_data);
      en_data.allocate_workspace = constants::NAG_ED_YES;

      double local_tol = opt.tol_value;
      types::f77_integer local_maxit = opt.maxit_value;
      double local_p;

      g01gbft_(en_data, t, df, delta, local_tol, local_maxit, local_p,
               opt.fail.errbuf, opt.fail.errorid, opt.fail.errbuf_length);

      if (!(opt.fail.initial_error_handler(en_data))) {
        if (opt.fail.ierr == 1 && opt.fail.ifmt == 99999) {
          opt.fail.set_errorid(1, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(true, "On entry, df = ", 1, ".");
          opt.fail.append_msg(false, "Constraint: df >= 1.0.");
        } else if (opt.fail.ierr == 2 && opt.fail.ifmt == 99996) {
          opt.fail.set_errorid(2, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(true, "On entry, opt.maxit = ", 1, ".");
          opt.fail.append_msg(false, "Constraint: opt.maxit >= 1.");
        } else if (opt.fail.ierr == 3 && opt.fail.ifmt == 99997) {
          opt.fail.set_errorid(3, error_handler::ErrorCategory::Warning,
                               error_handler::ErrorType::GeneralWarning);
          opt.fail.append_msg(
            false,
            "One of the series has failed to converge with opt.maxit = ", 1);
          opt.fail.append_msg(false, "and opt.tol = ", 2, ".");
          opt.fail.append_msg(false, "Reconsider the requested tolerance "
                                     "and/or the maximum number of "
                                     "iterations.");
        } else if (opt.fail.ierr == 4 && opt.fail.ifmt == 99995) {
          opt.fail.set_errorid(4, error_handler::ErrorCategory::Warning,
                               error_handler::ErrorType::GeneralWarning);
          opt.fail.append_msg(false, "The probability is too close to 0 or 1.");
          opt.fail.append_msg(false, "The returned value should be a "
                                     "reasonable estimate of the true value.");
        } else if (opt.fail.ierr == 4 && opt.fail.ifmt == 99998) {
          opt.fail.set_errorid(4, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "Unable to calculate the probability as "
                                     "it is too close to zero or one.");
        } else {
          opt.fail.set_unexpected_error();
        }
        opt.fail.throw_error();
      }
      if (opt.fail.error_thrown) {
        return std::numeric_limits<double>::quiet_NaN();
      }
      opt.fail.throw_warning(local_p);

      return local_p;
    }

    // alt-1
    double prob_students_t_noncentral(const double t, const double df,
                                      const double delta) {
      stat::OptionalG01GB local_opt;

      double local_p = prob_students_t_noncentral(t, df, delta, local_opt);

      return local_p;
    }
  }
}
#define g01gb stat::prob_students_t_noncentral
#endif
