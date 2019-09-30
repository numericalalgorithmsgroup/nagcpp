// example of using:
//   nagcpp::fit::dim1_spline_eval (e02bb)
#include <iomanip>
#include <iostream>

#include "e02/nagcpp_e02bb.hpp"

int main(void) {
  std::cout << "nagcpp::fit::dim1_spline_eval Example" << std::endl;

  std::vector<double> lamda = {1.0, 1.0, 1.0, 1.0, 3.0, 6.0,
                               8.0, 9.0, 9.0, 9.0, 9.0};
  std::vector<double> c = {1.0, 2.0, 4.0, 7.0, 6.0, 4.0, 3.0};
  c.resize(lamda.size());

  std::cout << std::fixed << std::setprecision(4);

  // title for the results
  std::cout << std::endl;
  std::cout << "                        Value of" << std::endl;
  std::cout << "  R           x       cubic spline" << std::endl;

  // evaluate the spline at m equally spaced points in the interval
  // lamda[3] <= x <= lamda[ncap+3]
  size_t m = 9;
  size_t ncap = lamda.size() - 7;
  double a = lamda[3];
  double b = lamda[ncap + 3];
  for (size_t r = 0; r < m; ++r) {
    double x = ((m - r - 1) * a + r * b) / static_cast<double>(m - 1);
    double s;

    try {
      nagcpp::fit::dim1_spline_eval(lamda, c, x, s);
    } catch (nagcpp::error_handler::Exception &e) {
      std::cout << e.msg << std::endl;
      return 1;
    }

    std::cout << std::setw(3) << r << std::setw(14) << x << std::setw(14) << s
              << std::endl;
  }
  return 0;
}
