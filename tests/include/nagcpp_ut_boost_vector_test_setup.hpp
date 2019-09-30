#ifndef NAGCPP_UT_BOOST_TEST_SETUP
#define NAGCPP_UT_BOOST_TEST_SETUP

#ifdef HAVE_BOOST_VECTOR
// boost types to run through tests in ut_data_handling_1D.cpp ...
// clang-format off
#define BOOST_1D_TYPES_TO_TEST_WRAPPERS \
run_this<double, data_handling::INOUT::IN, boost::numeric::ublas::vector<double>>("boost vector, double, IN"); \
run_this<double, data_handling::INOUT::OUT, boost::numeric::ublas::vector<double>>("boost vector, double, OUT"); \
run_this<double, data_handling::INOUT::INOUT, boost::numeric::ublas::vector<double>>("boost vector, double, INOUT"); \
run_this<double, data_handling::INOUT::IN, boost::numeric::ublas::vector<double>>("boost vector, double, IN"); \
run_this<double, data_handling::INOUT::OUT, boost::numeric::ublas::vector<double>>("boost vector, double, OUT"); \
run_this<double, data_handling::INOUT::INOUT, boost::numeric::ublas::vector<double>>("boost vector, double, INOUT"); \
run_this<types::f77_integer, data_handling::INOUT::IN, boost::numeric::ublas::vector<types::f77_integer>>("boost vector, f77_integer, IN"); \
run_this<types::f77_integer, data_handling::INOUT::OUT, boost::numeric::ublas::vector<types::f77_integer>>("boost vector, f77_integer, OUT"); \
run_this<types::f77_integer, data_handling::INOUT::INOUT, boost::numeric::ublas::vector<types::f77_integer>>("boost vector, f77_integer, INOUT"); \
run_this<types::f77_integer, data_handling::INOUT::IN, boost::numeric::ublas::vector<types::f77_integer>>("boost vector, f77_integer, IN"); \
run_this<types::f77_integer, data_handling::INOUT::OUT, boost::numeric::ublas::vector<types::f77_integer>>("boost vector, f77_integer, OUT"); \
run_this<types::f77_integer, data_handling::INOUT::INOUT, boost::numeric::ublas::vector<types::f77_integer>>("boost vector, f77_integer, INOUT");

#define BOOST_1D_TYPES_TO_TEST_CALLBACKS \
  BOOST_1D_TYPES_TO_TEST_WRAPPERS
// clang-format on
// ... boost types to run through tests in ut_data_handling_1D.cpp

// structure to allow tests to be run on a boost vector ...
template <typename RT, enum data_handling::INOUT inout, typename MRT,
          ut::TYPE_IS type_is>
struct test_setup<RT, inout, boost::numeric::ublas::vector<MRT>, type_is> {
  using AC = boost::numeric::ublas::vector<MRT>;
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
    test_setup_utilities::set_expected_results<RT, AC>(ac, ac.size());
  }
  static RT max_abs_diff(const AC &observed, const std::vector<RT> &expected,
                         const size_t n1) {
    // return maximum absolute difference between observed and expected
    return test_setup_utilities::get_max_abs_diff<RT, AC>(observed, expected,
                                                          n1);
  }
  static bool check_meta_info(const AC &ac, const size_t n1) {
    auto ndims = 1;
    auto size1 = ac.size();
    return (static_cast<size_t>(ndims) == 1 &&
            static_cast<size_t>(size1) == n1);
  }
};
// ... structure to allow tests to be run on a boost vector
#else

#define BOOST_1D_TYPES_TO_TEST_WRAPPERS
#define BOOST_1D_TYPES_TO_TEST_CALLBACKS
#endif

#endif
