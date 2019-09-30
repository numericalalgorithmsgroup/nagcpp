// Test some of RawData implementation in nagcpp_data_handling_default.hpp
// (additional tests are also in ut_data_handling_XD.cpp)
#include "include/cxxunit_testing.hpp"
#include "include/nagcpp_ut_generate_data.hpp"
#include "utility/nagcpp_data_handling_default.hpp"

#include <vector>

using namespace nagcpp;

struct test_float_to_double : public TestCase {
  void run() override {
    std::vector<float> vf = ut::get_expected_values<float>(20);
    data_handling::RawData<double, data_handling::INOUT, std::vector<float>> rd(
      vf);
    ASSERT_ARRAY_EQUAL(vf.size(), vf.data(), rd.data);

    std::vector<float> bvf(vf.size());
    rd.copy_back(bvf);
    ASSERT_ARRAY_EQUAL(vf.size(), vf.data(), bvf.data());
  }
};
// clang-format off
REGISTER_TEST(test_float_to_double, "Test float to double");
// clang-format on

struct test_int_to_double : public TestCase {
  void run() override {
    std::vector<int> vf = ut::get_expected_values<int>(20);
    data_handling::RawData<double, data_handling::INOUT, std::vector<int>> rd(
      vf);
    ASSERT_ARRAY_EQUAL(vf.size(), vf.data(), rd.data);

    std::vector<int> bvf(vf.size());
    rd.copy_back(bvf);
    ASSERT_ARRAY_EQUAL(vf.size(), vf.data(), bvf.data());
  }
};
// clang-format off
REGISTER_TEST(test_int_to_double, "Test int to double");
// clang-format on

struct test_int_to_f77_integer : public TestCase {
  void run() override {
    std::vector<int> vf = ut::get_expected_values<int>(20);
    data_handling::RawData<types::f77_integer, data_handling::INOUT,
                           std::vector<int>>
      rd(vf);
    ASSERT_ARRAY_EQUAL(vf.size(), vf.data(), rd.data);

    std::vector<int> bvf(vf.size());
    rd.copy_back(bvf);
    ASSERT_ARRAY_EQUAL(vf.size(), vf.data(), bvf.data());
  }
};
// clang-format off
REGISTER_TEST(test_int_to_f77_integer, "Test int to f77_integer");
// clang-format on

struct test_long_to_f77_integer : public TestCase {
  void run() override {
    std::vector<long> vf = ut::get_expected_values<long>(20);
    data_handling::RawData<types::f77_integer, data_handling::INOUT,
                           std::vector<long>>
      rd(vf);
    ASSERT_ARRAY_EQUAL(vf.size(), vf.data(), rd.data);

    std::vector<long> bvf(vf.size());
    rd.copy_back(bvf);
    ASSERT_ARRAY_EQUAL(vf.size(), vf.data(), bvf.data());
  }
};
// clang-format off
REGISTER_TEST(test_long_to_f77_integer, "Test long to f77_integer");
// clang-format on

struct test_uint_to_f77_integer : public TestCase {
  void run() override {
    std::vector<unsigned int> vf = ut::get_expected_values<unsigned int>(20);
    data_handling::RawData<types::f77_integer, data_handling::INOUT,
                           std::vector<unsigned int>>
      rd(vf);
    ASSERT_ARRAY_EQUAL(vf.size(), vf.data(), rd.data);

    std::vector<unsigned int> bvf(vf.size());
    rd.copy_back(bvf);
    ASSERT_ARRAY_EQUAL(vf.size(), vf.data(), bvf.data());
  }
};
// clang-format off
REGISTER_TEST(test_uint_to_f77_integer, "Test unsigned long to f77_integer");
// clang-format on

struct test_ulong_to_f77_integer : public TestCase {
  void run() override {
    std::vector<unsigned long> vf = ut::get_expected_values<unsigned long>(20);
    data_handling::RawData<types::f77_integer, data_handling::INOUT,
                           std::vector<unsigned long>>
      rd(vf);
    ASSERT_ARRAY_EQUAL(vf.size(), vf.data(), rd.data);

    std::vector<unsigned long> bvf(vf.size());
    rd.copy_back(bvf);
    ASSERT_ARRAY_EQUAL(vf.size(), vf.data(), bvf.data());
  }
};
// clang-format off
REGISTER_TEST(test_ulong_to_f77_integer, "Test unsigned long to f77_integer");
// clang-format on
