#ifndef NAGCPP_UT_BOOST_TEST_SETUP
#define NAGCPP_UT_BOOST_TEST_SETUP

#ifdef HAVE_BOOST_MATRIX
// boost types to run through tests in ut_data_handling_2D.cpp ...
// clang-format off
#define BOOST_2D_TYPES_TO_TEST_WRAPPERS \
run_this<ut::SORDER::COL_MAJOR, double, data_handling::INOUT::IN, boost::numeric::ublas::matrix<double, boost::numeric::ublas::column_major>>("boost matrix, double, COL_MAJOR, IN"); \
run_this<ut::SORDER::COL_MAJOR, double, data_handling::INOUT::OUT, boost::numeric::ublas::matrix<double, boost::numeric::ublas::column_major>>("boost matrix, double, COL_MAJOR, OUT"); \
run_this<ut::SORDER::COL_MAJOR, double, data_handling::INOUT::INOUT, boost::numeric::ublas::matrix<double, boost::numeric::ublas::column_major>>("boost matrix, double, COL_MAJOR, INOUT"); \
run_this<ut::SORDER::ROW_MAJOR, double, data_handling::INOUT::IN, boost::numeric::ublas::matrix<double, boost::numeric::ublas::row_major>>("boost matrix, double, ROW_MAJOR, IN"); \
run_this<ut::SORDER::ROW_MAJOR, double, data_handling::INOUT::OUT, boost::numeric::ublas::matrix<double, boost::numeric::ublas::row_major>>("boost matrix, double, ROW_MAJOR, OUT"); \
run_this<ut::SORDER::ROW_MAJOR, double, data_handling::INOUT::INOUT, boost::numeric::ublas::matrix<double, boost::numeric::ublas::row_major>>("boost matrix, double, ROW_MAJOR, INOUT"); \
run_this<ut::SORDER::COL_MAJOR, types::f77_integer, data_handling::INOUT::IN, boost::numeric::ublas::matrix<types::f77_integer, boost::numeric::ublas::column_major>>("boost matrix, f77_integer, COL_MAJOR, IN"); \
run_this<ut::SORDER::COL_MAJOR, types::f77_integer, data_handling::INOUT::OUT, boost::numeric::ublas::matrix<types::f77_integer, boost::numeric::ublas::column_major>>("boost matrix, f77_integer, COL_MAJOR, OUT"); \
run_this<ut::SORDER::COL_MAJOR, types::f77_integer, data_handling::INOUT::INOUT, boost::numeric::ublas::matrix<types::f77_integer, boost::numeric::ublas::column_major>>("boost matrix, f77_integer, COL_MAJOR, INOUT"); \
run_this<ut::SORDER::ROW_MAJOR, types::f77_integer, data_handling::INOUT::IN, boost::numeric::ublas::matrix<types::f77_integer, boost::numeric::ublas::row_major>>("boost matrix, f77_integer, ROW_MAJOR, IN"); \
run_this<ut::SORDER::ROW_MAJOR, types::f77_integer, data_handling::INOUT::OUT, boost::numeric::ublas::matrix<types::f77_integer, boost::numeric::ublas::row_major>>("boost matrix, f77_integer, ROW_MAJOR, OUT"); \
run_this<ut::SORDER::ROW_MAJOR, types::f77_integer, data_handling::INOUT::INOUT, boost::numeric::ublas::matrix<types::f77_integer, boost::numeric::ublas::row_major>>("boost matrix, f77_integer, ROW_MAJOR, INOUT");

#define BOOST_2D_TYPES_TO_TEST_CALLBACKS \
  BOOST_2D_TYPES_TO_TEST_WRAPPERS
// clang-format on
// ... boost types to run through tests in ut_data_handling_2D.cpp

// structure to allow tests to be run on a boost matrix ...
template <enum ut::SORDER sorder, typename RT, enum data_handling::INOUT inout,
          typename MRT, typename MSO, ut::TYPE_IS type_is>
struct test_setup<sorder, RT, inout, boost::numeric::ublas::matrix<MRT, MSO>,
                  type_is> {
  using AC = boost::numeric::ublas::matrix<MRT, MSO>;
  static std::unique_ptr<AC> get_test_data(const size_t n1, const size_t n2) {
    if (n1 > 0 && n2 > 0) {
      // return a populated array of the stated size
      std::unique_ptr<AC> ac = std::unique_ptr<AC>(new AC(n1, n2));
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
    test_setup_utilities::set_expected_results<sorder, RT, AC>(ac, ac.size1(),
                                                               ac.size2());
  }
  static RT max_abs_diff(const AC &observed, const std::vector<RT> &expected,
                         const size_t n1, const size_t n2) {
    // return maximum absolute difference between observed and expected
    return test_setup_utilities::get_max_abs_diff<sorder, RT, AC>(observed,
                                                                  expected, n1,
                                                                  n2);
  }
  static bool check_meta_info(const AC &ac, const bool is_col_major,
                              const size_t n1, const size_t n2) {
    auto ndims = 2;
    auto size1 = ac.size1();
    auto size2 = ac.size2();
    bool stored_in_col_major = this_is_col_major(ac);
    return (
      static_cast<size_t>(ndims) == 2 && stored_in_col_major == is_col_major &&
      static_cast<size_t>(size1) == n1 && static_cast<size_t>(size2) == n2);
  }

private:
  inline static bool this_is_col_major(
    const boost::numeric::ublas::matrix<
      MRT, boost::numeric::ublas::column_major> &array_container) {
    return true;
  }
  inline static bool this_is_col_major(
    const boost::numeric::ublas::matrix<MRT, boost::numeric::ublas::row_major>
      &array_container) {
    return false;
  }
};
// ... structure to allow tests to be run on a boost matrix
#else

#define BOOST_2D_TYPES_TO_TEST_WRAPPERS
#define BOOST_2D_TYPES_TO_TEST_CALLBACKS
#endif

#endif
