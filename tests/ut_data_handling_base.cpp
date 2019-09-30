// unit test for code in data_handling_base
// see also the tests in data_handling_XD unit tests (1D, 2D, 3D) etc which will
// cover most of the base coode
#include "include/cxxunit_testing.hpp"
#include "utility/nagcpp_data_handling_base.hpp"

using namespace nagcpp;

struct test_INOUT_functions : public TestCase {
  void run() override {
    ASSERT_TRUE(data_handling::is_in<data_handling::INOUT::IN>::value);
    ASSERT_FALSE(data_handling::is_in<data_handling::INOUT::OUT>::value);
    ASSERT_FALSE(data_handling::is_in<data_handling::INOUT::INOUT>::value);

    ASSERT_FALSE(data_handling::is_out<data_handling::INOUT::IN>::value);
    ASSERT_TRUE(data_handling::is_out<data_handling::INOUT::OUT>::value);
    ASSERT_FALSE(data_handling::is_out<data_handling::INOUT::INOUT>::value);

    ASSERT_FALSE(data_handling::is_inout<data_handling::INOUT::IN>::value);
    ASSERT_FALSE(data_handling::is_inout<data_handling::INOUT::OUT>::value);
    ASSERT_TRUE(data_handling::is_inout<data_handling::INOUT::INOUT>::value);
  }
};
// clang-format off
REGISTER_TEST(test_INOUT_functions, "Test trait functions for INOUT");
// clang-format on
