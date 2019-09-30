// example of using:
//   nagcpp::opt::handle_solve_lp_ipm (e04mt)
//   nagcpp::opt::handle_set_quadobj (e04rf)
//   nagcpp::opt::handle_set_simplebounds (e04rh)
//   nagcpp::opt::handle_set_linconstr (e04rj)
// in addition, the following routines are implicitly
// called via the communication class:
//   nagcpp::opt::handle_init (e04ra)
//   nagcpp::opt::handle_opt_set (e04zm)
//   nagcpp::opt::handle_free (e04rz)
#include <iostream>
#include <math.h>
#include <vector>

#include "e04/nagcpp_class_CommE04RA.hpp"
#include "e04/nagcpp_e04mt.hpp"
#include "e04/nagcpp_e04rf.hpp"
#include "e04/nagcpp_e04rh.hpp"
#include "e04/nagcpp_e04rj.hpp"

int main(void) {
  std::cout << "nagcpp::opt::handle_solve_lp_ipm Example" << std::endl;

  try {
    nagcpp::types::f77_integer nvar = 7;

    // initialise the problem handle
    nagcpp::opt::CommE04RA handle(nvar);

    // set objective function (e04rf)
    std::vector<nagcpp::types::f77_integer> idxc = {1, 2, 3, 4, 5, 6, 7};
    std::vector<double> c = {-0.02, -0.20, -0.20, -0.20, -0.20, 0.04, 0.04};
    nagcpp::opt::handle_set_quadobj(handle, idxc, c, nullptr, nullptr, nullptr);

    // set box constraints (e04rh)
    std::vector<double> xl = {-0.01, -0.1, -0.01, -0.04, -0.1, -0.01, -0.01};
    std::vector<double> xu = {0.01, 0.15, 0.03, 0.02, 0.05, 1.0e20, 1.0e20};
    nagcpp::opt::handle_set_simplebounds(handle, xl, xu);

    // set linear constraints (e04rj)
    std::vector<double> bla = {-0.13,   -1.0e20, -1.0e20, -1.0e20,
                               -1.0e20, -0.0992, -0.003};
    std::vector<double> bua = {-0.13,   -0.0049, -0.0064, -0.0037,
                               -0.0012, 1.0e20,  0.002};
    std::vector<nagcpp::types::f77_integer> irowa = {
      1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 4,
      4, 4, 4, 4, 5, 5, 5, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7};
    std::vector<nagcpp::types::f77_integer> icola = {
      1, 2, 3, 4, 5, 6, 7, 1, 2, 3, 4, 5, 6, 7, 1, 2, 3, 4, 5, 6, 1,
      2, 3, 4, 5, 1, 2, 5, 1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6, 7};
    std::vector<double> a = {1.00, 1.00, 1.00, 1.00, 1.00, 1.00, 1.00,
                             0.15, 0.04, 0.02, 0.04, 0.02, 0.01, 0.03,
                             0.03, 0.05, 0.08, 0.02, 0.06, 0.01, 0.02,
                             0.04, 0.01, 0.02, 0.02, 0.02, 0.03, 0.01,
                             0.70, 0.75, 0.80, 0.75, 0.80, 0.97, 0.02,
                             0.06, 0.08, 0.12, 0.02, 0.01, 0.97};
    nagcpp::opt::handle_set_linconstr(handle, bla, bua, irowa, icola, a);

    // turn on monitoring
    handle.LPIPMMonitorFrequency(1);

    // require a high accuracy solution
    handle.LPIPMStopTolerance(1.0e-10);

    // require printing of the solution at the end of the solve
    handle.PrintSolution("YES");

    // use a constant number of centrality correctors steps
    handle.LPIPMCentralityCorrectors(-6);

    // use a custom monitoring function
    std::string ptype = "Primal-Dual";
    auto monit =
      [&](nagcpp::opt::CommE04RA &comm,
          const nagcpp::utility::array1D<double, nagcpp::data_handling::IN>
            &rinfo,
          const nagcpp::utility::array1D<double, nagcpp::data_handling::IN>
            &stats) {
        double tol = 1.2e-8;
        bool good_solution;
        if (ptype == "Primal-Dual") {
          good_solution = (rinfo(4) < tol && rinfo(5) < tol && rinfo(6) < tol);
        } else {
          good_solution = (rinfo(14) < tol && rinfo(15) < tol &&
                           rinfo(16) < tol && rinfo(17) < tol);
        }
        if (good_solution) {
          std::cout << "Iteration " << static_cast<int>(stats(0)) << std::endl;
          std::cout << "monit() reports good approximate solution (tol = "
                    << tol << "):" << std::endl;
        }
      };

    std::vector<double> x;
    std::vector<double> u;
    std::vector<double> rinfo;
    std::vector<double> stats;

    // call LP interior point solver with the default (primal-dual) algorithm
    handle_solve_lp_ipm(handle, x, u, rinfo, stats, monit);

  } catch (nagcpp::error_handler::Exception &e) {
    std::cout << e.msg << std::endl;
    return 1;
  }

  return 0;
}
