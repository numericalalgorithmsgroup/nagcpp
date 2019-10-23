// example of using:
//   nagcpp::opt::handle_solve_socp_ipm (e04pt)
//   nagcpp::opt::handle_set_linobj (e04re)
//   nagcpp::opt::handle_set_simplebounds (e04rh)
//   nagcpp::opt::handle_set_linconstr (e04rj)
//   nagcpp::opt::handle_set_group (e04rb)
// in addition, the following routines are implicitly
// called via the communication class:
//   nagcpp::opt::handle_init (e04ra)
//   nagcpp::opt::handle_opt_set (e04zm)
//   nagcpp::opt::handle_free (e04rz)
#include <iomanip>
#include <iostream>
#include <vector>

#include "e04/nagcpp_class_CommE04RA.hpp"
#include "e04/nagcpp_e04pt.hpp"
#include "e04/nagcpp_e04rb.hpp"
#include "e04/nagcpp_e04re.hpp"
#include "e04/nagcpp_e04rh.hpp"
#include "e04/nagcpp_e04rj.hpp"

int main(void) {
  std::cout << "nagcpp::opt::handle_solve_socp_ipm Example" << std::endl;

  try {
    // initialise the problem handle
    nagcpp::types::f77_integer n = 3;
    nagcpp::opt::CommE04RA handle(n);

    // set objective function (e04re)
    std::vector<double> c = {10.0, 20.0, 1.0};
    nagcpp::opt::handle_set_linobj(handle, c);

    // set box constraints (e04rh)
    std::vector<double> xl = {-2.0, -2.0, -1.0e20};
    std::vector<double> xu = {2.0, 2.0, 1.0e20};
    nagcpp::opt::handle_set_simplebounds(handle, xl, xu);

    // set linear constraints (e04rj)
    std::vector<double> bla = {-1.0e20, 1.0};
    std::vector<double> bua = {1.5, 1.0e20};
    std::vector<nagcpp::types::f77_integer> irowa = {1, 1, 1, 2, 2, 2};
    std::vector<nagcpp::types::f77_integer> icola = {1, 2, 3, 1, 2, 3};
    std::vector<double> a = {-0.1, -0.1, 1.0, -0.06, 1.0, 1.0};
    nagcpp::opt::handle_set_linconstr(handle, bla, bua, irowa, icola, a);

    // create the cone constraints (e04rb)
    std::string cone_type = "QUAD";
    std::vector<nagcpp::types::f77_integer> vidx_cone = {3, 1, 2};
    nagcpp::types::f77_integer idgroup = 0;
    nagcpp::opt::handle_set_group(handle, cone_type, vidx_cone, idgroup);

    // turn off printing of intermediate progress output
    handle.PrintLevel(1);

    std::vector<double> x;
    std::vector<double> u;
    std::vector<double> uc;
    std::vector<double> rinfo;
    std::vector<double> stats;

    // call SOCP interior point solver (e04pt)
    handle_solve_socp_ipm(handle, x, u, uc, rinfo, stats, nullptr);

    // print the solution
    std::cout << std::endl;
    std::cout << "Optional X:" << std::endl;
    std::cout << "  i         Value" << std::endl;
    std::cout.precision(5);
    std::cout.setf(std::ios::scientific);
    for (size_t i = 0; i < x.size(); ++i) {
      std::cout << std::setw(3) << i << std::setw(17) << x[i] << std::endl;
    }

  } catch (nagcpp::error_handler::Exception &e) {
    std::cout << e.msg << std::endl;
    return 1;
  }

  return 0;
}
