// example of using:
//   nagcpp::stat::prob_students_t_noncentral (g01gb)
#include <iomanip>
#include <iostream>
#include <vector>

#include "g01/nagcpp_g01gb.hpp"

int main(void) {
  std::cout << "nagcpp::stat::prob_students_t_noncentral Example" << std::endl;
  std::vector<double> t = {-1.528, -0.188, 1.138};
  std::vector<double> df = {20.0, 7.5, 45.0};
  std::vector<double> delta = {2.0, 1.0, 0.0};

  std::cout << "       t        df       Delta  Probability" << std::endl;
  std::cout << std::fixed;
  for (std::vector<double>::size_type i = 0; i < df.size(); i++) {
    std::cout << std::setprecision(3) << std::setw(10) << t[i] << std::setw(10)
              << df[i] << std::setw(10) << delta[i];
    double prob;
    try {
      prob = nagcpp::stat::prob_students_t_noncentral(t[i], df[i], delta[i]);

    } catch (nagcpp::error_handler::Exception &e) {
      std::cout << std::endl << e.msg << std::endl;
      return 1;
    }

    std::cout << std::setprecision(4) << std::setw(11) << prob << std::endl;
  }

  return 0;
}
