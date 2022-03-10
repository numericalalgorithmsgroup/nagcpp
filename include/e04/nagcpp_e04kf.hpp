// Header for nagcpp::opt::handle_solve_bounds_foas (e04kf)

// Copyright 2022, Numerical Algorithms Group Ltd, Oxford, UK.
// Generated by cpp-ft-wrapper.xsl
// Version 28.3.0.0
#ifndef NAGCPP_E04KF_HPP
#define NAGCPP_E04KF_HPP

#include "utility/nagcpp_callback_handling.hpp"
#include "utility/nagcpp_consts.hpp"
#include "utility/nagcpp_data_handling.hpp"
#include "utility/nagcpp_engine_routines.hpp"
#include "utility/nagcpp_engine_types.hpp"
#include "utility/nagcpp_error_handler.hpp"
#include "utility/nagcpp_utility_comm.hpp"
#include "utility/nagcpp_utility_macros.hpp"
#include "utility/nagcpp_utility_optional.hpp"
#include "utility/nagcpp_utility_print_rec.hpp"

namespace nagcpp {
  namespace opt {
    // handle_solve_bounds_foas (e04kf)
    // First-order active-set method for box constrained nonlinear optimization
    // with low memory requirements.
    // Note: this function uses optional algorithmic parameters, see also:
    // opt::handle_opt_set (e04zm), opt::handle_opt_get (e04zn).
    // opt::handle_solve_bounds_foas (e04kf) is a solver from the NAG optimization
    // modelling suite for bound-constrained large-scale Nonlinear Programming
    // (NLP) problems.
    // It is a first-order active-set method (FOAS) that has low memory
    // requirements and thus is suitable for very large-scale problems.

    // parameters:
    //   comm: opt::CommE04RA, scalar
    //     Communication structure.
    //     An object of either the derived class opt::CommE04RA or its base class
    //     utility::NoneCopyableComm can be supplied.
    //     It is recommended that the derived class is used. If the base class is
    //     supplied it must
    //     first be initialized via a call to opt::handle_init (e04ra).
    //   objfun: void, function
    //     objfun must calculate the value of the nonlinear objective function f(x)
    //     at a specified point x

    //     parameters:
    //       x: double, array, shape(nvar)
    //         The vector x of variable values at which the objective function is to be
    //         evaluated
    //       fx: double, scalar
    //         On exit: the value of the objective function at x
    //       inform: types::f77_integer, scalar
    //         On entry: a non-negative value
    //         On exit: may be used to indicate that the function cannot be evaluated
    //         at the requested point x by setting inform < 0
    //   objgrd: void, function
    //     objgrd must calculate the values of the nonlinear objective function
    //     gradient df/dx at a specified point x

    //     parameters:
    //       x: double, array, shape(nvar)
    //         The vector x of variable values at which the objective function gradient
    //         is to be evaluated
    //       fdx: double, array, shape(nnzfd)
    //         On entry: the elements should only be assigned and not referenced
    //         On exit: the values of the nonzero elements in the sparse gradient
    //         vector of the objective function, in the order specified by idxfd in a
    //         previous call to opt::handle_set_nlnobj (e04rg)
    //       inform: types::f77_integer, scalar
    //         On entry: a non-negative value
    //         On exit: may be used to inform that the gradient cannot be evaluated at
    //         the requested point x by setting inform < 0
    //   monit: void, function
    //     monit is provided to enable you to monitor the progress of the
    //     optimization and optionally to terminate the solver early if necessary

    //     parameters:
    //       x: double, array, shape(nvar)
    //         The vector x of decision variables at the current iteration
    //       rinfo: double, array, shape(100)
    //         Error measures and various indicators at the end of the current
    //         iteration as described in rinfo
    //       stats: double, array, shape(100)
    //         Solver statistics at the end of the current iteration as described in
    //         stats
    //   nvar: types::f77_integer, scalar
    //     n, the current number of decision variables x in the model
    //   x: double, array, shape(nvar)
    //     On entry: x_0, the initial estimates of the variables, x
    //     On exit: the final values of the variables, x
    //   rinfo: double, array, shape(100)
    //     On exit, if not null on entry: error measures and various indicators at
    //     the end of the final iteration
    //   stats: double, array, shape(100)
    //     On exit, if not null on entry: solver statistics at the end of the final
    //     iteration
    //   opt: opt::OptionalE04KF
    //     Optional parameter container, derived from utility::Optional.
    //     contains:
    //       fail: error_handler::ErrorHandler

    // other parameters:
    //   Defaults: valueless
    //     This special keyword may be used to reset all options to their default
    //     values
    //   FOAS Estimate Derivatives: char
    //     Default = "NO"
    //     This option indicates whether to check for and estimate missing entries of
    //     the user-supplied gradient vector
    //   FOAS Finite Diff Interval: double
    //     Default = sqrt(epsilon)
    //     Specifies the relative perturbation size used to estimate a derivative
    //     using the forward (or backward) finite-difference method
    //   FOAS Iteration Limit: types::f77_integer
    //     Default = 10^7
    //     This parameter sets the maximum number of iterations to be performed by
    //     opt::handle_solve_bounds_foas (e04kf)
    //   FOAS Memory: types::f77_integer
    //     Default = 11
    //     This parameter specifies the maximum number of memory vectors to use in
    //     the LCG solver
    //   FOAS Monitor Frequency: types::f77_integer
    //     Default = 0
    //     This parameter specifies the frequency on which to call the monitor
    //     function monit
    //   FOAS Print Frequency: types::f77_integer
    //     Default = "1"
    //     This parameter specifies the frequency with which to print information
    //     regarding each iteration to "Print File" and/or "Monitoring File"
    //   FOAS Progress Tolerance: double
    //     Default = epsilon^(3/4)
    //     Specifies the tolerance for epsilon_prog (see [equation]) for which the
    //     function characterises a poor rate of progress given that it deems to be
    //     far from a solution
    //   FOAS Rel Stop Tolerance: double
    //     Default = epsilon^(3/4)
    //     This parameter sets the value of epsilon_rel which specifies the relative
    //     tolerance for the convergence measures in the stopping criteria, see
    //     [equation] and [equation] in Stopping Criteria
    //   FOAS Restart Factor: double
    //     Default = 6.0
    //     This factor specifies the frequency nvar*"FOAS Restart Factor" with which
    //     the CG/LCG directions are replaced by the steepest descent direction (d_k
    //     = -g_k)
    //   FOAS Slow Tolerance: double
    //     Default = epsilon^(1/8)
    //     Specifies the tolerance for epsilon_slow (see [equation]) for which the
    //     function characterises a slow rate of convergence
    //   FOAS Stop Tolerance: double
    //     Default = max(10^-6,sqrt(epsilon))
    //     This parameter sets the value of epsilon_tol which specifies the tolerance
    //     for the convergence measures in the stopping criteria, see [equation] and
    //     [equation] in Stopping Criteria
    //   FOAS Tolerance Norm: char
    //     Default = "INFINITY"
    //     This parameter specifies the norm used to measure some stopping metrics,
    //     such as optimality tolerances (see Stopping Criteria)
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
    //     solver to the primary output
    //   Print Options: char
    //     Default = "YES"
    //     If "Print Options" = "YES", a listing of options will be printed to the
    //     primary output
    //   Print Solution: char
    //     Default = "NO"
    //     If "Print Solution" = "YES", the final values of the solution vector are
    //     printed on the primary and secondary outputs
    //   Stats Time: char
    //     Default = "NO"
    //     This parameter allows you to turn on timings of various parts of the
    //     algorithm to give a better overview of where most of the time is spent
    //   Task: char
    //     Default = "MINIMIZE"
    //     This parameter specifies the required direction of the optimization
    //   Time Limit: double
    //     Default = 10^6
    //     This parameter specifies a limit in seconds that the solver can use to
    //     solve one problem
    //   Verify Derivatives: char
    //     Default = "NO"
    //     This parameter specifies whether the function should perform numerical
    //     checks on the consistency of the user-supplied gradient function

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
    //     On entry, nvar = <value>,
    //     expected value = <value>.
    //     Constraint: nvar must match the current number of variables
    //     of the model in the comm.handle.
    //   (errorid 7)
    //     Please provide a proper objfun function.
    //   (errorid 7)
    //     Please provide a proper objgrd function.
    //   (errorid 21)
    //     The current starting point is unusable.
    //   (errorid 26)
    //     User-provided gradient is likely to be incorrect.
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

    // error_handler::CallbackEarlyTermination
    //   (errorid 20)
    //     User requested termination during a monitoring step.

    // error_handler::WarningException
    //   (errorid 22)
    //     Maximum number of iterations reached.
    //   (errorid 23)
    //     The solver terminated after the maximum time allowed was exhausted.
    //   (errorid 24)
    //     The solver was terminated because no further progress could be achieved.
    //   (errorid 25)
    //     Invalid number detected in user-supplied function and recovery failed.
    //   (errorid 25)
    //     Invalid number detected in user-supplied gradient and recovery failed.
    //   (errorid 50)
    //     Problem was solved to an acceptable level; full accuracy was not achieved.
    //   (errorid 54)
    //     The problem seems to be unbounded and the algorithm was stopped.

    // error_handler::CallbackException
    //   (errorid 10701)
    //     An exception was thrown in a callback.
    //   (errorid 10702)
    //     The memory address for an array in a callback has changed.

    extern "C" {
#ifndef E04KFFT_OBJFUN
#define E04KFFT_OBJFUN                                                    \
  std::function<void(                                                     \
    const data_handling::CallbackAddresses *, types::engine_data &,       \
    const utility::array1D<double, data_handling::ArgIntent::IntentIN> &, \
    double &, types::f77_integer &)>
#endif

#if defined(_WIN32) && defined(USE_STDCALL)
#define e04kfvt_(en_data, nvar, x, fx, inform, iuser, ruser) \
  E04KFVT(en_data, nvar, x, fx, inform, iuser, ruser)
#elif defined(_WIN32) || defined(_WIN64)
#define e04kfvt_ E04KFVT
#else
#define E04KFVT e04kfvt_
#endif
    void NAG_CALL E04KFVT(types::engine_data &en_data,
                          const types::f77_integer &nvar, const double x[],
                          double &fx, types::f77_integer &inform, void *iuser,
                          void *ruser);

#ifndef E04KFFT_OBJFUNH
#define E04KFFT_OBJFUNH                                                  \
  void(NAG_CALL * objfunh)(const E04KFFT_OBJFUN &, types::engine_data &, \
                           const types::f77_integer &, const double[],   \
                           double &, types::f77_integer &, void *, void *)
#endif

#ifndef E04KFFT_OBJGRD
#define E04KFFT_OBJGRD                                                    \
  std::function<void(                                                     \
    const data_handling::CallbackAddresses *, types::engine_data &,       \
    const utility::array1D<double, data_handling::ArgIntent::IntentIN> &, \
    utility::array1D<double, data_handling::ArgIntent::IntentINOUT> &,    \
    types::f77_integer &)>
#endif

#if defined(_WIN32) && defined(USE_STDCALL)
#define e04kfwt_(en_data, nvar, x, nnzfd, fdx, inform, iuser, ruser) \
  E04KFWT(en_data, nvar, x, nnzfd, fdx, inform, iuser, ruser)
#elif defined(_WIN32) || defined(_WIN64)
#define e04kfwt_ E04KFWT
#else
#define E04KFWT e04kfwt_
#endif
    void NAG_CALL E04KFWT(types::engine_data &en_data,
                          const types::f77_integer &nvar, const double x[],
                          const types::f77_integer &nnzfd, double fdx[],
                          types::f77_integer &inform, void *iuser, void *ruser);

#ifndef E04KFFT_OBJGRDH
#define E04KFFT_OBJGRDH                                                  \
  void(NAG_CALL * objgrdh)(const E04KFFT_OBJGRD &, types::engine_data &, \
                           const types::f77_integer &, const double[],   \
                           const types::f77_integer &, double[],         \
                           types::f77_integer &, void *, void *)
#endif

#ifndef E04KFFT_MONIT
#define E04KFFT_MONIT                                                     \
  std::function<void(                                                     \
    const data_handling::CallbackAddresses *, types::engine_data &,       \
    const utility::array1D<double, data_handling::ArgIntent::IntentIN> &, \
    const utility::array1D<double, data_handling::ArgIntent::IntentIN> &, \
    const utility::array1D<double, data_handling::ArgIntent::IntentIN> &)>
#endif

#ifndef E04KFFT_MONITH
#define E04KFFT_MONITH                                                 \
  void(NAG_CALL * monith)(const E04KFFT_MONIT &, types::engine_data &, \
                          const types::f77_integer &, const double[],  \
                          types::f77_integer &, const double[],        \
                          const double[], void *, void *)
#endif

#if defined(_WIN32) && defined(USE_STDCALL)
#define e04kfft_(en_data, print_rec, print_rech, handle, objfun, objfunh,      \
                 objgrd, objgrdh, monit, monith, nvar, x, rinfo, stats, iuser, \
                 ruser, errbuf, ifail, errbuf_length)                          \
  E04KFFT(en_data, print_rec, print_rech, handle, objfun, objfunh, objgrd,     \
          objgrdh, monit, monith, nvar, x, rinfo, stats, iuser, ruser, errbuf, \
          errbuf_length, ifail)
#elif defined(_WIN32) || defined(_WIN64)
#define e04kfft_ E04KFFT
#else
#define E04KFFT e04kfft_
#endif
    extern void NAG_CALL
      E04KFFT(types::engine_data &en_data, void *print_rec, NAG_PRINT_RECH,
              void *handle, const E04KFFT_OBJFUN &, E04KFFT_OBJFUNH,
              const E04KFFT_OBJGRD &, E04KFFT_OBJGRDH, const E04KFFT_MONIT &,
              E04KFFT_MONITH, const types::f77_integer &nvar, double x[],
              double rinfo[], double stats[], void *iuser, void *ruser,
              char *errbuf NAG_STDCALL_LEN(errbuf_length),
              types::f77_integer &ifail NAG_NSTDCALL_LEN(errbuf_length));
    }

    class CommE04RA;

    class OptionalE04KF : public utility::Optional {
    public:
      OptionalE04KF() : Optional() {}
      template <typename COMM, typename OBJFUN, typename OBJGRD, typename MONIT,
                typename X, typename RINFO, typename STATS>
      friend void handle_solve_bounds_foas(COMM &comm, OBJFUN &&objfun,
                                           OBJGRD &&objgrd, MONIT &&monit,
                                           X &&x, RINFO &&rinfo, STATS &&stats,
                                           opt::OptionalE04KF &opt);
    };

    void e04kf_objfunh(const E04KFFT_OBJFUN &objfun,
                       types::engine_data &en_data,
                       const types::f77_integer &nvar, const double *x,
                       double &fx, types::f77_integer &inform, void *iuser,
                       void *ruser) {
      error_handler::ExceptionPointer *ep =
        static_cast<error_handler::ExceptionPointer *>(en_data.wrapptr1);
      utility::array1D<double, data_handling::ArgIntent::IntentIN> local_x(
        x, nvar);
      data_handling::CallbackAddresses *callbacks =
        static_cast<data_handling::CallbackAddresses *>(en_data.wrapptr2);

      try {
        if (static_cast<bool>((*callbacks).address[0])) {
          objfun(callbacks, en_data, local_x, fx, inform);
        } else {
          e04kfvt_(en_data, nvar, x, fx, inform, iuser, ruser);
        }
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

    template <typename OBJFUN_X, typename OBJFUN>
    struct e04kf_objfun_cs {
      static void run(
        const data_handling::CallbackAddresses *callbacks,
        types::engine_data &en_data,
        const utility::array1D<double, data_handling::ArgIntent::IntentIN> &x,
        double &fx, types::f77_integer &inform) {
        OBJFUN &objfun =
          *((typename std::remove_reference<OBJFUN>::type *)(*callbacks)
              .address[0]);

        auto local_x = data_handling::convert_nag_array_to_user<
          const utility::array1D<double, data_handling::ArgIntent::IntentIN>,
          data_handling::ArgIntent::IntentIN, OBJFUN_X>(x);

        objfun(local_x.get(), fx, inform);
      }
    };

    template <>
    struct e04kf_objfun_cs<std::nullptr_t, std::nullptr_t> {
      static void run(
        const data_handling::CallbackAddresses *callbacks,
        types::engine_data &en_data,
        const utility::array1D<double, data_handling::ArgIntent::IntentIN> &x,
        double &fx, types::f77_integer &inform) {
        return;
      }
    };

    void e04kf_objgrdh(const E04KFFT_OBJGRD &objgrd,
                       types::engine_data &en_data,
                       const types::f77_integer &nvar, const double *x,
                       const types::f77_integer &nnzfd, double *fdx,
                       types::f77_integer &inform, void *iuser, void *ruser) {
      error_handler::ExceptionPointer *ep =
        static_cast<error_handler::ExceptionPointer *>(en_data.wrapptr1);
      utility::array1D<double, data_handling::ArgIntent::IntentIN> local_x(
        x, nvar);
      utility::array1D<double, data_handling::ArgIntent::IntentINOUT> local_fdx(
        fdx, nnzfd);
      data_handling::CallbackAddresses *callbacks =
        static_cast<data_handling::CallbackAddresses *>(en_data.wrapptr2);

      try {
        if (static_cast<bool>((*callbacks).address[1])) {
          objgrd(callbacks, en_data, local_x, local_fdx, inform);
        } else {
          e04kfwt_(en_data, nvar, x, nnzfd, fdx, inform, iuser, ruser);
        }
      } catch (...) {
        // callback threw an exception
        en_data.hlperr = error_handler::HLPERR_USER_EXCEPTION;
        ep->eptr = std::current_exception();
      }

      if ((x != local_x.data()) && (fdx != local_fdx.data())) {
        // address of an array changed
        en_data.hlperr = error_handler::HLPERR_ARRAY_POINTER_CHANGED;
        return;
      }
    }

    template <typename OBJGRD_X, typename OBJGRD_FDX, typename OBJGRD>
    struct e04kf_objgrd_cs {
      static void run(
        const data_handling::CallbackAddresses *callbacks,
        types::engine_data &en_data,
        const utility::array1D<double, data_handling::ArgIntent::IntentIN> &x,
        utility::array1D<double, data_handling::ArgIntent::IntentINOUT> &fdx,
        types::f77_integer &inform) {
        OBJGRD &objgrd =
          *((typename std::remove_reference<OBJGRD>::type *)(*callbacks)
              .address[1]);

        auto local_x = data_handling::convert_nag_array_to_user<
          const utility::array1D<double, data_handling::ArgIntent::IntentIN>,
          data_handling::ArgIntent::IntentIN, OBJGRD_X>(x);
        auto local_fdx = data_handling::convert_nag_array_to_user<
          utility::array1D<double, data_handling::ArgIntent::IntentINOUT>,
          data_handling::ArgIntent::IntentINOUT, OBJGRD_FDX>(fdx);

        objgrd(local_x.get(), local_fdx.get(), inform);
      }
    };

    template <>
    struct e04kf_objgrd_cs<std::nullptr_t, std::nullptr_t, std::nullptr_t> {
      static void run(
        const data_handling::CallbackAddresses *callbacks,
        types::engine_data &en_data,
        const utility::array1D<double, data_handling::ArgIntent::IntentIN> &x,
        utility::array1D<double, data_handling::ArgIntent::IntentINOUT> &fdx,
        types::f77_integer &inform) {
        return;
      }
    };

    void e04kf_monith(const E04KFFT_MONIT &monit, types::engine_data &en_data,
                      const types::f77_integer &nvar, const double *x,
                      types::f77_integer &inform, const double *rinfo,
                      const double *stats, void *iuser, void *ruser) {
      error_handler::ExceptionPointer *ep =
        static_cast<error_handler::ExceptionPointer *>(en_data.wrapptr1);
      utility::array1D<double, data_handling::ArgIntent::IntentIN> local_x(
        x, nvar);
      utility::array1D<double, data_handling::ArgIntent::IntentIN> local_rinfo(
        rinfo, 100);
      utility::array1D<double, data_handling::ArgIntent::IntentIN> local_stats(
        stats, 100);
      data_handling::CallbackAddresses *callbacks =
        static_cast<data_handling::CallbackAddresses *>(en_data.wrapptr2);

      try {
        monit(callbacks, en_data, local_x, local_rinfo, local_stats);

      } catch (const error_handler::CallbackEarlyTermination &e) {
        // user threw an early termination exception
        NAG_UNUSED_PARAMETER(e);
        en_data.hlperr = 0;
        inform = -1;
        ep->eptr = std::current_exception();

      } catch (...) {
        // callback threw an exception
        en_data.hlperr = error_handler::HLPERR_USER_EXCEPTION;
        ep->eptr = std::current_exception();
      }

      if ((x != local_x.data()) && (rinfo != local_rinfo.data()) &&
          (stats != local_stats.data())) {
        // address of an array changed
        en_data.hlperr = error_handler::HLPERR_ARRAY_POINTER_CHANGED;
        return;
      }
    }

    template <typename MONIT_X, typename MONIT_RINFO, typename MONIT_STATS,
              typename MONIT>
    struct e04kf_monit_cs {
      static void run(
        const data_handling::CallbackAddresses *callbacks,
        types::engine_data &en_data,
        const utility::array1D<double, data_handling::ArgIntent::IntentIN> &x,
        const utility::array1D<double, data_handling::ArgIntent::IntentIN>
          &rinfo,
        const utility::array1D<double, data_handling::ArgIntent::IntentIN>
          &stats) {
        MONIT &monit =
          *((typename std::remove_reference<MONIT>::type *)(*callbacks)
              .address[2]);

        auto local_x = data_handling::convert_nag_array_to_user<
          const utility::array1D<double, data_handling::ArgIntent::IntentIN>,
          data_handling::ArgIntent::IntentIN, MONIT_X>(x);
        auto local_rinfo = data_handling::convert_nag_array_to_user<
          const utility::array1D<double, data_handling::ArgIntent::IntentIN>,
          data_handling::ArgIntent::IntentIN, MONIT_RINFO>(rinfo);
        auto local_stats = data_handling::convert_nag_array_to_user<
          const utility::array1D<double, data_handling::ArgIntent::IntentIN>,
          data_handling::ArgIntent::IntentIN, MONIT_STATS>(stats);

        monit(local_x.get(), local_rinfo.get(), local_stats.get());
      }
    };

    template <>
    struct e04kf_monit_cs<std::nullptr_t, std::nullptr_t, std::nullptr_t,
                          std::nullptr_t> {
      static void run(
        const data_handling::CallbackAddresses *callbacks,
        types::engine_data &en_data,
        const utility::array1D<double, data_handling::ArgIntent::IntentIN> &x,
        const utility::array1D<double, data_handling::ArgIntent::IntentIN>
          &rinfo,
        const utility::array1D<double, data_handling::ArgIntent::IntentIN>
          &stats) {
        return;
      }
    };

    template <typename COMM, typename OBJFUN, typename OBJGRD, typename MONIT,
              typename X, typename RINFO, typename STATS>
    void handle_solve_bounds_foas(COMM &comm, OBJFUN &&objfun, OBJGRD &&objgrd,
                                  MONIT &&monit, X &&x, RINFO &&rinfo,
                                  STATS &&stats, opt::OptionalE04KF &opt) {
      opt.fail.prepare("opt::handle_solve_bounds_foas (e04kf)");
      types::engine_data en_data;
      engine_routines::y90haan_(en_data);
      en_data.allocate_workspace = constants::NAG_ED_YES;
      error_handler::ExceptionPointer ep;
      en_data.wrapptr1 = &ep;
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
      data_handling::CallbackAddresses callbacks(3);
      en_data.wrapptr2 = static_cast<void *>(std::addressof(callbacks));
      callbacks.address[0] =
        callback_handling::function_to_void_pointer(objfun);
      callbacks.address[1] =
        callback_handling::function_to_void_pointer(objgrd);
      callbacks.address[2] = callback_handling::function_to_void_pointer(monit);
      data_handling::RawData<double, data_handling::ArgIntent::IntentINOUT,
                             typename std::remove_reference<X>::type>
        local_x(x);

      void *local_print_rec = static_cast<void *>(&opt.iomanager);
      using local_objfun_x_t = callback_handling::get_argument_type_t<
        0, callback_handling::argument_type_of_t<
             typename std::remove_reference<OBJFUN>::type>>;
      auto local_objfun =
        e04kf_objfun_cs<local_objfun_x_t,
                        typename std::remove_reference<OBJFUN>::type>::run;
      using local_objgrd_x_t = callback_handling::get_argument_type_t<
        0, callback_handling::argument_type_of_t<
             typename std::remove_reference<OBJGRD>::type>>;
      using local_objgrd_fdx_t = callback_handling::get_argument_type_t<
        1, callback_handling::argument_type_of_t<
             typename std::remove_reference<OBJGRD>::type>>;
      auto local_objgrd =
        e04kf_objgrd_cs<local_objgrd_x_t, local_objgrd_fdx_t,
                        typename std::remove_reference<OBJGRD>::type>::run;
      using local_monit_x_t = callback_handling::get_argument_type_t<
        0, callback_handling::argument_type_of_t<
             typename std::remove_reference<MONIT>::type>>;
      using local_monit_rinfo_t = callback_handling::get_argument_type_t<
        1, callback_handling::argument_type_of_t<
             typename std::remove_reference<MONIT>::type>>;
      using local_monit_stats_t = callback_handling::get_argument_type_t<
        2, callback_handling::argument_type_of_t<
             typename std::remove_reference<MONIT>::type>>;
      auto local_monit =
        e04kf_monit_cs<local_monit_x_t, local_monit_rinfo_t,
                       local_monit_stats_t,
                       typename std::remove_reference<MONIT>::type>::run;
      types::f77_integer local_nvar =
        data_handling::get_size(opt.fail, "nvar", local_x, 1);
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
      void *local_iuser = nullptr;
      void *local_ruser = nullptr;

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
      local_x.check(opt.fail, "x", true, local_nvar);
      if (opt.fail.error_thrown) {
        return;
      }

      e04kfft_(en_data, local_print_rec, utility::print_rech, &comm.handle,
               local_objfun, e04kf_objfunh, local_objgrd, e04kf_objgrdh,
               local_monit, e04kf_monith, local_nvar, local_x.data,
               local_rinfo.data, local_stats.data, local_iuser, local_ruser,
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
        } else if (opt.fail.ierr == 4 && opt.fail.ifmt == 401) {
          opt.fail.set_errorid(4, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "On entry, nvar = ", 1, ",");
          opt.fail.append_msg(true, "expected value = ", 2, ".");
          opt.fail.append_msg(false, "Constraint: nvar must match the current "
                                     "number of variables");
          opt.fail.append_msg(false, "of the model in the comm.handle.");
        } else if (opt.fail.ierr == 7 && opt.fail.ifmt == 703) {
          opt.fail.set_errorid(7, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "Please provide a proper objfun "
                                     "function.");
        } else if (opt.fail.ierr == 7 && opt.fail.ifmt == 704) {
          opt.fail.set_errorid(7, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "Please provide a proper objgrd "
                                     "function.");
        } else if (opt.fail.ierr == 20) {
          opt.fail.set_errorid(20, error_handler::ErrorCategory::Warning,
                               error_handler::ErrorType::GeneralWarning);
          opt.fail.append_msg(false, "User requested termination during a "
                                     "monitoring step.");
          opt.fail.append_exception_msg(en_data);
        } else if (opt.fail.ierr == 21) {
          opt.fail.set_errorid(21, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "The current starting point is unusable.");
        } else if (opt.fail.ierr == 22 && opt.fail.ifmt == 2201) {
          opt.fail.set_errorid(22, error_handler::ErrorCategory::Warning,
                               error_handler::ErrorType::GeneralWarning);
          opt.fail.append_msg(false, "Maximum number of iterations reached.");
        } else if (opt.fail.ierr == 23 && opt.fail.ifmt == 2303) {
          opt.fail.set_errorid(23, error_handler::ErrorCategory::Warning,
                               error_handler::ErrorType::GeneralWarning);
          opt.fail.append_msg(false, "The solver terminated after the maximum "
                                     "time allowed was exhausted.");
        } else if (opt.fail.ierr == 24) {
          opt.fail.set_errorid(24, error_handler::ErrorCategory::Warning,
                               error_handler::ErrorType::GeneralWarning);
          opt.fail.append_msg(false, "The solver was terminated because no "
                                     "further progress could be achieved.");
        } else if (opt.fail.ierr == 25 && opt.fail.ifmt == 2502) {
          opt.fail.set_errorid(25, error_handler::ErrorCategory::Warning,
                               error_handler::ErrorType::GeneralWarning);
          opt.fail.append_msg(false, "Invalid number detected in user-supplied "
                                     "function and recovery failed.");
        } else if (opt.fail.ierr == 25 && opt.fail.ifmt == 2503) {
          opt.fail.set_errorid(25, error_handler::ErrorCategory::Warning,
                               error_handler::ErrorType::GeneralWarning);
          opt.fail.append_msg(false, "Invalid number detected in user-supplied "
                                     "gradient and recovery failed.");
        } else if (opt.fail.ierr == 26) {
          opt.fail.set_errorid(26, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "User-provided gradient is likely to be "
                                     "incorrect.");
        } else if (opt.fail.ierr == 50) {
          opt.fail.set_errorid(50, error_handler::ErrorCategory::Warning,
                               error_handler::ErrorType::GeneralWarning);
          opt.fail.append_msg(false, "Problem was solved to an acceptable "
                                     "level; full accuracy was not achieved.");
        } else if (opt.fail.ierr == 54) {
          opt.fail.set_errorid(54, error_handler::ErrorCategory::Warning,
                               error_handler::ErrorType::GeneralWarning);
          opt.fail.append_msg(false, "The problem seems to be unbounded and "
                                     "the algorithm was stopped.");
        } else {
          opt.fail.set_unexpected_error();
        }
        opt.fail.throw_error();
      }
      if (opt.fail.error_thrown) {
        return;
      }

      local_x.copy_back(x);
      local_rinfo.copy_back(rinfo);
      local_stats.copy_back(stats);
      opt.fail.throw_warning();
    }

    // alt-1
    template <typename COMM, typename OBJFUN, typename OBJGRD, typename MONIT,
              typename X, typename RINFO, typename STATS>
    void handle_solve_bounds_foas(COMM &comm, OBJFUN &&objfun, OBJGRD &&objgrd,
                                  MONIT &&monit, X &&x, RINFO &&rinfo,
                                  STATS &&stats) {
      opt::OptionalE04KF local_opt;

      handle_solve_bounds_foas(comm, objfun, objgrd, monit, x, rinfo, stats,
                               local_opt);
    }
  }
}
#define e04kf opt::handle_solve_bounds_foas
#endif
