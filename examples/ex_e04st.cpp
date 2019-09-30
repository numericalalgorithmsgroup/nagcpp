// example of using:
//   nagcpp::opt::handle_solve_ipopt (e04st)
//   nagcpp::opt::handle_set_simplebounds (e04rh)
//   nagcpp::opt::handle_set_linobj (e04re)
//   nagcpp::opt::handle_set_linconstr (e04rj)
//   nagcpp::opt::handle_set_nlnconstr (e04rk)
//   nagcpp::opt::handle_set_nlnhess (e04rl)
//   nagcpp::opt::handle_​print (e04ry)
// in addition, the following routines are implicitly
// called via the communication class:
//   nagcpp::opt::handle_init (e04ra)
//   nagcpp::opt::handle_opt_set (e04zm)
//   nagcpp::opt::handle_free (e04rz)
#include <fstream>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <vector>

#include "e04/nagcpp_class_CommE04RA.hpp"
#include "e04/nagcpp_e04re.hpp"
#include "e04/nagcpp_e04rh.hpp"
#include "e04/nagcpp_e04rj.hpp"
#include "e04/nagcpp_e04rk.hpp"
#include "e04/nagcpp_e04rl.hpp"
#include "e04/nagcpp_e04ry.hpp"
#include "e04/nagcpp_e04st.hpp"

void confun(const std::vector<double> &x,
            const nagcpp::types::f77_integer ncnln, std::vector<double> &gx) {
  gx[0] = 12.0 * x[0] + 11.9 * x[1] + 41.8 * x[2] + 52.1 * x[3] -
          1.645 * std::sqrt(0.28 * pow(x[0], 2) + 0.19 * pow(x[1], 2) +
                            20.5 * pow(x[2], 2) + 0.62 * pow(x[3], 2));
}

void congrd(const std::vector<double> &x,
            const nagcpp::types::f77_integer nnzgd, std::vector<double> &gdx) {
  double tmp = std::sqrt(0.62 * pow(x[3], 2) + 20.5 * pow(x[2], 2) +
                         0.19 * pow(x[1], 2) + 0.28 * pow(x[0], 2));
  gdx[0] = (12.0 * tmp - 0.4606 * x[0]) / tmp;
  gdx[1] = (11.9 * tmp - 0.31255 * x[1]) / tmp;
  gdx[2] = (41.8 * tmp - 33.7225 * x[2]) / tmp;
  gdx[3] = (52.1 * tmp - 1.0199 * x[3]) / tmp;
}
void hess(const std::vector<double> &x, const nagcpp::types::f77_integer idf,
          const double sigma, const std::vector<double> &lamda,
          const nagcpp::types::f77_integer nnzh, std::vector<double> &hx) {
  bool terminate = true;
  std::fill(hx.begin(), hx.end(), 0.0);

  if (idf == 0) {
    terminate = false;

  } else if (idf == 1 || idf == -1) {
    double tmp = std::sqrt(0.62 * pow(x[3], 2) + 20.5 * pow(x[2], 2) +
                           0.19 * pow(x[1], 2) + 0.28 * pow(x[0], 2));
    tmp = tmp * (pow(x[3], 2) + 33.064516129032258064 * pow(x[2], 2) +
                 0.30645161290322580645 * pow(x[1], 2) +
                 0.45161290322580645161 * pow(x[0], 2));
    // 1,1..4
    hx[0] = (-0.4606 * pow(x[3], 2) - 15.229516129032258064 * pow(x[2], 2) -
             0.14115161290322580645 * pow(x[1], 2)) /
            tmp;
    hx[1] = (0.14115161290322580645 * x[0] * x[1]) / tmp;
    hx[2] = (15.229516129032258064 * x[0] * x[2]) / tmp;
    hx[3] = (0.4606 * x[0] * x[3]) / tmp;
    // 2,2..4
    hx[4] = (-0.31255 * pow(x[3], 2) - 10.334314516129032258 * pow(x[2], 2) -
             0.14115161290322580645 * pow(x[0], 2)) /
            tmp;
    hx[5] = (10.334314516129032258 * x[1] * x[2]) / tmp;
    hx[6] = (0.31255 * x[1] * x[3]) / tmp;
    // 3,3..4
    hx[7] = (-33.7225 * pow(x[3], 2) - 10.334314516129032258 * pow(x[1], 2) -
             15.229516129032258065 * pow(x[0], 2)) /
            tmp;
    hx[8] = (33.7225 * x[2] * x[3]) / tmp;
    // 4,4
    hx[9] = (-33.7225 * pow(x[2], 2) - 0.31255 * pow(x[1], 2) -
             0.4606 * pow(x[0], 2)) /
            tmp;
    if (idf == -1) {
      for (auto ihx = hx.begin(); ihx != hx.end(); ++ihx) {
        (*ihx) *= lamda[0];
      }
    }
    terminate = false;
  }

  if (terminate) {
    throw nagcpp::error_handler::CallbackEarlyTermination("hess", "unhandled "
                                                                  "value of "
                                                                  "idf");
  }
}

typedef std::vector<double>::size_type vsize_t;

int main(void) {
  std::cout << "nagcpp::opt::handle_solve_lp_ipm Example" << std::endl
            << std::endl;

  try {
    vsize_t k = 0;
    nagcpp::types::f77_integer nvar = 4;

    // initialise the problem handle
    nagcpp::opt::CommE04RA handle(nvar);

    double bigbnd = 1.0e20;

    // set simple bounds, x_i>=0 (e04rh)
    std::vector<double> bl(nvar, 0.0);
    std::vector<double> bu(nvar, bigbnd);
    nagcpp::opt::handle_set_simplebounds(handle, bl, bu);

    // set linear objective (e04re)
    std::vector<double> coeffs = {24.55, 26.75, 39.00, 40.50};
    nagcpp::opt::handle_set_linobj(handle, coeffs);

    // set linear constraints (e04rj)
    std::vector<double> linbl = {5.0, 1.0};
    std::vector<double> linbu = {bigbnd, 1.0};
    std::vector<nagcpp::types::f77_integer> irowb = {1, 1, 1, 1, 2, 2, 2, 2};
    std::vector<nagcpp::types::f77_integer> icolb = {1, 2, 3, 4, 1, 2, 3, 4};
    std::vector<double> b = {2.3, 5.6, 11.1, 1.3, 1.0, 1.0, 1.0, 1.0};
    nagcpp::opt::handle_set_linconstr(handle, linbl, linbu, irowb, icolb, b);

    // set nonlinear constraints (e04rk)
    std::vector<double> nlnbl = {21.0};
    std::vector<double> nlnbu = {bigbnd};
    std::vector<nagcpp::types::f77_integer> irowgb = {1, 1, 1, 1};
    std::vector<nagcpp::types::f77_integer> icolgb = {1, 2, 3, 4};
    nagcpp::opt::handle_set_nlnconstr(handle, nlnbl, nlnbu, irowgb, icolgb);

    // hessian of nonlinear constraint (e04rl)
    std::vector<nagcpp::types::f77_integer> irowh(nvar * (nvar + 1) / 2);
    std::vector<nagcpp::types::f77_integer> icolh(nvar * (nvar + 1) / 2);
    // NB: i and j are 1-based
    for (vsize_t i = 1; i <= static_cast<vsize_t>(nvar); ++i) {
      for (vsize_t j = i; j <= static_cast<vsize_t>(nvar); ++j) {
        irowh[k] = i;
        icolh[k] = j;
        ++k;
      }
    }
    nagcpp::opt::handle_set_nlnhess(handle, 1, irowh, icolh);

    // open some output streams
    std::ofstream printing_fs("ex_e04st.out");
    std::ofstream monitoring_fs("ex_e04st.mon");

    // register the streams to the global IO manager
    // this example uses three streams, std::cout, and two files
    // an alternative to using the global IO manager is to create
    // a local instance and pass that to the routines via the
    // optional parameters argument
    nagcpp::types::f77_integer nout =
      nagcpp::iomanager::GLOBAL_IOMANAGER->register_ostream(std::cout);
    nagcpp::types::f77_integer printing_unit_number =
      nagcpp::iomanager::GLOBAL_IOMANAGER->register_ostream(printing_fs);
    nagcpp::types::f77_integer monitoring_unit_number =
      nagcpp::iomanager::GLOBAL_IOMANAGER->register_ostream(monitoring_fs);

    // turn on monitoring
    handle.MonitoringLevel(5);
    handle.MonitoringFile(monitoring_unit_number);

    // turn on printing
    handle.PrintLevel(2);
    handle.PrintFile(printing_unit_number);

    // set some control parameters
    handle.StopTolerance1(2.5e-8);
    handle.OuterIterationLimit(26);
    handle.TimeLimit(60);

    // initial values for variable
    std::vector<double> x(nvar, 1.0);

    // nnzu = 2 * (number of variables +
    //        number linear constraints + number non-linear constraints)
    nagcpp::types::f77_integer nnzu =
      2 * nvar + 2 * linbl.size() + 2 * nlnbl.size();
    std::vector<double> u;
    std::vector<double> rinfo;
    std::vector<double> stats;

    // we are going to be using the default values for the optional
    // arguments, however we want to print out any warning messages
    nagcpp::opt::OptionalE04ST opt;

    // summarise the problem being solved (e04ry)
    nagcpp::opt::handle_print(handle, nout, "Overview");

    // call the solver
    handle_solve_ipopt(handle, nullptr, nullptr, confun, congrd, hess, nullptr,
                       x, nnzu, u, rinfo, stats, opt);
    if (opt.fail.warning_thrown) {
      std::cout << std::endl << opt.fail.msg << std::endl << std::endl;
    }

    std::cout.precision(6);
    std::cout.setf(std::ios::scientific);
    std::cout << std::endl << "Variables" << std::endl;
    for (vsize_t i = 0; i < x.size(); ++i) {
      std::cout << "      x(" << std::setw(10) << i << ")" << std::setw(17)
                << "=" << std::setw(20) << x[i] << std::endl;
    }
    std::cout << "Variable bound Lagrange multipliers" << std::endl;
    k = 0;
    for (vsize_t i = 0; i < static_cast<vsize_t>(nvar); i++) {
      std::cout << "     zL(" << std::setw(10) << i << ")" << std::setw(17)
                << "=" << std::setw(20) << u[k] << std::endl;
      ++k;
      std::cout << "     zU(" << std::setw(10) << i << ")" << std::setw(17)
                << "=" << std::setw(20) << u[k] << std::endl;
      ++k;
    }
    std::cout << "Linear constraints Lagrange multipliers" << std::endl;
    for (vsize_t i = 0; i < linbl.size(); i++) {
      std::cout << "     l-(" << std::setw(10) << i << ")" << std::setw(17)
                << "=" << std::setw(20) << u[k] << std::endl;
      ++k;
      std::cout << "     l+(" << std::setw(10) << i << ")" << std::setw(17)
                << "=" << std::setw(20) << u[k] << std::endl;
      ++k;
    }
    std::cout << "Nonlinear constraints Lagrange multipliers" << std::endl;
    for (vsize_t i = 0; i < nlnbl.size(); i++) {
      std::cout << "     l-(" << std::setw(10) << i << ")" << std::setw(17)
                << "=" << std::setw(20) << u[k] << std::endl;
      ++k;
      std::cout << "     l+(" << std::setw(10) << i << ")" << std::setw(17)
                << "=" << std::setw(20) << u[k] << std::endl;
      ++k;
    }
    std::cout.precision(7);
    std::cout << "At solution, Objective minimum     =" << std::setw(20)
              << rinfo[0] << std::endl;
    std::cout.precision(2);
    std::cout << "             Constraint violation  =" << std::setw(20)
              << rinfo[1] << std::endl;
    std::cout << "             Dual infeasibility    =" << std::setw(20)
              << rinfo[2] << std::endl;
    std::cout << "             Complementarity       =" << std::setw(20)
              << rinfo[3] << std::endl;
    std::cout << "             KKT error             =" << std::setw(20)
              << rinfo[4] << std::endl;
    // round time to the nearest 10 seconds, to avoid suprious differences in results file
    std::cout << "Solution took less than "
              << static_cast<int>(std::ceil(stats[7] / 10) * 10) << " seconds"
              << std::endl;
    std::cout << "    after iterations                        : "
              << std::setw(10) << int(stats[0]) << std::endl;
    std::cout << "    after objective evaluations             : "
              << std::setw(10) << int(stats[18]) << std::endl;
    std::cout << "    after objective gradient evaluations    : "
              << std::setw(10) << int(stats[4]) << std::endl;
    std::cout << "    after constraint evaluations            : "
              << std::setw(10) << int(stats[19]) << std::endl;
    std::cout << "    after constraint gradient evaluations   : "
              << std::setw(10) << int(stats[20]) << std::endl;
    std::cout << "    after hessian evaluations               : "
              << std::setw(10) << int(stats[3]) << std::endl;

    // deregister the streams as we no longer need them
    nagcpp::iomanager::GLOBAL_IOMANAGER->deregister_ostream(printing_fs);
    nagcpp::iomanager::GLOBAL_IOMANAGER->deregister_ostream(monitoring_fs);

    printing_fs.close();
    monitoring_fs.close();

  } catch (nagcpp::error_handler::Exception &e) {
    std::cout << e.msg << std::endl;
    return 1;
  }

  return 0;
}
