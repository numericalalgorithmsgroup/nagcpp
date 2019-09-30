// example of using:
//   nagcpp::roots::contfn_brent (c05ay)
#include <iostream>
#include <math.h>
#include <vector>

#include "c05/nagcpp_c05ay.hpp"
#include "utility/nagcpp_utility_array.hpp"

double f(const double x) { return exp(-x) - x; }

int main(void) {
  std::cout << "nagcpp::roots::contfn_brent Example" << std::endl;

  double a = 0.0;
  double b = 1.0;
  double x;

  try {

    nagcpp::roots::contfn_brent(a, b, f, x);

  } catch (nagcpp::error_handler::ErrorException &e) {
    std::cout << e.msg << std::endl;
    return 1;
  }

  std::cout.precision(5);
  std::cout << "x = " << x << std::endl;

  return 0;
}
