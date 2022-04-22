// Header for nagcpp::correg::corrmat_nearest_rank (g02ak)

// Copyright 2022, Numerical Algorithms Group Ltd, Oxford, UK.
// Generated by cpp-ft-wrapper.xsl
// Version 28.4.0.0
#ifndef NAGCPP_G02AK_HPP
#define NAGCPP_G02AK_HPP

#include "utility/nagcpp_consts.hpp"
#include "utility/nagcpp_data_handling.hpp"
#include "utility/nagcpp_engine_routines.hpp"
#include "utility/nagcpp_engine_types.hpp"
#include "utility/nagcpp_error_handler.hpp"
#include "utility/nagcpp_utility_optional.hpp"

namespace nagcpp {
  namespace correg {
    // corrmat_nearest_rank (g02ak)
    // Computes the rank-constrained nearest correlation matrix to a real square
    // matrix, using the method of Qi and Sun.
    // correg::corrmat_nearest_rank (g02ak) computes the nearest correlation matrix
    // of maximum prescribed rank, in the Frobenius norm, to a given square, input
    // matrix.

    // parameters:
    //   g: double, array, shape(n, n)
    //     On entry: G~, the initial matrix
    //     On exit: a symmetric matrix G = 1/2(G~+G~^T) with diagonal elements set to
    //     1.0
    //   f: double, scalar
    //     On exit: the difference between X and G given by 1/2||X-G||_F^2
    //   rankerr: double, scalar
    //     On exit: the rank error of X, defined as sum_i = r+1^n(lambda_i), given
    //     that lambda_i denote eigenvalues of X sorted in non-increasing order
    //   nsub: types::f77_integer, scalar
    //     On exit: the total number of majorized problems that have been solved,
    //     i.e., the total number of calls for correg::corrmat_nearest (g02aa)
    //   ldg: types::f77_integer, scalar
    //     The first dimension of the array g.
    //   n: types::f77_integer, scalar
    //     The order of the matrix G
    //   rank: types::f77_integer, scalar
    //     r, the upper bound for the rank of X
    //   x: double, array, shape(n, n)
    //     On exit, if not null on entry: X, the nearest correlation matrix of rank r
    //   opt: correg::OptionalG02AK
    //     Optional parameter container, derived from utility::Optional.
    //     contains:
    //       errtol: double, scalar
    //         The termination tolerance for the convergence measure of the objective
    //         function value
    //         default value: 0.0
    //       ranktol: double, scalar
    //         The feasibility tolerance for the rank constraint
    //         default value: 0.0
    //       maxits: types::f77_integer, scalar
    //         Specifies the maximum number of iterations used for the majorization
    //         approach to solve penalized problems at each level of penalty parameter
    //         default value: 0
    //       maxit: types::f77_integer, scalar
    //         Specifies the maximum number of iterations for the penalty method, i.e.,
    //         the maximum level of penalty parameter
    //         default value: 0
    //       fail: error_handler::ErrorHandler

    // error_handler::ErrorException
    //   (errorid 1)
    //     On entry, n = <value>.
    //     Constraint: n > 0.
    //   (errorid 4)
    //     On entry, rank = <value> and n = <value>.
    //     Constraint: 0 < rank <= n.
    //   (errorid 5)
    //     Majorized penalty approach fails to converge in opt.maxit level of penalty
    //     iterations.
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
    //   (errorid -399)
    //     Your licence key may have expired or may not have been installed correctly.
    //   (errorid -999)
    //     Dynamic memory allocation failed.

    // error_handler::WarningException
    //   (errorid 6)
    //     Convergence is limited by machine precision. The objective function
    //     value or rank is decreasing very slowly.
    //     The array returned in x may still be of interest.

    extern "C" {
#if defined(_WIN32) && defined(USE_STDCALL)
#define g02akft_(en_data, g, ldg, n, rank, errtol, ranktol, maxits, maxit, x,  \
                 ldx, f, rankerr, nsub, errbuf, ifail, errbuf_length)          \
  G02AKFT(en_data, g, ldg, n, rank, errtol, ranktol, maxits, maxit, x, ldx, f, \
          rankerr, nsub, errbuf, errbuf_length, ifail)
#elif defined(_WIN32) || defined(_WIN64)
#define g02akft_ G02AKFT
#else
#define G02AKFT g02akft_
#endif
    extern void NAG_CALL G02AKFT(
      types::engine_data &en_data, double g[], const types::f77_integer &ldg,
      const types::f77_integer &n, const types::f77_integer &rank,
      const double &errtol, const double &ranktol,
      const types::f77_integer &maxits, const types::f77_integer &maxit,
      double x[], const types::f77_integer &ldx, double &f, double &rankerr,
      types::f77_integer &nsub, char *errbuf NAG_STDCALL_LEN(errbuf_length),
      types::f77_integer &ifail NAG_NSTDCALL_LEN(errbuf_length));
    }

    class OptionalG02AK : public utility::Optional {
    private:
      double errtol_value;
      double ranktol_value;
      types::f77_integer maxits_value;
      types::f77_integer maxit_value;

    public:
      OptionalG02AK()
        : Optional(), errtol_value(0.0), ranktol_value(0.0), maxits_value(0),
          maxit_value(0) {}
      OptionalG02AK &errtol(double value) {
        errtol_value = value;
        return (*this);
      }
      double get_errtol(void) { return errtol_value; }
      OptionalG02AK &ranktol(double value) {
        ranktol_value = value;
        return (*this);
      }
      double get_ranktol(void) { return ranktol_value; }
      OptionalG02AK &maxits(types::f77_integer value) {
        maxits_value = value;
        return (*this);
      }
      types::f77_integer get_maxits(void) { return maxits_value; }
      OptionalG02AK &maxit(types::f77_integer value) {
        maxit_value = value;
        return (*this);
      }
      types::f77_integer get_maxit(void) { return maxit_value; }
      template <typename G, typename X>
      friend void corrmat_nearest_rank(G &&g, const types::f77_integer rank,
                                       X &&x, double &f, double &rankerr,
                                       types::f77_integer &nsub,
                                       correg::OptionalG02AK &opt);
    };

    template <typename G, typename X>
    void corrmat_nearest_rank(G &&g, const types::f77_integer rank, X &&x,
                              double &f, double &rankerr,
                              types::f77_integer &nsub,
                              correg::OptionalG02AK &opt) {
      opt.fail.prepare("correg::corrmat_nearest_rank (g02ak)");
      types::engine_data en_data;
      engine_routines::y90haan_(en_data);
      en_data.allocate_workspace = constants::NAG_ED_YES;
      data_handling::RawData<double, data_handling::ArgIntent::IntentINOUT,
                             typename std::remove_reference<G>::type>
        local_g(g);

      types::f77_integer local_n =
        data_handling::get_size(opt.fail, "n", local_g, 1, local_g, 2);
      if (opt.fail.error_thrown) {
        return;
      }
      double local_errtol = opt.errtol_value;
      double local_ranktol = opt.ranktol_value;
      types::f77_integer local_maxits = opt.maxits_value;
      types::f77_integer local_maxit = opt.maxit_value;
      data_handling::RawData<double, data_handling::ArgIntent::IntentOUT,
                             typename std::remove_reference<X>::type>
        local_x(x);
      local_x.resize(x, local_n, local_n);
      types::f77_integer local_storage_order =
        data_handling::get_storage_order(opt.default_to_col_major, local_g,
                                         local_x);
      en_data.storage_order = local_storage_order;

      types::f77_integer local_ldx = local_x.get_LD(local_storage_order);
      local_x.check(opt.fail, "x", true, local_storage_order, local_n, local_n);
      if (opt.fail.error_thrown) {
        return;
      }
      types::f77_integer local_ldg = local_g.get_LD(local_storage_order);
      local_g.check(opt.fail, "g", true, local_storage_order, local_n, local_n);
      if (opt.fail.error_thrown) {
        return;
      }

      g02akft_(en_data, local_g.data, local_ldg, local_n, rank, local_errtol,
               local_ranktol, local_maxits, local_maxit, local_x.data,
               local_ldx, f, rankerr, nsub, opt.fail.errbuf, opt.fail.errorid,
               opt.fail.errbuf_length);

      if (!(opt.fail.initial_error_handler(en_data))) {
        if (opt.fail.ierr == 1 && opt.fail.ifmt == 1001) {
          opt.fail.set_errorid(1, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(true, "On entry, n = ", 1, ".");
          opt.fail.append_msg(false, "Constraint: n > 0.");
        } else if (opt.fail.ierr == 4 && opt.fail.ifmt == 4001) {
          opt.fail.set_errorid(4, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(true, "On entry, rank = ", 1, " and n = ", 2,
                              ".");
          opt.fail.append_msg(false, "Constraint: 0 < rank <= n.");
        } else if (opt.fail.ierr == 5 && opt.fail.ifmt == 5001) {
          opt.fail.set_errorid(5, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "Majorized penalty approach fails to "
                                     "converge in opt.maxit level of penalty");
          opt.fail.append_msg(false, "iterations.");
        } else if (opt.fail.ierr == 6) {
          opt.fail.set_errorid(6, error_handler::ErrorCategory::Warning,
                               error_handler::ErrorType::GeneralWarning);
          opt.fail.append_msg(false, "Convergence is limited by machine "
                                     "precision. The objective function");
          opt.fail.append_msg(true, "value or rank is decreasing very slowly.");
          opt.fail.append_msg(false, "The array returned in x may still be of "
                                     "interest.");
        } else {
          opt.fail.set_unexpected_error();
        }
        opt.fail.throw_error();
      }
      if (opt.fail.error_thrown) {
        return;
      }

      local_x.copy_back(x);
      opt.fail.throw_warning();
    }

    // alt-1
    template <typename G, typename X>
    void corrmat_nearest_rank(G &&g, const types::f77_integer rank, X &&x,
                              double &f, double &rankerr,
                              types::f77_integer &nsub) {
      correg::OptionalG02AK local_opt;

      corrmat_nearest_rank(g, rank, x, f, rankerr, nsub, local_opt);
    }
  }
}
#define g02ak correg::corrmat_nearest_rank
#endif
