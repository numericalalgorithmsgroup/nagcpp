// example of using:
//   nagcpp::opt::nlp1_solve (e04uc)
// in addition, the following routines are implicitly
// called via the communication class:
//   nagcpp::opt::nlp1_init (e04wb)
//   nagcpp::opt::nlp1_option_string (e04eu)
#include <iostream>
#include <math.h>

#include "e04/nagcpp_class_CommE04WB.hpp"
#include "e04/nagcpp_e04uc.hpp"
#include "utility/nagcpp_utility_array.hpp"

// a simple sample matrix class
#include "include/nag_my_matrix.hpp"

void objfun(
  const nagcpp::types::f77_integer mode,
  const nagcpp::utility::array1D<double, nagcpp::data_handling::IN> &x,
  double &objf,
  nagcpp::utility::array1D<double, nagcpp::data_handling::INOUT> &objgrd,
  const nagcpp::types::f77_integer nstate) {
  if (mode == 0 || mode == 2) {
    objf = x(0) * x(3) * (x(0) + x(1) + x(2)) + x(2);
  }
  if (mode == 1 || mode == 2) {
    objgrd(0) = x(3) * (2.0 * x(0) + x(1) + x(2));
    objgrd(1) = x(0) * x(3);
    objgrd(2) = x(0) * x(3) + 1.0;
    objgrd(3) = x(0) * (x(0) + x(1) + x(2));
  }
}

void confun(
  const nagcpp::types::f77_integer mode,
  const nagcpp::utility::array1D<nagcpp::types::f77_integer,
                                 nagcpp::data_handling::IN> &needc,
  const nagcpp::utility::array1D<double, nagcpp::data_handling::IN> &x,
  nagcpp::utility::array1D<double, nagcpp::data_handling::OUT> &c,
  nagcpp::utility::array2D<double, nagcpp::data_handling::INOUT> &cjac,
  const nagcpp::types::f77_integer nstate) {
  if (needc(0) > 0) {
    if (mode == 0 || mode == 2) {
      c(0) = pow(x(0), 2) + pow(x(1), 2) + pow(x(2), 2) + pow(x(3), 2);
    }
    if (mode == 1 || mode == 2) {
      cjac(0, 0) = 2.0 * x(0);
      cjac(0, 1) = 2.0 * x(1);
      cjac(0, 2) = 2.0 * x(2);
      cjac(0, 3) = 2.0 * x(3);
    }
  }
  if (needc(1) > 0) {
    if (mode == 0 || mode == 2) {
      c(1) = x(0) * x(1) * x(2) * x(3);
    }
    if (mode == 1 || mode == 2) {
      cjac(1, 0) = x(1) * x(2) * x(3);
      cjac(1, 1) = x(0) * x(2) * x(3);
      cjac(1, 2) = x(0) * x(1) * x(3);
      cjac(1, 3) = x(0) * x(1) * x(2);
    }
  }
}

int main(void) {
  std::cout << "nagcpp::opt::nlp1_solve Example" << std::endl;

  try {
    std::vector<double> va = {1.0, 1.0, 1.0, 1.0};
    MyMatrix<double> a(1, 4, va);
    std::vector<double> bl = {1.0, 1.0, 1.0, 1.0, -1.0e+25, -1.0e+25, 25.0};
    std::vector<double> bu = {5.0, 5.0, 5.0, 5.0, 20.0, 40.0, 1.0e+25};
    nagcpp::types::f77_integer itera;
    std::vector<nagcpp::types::f77_integer> istate;
    std::vector<double> c;
    MyMatrix<double> cjac;
    std::vector<double> clamda;
    double objf;
    std::vector<double> objgrd;
    MyMatrix<double> r;
    std::vector<double> x = {1.0, 5.0, 5.0, 1.0};
    nagcpp::opt::CommE04WB comm("nlp1_solve");

    // solve the optimization
    nagcpp::opt::nlp1_solve(a, bl, bu, confun, objfun, itera, istate, c, cjac,
                            clamda, objf, objgrd, r, x,
                            comm.MajorPrintLevel(1));

  } catch (nagcpp::error_handler::Exception &e) {
    std::cout << e.msg << std::endl;
    return 1;
  }

  return 0;
}
