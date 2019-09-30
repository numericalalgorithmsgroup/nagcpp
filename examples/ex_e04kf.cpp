// example of using:
//   nagcpp::opt::handle_solve_bounds_foas (e04kf)
//   nagcpp::opt::handle_set_simplebounds (e04rh)
//   nagcpp::opt::handle_set_nlnobj (e04rg)
// in addition, the following routines are implicitly
// called via the communication class:
//   nagcpp::opt::handle_init (e04ra)
//   nagcpp::opt::handle_opt_set (e04zm)
//   nagcpp::opt::handle_free (e04rz)
#include <iomanip>
#include <iostream>
#include <math.h>
#include <numeric>
#include <sstream>
#include <vector>

#include "e04/nagcpp_class_CommE04RA.hpp"
#include "e04/nagcpp_e04kf.hpp"
#include "e04/nagcpp_e04rg.hpp"
#include "e04/nagcpp_e04rh.hpp"

void objfun(const std::vector<double> &x, double &fx,
            const nagcpp::types::f77_integer inform) {
  // Rosenbrock function
  fx = pow(1.0 - x[0], 2) + 100.0 * pow(x[1] - pow(x[0], 2), 2);
}

void objgrd(const std::vector<double> &x, std::vector<double> &fdx,
            const nagcpp::types::f77_integer inform) {
  fdx[0] = 2.0 * x[0] - 400.0 * x[0] * (x[1] - pow(x[0], 2)) - 2.0;
  fdx[1] = 200.0 * (x[1] - pow(x[0], 2));
}

int main(void) {
  std::cout << "nagcpp::opt::handle_solve_bounds_foas Example" << std::endl
            << std::endl;

  try {
    nagcpp::types::f77_integer nvar = 2;

    // initialise the problem handle
    nagcpp::opt::CommE04RA handle(nvar);

    // define simple box bounds (e04rh)
    std::vector<double> blx = {-1.0, -2.0};
    std::vector<double> bux = {0.8, 2.0};
    nagcpp::opt::handle_set_simplebounds(handle, blx, bux);

    // add nonlinear objective information (e04rg)
    std::vector<nagcpp::types::f77_integer> iidx(nvar);
    std::iota(iidx.begin(), iidx.end(), 1);
    nagcpp::opt::handle_set_nlnobj(handle, iidx);

    // as an example, we are going to send monitoring output to a string buffer
    std::stringstream monitoring_buffer;

    // register the string buffer to the global IO manager
    // an alternative to using the global IO manager is to create
    // a local instance and pass that to the routines via the
    // optional parameters argument
    nagcpp::types::f77_integer monitoring_unit_number =
      nagcpp::iomanager::GLOBAL_IOMANAGER->register_ostream(monitoring_buffer);

    // turn on printing
    handle.PrintLevel(1);
    handle.PrintSolution("yes");

    // don't print the options
    // (they are output by the default monitoring function)
    handle.PrintOptions("no");

    // turn on monitoring
    handle.MonitoringLevel(3);
    handle.MonitoringFile(monitoring_unit_number);

    // set some control parameters
    handle.FOASPrintFrequency(5);

    // initial values for variable
    std::vector<double> x = {-1.5, 1.9};

    std::vector<double> u;
    std::vector<double> rinfo;
    std::vector<double> stats;

    // we are going to be using the default values for the optional
    // arguments, however we want to print out any warning messages
    nagcpp::opt::OptionalE04KF opt;

    // call the solver
    nagcpp::opt::handle_solve_bounds_foas(handle, objfun, objgrd, nullptr, x,
                                          rinfo, stats, opt);
    if (opt.fail.warning_thrown) {
      std::cout << std::endl << opt.fail.msg << std::endl << std::endl;
    }

    std::cout << "Solution found: " << std::endl;
    std::cout.precision(1);
    std::cout.setf(std::ios::scientific);
    std::cout << "   Objective function value at solution: " << std::setw(9)
              << rinfo[0] << std::endl;

    // output the monitoring information from the string buffer
    std::cout << std::endl;
    std::cout << "Monitoring Information:" << std::endl;
    std::cout << monitoring_buffer.str() << std::endl;

  } catch (nagcpp::error_handler::Exception &e) {
    std::cout << e.msg << std::endl;
    return 1;
  }

  return 0;
}
