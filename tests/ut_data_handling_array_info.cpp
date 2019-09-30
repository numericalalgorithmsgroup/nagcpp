// unit test for the array_info class
#include "include/cxxunit_testing.hpp"
#include "utility/nagcpp_data_handling_array_info.hpp"

using namespace nagcpp;

struct test_assignment_operator : public TestCase {
  void run() override {

    {
      SUB_TEST("using integer");
      data_handling::array_info<int> a;
      a = 2;
      ASSERT_EQUAL(a.value, 2);
      ASSERT_TRUE(a.set);
    }

    {
      SUB_TEST("using data_handling::array_info<int> on LHS");
      data_handling::array_info<int> a;
      data_handling::array_info<double> b(true, 5);
      a = b;
      ASSERT_EQUAL(a.value, 5);
      ASSERT_TRUE(a.set);
      ASSERT_EQUAL(b.value, 5);
      ASSERT_TRUE(b.set);
      b.value = 8;
      ASSERT_EQUAL(a.value, 5);
      ASSERT_EQUAL(b.value, 8);
      a.value = 3;
      ASSERT_EQUAL(a.value, 3);
      ASSERT_EQUAL(b.value, 8);
    }

    {
      SUB_TEST("chaining");
      data_handling::array_info<double> a, b, c;
      a = b = c = 3;
      ASSERT_EQUAL(a.value, 3);
      ASSERT_TRUE(a.set);
      ASSERT_EQUAL(b.value, 3);
      ASSERT_TRUE(b.set);
      ASSERT_EQUAL(c.value, 3);
      ASSERT_TRUE(c.set);
      b.value = 5;
      ASSERT_EQUAL(a.value, 3);
      ASSERT_EQUAL(b.value, 5);
      ASSERT_EQUAL(c.value, 3);
    }
  }
};
// clang-format off
REGISTER_TEST(test_assignment_operator, "Test assignment operator (=)");
// clang-format on

struct test_multiplication_assignment_operator : public TestCase {
  void run() override {

    {
      SUB_TEST("using integer");
      data_handling::array_info<int> a(true, 3);
      a *= 2;
      ASSERT_EQUAL(a.value, 6);
      ASSERT_TRUE(a.set);
    }

    {
      SUB_TEST("using data_handling::array_info<int> on LHS");
      data_handling::array_info<int> a(true, 3);
      data_handling::array_info<double> b(true, 5);
      a *= b;
      ASSERT_EQUAL(a.value, 15);
      ASSERT_TRUE(a.set);
      ASSERT_EQUAL(b.value, 5);
      ASSERT_TRUE(b.set);
    }

    {
      SUB_TEST("using data_handling::array_info<double>");
      data_handling::array_info<double> a(true, 3);
      data_handling::array_info<double> b(true, 5);
      a *= b;
      ASSERT_EQUAL(a.value, 15);
      ASSERT_TRUE(a.set);
      ASSERT_EQUAL(b.value, 5);
      ASSERT_TRUE(b.set);
    }

    {
      SUB_TEST("using data_handling::array_info, LHS not set");
      data_handling::array_info<int> a(false);
      data_handling::array_info<double> b(true, 5);
      a *= b;
      ASSERT_FALSE(a.set);
      ASSERT_EQUAL(b.value, 5);
      ASSERT_TRUE(b.set);
    }

    {
      SUB_TEST("using data_handling::array_info, RHS not set");
      data_handling::array_info<int> a(true, 3);
      data_handling::array_info<double> b(false);
      ASSERT_TRUE(a.set);
      ASSERT_EQUAL(a.value, 3);
      a *= b;
      ASSERT_FALSE(a.set);
      ASSERT_FALSE(a.set);
    }

    {
      SUB_TEST("chaining");
      data_handling::array_info<int> a(true, 3);
      data_handling::array_info<int> b;
      b = (a *= 3.0);
      ASSERT_EQUAL(a.value, 9);
      ASSERT_TRUE(a.set);
      ASSERT_EQUAL(b.value, 9);
      ASSERT_TRUE(b.set);
      b.value = 4;
      ASSERT_EQUAL(a.value, 9);
      ASSERT_EQUAL(b.value, 4);
    }
  }
};
// clang-format off
REGISTER_TEST(test_multiplication_assignment_operator, "Test multiplication assignment operator (*=)");
// clang-format on

struct test_equality_operator : public TestCase {
  void run() override {

    {
      SUB_TEST("using integer");
      data_handling::array_info<int> a(true, 3);
      ASSERT_TRUE((a == 3));
      ASSERT_FALSE((a != 3));
    }

    {
      SUB_TEST("using data_handling::array_info<int>");
      data_handling::array_info<int> a(true, 3);
      data_handling::array_info<double> b(true, 3);
      data_handling::array_info<double> c(true, 5);
      ASSERT_TRUE((a == b));
      ASSERT_FALSE((a != b));
      ASSERT_TRUE((a != c));
      ASSERT_FALSE((a == c));
    }

    {
      SUB_TEST("using data_handling::array_info, some values not set");
      data_handling::array_info<double> a(true, 3);
      data_handling::array_info<double> b;
      ASSERT_FALSE((a == b));
      ASSERT_FALSE((a != b));
      ASSERT_FALSE((b == a));
      ASSERT_FALSE((a != b));
    }
  }
};
// clang-format off
REGISTER_TEST(test_equality_operator, "Test equality operator (== and !=)");
// clang-format on
