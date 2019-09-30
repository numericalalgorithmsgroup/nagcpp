// example of using:
//   nagcpp::matop::real_nmf_rcomm (f01sb)
//   nagcpp::sparse::real_gen_matvec (f11xa)
//   nagcpp::blas::dlange (f06ra)
//   nagcpp::blas::dgemm (f06ya)
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

#include "f01/nagcpp_f01sb.hpp"
#include "f06/nagcpp_f06ra.hpp"
#include "f06/nagcpp_f06ya.hpp"
#include "f11/nagcpp_f11xa.hpp"

// a simple sample matrix class
#include "include/nag_my_matrix.hpp"

int main(void) {
  std::cout << "nagcpp::matop::real_nmf_rcomm Example" << std::endl;
  typedef std::vector<double>::size_type vsize_t;
  std::vector<double> a = {6.0, 3.0, 6.0, 3.0, 1.0, 7.0, 2.0, 2.0, 4.0,
                           2.0, 2.0, 6.0, 3.0, 2.0, 1.0, 2.0, 1.0, 6.0,
                           7.0, 3.0, 1.0, 2.0, 1.0, 1.0, 3.0};
  std::vector<nagcpp::types::f77_integer> icolix = {1, 1, 1, 1, 2, 2, 2, 2, 3,
                                                    3, 3, 3, 3, 4, 4, 4, 4, 5,
                                                    5, 5, 5, 6, 6, 6, 6};
  std::vector<nagcpp::types::f77_integer> irowix = {2, 4, 5, 6, 1, 3, 5, 7, 1,
                                                    3, 4, 6, 7, 2, 4, 5, 6, 3,
                                                    4, 5, 7, 1, 3, 4, 6};
  size_t m = 7;
  size_t n = 6;
  size_t k = 4;
  MyMatrix<double> w(m, k);
  MyMatrix<double> h(k, n);
  MyMatrix<double> ht(n, k);

  // choose values for the arguments errtol and seed
  // rather than using the defaults
  nagcpp::matop::OptionalF01SB opt;
  opt.seed(234);
  opt.errtol(1.0e-3);

  // we will terminate after 200 iterations
  vsize_t maxit = 200;

  // we are going to pretend that A is q x q, rather than m x n
  size_t q = std::max(m, n);
  std::vector<double> tmp_x(q, 0);
  std::vector<double> tmp_y(q);

  vsize_t icount;
  double rel_resid_norm;

  // find a non-negative matrix factorixation A ~= WH
  try {
    nagcpp::utility::CopyableComm comm;
    nagcpp::types::f77_integer irevcm = 0;
    for (icount = 0; icount < maxit;) {
      nagcpp::matop::real_nmf_rcomm(irevcm, w, h, ht, comm, opt);

      if (irevcm == 1) {
        ++icount;

      } else if (irevcm == 2) {
        // compute a^t * w and store in ht
        for (vsize_t j = 0; j < k; ++j) {
          for (vsize_t i = 0; i < m; ++i) {
            tmp_x[i] = w(i, j);
          }
          // sparse matrix vector product (f11xa)
          nagcpp::sparse::real_gen_matvec("Transpose", a, irowix, icolix, tmp_x,
                                          tmp_y);
          for (vsize_t i = 0; i < n; ++i) {
            ht(i, j) = tmp_y[i];
          }
        }

      } else if (irevcm == 3) {
        // compute a * ht and store in w (f11mk)
        for (vsize_t j = 0; j < k; ++j) {
          for (vsize_t i = 0; i < n; ++i) {
            tmp_x[i] = ht(i, j);
          }
          // sparse matrix vector product (f11xa)
          nagcpp::sparse::real_gen_matvec("NoTranspose", a, irowix, icolix,
                                          tmp_x, tmp_y);
          for (vsize_t i = 0; i < m; ++i) {
            w(i, j) = tmp_y[i];
          }
        }

      } else {
        // nagcpp::matop::real_nmf_rcomm has finished
        break;
      }
    }

    std::cout << "Exited after ";
    if (icount >= maxit) {
      std::cout << "the maximum number of iterations (" << maxit << ")"
                << std::endl;
    } else {
      std::cout << icount << " iterations" << std::endl;
    }

    // get a dense version of the matrix A
    MyMatrix<double> da(m, n, std::vector<double>(m * n, 0));
    for (vsize_t i = 0; i < a.size(); ++i) {
      da(irowix[i] - 1, icolix[i] - 1) = a[i];
    }

    // get ||A|| (f06ra)
    double norma = nagcpp::blas::dlange("F", da);

    // calculate A = A-WH (f06ya)
    nagcpp::blas::dgemm("NoTranspose", "NoTranspose", -1.0, w, h, 1.0, da);

    // get ||A-WH|| (f06ra)
    double norm = nagcpp::blas::dlange("F", da);
    rel_resid_norm = norm / norma;

  } catch (nagcpp::error_handler::Exception &e) {
    std::cout << e.msg << std::endl;
    return 1;
  }

  std::cout << "W" << std::endl;
  std::cout.precision(4);
  std::cout.setf(std::ios::scientific);
  std::cout << "         ";
  for (vsize_t j = 0; j < k; ++j) {
    std::cout << std::setw(15) << j + 1;
  }
  std::cout << std::endl;
  for (vsize_t i = 0; i < m; ++i) {
    std::cout << std::left << std::setw(4) << i + 1;
    for (vsize_t j = 0; j < k; ++j) {
      std::cout << std::setw(15) << w(i, j);
    }
    std::cout << std::endl;
  }

  std::cout << std::endl << "H^T" << std::endl;
  std::cout.precision(4);
  std::cout.setf(std::ios::scientific);
  std::cout << "         ";
  for (vsize_t i = 0; i < k; ++i) {
    std::cout << std::setw(15) << i + 1;
  }
  std::cout << std::endl;
  for (vsize_t j = 0; j < n; ++j) {
    std::cout << std::left << std::setw(4) << j + 1;
    for (vsize_t i = 0; i < k; ++i) {
      std::cout << std::setw(15) << h(i, j);
    }
    std::cout << std::endl;
  }

  std::cout << std::endl;
  std::cout << "The relative residual norm, ||A-WH|| / ||A||, is: "
            << rel_resid_norm << std::endl;

  return 0;
}
