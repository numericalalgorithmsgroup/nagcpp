// unit tests for 1D classes that may be passed into a NAG routine
#include "../examples/include/nag_my_data.hpp"
#include "../examples/include/nag_my_vector.hpp"
#include "include/cxxunit_testing.hpp"
#include "include/nagcpp_ut_generate_data.hpp"
#include "include/nagcpp_ut_utilities.hpp"
#include "include/nagcpp_ut_utility_array_wrapper.hpp"
#include "utility/nagcpp_data_handling.hpp"
#include "utility/nagcpp_error_handler.hpp"
#include "utility/nagcpp_utility_array.hpp"
#include <algorithm>
#include <memory>
#include <type_traits>

using namespace nagcpp;

// clang-format off

// to test custom types, add a corresponding call to run_this
// in one or more of these #defines (see SUPPORT_TYPES_TO_TEST_WRAPPERS etc)
// a call to run_this should be added to ADDITIONAL_TYPES_TO_TEST_WRAPPERS
// if the type will be used as an argument to a NAG routine
// a call to run_this should be added to ADDITIONAL_TYPES_TO_TEST_CALLBACKS
// if the type will be used as an argument to a callback routine
// (if it will be used to both an entry should be added to both #defines)
#define ADDITIONAL_TYPES_TO_TEST_WRAPPERS
#define ADDITIONAL_TYPES_TO_TEST_CALLBACKS

// in addition you need to supply a specialisation of the test_setup struct
// for your type (see below)

// run_this is a method that runs an individual unit test,
// all have the same prototype:
//   template <typename RT, enum data_handling::ArgIntent inout, typename AC>
//   void run_this(std::string label="")
//   AC     - type that will be used as an argument to a NAG routine
//            (for example std::vector<double>)
//   inout  - whether the AC type will be used for input, output or
//            input / output arguement, if it will be used for all three
//            then there needs to be three calls to run_this
//            (different subset of tests are run depending on the value of this)
//   RT     - type of the underlying NAG array the type being tested will be used
//            as an argument for (double, types::f77_integer etc)
//   label  - descriptive label summarising the AC, inout, RT information
//            used in output if tests fail
// NB: run_this has a final template argument (type_is, this need only
//     be supplied for internal tests)

// in order to run this test suite over a custom type a specialisation
// of the test_setup structure must be supplied.
// (assuming that the generic one doesn't work)
// the test_setup structure has the following static methods
// (where AC is the type of the custom type and RT is the type of the
// data it holds and are the same as the types of the same name in the
// call to run_this)
// std::unique_ptr<AC> get_test_data(const size_t n1);
//    return an smart pointer to an instance of type A
//    if n1 > 0, then this should hold a vector of size n1 and
//    set_values should be run to populate the vector
//    if n1 <= 0, then the type should be set up in such a way that
//    when the the underlying (contiguous) data array is requested a
//    null pointer is returned (i.e. it has not been allocated)
// void set_values(AC &ac);
//    populate the ac with the values returned by ut::get_expected_values
// RT max_abs_diff(const AC &observed, const std::vector<RT> &expected,
//                 const size_t n1);
//    return the maximum absolute difference between the first n1 elements
//    of the data stored in expected and observed.
// bool check_meta_info(const AC &ac, const size_t n1)
//    return true if any meta information stored in ac is correct
//    n1 = length of the vector
//    (if there is no meta information stored, return true)
// the default test_setup has four template parameters
//   RT      - type of the underlying data (double or types::f77_integer)
//   inout   - data_handling::ArgIntent value indicating whether the class
//             being tested will be used as an input (IN), output (OUT)
//             or input / output (INOUT) argument
//   AC      - type of the class being tested
//   type_is - should be left at its default value, used to identify
//             internal types

// NB: this test suite runs:
//   9 tests on types used in wrappers
//      of which only 5 are run on data_handling::ArgIntent::IN classes
//      (or internal ones) and (max of) 7 are run if ut::has_resize
//      is false
//   1 test on types used in callbacks

// easiest way to run a single test is to use search-and-replace to comment out
// "REGISTER_TEST" and then manually uncomment the one you want to run

// clang-format on
template <typename RT, enum data_handling::ArgIntent inout, typename AC,
          ut::TYPE_IS type_is = ut::TYPE_IS::GENERAL>
struct test_setup;

// some utility functions that may be of use in specialisations of test_setup ...
namespace test_setup_utilities {
  template <typename RT, typename AC>
  static void set_expected_results(AC &ac, const size_t n1) {
    std::vector<RT> expected_results = ut::get_expected_values<RT>(n1);
    for (size_t i = 0; i < n1; ++i) {
      ac(i) = expected_results[i];
    }
  }
  template <typename RT, typename AC>
  static RT get_max_abs_diff(const AC &observed,
                             const std::vector<RT> &expected, const size_t n1) {
    // return maximum absolute difference between observed and expected
    RT max_diff = 0;
    for (size_t i = 0; i < n1; ++i) {
      RT this_diff = static_cast<RT>(std::fabs(
        static_cast<double>(observed(i)) - static_cast<double>(expected[i])));
      max_diff = std::max(this_diff, max_diff);
    }
    return max_diff;
  }
}
// ... some utility functions that may be of use in specialisations of test_setup

// structure to allow tests to be run on a boost types ...
#include "include/nagcpp_ut_boost_vector_test_setup.hpp"
// ... structure to allow tests to be run on a boost types

// structure to allow tests to be run on std::vector ...
template <typename RT, enum data_handling::ArgIntent inout, typename VRT>
struct test_setup<RT, inout, std::vector<VRT>> {
  using AC = std::vector<VRT>;
  static std::unique_ptr<AC> get_test_data(const size_t n1) {
    if (n1 > 0) {
      // return a populated array of the stated size
      std::unique_ptr<AC> ac = std::unique_ptr<AC>(new AC(n1));
      set_values(*ac);
      return ac;

    } else {
      // return an array where the data class variable is a null pointer
      std::unique_ptr<AC> ac = std::unique_ptr<AC>(new AC());
      return ac;
    }
  }
  static void set_values(AC &ac) {
    // set ac to values returned by the get_expected_values function
    size_t n1 = static_cast<size_t>(ac.size());
    std::vector<VRT> expected_results = ut::get_expected_values<VRT>(n1);
    for (size_t i = 0; i < n1; ++i) {
      ac[i] = expected_results[i];
    }
  }
  static RT max_abs_diff(const AC &observed, const std::vector<RT> &expected,
                         const size_t n1) {
    // return maximum absolute difference between observed and expected
    RT max_diff = 0;
    for (size_t i = 0; i < n1; ++i) {
      RT this_diff = static_cast<RT>(std::fabs(
        static_cast<double>(observed[i]) - static_cast<double>(expected[i])));
      max_diff = std::max(this_diff, max_diff);
    }
    return max_diff;
  }
  static bool check_meta_info(const AC &ac, const size_t n1) {
    auto ndims = 1;
    auto size1 = ac.size();
    return (static_cast<size_t>(ndims) == 1 &&
            static_cast<size_t>(size1) == n1);
  }
};
// ... structure to allow tests to be run on std::vector

// structure to allow tests to be run on (some) arbitrary types ...
template <typename RT, enum data_handling::ArgIntent inout, typename AC,
          ut::TYPE_IS type_is>
struct test_setup {
  using UPAC = std::unique_ptr<AC>;

  template <typename DUMMY = UPAC>
  static auto get_test_data(const size_t n1) ->
    typename std::enable_if<ut::is_const_data_pointer_type<type_is>::value,
                            DUMMY>::type {
    if (n1 > 0) {
      // return a populated array of the stated size
      std::vector<RT> expected_results = ut::get_expected_values<RT>(n1);
      UPAC ac = std::unique_ptr<AC>(new AC(expected_results, n1));
      return ac;

    } else {
      // return an array where the data class variable is a null pointer
      UPAC ac = std::unique_ptr<AC>(new AC());
      return ac;
    }
  }
  template <typename DUMMY = UPAC>
  static auto get_test_data(const size_t n1) ->
    typename std::enable_if<!ut::is_const_data_pointer_type<type_is>::value,
                            DUMMY>::type {
    if (n1 > 0) {
      // return a populated array of the stated size
      UPAC ac = std::unique_ptr<AC>(new AC(n1));
      set_values(*ac);
      return ac;

    } else {
      // return an array where the data class variable is a null pointer
      UPAC ac = std::unique_ptr<AC>(new AC());
      return ac;
    }
  }
  template <typename DUMMY = void>
  static auto set_values(AC &ac) ->
    typename std::enable_if<!ut::is_internal_type<type_is>::value,
                            DUMMY>::type {
    auto size1 = data_handling::getDim1(ac, 0);
    size_t n1 = static_cast<size_t>(size1.value);
    test_setup_utilities::set_expected_results<RT, AC>(ac, n1);
  }
  template <typename DUMMY = void>
  static auto set_values(AC &ac) ->
    typename std::enable_if<ut::is_internal_type<type_is>::value, DUMMY>::type {
    nagcpp::error_handler::ErrorHandler eh;
    size_t n1 = data_handling::get_size(eh, "AC", ac, 1);
    test_setup_utilities::set_expected_results<RT, AC>(ac, n1);
  }
  static RT max_abs_diff(const AC &observed, const std::vector<RT> &expected,
                         const size_t n1) {
    // return maximum absolute difference between observed and expected
    return test_setup_utilities::get_max_abs_diff<RT, AC>(observed, expected,
                                                          n1);
  }
  template <typename DUMMY = bool>
  static auto check_meta_info(const AC &ac, const size_t n1) ->
    typename std::enable_if<!ut::is_internal_type<type_is>::value,
                            DUMMY>::type {
    auto ndim = data_handling::getNDims(ac, 0);
    auto size1 = data_handling::getDim1(ac, 0);
    return ((ndim.set && ndim.value == 1) &&
            (size1.set && static_cast<size_t>(size1.value) == n1));
  }
  template <typename DUMMY = bool>
  static auto check_meta_info(const AC &ac, const size_t n1) ->
    typename std::enable_if<ut::is_internal_type<type_is>::value, DUMMY>::type {
    nagcpp::error_handler::ErrorHandler eh;
    auto size1 = data_handling::get_size(eh, "AC", ac, 1);
    return (static_cast<size_t>(size1) == n1);
  }
};
// ... structure to allow tests to be run on (some) arbitrary type

// clang-format off
// #defines for supported types
#define SUPPORTED_TYPES_TO_TEST_BOTH \
  run_this<double, data_handling::ArgIntent::IN, std::vector<double>>("std::vector<double>, double, IN"); \
  run_this<double, data_handling::ArgIntent::OUT, std::vector<double>>("std::vector<double>, double, OUT"); \
  run_this<double, data_handling::ArgIntent::INOUT, std::vector<double>>("std::vector<double>, double, INOUT"); \
  run_this<types::f77_integer, data_handling::ArgIntent::IN, std::vector<types::f77_integer>>("std::vector<f77_integer>, f77_integer, IN"); \
  run_this<types::f77_integer, data_handling::ArgIntent::INOUT, std::vector<types::f77_integer>>("std::vector<f77_integer>, f77_integer, INOUT"); \
  run_this<types::f77_integer, data_handling::ArgIntent::OUT, std::vector<types::f77_integer>>("std::vector<f77_integer>, f77_integer, OUT");

// NB: MyVector and MyData are supplied as samples of how to write a custom
// data class that can be used by the NAG interfaces (see example directory)
// the array1D_wrapper class is a wrapper around array1D
#define SUPPORTED_TYPES_TO_TEST_WRAPPERS \
  SUPPORTED_TYPES_TO_TEST_BOTH \
  run_this<double, data_handling::ArgIntent::IN, MyVector<double>>("MyVector<double>. double, IN"); \
  run_this<double, data_handling::ArgIntent::OUT, MyVector<double>>("MyVector<double>, double, OUT"); \
  run_this<double, data_handling::ArgIntent::INOUT, MyVector<double>>("MyVector<double>, double, INOUT"); \
  run_this<types::f77_integer, data_handling::ArgIntent::IN, MyVector<types::f77_integer>>("MyVector<f77_integer>, f77_integer, IN"); \
  run_this<types::f77_integer, data_handling::ArgIntent::OUT, MyVector<types::f77_integer>>("MyVector<f77_integer>, f77_integer, OUT"); \
  run_this<types::f77_integer, data_handling::ArgIntent::INOUT, MyVector<types::f77_integer>>("MyVector<f77_integer> f77_integer, INOUT"); \
  run_this<double, data_handling::ArgIntent::IN, MyData<double>>("MyData<double>, double, IN"); \
  run_this<double, data_handling::ArgIntent::OUT, MyData<double>>("MyData<double>, double, OUT"); \
  run_this<double, data_handling::ArgIntent::INOUT, MyData<double>>("MyData<double>, double, INOUT"); \
  run_this<types::f77_integer, data_handling::ArgIntent::IN, MyData<types::f77_integer>>("MyData<f77_integer>, f77_integer, IN"); \
  run_this<types::f77_integer, data_handling::ArgIntent::OUT, MyData<types::f77_integer>>("MyData<f77_integer>, f77_integer, OUT"); \
  run_this<types::f77_integer, data_handling::ArgIntent::INOUT, MyData<types::f77_integer>>("MyData<f77_integer>, f77_integer, INOUT"); \
  run_this<double, data_handling::ArgIntent::IN, ut::array1D_wrapper<double, data_handling::ArgIntent::IN>, ut::TYPE_IS::CONST_DATA_POINTER>("ut::array1D_wrapper<double, IN>, double, IN"); \
  run_this<double, data_handling::ArgIntent::OUT, ut::array1D_wrapper<double, data_handling::ArgIntent::OUT>, ut::TYPE_IS::CONST_DATA_POINTER>("ut::array1D_wrapper<double, OUT>, double, OUT"); \
  run_this<double, data_handling::ArgIntent::INOUT, ut::array1D_wrapper<double, data_handling::ArgIntent::INOUT>, ut::TYPE_IS::CONST_DATA_POINTER>("ut::array1D_wrapper<double, INOUT>, double, INOUT"); \
  run_this<types::f77_integer, data_handling::ArgIntent::IN, ut::array1D_wrapper<types::f77_integer, data_handling::ArgIntent::IN>, ut::TYPE_IS::CONST_DATA_POINTER>("ut::array1D_wrapper<f77_integer, IN>, f77_integer, IN"); \
  run_this<types::f77_integer, data_handling::ArgIntent::OUT, ut::array1D_wrapper<types::f77_integer, data_handling::ArgIntent::OUT>, ut::TYPE_IS::CONST_DATA_POINTER>("ut::array1D_wrapper<f77_integer, OUT>, f77_integer, OUT"); \
  run_this<types::f77_integer, data_handling::ArgIntent::INOUT, ut::array1D_wrapper<types::f77_integer, data_handling::ArgIntent::INOUT>, ut::TYPE_IS::CONST_DATA_POINTER>("ut::array1D_wrapper<f77_integer, INOUT>, f77_integer, INOUT"); \
  BOOST_1D_TYPES_TO_TEST_WRAPPERS

#define SUPPORTED_TYPES_TO_TEST_CALLBACKS \
  SUPPORTED_TYPES_TO_TEST_BOTH \
  run_this<double, data_handling::ArgIntent::IN, utility::array1D<double, data_handling::ArgIntent::IN>, ut::TYPE_IS::CONST_DATA_POINTER>("ut::array1D<double, IN>, double, IN"); \
  run_this<double, data_handling::ArgIntent::OUT, utility::array1D<double, data_handling::ArgIntent::OUT>, ut::TYPE_IS::CONST_DATA_POINTER>("ut::array1D<double, OUT>, double, OUT"); \
  run_this<double, data_handling::ArgIntent::INOUT, utility::array1D<double, data_handling::ArgIntent::INOUT>, ut::TYPE_IS::CONST_DATA_POINTER>("ut::array1D<double, INOUT>, double, INOUT"); \
  run_this<types::f77_integer, data_handling::ArgIntent::IN, utility::array1D<types::f77_integer, data_handling::ArgIntent::IN>, ut::TYPE_IS::CONST_DATA_POINTER>("ut::array1D<f77_integer, IN>, f77_integer, IN"); \
  run_this<types::f77_integer, data_handling::ArgIntent::OUT, utility::array1D<types::f77_integer, data_handling::ArgIntent::OUT>, ut::TYPE_IS::CONST_DATA_POINTER>("ut::array1D<f77_integer, OUT>, f77_integer, OUT"); \
  run_this<types::f77_integer, data_handling::ArgIntent::INOUT, utility::array1D<types::f77_integer, data_handling::ArgIntent::INOUT>, ut::TYPE_IS::CONST_DATA_POINTER>("ut::array1D<f77_integer, INOUT>, f77_integer, INOUT"); \
  BOOST_1D_TYPES_TO_TEST_WRAPPERS

// #defines for internal types (these are not expected to be used as
// input to NAG routines, but are leveraging some of the same tests)
// (RawData<RT,inout> can potentially be used for local arrays, but
// never with data_handling::ArgIntent::IN)
#define INTERNAL_TYPES_TO_TEST_WRAPPERS \
  run_this<double, data_handling::ArgIntent::OUT, data_handling::RawData<double, data_handling::ArgIntent::OUT>, ut::TYPE_IS::INTERNAL> ("RawData<double, OUT>, double, OUT"); \
  run_this<double, data_handling::ArgIntent::INOUT, data_handling::RawData<double, data_handling::ArgIntent::INOUT>, ut::TYPE_IS::INTERNAL> ("RawData<double, INOUT>, double, INOUT"); \
  run_this<types::f77_integer, data_handling::ArgIntent::OUT, data_handling::RawData<types::f77_integer, data_handling::ArgIntent::OUT>, ut::TYPE_IS::INTERNAL> ("RawData<f77_integer, OUT>, f77_integer, OUT"); \
  run_this<types::f77_integer, data_handling::ArgIntent::INOUT, data_handling::RawData<types::f77_integer, data_handling::ArgIntent::INOUT>, ut::TYPE_IS::INTERNAL> ("RawData<f77_integer, INOUT>, f77_integer, INOUT");

// #define used to set up tests for types valid in main wrappers
#define DEFINE_RUN_METHOD_WRAPPERS \
  void run() override { \
    ADDITIONAL_TYPES_TO_TEST_WRAPPERS \
    SUPPORTED_TYPES_TO_TEST_WRAPPERS \
    INTERNAL_TYPES_TO_TEST_WRAPPERS \
  }

// #define used to set up tests for types valid in callbacks
#define DEFINE_RUN_METHOD_CALLBACKS \
  void run() override { \
    ADDITIONAL_TYPES_TO_TEST_CALLBACKS \
    SUPPORTED_TYPES_TO_TEST_CALLBACKS \
  }
// clang-format on

//******************************************************************************
//******************************************************************************
//******************************************************************************
// unit tests are from this point onwards

// NB: we usually want to pass the users type through RawData in these
// tests, to mimic what the wrappers do, however for internal test
// the "users" type is already RawData so we want to directly test it
// (which is why there is the
//   run_this -> call_test -> do_test
// setup)

// tests related to using the type as an argument to a NAG routine ...
struct test_get_size_function : public TestCase {
  DEFINE_RUN_METHOD_WRAPPERS

  template <typename RT, enum data_handling::ArgIntent inout, typename AC,
            enum ut::TYPE_IS type_is = ut::TYPE_IS::GENERAL>
  void run_this(std::string label = "") {
    SUB_TITLE(label);
    static const size_t n1 = 10;
    std::unique_ptr<AC> ac1 =
      test_setup<RT, inout, AC, type_is>::get_test_data(n1);

    static const size_t n2 = 20;
    std::unique_ptr<AC> ac2 =
      test_setup<RT, inout, AC, type_is>::get_test_data(n2);

    call_test<RT, inout, AC, type_is>(ac1, ac2, n1);
  }

  template <typename RT, enum data_handling::ArgIntent inout, typename AC,
            enum ut::TYPE_IS type_is>
  auto call_test(std::unique_ptr<AC> &ac1, std::unique_ptr<AC> &ac2, size_t n1)
    ->
    typename std::enable_if<!ut::is_internal_type<type_is>::value, void>::type {
    using RD = data_handling::RawData<RT, inout, AC>;
    RD local_ac1(*ac1);
    RD local_ac2(*ac2);
    do_test<RD>(local_ac1, local_ac2, n1);
  }
  template <typename RT, enum data_handling::ArgIntent inout, typename AC,
            enum ut::TYPE_IS type_is>
  auto call_test(std::unique_ptr<AC> &ac1, std::unique_ptr<AC> &ac2, size_t n1)
    ->
    typename std::enable_if<ut::is_internal_type<type_is>::value, void>::type {
    do_test<AC>(*ac1, *ac2, n1);
  }

  template <typename RD>
  void do_test(RD &local_ac1, RD &local_ac2, size_t n1) {
    nagcpp::error_handler::ErrorHandler eh;
    {
      SUB_TEST("get size: single array passed");
      ASSERT_EQUAL_UNSIGNED(data_handling::get_size(eh, "VAR1_1", local_ac1, 1),
                            n1);
    }
    {
      SUB_TEST("get size: multiple arrays - should be taking first available");
      ASSERT_EQUAL_UNSIGNED(
        data_handling::get_size(eh, "VAR1_2", local_ac1, 1, local_ac2, 1), n1);
    }
    {
      SUB_TEST("get size: multiple arrays - no error checking on individual "
               "arrays");
      ASSERT_EQUAL_UNSIGNED(
        data_handling::get_size(eh, "VAR1_3", local_ac1, 1, local_ac2, 2), n1);
      ASSERT_EQUAL_UNSIGNED(
        data_handling::get_size(eh, "VAR1_4", local_ac2, 2, local_ac1, 1), n1);
    }
    {
      SUB_TEST("get size: size not available");
      ASSERT_THROWS(error_handler::ErrorException,
                    data_handling::get_size(eh, "VAR1_5", local_ac1, 2));
      ASSERT_TRUE(eh.error_thrown);
      ASSERT_HAS_KEYWORD(eh.msg, "VAR1_5");
      ASSERT_HAS_KEYWORD(eh.msg, "to ascertain");

      // check that EH is reset after a correct size query
      ASSERT_EQUAL_UNSIGNED(data_handling::get_size(eh, "VAR1_6", local_ac1, 1),
                            n1);
      ASSERT_FALSE(eh.error_thrown);
    }
  }
};
// clang-format off
REGISTER_TEST(test_get_size_function, "Test the function that returns the size of the array");
// clang-format on

//************************************************
struct test_check_function : public TestCase {
  DEFINE_RUN_METHOD_WRAPPERS

  template <typename RT, enum data_handling::ArgIntent inout, typename AC,
            enum ut::TYPE_IS type_is = ut::TYPE_IS::GENERAL>
  void run_this(std::string label = "") {
    SUB_TITLE(label);
    static const size_t n1 = 10;
    std::unique_ptr<AC> ac =
      test_setup<RT, inout, AC, type_is>::get_test_data(n1);
    call_test<RT, inout, AC, type_is>(ac, n1);
  }

  template <typename RT, enum data_handling::ArgIntent inout, typename AC,
            enum ut::TYPE_IS type_is>
  auto call_test(std::unique_ptr<AC> &ac, size_t n1) ->
    typename std::enable_if<!ut::is_internal_type<type_is>::value, void>::type {
    using RD = data_handling::RawData<RT, inout, AC>;
    RD local_ac(*ac);
    do_test<RD>(local_ac, n1);
  }
  template <typename RT, enum data_handling::ArgIntent inout, typename AC,
            enum ut::TYPE_IS type_is>
  auto call_test(std::unique_ptr<AC> &ac, size_t n1) ->
    typename std::enable_if<ut::is_internal_type<type_is>::value, void>::type {
    do_test<AC>(*ac, n1);
  }

  template <typename RD>
  void do_test(RD &local_ac, size_t n1) {
    nagcpp::error_handler::ErrorHandler eh;
    {
      SUB_TEST("check function: correct size");
      ASSERT_THROWS_NOTHING(local_ac.check(eh, "VAR1_1", true, n1));
    }
    {
      SUB_TEST("check function: expected 1D array of different size");
      // one element larger
      ASSERT_THROWS(error_handler::ErrorException,
                    local_ac.check(eh, "VAR1_2", true, n1 + 1));
      ASSERT_TRUE(eh.error_thrown);
      ASSERT_HAS_KEYWORD(eh.msg, "VAR1_2");

      // one element smaller
      ASSERT_THROWS(error_handler::ErrorException,
                    local_ac.check(eh, "VAR1_3", true, n1 - 1));
      ASSERT_TRUE(eh.error_thrown);
      ASSERT_HAS_KEYWORD(eh.msg, "VAR1_3");

      // check that EH is reset after a correct check
      ASSERT_THROWS_NOTHING(local_ac.check(eh, "VAR1_4", true, n1));
      ASSERT_FALSE(eh.error_thrown);
    }
    {
      SUB_TEST("check function: expected 2D array");
      ASSERT_THROWS(error_handler::ErrorException,
                    local_ac.check(eh, "VAR1_5", true, 1, n1, 2));
      ASSERT_TRUE(eh.error_thrown);
      ASSERT_HAS_KEYWORD(eh.msg, "VAR1_5");

      // check that EH is reset after a correct check
      ASSERT_THROWS_NOTHING(local_ac.check(eh, "VAR1_6", true, n1));
      ASSERT_FALSE(eh.error_thrown);
    }
    {
      SUB_TEST("check function: expected 3D array");
      ASSERT_THROWS(error_handler::ErrorException,
                    local_ac.check(eh, "VAR1_7", true, 1, n1, 2, 3));
      ASSERT_TRUE(eh.error_thrown);
      ASSERT_HAS_KEYWORD(eh.msg, "VAR1_7");

      // check that EH is reset after a correct check
      ASSERT_THROWS_NOTHING(local_ac.check(eh, "VAR1_8", true, n1));
      ASSERT_FALSE(eh.error_thrown);
    }
  }
};
// clang-format off
REGISTER_TEST(test_check_function, "Test the function that checks whether the correct size array has been supplied");
// clang-format on

//************************************************
struct test_data_variable : public TestCase {
  DEFINE_RUN_METHOD_WRAPPERS

  template <typename RT, enum data_handling::ArgIntent inout, typename AC,
            enum ut::TYPE_IS type_is = ut::TYPE_IS::GENERAL>
  void run_this(std::string label = "") {
    SUB_TITLE(label);
    static const size_t n1 = 11;
    std::unique_ptr<AC> ac =
      test_setup<RT, inout, AC, type_is>::get_test_data(n1);
    call_test<RT, inout, AC, type_is>(ac, n1);
  }

  template <typename RT, enum data_handling::ArgIntent inout, typename AC,
            enum ut::TYPE_IS type_is>
  auto call_test(std::unique_ptr<AC> &ac, size_t n1) ->
    typename std::enable_if<!ut::is_internal_type<type_is>::value, void>::type {
    using RD = data_handling::RawData<RT, inout, AC>;
    RD local_ac(*ac);
    do_test<RD, RT>(local_ac, n1);
  }

  template <typename RT, enum data_handling::ArgIntent inout, typename AC,
            enum ut::TYPE_IS type_is>
  auto call_test(std::unique_ptr<AC> &ac, size_t n1) ->
    typename std::enable_if<ut::is_internal_type<type_is>::value, void>::type {
    do_test<AC, RT>(*ac, n1);
  }

  template <typename RD, typename RT>
  void do_test(RD &local_ac, size_t n1) {
    {
      SUB_TEST("data variable: check contiguous memory");
      std::vector<RT> expected_results = ut::get_expected_values<RT>(n1);
      ASSERT_ARRAY_EQUAL(n1, local_ac.data, expected_results);
    }
  }
};
// clang-format off
REGISTER_TEST(test_data_variable, "Test the data class variable");
// clang-format on

//************************************************
struct test_get_data_method : public TestCase {
  DEFINE_RUN_METHOD_WRAPPERS

  template <typename RT, enum data_handling::ArgIntent inout, typename AC,
            enum ut::TYPE_IS type_is = ut::TYPE_IS::GENERAL>
  auto run_this(std::string label = "") ->
    typename std::enable_if<ut::is_internal_type<type_is>::value, void>::type {
    // don't run the get_data method on internal arrays
  }

  template <typename RT, enum data_handling::ArgIntent inout, typename AC,
            enum ut::TYPE_IS type_is = ut::TYPE_IS::GENERAL>
  auto run_this(std::string label = "") ->
    typename std::enable_if<!ut::is_internal_type<type_is>::value, void>::type {
    using RD = data_handling::RawData<RT, inout, AC>;
    SUB_TITLE(label);
    static const size_t n1 = 11;
    std::unique_ptr<AC> ac1 =
      test_setup<RT, inout, AC, type_is>::get_test_data(n1);
    RD local_ac1(*ac1);
    static const size_t n2 = 12;
    std::unique_ptr<AC> ac2 =
      test_setup<RT, inout, AC, type_is>::get_test_data(n2);
    RD local_ac(*ac1);
    {
      SUB_TEST("data variable: check contiguous memory");
      std::vector<RT> expected_results = ut::get_expected_values<RT>(n1);
      ASSERT_ARRAY_EQUAL(n1, local_ac.data, expected_results);
    }
    {
      SUB_TEST("update local data using get_data method: check sizes");
      nagcpp::error_handler::ErrorHandler eh;
      ASSERT_THROWS_NOTHING(local_ac.check(eh, "VAR1_1", true, n1));
      ASSERT_FALSE(eh.error_thrown);
      local_ac.get_data(*ac2);
      ASSERT_THROWS_NOTHING(local_ac.check(eh, "VAR2_1", true, n2));
      ASSERT_FALSE(eh.error_thrown);
    }
    {
      SUB_TEST("data variable: check contiguous memory after update");
      std::vector<RT> expected_results = ut::get_expected_values<RT>(n2);
      ASSERT_ARRAY_EQUAL(n2, local_ac.data, expected_results);
    }
  }
};
// clang-format off
REGISTER_TEST(test_get_data_method, "Test the get_data method returns contiguous memory (of the expected size)");
// clang-format on

//************************************************
struct test_array_referencing_overload : public TestCase {
  DEFINE_RUN_METHOD_WRAPPERS

  template <typename RT, enum data_handling::ArgIntent inout, typename AC,
            enum ut::TYPE_IS type_is = ut::TYPE_IS::GENERAL>
  void run_this(std::string label = "") {
    SUB_TITLE(label);
    static const size_t n1 = 9;
    std::unique_ptr<AC> ac =
      test_setup<RT, inout, AC, type_is>::get_test_data(n1);
    call_test<RT, inout, AC, type_is>(ac, n1);
  }

  template <typename RT, enum data_handling::ArgIntent inout, typename AC,
            enum ut::TYPE_IS type_is>
  auto call_test(std::unique_ptr<AC> &ac, size_t n1) ->
    typename std::enable_if<!ut::is_internal_type<type_is>::value, void>::type {
    using RD = data_handling::RawData<RT, inout, AC>;
    RD local_ac(*ac);
    do_test<RD, RT>(local_ac, n1);
  }
  template <typename RT, enum data_handling::ArgIntent inout, typename AC,
            enum ut::TYPE_IS type_is>
  auto call_test(std::unique_ptr<AC> &ac, size_t n1) ->
    typename std::enable_if<ut::is_internal_type<type_is>::value, void>::type {
    do_test<AC, RT>(*ac, n1);
  }

  template <typename RD, typename RT>
  void do_test(RD &local_ac, size_t n1) {
    std::vector<RT> expected_results = ut::get_expected_values<RT>(n1);
    bool passed = true;
    for (size_t i = 0; i < n1 && passed; ++i) {
      ASSERT_EQUAL_ONLY_COUNT_FAILURE(local_ac(i), expected_results[i]);
      passed = last_assert_passed;
    }
    ASSERT_TRUE_LABELLED("local_ac vs expected_results", passed);
  }
};
// clang-format off
REGISTER_TEST(test_array_referencing_overload, "Test that the array referencing overload works");
// clang-format on

//************************************************
struct test_allocate_local_method : public TestCase {
  DEFINE_RUN_METHOD_WRAPPERS

  template <typename RT, enum data_handling::ArgIntent inout, typename AC,
            enum ut::TYPE_IS type_is = ut::TYPE_IS::GENERAL>
  auto run_this(std::string label = "") ->
    typename std::enable_if<data_handling::is_in<inout>::value, void>::type {
    // allocate_local should never be called on an input array
  }

  template <typename RT, enum data_handling::ArgIntent inout, typename AC,
            enum ut::TYPE_IS type_is = ut::TYPE_IS::GENERAL>
  auto run_this(std::string label = "") ->
    typename std::enable_if<!data_handling::is_in<inout>::value, void>::type {
    SUB_TITLE(label);
    std::unique_ptr<AC> ac =
      test_setup<RT, inout, AC, type_is>::get_test_data(0);
    call_test<RT, inout, AC, type_is>(ac);
  }

  template <typename RT, enum data_handling::ArgIntent inout, typename AC,
            enum ut::TYPE_IS type_is>
  auto call_test(std::unique_ptr<AC> &ac) ->
    typename std::enable_if<!ut::is_internal_type<type_is>::value, void>::type {
    using RD = data_handling::RawData<RT, inout, AC>;
    RD local_ac(*ac);
    do_test<RT, RD>(local_ac);
  }
  template <typename RT, enum data_handling::ArgIntent inout, typename AC,
            enum ut::TYPE_IS type_is>
  auto call_test(std::unique_ptr<AC> &ac) ->
    typename std::enable_if<ut::is_internal_type<type_is>::value, void>::type {
    do_test<RT, AC>(*ac);
  }

  template <typename RT, typename RD>
  void do_test(RD &local_ac) {
    static const size_t n2 = 12;
    local_ac.allocate_local(n2);

    ASSERT_CPOINTER_IS_NOT_NULL(local_ac.data);
    if (last_assert_passed) {
      // set an element of the array to something - this is just
      // here as a valgrind check the memory is allocated
      local_ac.data[0] = static_cast<RT>(3.1);
      local_ac.data[n2 - 1] = static_cast<RT>(3.0);
    }
    nagcpp::error_handler::ErrorHandler eh;
    ASSERT_THROWS_NOTHING(local_ac.check(eh, "VAR1_1", true, n2));
  }
};
// clang-format off
REGISTER_TEST(test_allocate_local_method, "Test we can allocate a local array with RawData templated using user data type");
// clang-format on

//************************************************
struct test_resize_method : public TestCase {
  DEFINE_RUN_METHOD_WRAPPERS

  template <typename RT, enum data_handling::ArgIntent inout, typename AC,
            enum ut::TYPE_IS type_is = ut::TYPE_IS::GENERAL>
  auto run_this(std::string label = "") ->
    typename std::enable_if<!ut::has_resize<inout, type_is>::value,
                            void>::type {
    // resize should never be called on things like an input array or an internal array
    // or an array defined via type_is to not have a resize
  }

  template <typename RT, enum data_handling::ArgIntent inout, typename AC,
            enum ut::TYPE_IS type_is = ut::TYPE_IS::GENERAL>
  auto run_this(std::string label = "") ->
    typename std::enable_if<ut::has_resize<inout, type_is>::value, void>::type {

    using RD = data_handling::RawData<RT, inout, AC>;
    SUB_TITLE(label);
    nagcpp::error_handler::ErrorHandler eh;
    {
      SUB_TEST("resize when initial container is null");
      std::unique_ptr<AC> ac1 =
        test_setup<RT, inout, AC, type_is>::get_test_data(0);
      RD local_ac(*ac1);

      ASSERT_CPOINTER_IS_NULL(local_ac.data);
      static const size_t n1 = 9;
      local_ac.resize(*ac1, n1);

      ASSERT_CPOINTER_IS_NOT_NULL(local_ac.data);
      if (last_assert_passed) {
        // set an element of the array to something - this is just
        // here as a valgrind check the memory is allocated
        local_ac.data[0] = static_cast<RT>(3.1);
        local_ac.data[n1 - 1] = static_cast<RT>(3.0);
      }
      ASSERT_THROWS_NOTHING(local_ac.check(eh, "VAR1_1", true, n1));
    }

    // the wrappers should never call a naked resize that has to
    // preserve the data, that should always be done via the copyback method
    // {
    //   // this may happen as part of the copyback call when
    //   // resizing at the same time
    //   SUB_TEST("resize when initial container is not null");
    //   static const size_t n1 = 20;
    //   std::unique_ptr<AC> ac1 =
    //     test_setup<RT, inout, AC, type_is>::get_test_data(n1);
    //   RD local_ac(*ac1);
    //   ASSERT_THROWS_NOTHING(local_ac.check(eh, "VAR1_1", true, n1));

    //   ASSERT_CPOINTER_IS_NOT_NULL(local_ac.data);
    //   static const size_t n2 = 9;
    //   local_ac.resize(*ac1, n2);

    //   ASSERT_CPOINTER_IS_NOT_NULL(local_ac.data);
    //   ASSERT_THROWS_NOTHING(local_ac.check(eh, "VAR1_1", true, n2));

    //   // check that the resize preserves input in this case
    //   std::vector<RT> expected_results = ut::get_expected_values<RT>(n1);
    //   ASSERT_ARRAY_EQUAL(n2, local_ac.data, expected_results);
    // }
  }
};
// clang-format off
REGISTER_TEST(test_resize_method, "Test the method that resizes arrays");
// clang-format on

//************************************************
struct test_copy_back_method_array_preallocated : public TestCase {
  DEFINE_RUN_METHOD_WRAPPERS

  template <typename RT, enum data_handling::ArgIntent inout, typename AC,
            enum ut::TYPE_IS type_is = ut::TYPE_IS::GENERAL>
  auto run_this(std::string label = "") ->
    typename std::enable_if<data_handling::is_in<inout>::value ||
                              ut::is_internal_type<type_is>::value,
                            void>::type {
    // copyback should never be called on an input array or an internal array
  }

  template <typename RT, enum data_handling::ArgIntent inout, typename AC,
            enum ut::TYPE_IS type_is = ut::TYPE_IS::GENERAL>
  auto run_this(std::string label = "") ->
    typename std::enable_if<!(data_handling::is_in<inout>::value ||
                              ut::is_internal_type<type_is>::value),
                            void>::type {
    using RD = data_handling::RawData<RT, inout, AC>;
    SUB_TITLE(label);
    nagcpp::error_handler::ErrorHandler eh;
    {
      SUB_TEST("copy_back with no resize");
      static const size_t n1 = 10;
      std::unique_ptr<AC> ac1 =
        test_setup<RT, inout, AC, type_is>::get_test_data(n1);
      RD local_ac(*ac1);

      // get a set of expected results, different from those used in test_setup
      std::vector<RT> expected_results =
        ut::get_expected_values<RT>(n1, static_cast<RT>(32.23));

      // copy the expected results into RawData
      for (size_t i = 0; i < n1; ++i) {
        local_ac.data[i] = expected_results[i];
      }
      // copy back from RawData to users type
      local_ac.copy_back(*ac1);
      // compare values
      auto max_diff =
        test_setup<RT, inout, AC, type_is>::max_abs_diff(*ac1, expected_results,
                                                         n1);
      ASSERT_EQUAL(max_diff, 0);

      // check the meta information
      bool meta_info_ok =
        test_setup<RT, inout, AC, type_is>::check_meta_info(*ac1, n1);
      ASSERT_TRUE(meta_info_ok);
    }
    {
      SUB_TEST("resize container to smaller and copy back");
      static const size_t n1 = 20;
      std::unique_ptr<AC> ac1 =
        test_setup<RT, inout, AC, type_is>::get_test_data(n1);
      RD local_ac(*ac1);

      // get a set of expected results, different from those used in test_setup
      static const size_t n2 = 8;
      std::vector<RT> expected_results =
        ut::get_expected_values<RT>(n2, static_cast<RT>(42.24));

      // copy the expected results into RawData
      for (size_t i = 0; i < n2; ++i) {
        local_ac.data[i] = expected_results[i];
      }
      // copy back from RawData to users type, resizing as we go
      local_ac.copy_back(*ac1, n2);

      // compare values
      auto max_diff =
        test_setup<RT, inout, AC, type_is>::max_abs_diff(*ac1, expected_results,
                                                         n2);
      ASSERT_EQUAL(max_diff, 0);

      // check the size
      bool meta_info_ok;
      if (ut::has_resize<inout, type_is>::value) {
        meta_info_ok =
          test_setup<RT, inout, AC, type_is>::check_meta_info(*ac1, n2);
      } else {
        // there is no resize, we are assuming that the array size remains the same
        meta_info_ok =
          test_setup<RT, inout, AC, type_is>::check_meta_info(*ac1, n1);
      }
      ASSERT_TRUE(meta_info_ok);
    }
    // resizing the container to larger when copying back should never happen
  }
};
// clang-format off
REGISTER_TEST(test_copy_back_method_array_preallocated, "Test method to copy data back into array container (pre-allocated)");
// clang-format on

//************************************************
struct test_copy_back_method_array_not_preallocated : public TestCase {
  DEFINE_RUN_METHOD_WRAPPERS

  template <typename RT, enum data_handling::ArgIntent inout, typename AC,
            enum ut::TYPE_IS type_is = ut::TYPE_IS::GENERAL>
  auto run_this(std::string label = "") ->
    typename std::enable_if<!ut::has_resize<inout, type_is>::value,
                            void>::type {
    // copyback should never be called on an input array or an internal array
  }

  template <typename RT, enum data_handling::ArgIntent inout, typename AC,
            enum ut::TYPE_IS type_is = ut::TYPE_IS::GENERAL>
  auto run_this(std::string label = "") ->
    typename std::enable_if<ut::has_resize<inout, type_is>::value, void>::type {
    using RD = data_handling::RawData<RT, inout, AC>;
    SUB_TITLE(label);
    nagcpp::error_handler::ErrorHandler eh;
    {
      SUB_TEST("copy_back with no resize");
      static const size_t n1 = 10;
      std::unique_ptr<AC> ac1 =
        test_setup<RT, inout, AC, type_is>::get_test_data(0);
      RD local_ac(*ac1);

      ASSERT_CPOINTER_IS_NULL(local_ac.data);

      // run the resize method directly on local_ac
      local_ac.resize(*ac1, n1);

      // get a set of expected results, different from those used in test_setup
      std::vector<RT> expected_results = ut::get_expected_values<RT>(n1);

      ASSERT_CPOINTER_IS_NOT_NULL(local_ac.data);
      if (last_assert_passed) {
        // copy the expected results into RawData
        for (size_t i = 0; i < n1; ++i) {
          local_ac.data[i] = expected_results[i];
        }
      }

      ASSERT_THROWS_NOTHING(local_ac.check(eh, "VAR1_1", true, n1));

      // copy back from RawData to users type
      local_ac.copy_back(*ac1);

      // compare values
      auto max_diff =
        test_setup<RT, inout, AC, type_is>::max_abs_diff(*ac1, expected_results,
                                                         n1);
      ASSERT_EQUAL(max_diff, 0);

      // check the size
      bool meta_info_ok =
        test_setup<RT, inout, AC, type_is>::check_meta_info(*ac1, n1);
      ASSERT_TRUE(meta_info_ok);
    }
    {
      SUB_TEST("resize container to smaller and copy back");
      static const size_t n1 = 20;
      std::unique_ptr<AC> ac1 =
        test_setup<RT, inout, AC, type_is>::get_test_data(0);
      RD local_ac(*ac1);

      ASSERT_CPOINTER_IS_NULL(local_ac.data);

      // run the resize method directly on local_ac
      local_ac.resize(*ac1, n1);
      ASSERT_THROWS_NOTHING(local_ac.check(eh, "VAR1_2", true, n1));

      // get a set of expected results, different from those used in test_setup
      static const size_t n2 = 8;
      std::vector<RT> expected_results = ut::get_expected_values<RT>(n2);

      // copy the expected results into RawData
      for (size_t i = 0; i < n2; ++i) {
        local_ac.data[i] = expected_results[i];
      }
      // copy back from RawData to users type, resizing as we go
      local_ac.copy_back(*ac1, n2);

      // compare values
      auto max_diff =
        test_setup<RT, inout, AC, type_is>::max_abs_diff(*ac1, expected_results,
                                                         n2);
      ASSERT_EQUAL(max_diff, 0);

      // check the size
      bool meta_info_ok =
        test_setup<RT, inout, AC, type_is>::check_meta_info(*ac1, n2);
      ASSERT_TRUE(meta_info_ok);
    }
  }
};
// clang-format off
REGISTER_TEST(test_copy_back_method_array_not_preallocated, "Test method to copy data back into array container (not pre-allocated)");
// clang-format on
// ... tests related to using the type as an argument to a NAG routine

template <typename RT, enum data_handling::ArgIntent inout, typename AC,
          enum ut::TYPE_IS type_is = ut::TYPE_IS::GENERAL>
void pseudo_helper_in(const RT *x, const size_t n1, bool &meta_info_ok,
                      RT &max_diff) {
  // pack raw data into utility::array1D
  utility::array1D<RT, data_handling::ArgIntent::IN> local_x(x, n1);

  // convert utility::array1D into the users type
  auto user_x = data_handling::convert_nag_array_to_user<
    const utility::array1D<RT, data_handling::ArgIntent::IN>, inout, AC>(local_x);

  // simulate calling a callback with X as an input argument ...
  // check that the users type has the correct meta information
  meta_info_ok =
    test_setup<RT, inout, AC, type_is>::check_meta_info(user_x.get(), n1);

  // check that the values in the users type are correct
  std::vector<RT> ex(x, x + n1);
  max_diff =
    test_setup<RT, inout, AC, type_is>::max_abs_diff(user_x.get(), ex, n1);
  // ... simulate calling a callback with X as an input argument
}

template <typename RT, enum data_handling::ArgIntent inout, typename AC,
          enum ut::TYPE_IS type_is = ut::TYPE_IS::GENERAL>
void pseudo_helper_out(RT *x, const size_t n1, bool &meta_info_ok) {
  // pack raw data into utility::array1D
  utility::array1D<RT, data_handling::ArgIntent::OUT> local_x(x, n1);

  // convert utility::array1D into the users type
  auto user_x = data_handling::convert_nag_array_to_user<
    utility::array1D<RT, data_handling::ArgIntent::OUT>, inout, AC>(local_x);

  // simulate calling a callback with X as an output argument ...
  // check that the users type has the correct meta information
  meta_info_ok =
    test_setup<RT, inout, AC, type_is>::check_meta_info(user_x.get(), n1);

  // populate the users type
  test_setup<RT, inout, AC, type_is>::set_values(user_x.get());
  // ... simulate calling a callback with X as an output argument
}

template <typename RT, enum data_handling::ArgIntent inout, typename AC,
          enum ut::TYPE_IS type_is = ut::TYPE_IS::GENERAL>
void pseudo_helper_inout(RT *x, const size_t n1, bool &meta_info_ok,
                         RT &max_diff) {
  // pack raw data into utility::array1D
  utility::array1D<RT, data_handling::ArgIntent::INOUT> local_x(x, n1);

  // convert utility::array1D into the users type
  auto user_x = data_handling::convert_nag_array_to_user<
    utility::array1D<RT, data_handling::ArgIntent::INOUT>, inout, AC>(local_x);

  // simulate calling a callback with X as an input / output argument ...
  // check that the users type has the correct meta information
  meta_info_ok =
    test_setup<RT, inout, AC, type_is>::check_meta_info(user_x.get(), n1);

  // check that the values in the users type are correct
  std::vector<RT> ex(x, x + n1);
  max_diff =
    test_setup<RT, inout, AC, type_is>::max_abs_diff(user_x.get(), ex, n1);

  // populate the users type
  test_setup<RT, inout, AC, type_is>::set_values(user_x.get());
  // ... simulate calling a callback with X as an input / output argument
}

//******************************************************************************
//******************************************************************************

// tests related to using the type as an argument to a NAG callback function ...
//************************************************
struct test_convert_nag_array_to_user : public TestCase {
  DEFINE_RUN_METHOD_CALLBACKS

  template <typename RT, enum data_handling::ArgIntent inout, typename AC,
            enum ut::TYPE_IS type_is = ut::TYPE_IS::GENERAL>
  auto run_this(std::string label = "") ->
    typename std::enable_if<data_handling::is_in<inout>::value, void>::type {
    SUB_TITLE(label);
    static const size_t n1 = 21;
    std::vector<RT> raw_data = ut::get_expected_values<RT>(n1, static_cast<RT>(132.12));
    RT max_diff;
    bool meta_info_ok;
    pseudo_helper_in<RT, inout, AC>(raw_data.data(), n1, meta_info_ok,
                                    max_diff);
    {
      SUB_TEST("check data passed to user type");
      ASSERT_TRUE(meta_info_ok);
      ASSERT_EQUAL(max_diff, 0);
    }
  }

  template <typename RT, enum data_handling::ArgIntent inout, typename AC,
            enum ut::TYPE_IS type_is = ut::TYPE_IS::GENERAL>
  auto run_this(std::string label = "") ->
    typename std::enable_if<data_handling::is_out<inout>::value, void>::type {
    SUB_TITLE(label);
    static const size_t n1 = 20;
    std::vector<RT> raw_data(n1, -999);
    bool meta_info_ok;
    pseudo_helper_out<RT, inout, AC>(raw_data.data(), n1, meta_info_ok);
    {
      SUB_TEST("check data passed to user type");
      ASSERT_TRUE(meta_info_ok);
    }
    {
      SUB_TEST("check user type updates data");
      std::vector<RT> expected_results = ut::get_expected_values<RT>(n1);
      ASSERT_ARRAY_EQUAL(n1, raw_data, expected_results);
    }
  }

  template <typename RT, enum data_handling::ArgIntent inout, typename AC,
            enum ut::TYPE_IS type_is = ut::TYPE_IS::GENERAL>
  auto run_this(std::string label = "") ->
    typename std::enable_if<data_handling::is_inout<inout>::value, void>::type {
    SUB_TITLE(label);
    static const size_t n1 = 11;
    std::vector<RT> raw_data = ut::get_expected_values<RT>(n1, static_cast<RT>(132.12));
    RT max_diff;
    bool meta_info_ok;
    pseudo_helper_inout<RT, inout, AC>(raw_data.data(), n1, meta_info_ok,
                                       max_diff);
    {
      SUB_TEST("check data passed to user type");
      ASSERT_TRUE(meta_info_ok);
      ASSERT_EQUAL(max_diff, 0);
    }
    {
      SUB_TEST("check user type updates data");
      std::vector<RT> expected_results = ut::get_expected_values<RT>(n1);
      ASSERT_ARRAY_FLOATS_EQUAL(n1, raw_data, expected_results);
    }
  }
};
// clang-format off
REGISTER_TEST(test_convert_nag_array_to_user, "Test auto discovery and conversion of NAG array type to users type");
// clang-format on
// ... tests related to using the type as an argument to a NAG callback function
