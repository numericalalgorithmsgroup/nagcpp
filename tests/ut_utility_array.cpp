// additional unit tests for the utility::arrayXD classes
// more tests can be found in the data_handling_XD unit test
#include "include/cxxunit_testing.hpp"
#include "utility/nagcpp_data_handling_base.hpp"
#include "utility/nagcpp_utility_array.hpp"
#include <vector>

using namespace nagcpp;

struct test_array1D_element_get_set : public TestCase {
  void run() override {
    int n = 4;
    std::vector<int> dx = {1, 2, 3, 4};
    utility::array1D<int> v(dx.data(), n);
    ASSERT_EQUAL(v(0), 1);
    ASSERT_EQUAL(v(1), 2);
    ASSERT_EQUAL(v(2), 3);
    ASSERT_EQUAL(v(3), 4);
    bool passed = true;
    for (int i = 0; i < n && passed; ++i) {
      passed = (v(i) == dx[i]);
      if (!passed) {
        ASSERT_EQUAL(v(i), dx[i]);
      }
    }
    ASSERT_TRUE_LABELLED("dx vs v (changed)", passed);

    // change v
    v(2) = 15;
    ASSERT_EQUAL(v(0), 1);
    ASSERT_EQUAL(v(1), 2);
    ASSERT_EQUAL(v(2), 15);
    ASSERT_EQUAL(v(3), 4);
    passed = true;
    for (int i = 0; i < n && passed; ++i) {
      passed = (v(i) == dx[i]);
      if (!passed) {
        ASSERT_EQUAL(v(i), dx[i]);
      }
    }
    ASSERT_TRUE_LABELLED("dx vs v (changed)", passed);
  }
};
// clang-format off
REGISTER_TEST(test_array1D_element_get_set, "Test array1D () operator overload");
// clang-format on

struct test_array1D_element_get_const : public TestCase {
  void run() override {
    int n = 4;
    std::vector<int> dx = {1, 2, 3, 4};
    utility::array1D<int, data_handling::INOUT::IN> v(dx.data(), n);
    ASSERT_EQUAL(v(0), 1);
    ASSERT_EQUAL(v(1), 2);
    ASSERT_EQUAL(v(2), 3);
    ASSERT_EQUAL(v(3), 4);
    bool passed = true;
    for (int i = 0; i < n && passed; ++i) {
      passed = (v(i) == dx[i]);
      if (!passed) {
        ASSERT_EQUAL(v(i), dx[i]);
      }
    }
    ASSERT_TRUE_LABELLED("dx vs v", passed);
  }
};
// clang-format off
REGISTER_TEST(test_array1D_element_get_const, "Test array1D () operator overload (const)");
// clang-format on

struct test_array2D_element_get_set : public TestCase {
  void run() override {
    {
      SUB_TEST("col major order");
      int n1 = 5, n2 = 3;
      std::vector<int> dx = {11, 21, 31, 41, 51, 12, 22, 32,
                             42, 52, 13, 23, 33, 43, 53};
      utility::array2D<int> m(dx.data(), n1, n2, true);
      ASSERT_EQUAL(m(0, 0), 11);
      ASSERT_EQUAL(m(1, 0), 21);
      ASSERT_EQUAL(m(4, 0), 51);

      ASSERT_EQUAL(m(2, 1), 32);
      ASSERT_EQUAL(m(3, 1), 42);
      ASSERT_EQUAL(m(4, 1), 52);

      ASSERT_EQUAL(m(0, 2), 13);
      ASSERT_EQUAL(m(1, 2), 23);
      ASSERT_EQUAL(m(4, 2), 53);

      bool passed = true;
      for (int j = 0, px = 0; j < n2 && passed; ++j) {
        for (int i = 0; i < n1 && passed; ++i, ++px) {
          passed = (m(i, j) == dx[px]);
          if (!passed) {
            ASSERT_EQUAL(m(i, j), dx[px]);
          }
        }
      }
      ASSERT_TRUE_LABELLED("dx vs m (original)", passed);

      // change m
      m(3, 1) = 150;
      ASSERT_EQUAL(m(2, 1), 32);
      ASSERT_EQUAL(m(3, 1), 150);
      ASSERT_EQUAL(m(4, 1), 52);

      // check that dx updates when m changed
      passed = true;
      for (int j = 0, px = 0; j < n2 && passed; ++j) {
        for (int i = 0; i < n1 && passed; ++i, ++px) {
          passed = (m(i, j) == dx[px]);
          if (!passed) {
            ASSERT_EQUAL(m(i, j), dx[px]);
          }
        }
      }
      ASSERT_TRUE_LABELLED("dx vs m (changed)", passed);
    }
    {
      SUB_TEST("row major order");
      int n1 = 5, n2 = 3;
      std::vector<int> dx = {11, 12, 13, 21, 22, 23, 31, 32,
                             33, 41, 42, 43, 51, 52, 53};
      utility::array2D<int> m(dx.data(), n1, n2, false);
      ASSERT_EQUAL(m(0, 0), 11);
      ASSERT_EQUAL(m(1, 0), 21);
      ASSERT_EQUAL(m(4, 0), 51);

      ASSERT_EQUAL(m(2, 1), 32);
      ASSERT_EQUAL(m(3, 1), 42);
      ASSERT_EQUAL(m(4, 1), 52);

      ASSERT_EQUAL(m(0, 2), 13);
      ASSERT_EQUAL(m(1, 2), 23);
      ASSERT_EQUAL(m(4, 2), 53);

      bool passed = true;
      for (int i = 0, px = 0; i < n1 && passed; ++i) {
        for (int j = 0; j < n2 && passed; ++px, ++j) {
          passed = (m(i, j) == dx[px]);
          if (!passed) {
            ASSERT_EQUAL(m(i, j), dx[px]);
          }
        }
      }
      ASSERT_TRUE_LABELLED("dx vs m (original)", passed);

      // change m
      m(3, 1) = 150;
      ASSERT_EQUAL(m(2, 1), 32);
      ASSERT_EQUAL(m(3, 1), 150);
      ASSERT_EQUAL(m(4, 1), 52);

      // check that dx updates when m changed
      passed = true;
      for (int i = 0, px = 0; i < n1 && passed; ++i) {
        for (int j = 0; j < n2 && passed; ++j, ++px) {
          passed = (m(i, j) == dx[px]);
          if (!passed) {
            ASSERT_EQUAL(m(i, j), dx[px]);
          }
        }
      }
      ASSERT_TRUE_LABELLED("dx vs m (changed)", passed);
    }
  }
};
// clang-format off
REGISTER_TEST(test_array2D_element_get_set, "Test array2D () operator overload");
// clang-format on

struct test_array2D_element_get_const : public TestCase {
  void run() override {
    {
      SUB_TEST("col major order");
      int n1 = 5, n2 = 3;
      std::vector<int> dx = {11, 21, 31, 41, 51, 12, 22, 32,
                             42, 52, 13, 23, 33, 43, 53};
      utility::array2D<int, data_handling::INOUT::IN> m(dx.data(), n1, n2,
                                                        true);
      ASSERT_EQUAL(m(0, 0), 11);
      ASSERT_EQUAL(m(1, 0), 21);
      ASSERT_EQUAL(m(4, 0), 51);

      ASSERT_EQUAL(m(2, 1), 32);
      ASSERT_EQUAL(m(3, 1), 42);
      ASSERT_EQUAL(m(4, 1), 52);

      ASSERT_EQUAL(m(0, 2), 13);
      ASSERT_EQUAL(m(1, 2), 23);
      ASSERT_EQUAL(m(4, 2), 53);

      bool passed = true;
      for (int j = 0, px = 0; j < n2 && passed; ++j) {
        for (int i = 0; i < n1 && passed; ++i, ++px) {
          passed = (m(i, j) == dx[px]);
          if (!passed) {
            ASSERT_EQUAL(m(i, j), dx[px]);
          }
        }
      }
      ASSERT_TRUE_LABELLED("dx vs m", passed);
    }
    {
      SUB_TEST("row major order");
      int n1 = 5, n2 = 3;
      std::vector<int> dx = {11, 12, 13, 21, 22, 23, 31, 32,
                             33, 41, 42, 43, 51, 52, 53};
      utility::array2D<int, data_handling::INOUT::IN> m(dx.data(), n1, n2,
                                                        false);
      ASSERT_EQUAL(m(0, 0), 11);
      ASSERT_EQUAL(m(1, 0), 21);
      ASSERT_EQUAL(m(4, 0), 51);

      ASSERT_EQUAL(m(2, 1), 32);
      ASSERT_EQUAL(m(3, 1), 42);
      ASSERT_EQUAL(m(4, 1), 52);

      ASSERT_EQUAL(m(0, 2), 13);
      ASSERT_EQUAL(m(1, 2), 23);
      ASSERT_EQUAL(m(4, 2), 53);

      bool passed = true;
      for (int i = 0, px = 0; i < n1 && passed; ++i) {
        for (int j = 0; j < n2 && passed; ++px, ++j) {
          passed = (m(i, j) == dx[px]);
          if (!passed) {
            ASSERT_EQUAL(m(i, j), dx[px]);
          }
        }
      }
      ASSERT_TRUE_LABELLED("dx vs m", passed);
    }
  }
};
// clang-format off
REGISTER_TEST(test_array2D_element_get_const, "Test array2D () operator overload (const)");
// clang-format on

struct test_array3D_element_get_set : public TestCase {
  void run() override {
    {
      SUB_TEST("col major order");
      int n1 = 5, n2 = 4, n3 = 3;
      // clang-format off
      std::vector<int> dx = {111,211,311,411,511,
                             121,221,321,421,521,
                             131,231,331,431,531,
                             141,241,341,441,541,
                             112,212,312,412,512,
                             122,222,322,422,522,
                             132,232,332,432,532,
                             142,242,342,442,542,
                             113,213,313,413,513,
                             123,223,323,423,523,
                             133,233,333,433,533,
                             143,243,343,443,543};
      // clang-format on
      utility::array3D<int> m(dx.data(), n1, n2, n3, true);
      ASSERT_EQUAL(m(0, 0, 0), 111);
      ASSERT_EQUAL(m(1, 0, 0), 211);
      ASSERT_EQUAL(m(4, 0, 0), 511);

      ASSERT_EQUAL(m(2, 1, 1), 322);
      ASSERT_EQUAL(m(3, 1, 1), 422);

      ASSERT_EQUAL(m(0, 3, 2), 143);
      ASSERT_EQUAL(m(1, 3, 2), 243);
      ASSERT_EQUAL(m(4, 3, 2), 543);

      bool passed = true;
      for (int k = 0, px = 0; k < n3 && passed; ++k) {
        for (int j = 0; j < n2 && passed; ++j) {
          for (int i = 0; i < n1 && passed; ++i, ++px) {
            passed = (m(i, j, k) == dx[px]);
            if (!passed) {
              ASSERT_EQUAL(m(i, j, k), dx[px]);
            }
          }
        }
      }
      ASSERT_TRUE_LABELLED("dx vs m (original)", passed);

      // change m
      m(3, 2, 1) = 9999;
      ASSERT_EQUAL(m(2, 1, 1), 322);
      ASSERT_EQUAL(m(3, 2, 1), 9999);
      ASSERT_EQUAL(m(4, 1, 1), 522);

      // check that dx updates when m changed
      passed = true;
      for (int k = 0, px = 0; k < n3 && passed; ++k) {
        for (int j = 0; j < n2 && passed; ++j) {
          for (int i = 0; i < n1 && passed; ++i, ++px) {
            passed = (m(i, j, k) == dx[px]);
            if (!passed) {
              ASSERT_EQUAL(m(i, j, k), dx[px]);
            }
          }
        }
      }
      ASSERT_TRUE_LABELLED("dx vs m (changed)", passed);
    }
    {
      SUB_TEST("row major order");
      int n1 = 5, n2 = 4, n3 = 3;
      // clang-format off
      std::vector<int> dx = {111,112,113,121,122,123,131,132,133,141,142,143,
                             211,212,213,221,222,223,231,232,233,241,242,243,
                             311,312,313,321,322,323,331,332,333,341,342,343,
                             411,412,413,421,422,423,431,432,433,441,442,443,
                             511,512,513,521,522,523,531,532,533,541,542,543};
      // clang-format on
      utility::array3D<int> m(dx.data(), n1, n2, n3, false);
      ASSERT_EQUAL(m(0, 0, 0), 111);
      ASSERT_EQUAL(m(1, 0, 0), 211);
      ASSERT_EQUAL(m(4, 0, 0), 511);

      ASSERT_EQUAL(m(2, 1, 1), 322);
      ASSERT_EQUAL(m(3, 1, 1), 422);

      ASSERT_EQUAL(m(0, 3, 2), 143);
      ASSERT_EQUAL(m(1, 3, 2), 243);
      ASSERT_EQUAL(m(4, 3, 2), 543);

      bool passed = true;
      for (int i = 0, px = 0; i < n1 && passed; ++i) {
        for (int j = 0; j < n2 && passed; ++j) {
          for (int k = 0; k < n3 && passed; ++k, ++px) {
            passed = (m(i, j, k) == dx[px]);
            if (!passed) {
              ASSERT_EQUAL(m(i, j, k), dx[px]);
            }
          }
        }
      }
      ASSERT_TRUE_LABELLED("dx vs m (original)", passed);

      // change m
      m(3, 2, 1) = 9999;
      ASSERT_EQUAL(m(2, 1, 1), 322);
      ASSERT_EQUAL(m(3, 2, 1), 9999);
      ASSERT_EQUAL(m(4, 1, 1), 522);

      // check that dx updates when m changed
      passed = true;
      for (int i = 0, px = 0; i < n1 && passed; ++i) {
        for (int j = 0; j < n2 && passed; ++j) {
          for (int k = 0; k < n3 && passed; ++k, ++px) {
            passed = (m(i, j, k) == dx[px]);
            if (!passed) {
              ASSERT_EQUAL(m(i, j, k), dx[px]);
            }
          }
        }
      }
      ASSERT_TRUE_LABELLED("dx vs m (changed)", passed);
    }
  }
};
// clang-format off
REGISTER_TEST(test_array3D_element_get_set, "Test array3D () operator overload");
// clang-format on

struct test_array3D_element_get_const : public TestCase {
  void run() override {
    {
      SUB_TEST("col major order");
      int n1 = 5, n2 = 4, n3 = 3;
      // clang-format off
      std::vector<int> dx = {111,211,311,411,511,
                             121,221,321,421,521,
                             131,231,331,431,531,
                             141,241,341,441,541,
                             112,212,312,412,512,
                             122,222,322,422,522,
                             132,232,332,432,532,
                             142,242,342,442,542,
                             113,213,313,413,513,
                             123,223,323,423,523,
                             133,233,333,433,533,
                             143,243,343,443,543};
      // clang-format on
      utility::array3D<int, data_handling::INOUT::IN> m(dx.data(), n1, n2, n3,
                                                        true);
      ASSERT_EQUAL(m(0, 0, 0), 111);
      ASSERT_EQUAL(m(1, 0, 0), 211);
      ASSERT_EQUAL(m(4, 0, 0), 511);

      ASSERT_EQUAL(m(2, 1, 1), 322);
      ASSERT_EQUAL(m(3, 1, 1), 422);

      ASSERT_EQUAL(m(0, 3, 2), 143);
      ASSERT_EQUAL(m(1, 3, 2), 243);
      ASSERT_EQUAL(m(4, 3, 2), 543);

      bool passed = true;
      for (int k = 0, px = 0; k < n3 && passed; ++k) {
        for (int j = 0; j < n2 && passed; ++j) {
          for (int i = 0; i < n1 && passed; ++i, ++px) {
            passed = (m(i, j, k) == dx[px]);
            if (!passed) {
              ASSERT_EQUAL(m(i, j, k), dx[px]);
            }
          }
        }
      }
      ASSERT_TRUE_LABELLED("dx vs m", passed);
    }
    {
      SUB_TEST("row major order");
      int n1 = 5, n2 = 4, n3 = 3;
      // clang-format off
      std::vector<int> dx = {111,112,113,121,122,123,131,132,133,141,142,143,
                             211,212,213,221,222,223,231,232,233,241,242,243,
                             311,312,313,321,322,323,331,332,333,341,342,343,
                             411,412,413,421,422,423,431,432,433,441,442,443,
                             511,512,513,521,522,523,531,532,533,541,542,543};
      // clang-format on
      utility::array3D<int, data_handling::INOUT::IN> m(dx.data(), n1, n2, n3,
                                                        false);
      ASSERT_EQUAL(m(0, 0, 0), 111);
      ASSERT_EQUAL(m(1, 0, 0), 211);
      ASSERT_EQUAL(m(4, 0, 0), 511);

      ASSERT_EQUAL(m(2, 1, 1), 322);
      ASSERT_EQUAL(m(3, 1, 1), 422);

      ASSERT_EQUAL(m(0, 3, 2), 143);
      ASSERT_EQUAL(m(1, 3, 2), 243);
      ASSERT_EQUAL(m(4, 3, 2), 543);

      bool passed = true;
      for (int i = 0, px = 0; i < n1 && passed; ++i) {
        for (int j = 0; j < n2 && passed; ++j) {
          for (int k = 0; k < n3 && passed; ++k, ++px) {
            passed = (m(i, j, k) == dx[px]);
            if (!passed) {
              ASSERT_EQUAL(m(i, j, k), dx[px]);
            }
          }
        }
      }
      ASSERT_TRUE_LABELLED("dx vs m", passed);
    }
  }
};
// clang-format off
REGISTER_TEST(test_array3D_element_get_const, "Test array3D () operator overload (const)");
// clang-format on
