// unit tests for the utility routines in nagcpp_ut_generate_data.hpp
// used by other unit tests

// we only test double, code is the same for all
#include "include/cxxunit_testing.hpp"
#include "include/nagcpp_ut_generate_data.hpp"
#include <vector>

using namespace nagcpp;

struct test_get_expected_1D : public TestCase {
  void run() override {
    size_t n1 = 5;
    double eps = 0.0001;
    {
      SUB_TEST("double");
      std::vector<double> generated = ut::get_expected_values<double>(n1);

      // 10 * i + (i / n1 + 2), i = 1, ..., n1
      std::vector<double> expected = {10.142857, 20.285714, 30.428571,
                                      40.571529, 50.714286};
      ASSERT_ARRAY_ALMOST_EQUAL(n1, expected, generated, eps);

      double adj = 43.2;
      std::vector<double> adj_generated =
        ut::get_expected_values<double>(n1, adj);
      std::vector<double> adj_expected(n1);
      for (size_t i = 0; i < n1; ++i) {
        adj_expected[i] = expected[i] + adj;
      }
      ASSERT_ARRAY_ALMOST_EQUAL(n1, adj_expected, adj_generated, eps);
    }
    {
      SUB_TEST("integer");
      std::vector<int> generated = ut::get_expected_values<int>(n1);

      // 10 * i, i = 1, ..., n1
      std::vector<int> expected = {10, 20, 30, 40, 50};
      ASSERT_ARRAY_EQUAL(n1, expected, generated);

      int adj = 43;
      std::vector<int> adj_generated = ut::get_expected_values<int>(n1, adj);
      std::vector<int> adj_expected(n1);
      for (size_t i = 0; i < n1; ++i) {
        adj_expected[i] = expected[i] + adj;
      }
      ASSERT_ARRAY_EQUAL(n1, adj_expected, adj_generated);
    }
  }
};
// clang-format off
REGISTER_TEST(test_get_expected_1D, "Test ut::get_expected_values for vectors (1D array)");
// clang-format on

struct test_get_expected_2D : public TestCase {
  void run() override {
    double eps = 0.001;
    size_t n1 = 4;
    size_t n2 = 3;
    size_t n12 = n1 * n2;
    {
      SUB_TEST("col major order - double");
      std::vector<double> generated =
        ut::get_expected_values<ut::SORDER::COL_MAJOR, double>(n1, n2);

      // (j * n1 + i) * 10 + i / (n1 + 2), i = 1, ..., n1, j = 1, ..., n2
      // clang-format off
      std::vector<double> expected = { 50.166667, 60.333333, 70.5, 80.666667,
                                       90.166667,100.333333,110.5,120.666667,
                                      130.166667,140.333333,150.5,160.666667};
      // clang-format on
      ASSERT_ARRAY_ALMOST_EQUAL(n12, expected, generated, eps);

      double adj = 43.42;
      std::vector<double> adj_generated =
        ut::get_expected_values<ut::SORDER::COL_MAJOR, double>(n1, n2, adj);
      std::vector<double> adj_expected(n12);
      for (size_t i = 0; i < n12; ++i) {
        adj_expected[i] = expected[i] + adj;
      }
      ASSERT_ARRAY_ALMOST_EQUAL(n12, adj_expected, adj_generated, eps);
    }
    {
      SUB_TEST("col major order - integer");
      std::vector<int> generated =
        ut::get_expected_values<ut::SORDER::COL_MAJOR, int>(n1, n2);

      // (j * n1 + i) * 10, i = 1, ..., n1, j = 1, ..., n2
      // clang-format off
      std::vector<int> expected = { 50, 60, 70, 80,
                                    90,100,110,120,
                                   130,140,150,160};
      // clang-format on
      ASSERT_ARRAY_EQUAL(n12, expected, generated);

      int adj = 43;
      std::vector<int> adj_generated =
        ut::get_expected_values<ut::SORDER::COL_MAJOR, int>(n1, n2, adj);
      std::vector<int> adj_expected(n12);
      for (size_t i = 0; i < n12; ++i) {
        adj_expected[i] = expected[i] + adj;
      }
      ASSERT_ARRAY_EQUAL(n12, adj_expected, adj_generated);
    }
    {
      SUB_TEST("row major order - double");
      std::vector<double> generated =
        ut::get_expected_values<ut::SORDER::ROW_MAJOR, double>(n1, n2);

      // (j * n1 + i) * 10 + i / (n1 + 2), i = 1, ..., n1, j = 1, ..., n2
      // clang-format off
      std::vector<double> expected = {50.166667,  90.166667, 130.166667,
                                      60.333333, 100.333333, 140.333333,
                                      70.5,      110.5,      150.5,
                                      80.666667, 120.666667, 160.666667};
      // clang-format on
      ASSERT_ARRAY_ALMOST_EQUAL(n12, expected, generated, eps);

      double adj = 43.42;
      std::vector<double> adj_generated =
        ut::get_expected_values<ut::SORDER::ROW_MAJOR, double>(n1, n2, adj);
      std::vector<double> adj_expected(n12);
      for (size_t i = 0; i < n12; ++i) {
        adj_expected[i] = expected[i] + adj;
      }
      ASSERT_ARRAY_ALMOST_EQUAL(n12, adj_expected, adj_generated, eps);
    }
    {
      SUB_TEST("row major order - integer");
      std::vector<int> generated =
        ut::get_expected_values<ut::SORDER::ROW_MAJOR, int>(n1, n2);

      // (j * n1 + i) * 10, i = 1, ..., n1, j = 1, ..., n2
      // clang-format off
      std::vector<int> expected = {50, 90,  130,
                                   60, 100, 140,
                                   70, 110, 150,
                                   80, 120, 160};
      // clang-format on
      ASSERT_ARRAY_EQUAL(n12, expected, generated);

      int adj = 43;
      std::vector<int> adj_generated =
        ut::get_expected_values<ut::SORDER::ROW_MAJOR, int>(n1, n2, adj);
      std::vector<int> adj_expected(n12);
      for (size_t i = 0; i < n12; ++i) {
        adj_expected[i] = expected[i] + adj;
      }
      ASSERT_ARRAY_EQUAL(n12, adj_expected, adj_generated);
    }
  }
};
// clang-format off
REGISTER_TEST(test_get_expected_2D, "Test ut::get_expected_values for matrices (2D array)");
// clang-format on

struct test_get_expected_3D : public TestCase {
  void run() override {
    double eps = 0.001;
    size_t n1 = 4;
    size_t n2 = 3;
    size_t n3 = 2;
    size_t n123 = n1 * n2 * n3;
    {
      SUB_TEST("col major order - double");
      std::vector<double> generated =
        ut::get_expected_values<ut::SORDER::COL_MAJOR, double>(n1, n2, n3);

      // (k * n1 * n2 + j * n1 + i) * 10 + i / (n1 + 2), i = 1, ..., n1, j = 1, ..., n2,k = 1, ..., n3
      // clang-format off
      std::vector<double> expected = {170.166667, 180.333333, 190.5, 200.666667,
                                      210.166667, 220.333333, 230.5, 240.666667,
                                      250.166667, 260.333333, 270.5, 280.666667,
                                      290.166667, 300.333333, 310.5, 320.666667,
                                      330.166667, 340.333333, 350.5, 360.666667,
                                      370.166667, 380.333333, 390.5, 400.666667};
      // clang-format on
      ASSERT_ARRAY_ALMOST_EQUAL(n123, expected, generated, eps);

      double adj = 43;
      std::vector<double> adj_generated =
        ut::get_expected_values<ut::SORDER::COL_MAJOR, double>(n1, n2, n3, adj);
      std::vector<double> adj_expected(n123);
      for (size_t i = 0; i < n123; ++i) {
        adj_expected[i] = expected[i] + adj;
      }
      ASSERT_ARRAY_ALMOST_EQUAL(n123, adj_expected, adj_generated, eps);
    }
    {
      SUB_TEST("col major order - integer");
      std::vector<int> generated =
        ut::get_expected_values<ut::SORDER::COL_MAJOR, int>(n1, n2, n3);

      // (k * n1 * n2 + j * n1 + i) * 10, i = 1, ..., n1, j = 1, ..., n2,k = 1, ..., n3
      // clang-format off
      std::vector<int> expected = {170, 180, 190, 200,
                                   210, 220, 230, 240,
                                   250, 260, 270, 280,
                                   290, 300, 310, 320,
                                   330, 340, 350, 360,
                                   370, 380, 390, 400};
      // clang-format on
      ASSERT_ARRAY_EQUAL(n123, expected, generated);

      int adj = 43;
      std::vector<int> adj_generated =
        ut::get_expected_values<ut::SORDER::COL_MAJOR, int>(n1, n2, n3, adj);
      std::vector<int> adj_expected(n123);
      for (size_t i = 0; i < n123; ++i) {
        adj_expected[i] = expected[i] + adj;
      }
      ASSERT_ARRAY_EQUAL(n123, adj_expected, adj_generated);
    }
    {
      SUB_TEST("row major order - double");
      std::vector<double> generated =
        ut::get_expected_values<ut::SORDER::ROW_MAJOR, double>(n1, n2, n3);

      // (k * n1 * n2 + j * n1 + i) * 10 + i / (n1 + 2), i = 1, ..., n1, j = 1, ..., n2,k = 1, ..., n3
      // clang-format off
      std::vector<double> expected = {170.166667, 290.166667, 210.166667, 330.166667, 250.166667, 370.166667,
                                      180.333333, 300.333333, 220.333333, 340.333333, 260.333333, 380.333333,
                                      190.5,      310.5,      230.5,      350.5,      270.5,      390.5,
                                      200.666667, 320.666667, 240.666667, 360.666667, 280.666667, 400.666667};
      // clang-format on
      ASSERT_ARRAY_ALMOST_EQUAL(n123, expected, generated, eps);

      double adj = 43;
      std::vector<double> adj_generated =
        ut::get_expected_values<ut::SORDER::ROW_MAJOR, double>(n1, n2, n3, adj);
      std::vector<double> adj_expected(n123);
      for (size_t i = 0; i < n123; ++i) {
        adj_expected[i] = expected[i] + adj;
      }
      ASSERT_ARRAY_ALMOST_EQUAL(n123, adj_expected, adj_generated, eps);
    }
    {
      SUB_TEST("row major order - integer");
      std::vector<int> generated =
        ut::get_expected_values<ut::SORDER::ROW_MAJOR, int>(n1, n2, n3);

      // (k * n1 * n2 + j * n1 + i) * 10, i = 1, ..., n1, j = 1, ..., n2,k = 1, ..., n3
      // clang-format off
      std::vector<int> expected = {170, 290, 210, 330, 250, 370,
                                   180, 300, 220, 340, 260, 380,
                                   190, 310, 230, 350, 270, 390,
                                   200, 320, 240, 360, 280, 400};
      // clang-format on
      ASSERT_ARRAY_EQUAL(n123, expected, generated);

      int adj = 43;
      std::vector<int> adj_generated =
        ut::get_expected_values<ut::SORDER::ROW_MAJOR, int>(n1, n2, n3, adj);
      std::vector<int> adj_expected(n123);
      for (size_t i = 0; i < n123; ++i) {
        adj_expected[i] = expected[i] + adj;
      }
      ASSERT_ARRAY_EQUAL(n123, adj_expected, adj_generated);
    }
  }
};
// clang-format off
REGISTER_TEST(test_get_expected_3D, "Test ut::get_expected_values for tables (3D array)");
// clang-format on

struct test_top_left_2D : public TestCase {
  void run() override {
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
      SUB_TEST("column major order");
      std::vector<double> ce1 =
        ut::top_left<ut::SORDER::COL_MAJOR, double>(expected_initial.data(),
                                                    n1_1, n2_1, n1_2, n2_2);
      std::vector<double> ce2 =
        ut::top_left<ut::SORDER::COL_MAJOR, double>(expected.data(), n1_2, n2_2,
                                                    n1_1, n2_1);
      ASSERT_ARRAY_EQUAL((n1_2 * n2_2), ce1, expected);
      ASSERT_ARRAY_EQUAL((n1_1 * n2_1), ce2, expected_initial);
    }
    {
      SUB_TEST("row major order");
      std::vector<double> re1 =
        ut::top_left<ut::SORDER::ROW_MAJOR, double>(initial.data(), n1_1, n2_1,
                                                    n1_2, n2_2);
      std::vector<double> re2 =
        ut::top_left<ut::SORDER::ROW_MAJOR, double>(expected_row.data(), n1_2,
                                                    n2_2, n1_1, n2_1);
      ASSERT_ARRAY_EQUAL((n1_2 * n2_2), re1, expected_row);
      ASSERT_ARRAY_EQUAL((n1_1 * n2_1), re2, initial);
    }
  }
};
// clang-format off
REGISTER_TEST(test_top_left_2D, "Test ut::top_left for a matrix (2D array)");
// clang-format on

struct test_top_left_3D : public TestCase {
  void run() override {
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
    // row_major (proper! - not the half and half of initial)
    std::vector<double> initial_row = {111, 112, 121, 122, 131, 132,
                                       211, 212, 221, 222, 231, 232,
                                       311, 312, 321, 322, 331, 332,
                                       411, 412, 421, 422, 431, 432};
    std::vector<double> expected_row = {111, 112, 0, 121, 122, 0, 131, 132, 0, 0, 0, 0,
                                        211, 212, 0, 221, 222, 0, 231, 232, 0, 0, 0, 0,
                                        311, 312, 0, 321, 322, 0, 331, 332, 0, 0, 0, 0,
                                        411, 412, 0, 421, 422, 0, 431, 432, 0, 0, 0, 0,
                                        0,   0, 0,   0,   0, 0,   0,   0, 0, 0, 0, 0};

    // clang-format on
    {
      SUB_TEST("column major order");
      std::vector<double> ce1 = ut::top_left<ut::SORDER::COL_MAJOR, double>(
        expected_initial.data(), n1_1, n2_1, n3_1, n1_2, n2_2, n3_2);
      std::vector<double> ce2 =
        ut::top_left<ut::SORDER::COL_MAJOR, double>(expected.data(), n1_2, n2_2,
                                                    n3_2, n1_1, n2_1, n3_1);
      ASSERT_ARRAY_EQUAL((n1_2 * n2_2 * n3_2), ce1, expected);
      ASSERT_ARRAY_EQUAL((n1_1 * n2_1 * n3_1), ce2, expected_initial);
    }
    {
      SUB_TEST("row major order");
      std::vector<double> re1 = ut::top_left<ut::SORDER::ROW_MAJOR, double>(
        initial_row.data(), n1_1, n2_1, n3_1, n1_2, n2_2, n3_2);
      std::vector<double> re2 = ut::top_left<ut::SORDER::ROW_MAJOR, double>(
        expected_row.data(), n1_2, n2_2, n3_2, n1_1, n2_1, n3_1);
      ASSERT_ARRAY_EQUAL((n1_2 * n2_2 * n3_2), re1, expected_row);
      ASSERT_ARRAY_EQUAL((n1_1 * n2_1 * n3_1), re2, initial_row);
    }
  }
};
// clang-format off
REGISTER_TEST(test_top_left_3D, "Test ut::top_left for a table (3D array)");
// clang-format on
