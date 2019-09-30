// example of using:
//   nagcpp::interp::dim1_spline (e01ba)
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

#include "e01/nagcpp_e01ba.hpp"

int main(void) {
  std::cout << "nagcpp::interp::dim1_spline Example" << std::endl;
  std::vector<double> x = {0.0, 0.2, 0.4, 0.6, 0.75, 0.9, 1.0};
  std::vector<double> y(x.size());
  std::transform(x.begin(), x.end(), y.begin(),
                 [](double x) -> double { return exp(x); });
  std::vector<double> c;
  std::vector<double> lamda;

  try {
    nagcpp::interp::dim1_spline(x, y, lamda, c);

  } catch (nagcpp::error_handler::Exception &e) {
    std::cout << e.msg << std::endl;
    return 1;
  }

  std::cout << "              Knot          B-spline coeff" << std::endl;
  std::cout << "   i       lambda_{i+2}          N_i(x)" << std::endl;
  std::cout << std::string(42, '-') << std::endl;
  for (auto it = c.begin(); it != c.end(); ++it) {
    std::size_t i = it - c.begin();
    std::cout << std::setw(4) << i;
    std::cout << std::fixed << std::setprecision(4);
    if (it == c.begin() || it == c.end()) {
      std::cout << std::setw(35) << c[i] << std::endl;
    } else {
      std::cout << std::setw(15) << lamda[i + 2] << std::setw(20) << c[i]
                << std::endl;
    }
  }

  return 0;
}
