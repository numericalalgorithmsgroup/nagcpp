// Header for the communication class for routines who need to be initialized
// via a call to nagcpp::opt::nlp1_init (e04wb)

// Copyright 2021, Numerical Algorithms Group Ltd, Oxford, UK.
// Generated by cpp-ft-wrapper.xsl
// Version 27.3.0.0
#ifndef NAGCPP_COMME04WB
#define NAGCPP_COMME04WB

#include "e04/nagcpp_e04ue.hpp"
#include "e04/nagcpp_e04wb.hpp"
#include "utility/nagcpp_utility_comm.hpp"
#include "utility/nagcpp_utility_functions.hpp"

namespace nagcpp {
  namespace opt {
    class CommE04WB : public utility::CopyableComm {
    public:
      CommE04WB(const std::string rname, opt::OptionalE04WB &opt)
        : CopyableComm() {
        nlp1_init(rname, (*this), opt);
      }
      CommE04WB(const std::string rname) : CopyableComm() {
        nlp1_init(rname, (*this));
      }
      ~CommE04WB() {}
      CommE04WB &set(const std::string str, opt::OptionalE04UE &opt) {
        nlp1_option_string(str, (*this), opt);
        return (*this);
      }
      CommE04WB &set(const std::string str) {
        nlp1_option_string(str, (*this));
        return (*this);
      }

      // Central Difference Interval:
      //   Default values are computed
      //   If the algorithm switches to central differences because the
      //   forward-difference approximation is not sufficiently accurate, the value of
      //   r is used as the difference interval for every element of x
      CommE04WB &CentralDifferenceInterval(double value,
                                           opt::OptionalE04UE &opt) {
        std::string local_optstr =
          utility::set_optstr("Central Difference Interval", value);
        nlp1_option_string(local_optstr, (*this), opt);
        return (*this);
      }
      CommE04WB &CentralDifferenceInterval(double value) {
        opt::OptionalE04UE local_opt;
        return CentralDifferenceInterval(value, local_opt);
      }

      // Cold Start:
      //   Default
      //   This option controls the specification of the initial working set in both
      //   the procedure for finding a feasible point for the linear constraints and
      //   bounds and in the first QP subproblem thereafter
      CommE04WB &ColdStart(opt::OptionalE04UE &opt) {
        std::string local_optstr = "Cold Start";
        nlp1_option_string(local_optstr, (*this), opt);
        return (*this);
      }
      CommE04WB &ColdStart(void) {
        opt::OptionalE04UE local_opt;
        return ColdStart(local_opt);
      }

      // Crash Tolerance:
      //   Default = 0.01
      //   The behaviour of this parameter is solver dependent. Please refer to the
      //   individual solver documentation.
      CommE04WB &CrashTolerance(double value, opt::OptionalE04UE &opt) {
        std::string local_optstr =
          utility::set_optstr("Crash Tolerance", value);
        nlp1_option_string(local_optstr, (*this), opt);
        return (*this);
      }
      CommE04WB &CrashTolerance(double value) {
        opt::OptionalE04UE local_opt;
        return CrashTolerance(value, local_opt);
      }

      // Defaults:
      //   This special keyword may be used to reset all options to their default
      //   values
      CommE04WB &Defaults(opt::OptionalE04UE &opt) {
        std::string local_optstr = "Defaults";
        nlp1_option_string(local_optstr, (*this), opt);
        return (*this);
      }
      CommE04WB &Defaults(void) {
        opt::OptionalE04UE local_opt;
        return Defaults(local_opt);
      }

      // Derivative Level:
      //   Default = 3
      //   The behaviour of this parameter is solver dependent. Please refer to the
      //   individual solver documentation.
      CommE04WB &DerivativeLevel(types::f77_integer value,
                                 opt::OptionalE04UE &opt) {
        std::string local_optstr =
          utility::set_optstr("Derivative Level", value);
        nlp1_option_string(local_optstr, (*this), opt);
        return (*this);
      }
      CommE04WB &DerivativeLevel(types::f77_integer value) {
        opt::OptionalE04UE local_opt;
        return DerivativeLevel(value, local_opt);
      }

      // Difference Interval:
      //   Default values are computed
      //   This option defines an interval used to estimate derivatives by finite
      //   differences in the following circumstances
      CommE04WB &DifferenceInterval(double value, opt::OptionalE04UE &opt) {
        std::string local_optstr =
          utility::set_optstr("Difference Interval", value);
        nlp1_option_string(local_optstr, (*this), opt);
        return (*this);
      }
      CommE04WB &DifferenceInterval(double value) {
        opt::OptionalE04UE local_opt;
        return DifferenceInterval(value, local_opt);
      }

      // Feasibility Tolerance:
      //   Default = sqrt(epsilon)
      //   The scalar r defines the maximum acceptable absolute violations in linear
      //   and nonlinear constraints at a "feasible" point; i.e., a constraint is
      //   considered satisfied if its violation does not exceed r
      CommE04WB &FeasibilityTolerance(double value, opt::OptionalE04UE &opt) {
        std::string local_optstr =
          utility::set_optstr("Feasibility Tolerance", value);
        nlp1_option_string(local_optstr, (*this), opt);
        return (*this);
      }
      CommE04WB &FeasibilityTolerance(double value) {
        opt::OptionalE04UE local_opt;
        return FeasibilityTolerance(value, local_opt);
      }

      // Function Precision:
      //   Default = epsilon^0.9
      //   This parameter defines epsilon_r, which is intended to be a measure of the
      //   accuracy with which the problem functions F(x) and c(x) can be computed
      CommE04WB &FunctionPrecision(double value, opt::OptionalE04UE &opt) {
        std::string local_optstr =
          utility::set_optstr("Function Precision", value);
        nlp1_option_string(local_optstr, (*this), opt);
        return (*this);
      }
      CommE04WB &FunctionPrecision(double value) {
        opt::OptionalE04UE local_opt;
        return FunctionPrecision(value, local_opt);
      }

      // Hessian:
      //   Default = NO
      //   This option controls the contents of the upper triangular matrix R (see
      //   Arguments)
      CommE04WB &Hessian(std::string value, opt::OptionalE04UE &opt) {
        std::string local_optstr = utility::set_optstr("Hessian", value);
        nlp1_option_string(local_optstr, (*this), opt);
        return (*this);
      }
      CommE04WB &Hessian(std::string value) {
        opt::OptionalE04UE local_opt;
        return Hessian(value, local_opt);
      }

      // Infinite Bound Size:
      //   Default = 10^20
      //   If r > 0, r defines the "infinite" bound bigbnd in the definition of the
      //   problem constraints
      CommE04WB &InfiniteBoundSize(double value, opt::OptionalE04UE &opt) {
        std::string local_optstr =
          utility::set_optstr("Infinite Bound Size", value);
        nlp1_option_string(local_optstr, (*this), opt);
        return (*this);
      }
      CommE04WB &InfiniteBoundSize(double value) {
        opt::OptionalE04UE local_opt;
        return InfiniteBoundSize(value, local_opt);
      }

      // Infinite Step Size:
      //   Default = max(bigbnd, 10^20)
      //   If r > 0, r specifies the magnitude of the change in variables that is
      //   treated as a step to an unbounded solution
      CommE04WB &InfiniteStepSize(double value, opt::OptionalE04UE &opt) {
        std::string local_optstr =
          utility::set_optstr("Infinite Step Size", value);
        nlp1_option_string(local_optstr, (*this), opt);
        return (*this);
      }
      CommE04WB &InfiniteStepSize(double value) {
        opt::OptionalE04UE local_opt;
        return InfiniteStepSize(value, local_opt);
      }

      // Iteration Limit:
      //   Please refer to the individual solver documentation.
      //   The value of i specifies the maximum number of major iterations allowed
      //   before termination
      CommE04WB &IterationLimit(types::f77_integer value,
                                opt::OptionalE04UE &opt) {
        std::string local_optstr =
          utility::set_optstr("Iteration Limit", value);
        nlp1_option_string(local_optstr, (*this), opt);
        return (*this);
      }
      CommE04WB &IterationLimit(types::f77_integer value) {
        opt::OptionalE04UE local_opt;
        return IterationLimit(value, local_opt);
      }

      // Iters:
      //   Please refer to the individual solver documentation.
      //   The value of i specifies the maximum number of major iterations allowed
      //   before termination
      CommE04WB &Iters(types::f77_integer value, opt::OptionalE04UE &opt) {
        std::string local_optstr = utility::set_optstr("Iters", value);
        nlp1_option_string(local_optstr, (*this), opt);
        return (*this);
      }
      CommE04WB &Iters(types::f77_integer value) {
        opt::OptionalE04UE local_opt;
        return Iters(value, local_opt);
      }

      // Itns:
      //   Please refer to the individual solver documentation.
      //   The value of i specifies the maximum number of major iterations allowed
      //   before termination
      CommE04WB &Itns(types::f77_integer value, opt::OptionalE04UE &opt) {
        std::string local_optstr = utility::set_optstr("Itns", value);
        nlp1_option_string(local_optstr, (*this), opt);
        return (*this);
      }
      CommE04WB &Itns(types::f77_integer value) {
        opt::OptionalE04UE local_opt;
        return Itns(value, local_opt);
      }

      // Line Search Tolerance:
      //   Default = 0.9
      //   The value r (0 <= r < 1) controls the accuracy with which the step alpha
      //   taken during each iteration approximates a minimum of the merit function
      //   along the search direction (the smaller the value of r, the more accurate
      //   the linesearch)
      CommE04WB &LineSearchTolerance(double value, opt::OptionalE04UE &opt) {
        std::string local_optstr =
          utility::set_optstr("Line Search Tolerance", value);
        nlp1_option_string(local_optstr, (*this), opt);
        return (*this);
      }
      CommE04WB &LineSearchTolerance(double value) {
        opt::OptionalE04UE local_opt;
        return LineSearchTolerance(value, local_opt);
      }

      // Linear Feasibility Tolerance:
      //   Default = sqrt(epsilon)
      //   The default value of r_2 is epsilon^0.33 if "Derivative Level" = 0 or 1,
      //   and sqrt(epsilon) otherwise
      CommE04WB &LinearFeasibilityTolerance(double value,
                                            opt::OptionalE04UE &opt) {
        std::string local_optstr =
          utility::set_optstr("Linear Feasibility Tolerance", value);
        nlp1_option_string(local_optstr, (*this), opt);
        return (*this);
      }
      CommE04WB &LinearFeasibilityTolerance(double value) {
        opt::OptionalE04UE local_opt;
        return LinearFeasibilityTolerance(value, local_opt);
      }

      // List:
      //   Option "List" enables printing of each option specification as it is
      //   supplied
      CommE04WB &List(opt::OptionalE04UE &opt) {
        std::string local_optstr = "List";
        nlp1_option_string(local_optstr, (*this), opt);
        return (*this);
      }
      CommE04WB &List(void) {
        opt::OptionalE04UE local_opt;
        return List(local_opt);
      }

      // Major Iteration Limit:
      //   Please refer to the individual solver documentation.
      //   The value of i specifies the maximum number of major iterations allowed
      //   before termination
      CommE04WB &MajorIterationLimit(types::f77_integer value,
                                     opt::OptionalE04UE &opt) {
        std::string local_optstr =
          utility::set_optstr("Major Iteration Limit", value);
        nlp1_option_string(local_optstr, (*this), opt);
        return (*this);
      }
      CommE04WB &MajorIterationLimit(types::f77_integer value) {
        opt::OptionalE04UE local_opt;
        return MajorIterationLimit(value, local_opt);
      }

      // Major Print Level:
      //   The behaviour of this parameter is solver dependent. Please refer to the
      //   individual solver documentation.
      CommE04WB &MajorPrintLevel(types::f77_integer value,
                                 opt::OptionalE04UE &opt) {
        std::string local_optstr =
          utility::set_optstr("Major Print Level", value);
        nlp1_option_string(local_optstr, (*this), opt);
        return (*this);
      }
      CommE04WB &MajorPrintLevel(types::f77_integer value) {
        opt::OptionalE04UE local_opt;
        return MajorPrintLevel(value, local_opt);
      }

      // Minor Iteration Limit:
      //   Default = max(50, 3*(n+n_L+n_N))
      //   The value of i specifies the maximum number of iterations for finding a
      //   feasible point with respect to the bounds and linear constraints (if any)
      CommE04WB &MinorIterationLimit(types::f77_integer value,
                                     opt::OptionalE04UE &opt) {
        std::string local_optstr =
          utility::set_optstr("Minor Iteration Limit", value);
        nlp1_option_string(local_optstr, (*this), opt);
        return (*this);
      }
      CommE04WB &MinorIterationLimit(types::f77_integer value) {
        opt::OptionalE04UE local_opt;
        return MinorIterationLimit(value, local_opt);
      }

      // Minor Print Level:
      //   Default = 0
      //   The behaviour of this parameter is solver dependent. Please refer to the
      //   individual solver documentation.
      CommE04WB &MinorPrintLevel(types::f77_integer value,
                                 opt::OptionalE04UE &opt) {
        std::string local_optstr =
          utility::set_optstr("Minor Print Level", value);
        nlp1_option_string(local_optstr, (*this), opt);
        return (*this);
      }
      CommE04WB &MinorPrintLevel(types::f77_integer value) {
        opt::OptionalE04UE local_opt;
        return MinorPrintLevel(value, local_opt);
      }

      // Monitoring File:
      //   Default = -1
      //   The behaviour of this parameter is solver dependent. Please refer to the
      //   individual solver documentation.
      CommE04WB &MonitoringFile(types::f77_integer value,
                                opt::OptionalE04UE &opt) {
        std::string local_optstr =
          utility::set_optstr("Monitoring File", value);
        nlp1_option_string(local_optstr, (*this), opt);
        return (*this);
      }
      CommE04WB &MonitoringFile(types::f77_integer value) {
        opt::OptionalE04UE local_opt;
        return MonitoringFile(value, local_opt);
      }

      // Nolist:
      //   Please refer to the individual solver documentation.
      //   Option "List" enables printing of each option specification as it is
      //   supplied
      CommE04WB &Nolist(opt::OptionalE04UE &opt) {
        std::string local_optstr = "Nolist";
        nlp1_option_string(local_optstr, (*this), opt);
        return (*this);
      }
      CommE04WB &Nolist(void) {
        opt::OptionalE04UE local_opt;
        return Nolist(local_opt);
      }

      // Nonlinear Feasibility Tolerance:
      //   Default = epsilon^0.33 or sqrt(epsilon)
      //   The default value of r_2 is epsilon^0.33 if "Derivative Level" = 0 or 1,
      //   and sqrt(epsilon) otherwise
      CommE04WB &NonlinearFeasibilityTolerance(double value,
                                               opt::OptionalE04UE &opt) {
        std::string local_optstr =
          utility::set_optstr("Nonlinear Feasibility Tolerance", value);
        nlp1_option_string(local_optstr, (*this), opt);
        return (*this);
      }
      CommE04WB &NonlinearFeasibilityTolerance(double value) {
        opt::OptionalE04UE local_opt;
        return NonlinearFeasibilityTolerance(value, local_opt);
      }

      // Optimality Tolerance:
      //   Default = epsilon_r^0.8
      //   The parameter r (epsilon_r <= r < 1) specifies the accuracy to which you
      //   wish the final iterate to approximate a solution of the problem
      CommE04WB &OptimalityTolerance(double value, opt::OptionalE04UE &opt) {
        std::string local_optstr =
          utility::set_optstr("Optimality Tolerance", value);
        nlp1_option_string(local_optstr, (*this), opt);
        return (*this);
      }
      CommE04WB &OptimalityTolerance(double value) {
        opt::OptionalE04UE local_opt;
        return OptimalityTolerance(value, local_opt);
      }

      // Print Level:
      //   Please refer to the individual solver documentation.
      //   The behaviour of this parameter is solver dependent. Please refer to the
      //   individual solver documentation.
      CommE04WB &PrintLevel(types::f77_integer value, opt::OptionalE04UE &opt) {
        std::string local_optstr = utility::set_optstr("Print Level", value);
        nlp1_option_string(local_optstr, (*this), opt);
        return (*this);
      }
      CommE04WB &PrintLevel(types::f77_integer value) {
        opt::OptionalE04UE local_opt;
        return PrintLevel(value, local_opt);
      }

      // Start Constraint Check At Variable:
      //   Default = 1
      //   These keywords take effect only if "Verify Level" > 0
      CommE04WB &StartConstraintCheckAtVariable(types::f77_integer value,
                                                opt::OptionalE04UE &opt) {
        std::string local_optstr =
          utility::set_optstr("Start Constraint Check At Variable", value);
        nlp1_option_string(local_optstr, (*this), opt);
        return (*this);
      }
      CommE04WB &StartConstraintCheckAtVariable(types::f77_integer value) {
        opt::OptionalE04UE local_opt;
        return StartConstraintCheckAtVariable(value, local_opt);
      }

      // Start Objective Check At Variable:
      //   Default = 1
      //   These keywords take effect only if "Verify Level" > 0
      CommE04WB &StartObjectiveCheckAtVariable(types::f77_integer value,
                                               opt::OptionalE04UE &opt) {
        std::string local_optstr =
          utility::set_optstr("Start Objective Check At Variable", value);
        nlp1_option_string(local_optstr, (*this), opt);
        return (*this);
      }
      CommE04WB &StartObjectiveCheckAtVariable(types::f77_integer value) {
        opt::OptionalE04UE local_opt;
        return StartObjectiveCheckAtVariable(value, local_opt);
      }

      // Step Limit:
      //   Default = 2.0
      //   If r > 0,r specifies the maximum change in variables at the first step of
      //   the linesearch
      CommE04WB &StepLimit(double value, opt::OptionalE04UE &opt) {
        std::string local_optstr = utility::set_optstr("Step Limit", value);
        nlp1_option_string(local_optstr, (*this), opt);
        return (*this);
      }
      CommE04WB &StepLimit(double value) {
        opt::OptionalE04UE local_opt;
        return StepLimit(value, local_opt);
      }

      // Stop Constraint Check At Variable:
      //   Default = n
      //   These keywords take effect only if "Verify Level" > 0
      CommE04WB &StopConstraintCheckAtVariable(types::f77_integer value,
                                               opt::OptionalE04UE &opt) {
        std::string local_optstr =
          utility::set_optstr("Stop Constraint Check At Variable", value);
        nlp1_option_string(local_optstr, (*this), opt);
        return (*this);
      }
      CommE04WB &StopConstraintCheckAtVariable(types::f77_integer value) {
        opt::OptionalE04UE local_opt;
        return StopConstraintCheckAtVariable(value, local_opt);
      }

      // Stop Objective Check At Variable:
      //   Default = n
      //   These keywords take effect only if "Verify Level" > 0
      CommE04WB &StopObjectiveCheckAtVariable(types::f77_integer value,
                                              opt::OptionalE04UE &opt) {
        std::string local_optstr =
          utility::set_optstr("Stop Objective Check At Variable", value);
        nlp1_option_string(local_optstr, (*this), opt);
        return (*this);
      }
      CommE04WB &StopObjectiveCheckAtVariable(types::f77_integer value) {
        opt::OptionalE04UE local_opt;
        return StopObjectiveCheckAtVariable(value, local_opt);
      }

      // Verify:
      //   The behaviour of this parameter is solver dependent. Please refer to the
      //   individual solver documentation.
      CommE04WB &Verify(opt::OptionalE04UE &opt) {
        std::string local_optstr = "Verify";
        nlp1_option_string(local_optstr, (*this), opt);
        return (*this);
      }
      CommE04WB &Verify(void) {
        opt::OptionalE04UE local_opt;
        return Verify(local_opt);
      }

      // Verify Constraint Gradients:
      //   The behaviour of this parameter is solver dependent. Please refer to the
      //   individual solver documentation.
      CommE04WB &VerifyConstraintGradients(opt::OptionalE04UE &opt) {
        std::string local_optstr = "Verify Constraint Gradients";
        nlp1_option_string(local_optstr, (*this), opt);
        return (*this);
      }
      CommE04WB &VerifyConstraintGradients(void) {
        opt::OptionalE04UE local_opt;
        return VerifyConstraintGradients(local_opt);
      }

      // Verify Gradients:
      //   The behaviour of this parameter is solver dependent. Please refer to the
      //   individual solver documentation.
      CommE04WB &VerifyGradients(opt::OptionalE04UE &opt) {
        std::string local_optstr = "Verify Gradients";
        nlp1_option_string(local_optstr, (*this), opt);
        return (*this);
      }
      CommE04WB &VerifyGradients(void) {
        opt::OptionalE04UE local_opt;
        return VerifyGradients(local_opt);
      }

      // Verify Level:
      //   Default = 0
      //   The behaviour of this parameter is solver dependent. Please refer to the
      //   individual solver documentation.
      CommE04WB &VerifyLevel(types::f77_integer value,
                             opt::OptionalE04UE &opt) {
        std::string local_optstr = utility::set_optstr("Verify Level", value);
        nlp1_option_string(local_optstr, (*this), opt);
        return (*this);
      }
      CommE04WB &VerifyLevel(types::f77_integer value) {
        opt::OptionalE04UE local_opt;
        return VerifyLevel(value, local_opt);
      }

      // Verify Objective Gradients:
      //   The behaviour of this parameter is solver dependent. Please refer to the
      //   individual solver documentation.
      CommE04WB &VerifyObjectiveGradients(opt::OptionalE04UE &opt) {
        std::string local_optstr = "Verify Objective Gradients";
        nlp1_option_string(local_optstr, (*this), opt);
        return (*this);
      }
      CommE04WB &VerifyObjectiveGradients(void) {
        opt::OptionalE04UE local_opt;
        return VerifyObjectiveGradients(local_opt);
      }

      // Warm Start:
      //   This option controls the specification of the initial working set in both
      //   the procedure for finding a feasible point for the linear constraints and
      //   bounds and in the first QP subproblem thereafter
      CommE04WB &WarmStart(opt::OptionalE04UE &opt) {
        std::string local_optstr = "Warm Start";
        nlp1_option_string(local_optstr, (*this), opt);
        return (*this);
      }
      CommE04WB &WarmStart(void) {
        opt::OptionalE04UE local_opt;
        return WarmStart(local_opt);
      }
    };
  }
}
#endif
