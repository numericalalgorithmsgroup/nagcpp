#include <vector>

#include "../examples/include/nag_my_matrix.hpp"
#include "f08/nagcpp_f08fc.hpp"
#include "include/cxxunit_testing.hpp"
#include "x02/nagcpp_x02aj.hpp"

using namespace nagcpp;

struct test_simple_example_fortran : public TestCase {
  void run() override {
    // this is the Fortran example
    double eps = machine::precision() * 100.0;

    // clang-format off
    // data for A (row major order)
    std::vector<double> ra = {1.0, 99.9, 99.9, 99.9,
                              2.0,  2.0, 99.9, 99.9,
                              3.0,  3.0,  3.0, 99.9,
                              4.0,  4.0,  4.0,  4.0};

    // expected results
    // (taken from running this program, sanity checked from Fortran example)
    // eigenvalues
    std::vector<double> evalues = {-2.053115763536997, -0.514642779390613, -0.294326451773802, 12.862084994701416};
    // (normalized) eigenvectors (row major order)
    std::vector<double> revectors = {  0.700349026088273,-0.514373575732108,-0.276677588114017, 0.410342026218597,
                                       0.359233810606341, 0.485103335886423, 0.663358845738863, 0.442245253913612,
                                      -0.156851475724139, 0.541978203304837,-0.650424727889853, 0.508532118017172,
                                      -0.596539961392038,-0.454262264823847, 0.245666903275196, 0.614356282506063};
    size_t n = 4;
    // clang-format on
    {
      SUB_TEST("UPLO='L'");
      MyMatrix<double> a(n, n, ra);
      std::string uplo = "L";
      std::string job = "V";
      std::vector<double> w;
      lapackeig::dsyevd(job, uplo, a, w);

      // normalize the eigenvectors
      for (size_t j = 0; j < a.size2(); ++j) {
        double mval = std::fabs(a(0, j));
        size_t mi = 0;
        for (size_t i = 0; i < a.size1(); ++i) {
          if (std::fabs(a(i, j)) > mval) {
            mval = std::fabs(a(i, j));
            mi = i;
          }
        }
        if (a(mi, j) < 0.0) {
          for (size_t i = 0; i < a.size1(); ++i) {
            a(i, j) = -a(i, j);
          }
        }
      }

      ASSERT_ARRAY_ALMOST_EQUAL(w.size(), w.data(), evalues.data(), eps);
      ASSERT_2DARRAY_ALMOST_EQUAL_ROW_VS_COL(a.size1(), a.size2(), revectors,
                                             a.data(), eps);
    }
    // A does change when JOB='N'
    // {
    //   SUB_TEST("UPLO='L', JOB='N'");
    //   MyMatrix<double> a(n, n, ra);
    //   std::string uplo = "L";
    //   std::string job = "N";
    //   std::vector<double> w;
    //   lapackeig::dsyevd(job, uplo, a, w);

    //   ASSERT_ARRAY_ALMOST_EQUAL(w.size(), w.data(), evalues.data(),eps);
    //   // A should not change
    //   ASSERT_2DARRAY_ALMOST_EQUAL_ROW_VS_COL(a.size1(),a.size2(), ra.data(), a.data(),eps);
    // }
    {
      SUB_TEST("UPLO='U'");

      // transpose the raw data
      MyMatrix<double> ta(n, n, ra);
      MyMatrix<double> a(n, n);
      for (size_t j = 0; j < a.size2(); ++j) {
        for (size_t i = 0; i < a.size1(); ++i) {
          a(i, j) = ta(j, i);
        }
      }
      std::string uplo = "U";
      std::string job = "V";
      std::vector<double> w;
      lapackeig::dsyevd(job, uplo, a, w);

      // normalize the eigenvectors
      for (size_t j = 0; j < a.size2(); ++j) {
        double mval = std::fabs(a(0, j));
        size_t mi = 0;
        for (size_t i = 0; i < a.size1(); ++i) {
          if (std::fabs(a(i, j)) > mval) {
            mval = std::fabs(a(i, j));
            mi = i;
          }
        }
        if (a(mi, j) < 0.0) {
          for (size_t i = 0; i < a.size1(); ++i) {
            a(i, j) = -a(i, j);
          }
        }
      }

      ASSERT_ARRAY_ALMOST_EQUAL(w.size(), w.data(), evalues.data(), eps);
      ASSERT_2DARRAY_ALMOST_EQUAL_ROW_VS_COL(a.size1(), a.size2(), revectors,
                                             a.data(), eps);
    }
  }
};
// clang-format off
REGISTER_TEST(test_simple_example_fortran, "Test Fortran example");
// clang-format on
