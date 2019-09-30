// example of using:
//   nagcpp::quad::md_gauss (d01fb)
//   nagcpp::quad::dim1_gauss_wres (d01tb)
#include <iostream>
#include <math.h>
#include <vector>

#include "d01/nagcpp_d01fb.hpp"
#include "d01/nagcpp_d01tb.hpp"

// function of interest
double f(const std::vector<double> &x) {
  double p1 = 6;
  double p2 = 8;
  return pow(x[0] * x[1] * x[2], p1) / pow(x[3] + 2, p2) *
         exp(-2 * x[1] - 0.5 * x[2] * x[2]);
}

int main(void) {
  std::cout << "nagcpp::quad::md_gauss Example" << std::endl;

  // number of points per dimension
  std::vector<nagcpp::types::f77_integer> nptvec = {4, 4, 4, 4};

  // preallocate the arrays for the combined weights and abscis
  size_t lwa = 0;
  for (auto n : nptvec)
    lwa += n;
  std::vector<double> weight(lwa);
  std::vector<double> abscis(lwa);

  // calculate some weights and abscis ...
  std::vector<nagcpp::types::f77_integer> key = {0, -3, -4, -5};
  std::vector<double> a = {1.0, 0.0, 0.0, 1.0};
  std::vector<double> b = {2.0, 2.0, 0.5, 2.0};

  // loop over dimension
  size_t k = 0;
  for (auto i = 0u; i < nptvec.size(); ++i) {
    std::vector<double> this_weight;
    std::vector<double> this_abscis;

    try {
      nagcpp::quad::dim1_gauss_wres(key[i], a[i], b[i], nptvec[i], this_weight,
                                    this_abscis);

    } catch (nagcpp::error_handler::Exception &e) {
      std::cout << e.msg << std::endl;
      return 1;
    }

    // concatenate the weights and abscis
    for (auto j = 0; j < nptvec[i]; ++j, ++k) {
      weight[k] = this_weight[j];
      abscis[k] = this_abscis[j];
    }
  }
  // ... calculate some weights and abscis

  // approximate the integral of f
  double mdint;
  try {
    mdint = nagcpp::quad::md_gauss(nptvec, weight, abscis, f);

  } catch (nagcpp::error_handler::Exception &e) {
    std::cout << e.msg << std::endl;
    return 1;
  }

  std::cout.precision(5);
  std::cout << "Answer = " << mdint << std::endl;

  return 0;
}
