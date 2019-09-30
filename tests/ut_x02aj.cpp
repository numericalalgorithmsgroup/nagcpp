#include <vector>

#include "include/cxxunit_testing.hpp"
#include "x02/nagcpp_x02aj.hpp"

struct test_simple_example : public TestCase {
  void run() override {
    double eps = nagcpp::machine::precision();
    // this is only going to be true for a double precision library
    double expected_eps = 1.110223024625156540E-016;
    ASSERT_FLOATS_EQUAL((eps / expected_eps), 1.0);
  }
};
// clang-format off
REGISTER_TEST(test_simple_example, "Test simple example");
// clang-format on
