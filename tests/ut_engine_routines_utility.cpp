#include <sstream>
#include <stdio.h>

#include "include/cxxunit_testing.hpp"
#include "utility/nagcpp_consts.hpp"
#include "utility/nagcpp_engine_routines.hpp"
#include "utility/nagcpp_error_handler.hpp"

using namespace nagcpp::engine_routines;

struct test_y90haan : public TestCase {
  void run() override {
    nagcpp::types::engine_data en_data;
    y90haan_(en_data);
    ASSERT_EQUAL(en_data.hlperr, nagcpp::error_handler::HLPERR_SUCCESS);
    ASSERT_FALSE(en_data.cpuser);
    ASSERT_EQUAL(en_data.storage_order, nagcpp::constants::NAG_ED_COL_MAJOR);
    ASSERT_EQUAL(en_data.allocate_workspace, nagcpp::constants::NAG_ED_NO);
    ASSERT_FALSE(en_data.wrapptr1);
    ASSERT_FALSE(en_data.wrapptr2);
    ASSERT_FALSE(en_data.y90_print_rec);
  }
};
// clang-format off
REGISTER_TEST(test_y90haan, "Test y90haan initialisation");
// clang-format on
