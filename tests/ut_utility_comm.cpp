// unit test for code in nagcpp_utility_comm
#include "include/cxxunit_testing.hpp"
#include "utility/nagcpp_utility_comm.hpp"
#include <type_traits>

using namespace nagcpp;

class NN : public utility::NoneCopyableComm {};
class CC : public utility::CopyableComm {};

struct test_noncopyable : public TestCase {
  void run() override {
    {
      SUB_TEST("construction");
      utility::NoneCopyableComm a;
      ASSERT_TRUE((a.handle == nullptr));
    }
    {
      SUB_TEST("not copyable");
      ASSERT_FALSE((std::is_assignable<utility::NoneCopyableComm,
                                       utility::NoneCopyableComm>::value));
      ASSERT_FALSE((std::is_copy_assignable<utility::NoneCopyableComm>::value));
      ASSERT_FALSE(
        (std::is_copy_constructible<utility::NoneCopyableComm>::value));
    }
    {
      SUB_TEST("child class not copyable");
      ASSERT_FALSE((std::is_assignable<NN, NN>::value));
      ASSERT_FALSE((std::is_copy_assignable<NN>::value));
      ASSERT_FALSE((std::is_copy_constructible<NN>::value));
    }
  }
};
// clang-format off
REGISTER_TEST(test_noncopyable, "Test noncopyable");
// clang-format on

struct test_copyable : public TestCase {
  void run() override {
    {
      SUB_TEST("construction");
      utility::CopyableComm a;
      ASSERT_TRUE((a.handle == nullptr));
    }
    {
      SUB_TEST("copyable");
      ASSERT_TRUE((std::is_assignable<utility::CopyableComm,
                                      utility::CopyableComm>::value));
      ASSERT_TRUE((std::is_copy_assignable<utility::CopyableComm>::value));
      ASSERT_TRUE((std::is_copy_constructible<utility::CopyableComm>::value));
    }
    {
      SUB_TEST("child class copyable");
      ASSERT_TRUE((std::is_assignable<CC, CC>::value));
      ASSERT_TRUE((std::is_copy_assignable<CC>::value));
      ASSERT_TRUE((std::is_copy_constructible<CC>::value));
    }
    {
      SUB_TEST("allocate / deallocate");
      utility::CopyableComm a;
      a.allocate(3);
      ASSERT_EQUAL(a.lrcomm, 3);
      ASSERT_EQUAL(a.licomm, 0);
      ASSERT_EQUAL(a.lccomm, 0);
      ASSERT_EQUAL(a.llcomm, 0);
      ASSERT_EQUAL(a.ccomm_length, 0);
      a.deallocate();
      ASSERT_EQUAL(a.lrcomm, 0);
      ASSERT_EQUAL(a.licomm, 0);
      ASSERT_EQUAL(a.lccomm, 0);
      ASSERT_EQUAL(a.llcomm, 0);
      ASSERT_EQUAL(a.ccomm_length, 0);
      a.allocate(5, 4, 2, 3);
      a.rcomm[1] = 3.0;
      a.icomm[0] = 1;
      a.ccomm[1] = 'c';
      a.lcomm[2] = 1;
      ASSERT_EQUAL(a.lrcomm, 5);
      ASSERT_EQUAL(a.licomm, 4);
      ASSERT_EQUAL(a.lccomm, 2);
      ASSERT_EQUAL(a.llcomm, 3);
      ASSERT_EQUAL(a.ccomm_length, 1);
      a.deallocate();
      ASSERT_EQUAL(a.lrcomm, 0);
      ASSERT_EQUAL(a.licomm, 0);
      ASSERT_EQUAL(a.lccomm, 0);
      ASSERT_EQUAL(a.llcomm, 0);
      ASSERT_EQUAL(a.ccomm_length, 0);
    }
    {
      SUB_TEST("assignment operator");
      // set up a1
      utility::CopyableComm a1;
      a1.allocate(5, 4, 3, 2);
      a1.rcomm[0] = 5.0;
      a1.rcomm[4] = 2.0;
      a1.icomm[0] = 3;
      a1.icomm[3] = 6;
      a1.ccomm[0] = 'a';
      a1.ccomm[2] = 'b';
      a1.lcomm[0] = 1;
      a1.lcomm[1] = 50;

      utility::CopyableComm a2;

      // shove random noise into a2
      a2.allocate(15, 14, 13, 12);
      a2.rcomm[0] = 115.0;
      a2.rcomm[4] = 112.0;
      a2.icomm[0] = 113;
      a2.icomm[3] = 116;
      a2.ccomm[0] = 'A';
      a2.ccomm[2] = 'B';
      a2.lcomm[0] = 111;
      a2.lcomm[1] = 1150;
      ASSERT_EQUAL(a2.lrcomm, 15);
      ASSERT_EQUAL(a2.licomm, 14);
      ASSERT_EQUAL(a2.lccomm, 13);
      ASSERT_EQUAL(a2.llcomm, 12);

      // copy a1 into a2
      a2 = a1;

      // delete a1
      a1.deallocate();

      // check a2 has the data put into a1
      ASSERT_EQUAL(a2.lrcomm, 5);
      ASSERT_EQUAL(a2.licomm, 4);
      ASSERT_EQUAL(a2.lccomm, 3);
      ASSERT_EQUAL(a2.llcomm, 2);
      ASSERT_EQUAL(a2.rcomm[0], 5.0);
      ASSERT_EQUAL(a2.rcomm[4], 2.0);
      ASSERT_EQUAL(a2.icomm[0], 3);
      ASSERT_EQUAL(a2.icomm[3], 6);
      ASSERT_EQUAL(a2.ccomm[0], 'a');
      ASSERT_EQUAL(a2.ccomm[2], 'b');
      ASSERT_EQUAL(a2.lcomm[0], 1);
      ASSERT_EQUAL(a2.lcomm[1], 50);
    }
    {
      SUB_TEST("copy constructor");
      utility::CopyableComm a1;

      // set up a1
      a1.allocate(5, 4, 3, 2);
      a1.rcomm[0] = 5.0;
      a1.rcomm[4] = 2.0;
      a1.icomm[0] = 3;
      a1.icomm[3] = 6;
      a1.ccomm[0] = 'a';
      a1.ccomm[2] = 'b';
      a1.lcomm[0] = 1;
      a1.lcomm[1] = 50;

      // create a2 and copy in a1
      utility::CopyableComm a2 = utility::CopyableComm(a1);

      // delete a1

      // check a2 has the data put into a1
      ASSERT_EQUAL(a2.rcomm[0], 5.0);
      ASSERT_EQUAL(a2.rcomm[4], 2.0);
      ASSERT_EQUAL(a2.icomm[0], 3);
      ASSERT_EQUAL(a2.icomm[3], 6);
      ASSERT_EQUAL(a2.ccomm[0], 'a');
      ASSERT_EQUAL(a2.ccomm[2], 'b');
      ASSERT_EQUAL(a2.lcomm[0], 1);
      ASSERT_EQUAL(a2.lcomm[1], 50);
    }
  }
};
// clang-format off
REGISTER_TEST(test_copyable, "Test copyable");
// clang-format on
