// example of using:
//   nagcpp::correg::corrmat_​nearest__rank (g02ak)
#include <iomanip>
#include <iostream>
#include <vector>

#include "g02/nagcpp_g02ak.hpp"

// a simple sample matrix class
#include "include/nag_my_matrix.hpp"

int main(void) {
  std::cout << "nagcpp::correg::corrmat_​nearest_rank Example" << std::endl;
  // clang-format off
  std::vector<double> rg = {
     2.0, -1.0,  0.0,  0.0,
    -1.0,  2.0, -1.0,  0.0,
     0.0, -1.0,  2.0, -1.0,
     0.0,  0.0, -1.0,  2.0
  };
  // clang-format on
  MyMatrix<double> g(4, 4, rg);
  nagcpp::types::f77_integer rank = 2;
  MyMatrix<double> x;
  double f, rankerr;
  nagcpp::types::f77_integer nsub;

  try {
    nagcpp::correg::corrmat_nearest_rank(g, rank, x, f, rankerr, nsub);

  } catch (nagcpp::error_handler::Exception &e) {
    std::cout << e.msg << std::endl;
    return 1;
  }

  std::cout << std::endl;
  std::cout << "NCM with rank constraint" << std::endl;
  std::cout.precision(4);
  std::cout.setf(std::ios::fixed);
  std::cout << " ";
  for (size_t j = 0; j < g.size2(); ++j) {
    std::cout << std::setw(9) << j + 1;
  }
  std::cout << std::endl;
  for (size_t i = 0; i < g.size1(); ++i) {
    std::cout << i + 1;
    for (size_t j = 0; j < g.size2(); ++j) {
      std::cout << std::setw(9) << x(i, j);
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;

  std::cout << std::setw(40) << std::left
            << "Number of subproblems solved:" << nsub << std::endl;
  std::cout << std::setw(40) << std::left
            << "Squared Frobenius norm of difference:" << f << std::endl;
  std::cout << std::setw(40) << std::left << "Rank error:" << rankerr
            << std::endl;

  return 0;
}
