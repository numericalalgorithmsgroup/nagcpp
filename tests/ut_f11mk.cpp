#include <vector>

#include "../examples/include/nag_my_matrix.hpp"
#include "f11/nagcpp_f11mk.hpp"
#include "include/cxxunit_testing.hpp"

struct test_fortran_example : public TestCase {
  void run() override {
    std::vector<nagcpp::types::f77_integer> icolzp = {1, 3, 5, 7, 9, 12};
    std::vector<double> a = {2.0,  4.0, 1.0, -2.0, 1.0, 1.0,
                             -1.0, 1.0, 1.0, 2.0,  3.0};
    std::vector<nagcpp::types::f77_integer> irowix = {1, 3, 1, 5, 2, 3,
                                                      2, 4, 3, 4, 5};
    std::vector<double> rb = {0.70, 1.40, 0.16, 0.32, 0.52,
                              1.04, 0.77, 1.54, 0.28, 0.56};
    int m = 2;
    int n = 5;
    // NB: MyDataMatrix transposes from row major to column major order
    MyMatrix<double> b(n, m, rb);
    MyMatrix<double> c;
    double alpha = 1.0;
    double beta = 0.0;
    nagcpp::sparse::direct_real_gen_matmul("NoTranspose", alpha, icolzp, irowix,
                                           a, b, beta, c);

    // expected results, assuming we are working in column major order
    std::vector<double> er = {1.56, -0.25, 3.6, 1.33, 0.52,
                              3.12, -0.5,  7.2, 2.66, 1.04};
    ASSERT_TRUE(b.is_col_major());
    ASSERT_TRUE(c.is_col_major());
    ASSERT_ARRAY_FLOATS_EQUAL(n * m, er.data(), c.data());
  }
};
// clang-format off
REGISTER_TEST(test_fortran_example, "Test fortran example");
// clang-format on
