// example of using:
//   nagcpp::stat::quantiles (g01am)
#include <iomanip>
#include <iostream>
#include <vector>

#include "g01/nagcpp_g01am.hpp"

int main(void) {
  std::cout << "nagcpp::stat::quantiles Example" << std::endl;
  std::vector<double> rv = {4.9, 7.0, 3.9, 9.5, 1.3, 3.1,
                            9.7, 0.3, 8.5, 0.6, 6.2};
  std::vector<double> q = {0.0, 0.25, 0.5, 1.0};
  std::vector<double> qv;

  try {
    nagcpp::stat::quantiles(rv, q, qv);

  } catch (nagcpp::error_handler::Exception &e) {
    std::cout << e.msg << std::endl;
    return 1;
  }

  std::cout << "  Quantile   Result" << std::endl;
  std::cout << " " << std::string(19, '-') << std::endl;
  std::cout << std::fixed << std::setprecision(2);
  for (size_t i = 0; i < qv.size(); ++i) {
    std::cout << std::setw(8) << q[i] << std::setw(10) << qv[i] << std::endl;
  }

  return 0;
}
