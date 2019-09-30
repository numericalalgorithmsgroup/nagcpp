// example of using:
//   nagcpp::opt::handle_solve_dfls_rcomm (e04fg)
//   nagcpp::opt::handle_set_simplebounds (e04rh)
//   nagcpp::opt::handle_set_nlnls (e04rm)
// in addition, the following routines are implicitly
// called via the communication class:
//   nagcpp::opt::handle_init (e04ra)
//   nagcpp::opt::handle_opt_set (e04zm)
//   nagcpp::opt::handle_free (e04rz)
// additional information:
//   this examples uses boost matrices as arguments
#include "e04/nagcpp_class_CommE04RA.hpp"
#include "e04/nagcpp_e04fg.hpp"
#include "e04/nagcpp_e04rh.hpp"
#include "e04/nagcpp_e04rm.hpp"
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <iostream>
#include <math.h>

int main(void) {
  std::cout << "nagcpp::opt::handle_solve_dfls_rcomm Example" << std::endl;

  // throw warnings as exceptions
  nagcpp::error_handler::GLOBAL_ERROR_HANDLER_CONTROL.error_handler_type =
    nagcpp::error_handler::ErrorHandlerType::ThrowAll;

  try {
    nagcpp::types::f77_integer nvar = 2;

    // initialise the problem handle
    nagcpp::opt::CommE04RA handle(nvar);

    // define residuals structure (e04rm)
    // the residual structure is dense so irowrd and icolrd are not required
    nagcpp::types::f77_integer nres = 2;
    nagcpp::opt::handle_set_nlnls(handle, nres, nullptr, nullptr);

    // relax the main convergence criteria a bit
    handle.DFOTrustRegionTolerance(5.0e-6);

    // print the solution
    handle.PrintSolution("Yes");

    // define starting point
    nagcpp::types::f77_integer maxeval = 2;
    boost::numeric::ublas::matrix<double> x(nvar, maxeval);
    x(0, 0) = -1.2;
    x(1, 0) = 1.0;

    // define bounds for the second and fourth variables (e04rh)
    boost::numeric::ublas::vector<double> lx(2);
    lx(0) = -1.5;
    lx(1) = -2.0;
    boost::numeric::ublas::vector<double> ux(2);
    ux(0) = 2.0;
    ux(1) = 1.0e20;
    nagcpp::opt::handle_set_simplebounds(handle, lx, ux);

    nagcpp::types::f77_integer neval;
    boost::numeric::ublas::matrix<double> rx(nres, maxeval);
    boost::numeric::ublas::vector<double> rinfo;
    boost::numeric::ublas::vector<double> stats;

    // call the solver (e04fg) in the reverse communication loop
    nagcpp::types::f77_integer irevcm = 1;
    do {
      nagcpp::opt::handle_solve_dfls_rcomm(handle, irevcm, neval, x, rx, rinfo,
                                           stats);
      if (irevcm == 1) {
        for (nagcpp::types::f77_integer i = 0; i < neval; ++i) {
          rx(0, i) = 1.0 - x(0, i);
          rx(1, i) = 10 * (x(1, i) - pow(x(0, i), 2));
        }
      }
    } while (irevcm != 0);

  } catch (nagcpp::error_handler::Exception &e) {
    std::cout << e.msg << std::endl;
    return 1;
  }

  return 0;
}
