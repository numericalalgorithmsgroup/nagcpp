#include <vector>

#include "../examples/include/nag_my_matrix.hpp"
#include "f06/nagcpp_f06ya.hpp"
#include "include/cxxunit_testing.hpp"

struct test_simple_example_1 : public TestCase {
  void run() override {
    // data for A and B (row major order)
    std::vector<double> ra = {0.1, 0.9, 0.3, 0.7, 0.5, 0.3, 0.6, 0.3,
                              0.8, 0.4, 0.0, 0.0, 0.6, 0.7, 0.5};
    std::vector<double> rb = {0.1, 1.0, 0.3, 0.5, 0.6, 0.9, 0.1, 0.2, 0.8, 0.2};
    // expected results (assumes we are working in column major order)
    std::vector<double> er = {0.93, 0.79, 0.83, 1.06, 1.11, 0.78};
    // NB: MyMatrix transposes from row major to column major order
    MyMatrix<double> a(3, 5, ra);
    MyMatrix<double> b(5, 2, rb);
    MyMatrix<double> c;

    double alpha = 1.0;
    double beta = 0.0;
    nagcpp::blas::dgemm("NoTranspose", "NoTranspose", alpha, a, b, beta, c);

    ASSERT_TRUE(a.is_col_major());
    ASSERT_TRUE(b.is_col_major());
    ASSERT_TRUE(c.is_col_major());

    ASSERT_ARRAY_FLOATS_EQUAL(er.size(), er.data(), c.data());
  }
};
// clang-format off
REGISTER_TEST(test_simple_example_1, "Test simple example C = A*B");
// clang-format on
