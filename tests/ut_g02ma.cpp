#include "../examples/include/nag_my_matrix.hpp"
#include "g02/nagcpp_g02ma.hpp"
#include "include/cxxunit_testing.hpp"
#include "utility/nagcpp_data_handling_base.hpp"
#include "utility/nagcpp_utility_array.hpp"
#include "x02/nagcpp_x02aj.hpp"
#include <vector>

using namespace nagcpp;

struct test_simple_example : public TestCase {
  void run() override {
    // this is the Fortran example
    const size_t n = 20;
    const size_t m = 6;
    // clang-format off
    std::vector<double> rd_rm = {
                                 10.28,  1.77,  9.69, 15.58,  8.23, 10.44,
                                  9.08,  8.99, 11.53,  6.57, 15.89, 12.58,
                                 17.98, 13.10,  1.04, 10.45, 10.12, 16.68,
                                 14.82, 13.79, 12.23,  7.00,  8.14,  7.79,
                                 17.53,  9.41,  6.24,  3.75, 13.12, 17.08,
                                  7.78, 10.38,  9.83,  2.58, 10.13,  4.25,
                                 11.95, 21.71,  8.83, 11.00, 12.59, 10.52,
                                 14.60, 10.09, -2.70,  9.89, 14.67,  6.49,
                                  3.63,  9.07, 12.59, 14.09,  9.06,  8.19,
                                  6.35,  9.79,  9.40, 12.79,  8.38, 16.79,
                                  4.66,  3.55, 16.82, 13.83, 21.39, 13.88,
                                  8.32, 14.04, 17.17,  7.93,  7.39, -1.09,
                                 10.86, 13.68,  5.75, 10.44, 10.36, 10.06,
                                  4.76,  4.92, 17.83,  2.90,  7.58, 11.97,
                                  5.05, 10.41,  9.89,  9.04,  7.90, 13.12,
                                  5.41,  9.32,  5.27, 15.53,  5.06, 19.84,
                                  9.77,  2.37,  9.54, 20.23,  9.33,  8.82,
                                 14.28,  4.34, 14.23, 14.95, 18.16, 11.03,
                                 10.17,  6.80,  3.17,  8.57, 16.07, 15.93,
                                  5.39,  2.67,  6.37, 13.56, 10.68,  7.35
    };
    // clang-format on
    std::vector<double> y = {-46.47, -35.80, -129.22, -42.44,  -73.51,
                             -26.61, -63.90, -76.73,  -32.64,  -83.29,
                             -16.31, -5.82,  -47.75,  18.38,   -54.71,
                             -55.62, -45.28, -22.76,  -104.32, -55.94};

    nagcpp::correg::OptionalG02MA opt_cm;
    {
      SUB_TEST("check simple optional arguments can be queried");
      ASSERT_EQUAL(opt_cm.get_pred(), 3);
      ASSERT_EQUAL(opt_cm.get_prey(), 1);
    }
    {
      SUB_TEST("check querying complex optional argument causes an error");
      ASSERT_THROWS(error_handler::ErrorException, opt_cm.get_mnstep());
      if (last_assert_passed) {
        try {
          opt_cm.get_mnstep();
        } catch (error_handler::Exception &e) {
          ASSERT_EQUAL(e.errorid, 10606);
          ASSERT_HAS_KEYWORD(e.msg, "mnstep");
          ASSERT_HAS_KEYWORD(e.msg, "not yet available");
        }
      }
    }

    // call the routine in the same way as in the example (data / results in
    // column major order)
    nagcpp::types::f77_integer mtype = 1;

    // NB: MyMatrix takes the data in, in row major order, even though it internally stores
    // it in column major
    MyMatrix<double> d_cm(n, m, rd_rm);
    nagcpp::types::f77_integer ip_cm, nstep_cm;
    MyMatrix<double> b_cm, fitsum_cm;
    ASSERT_THROWS_NOTHING(nagcpp::correg::lars(
      mtype, d_cm, nullptr, y, ip_cm, nstep_cm, b_cm, fitsum_cm, opt_cm));

    double eps = 100.0 * machine::precision();
    {
      SUB_TEST("check against hardcoded expected values");
      ASSERT_EQUAL(nstep_cm, 6);
      ASSERT_EQUAL(ip_cm, 6);
      ASSERT_EQUAL(b_cm.size1(), static_cast<size_t>(ip_cm));
      ASSERT_EQUAL(b_cm.size2(), static_cast<size_t>(nstep_cm + 2));
      ASSERT_EQUAL(fitsum_cm.size1(), static_cast<size_t>(6));
      ASSERT_EQUAL(fitsum_cm.size2(), static_cast<size_t>(nstep_cm + 1));

      // clang-format off
      // expected results obtained from running this routine
      std::vector<double> eb = {0.0,0.0,3.124749655743967e+00,0.0,0.0,0.0,0.0,0.0,
                                3.791985493676526e+00,0.0,0.0,-7.127547042909556e-01,
                                -4.464195900504550e-01,0.0,3.997522610076478e+00,0.0,0.0,
                                -1.150509374817377e+00,-6.278634798573695e-01,-2.952286679905289e-01,
                                4.097864963393758e+00,0.0,0.0,-1.466475103905966e+00,
                                -1.059572890076814e+00,-1.056375927998576e+00,4.110272441317219e+00,
                                -8.637123421096782e-01,0.0,-1.947919546243262e+00,-1.073487223402365e+00,
                                -1.131599903079558e+00,4.118283956913130e+00,-9.346938526665269e-01,
                                -5.884088357527006e-02,-1.981328464424616e+00,5.195941397728943e-02,
                                4.643466389031658e-02,4.313234373922156e-02,4.932770179401318e-02,
                                5.510183220832197e-02,4.607483465288929e-02,9.6335e+00,9.01,9.236e+00,
                                1.0534e+01,1.12125e+01,1.1086e+01};
      std::vector<double> efitsum = {7.244562629464849e+01,8.929855426181415e+03,2.0,1.335542814423161e+01,
                                     1.232265112211567e+02,7.244562629464849e+01,1.033846284488867e+02,
                                     6.404701131607857e+03,3.0,7.054399526218461e+00,5.078088492650819e+01,
                                     2.484080356383739e+01,1.262425423292193e+02,5.258246832794257e+03,4.0,
                                     5.285619945443155e+00,3.083630110893903e+01,1.622506491385065e+01,
                                     1.452765573642452e+02,4.657051080646879e+03,5.0,5.309287982549730e+00,
                                     1.931938259936432e+01,1.158684968315624e+01,1.982234626936995e+02,
                                     3.959401226588743e+03,6.0,5.015879054495576e+00,1.226595297177365e+01,
                                     2.452016817817405e+01,2.035289307859593e+02,3.954570853812258e+03,7.0,
                                     7.0,9.104517626884195e-01,2.197810905534213e+00,-5.0037e+01,2.153593022e+04,
                                     1.0,5.279582164777955e+01,3.041977579855583e+02,1.0015e+03};
      // clang-format on
      ASSERT_ARRAY_ALMOST_EQUAL(eb.size(), eb, b_cm.data(), eps);
      ASSERT_ARRAY_ALMOST_EQUAL(efitsum.size(), efitsum, fitsum_cm.data(), eps);
    }

    // sanity check that everything is in column major order
    ASSERT_TRUE(d_cm.is_col_major());
    ASSERT_TRUE(b_cm.is_col_major());
    ASSERT_TRUE(fitsum_cm.is_col_major());

    {
      SUB_TEST("check that we can now query complicated optional arguments");
      nagcpp::types::f77_integer emntype = (mtype == 1) ? m : 200 * m;
      ASSERT_EQUAL(opt_cm.get_mnstep(), emntype);
    }

    // because we are preallocating the arrays to the correct size, we need
    // to set MNSTEP
    nagcpp::correg::OptionalG02MA opt_rm;
    opt_rm.mnstep(nstep_cm);

    {
      SUB_TEST("check that we can query a complicated optional argument if we "
               "have set it");
      ASSERT_EQUAL(opt_rm.get_mnstep(), nstep_cm);
    }

    utility::array2D<double, data_handling::INOUT::IN> d_rm(rd_rm.data(), n, m,
                                                            false);

    // preallocate some more output arrays
    std::vector<double> ib_rm((nstep_cm + 2) * ip_cm);
    utility::array2D<double, data_handling::INOUT::OUT> b_rm(
      ib_rm.data(), ip_cm, nstep_cm + 2, false);
    std::vector<double> ifitsum_rm((nstep_cm + 1) * 6);
    utility::array2D<double, data_handling::INOUT::OUT> fitsum_rm(
      ifitsum_rm.data(), 6, nstep_cm + 1, false);
    nagcpp::types::f77_integer ip_rm, nstep_rm;

    // call the routine with everything in row major order
    ASSERT_THROWS_NOTHING(nagcpp::correg::lars(
      mtype, d_rm, nullptr, y, ip_rm, nstep_rm, b_rm, fitsum_rm, opt_cm));

    // sanity check that everything is in row major order
    ASSERT_FALSE(d_rm.is_col_major());
    ASSERT_FALSE(b_rm.is_col_major());
    ASSERT_FALSE(fitsum_rm.is_col_major());

    {
      SUB_TEST("check that row major order and col major order give the same "
               "results");
      ASSERT_EQUAL(nstep_cm, nstep_rm);
      ASSERT_EQUAL(ip_cm, ip_rm);

      // NB: array2D stores sizes as types::f77_integer (as they are usually going into
      // out from the engine), MyMatrix stores them as the more intuitive size_t
      ASSERT_EQUAL(b_cm.size1(), static_cast<size_t>(b_rm.size1()));
      ASSERT_EQUAL(b_cm.size2(), static_cast<size_t>(b_rm.size2()));
      ASSERT_2DARRAY_ALMOST_EQUAL_ROW_VS_COL(b_cm.size1(), b_cm.size2(),
                                             b_rm.data(), b_cm.data(), eps);

      ASSERT_EQUAL(fitsum_cm.size1(), static_cast<size_t>(fitsum_rm.size1()));
      ASSERT_EQUAL(fitsum_cm.size2(), static_cast<size_t>(fitsum_rm.size2()));
      ASSERT_2DARRAY_ALMOST_EQUAL_ROW_VS_COL(fitsum_cm.size1(),
                                             fitsum_cm.size2(),
                                             fitsum_rm.data(), fitsum_cm.data(),
                                             eps);
    }

    {
      SUB_TEST("check that a complicated optional argument we have set is not "
               "changed by the routine");
      ASSERT_EQUAL(opt_rm.get_mnstep(), nstep_cm);
    }
  }
};
// clang-format off
REGISTER_TEST(test_simple_example, "Test simple example (vs hardcoded and row vs column order)");
// clang-format on
