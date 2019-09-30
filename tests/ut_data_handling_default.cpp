// unit test for code in data_handling_default see also the tests in
// data_handling_XD unit tests (1D, 2D, 3D) etc
#include "include/cxxunit_testing.hpp"
#include "utility/nagcpp_data_handling_default.hpp"

using namespace nagcpp;

namespace test_case_dim_dim1 {
  class AAA {
  public:
    double size(void) { return 1; }
    Integer size1(void) { return 5; }
  };

  class BBB {
  public:
    unsigned int size1(void) { return 2; }
  };

  class CCC {
  public:
    long size(void) { return 3; }
  };

  class DDD {
  public:
  };
}

struct test_getDim : public TestCase {
  void run() override {
    using namespace test_case_dim_dim1;

    {
      SUB_TEST("size and size1");
      AAA a;
      auto a0 = data_handling::getDim(a, 0);
      ASSERT_EQUAL(a0.value, 1);
      ASSERT_TRUE(a0.set);
    }

    {
      SUB_TEST("size1 only");
      BBB b;
      auto b0 = data_handling::getDim(b, 0);
      ASSERT_EQUAL(b0.value, 2);
      ASSERT_TRUE(b0.set);
    }

    {
      SUB_TEST("size only");
      CCC c;
      auto c0 = data_handling::getDim(c, 0);
      ASSERT_EQUAL(c0.value, 3);
      ASSERT_TRUE(c0.set);
    }

    {
      SUB_TEST("neither size1 nor size");
      DDD d;
      auto d0 = data_handling::getDim(d, 0);
      ASSERT_EQUAL(d0.value, 0);
      ASSERT_FALSE(d0.set);
    }
  }
};
// clang-format off
REGISTER_TEST(test_getDim, "Test getDim");
// clang-format on

struct test_getDim1 : public TestCase {
  void run() override {
    using namespace test_case_dim_dim1;

    {
      SUB_TEST("size and size1");
      AAA a;
      auto a1 = data_handling::getDim1(a, 0);
      ASSERT_EQUAL(a1.value, 5);
      ASSERT_TRUE(a1.set);
    }

    {
      SUB_TEST("size1 only");
      BBB b;
      auto b1 = data_handling::getDim1(b, 0);
      ASSERT_EQUAL(b1.value, 2);
      ASSERT_TRUE(b1.set);
    }

    {
      SUB_TEST("size only");
      CCC c;
      auto c1 = data_handling::getDim1(c, 0);
      ASSERT_EQUAL(c1.value, 3);
      ASSERT_TRUE(c1.set);
    }

    {
      SUB_TEST("neither size nor size1");
      DDD d;
      auto d1 = data_handling::getDim1(d, 0);
      ASSERT_EQUAL(d1.value, 0);
      ASSERT_FALSE(d1.set);
    }
  }
};
// clang-format off
REGISTER_TEST(test_getDim1, "Test getDim1");
// clang-format on

struct test_getDim2 : public TestCase {
  class AAA {
  public:
    unsigned int size2(void) { return 2; }
  };
  class BBB {
  public:
  };

  void run() override {

    {
      SUB_TEST("size2 present");
      AAA a;
      auto da = data_handling::getDim2(a, 0);
      ASSERT_EQUAL(da.value, 2);
      ASSERT_TRUE(da.set);
    }

    {
      SUB_TEST("size2 not present");
      BBB b;
      auto db = data_handling::getDim2(b, 0);
      ASSERT_EQUAL(db.value, 0);
      ASSERT_FALSE(db.set);
    }
  }
};
// clang-format off
REGISTER_TEST(test_getDim2, "Test getDim2");
// clang-format on

struct test_getDim3 : public TestCase {
  class AAA {
  public:
    unsigned int size3(void) { return 2; }
  };
  class BBB {};

  void run() override {

    {
      SUB_TEST("size3 present");
      AAA a;
      auto da = data_handling::getDim3(a, 0);
      ASSERT_EQUAL(da.value, 2);
      ASSERT_TRUE(da.set);
    }

    {
      SUB_TEST("size3 not present");
      BBB b;
      auto db = data_handling::getDim3(b, 0);
      ASSERT_EQUAL(db.value, 0);
      ASSERT_FALSE(db.set);
    }
  }
};
// clang-format off
REGISTER_TEST(test_getDim3, "Test getDim3");
// clang-format on

struct test_getStorageOrder : public TestCase {
  class AAA {
    bool is_cm;

  public:
    AAA(bool cm) : is_cm(cm) {}
    bool is_col_major(void) { return is_cm; }
  };
  class BBB {};

  void run() override {

    {
      SUB_TEST("class has is_col_major");
      {
        AAA a1(true);
        auto so1 = data_handling::getStorageOrder(a1, 0);
        ASSERT_TRUE(a1.is_col_major());
        ASSERT_TRUE(so1.value);
        ASSERT_TRUE(so1.set);

        AAA a2(false);
        auto so2 = data_handling::getStorageOrder(a2, 0);
        ASSERT_FALSE(a2.is_col_major());
        ASSERT_FALSE(so2.value);
        ASSERT_TRUE(so2.set);
      }
    }

    {
      SUB_TEST("class doesn't have is_col_major");
      BBB b;
      auto so1 = data_handling::getStorageOrder(b, 0);
      ASSERT_FALSE(so1.set);
    }
  }
};
// clang-format off
REGISTER_TEST(test_getStorageOrder, "Test getStorageOrder");
// clang-format on

struct test_getNDims : public TestCase {
  class AAA0 {};
  class AAA1 {
  public:
    int ndims(void) { return 5; }
  };
  class AAA2 {
  public:
    int size1(void) { return 0; }
  };
  class AAA3 {
  public:
    int size(void) { return 3; }
  };
  class AAA4 {
  public:
    int size(void) { return 0; }
    int size1(void) { return 0; }
  };
  class BBB {
  public:
    int size1(void) { return 0; }
    int size2(void) { return 0; }
  };
  class CCC0 {
  public:
    int size1(void) { return 0; }
    int size2(void) { return 0; }
    int size3(void) { return 0; }
  };
  class CCC1 {
  public:
    int size(void) { return 0; }
    int size2(void) { return 0; }
    int size3(void) { return 0; }
  };
  class CCC2 {
  public:
    int size(void) { return 0; }
    int size1(void) { return 0; }
    int size2(void) { return 0; }
    int size3(void) { return 0; }
  };
  class DDD1 {
  public:
    int size1(void) { return 0; }
    int size3(void) { return 0; }
  };
  class DDD2 {
  public:
    int size2(void) { return 0; }
    int size3(void) { return 0; }
  };
  class EEE {
  public:
    int size1(void) { return 0; }
    int size2(void) { return 0; }
    int size3(void) { return 0; }
    int ndims(void) { return 6; }
  };

  void run() override {
    {
      SUB_TEST("no dim information");
      AAA0 a;

      auto nd = data_handling::getNDims(a, 0);
      ASSERT_EQUAL(nd.value, 0);
      ASSERT_FALSE(nd.set);
    }
    {
      SUB_TEST("just ndims method");
      AAA1 a;
      auto nd = data_handling::getNDims(a, 0);
      ASSERT_EQUAL(nd.value, 5);
      ASSERT_TRUE(nd.set);
    }
    {
      SUB_TEST("no ndims, ascertain from size methods (size1)");
      AAA2 a;
      auto nd = data_handling::getNDims(a, 0);
      ASSERT_EQUAL(nd.value, 1);
      ASSERT_TRUE(nd.set);
    }
    {
      SUB_TEST("no ndims, ascertain from size methods (size)");
      AAA3 a;
      auto nd = data_handling::getNDims(a, 0);
      ASSERT_EQUAL(nd.value, 1);
      ASSERT_TRUE(nd.set);
    }
    {
      SUB_TEST("no ndims, ascertain from size methods (size and size1)");
      AAA4 a;

      auto nd = data_handling::getNDims(a, 0);
      ASSERT_EQUAL(nd.value, 1);
      ASSERT_TRUE(nd.set);
    }
    {
      SUB_TEST("no ndims, ascertain from size methods (size1 and size2)");
      BBB b;
      auto nd = data_handling::getNDims(b, 0);
      ASSERT_EQUAL(nd.value, 2);
      ASSERT_TRUE(nd.set);
    }
    {
      SUB_TEST("no ndims, ascertain from size methods (size1, size2 and "
               "size3)");
      CCC0 c;
      auto nd = data_handling::getNDims(c, 0);
      ASSERT_EQUAL(nd.value, 3);
      ASSERT_TRUE(nd.set);
    }
    {
      SUB_TEST("no ndims, ascertain from size methods (size, size2 and size3)");
      CCC1 c;
      auto nd = data_handling::getNDims(c, 0);
      ASSERT_EQUAL(nd.value, 3);
      ASSERT_TRUE(nd.set);
    }
    {
      SUB_TEST("no ndims, ascertain from size methods (size, size1 and size2 "
               "and size3)");
      CCC2 c;
      auto nd = data_handling::getNDims(c, 0);
      ASSERT_EQUAL(nd.value, 3);
      ASSERT_TRUE(nd.set);
    }
    {
      SUB_TEST("no ndims, some size methods missing (size2 missing)");
      DDD1 d;
      auto nd = data_handling::getNDims(d, 0);
      ASSERT_EQUAL(nd.value, 1);
      ASSERT_TRUE(nd.set);
    }
    {
      SUB_TEST("no ndims, some size methods missing (size1 missing)");
      DDD2 d;
      auto nd = data_handling::getNDims(d, 0);
      ASSERT_EQUAL(nd.value, 0);
      ASSERT_FALSE(nd.set);
    }
    {
      SUB_TEST("take ndims in preference to presence of size");
      EEE e;
      auto nd = data_handling::getNDims(e, 0);
      ASSERT_EQUAL(nd.value, 6);
      ASSERT_TRUE(nd.set);
    }
  }
};
// clang-format off
REGISTER_TEST(test_getNDims, "Test getNDims");
// clang-format on

namespace test_case_resize {
  typedef unsigned int test_dim_type;
  class AAA {
  public:
    test_dim_type td1;
    test_dim_type td2;
    test_dim_type td3;
    AAA() : td1(1), td2(2), td3(3) {}
    void resize(test_dim_type d1) { td1 = d1; }
    void resize(test_dim_type d1, test_dim_type d2) {
      td1 = d1;
      td2 = d2;
    }
    void resize(test_dim_type d1, test_dim_type d2, test_dim_type d3) {
      td1 = d1;
      td2 = d2;
      td3 = d3;
    }
  };

  class BBB {};

  class M1 {
  public:
    test_dim_type td1;
    M1() : td1(1) {}
    void resize(test_dim_type d1) { td1 = d1; }
  };

  class M2 {
  public:
    test_dim_type td1;
    test_dim_type td2;
    M2() : td1(1), td2(2) {}
    void resize(test_dim_type d1, test_dim_type d2) {
      td1 = d1;
      td2 = d2;
    }
  };

  class M3 {
  public:
    test_dim_type td1;
    test_dim_type td2;
    test_dim_type td3;
    M3() : td1(1), td2(2), td3(3) {}
    void resize(test_dim_type d1, test_dim_type d2, test_dim_type d3) {
      td1 = d1;
      td2 = d2;
      td3 = d3;
    }
  };
} // namespace test_case_resize

struct test_resize1D : public TestCase {
  void run() override {
    {
      using namespace test_case_resize;

      {
        AAA a;
        data_handling::resize1D(a, 11, 0);
        ASSERT_EQUAL(a.td1, ((test_dim_type)11));
        ASSERT_EQUAL(a.td2, ((test_dim_type)2));
        ASSERT_EQUAL(a.td3, ((test_dim_type)3));
      }

      {
        BBB b;
        data_handling::resize1D(b, 21, 0);
        // nothing to test here, we are expecting
        // the call to resize to do nothing
      }

      {
        M1 m1;
        data_handling::resize1D(m1, 31, 0);
        ASSERT_EQUAL(m1.td1, ((test_dim_type)31));
      }

      {
        M2 m2;
        data_handling::resize1D(m2, 41, 0);
        ASSERT_EQUAL(m2.td1, ((test_dim_type)1));
      }
    }
  }
};
// clang-format off
REGISTER_TEST(test_resize1D, "Test resize1D");
// clang-format on

struct test_resize2D : public TestCase {
  void run() override {
    {
      using namespace test_case_resize;
      {
        AAA a;
        data_handling::resize2D(a, 11, 12, 0);
        ASSERT_EQUAL(a.td1, ((test_dim_type)11));
        ASSERT_EQUAL(a.td2, ((test_dim_type)12));
        ASSERT_EQUAL(a.td3, ((test_dim_type)3));
      }

      {
        BBB b;
        data_handling::resize2D(b, 21, 22, 0);
        // nothing to test here, we are expecting
        // the call to resize to do nothing
      }

      {
        M1 m1;
        data_handling::resize2D(m1, 31, 32, 0);
        ASSERT_EQUAL(m1.td1, ((test_dim_type)1));
      }

      {
        M2 m2;
        data_handling::resize2D(m2, 41, 42, 0);
        ASSERT_EQUAL(m2.td1, ((test_dim_type)41));
        ASSERT_EQUAL(m2.td2, ((test_dim_type)42));
      }

      {
        M3 m3;
        data_handling::resize2D(m3, 51, 52, 0);
        ASSERT_EQUAL(m3.td1, ((test_dim_type)1));
        ASSERT_EQUAL(m3.td2, ((test_dim_type)2));
      }
    }
  }
};
// clang-format off
REGISTER_TEST(test_resize2D, "Test resize2D");
// clang-format on

struct test_resize3D : public TestCase {
  void run() override {
    {
      using namespace test_case_resize;
      {
        AAA a;
        data_handling::resize3D(a, 11, 12, 13, 0);
        ASSERT_EQUAL(a.td1, ((test_dim_type)11));
        ASSERT_EQUAL(a.td2, ((test_dim_type)12));
        ASSERT_EQUAL(a.td3, ((test_dim_type)13));
      }

      {
        BBB b;
        data_handling::resize3D(b, 21, 22, 23, 0);
        // nothing to test here, we are expecting
        // the call to resize to do nothing
      }

      {
        M1 m1;
        data_handling::resize3D(m1, 31, 32, 33, 0);
        ASSERT_EQUAL(m1.td1, ((test_dim_type)1));
      }

      {
        M2 m2;
        data_handling::resize3D(m2, 41, 42, 43, 0);
        ASSERT_EQUAL(m2.td1, ((test_dim_type)1));
        ASSERT_EQUAL(m2.td2, ((test_dim_type)2));
      }

      {
        M3 m3;
        data_handling::resize3D(m3, 51, 52, 53, 0);
        ASSERT_EQUAL(m3.td1, ((test_dim_type)51));
        ASSERT_EQUAL(m3.td2, ((test_dim_type)52));
        ASSERT_EQUAL(m3.td3, ((test_dim_type)53));
      }
    }
  }
};
// clang-format off
REGISTER_TEST(test_resize3D, "Test resize3D");
// clang-format on

struct test_getData : public TestCase {
  class AAA {
  public:
    double *p;
    AAA(void) {
      p = new double[5];
      p[0] = 1.0;
      p[1] = 2.0;
      p[2] = 3.0;
      p[3] = 4.0;
      p[4] = 5.0;
    }
    ~AAA(void) { delete[] p; }
    double *data(void) { return p; }
  };
  class BBB {};

  void run() override {
    {
      SUB_TEST("has data method");
      AAA a;
      double *dp = data_handling::getData<double>(a, 0);
      ASSERT_EQUAL(a.p, dp);
      ASSERT_EQUAL(dp[0], 1.0);
      ASSERT_EQUAL(dp[1], 2.0);
      ASSERT_EQUAL(dp[2], 3.0);
      ASSERT_EQUAL(dp[3], 4.0);
      ASSERT_EQUAL(dp[4], 5.0);
      dp[2] = 10.0;
      dp[4] = 20.0;
      ASSERT_EQUAL(dp[2], 10.0);
      ASSERT_EQUAL(dp[4], 20.0);
    }
    {
      SUB_TEST("no data method");
      BBB b;
      double *dp = data_handling::getData<double>(b, 0);
      ASSERT_FALSE((dp));
    }
  }
};
// clang-format off
REGISTER_TEST(test_getData, "Test getData");
// clang-format on

struct test_has_method_functions : public TestCase {
  void run() override {
    struct has_all_methods {
      void size(void) {}
      void size1(void) {}
      void size2(void) {}
      void size3(void) {}
      void is_col_major(void) {}
      void data(void) {}
      void ndims(void) {}
      void resize(void) {}
    };
    struct has_no_methods {};

    ASSERT_TRUE((data_handling::has_size<has_all_methods, int>()));
    ASSERT_TRUE((data_handling::has_size1<has_all_methods, int>()));
    ASSERT_TRUE((data_handling::has_size2<has_all_methods, int>()));
    ASSERT_TRUE((data_handling::has_size3<has_all_methods, int>()));
    ASSERT_TRUE((data_handling::has_is_col_major<has_all_methods, int>()));
    ASSERT_TRUE((data_handling::has_data<has_all_methods, int>()));
    ASSERT_TRUE((data_handling::has_ndims<has_all_methods, int>()));

    ASSERT_FALSE((data_handling::has_size<has_no_methods, int>()));
    ASSERT_FALSE((data_handling::has_size1<has_no_methods, int>()));
    ASSERT_FALSE((data_handling::has_size2<has_no_methods, int>()));
    ASSERT_FALSE((data_handling::has_size3<has_no_methods, int>()));
    ASSERT_FALSE((data_handling::has_is_col_major<has_no_methods, int>()));
    ASSERT_FALSE((data_handling::has_data<has_no_methods, int>()));
    ASSERT_FALSE((data_handling::has_ndims<has_no_methods, int>()));
  }
};
// clang-format off
REGISTER_TEST(test_has_method_functions, "Test trait functions for checking if a method exists");
// clang-format on
