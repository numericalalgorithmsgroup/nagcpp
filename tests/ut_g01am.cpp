#include "g01/nagcpp_g01am.hpp"
#include "include/cxxunit_testing.hpp"
#include <vector>

using namespace nagcpp;

struct test_simple_example : public TestCase {
  void run() override {
    // this is the Fortran example
    std::vector<double> rv = {4.9, 7.0, 3.9, 9.5, 1.3, 3.1,
                              9.7, 0.3, 8.5, 0.6, 6.2};
    std::vector<double> q = {0.0, 0.25, 0.5, 1.0};
    std::vector<double> qv;
    nagcpp::stat::quantiles(rv, q, qv);

    std::vector<double> eqv = {0.3, 2.2, 4.9, 9.7};
    ASSERT_ARRAY_FLOATS_EQUAL(eqv.size(), eqv, qv);
  }
};
// clang-format off
REGISTER_TEST(test_simple_example, "Test simple example");
// clang-format on
