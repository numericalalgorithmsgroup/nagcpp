#include <vector>

#include "f11/nagcpp_f11xa.hpp"
#include "include/cxxunit_testing.hpp"

struct test_fortran_example : public TestCase {
  void run() override {
    std::vector<double> a = {2.0, 1.0, 1.0, -1.0, 4.0, 1.0,
                             1.0, 1.0, 2.0, -2.0, 3.0};
    std::vector<nagcpp::types::f77_integer> irow = {1, 1, 2, 2, 3, 3,
                                                    3, 4, 4, 5, 5};
    std::vector<nagcpp::types::f77_integer> icol = {1, 2, 3, 4, 1, 3,
                                                    5, 4, 5, 2, 5};
    std::vector<double> x = {0.70, 0.16, 0.52, 0.77, 0.28};
    std::vector<double> y1;
    nagcpp::sparse::real_gen_matvec("N", a, irow, icol, x, y1);
    std::vector<double> ey1 = {0.1560E+01, -0.2500E+00, 0.3600E+01, 0.1330E+01,
                               0.5200E+00};
    std::vector<double> y2;
    nagcpp::sparse::real_gen_matvec("T", a, irow, icol, x, y2);
    std::vector<double> ey2 = {0.3480E+01, 0.1400E+00, 0.6800E+00, 0.6100E+00,
                               0.2900E+01};
    ASSERT_ARRAY_FLOATS_EQUAL(ey1.size(), ey1.data(), y1.data());
    ASSERT_ARRAY_FLOATS_EQUAL(ey2.size(), ey2.data(), y2.data());
  }
};
// clang-format off
REGISTER_TEST(test_fortran_example, "Test fortran example");
// clang-format on
