// Header for nagcpp::opt::handle_solve_dfls_rcomm (e04fg)

// Copyright 2022, Numerical Algorithms Group Ltd, Oxford, UK.
// Generated by cpp-ft-wrapper.xsl
// Version 28.6.0.0
#ifndef NAGCPP_E04FG_HPP
#define NAGCPP_E04FG_HPP

#include "utility/nagcpp_consts.hpp"
#include "utility/nagcpp_data_handling.hpp"
#include "utility/nagcpp_engine_routines.hpp"
#include "utility/nagcpp_engine_types.hpp"
#include "utility/nagcpp_error_handler.hpp"
#include "utility/nagcpp_utility_comm.hpp"
#include "utility/nagcpp_utility_optional.hpp"
#include "utility/nagcpp_utility_print_rec.hpp"

namespace nagcpp {
  namespace opt {
    // handle_solve_dfls_rcomm (e04fg)
    // Reverse communication derivative-free (DFO) solver for a nonlinear least
    // squares objective function with bounded variables.
    // Note: this function uses optional algorithmic parameters, see also:
    // opt::handle_opt_set (e04zm), opt::handle_opt_get (e04zn).
    // opt::handle_solve_dfls_rcomm (e04fg) is a reverse communication
    // Derivative-free Optimization (DFO) solver from the NAG optimization
    // modelling suite (DFLS) for small to medium-scale nonlinear least squares
    // problems with bound constraints.

    // parameters:
    //   comm: opt::CommE04RA, scalar
    //     Communication structure.
    //     An object of either the derived class opt::CommE04RA or its base class
    //     utility::NoneCopyableComm can be supplied.
    //     It is recommended that the derived class is used. If the base class is
    //     supplied it must
    //     first be initialized via a call to opt::handle_init (e04ra).
    //   stats: double, array, shape(100)
    //     On exit, if not null on entry: solver statistics at monitoring steps or at
    //     the end of the final iteration
    //   irevcm: types::f77_integer, scalar
    //     On entry: does not need to be set on the first call of
    //     opt::handle_solve_dfls_rcomm (e04fg)
    //     On exit: indicates what action is to be performed before the next call to
    //     opt::handle_solve_dfls_rcomm (e04fg)
    //   neval: types::f77_integer, scalar
    //     On exit: indicates the number of objective evaluations required for the
    //     next call of opt::handle_solve_dfls_rcomm (e04fg) in rx
    //   maxeval: types::f77_integer, scalar
    //     The maximum number of function evaluations that can be requested at the
    //     same time
    //   nvar: types::f77_integer, scalar
    //     n, the current number of decision variables x in the model
    //   x: double, array, shape(nvar, maxeval)
    //     On entry: the first column contains x_0, the initial estimates of the
    //     variables x
    //     On exit: if irevcm = 0 or 2, the first column contains the best computed
    //     estimate of the solution
    //   nres: types::f77_integer, scalar
    //     m_r, the number of residuals in the problem
    //   rx: double, array, shape(nres, maxeval)
    //     On entry: does not need to be set on the first call to
    //     opt::handle_solve_dfls_rcomm (e04fg)
    //     On exit: if irevcm = 0 or 2, the first column contains the residuals of
    //     the best computed point
    //   rinfo: double, array, shape(100)
    //     On exit, if not null on entry: optimal objective value and various
    //     indicators at monitoring steps or at the end of the final iteration
    //   opt: opt::OptionalE04FG
    //     Optional parameter container, derived from utility::Optional.
    //     contains:
    //       fail: error_handler::ErrorHandler

    // other parameters:
    //   Defaults: valueless
    //     This special keyword may be used to reset all options to their default
    //     values
    //   DFLS Small Residuals Tol: double
    //     Default = epsilon^0.75
    //     This option defines the tolerance on the value of the residuals
    //   DFO Initial Interp Points: char
    //     Default = "Coordinate"
    //     Determines how the initial interpolation points are chosen
    //   DFO Maximum Slow Steps: types::f77_integer
    //     Default = 20
    //     If "DFO Maximum Slow Steps" > 0, this parameter defines the maximum number
    //     of consecutive slow iterations n_slow allowed
    //   DFO Max Objective Calls: types::f77_integer
    //     Default = 500
    //     A limit on the number of objective function evaluations the solver is
    //     allowed to compute
    //   DFO Max Soft Restarts: types::f77_integer
    //     Default = 5
    //     The maximum total number of soft restarts that can be performed if the
    //     objective function is declared as noisy ("DFO Noisy Problem" = "YES")
    //   DFO Max Unsucc Soft Restarts: types::f77_integer
    //     Default = 3
    //     The maximum number of consecutive unsuccessful soft restarts that can be
    //     performed if the objective function is declared as noisy ("DFO Noisy
    //     Problem" = "YES")
    //   DFO Monitor Frequency: types::f77_integer
    //     Default = 0
    //     If "DFO Monitor Frequency" > 0, the solver will stop at the end of every
    //     ith step for monitoring purposes
    //   DFO Noise Level: double
    //     Default = 0.0
    //     Indicates the noise level expected when evaluating the objective function
    //   DFO Noisy Problem: char
    //     Default = "NO"
    //     Indicates if the function evaluations provided to the solver are noisy
    //   DFO Number Initial Points: types::f77_integer
    //     Default = 0
    //     The initial number of interpolation points in Y_0 (1) used to build the
    //     linear models of the residuals
    //   DFO Number Interp Points: types::f77_integer
    //     Default = 0
    //     The maximum number of interpolation points in Y_k (1) used to build the
    //     linear models of the residuals
    //   DFO Number Soft Restarts Pts: types::f77_integer
    //     Default = 3
    //     The number of interpolation points that are replaced during a soft restart
    //   DFO Print Frequency: types::f77_integer
    //     Default = 1
    //     If "DFO Print Frequency" > 0, the solver prints the iteration log to the
    //     appropriate units at the end of every ith step
    //   DFO Random Seed: types::f77_integer
    //     Default = -1
    //     The random seed used to generate the random points used to build the
    //     initial model or build the underdetermined models when the interpolation
    //     set has not fully grown ("DFO Number Initial Points" < "DFO Number Interp
    //     Points")
    //   DFO Starting Trust Region: double
    //     Default = 0.1
    //     rho_beg, the initial trust region radius
    //   DFO Trust Region Slow Tol: double
    //     Default = epsilon^0.25
    //     The minimal acceptable trust region radius for the solution to be declared
    //     as acceptable
    //   DFO Trust Region Tolerance: double
    //     Default = epsilon^0.37
    //     rho_end, the requested trust region radius
    //   Infinite Bound Size: double
    //     Default = 10^20
    //     This defines the "infinite" bound bigbnd in the definition of the problem
    //     constraints
    //   Monitoring File: types::f77_integer
    //     Default = -1
    //     If i >= 0, the unit number for the secondary (monitoring) output
    //   Monitoring Level: types::f77_integer
    //     Default = 4
    //     This parameter sets the amount of information detail that will be printed
    //     by the solver to the secondary output
    //   Print File: types::f77_integer
    //     Default = advisory message unit number
    //     If i >= 0, the unit number for the primary output of the solver
    //   Print Level: types::f77_integer
    //     Default = 2
    //     This parameter defines how detailed information should be printed by the
    //     solver to the primary and secondary output
    //   Print Options: char
    //     Default = "YES"
    //     If "Print Options" = "YES", a listing of options will be printed to the
    //     primary output and is always printed to the secondary output
    //   Print Solution: char
    //     Default = "NO"
    //     If "Print Solution" = "YES", the solution will be printed to the primary
    //     and secondary output
    //   Stats Time: char
    //     Default = "NO"
    //     This parameter turns on timings of various parts of the algorithm to give
    //     a better overview of where most of the time is spent
    //   Time Limit: double
    //     Default = 10^6
    //     A limit to the number of seconds that the solver can use to solve one
    //     problem

    // error_handler::ErrorException
    //   (errorid 1)
    //     comm.handle has not been initialized.
    //   (errorid 1)
    //     comm.handle does not belong to the NAG optimization modelling suite,
    //     has not been initialized properly or is corrupted.
    //   (errorid 1)
    //     comm.handle has not been initialized properly or is corrupted.
    //   (errorid 2)
    //     This solver does not support the model defined in the handle.
    //   (errorid 2)
    //     The problem is already being solved.
    //   (errorid 4)
    //     On entry, maxeval = <value>.
    //     Constraint: maxeval > 0.
    //   (errorid 4)
    //     On entry, nvar = <value>,
    //     expected value = <value>.
    //     Constraint: nvar must match the current number of variables
    //     of the model in the comm.handle.
    //   (errorid 4)
    //     The information supplied does not match with that previously stored.
    //     On entry, nres = <value> must match that
    //     given during the definition of the objective in the comm.handle,
    //     i.e., <value>.
    //   (errorid 4)
    //     The information supplied does not match with that previously stored.
    //     On entry, maxeval = <value> must match that
    //     given during the first call of the function, i.e., <value>.
    //   (errorid 5)
    //     Inconsistent options "DFO Trust Region Tolerance" rho_end
    //     and "DFO Starting Trust Region" rho_beg.
    //     Constraint: rho_end < rho_beg.
    //     Use opt::handle_opt_set (e04zm) to set compatible option values.
    //   (errorid 5)
    //     Inconsistent options "DFO Trust Region Tolerance" rho_end
    //     and "DFO Trust Region Slow Tol" rho_tol.
    //     Constraint: rho_end < rho_tol.
    //     Use opt::handle_opt_set (e04zm) to set compatible option values.
    //   (errorid 5)
    //     Option "DFO Starting Trust Region"
    //     rho_beg = <value>,
    //     l_x(i) = <value>,
    //     u_x(i) = <value> and i = <value>.
    //     Constraint: if l_x(i) != u_x(i) in coordinate i,
    //     then u_x(i)-l_x(i) >= 2*rho_beg.
    //     Use opt::handle_opt_set (e04zm) to set compatible option values.
    //   (errorid 6)
    //     There were n_r = <value> unequal bounds and
    //     the option
    //     "DFO Number Interp Points" npt = <value>.
    //     Constraint: n_r+1 <= npt <= (n_r+1)*(n_r+2)/2.
    //     Use opt::handle_opt_set (e04zm) to set compatible option values.
    //   (errorid 6)
    //     The number of initial interpolation points is greater than the maximum.
    //     Use "DFO Number Interp Points" and "DFO Number Initial Points"
    //     to control the number of interpolation points.
    //   (errorid 6)
    //     Initial number of interpolation points ninit = <value>,
    //     total number of interpolation points npts = <value>,
    //     number of variables nvar = <value>.
    //     Constraint: growing interpolation set is only supported for linear models
    //     (npts = nvar+1).
    //     Use "DFO Number Interp Points" and "DFO Number Initial Points"
    //     to control the number of interpolation points.
    //   (errorid 8)
    //     Maximization is not possible for a nonlinear least squares problem.
    //   (errorid 10601)
    //     On entry, argument <value> must be a vector of size <value> array.
    //     Supplied argument has <value> dimensions.
    //   (errorid 10601)
    //     On entry, argument <value> must be a vector of size <value> array.
    //     Supplied argument was a vector of size <value>.
    //   (errorid 10601)
    //     On entry, argument <value> must be a vector of size <value> array.
    //     The size for the supplied array could not be ascertained.
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
    //   (errorid 10605)
    //     On entry, the communication class <value> has not been initialized
    //     correctly.
    //   (errorid 10703)
    //     An exception was thrown during IO (writing).
    //   (errorid -99)
    //     An unexpected error has been triggered by this routine.
    //   (errorid -399)
    //     Your licence key may have expired or may not have been installed correctly.
    //   (errorid -999)
    //     Dynamic memory allocation failed.

    // error_handler::WarningException
    //   (errorid 17)
    //     Rescue failed: the trust region could not be reduced further after
    //     some function evaluation could not be provided.
    //     Check the specification of your objective and whether it needs rescaling.
    //     Try a different initial x.
    //   (errorid 17)
    //     Some initial interpolation points were not provided.
    //     Rescue cannot be attempted at this stage.
    //     Check the specification of your objective and whether it needs rescaling.
    //     Try a different initial x.
    //   (errorid 18)
    //     The predicted reduction in a trust region step was non-positive.
    //     Check the specification of your objective and whether it needs rescaling.
    //     Try a different initial x.
    //   (errorid 21)
    //     Maximum number of function evaluations exceeded.
    //   (errorid 23)
    //     The solver terminated after the maximum time allowed was exceeded.
    //   (errorid 24)
    //     No progress, the solver was stopped after <value>
    //     consecutive slow steps.
    //     Use the option "DFO Maximum Slow Steps" to modify the
    //     maximum number of slow steps accepted.
    //   (errorid 50)
    //     The problem was solved to an acceptable level after
    //     <value> consecutive slow iterations.
    //     Use the option "DFO Maximum Slow Steps" to modify the
    //     maximum number of slow steps accepted.

    // error_handler::CallbackEarlyTermination
    //   (errorid 20)
    //     User requested termination during a monitoring step.
    //   (errorid 20)
    //     User requested termination during an objective evaluation step.

    extern "C" {
#if defined(_WIN32) && defined(USE_STDCALL)
#define e04fgft_(en_data, print_rec, print_rech, handle, irevcm, neval,   \
                 maxeval, nvar, x, nres, rx, rinfo, stats, errbuf, ifail, \
                 errbuf_length)                                           \
  E04FGFT(en_data, print_rec, print_rech, handle, irevcm, neval, maxeval, \
          nvar, x, nres, rx, rinfo, stats, errbuf, errbuf_length, ifail)
#elif defined(_WIN32) || defined(_WIN64)
#define e04fgft_ E04FGFT
#else
#define E04FGFT e04fgft_
#endif
    extern void NAG_CALL E04FGFT(
      types::engine_data &en_data, void *print_rec, NAG_PRINT_RECH,
      void *handle, types::f77_integer &irevcm, types::f77_integer &neval,
      const types::f77_integer &maxeval, const types::f77_integer &nvar,
      double x[], const types::f77_integer &nres, double rx[], double rinfo[],
      double stats[], char *errbuf NAG_STDCALL_LEN(errbuf_length),
      types::f77_integer &ifail NAG_NSTDCALL_LEN(errbuf_length));
    }

    class CommE04RA;

    class OptionalE04FG : public utility::Optional {
    public:
      OptionalE04FG() : Optional() {}
      template <typename COMM, typename X, typename RX, typename RINFO,
                typename STATS>
      friend void handle_solve_dfls_rcomm(COMM &comm,
                                          types::f77_integer &irevcm,
                                          types::f77_integer &neval, X &&x,
                                          RX &&rx, RINFO &&rinfo, STATS &&stats,
                                          opt::OptionalE04FG &opt);
    };

    template <typename COMM, typename X, typename RX, typename RINFO,
              typename STATS>
    void handle_solve_dfls_rcomm(COMM &comm, types::f77_integer &irevcm,
                                 types::f77_integer &neval, X &&x, RX &&rx,
                                 RINFO &&rinfo, STATS &&stats,
                                 opt::OptionalE04FG &opt) {
      opt.fail.prepare("opt::handle_solve_dfls_rcomm (e04fg)");
      types::engine_data en_data;
      engine_routines::y90haan_(en_data);
      en_data.allocate_workspace = constants::NAG_ED_YES;
      static_assert(std::is_same<COMM, utility::NoneCopyableComm>::value ||
                      std::is_same<COMM, opt::CommE04RA>::value,
                    "Invalid type for comm: must be either "
                    "utility::NoneCopyableComm or opt::CommE04RA");
      if (!(comm.check())) {
        opt.fail.raise_error_comm_invalid("comm");
        if (opt.fail.error_thrown) {
          return;
        }
      }
      data_handling::RawData<double, data_handling::ArgIntent::IntentINOUT,
                             typename std::remove_reference<X>::type>
        local_x(x);
      data_handling::RawData<double, data_handling::ArgIntent::IntentINOUT,
                             typename std::remove_reference<RX>::type>
        local_rx(rx);

      void *local_print_rec = static_cast<void *>(&opt.iomanager);
      types::f77_integer local_maxeval =
        data_handling::get_size(opt.fail, "maxeval", local_x, 2, local_rx, 2);
      if (opt.fail.error_thrown) {
        return;
      }
      types::f77_integer local_nvar =
        data_handling::get_size(opt.fail, "nvar", local_x, 1);
      if (opt.fail.error_thrown) {
        return;
      }
      types::f77_integer local_nres =
        data_handling::get_size(opt.fail, "nres", local_rx, 1);
      if (opt.fail.error_thrown) {
        return;
      }
      data_handling::RawData<double, data_handling::ArgIntent::IntentOUT,
                             typename std::remove_reference<RINFO>::type>
        local_rinfo(rinfo);
      local_rinfo.resize(rinfo, static_cast<types::f77_integer>(100));
      data_handling::RawData<double, data_handling::ArgIntent::IntentOUT,
                             typename std::remove_reference<STATS>::type>
        local_stats(stats);
      local_stats.resize(stats, static_cast<types::f77_integer>(100));
      types::f77_integer local_storage_order =
        data_handling::get_storage_order(opt.default_to_col_major, local_x,
                                         local_rx);
      en_data.storage_order = local_storage_order;

      local_stats.check(opt.fail, "stats", true,
                        static_cast<types::f77_integer>(100));
      if (opt.fail.error_thrown) {
        return;
      }
      local_rinfo.check(opt.fail, "rinfo", true,
                        static_cast<types::f77_integer>(100));
      if (opt.fail.error_thrown) {
        return;
      }
      local_rx.check(opt.fail, "rx", true, local_storage_order, local_nres,
                     local_maxeval);
      if (opt.fail.error_thrown) {
        return;
      }
      local_x.check(opt.fail, "x", true, local_storage_order, local_nvar,
                    local_maxeval);
      if (opt.fail.error_thrown) {
        return;
      }

      e04fgft_(en_data, local_print_rec, utility::print_rech, &comm.handle,
               irevcm, neval, local_maxeval, local_nvar, local_x.data,
               local_nres, local_rx.data, local_rinfo.data, local_stats.data,
               opt.fail.errbuf, opt.fail.errorid, opt.fail.errbuf_length);

      if (!(opt.fail.initial_error_handler(en_data))) {
        if (opt.fail.ierr == 1 && opt.fail.ifmt == 100) {
          opt.fail.set_errorid(1, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "comm.handle has not been initialized.");
        } else if (opt.fail.ierr == 1 && opt.fail.ifmt == 101) {
          opt.fail.set_errorid(1, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "comm.handle does not belong to the NAG "
                                     "optimization modelling suite,");
          opt.fail.append_msg(false, "has not been initialized properly or is "
                                     "corrupted.");
        } else if (opt.fail.ierr == 1 && opt.fail.ifmt == 102) {
          opt.fail.set_errorid(1, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "comm.handle has not been initialized "
                                     "properly or is corrupted.");
        } else if (opt.fail.ierr == 2 && opt.fail.ifmt == 200) {
          opt.fail.set_errorid(2, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "This solver does not support the model "
                                     "defined in the handle.");
        } else if (opt.fail.ierr == 2 && opt.fail.ifmt == 201) {
          opt.fail.set_errorid(2, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "The problem is already being solved.");
        } else if (opt.fail.ierr == 4 && opt.fail.ifmt == 400) {
          opt.fail.set_errorid(4, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(true, "On entry, maxeval = ", 1, ".");
          opt.fail.append_msg(false, "Constraint: maxeval > 0.");
        } else if (opt.fail.ierr == 4 && opt.fail.ifmt == 401) {
          opt.fail.set_errorid(4, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "On entry, nvar = ", 1, ",");
          opt.fail.append_msg(true, "expected value = ", 2, ".");
          opt.fail.append_msg(false, "Constraint: nvar must match the current "
                                     "number of variables");
          opt.fail.append_msg(false, "of the model in the comm.handle.");
        } else if (opt.fail.ierr == 4 && opt.fail.ifmt == 402) {
          opt.fail.set_errorid(4, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(true, "The information supplied does not match "
                                    "with that previously stored.");
          opt.fail.append_msg(false, "On entry, nres = ", 1,
                              " must match that");
          opt.fail.append_msg(false, "given during the definition of the "
                                     "objective in the comm.handle,");
          opt.fail.append_msg(false, "i.e., ", 2, ".");
        } else if (opt.fail.ierr == 4 && opt.fail.ifmt == 403) {
          opt.fail.set_errorid(4, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(true, "The information supplied does not match "
                                    "with that previously stored.");
          opt.fail.append_msg(false, "On entry, maxeval = ", 1,
                              " must match that");
          opt.fail.append_msg(false,
                              "given during the first call of the function, "
                              "i.e., ",
                              2, ".");
        } else if (opt.fail.ierr == 5 && opt.fail.ifmt == 500) {
          opt.fail.set_errorid(5, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "Inconsistent options \"DFO Trust Region "
                                     "Tolerance\" rho_end");
          opt.fail.append_msg(true, "and \"DFO Starting Trust Region\" "
                                    "rho_beg.");
          opt.fail.append_msg(true, "Constraint: rho_end < rho_beg.");
          opt.fail.append_msg(false, "Use opt::handle_opt_set to set "
                                     "compatible option values.");
        } else if (opt.fail.ierr == 5 && opt.fail.ifmt == 501) {
          opt.fail.set_errorid(5, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "Inconsistent options \"DFO Trust Region "
                                     "Tolerance\" rho_end");
          opt.fail.append_msg(true, "and \"DFO Trust Region Slow Tol\" "
                                    "rho_tol.");
          opt.fail.append_msg(true, "Constraint: rho_end < rho_tol.");
          opt.fail.append_msg(false, "Use opt::handle_opt_set to set "
                                     "compatible option values.");
        } else if (opt.fail.ierr == 5 && opt.fail.ifmt == 502) {
          opt.fail.set_errorid(5, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "Option \"DFO Starting Trust Region\"");
          opt.fail.append_msg(false, "rho_beg = ", 1, ",");
          opt.fail.append_msg(false, "l_x(i) = ", 2, ",");
          opt.fail.append_msg(true, "u_x(i) = ", 3, " and i = ", 4, ".");
          opt.fail.append_msg(false, "Constraint: if l_x(i) != u_x(i) in "
                                     "coordinate i,");
          opt.fail.append_msg(true, "then u_x(i)-l_x(i) >= 2*rho_beg.");
          opt.fail.append_msg(false, "Use opt::handle_opt_set to set "
                                     "compatible option values.");
        } else if (opt.fail.ierr == 6 && opt.fail.ifmt == 600) {
          opt.fail.set_errorid(6, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "There were n_r = ", 1,
                              " unequal bounds and");
          opt.fail.append_msg(false, "the option");
          opt.fail.append_msg(true, "\"DFO Number Interp Points\" npt = ", 2,
                              ".");
          opt.fail.append_msg(true, "Constraint: n_r+1 <= npt <= "
                                    "(n_r+1)*(n_r+2)/2.");
          opt.fail.append_msg(false, "Use opt::handle_opt_set to set "
                                     "compatible option values.");
        } else if (opt.fail.ierr == 6 && opt.fail.ifmt == 601) {
          opt.fail.set_errorid(6, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(true, "The number of initial interpolation "
                                    "points is greater than the maximum.");
          opt.fail.append_msg(false, "Use \"DFO Number Interp Points\" and "
                                     "\"DFO Number Initial Points\"");
          opt.fail.append_msg(false, "to control the number of interpolation "
                                     "points.");
        } else if (opt.fail.ierr == 6 && opt.fail.ifmt == 602) {
          opt.fail.set_errorid(6, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(
            false, "Initial number of interpolation points ninit = ", 1, ",");
          opt.fail.append_msg(false,
                              "total number of interpolation points npts = ", 2,
                              ",");
          opt.fail.append_msg(true, "number of variables nvar = ", 3, ".");
          opt.fail.append_msg(false, "Constraint: growing interpolation set is "
                                     "only supported for linear models");
          opt.fail.append_msg(true, "(npts = nvar+1).");
          opt.fail.append_msg(false, "Use \"DFO Number Interp Points\" and "
                                     "\"DFO Number Initial Points\"");
          opt.fail.append_msg(false, "to control the number of interpolation "
                                     "points.");
        } else if (opt.fail.ierr == 8 && opt.fail.ifmt == 801) {
          opt.fail.set_errorid(8, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "Maximization is not possible for a "
                                     "nonlinear least squares problem.");
        } else if (opt.fail.ierr == 17 && opt.fail.ifmt == 1700) {
          opt.fail.set_errorid(17, error_handler::ErrorCategory::Warning,
                               error_handler::ErrorType::GeneralWarning);
          opt.fail.append_msg(false, "Rescue failed: the trust region could "
                                     "not be reduced further after");
          opt.fail.append_msg(false, "some function evaluation could not be "
                                     "provided.");
          opt.fail.append_msg(false, "Check the specification of your "
                                     "objective and whether it needs "
                                     "rescaling.");
          opt.fail.append_msg(false, "Try a different initial x.");
        } else if (opt.fail.ierr == 17 && opt.fail.ifmt == 1701) {
          opt.fail.set_errorid(17, error_handler::ErrorCategory::Warning,
                               error_handler::ErrorType::GeneralWarning);
          opt.fail.append_msg(false, "Some initial interpolation points were "
                                     "not provided.");
          opt.fail.append_msg(true, "Rescue cannot be attempted at this "
                                    "stage.");
          opt.fail.append_msg(false, "Check the specification of your "
                                     "objective and whether it needs "
                                     "rescaling.");
          opt.fail.append_msg(false, "Try a different initial x.");
        } else if (opt.fail.ierr == 18 && opt.fail.ifmt == 1800) {
          opt.fail.set_errorid(18, error_handler::ErrorCategory::Warning,
                               error_handler::ErrorType::GeneralWarning);
          opt.fail.append_msg(false, "The predicted reduction in a trust "
                                     "region step was non-positive.");
          opt.fail.append_msg(false, "Check the specification of your "
                                     "objective and whether it needs "
                                     "rescaling.");
          opt.fail.append_msg(false, "Try a different initial x.");
        } else if (opt.fail.ierr == 20 && opt.fail.ifmt == 2000) {
          opt.fail.set_errorid(20, error_handler::ErrorCategory::Warning,
                               error_handler::ErrorType::GeneralWarning);
          opt.fail.append_msg(false, "User requested termination during a "
                                     "monitoring step.");
          opt.fail.append_exception_msg(en_data);
        } else if (opt.fail.ierr == 20 && opt.fail.ifmt == 2001) {
          opt.fail.set_errorid(20, error_handler::ErrorCategory::Warning,
                               error_handler::ErrorType::GeneralWarning);
          opt.fail.append_msg(false, "User requested termination during an "
                                     "objective evaluation step.");
          opt.fail.append_exception_msg(en_data);
        } else if (opt.fail.ierr == 21 && opt.fail.ifmt == 2101) {
          opt.fail.set_errorid(21, error_handler::ErrorCategory::Warning,
                               error_handler::ErrorType::GeneralWarning);
          opt.fail.append_msg(false, "Maximum number of function evaluations "
                                     "exceeded.");
        } else if (opt.fail.ierr == 23 && opt.fail.ifmt == 2303) {
          opt.fail.set_errorid(23, error_handler::ErrorCategory::Warning,
                               error_handler::ErrorType::GeneralWarning);
          opt.fail.append_msg(false, "The solver terminated after the maximum "
                                     "time allowed was exceeded.");
        } else if (opt.fail.ierr == 24 && opt.fail.ifmt == 2400) {
          opt.fail.set_errorid(24, error_handler::ErrorCategory::Warning,
                               error_handler::ErrorType::GeneralWarning);
          opt.fail.append_msg(false,
                              "No progress, the solver was stopped after ", 1);
          opt.fail.append_msg(true, "consecutive slow steps.");
          opt.fail.append_msg(false, "Use the option \"DFO Maximum Slow "
                                     "Steps\" to modify the");
          opt.fail.append_msg(false, "maximum number of slow steps accepted.");
        } else if (opt.fail.ierr == 50 && opt.fail.ifmt == 5000) {
          opt.fail.set_errorid(50, error_handler::ErrorCategory::Warning,
                               error_handler::ErrorType::GeneralWarning);
          opt.fail.append_msg(false, "The problem was solved to an acceptable "
                                     "level after");
          opt.fail.append_msg(true, 1, " consecutive slow iterations.");
          opt.fail.append_msg(false, "Use the option \"DFO Maximum Slow "
                                     "Steps\" to modify the");
          opt.fail.append_msg(false, "maximum number of slow steps accepted.");
        } else {
          opt.fail.set_unexpected_error();
        }
        opt.fail.throw_error();
      }
      if (opt.fail.error_thrown) {
        return;
      }

      local_x.copy_back(x);
      local_rx.copy_back(rx);
      local_rinfo.copy_back(rinfo);
      local_stats.copy_back(stats);
      opt.fail.throw_warning();
    }

    // alt-1
    template <typename COMM, typename X, typename RX, typename RINFO,
              typename STATS>
    void handle_solve_dfls_rcomm(COMM &comm, types::f77_integer &irevcm,
                                 types::f77_integer &neval, X &&x, RX &&rx,
                                 RINFO &&rinfo, STATS &&stats) {
      opt::OptionalE04FG local_opt;

      handle_solve_dfls_rcomm(comm, irevcm, neval, x, rx, rinfo, stats,
                              local_opt);
    }
  }
}
#define e04fg opt::handle_solve_dfls_rcomm
#endif
