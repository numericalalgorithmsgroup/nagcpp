// additional tests for the example data handling classes nag_my_data,
// nag_my_vector, nag_my_matrix, nag_my_table most testing is done in the
// generic ut_data_handling_1D.cpp etc

// we only test double, code is the same for all
#include "../examples/include/nag_my_data.hpp"
#include "../examples/include/nag_my_matrix.hpp"
#include "../examples/include/nag_my_table.hpp"
#include "../examples/include/nag_my_vector.hpp"
#include "include/cxxunit_testing.hpp"
#include "include/nagcpp_ut_generate_data.hpp"
#include <vector>

using namespace nagcpp;

struct test_vector_resize : public TestCase {
  void run() override {
    run_this<MyVector<double>>("MyVector");
    run_this<MyData<double>>("MyData");
  }

  template <typename AC>
  void run_this(const std::string label = "") {
    // NB: the generic tests also test resize, but they are restricted
    // to cases that can occur in the wrappers, here we test other cases
    SUB_TITLE(label);
    {
      SUB_TEST("resize + preserve: larger");

      static const size_t n1 = 5;
      std::vector<double> initial = {1, 2, 3, 4, 5};
      static const size_t n2 = 7;
      std::vector<double> expected = {1, 2, 3, 4, 5, 0, 0};

      AC vv(n1, initial);
      ASSERT_ARRAY_EQUAL(n1, vv.data(), initial.data());
      vv.resize(n2);
      ASSERT_ARRAY_EQUAL(n2, vv.data(), expected.data());
    }
  }
};
// clang-format off
REGISTER_TEST(test_vector_resize, "Test vector resize method");
// clang-format on

struct test_matrix_resize : public TestCase {
  void run() override {
    run_this<MyMatrix<double>>("MyMatrix");
    run_this<MyData<double>>("MyData");
  }
  template <typename AC>
  void run_this(const std::string label = "") {
    // NB: the generic tests also test resize, but they are restricted
    // to cases that can occur in the wrappers, here we test other cases
    SUB_TITLE(label);
    {
      // clang-format off
      static const size_t n1_1 = 3;
      static const size_t n2_1 = 2;
      // row major
      std::vector<double> initial = {11, 12,
                                     21, 22,
                                     31, 32};
      // column major
      std::vector<double> expected_initial = {11, 21, 31,
                                              12, 22, 32};
      static const size_t n1_2 = 5;
      static const size_t n2_2 = 4;
      // column major
      std::vector<double> expected = {11, 21, 31, 0, 0,
                                      12, 22, 32, 0, 0,
                                       0,  0,  0, 0, 0,
                                       0,  0,  0, 0, 0};
      // row major
      std::vector<double> expected_row = {11, 12, 0, 0,
                                          21, 22, 0, 0,
                                          31, 32, 0, 0,
                                          0,   0, 0, 0,
                                          0,   0, 0, 0};

      // clang-format on
      {
        SUB_TEST("resize + preserve: larger (rows + columns)");
        AC mm(n1_1, n2_1, initial);
        ASSERT_ARRAY_EQUAL((n1_1 * n2_1), mm.data(), expected_initial.data());
        mm.resize(n1_2, n2_2);
        ASSERT_ARRAY_EQUAL((n1_2 * n2_2), mm.data(), expected.data());
      }
    }
  }
};
// clang-format off
REGISTER_TEST(test_matrix_resize, "Test matrix resize method");
// clang-format on

struct test_table_resize : public TestCase {
  void run() override {
    run_this<MyTable<double>>("MyTable");
    run_this<MyData<double>>("MyData");
  }
  template <typename AC>
  void run_this(const std::string label = "") {
    // NB: the generic tests also test resize, but they are restricted
    // to cases that can occur in the wrappers, here we test other cases
    SUB_TITLE(label);
    {
      // clang-format off
      static const size_t n1_1 = 4;
      static const size_t n2_1 = 3;
      static const size_t n3_1 = 2;
      // row major for matri<x, tables stacked (see code comments
      // in class)
      std::vector<double> initial = {111, 121, 131,
                                     211, 221, 231,
                                     311, 321, 331,
                                     411, 421, 431,
                                     112, 122, 132,
                                     212, 222, 232,
                                     312, 322, 332,
                                     412, 422, 432};
      // column major
      std::vector<double> expected_initial = {111, 211, 311, 411,
                                              121, 221, 321, 421,
                                              131, 231, 331, 431,
                                              112, 212, 312, 412,
                                              122, 222, 322, 422,
                                              132, 232, 332, 432};
      static const size_t n1_2 = 5;
      static const size_t n2_2 = 4;
      static const size_t n3_2 = 3;
      // column major
      std::vector<double> expected = {111, 211, 311, 411, 0,
                                      121, 221, 321, 421, 0,
                                      131, 231, 331, 431, 0,
                                        0,   0,   0,  0,  0,
                                      112, 212, 312, 412, 0,
                                      122, 222, 322, 422, 0,
                                      132, 232, 332, 432, 0,
                                        0,   0,   0,  0,  0,
                                        0,   0,   0,  0,  0,
                                        0,   0,   0,  0,  0,
                                        0,   0,   0,  0,  0,
                                        0,   0,   0,  0,  0};

      // clang-format on
      {
        SUB_TEST("resize + preserve: larger (rows + columns + tables)");
        AC tt(n1_1, n2_1, n3_1, initial);
        ASSERT_ARRAY_EQUAL((n1_1 * n2_1 * n3_1), tt.data(),
                           expected_initial.data());
        tt.resize(n1_2, n2_2, n3_2);
        ASSERT_ARRAY_EQUAL((n1_2 * n2_2 * n3_2), tt.data(), expected.data());
      }
    }
  }
};
// clang-format off
REGISTER_TEST(test_table_resize, "Test table (3D array) resize method");
// clang-format on
