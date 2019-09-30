// Example of using:
//   nagcpp::correg::lars (g02ma)
#include <iomanip>
#include <iostream>
#include <math.h>
#include <vector>

#include "g02/nagcpp_g02ma.hpp"

// a simple sample matrix class
#include "include/nag_my_matrix.hpp"

int main(void) {
  std::cout << "nagcpp::correg::lars Example" << std::endl;
  nagcpp::types::f77_integer mtype = 1;
  // clang-format off
  std::vector<double> rd = {
    10.28,  1.77,  9.69, 15.58,  8.23, 10.44,
     9.08,  8.99, 11.53,  6.57, 15.89, 12.58,
    17.98, 13.10,  1.04, 10.45, 10.12, 16.68,
    14.82, 13.79, 12.23,  7.00,  8.14,  7.79,
    17.53,  9.41,  6.24,  3.75, 13.12, 17.08,
     7.78, 10.38,  9.83,  2.58, 10.13,  4.25,
    11.95, 21.71,  8.83, 11.00, 12.59, 10.52,
    14.60, 10.09, -2.70,  9.89, 14.67,  6.49,
     3.63,  9.07, 12.59, 14.09,  9.06,  8.19,
     6.35,  9.79,  9.40, 12.79,  8.38, 16.79,
     4.66,  3.55, 16.82, 13.83, 21.39, 13.88,
     8.32, 14.04, 17.17,  7.93,  7.39, -1.09,
    10.86, 13.68,  5.75, 10.44, 10.36, 10.06,
     4.76,  4.92, 17.83,  2.90,  7.58, 11.97,
     5.05, 10.41,  9.89,  9.04,  7.90, 13.12,
     5.41,  9.32,  5.27, 15.53,  5.06, 19.84,
     9.77,  2.37,  9.54, 20.23,  9.33,  8.82,
    14.28,  4.34, 14.23, 14.95, 18.16, 11.03,
    10.17,  6.80,  3.17,  8.57, 16.07, 15.93,
     5.39,  2.67,  6.37, 13.56, 10.68,  7.35
  };
  // clang-format on
  MyMatrix<double> d(20, 6, rd);
  std::vector<double> y = {-46.47, -35.80, -129.22, -42.44,  -73.51,
                           -26.61, -63.90, -76.73,  -32.64,  -83.29,
                           -16.31, -5.82,  -47.75,  18.38,   -54.71,
                           -55.62, -45.28, -22.76,  -104.32, -55.94};
  nagcpp::types::f77_integer ip, nstep;
  MyMatrix<double> b, fitsum;

  // we are going to be using the default values for the optional
  // arguments, however we want to print out any warning messages
  nagcpp::correg::OptionalG02MA opt;

  try {
    nagcpp::correg::lars(mtype, d, nullptr, y, ip, nstep, b, fitsum, opt);

  } catch (nagcpp::error_handler::Exception &e) {
    std::cout << e.msg << std::endl;
    return 1;
  }

  if (opt.fail.warning_thrown) {
    std::cout << opt.fail.msg << std::endl;
  }

  std::cout.precision(3);
  std::cout.setf(std::ios::fixed);
  // display the parameter estimates
  std::cout << " Step " << std::string(((ip > 2) ? (ip - 2) : 0) * 5, ' ')
            << "Parameter Estimate" << std::endl;
  std::cout << std::string(5 + ip * 10, '-') << std::endl;
  for (int k = 0; k < nstep; k++) {
    std::cout << std::setw(4) << k + 1;
    for (int i = 0; i < ip; i++) {
      std::cout << std::setw(10) << b(i, k);
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
  std::cout << " alpha: " << std::setw(10) << fitsum(0, nstep) << std::endl;
  std::cout << std::endl;
  std::cout << " Step     Sum      RSS       df       Cp       Ck     "
            << "Step Size" << std::endl;
  std::cout << std::string(64, '-') << std::endl;
  for (int k = 0; k < nstep; k++) {
    std::cout << std::setw(4) << k + 1 << std::setw(10) << fitsum(0, k)
              << std::setw(10) << fitsum(1, k) << std::setw(7)
              << static_cast<int>(floor(fitsum(2, k) + 0.5)) << std::setw(10)
              << fitsum(3, k) << std::setw(10) << fitsum(4, k) << std::setw(10)
              << fitsum(5, k) << std::endl;
  }
  std::cout << std::endl;
  std::cout << "sigma^2: " << fitsum(4, nstep) << std::endl;

  return 0;
}
