// unit tests for type trait functions used by the other unit tests
#include "include/cxxunit_testing.hpp"
#include "include/nagcpp_ut_utilities.hpp"

using namespace nagcpp;

struct test_SORDER_functions : public TestCase {
  void run() override {
    ASSERT_TRUE(ut::is_col_major<ut::SORDER::COL_MAJOR>::value);
    ASSERT_FALSE(ut::is_col_major<ut::SORDER::ROW_MAJOR>::value);

    ASSERT_FALSE(ut::is_row_major<ut::SORDER::COL_MAJOR>::value);
    ASSERT_TRUE(ut::is_row_major<ut::SORDER::ROW_MAJOR>::value);
  }
};
// clang-format off
REGISTER_TEST(test_SORDER_functions, "Test trait functions for SORDER");
// clang-format on

struct test_TYPE_IS_functions : public TestCase {
  void run() override {
    ASSERT_TRUE(ut::is_internal_type<ut::TYPE_IS::INTERNAL>::value);
    ASSERT_FALSE(ut::is_internal_type<ut::TYPE_IS::GENERAL>::value);
    ASSERT_FALSE(ut::is_internal_type<ut::TYPE_IS::CONST_DATA_POINTER>::value);
    ASSERT_FALSE(ut::is_internal_type<ut::TYPE_IS::NO_RESIZE>::value);

    ASSERT_FALSE(ut::is_general_type<ut::TYPE_IS::INTERNAL>::value);
    ASSERT_TRUE(ut::is_general_type<ut::TYPE_IS::GENERAL>::value);
    ASSERT_FALSE(ut::is_general_type<ut::TYPE_IS::CONST_DATA_POINTER>::value);
    ASSERT_FALSE(ut::is_general_type<ut::TYPE_IS::NO_RESIZE>::value);

    ASSERT_FALSE(ut::is_const_data_pointer_type<ut::TYPE_IS::INTERNAL>::value);
    ASSERT_FALSE(ut::is_const_data_pointer_type<ut::TYPE_IS::GENERAL>::value);
    ASSERT_TRUE(
      ut::is_const_data_pointer_type<ut::TYPE_IS::CONST_DATA_POINTER>::value);
    ASSERT_FALSE(ut::is_const_data_pointer_type<ut::TYPE_IS::NO_RESIZE>::value);

    ASSERT_FALSE(ut::is_no_resize_type<ut::TYPE_IS::INTERNAL>::value);
    ASSERT_FALSE(ut::is_no_resize_type<ut::TYPE_IS::GENERAL>::value);
    ASSERT_FALSE(ut::is_no_resize_type<ut::TYPE_IS::CONST_DATA_POINTER>::value);
    ASSERT_TRUE(ut::is_no_resize_type<ut::TYPE_IS::NO_RESIZE>::value);
  }
};
// clang-format off
REGISTER_TEST(test_TYPE_IS_functions, "Test trait functions for TYPE_IS");
// clang-format on

struct test_index_operator_lhs_function : public TestCase {
  void run() override {
    ASSERT_FALSE((ut::index_operator_lhs<data_handling::INOUT::IN,
                                         ut::CONST_DATA_POINTER>::value));
    ASSERT_TRUE((ut::index_operator_lhs<data_handling::INOUT::OUT,
                                        ut::CONST_DATA_POINTER>::value));
    ASSERT_TRUE((ut::index_operator_lhs<data_handling::INOUT::INOUT,
                                        ut::CONST_DATA_POINTER>::value));

    ASSERT_TRUE(
      (ut::index_operator_lhs<data_handling::INOUT::IN, ut::GENERAL>::value));
    ASSERT_TRUE(
      (ut::index_operator_lhs<data_handling::INOUT::OUT, ut::GENERAL>::value));
    ASSERT_TRUE((
      ut::index_operator_lhs<data_handling::INOUT::INOUT, ut::GENERAL>::value));

    ASSERT_TRUE(
      (ut::index_operator_lhs<data_handling::INOUT::IN, ut::NO_RESIZE>::value));
    ASSERT_TRUE((
      ut::index_operator_lhs<data_handling::INOUT::OUT, ut::NO_RESIZE>::value));
    ASSERT_TRUE((ut::index_operator_lhs<data_handling::INOUT::INOUT,
                                        ut::NO_RESIZE>::value));

    ASSERT_TRUE(
      (ut::index_operator_lhs<data_handling::INOUT::IN, ut::INTERNAL>::value));
    ASSERT_TRUE(
      (ut::index_operator_lhs<data_handling::INOUT::OUT, ut::INTERNAL>::value));
    ASSERT_TRUE((ut::index_operator_lhs<data_handling::INOUT::INOUT,
                                        ut::INTERNAL>::value));
  }
};
// clang-format off
REGISTER_TEST(test_index_operator_lhs_function, "Test trait function: index_operator_lhs");
// clang-format on

struct test_has_resize_function : public TestCase {
  void run() override {
    ASSERT_FALSE((
      ut::has_resize<data_handling::INOUT::IN, ut::CONST_DATA_POINTER>::value));
    ASSERT_FALSE((ut::has_resize<data_handling::INOUT::OUT,
                                 ut::CONST_DATA_POINTER>::value));
    ASSERT_FALSE((ut::has_resize<data_handling::INOUT::INOUT,
                                 ut::CONST_DATA_POINTER>::value));

    ASSERT_FALSE(
      (ut::has_resize<data_handling::INOUT::IN, ut::GENERAL>::value));
    ASSERT_TRUE(
      (ut::has_resize<data_handling::INOUT::OUT, ut::GENERAL>::value));
    ASSERT_TRUE(
      (ut::has_resize<data_handling::INOUT::INOUT, ut::GENERAL>::value));

    ASSERT_FALSE(
      (ut::has_resize<data_handling::INOUT::IN, ut::NO_RESIZE>::value));
    ASSERT_FALSE(
      (ut::has_resize<data_handling::INOUT::OUT, ut::NO_RESIZE>::value));
    ASSERT_FALSE(
      (ut::has_resize<data_handling::INOUT::INOUT, ut::NO_RESIZE>::value));

    ASSERT_FALSE(
      (ut::has_resize<data_handling::INOUT::IN, ut::INTERNAL>::value));
    ASSERT_FALSE(
      (ut::has_resize<data_handling::INOUT::OUT, ut::INTERNAL>::value));
    ASSERT_FALSE(
      (ut::has_resize<data_handling::INOUT::INOUT, ut::INTERNAL>::value));
  }
};
// clang-format off
REGISTER_TEST(test_has_resize_function, "Test trait function: has_resize");
// clang-format on
