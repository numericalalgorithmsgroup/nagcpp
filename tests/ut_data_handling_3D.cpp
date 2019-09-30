// unit tests for 3D classes that may be passed into a NAG routine
#include "../examples/include/nag_my_data.hpp"
#include "../examples/include/nag_my_table.hpp"
#include "include/cxxunit_testing.hpp"
#include "include/nagcpp_ut_generate_data.hpp"
#include "include/nagcpp_ut_utilities.hpp"
#include "include/nagcpp_ut_utility_array_wrapper.hpp"
#include "utility/nagcpp_data_handling.hpp"
#include "utility/nagcpp_error_handler.hpp"
#include "utility/nagcpp_utility_array.hpp"
#include "x02/nagcpp_x02aj.hpp"
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
//   template <enum ut::SORDER sorder, typename RT, enum data_handling::INOUT inout, typename AC>
//   void run_this(std::string label="")
//   AC     - type that will be used as an argument to a NAG routine
//            (for example std::vector<double>)
//   inout  - whether the AC type will be used for input, output or
//            input / output arguement, if it will be used for all three
//            then there needs to be three calls to run_this
//            (different subset of tests are run depending on the value of this)
//   RT     - type of the underlying NAG array the type being tested will be used
//            as an argument for (double, types::f77_integer etc)
//   SORDER - whether the data is stored in COL_MAJOR or ROW_MAJOR order
//            (this is primarly to trigger tests in both orders if the class
//            supports that)
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
// std::unique_ptr<AC> get_test_data(const size_t n1, const size_t n2);
//    return an smart pointer to an instance of type A
//    if n1 > 0 && n2 > 0 && n3 > 0, then this should hold a matrix of size
//    n1 x n2 x n3 and set_values should be run to populate the vector
//    if n1 <= 0 || n2 <= 0 || n3 <= 0, then the type should be set up in such
//    a way that when the the underlying (contiguous) data array is requested
//    a null pointer is returned (i.e. it has not been allocated)
// void set_values(AC &ac);
//    populate the ac with the values returned by get_expected_values
//    get_expected_values is stored in either column major order or
//    row_major order, depending on the sorder template parameter
// RT max_abs_diff(const AC &observed, const std::vector<RT> &expected,
//                 const size_t n1, const size_t n2, const size_t n3);
//    return the maximum absolute difference between the observed and
//    expected data, as with set_values, the data in expected is stored
//    in the same order as expected_values, i.e. dependent on the sorder
//    template parameter
// bool check_meta_info(const AC &ac, bool is_col_major, const size_t n1,
//                      const size_t n2, const size_t n3)
//    return true if any meta information stored in ac is correct
//    is_col_major = if true, then the underlying (contiguous) data array
//                   is expected to be in column major order, otherwise
//                   it is expected to be in row major order
//    n1           = number of rows
//    n2           = number of columns
//    n3           = number of tables (i.e. number of n1 x n2 matrices)
//    (if there is no meta information stored, return true)
// the default test_setup has four template parameters
//   RT      - type of the underlying data (double or types::f77_integer)
//   inout   - data_handling::INOUT value indicating whether the class
//             being tested will be used as an input (IN), output (OUT)
//             or input / output (INOUT) argument
//   AC      - type of the class being tested
//   type_is - should be left at its default value, used to identify
//             internal types

// NB: this test suite runs:
//   11 tests on types used in wrappers
//      of which only 7 are run on data_handling::INOUT::IN classes
//      (or internal ones) and (max of) 9 are run if ut::has_resize
//      is false
//   1  test on types used in callbacks

// easiest way to run a single test is to use search-and-replace to comment out
// "REGISTER_TEST" and then manually uncomment the one you want to run

// clang-format on
template <enum ut::SORDER sorder, typename RT, enum data_handling::INOUT inout,
          typename AC, ut::TYPE_IS type_is = ut::GENERAL>
struct test_setup;

// structure to allow tests to be run on (some) arbitrary types ...
template <enum ut::SORDER sorder, typename RT, enum data_handling::INOUT inout,
          typename AC, ut::TYPE_IS type_is>
struct test_setup {
  using UPAC = std::unique_ptr<AC>;

  template <typename DUMMY = UPAC>
  static auto get_test_data(const size_t n1, const size_t n2, const size_t n3)
    -> typename std::enable_if<ut::is_const_data_pointer_type<type_is>::value,
                               DUMMY>::type {
    if (n1 > 0 && n2 > 0 && n3 > 0) {
      // return a populated array of the stated size
      std::vector<RT> expected_results =
        ut::get_expected_values<sorder, RT>(n1, n2, n3);
      UPAC ac = std::unique_ptr<AC>(new AC(expected_results, n1, n2, n3));
      return ac;

    } else {
      // return an array where the data class variable is a null pointer
      UPAC ac = std::unique_ptr<AC>(new AC());
      return ac;
    }
  }
  template <typename DUMMY = UPAC>
  static auto get_test_data(const size_t n1, const size_t n2, const size_t n3)
    -> typename std::enable_if<!ut::is_const_data_pointer_type<type_is>::value,
                               DUMMY>::type {
    if (n1 > 0 && n2 > 0 && n3 > 0) {
      // return a populated array of the stated size
      std::vector<RT> expected_results =
        ut::get_expected_values<sorder, RT>(n1, n2, n3);
      UPAC ac = std::unique_ptr<AC>(new AC(n1, n2, n3));
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
    auto size2 = data_handling::getDim2(ac, 0);
    auto size3 = data_handling::getDim3(ac, 0);
    size_t n1 = static_cast<size_t>(size1.value);
    size_t n2 = static_cast<size_t>(size2.value);
    size_t n3 = static_cast<size_t>(size3.value);
    set_expected_results(ac, n1, n2, n3);
  }
  template <typename DUMMY = void>
  static auto set_values(AC &ac) ->
    typename std::enable_if<ut::is_internal_type<type_is>::value, DUMMY>::type {
    nagcpp::error_handler::ErrorHandler eh;
    size_t n1 = data_handling::get_size(eh, "AC", ac, 1);
    size_t n2 = data_handling::get_size(eh, "AC", ac, 2);
    size_t n3 = data_handling::get_size(eh, "AC", ac, 3);
    ac.set_default_storage(ut::is_col_major<sorder>::value);
    set_expected_results(ac, n1, n2, n3);
  }
  static RT max_abs_diff(const AC &observed, const std::vector<RT> &expected,
                         const size_t n1, const size_t n2, const size_t n3) {
    // return maximum absolute difference between observed and expected
    RT max_diff = 0;
    if (ut::is_col_major<sorder>::value) {
      for (size_t k = 0, p = 0; k < n3; ++k) {
        for (size_t j = 0; j < n2; ++j) {
          for (size_t i = 0; i < n1; ++i, ++p) {
            RT this_diff =
              static_cast<RT>(std::fabs(static_cast<double>(observed(i, j, k)) -
                                        static_cast<double>(expected[p])));
            max_diff = std::max(this_diff, max_diff);
          }
        }
      }
    } else {
      for (size_t i = 0, p = 0; i < n1; ++i) {
        for (size_t j = 0; j < n2; ++j) {
          for (size_t k = 0; k < n3; ++k, ++p) {
            RT this_diff =
              static_cast<RT>(std::fabs(static_cast<double>(observed(i, j, k)) -
                                        static_cast<double>(expected[p])));
            max_diff = std::max(this_diff, max_diff);
          }
        }
      }
    }
    return max_diff;
  }
  template <typename DUMMY = bool>
  static auto check_meta_info(const AC &ac, const bool is_col_major,
                              const size_t n1, const size_t n2, const size_t n3)
    -> typename std::enable_if<!ut::is_internal_type<type_is>::value,
                               DUMMY>::type {
    auto ndim = data_handling::getNDims(ac, 0);
    auto size1 = data_handling::getDim1(ac, 0);
    auto size2 = data_handling::getDim2(ac, 0);
    auto size3 = data_handling::getDim3(ac, 0);
    auto local_storage_order = data_handling::getStorageOrder(ac, 0);
    return (ndim.set && ndim.value == 3) &&
           (size1.set && static_cast<size_t>(size1.value) == n1) &&
           (size2.set && static_cast<size_t>(size2.value) == n2) &&
           (size3.set && static_cast<size_t>(size3.value) == n3) &&
           local_storage_order == is_col_major;
  }
  template <typename DUMMY = bool>
  static auto check_meta_info(const AC &ac, const bool is_col_major,
                              const size_t n1, const size_t n2, const size_t n3)
    ->
    typename std::enable_if<ut::is_internal_type<type_is>::value, DUMMY>::type {
    nagcpp::error_handler::ErrorHandler eh;
    auto size1 = data_handling::get_size(eh, "AC", ac, 1);
    auto size2 = data_handling::get_size(eh, "AC", ac, 2);
    auto size3 = data_handling::get_size(eh, "AC", ac, 3);
    types::f77_integer isorder =
      data_handling::get_storage_order(ut::is_col_major<sorder>::value, ac);
    bool this_is_col_major = data_handling::set_is_col_major(isorder);
    return (static_cast<size_t>(size1) == n1) &&
           (static_cast<size_t>(size2) == n2) &&
           (static_cast<size_t>(size3) == n3) &&
           this_is_col_major == is_col_major;
  }

private:
  static void set_expected_results(AC &ac, const size_t n1, const size_t n2,
                                   const size_t n3) {
    std::vector<RT> expected_results =
      ut::get_expected_values<sorder, RT>(n1, n2, n3);
    if (ut::is_col_major<sorder>::value) {
      for (size_t k = 0, p = 0; k < n3; ++k) {
        for (size_t j = 0; j < n2; ++j) {
          for (size_t i = 0; i < n1; ++i, ++p) {
            ac(i, j, k) = expected_results[p];
          }
        }
      }
    } else {
      for (size_t i = 0, p = 0; i < n1; ++i) {
        for (size_t j = 0; j < n2; ++j) {
          for (size_t k = 0; k < n3; ++k, ++p) {
            ac(i, j, k) = expected_results[p];
          }
        }
      }
    }
  }
};
// ... structure to allow tests to be run on (some) arbitrary type

// clang-format off
// #defines for supported types
#define SUPPORTED_TYPES_TO_TEST_BOTH

// NB: MyMatrix and MyData are supplied as samples of how to write a custom
// data class that can be used by the NAG interfaces (see example directory)
// the array3D_wrapper class is a wrapper around array3D
#define SUPPORTED_TYPES_TO_TEST_WRAPPERS \
  SUPPORTED_TYPES_TO_TEST_BOTH \
  run_this<ut::SORDER::COL_MAJOR, double, data_handling::INOUT::IN, MyTable<double>>("MyTable<double>, double, COL_MAJOR, IN"); \
  run_this<ut::SORDER::COL_MAJOR, double, data_handling::INOUT::OUT, MyTable<double>>("MyTable<double>, double, COL_MAJOR, OUT"); \
  run_this<ut::SORDER::COL_MAJOR, double, data_handling::INOUT::INOUT, MyTable<double>>("MyTable<double>, double, COL_MAJOR, INOUT"); \
  run_this<ut::SORDER::COL_MAJOR, types::f77_integer, data_handling::INOUT::IN, MyTable<types::f77_integer>>("MyTable<f77_integer>, f77_integer, COL_MAJOR, IN"); \
  run_this<ut::SORDER::COL_MAJOR, types::f77_integer, data_handling::INOUT::OUT, MyTable<types::f77_integer>>("MyTable<f77_integer>, f77_integer, COL_MAJOR, OUT"); \
  run_this<ut::SORDER::COL_MAJOR, types::f77_integer, data_handling::INOUT::INOUT, MyTable<types::f77_integer>>("MyTable<f77_integer>, f77_integer, COL_MAJOR, INOUT"); \
\
  run_this<ut::SORDER::COL_MAJOR, double, data_handling::INOUT::IN, MyData<double>>("MyData<double>, double, COL_MAJOR, IN"); \
  run_this<ut::SORDER::COL_MAJOR, double, data_handling::INOUT::OUT, MyData<double>>("MyData<double>, double, COL_MAJOR, OUT"); \
  run_this<ut::SORDER::COL_MAJOR, double, data_handling::INOUT::INOUT, MyData<double>>("MyData<double>, double, COL_MAJOR, INOUT"); \
  run_this<ut::SORDER::COL_MAJOR, types::f77_integer, data_handling::INOUT::IN, MyData<types::f77_integer>>("MyData<f77_integer>, f77_integer, COL_MAJOR, IN"); \
  run_this<ut::SORDER::COL_MAJOR, types::f77_integer, data_handling::INOUT::OUT, MyData<types::f77_integer>>("MyData<f77_integer>, f77_integer, COL_MAJOR, OUT"); \
  run_this<ut::SORDER::COL_MAJOR, types::f77_integer, data_handling::INOUT::INOUT, MyData<types::f77_integer>>("MyData<f77_integer>, f77_integer, COL_MAJOR, INOUT"); \
\
  run_this<ut::SORDER::COL_MAJOR, double, data_handling::INOUT::IN, ut::array3D_wrapper<double, data_handling::INOUT::IN, ut::SORDER::COL_MAJOR>, ut::CONST_DATA_POINTER>("ut::array3D_wrapper<double, IN>, double, COL_MAJOR, IN"); \
  run_this<ut::SORDER::COL_MAJOR, double, data_handling::INOUT::OUT, ut::array3D_wrapper<double, data_handling::INOUT::OUT, ut::SORDER::COL_MAJOR>, ut::CONST_DATA_POINTER>("ut::array3D_wrapper<double, OUT>, double, COL_MAJOR, OUT"); \
  run_this<ut::SORDER::COL_MAJOR, double, data_handling::INOUT::INOUT, ut::array3D_wrapper<double, data_handling::INOUT::INOUT, ut::SORDER::COL_MAJOR>, ut::CONST_DATA_POINTER>("ut::array3D_wrapper<double, INOUT>, double, COL_MAJOR, INOUT"); \
  run_this<ut::SORDER::COL_MAJOR, types::f77_integer, data_handling::INOUT::IN, ut::array3D_wrapper<types::f77_integer, data_handling::INOUT::IN, ut::SORDER::COL_MAJOR>, ut::CONST_DATA_POINTER>("ut::array3D_wrapper<f77_integer, IN>, f77_integer, COL_MAJOR, IN"); \
  run_this<ut::SORDER::COL_MAJOR, types::f77_integer, data_handling::INOUT::OUT, ut::array3D_wrapper<types::f77_integer, data_handling::INOUT::OUT, ut::SORDER::COL_MAJOR>, ut::CONST_DATA_POINTER>("ut::array3D_wrapper<f77_integer, OUT>, f77_integer, COL_MAJOR, OUT"); \
  run_this<ut::SORDER::COL_MAJOR, types::f77_integer, data_handling::INOUT::INOUT, ut::array3D_wrapper<types::f77_integer, data_handling::INOUT::INOUT, ut::SORDER::COL_MAJOR>, ut::CONST_DATA_POINTER>("ut::array3D_wrapper<f77_integer, INOUT>, f77_integer, COL_MAJOR, INOUT"); \
\
  run_this<ut::SORDER::ROW_MAJOR, double, data_handling::INOUT::IN, ut::array3D_wrapper<double, data_handling::INOUT::IN, ut::SORDER::ROW_MAJOR>, ut::CONST_DATA_POINTER>("ut::array3D_wrapper<double, IN>, double, ROW_MAJOR, IN"); \
  run_this<ut::SORDER::ROW_MAJOR, double, data_handling::INOUT::OUT, ut::array3D_wrapper<double, data_handling::INOUT::OUT, ut::SORDER::ROW_MAJOR>, ut::CONST_DATA_POINTER>("ut::array3D_wrapper<double, OUT>, double, ROW_MAJOR, OUT"); \
  run_this<ut::SORDER::ROW_MAJOR, double, data_handling::INOUT::INOUT, ut::array3D_wrapper<double, data_handling::INOUT::INOUT, ut::SORDER::ROW_MAJOR>, ut::CONST_DATA_POINTER>("ut::array3D_wrapper<double, INOUT>, double, ROW_MAJOR, INOUT"); \
  run_this<ut::SORDER::ROW_MAJOR, types::f77_integer, data_handling::INOUT::IN, ut::array3D_wrapper<types::f77_integer, data_handling::INOUT::IN, ut::SORDER::ROW_MAJOR>, ut::CONST_DATA_POINTER>("ut::array3D_wrapper<f77_integer, IN>, f77_integer, ROW_MAJOR, IN"); \
  run_this<ut::SORDER::ROW_MAJOR, types::f77_integer, data_handling::INOUT::OUT, ut::array3D_wrapper<types::f77_integer, data_handling::INOUT::OUT, ut::SORDER::ROW_MAJOR>, ut::CONST_DATA_POINTER>("ut::array3D_wrapper<f77_integer, OUT>, f77_integer, ROW_MAJOR, OUT"); \
  run_this<ut::SORDER::ROW_MAJOR, types::f77_integer, data_handling::INOUT::INOUT, ut::array3D_wrapper<types::f77_integer, data_handling::INOUT::INOUT, ut::SORDER::ROW_MAJOR>, ut::CONST_DATA_POINTER>("ut::array3D_wrapper<f77_integer, INOUT>, f77_integer, ROW_MAJOR, INOUT");

#define SUPPORTED_TYPES_TO_TEST_CALLBACKS \
  SUPPORTED_TYPES_TO_TEST_BOTH \
  run_this<ut::SORDER::COL_MAJOR, double, data_handling::INOUT::IN, utility::array3D<double, data_handling::INOUT::IN>, ut::CONST_DATA_POINTER>("ut::array3D<double>, double, COL_MAJOR, IN"); \
  run_this<ut::SORDER::COL_MAJOR, double, data_handling::INOUT::OUT, utility::array3D<double, data_handling::INOUT::OUT>, ut::CONST_DATA_POINTER>("ut::array3D<double>, double, COL_MAJOR, OUT"); \
  run_this<ut::SORDER::COL_MAJOR, double, data_handling::INOUT::INOUT, utility::array3D<double, data_handling::INOUT::INOUT>, ut::CONST_DATA_POINTER>("ut::array3D<double>, double, COL_MAJOR, INOUT"); \
  run_this<ut::SORDER::COL_MAJOR, types::f77_integer, data_handling::INOUT::IN, utility::array3D<types::f77_integer, data_handling::INOUT::IN>, ut::CONST_DATA_POINTER>("ut::array3D<f77_integer>, f77_integer, COL_MAJOR, IN"); \
  run_this<ut::SORDER::COL_MAJOR, types::f77_integer, data_handling::INOUT::OUT, utility::array3D<types::f77_integer, data_handling::INOUT::OUT>, ut::CONST_DATA_POINTER>("ut::array3D<f77_integer>, f77_integer, COL_MAJOR, OUT"); \
  run_this<ut::SORDER::COL_MAJOR, types::f77_integer, data_handling::INOUT::INOUT, utility::array3D<types::f77_integer, data_handling::INOUT::INOUT>, ut::CONST_DATA_POINTER>("ut::array3D<f77_integer>, f77_integer, COL_MAJOR, INOUT"); \
\
  run_this<ut::SORDER::ROW_MAJOR, double, data_handling::INOUT::IN, utility::array3D<double, data_handling::INOUT::IN>, ut::CONST_DATA_POINTER>("ut::array3D<double>, double, ROW_MAJOR, IN"); \
  run_this<ut::SORDER::ROW_MAJOR, double, data_handling::INOUT::OUT, utility::array3D<double, data_handling::INOUT::OUT>, ut::CONST_DATA_POINTER>("ut::array3D<double>, double, ROW_MAJOR, OUT"); \
  run_this<ut::SORDER::ROW_MAJOR, double, data_handling::INOUT::INOUT, utility::array3D<double, data_handling::INOUT::INOUT>, ut::CONST_DATA_POINTER>("ut::array3D<double>, double, ROW_MAJOR, INOUT"); \
  run_this<ut::SORDER::ROW_MAJOR, types::f77_integer, data_handling::INOUT::IN, utility::array3D<types::f77_integer, data_handling::INOUT::IN>, ut::CONST_DATA_POINTER>("ut::array3D<f77_integer>, f77_integer, ROW_MAJOR, IN"); \
  run_this<ut::SORDER::ROW_MAJOR, types::f77_integer, data_handling::INOUT::OUT, utility::array3D<types::f77_integer, data_handling::INOUT::OUT>, ut::CONST_DATA_POINTER>("ut::array3D<f77_integer>, f77_integer, ROW_MAJOR, OUT"); \
  run_this<ut::SORDER::ROW_MAJOR, types::f77_integer, data_handling::INOUT::INOUT, utility::array3D<types::f77_integer, data_handling::INOUT::INOUT>, ut::CONST_DATA_POINTER>("ut::array3D<f77_integer>, f77_integer, ROW_MAJOR, INOUT");

// #defines for internal types (these are not expected to be used as
// input to NAG routines, but are leveraging some of the same tests)
// (RawData<RT,inout> can potentially be used for local arrays, but
// never with data_handling::IN)
#define INTERNAL_TYPES_TO_TEST_WRAPPERS \
  run_this<ut::SORDER::COL_MAJOR, double, data_handling::INOUT::OUT, data_handling::RawData<double, data_handling::INOUT::OUT>, ut::INTERNAL>("ut::RawData<double, OUT>, double, COL_MAJOR, OUT"); \
  run_this<ut::SORDER::COL_MAJOR, double, data_handling::INOUT::INOUT, data_handling::RawData<double, data_handling::INOUT::INOUT>, ut::INTERNAL>("ut::RawData<double, INOUT>, double, COL_MAJOR, INOUT"); \
  run_this<ut::SORDER::COL_MAJOR, types::f77_integer, data_handling::INOUT::OUT, data_handling::RawData<types::f77_integer, data_handling::INOUT::OUT>, ut::INTERNAL>("ut::RawData<f77_integer, OUT>, f77_integer, COL_MAJOR, OUT"); \
  run_this<ut::SORDER::COL_MAJOR, types::f77_integer, data_handling::INOUT::INOUT, data_handling::RawData<types::f77_integer, data_handling::INOUT::INOUT>, ut::INTERNAL>("ut::RawData<f77_integer, INOUT>, f77_integer, COL_MAJOR, INOUT"); \
  run_this<ut::SORDER::ROW_MAJOR, double, data_handling::INOUT::OUT, data_handling::RawData<double, data_handling::INOUT::OUT>, ut::INTERNAL>("ut::RawData<double, OUT>, double, ROW_MAJOR, OUT"); \
  run_this<ut::SORDER::ROW_MAJOR, double, data_handling::INOUT::INOUT, data_handling::RawData<double, data_handling::INOUT::INOUT>, ut::INTERNAL>("ut::RawData<double, INOUT>, double, ROW_MAJOR, INOUT"); \
  run_this<ut::SORDER::ROW_MAJOR, types::f77_integer, data_handling::INOUT::OUT, data_handling::RawData<types::f77_integer, data_handling::INOUT::OUT>, ut::INTERNAL>("ut::RawData<f77_integer, OUT>, f77_integer, ROW_MAJOR, OUT"); \
  run_this<ut::SORDER::ROW_MAJOR, types::f77_integer, data_handling::INOUT::INOUT, data_handling::RawData<types::f77_integer, data_handling::INOUT::INOUT>, ut::INTERNAL>("ut::RawData<f77_integer, INOUT>, f77_integer, ROW_MAJOR, INOUT");

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

  template <enum ut::SORDER sorder, typename RT,
            enum data_handling::INOUT inout, typename AC,
            enum ut::TYPE_IS type_is = ut::GENERAL>
  void run_this(std::string label = "") {
    SUB_TITLE(label);
    static const size_t n1_a = 6;
    static const size_t n2_a = 5;
    static const size_t n3_a = 3;
    std::unique_ptr<AC> ac_a =
      test_setup<sorder, RT, inout, AC, type_is>::get_test_data(n1_a, n2_a,
                                                                n3_a);

    static const size_t n1_b = 8;
    static const size_t n2_b = 7;
    static const size_t n3_b = 4;
    std::unique_ptr<AC> ac_b =
      test_setup<sorder, RT, inout, AC, type_is>::get_test_data(n1_b, n2_b,
                                                                n3_b);

    call_test<RT, inout, AC, type_is>(ac_a, ac_b, n1_a, n2_a, n3_a, n1_b, n2_b,
                                      n3_b);
  }

  template <typename RT, enum data_handling::INOUT inout, typename AC,
            enum ut::TYPE_IS type_is>
  auto call_test(std::unique_ptr<AC> &ac_a, std::unique_ptr<AC> &ac_b,
                 size_t n1_a, size_t n2_a, size_t n3_a, size_t n1_b,
                 size_t n2_b, size_t n3_b) ->
    typename std::enable_if<!ut::is_internal_type<type_is>::value, void>::type {
    using RD = data_handling::RawData<RT, inout, AC>;
    RD local_ac_a(*ac_a);
    RD local_ac_b(*ac_b);
    do_test<RD, inout>(local_ac_a, local_ac_b, n1_a, n2_a, n3_a, n1_b, n2_b,
                       n3_b);
  }
  template <typename RT, enum data_handling::INOUT inout, typename AC,
            enum ut::TYPE_IS type_is>
  auto call_test(std::unique_ptr<AC> &ac_a, std::unique_ptr<AC> &ac_b,
                 size_t n1_a, size_t n2_a, size_t n3_a, size_t n1_b,
                 size_t n2_b, size_t n3_b) ->
    typename std::enable_if<ut::is_internal_type<type_is>::value, void>::type {
    do_test<AC, inout>(*ac_a, *ac_b, n1_a, n2_a, n3_a, n1_b, n2_b, n3_b);
  }

  template <typename RD, enum data_handling::INOUT inout>
  void do_test(RD &local_ac_a, RD &local_ac_b, size_t n1_a, size_t n2_a,
               size_t n3_a, size_t n1_b, size_t n2_b, size_t n3_b) {
    nagcpp::error_handler::ErrorHandler eh;
    {
      SUB_TEST("get size: single array passed");
      ASSERT_EQUAL_UNSIGNED(
        data_handling::get_size(eh, "VAR1_1", local_ac_a, 1), n1_a);
      ASSERT_EQUAL_UNSIGNED(
        data_handling::get_size(eh, "VAR1_2", local_ac_a, 2), n2_a);
      ASSERT_EQUAL_UNSIGNED(
        data_handling::get_size(eh, "VAR1_3", local_ac_a, 3), n3_a);
    }
    {
      SUB_TEST("get size: multiple arrays - should be taking first available");
      ASSERT_EQUAL_UNSIGNED(data_handling::get_size(eh, "VAR1_4", local_ac_a, 1,
                                                    local_ac_b, 1),
                            n1_a);
      ASSERT_EQUAL_UNSIGNED(data_handling::get_size(eh, "VAR1_5", local_ac_a, 2,
                                                    local_ac_b, 1),
                            n2_a);
      ASSERT_EQUAL_UNSIGNED(data_handling::get_size(eh, "VAR1_6", local_ac_a, 3,
                                                    local_ac_b, 1),
                            n3_a);
    }
    {
      SUB_TEST("get size: multiple arrays - no error checking on individual "
               "arrays");
      data_handling::RawData<double, inout> local_tmp(10);
      ASSERT_EQUAL_UNSIGNED(data_handling::get_size(eh, "VAR1_7", local_ac_a, 1,
                                                    local_tmp, 2),
                            n1_a);
      ASSERT_EQUAL_UNSIGNED(data_handling::get_size(eh, "VAR1_8", local_ac_a, 2,
                                                    local_tmp, 2),
                            n2_a);
      ASSERT_EQUAL_UNSIGNED(data_handling::get_size(eh, "VAR1_9", local_ac_a, 3,
                                                    local_tmp, 2),
                            n3_a);
      ASSERT_EQUAL_UNSIGNED(data_handling::get_size(eh, "VAR1_10", local_tmp, 2,
                                                    local_ac_a, 1),
                            n1_a);
      ASSERT_EQUAL_UNSIGNED(data_handling::get_size(eh, "VAR1_11", local_tmp, 2,
                                                    local_ac_a, 2),
                            n2_a);
      ASSERT_EQUAL_UNSIGNED(data_handling::get_size(eh, "VAR1_12", local_tmp, 2,
                                                    local_ac_a, 3),
                            n3_a);
    }
  }
};
// clang-format off
REGISTER_TEST(test_get_size_function, "Test the function that returns the size of the array");
// clang-format on

//************************************************
struct test_LD_SD_TD_functions : public TestCase {
  DEFINE_RUN_METHOD_WRAPPERS

  template <enum ut::SORDER sorder, typename RT,
            enum data_handling::INOUT inout, typename AC,
            enum ut::TYPE_IS type_is = ut::GENERAL>
  void run_this(std::string label = "") {
    SUB_TITLE(label);
    static const size_t n1_a = 10;
    static const size_t n2_a = 5;
    static const size_t n3_a = 2;
    std::unique_ptr<AC> ac_a =
      test_setup<sorder, RT, inout, AC, type_is>::get_test_data(n1_a, n2_a,
                                                                n3_a);

    call_test<sorder, RT, inout, AC, type_is>(ac_a, n1_a, n2_a, n3_a);
  }

  template <enum ut::SORDER sorder, typename RT,
            enum data_handling::INOUT inout, typename AC,
            enum ut::TYPE_IS type_is>
  auto call_test(std::unique_ptr<AC> &ac_a, size_t n1_a, size_t n2_a,
                 size_t n3_a) ->
    typename std::enable_if<!ut::is_internal_type<type_is>::value, void>::type {
    using RD = data_handling::RawData<RT, inout, AC>;
    RD local_ac_a(*ac_a);
    do_test<sorder, RD>(local_ac_a, n1_a, n2_a, n3_a);
  }
  template <enum ut::SORDER sorder, typename RT,
            enum data_handling::INOUT inout, typename AC,
            enum ut::TYPE_IS type_is>
  auto call_test(std::unique_ptr<AC> &ac_a, size_t n1_a, size_t n2_a,
                 size_t n3_a) ->
    typename std::enable_if<ut::is_internal_type<type_is>::value, void>::type {
    do_test<sorder, AC>(*ac_a, n1_a, n2_a, n3_a);
  }

  template <enum ut::SORDER sorder, typename RD>
  void do_test(RD &local_ac_a, size_t n1_a, size_t n2_a, size_t n3_a) {
    types::f77_integer this_sorder_flag = ut::sorder_flag<sorder>();
    if (ut::is_col_major<sorder>::value) {
      ASSERT_EQUAL(n1_a,
                   static_cast<size_t>(local_ac_a.get_LD(this_sorder_flag)));
      ASSERT_EQUAL(n2_a,
                   static_cast<size_t>(local_ac_a.get_SD(this_sorder_flag)));
      ASSERT_EQUAL(n3_a,
                   static_cast<size_t>(local_ac_a.get_TD(this_sorder_flag)));
      ASSERT_EQUAL((10 * n1_a), static_cast<size_t>(local_ac_a.get_LD(
                                  this_sorder_flag, 10 * n1_a)));

    } else {
      ASSERT_EQUAL(n1_a,
                   static_cast<size_t>(local_ac_a.get_TD(this_sorder_flag)));
      ASSERT_EQUAL(n2_a,
                   static_cast<size_t>(local_ac_a.get_SD(this_sorder_flag)));
      ASSERT_EQUAL(n3_a,
                   static_cast<size_t>(local_ac_a.get_LD(this_sorder_flag)));
      ASSERT_EQUAL((10 * n3_a), static_cast<size_t>(local_ac_a.get_LD(
                                  this_sorder_flag, 10 * n3_a)));
    }
  }
};
// clang-format off
REGISTER_TEST(test_LD_SD_TD_functions, "Test the functions that get the lead, second and trailing dimensions");
// clang-format on

//************************************************
struct test_get_storage_order_function : public TestCase {
  DEFINE_RUN_METHOD_WRAPPERS

  template <enum ut::SORDER sorder, typename RT,
            enum data_handling::INOUT inout, typename AC,
            enum ut::TYPE_IS type_is = ut::GENERAL>
  void run_this(std::string label = "") {
    SUB_TITLE(label);
    static const size_t n1_a = 10;
    static const size_t n2_a = 5;
    static const size_t n3_a = 3;
    std::unique_ptr<AC> ac_a =
      test_setup<sorder, RT, inout, AC, type_is>::get_test_data(n1_a, n2_a,
                                                                n3_a);

    call_test<sorder, RT, inout, AC, type_is>(ac_a, n1_a, n2_a, n3_a);
  }

  template <enum ut::SORDER sorder, typename RT,
            enum data_handling::INOUT inout, typename AC,
            enum ut::TYPE_IS type_is>
  auto call_test(std::unique_ptr<AC> &ac_a, size_t n1_a, size_t n2_a,
                 size_t n3_a) ->
    typename std::enable_if<!ut::is_internal_type<type_is>::value, void>::type {
    using RD = data_handling::RawData<RT, inout, AC>;
    RD local_ac_a(*ac_a);
    do_test<sorder, RD>(local_ac_a, n1_a, n2_a, n3_a);
  }
  template <enum ut::SORDER sorder, typename RT,
            enum data_handling::INOUT inout, typename AC,
            enum ut::TYPE_IS type_is>
  auto call_test(std::unique_ptr<AC> &ac_a, size_t n1_a, size_t n2_a,
                 size_t n3_a) ->
    typename std::enable_if<ut::is_internal_type<type_is>::value, void>::type {
    do_test<sorder, AC>(*ac_a, n1_a, n2_a, n3_a);
  }

  template <enum ut::SORDER sorder, typename RD>
  void do_test(RD &local_ac_a, size_t n1_a, size_t n2_a, size_t n3_a) {
    types::f77_integer expected_sorder_flag = ut::sorder_flag<sorder>();
    types::f77_integer this_sorder_flag =
      data_handling::get_storage_order(ut::is_col_major<sorder>::value,
                                       local_ac_a);
    ASSERT_EQUAL(expected_sorder_flag, this_sorder_flag);
  }
};
// clang-format off
REGISTER_TEST(test_get_storage_order_function, "Test the function that gets the storage order");
// clang-format on

//************************************************
struct test_check_function : public TestCase {
  DEFINE_RUN_METHOD_WRAPPERS

  template <enum ut::SORDER sorder, typename RT,
            enum data_handling::INOUT inout, typename AC,
            enum ut::TYPE_IS type_is = ut::GENERAL>
  void run_this(std::string label = "") {
    SUB_TITLE(label);
    static const size_t n1_a = 5;
    static const size_t n2_a = 12;
    static const size_t n3_a = 4;
    std::unique_ptr<AC> ac =
      test_setup<sorder, RT, inout, AC, type_is>::get_test_data(n1_a, n2_a,
                                                                n3_a);
    call_test<sorder, RT, inout, AC, type_is>(ac, n1_a, n2_a, n3_a);
  }

  template <enum ut::SORDER sorder, typename RT,
            enum data_handling::INOUT inout, typename AC,
            enum ut::TYPE_IS type_is>
  auto call_test(std::unique_ptr<AC> &ac, size_t n1_a, size_t n2_a, size_t n3_a)
    ->
    typename std::enable_if<!ut::is_internal_type<type_is>::value, void>::type {
    using RD = data_handling::RawData<RT, inout, AC>;
    RD local_ac(*ac);
    do_test<sorder, RD>(local_ac, n1_a, n2_a, n3_a);
  }
  template <enum ut::SORDER sorder, typename RT,
            enum data_handling::INOUT inout, typename AC,
            enum ut::TYPE_IS type_is>
  auto call_test(std::unique_ptr<AC> &ac, size_t n1_a, size_t n2_a, size_t n3_a)
    ->
    typename std::enable_if<ut::is_internal_type<type_is>::value, void>::type {
    do_test<sorder, AC>(*ac, n1_a, n2_a, n3_a);
  }

  template <enum ut::SORDER sorder, typename RD>
  void do_test(RD &local_ac, size_t n1_a, size_t n2_a, size_t n3_a) {
    nagcpp::error_handler::ErrorHandler eh;
    {
      SUB_TEST("check function: correct size");
      ASSERT_THROWS_NOTHING(local_ac.check(
        eh, "VAR1_1", true, ut::sorder_flag<sorder>(), n1_a, n2_a, n3_a));
    }
    {
      SUB_TEST("check function: expected 2D array of different size");
      // rows one larger
      ASSERT_THROWS(error_handler::ErrorException,
                    local_ac.check(eh, "VAR1_2", true,
                                   ut::sorder_flag<sorder>(), n1_a + 1, n2_a,
                                   n3_a));
      ASSERT_TRUE(eh.error_thrown);
      ASSERT_HAS_KEYWORD(eh.msg, "VAR1_2");

      // rows one smaller
      ASSERT_THROWS(error_handler::ErrorException,
                    local_ac.check(eh, "VAR1_3", true,
                                   ut::sorder_flag<sorder>(), n1_a - 1, n2_a,
                                   n3_a));
      ASSERT_TRUE(eh.error_thrown);
      ASSERT_HAS_KEYWORD(eh.msg, "VAR1_3");

      // columns one larger
      ASSERT_THROWS(error_handler::ErrorException,
                    local_ac.check(eh, "VAR1_4", true,
                                   ut::sorder_flag<sorder>(), n1_a, n2_a + 1,
                                   n3_a));
      ASSERT_TRUE(eh.error_thrown);
      ASSERT_HAS_KEYWORD(eh.msg, "VAR1_4");

      // columns one smaller
      ASSERT_THROWS(error_handler::ErrorException,
                    local_ac.check(eh, "VAR1_5", true,
                                   ut::sorder_flag<sorder>(), n1_a, n2_a - 1,
                                   n3_a));
      ASSERT_TRUE(eh.error_thrown);
      ASSERT_HAS_KEYWORD(eh.msg, "VAR1_5");

      // tables one larger
      ASSERT_THROWS(error_handler::ErrorException,
                    local_ac.check(eh, "VAR1_6", true,
                                   ut::sorder_flag<sorder>(), n1_a, n2_a,
                                   n3_a + 1));
      ASSERT_TRUE(eh.error_thrown);
      ASSERT_HAS_KEYWORD(eh.msg, "VAR1_6");

      // tables one smaller
      ASSERT_THROWS(error_handler::ErrorException,
                    local_ac.check(eh, "VAR1_7", true,
                                   ut::sorder_flag<sorder>(), n1_a, n2_a,
                                   n3_a - 1));
      ASSERT_TRUE(eh.error_thrown);
      ASSERT_HAS_KEYWORD(eh.msg, "VAR1_7");

      // check that EH is reset after a correct check
      ASSERT_THROWS_NOTHING(local_ac.check(
        eh, "VAR1_8", true, ut::sorder_flag<sorder>(), n1_a, n2_a, n3_a));
      ASSERT_FALSE(eh.error_thrown);
    }
    {
      SUB_TEST("check function: expected 1D array");
      ASSERT_THROWS(error_handler::ErrorException,
                    local_ac.check(eh, "VAR1_8", true, n1_a));
      ASSERT_TRUE(eh.error_thrown);
      ASSERT_HAS_KEYWORD(eh.msg, "VAR1_8");

      // check that EH is reset after a correct check
      ASSERT_THROWS_NOTHING(local_ac.check(
        eh, "VAR1_9", true, ut::sorder_flag<sorder>(), n1_a, n2_a, n3_a));
      ASSERT_FALSE(eh.error_thrown);
    }
    {
      SUB_TEST("check function: expected 2D array");
      ASSERT_THROWS(error_handler::ErrorException,
                    local_ac.check(eh, "VAR1_10", true,
                                   ut::sorder_flag<sorder>(), n1_a, n2_a));
      ASSERT_TRUE(eh.error_thrown);
      ASSERT_HAS_KEYWORD(eh.msg, "VAR1_10");

      // check that EH is reset after a correct check
      ASSERT_THROWS_NOTHING(local_ac.check(
        eh, "VAR1_11", true, ut::sorder_flag<sorder>(), n1_a, n2_a, n3_a));
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

  template <enum ut::SORDER sorder, typename RT,
            enum data_handling::INOUT inout, typename AC,
            enum ut::TYPE_IS type_is = ut::GENERAL>
  void run_this(std::string label = "") {
    SUB_TITLE(label);
    static const size_t n1_a = 11;
    static const size_t n2_a = 7;
    static const size_t n3_a = 4;
    std::unique_ptr<AC> ac =
      test_setup<sorder, RT, inout, AC, type_is>::get_test_data(n1_a, n2_a,
                                                                n3_a);
    call_test<sorder, RT, inout, AC, type_is>(ac, n1_a, n2_a, n3_a);
  }

  template <enum ut::SORDER sorder, typename RT,
            enum data_handling::INOUT inout, typename AC,
            enum ut::TYPE_IS type_is>
  auto call_test(std::unique_ptr<AC> &ac, size_t n1_a, size_t n2_a, size_t n3_a)
    ->
    typename std::enable_if<!ut::is_internal_type<type_is>::value, void>::type {
    using RD = data_handling::RawData<RT, inout, AC>;
    RD local_ac(*ac);
    do_test<sorder, RT, RD>(local_ac, n1_a, n2_a, n3_a);
  }
  template <enum ut::SORDER sorder, typename RT,
            enum data_handling::INOUT inout, typename AC,
            enum ut::TYPE_IS type_is>
  auto call_test(std::unique_ptr<AC> &ac, size_t n1_a, size_t n2_a, size_t n3_a)
    ->
    typename std::enable_if<ut::is_internal_type<type_is>::value, void>::type {
    do_test<sorder, RT, AC>(*ac, n1_a, n2_a, n3_a);
  }

  template <enum ut::SORDER sorder, typename RT, typename RD>
  void do_test(RD &local_ac, size_t n1_a, size_t n2_a, size_t n3_a) {
    {
      SUB_TEST("data variable: check contiguous memory");
      std::vector<RT> expected_results =
        ut::get_expected_values<sorder, RT>(n1_a, n2_a, n3_a);
      ASSERT_ARRAY_EQUAL((n1_a * n2_a * n3_a), local_ac.data, expected_results);
    }
  }
};
// clang-format off
REGISTER_TEST(test_data_variable, "Test the data class variable");
// clang-format on

//************************************************
struct test_get_data_method : public TestCase {
  DEFINE_RUN_METHOD_WRAPPERS

  template <enum ut::SORDER sorder, typename RT,
            enum data_handling::INOUT inout, typename AC,
            enum ut::TYPE_IS type_is = ut::GENERAL>
  auto run_this(std::string label = "") ->
    typename std::enable_if<ut::is_internal_type<type_is>::value, void>::type {
    // don't run the get_data method on internal arrays
  }

  template <enum ut::SORDER sorder, typename RT,
            enum data_handling::INOUT inout, typename AC,
            enum ut::TYPE_IS type_is = ut::GENERAL>
  auto run_this(std::string label = "") ->
    typename std::enable_if<!ut::is_internal_type<type_is>::value, void>::type {
    using RD = data_handling::RawData<RT, inout, AC>;
    SUB_TITLE(label);
    static const size_t n1_a = 5;
    static const size_t n2_a = 3;
    static const size_t n3_a = 4;
    std::unique_ptr<AC> ac_a =
      test_setup<sorder, RT, inout, AC, type_is>::get_test_data(n1_a, n2_a,
                                                                n3_a);
    static const size_t n1_b = 6;
    static const size_t n2_b = 4;
    static const size_t n3_b = 2;
    std::unique_ptr<AC> ac_b =
      test_setup<sorder, RT, inout, AC, type_is>::get_test_data(n1_b, n2_b,
                                                                n3_b);
    RD local_ac(*ac_a);
    {
      SUB_TEST("data variable: check contiguous memory");
      std::vector<RT> expected_results =
        ut::get_expected_values<sorder, RT>(n1_a, n2_a, n3_a);
      ASSERT_ARRAY_EQUAL((n1_a * n2_a * n3_a), local_ac.data, expected_results);
    }
    {
      SUB_TEST("update local data using get_data method: check sizes");
      nagcpp::error_handler::ErrorHandler eh;
      ASSERT_THROWS_NOTHING(local_ac.check(
        eh, "VAR1_1", true, ut::sorder_flag<sorder>(), n1_a, n2_a, n3_a));
      ASSERT_FALSE(eh.error_thrown);
      local_ac.get_data(*ac_b);
      ASSERT_THROWS_NOTHING(local_ac.check(
        eh, "VAR2_1", true, ut::sorder_flag<sorder>(), n1_b, n2_b, n3_b));
      ASSERT_FALSE(eh.error_thrown);
    }
    {
      SUB_TEST("data variable: check contiguous memory after update");
      std::vector<RT> expected_results =
        ut::get_expected_values<sorder, RT>(n1_b, n2_b, n3_b);
      ASSERT_ARRAY_EQUAL((n1_b * n2_b * n3_b), local_ac.data, expected_results);
    }
  }
};
// clang-format off
REGISTER_TEST(test_get_data_method, "Test the get_data returns contiguous memory (of the expected size)");
// clang-format on

//************************************************
struct test_array_referencing_overload : public TestCase {
  DEFINE_RUN_METHOD_WRAPPERS

  template <enum ut::SORDER sorder, typename RT,
            enum data_handling::INOUT inout, typename AC,
            enum ut::TYPE_IS type_is = ut::GENERAL>
  void run_this(std::string label = "") {
    SUB_TITLE(label);
    static const size_t n1_a = 3;
    static const size_t n2_a = 6;
    static const size_t n3_a = 9;
    std::unique_ptr<AC> ac =
      test_setup<sorder, RT, inout, AC, type_is>::get_test_data(n1_a, n2_a,
                                                                n3_a);
    call_test<sorder, RT, inout, AC, type_is>(ac, n1_a, n2_a, n3_a);
  }

  template <enum ut::SORDER sorder, typename RT,
            enum data_handling::INOUT inout, typename AC,
            enum ut::TYPE_IS type_is>
  auto call_test(std::unique_ptr<AC> &ac, size_t n1_a, size_t n2_a, size_t n3_a)
    ->
    typename std::enable_if<!ut::is_internal_type<type_is>::value, void>::type {
    using RD = data_handling::RawData<RT, inout, AC>;
    RD local_ac(*ac);
    do_test<RT, RD>(local_ac, n1_a, n2_a, n3_a);
  }
  template <enum ut::SORDER sorder, typename RT,
            enum data_handling::INOUT inout, typename AC,
            enum ut::TYPE_IS type_is>
  auto call_test(std::unique_ptr<AC> &ac, size_t n1_a, size_t n2_a, size_t n3_a)
    ->
    typename std::enable_if<ut::is_internal_type<type_is>::value, void>::type {
    do_test<RT, AC>(*ac, n1_a, n2_a, n3_a);
  }

  template <typename RT, typename RD>
  void do_test(RD &local_ac, size_t n1_a, size_t n2_a, size_t n3_a) {
    // deliberately force this to be in column major order
    std::vector<RT> expected_results =
      ut::get_expected_values<ut::SORDER::COL_MAJOR, RT>(n1_a, n2_a, n3_a);
    bool passed = true;
    for (size_t k = 0, p = 0; k < n3_a && passed; ++k) {
      for (size_t j = 0; j < n2_a && passed; ++j) {
        for (size_t i = 0; i < n1_a && passed; ++i, ++p) {
          ASSERT_EQUAL_ONLY_COUNT_FAILURE(local_ac(i, j, k),
                                          expected_results[p]);
        }
      }
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

  template <enum ut::SORDER sorder, typename RT,
            enum data_handling::INOUT inout, typename AC,
            enum ut::TYPE_IS type_is = ut::GENERAL>
  auto run_this(std::string label = "") ->
    typename std::enable_if<data_handling::is_in<inout>::value, void>::type {
    // allocate_local should never be called on an input array
  }

  template <enum ut::SORDER sorder, typename RT,
            enum data_handling::INOUT inout, typename AC,
            enum ut::TYPE_IS type_is = ut::GENERAL>
  auto run_this(std::string label = "") ->
    typename std::enable_if<!data_handling::is_in<inout>::value, void>::type {
    using RD = data_handling::RawData<RT, inout, AC>;
    SUB_TITLE(label);
    static const size_t n1_a = 9;
    static const size_t n2_a = 3;
    static const size_t n3_a = 11;
    std::unique_ptr<AC> ac_a =
      test_setup<sorder, RT, inout, AC, type_is>::get_test_data(n1_a, n2_a,
                                                                n3_a);
    RD local_ac(*ac_a);

    static const size_t n1_b = 5;
    static const size_t n2_b = 8;
    static const size_t n3_b = 4;
    local_ac.allocate_local(n1_b, n2_b, n3_b);

    // set an element of the array to something - this is just
    // here as a valgrind check the memory is allocated
    local_ac.data[0] = static_cast<RT>(3.1);
    local_ac.data[(n1_b * n2_b * n3_b) - 1] = static_cast<RT>(3.0);

    nagcpp::error_handler::ErrorHandler eh;
    ASSERT_THROWS_NOTHING(local_ac.check(
      eh, "VAR1_1", true, ut::sorder_flag<sorder>(), n1_b, n2_b, n3_b));
  }
};
// clang-format off
REGISTER_TEST(test_allocate_local_method, "Test we can allocate a local array with RawData templated using user data type");
// clang-format on

//************************************************
struct test_resize_method : public TestCase {
  DEFINE_RUN_METHOD_WRAPPERS

  template <enum ut::SORDER sorder, typename RT,
            enum data_handling::INOUT inout, typename AC,
            enum ut::TYPE_IS type_is = ut::GENERAL>
  auto run_this(std::string label = "") ->
    typename std::enable_if<!ut::has_resize<inout, type_is>::value,
                            void>::type {
    // resize should never be called on things like an input array or an internal array
    // or an array defined via type_is to not have a resize
  }

  template <enum ut::SORDER sorder, typename RT,
            enum data_handling::INOUT inout, typename AC,
            enum ut::TYPE_IS type_is = ut::GENERAL>
  auto run_this(std::string label = "") ->
    typename std::enable_if<ut::has_resize<inout, type_is>::value, void>::type {
    using RD = data_handling::RawData<RT, inout, AC>;
    SUB_TITLE(label);
    nagcpp::error_handler::ErrorHandler eh;
    {
      SUB_TEST("resize when initial container is null");
      std::unique_ptr<AC> ac_a =
        test_setup<sorder, RT, inout, AC, type_is>::get_test_data(0, 0, 0);
      RD local_ac(*ac_a);

      ASSERT_CPOINTER_IS_NULL(local_ac.data);
      static const size_t n1_a = 3;
      static const size_t n2_a = 6;
      static const size_t n3_a = 6;
      local_ac.resize(*ac_a, n1_a, n2_a, n3_a);

      ASSERT_CPOINTER_IS_NOT_NULL(local_ac.data);
      if (last_assert_passed) {
        // set an element of the array to something - this is just
        // here as a valgrind check the memory is allocated
        local_ac.data[0] = static_cast<RT>(3.1);
        local_ac.data[(n1_a * n2_a * n3_a) - 1] = static_cast<RT>(3.0);
      }
      ASSERT_THROWS_NOTHING(local_ac.check(
        eh, "VAR1_1", true, ut::sorder_flag<sorder>(), n1_a, n2_a, n3_a));
    }

    // the wrappers should never call a naked resize that has to
    // preserve the data, that should always be done via the copyback method
    // {
    //   // this may happen as part of the copyback call when
    //   // resizing at the same time (in wrappers, the resize when there is data will always
    //   // be to a smaller array)
    //   SUB_TEST("resize to smaller when initial container is not null");
    //   static const size_t n1_a = 8;
    //   static const size_t n2_a = 10;
    //   static const size_t n3_a = 6;
    //   std::unique_ptr<AC> ac_a =
    //     test_setup<sorder, RT, inout, AC, type_is>::get_test_data(n1_a, n2_a,
    //                                                               n3_a);
    //   RD local_ac(*ac_a);
    //   ASSERT_THROWS_NOTHING(local_ac.check(
    //     eh, "VAR1_1", true, ut::sorder_flag<sorder>(), n1_a, n2_a, n3_a));

    //   ASSERT_CPOINTER_IS_NOT_NULL(local_ac.data);
    //   static const size_t n1_b = 6;
    //   static const size_t n2_b = 7;
    //   static const size_t n3_b = 5;
    //   local_ac.resize(*ac_a, n1_b, n2_b, n3_b);

    //   ASSERT_CPOINTER_IS_NOT_NULL(local_ac.data);
    //   ASSERT_THROWS_NOTHING(local_ac.check(
    //     eh, "VAR1_1", true, ut::sorder_flag<sorder>(), n1_b, n2_b, n3_b));

    //   // check that the resize preserves input in this case
    //   std::vector<RT> full_results =
    //     ut::get_expected_values<sorder, RT>(n1_a, n2_a, n3_a);
    //   std::vector<RT> expected_results =
    //     ut::top_left<sorder, RT>(full_results.data(), n1_a, n2_a, n3_a, n1_b,
    //                              n2_b, n3_b);
    //   ASSERT_ARRAY_EQUAL((n1_b * n2_b * n3_b), local_ac.data, expected_results);
    // }
  }
};
// clang-format off
REGISTER_TEST(test_resize_method, "Test the method that resizes arrays");
// clang-format on

//************************************************
struct test_copy_back_method_array_preallocated : public TestCase {
  DEFINE_RUN_METHOD_WRAPPERS

  template <enum ut::SORDER sorder, typename RT,
            enum data_handling::INOUT inout, typename AC,
            enum ut::TYPE_IS type_is = ut::GENERAL>
  auto run_this(std::string label = "") ->
    typename std::enable_if<data_handling::is_in<inout>::value ||
                              ut::is_internal_type<type_is>::value,
                            void>::type {
    // copyback should never be called on an input array or an internal array
  }

  template <enum ut::SORDER sorder, typename RT,
            enum data_handling::INOUT inout, typename AC,
            enum ut::TYPE_IS type_is = ut::GENERAL>
  auto run_this(std::string label = "") ->
    typename std::enable_if<!(data_handling::is_in<inout>::value ||
                              ut::is_internal_type<type_is>::value),
                            void>::type {
    using RD = data_handling::RawData<RT, inout, AC>;
    SUB_TITLE(label);
    nagcpp::error_handler::ErrorHandler eh;
    {
      SUB_TEST("copy_back with no resize");
      static const size_t n1_a = 3;
      static const size_t n2_a = 10;
      static const size_t n3_a = 4;
      std::unique_ptr<AC> ac_a =
        test_setup<sorder, RT, inout, AC, type_is>::get_test_data(n1_a, n2_a,
                                                                  n3_a);
      RD local_ac(*ac_a);

      // get a set of expected results, different from those used in test_setup
      std::vector<RT> expected_results =
        ut::get_expected_values<sorder, RT>(n1_a, n2_a, n3_a,
                                            static_cast<RT>(32.23));

      // copy the expected results into RawData
      for (size_t p = 0; p < (n1_a * n2_a * n3_a); ++p) {
        local_ac.data[p] = expected_results[p];
      }
      // copy back from RawData to users type
      local_ac.copy_back(*ac_a);
      // compare values
      auto max_diff = test_setup<sorder, RT, inout, AC, type_is>::max_abs_diff(
        *ac_a, expected_results, n1_a, n2_a, n3_a);
      ASSERT_EQUAL(max_diff, 0);

      // check the meta information
      types::f77_integer isorder =
        data_handling::get_storage_order(true, local_ac);
      bool local_storage_order = data_handling::set_is_col_major(isorder);

      bool meta_info_ok =
        test_setup<sorder, RT, inout, AC, type_is>::check_meta_info(
          *ac_a, local_storage_order, n1_a, n2_a, n3_a);
      ASSERT_TRUE(meta_info_ok);
    }
    {
      SUB_TEST("resize container to smaller and copy back");
      static const size_t n1_a = 11;
      static const size_t n2_a = 10;
      static const size_t n3_a = 4;
      std::unique_ptr<AC> ac_a =
        test_setup<sorder, RT, inout, AC, type_is>::get_test_data(n1_a, n2_a,
                                                                  n3_a);
      RD local_ac(*ac_a);

      // get a set of expected results, different from those used in test_setup
      static const size_t n1_b = 9;
      static const size_t n2_b = 8;
      static const size_t n3_b = 3;
      std::vector<RT> expected_results =
        ut::get_expected_values<sorder, RT>(n1_b, n2_b, n3_b,
                                            static_cast<RT>(42.24));

      // pretend local_ac has been altered by the engine ...
      // put the expected values into the top left hand corner of a n1_a x n2_a matrix
      // (as this is how the engine will be returning them - we trash the bottom right
      // part with -999 so we can easily see anything incorrectly being set)
      std::vector<RT> engine_results =
        ut::top_left<sorder, RT>(expected_results.data(), n1_b, n2_b, n3_b,
                                 n1_a, n2_a, n3_a, -999);

      // copy the expected results into RawData
      for (size_t p = 0; p < (n1_a * n2_a * n3_a); ++p) {
        local_ac.data[p] = engine_results[p];
      }
      // ... pretend local_ac has been altered by the engine

      // copy back from RawData to users type, resizing as we go
      local_ac.copy_back(*ac_a, n1_b, n2_b, n3_b);

      // compare values
      auto max_diff = test_setup<sorder, RT, inout, AC, type_is>::max_abs_diff(
        *ac_a, expected_results, n1_b, n2_b, n3_b);
      ASSERT_EQUAL(max_diff, 0);

      // check the size
      types::f77_integer isorder =
        data_handling::get_storage_order(true, local_ac);
      bool local_storage_order = data_handling::set_is_col_major(isorder);
      bool meta_info_ok;
      if (ut::has_resize<inout, type_is>::value) {
        meta_info_ok =
          test_setup<sorder, RT, inout, AC, type_is>::check_meta_info(
            *ac_a, local_storage_order, n1_b, n2_b, n3_b);
      } else {
        meta_info_ok =
          test_setup<sorder, RT, inout, AC, type_is>::check_meta_info(
            *ac_a, local_storage_order, n1_a, n2_a, n3_a);
      }
      ASSERT_TRUE(meta_info_ok);
    }
  }
};
// clang-format off
REGISTER_TEST(test_copy_back_method_array_preallocated, "Test method to copy data back into array container (pre-allocated)");
// clang-format on

//************************************************
struct test_copy_back_method_array_not_preallocated : public TestCase {
  DEFINE_RUN_METHOD_WRAPPERS

  template <enum ut::SORDER sorder, typename RT,
            enum data_handling::INOUT inout, typename AC,
            enum ut::TYPE_IS type_is = ut::GENERAL>
  auto run_this(std::string label = "") ->
    typename std::enable_if<!ut::has_resize<inout, type_is>::value,
                            void>::type {
    // copyback should never be called on an input array or an internal array
  }

  template <enum ut::SORDER sorder, typename RT,
            enum data_handling::INOUT inout, typename AC,
            enum ut::TYPE_IS type_is = ut::GENERAL>
  auto run_this(std::string label = "") ->
    typename std::enable_if<ut::has_resize<inout, type_is>::value, void>::type {
    using RD = data_handling::RawData<RT, inout, AC>;
    SUB_TITLE(label);
    nagcpp::error_handler::ErrorHandler eh;
    {
      SUB_TEST("copy_back with no resize");
      static const size_t n1_a = 4;
      static const size_t n2_a = 5;
      static const size_t n3_a = 8;
      std::unique_ptr<AC> ac_a =
        test_setup<sorder, RT, inout, AC, type_is>::get_test_data(0, 0, 0);
      RD local_ac(*ac_a);

      ASSERT_CPOINTER_IS_NULL(local_ac.data);

      // run the resize method directly on local_ac
      local_ac.resize(*ac_a, n1_a, n2_a, n3_a);

      ASSERT_CPOINTER_IS_NOT_NULL(local_ac.data);
      ASSERT_THROWS_NOTHING(local_ac.check(
        eh, "VAR1_1", true, ut::sorder_flag<sorder>(), n1_a, n2_a, n3_a));

      // get a set of expected results, different from those used in test_setup
      std::vector<RT> expected_results =
        ut::get_expected_values<sorder, RT>(n1_a, n2_a, n3_a);

      // copy the expected results into RawData
      for (size_t p = 0; p < (n1_a * n2_a * n3_a); ++p) {
        local_ac.data[p] = expected_results[p];
      }
      // copy back from RawData to users type
      local_ac.copy_back(*ac_a);

      // compare values
      auto max_diff = test_setup<sorder, RT, inout, AC, type_is>::max_abs_diff(
        *ac_a, expected_results, n1_a, n2_a, n3_a);
      ASSERT_EQUAL(max_diff, 0);

      // check the size
      types::f77_integer isorder =
        data_handling::get_storage_order(true, local_ac);
      bool local_storage_order = data_handling::set_is_col_major(isorder);
      bool meta_info_ok =
        test_setup<sorder, RT, inout, AC, type_is>::check_meta_info(
          *ac_a, local_storage_order, n1_a, n2_a, n3_a);
      ASSERT_TRUE(meta_info_ok);
    }
    {
      SUB_TEST("resize container to smaller and copy back");
      static const size_t n1_a = 8;
      static const size_t n2_a = 4;
      static const size_t n3_a = 11;
      std::unique_ptr<AC> ac_a =
        test_setup<sorder, RT, inout, AC, type_is>::get_test_data(0, 0, 0);

      data_handling::RawData<RT, inout, AC> local_ac(*ac_a);

      ASSERT_CPOINTER_IS_NULL(local_ac.data);

      // run the resize method directly on local_ac
      local_ac.resize(*ac_a, n1_a, n2_a, n3_a);
      ASSERT_THROWS_NOTHING(local_ac.check(
        eh, "VAR1_2", true, ut::sorder_flag<sorder>(), n1_a, n2_a, n3_a));

      // get a set of expected results, different from those used in test_setup
      static const size_t n1_b = 5;
      static const size_t n2_b = 3;
      static const size_t n3_b = 8;
      std::vector<RT> expected_results =
        ut::get_expected_values<sorder, RT>(n1_b, n2_b, n3_b);

      // pretend local_ac has been altered by the engine ...
      // put the expected values into the top left hand corner of a n1_a x n2_a x n3_a
      // matrix (as this is how the engine will be returning them - we trash the bottom
      // right part with -999 so we can easily see anything incorrectly being set)
      std::vector<RT> engine_results =
        ut::top_left<sorder, RT>(expected_results.data(), n1_b, n2_b, n3_b,
                                 n1_a, n2_a, n3_a, -999);

      // copy the expected results into RawData
      for (size_t p = 0; p < (n1_a * n2_a * n3_a); ++p) {
        local_ac.data[p] = engine_results[p];
      }
      // ... pretend local_ac has been altered by the engine

      // copy back from RawData to users type, resizing as we go
      local_ac.copy_back(*ac_a, n1_b, n2_b, n3_b);

      // compare values
      auto max_diff = test_setup<sorder, RT, inout, AC, type_is>::max_abs_diff(
        *ac_a, expected_results, n1_b, n2_b, n3_b);
      ASSERT_EQUAL(max_diff, 0);

      // check the size
      types::f77_integer isorder =
        data_handling::get_storage_order(true, local_ac);
      bool local_storage_order = data_handling::set_is_col_major(isorder);
      bool meta_info_ok =
        test_setup<sorder, RT, inout, AC, type_is>::check_meta_info(
          *ac_a, local_storage_order, n1_b, n2_b, n3_b);
      ASSERT_TRUE(meta_info_ok);
    }
  }
};
// clang-format off
REGISTER_TEST(test_copy_back_method_array_not_preallocated, "Test method to copy data back into array container (not pre-allocated)");
// clang-format on
// ... tests related to using the type as an argument to a NAG routine

template <enum ut::SORDER sorder, typename RT, enum data_handling::INOUT inout,
          typename AC, enum ut::TYPE_IS type_is = ut::GENERAL>
void pseudo_helper_in(const RT *x, const size_t n1_a, const size_t n2_a,
                      const size_t n3_a, bool &meta_info_ok, RT &max_diff) {
  // pack raw data into utility::array3D
  utility::array3D<RT, data_handling::INOUT::IN> local_x(
    x, n1_a, n2_a, n3_a, ut::is_col_major<sorder>::value);

  // convert utility::array3D into the users type
  auto user_x = data_handling::convert_nag_array_to_user<
    const utility::array3D<RT, data_handling::INOUT::IN>, inout, AC>(local_x);

  // simulate calling a callback with X as an input argument ...
  // check that the users type has the correct meta information
  meta_info_ok = test_setup<sorder, RT, inout, AC, type_is>::check_meta_info(
    user_x.get(), local_x.is_col_major(), n1_a, n2_a, n3_a);

  // check that the values in the users type are correct
  std::vector<RT> ex(x, x + (n1_a * n2_a * n3_a));
  max_diff =
    test_setup<sorder, RT, inout, AC, type_is>::max_abs_diff(user_x.get(), ex,
                                                             n1_a, n2_a, n3_a);
  // ... simulate calling a callback with X as an input argument
}

template <enum ut::SORDER sorder, typename RT, enum data_handling::INOUT inout,
          typename AC, enum ut::TYPE_IS type_is = ut::GENERAL>
void pseudo_helper_out(RT *x, const size_t n1_a, const size_t n2_a,
                       const size_t n3_a, bool &meta_info_ok) {
  // pack raw data into utility::array3D
  utility::array3D<RT, data_handling::INOUT::OUT> local_x(
    x, n1_a, n2_a, n3_a, ut::is_col_major<sorder>::value);

  // convert utility::array3D into the users type
  auto user_x = data_handling::convert_nag_array_to_user<
    utility::array3D<RT, data_handling::INOUT::OUT>, inout, AC>(local_x);

  // simulate calling a callback with X as an output argument ...
  // check that the users type has the correct meta information
  meta_info_ok = test_setup<sorder, RT, inout, AC, type_is>::check_meta_info(
    user_x.get(), local_x.is_col_major(), n1_a, n2_a, n3_a);

  // populate the users type
  test_setup<sorder, RT, inout, AC, type_is>::set_values(user_x.get());
  // ... simulate calling a callback with X as an output argument
}

template <enum ut::SORDER sorder, typename RT, enum data_handling::INOUT inout,
          typename AC, enum ut::TYPE_IS type_is = ut::GENERAL>
void pseudo_helper_inout(RT *x, const size_t n1_a, const size_t n2_a,
                         const size_t n3_a, bool &meta_info_ok, RT &max_diff) {
  // pack raw data into utility::array3D
  utility::array3D<RT, data_handling::INOUT::INOUT> local_x(
    x, n1_a, n2_a, n3_a, ut::is_col_major<sorder>::value);

  // convert utility::array3D into the users type
  auto user_x = data_handling::convert_nag_array_to_user<
    utility::array3D<RT, data_handling::INOUT::INOUT>, inout, AC>(local_x);

  // simulate calling a callback with X as an input / output argument ...
  // check that the users type has the correct meta information
  meta_info_ok = test_setup<sorder, RT, inout, AC, type_is>::check_meta_info(
    user_x.get(), local_x.is_col_major(), n1_a, n2_a, n3_a);

  // check that the values in the users type are correct
  std::vector<RT> ex(x, x + (n1_a * n2_a * n3_a));
  max_diff =
    test_setup<sorder, RT, inout, AC, type_is>::max_abs_diff(user_x.get(), ex,
                                                             n1_a, n2_a, n3_a);

  // populate the users type
  test_setup<sorder, RT, inout, AC, type_is>::set_values(user_x.get());
  // ... simulate calling a callback with X as an input / output argument
}

//******************************************************************************
//******************************************************************************

// tests related to using the type as an argument to a NAG callback function ...
//************************************************
struct test_convert_nag_array_to_user : public TestCase {
  DEFINE_RUN_METHOD_CALLBACKS

  template <enum ut::SORDER sorder, typename RT,
            enum data_handling::INOUT inout, typename AC,
            enum ut::TYPE_IS type_is = ut::GENERAL>
  auto run_this(std::string label = "") ->
    typename std::enable_if<data_handling::is_in<inout>::value, void>::type {
    SUB_TITLE(label);
    static const size_t n1_a = 3;
    static const size_t n2_a = 4;
    static const size_t n3_a = 4;
    std::vector<RT> raw_data =
      ut::get_expected_values<sorder, RT>(n1_a, n2_a, n3_a, static_cast<RT>(132.12));
    RT max_diff;
    bool meta_info_ok;
    pseudo_helper_in<sorder, RT, inout, AC>(raw_data.data(), n1_a, n2_a, n3_a,
                                            meta_info_ok, max_diff);
    {
      SUB_TEST("check data passed to user type");
      ASSERT_TRUE(meta_info_ok);
      ASSERT_EQUAL(max_diff, 0);
    }
  }

  template <enum ut::SORDER sorder, typename RT,
            enum data_handling::INOUT inout, typename AC,
            enum ut::TYPE_IS type_is = ut::GENERAL>
  auto run_this(std::string label = "") ->
    typename std::enable_if<data_handling::is_out<inout>::value, void>::type {
    SUB_TITLE(label);
    static const size_t n1_a = 5;
    static const size_t n2_a = 6;
    static const size_t n3_a = 3;
    std::vector<RT> raw_data((n1_a * n2_a * n3_a), -999);
    bool meta_info_ok;
    pseudo_helper_out<sorder, RT, inout, AC>(raw_data.data(), n1_a, n2_a, n3_a,
                                             meta_info_ok);
    {
      SUB_TEST("check data passed to user type");
      ASSERT_TRUE(meta_info_ok);
    }
    {
      SUB_TEST("check user type updates data");
      double eps = machine::precision() * 100.0;
      std::vector<RT> expected_results =
        ut::get_expected_values<sorder, RT>(n1_a, n2_a, n3_a);
      ASSERT_ARRAY_ALMOST_EQUAL((n1_a * n2_a * n3_a), raw_data, expected_results, eps);
    }
  }

  template <enum ut::SORDER sorder, typename RT,
            enum data_handling::INOUT inout, typename AC,
            enum ut::TYPE_IS type_is = ut::GENERAL>
  auto run_this(std::string label = "") ->
    typename std::enable_if<data_handling::is_inout<inout>::value, void>::type {
    SUB_TITLE(label);
    static const size_t n1_a = 5;
    static const size_t n2_a = 3;
    static const size_t n3_a = 2;
    std::vector<RT> raw_data =
      ut::get_expected_values<sorder, RT>(n1_a, n2_a, n3_a, static_cast<RT>(132.12));
    RT max_diff;
    bool meta_info_ok;
    pseudo_helper_inout<sorder, RT, inout, AC>(raw_data.data(), n1_a, n2_a,
                                               n3_a, meta_info_ok, max_diff);
    {
      SUB_TEST("check data passed to user type");
      ASSERT_TRUE(meta_info_ok);
      ASSERT_EQUAL(max_diff, 0);
    }
    {
      SUB_TEST("check user type updates data");
      std::vector<RT> expected_results =
        ut::get_expected_values<sorder, RT>(n1_a, n2_a, n3_a);
      ASSERT_ARRAY_FLOATS_EQUAL((n1_a * n2_a * n3_a), raw_data,
                                expected_results);
    }
  }
};
// clang-format off
REGISTER_TEST(test_convert_nag_array_to_user, "Test auto discovery and conversion of NAG array type to users type");
// clang-format on
// ... tests related to using the type as an argument to a NAG callback function
