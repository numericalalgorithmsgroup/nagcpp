#include "include/cxxunit_testing.hpp"
#include "utility/nagcpp_utility_functions.hpp"
#include <string>

struct test_str_toupper : public TestCase {
  void run() override {
    {
      std::string s1 = "Hello";
      std::string s2 = nagcpp::utility::str_toupper(s1);
      ASSERT_STRINGS_EQUAL(s1, "Hello");
      ASSERT_STRINGS_EQUAL(s2, "HELLO");
    }
  }
};
// clang-format off
REGISTER_TEST(test_str_toupper, "Test str_toupper");
// clang-format on

struct test_streq : public TestCase {
  void run() override {
    {
      std::string s1 = "hello";
      ASSERT_TRUE(nagcpp::utility::streq(s1, "HELLO"));
      ASSERT_TRUE(nagcpp::utility::streq(s1, "hello"));
      ASSERT_TRUE(nagcpp::utility::streq(s1, "hElLo"));
      ASSERT_FALSE(nagcpp::utility::streq(s1, "helloXX"));
      ASSERT_FALSE(nagcpp::utility::streq(s1, "he"));
      ASSERT_TRUE(nagcpp::utility::streq(s1, "helloXX", 5));
      ASSERT_TRUE(nagcpp::utility::streq(s1, "he", 2));
      ASSERT_FALSE(nagcpp::utility::streq(s1, "heXlo", 3));
      ASSERT_TRUE(nagcpp::utility::streq(s1, "heXlo", 2));
      ASSERT_TRUE(nagcpp::utility::streq(s1, "heXlo", 1));
    }
  }
};
// clang-format off
REGISTER_TEST(test_streq, "Test streq");
// clang-format on

struct test_strip_namespace : public TestCase {
  void run() override {
    {
      std::string s1 = "Hello";
      std::string s2 = "aa::bbbb::ff";
      std::string s3 = "aa:xxads";
      std::string s4 = "aa::ggg";

      std::string as1 = nagcpp::utility::strip_namespace(s1);
      std::string as2 = nagcpp::utility::strip_namespace(s2);
      std::string as3 = nagcpp::utility::strip_namespace(s3);
      std::string as4 = nagcpp::utility::strip_namespace(s4);

      ASSERT_STRINGS_EQUAL(as1, s1);
      ASSERT_STRINGS_EQUAL(as2, "ff");
      ASSERT_STRINGS_EQUAL(as3, s3);
      ASSERT_STRINGS_EQUAL(as4, "ggg");

      s1 = "Goodbye";
      s3 = "Tarah";
      ASSERT_STRINGS_EQUAL(as1, "Hello");
      ASSERT_STRINGS_EQUAL(s1, "Goodbye");
      ASSERT_STRINGS_EQUAL(as3, "aa:xxads");
      ASSERT_STRINGS_EQUAL(s3, "Tarah");
    }
  }
};
// clang-format off
REGISTER_TEST(test_strip_namespace, "Test strip_namespace");
// clang-format on

struct test_rname_eq : public TestCase {
  void run() override {
    {
      std::string s1 = "FF";
      std::string s2 = "aa::bbbb::ff";
      std::string s3 = "aa::ff";
      std::string s4 = "gg";
      std::string s5 = "aa::bbbb::gg";

      ASSERT_TRUE(nagcpp::utility::rname_eq(s1, s2));
      ASSERT_TRUE(nagcpp::utility::rname_eq(s1, "aa::ff"));
      ASSERT_TRUE(nagcpp::utility::rname_eq("xx::ff", s2));
      ASSERT_TRUE(nagcpp::utility::rname_eq("xx::ff", "zzzz::ff"));
      ASSERT_TRUE(nagcpp::utility::rname_eq(s2, s3));
      ASSERT_FALSE(nagcpp::utility::rname_eq(s4, s3));
      ASSERT_FALSE(nagcpp::utility::rname_eq(s2, s5));
    }
  }
};
// clang-format off
REGISTER_TEST(test_rname_eq, "Test rname_eq");
// clang-format on

struct test_set_optstr : public TestCase {
  void run() override {
    {
      std::string f1 = nagcpp::utility::set_optstr("HELLO THERE");
      ASSERT_STRINGS_EQUAL(f1, "HELLO THERE");
      std::string f2 = nagcpp::utility::set_optstr("HELLO THERE", 3.2);
      ASSERT_STRINGS_EQUAL(f2, "HELLO THERE = 3.2");
      std::string f3 = nagcpp::utility::set_optstr("HELLO THERE", 3.1e-15);
      ASSERT_STRINGS_EQUAL(f3, "HELLO THERE = 3.1e-15");
      std::string f4 = nagcpp::utility::set_optstr("HELLO THERE", 6);
      ASSERT_STRINGS_EQUAL(f4, "HELLO THERE = 6");
      std::string f5 =
        nagcpp::utility::set_optstr("HELLO THERE", "SOME STRING");
      ASSERT_STRINGS_EQUAL(f5, "HELLO THERE = SOME STRING");
      std::string ss = "SOME OTHER STRING";
      std::string f6 = nagcpp::utility::set_optstr("HELLO THERE", ss);
      ASSERT_STRINGS_EQUAL(f6, "HELLO THERE = SOME OTHER STRING");
    }
    {
      std::string opt = "GOODBYE";
      std::string f1 = nagcpp::utility::set_optstr(opt);
      std::string f2 = nagcpp::utility::set_optstr(opt, 33.3);
      std::string f3 = nagcpp::utility::set_optstr(opt, 88);
      std::string f4 = nagcpp::utility::set_optstr(opt, "SOMX STRING");
      opt = "FFFF";
      ASSERT_STRINGS_EQUAL(f1, "GOODBYE");
      ASSERT_STRINGS_EQUAL(f2, "GOODBYE = 33.3");
      ASSERT_STRINGS_EQUAL(f3, "GOODBYE = 88");
      ASSERT_STRINGS_EQUAL(f4, "GOODBYE = SOMX STRING");
    }
  }
};
// clang-format off
REGISTER_TEST(test_set_optstr, "Test set_optstr");
// clang-format on
