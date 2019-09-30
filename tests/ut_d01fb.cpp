#include "d01/nagcpp_d01fb.hpp"
#include "d01/nagcpp_d01tb.hpp"
#include "include/cxxunit_testing.hpp"
#include "utility/nagcpp_error_handler.hpp"
#include <vector>

using namespace nagcpp;

namespace example {
  // values used in the function
  double p1 = 6;
  double p2 = 8;

  // number of points per dimension
  std::vector<types::f77_integer> nptvec = {4, 4, 4, 4};

  // expected results ...
  // obtained by running this routine (mdint checked vs Fortran example)
  double mdint = 2.506470386732622e-01;
  std::vector<double> weight = {1.739274225687269e-01, 3.260725774312730e-01,
                                3.260725774312730e-01, 1.739274225687269e-01,
                                4.163695619189446e-01, 1.024051219227148e+00,
                                1.815573152910759e+00, 3.243572542203831e+00,
                                1.753944171790684e+00, 1.499016147343850e+00,
                                1.499016147343850e+00, 1.753944171790684e+00,
                                6.025497939505366e-01, 2.179205635439835e+00,
                                8.982199653682851e+00, 1.082360449169268e+02};
  std::vector<double> abscis = {1.930568155797026e+00,  1.669990521792428e+00,
                                1.330009478207572e+00,  1.069431844202974e+00,
                                1.612738448096961e-01,  8.728805505791732e-01,
                                2.268310148460564e+00,  4.697535456150566e+00,
                                2.334414218338977e+00,  7.419637843027258e-01,
                                -7.419637843027258e-01, -2.334414218338977e+00,
                                1.223836944463802e+00,  2.477675284083257e+00,
                                7.090647990761759e+00,  4.120783978069118e+01};
  // ... expected results
}

template <typename X>
double f_base(const X &x, const double p1, const double p2) {
  return pow(x[0] * x[1] * x[2], p1) / pow(x[3] + 2, p2) *
         exp(-2 * x[1] - 0.5 * x[2] * x[2]);
}

template <typename X>
double f_base(const X &x) {
  return f_base(x, example::p1, example::p2);
}

double f(const std::vector<double> &x) { return f_base(x); }

struct test_simple_example : public TestCase {
  void run() override {
    // this is the Fortran example

    // preallocate the arrays for the combined weights and abscis
    size_t lwa = 0;
    for (auto n : example::nptvec)
      lwa += n;
    std::vector<double> weight(lwa);
    std::vector<double> abscis(lwa);

    // calculate some weights and abscis ...
    std::vector<types::f77_integer> key = {0, -3, -4, -5};
    std::vector<double> a = {1.0, 0.0, 0.0, 1.0};
    std::vector<double> b = {2.0, 2.0, 0.5, 2.0};

    // loop over dimension
    size_t k = 0;
    for (auto i = 0u; i < example::nptvec.size(); ++i) {
      std::vector<double> this_weight;
      std::vector<double> this_abscis;
      quad::dim1_gauss_wres(key[i], a[i], b[i], example::nptvec[i], this_weight,
                            this_abscis);

      // concatenate the weights and abscis
      for (auto j = 0; j < example::nptvec[i]; ++j, ++k) {
        weight[k] = this_weight[j];
        abscis[k] = this_abscis[j];
      }
    }
    // ... calculate some weights and abscis

    // approximate the integral of f
    double mdint;
    mdint = quad::md_gauss(example::nptvec, weight, abscis, f);

    ASSERT_FLOATS_EQUAL(mdint, example::mdint);
    ASSERT_EQUAL(weight.size(), example::weight.size());
    if (last_assert_passed) {
      ASSERT_ARRAY_FLOATS_EQUAL(weight.size(), weight, example::weight);
    }
    ASSERT_EQUAL(abscis.size(), example::abscis.size());
    if (last_assert_passed) {
      ASSERT_ARRAY_FLOATS_EQUAL(abscis.size(), abscis, example::abscis);
    }
  }
};
// clang-format off
REGISTER_TEST(test_simple_example, "Test simple example");
// clang-format on

// NAG defined type as its arguments ...
// C like function
double clike_arr(const utility::array1D<double, data_handling::IN> &x) {
  return f_base(x);
}
// C++ std::function
std::function<double(const utility::array1D<double, data_handling::IN> &x)>
  function_arr = [](const utility::array1D<double, data_handling::IN> &x) {
    return f_base(x);
  };
// functor
struct functor_arr {
  double operator()(const utility::array1D<double, data_handling::IN> &x) {
    return f_base(x);
  }
};
// lambda function
auto lambda_arr = [](const utility::array1D<double, data_handling::IN> &x) {
  return f_base(x);
};
// functor with data
class functor_data_arr {
private:
  double p1, p2;

public:
  functor_data_arr() : p1(0), p2(0) {}
  functor_data_arr(double p1_, double p2_) : p1(p1_), p2(p2_) {}
  double operator()(const utility::array1D<double, data_handling::IN> &x) {
    return f_base(x, p1, p2);
  }
};
// ... NAG defined type as its arguments

// function using std::vector as its arguments ...
// C like function
double clike_std(const std::vector<double> &x) { return f_base(x); }
// C++ std::function
std::function<double(const std::vector<double> &x)> function_std =
  [](const std::vector<double> &x) { return f_base(x); };
// functor
struct functor_std {
  double operator()(const std::vector<double> &x) { return f_base(x); }
};
// lambda function
auto lambda_std = [](const std::vector<double> &x) { return f_base(x); };
// functor with data ...
// in this case we pass <class name>(<constructor arguments>) through as "f"
class functor_data_std {
private:
  double p1, p2;

public:
  functor_data_std() : p1(0), p2(0) {}
  functor_data_std(double p1_, double p2_) : p1(p1_), p2(p2_) {}
  double operator()(const std::vector<double> &x) { return f_base(x, p1, p2); }
};
// ... functor with data
// ... function using std::vector as its arguments

struct test_different_calling_types : public TestCase {
  void run() override {
    {
      SUB_TITLE("std::vector as input arguments");
      double mdint_clike = quad::md_gauss(example::nptvec, example::weight,
                                          example::abscis, clike_std);
      double mdint_function = quad::md_gauss(example::nptvec, example::weight,
                                             example::abscis, function_std);
      double mdint_functor = quad::md_gauss(example::nptvec, example::weight,
                                            example::abscis, functor_std());
      double mdint_lambda = quad::md_gauss(example::nptvec, example::weight,
                                           example::abscis, lambda_std);
      double mdint_functor_data =
        quad::md_gauss(example::nptvec, example::weight, example::abscis,
                       functor_data_std(example::p1, example::p2));
      double my_p1 = example::p1;
      double my_p2 = example::p2;
      auto lambda_data = [&](const std::vector<double> &x) {
        return f_base(x, my_p1, my_p2);
      };
      double mdint_lambda_data =
        quad::md_gauss(example::nptvec, example::weight, example::abscis,
                       lambda_data);
      ASSERT_FLOATS_EQUAL(mdint_clike, example::mdint);
      ASSERT_EQUAL(mdint_function, mdint_clike);
      ASSERT_EQUAL(mdint_functor, mdint_clike);
      ASSERT_EQUAL(mdint_lambda, mdint_clike);
      ASSERT_EQUAL(mdint_functor_data, mdint_clike);
      ASSERT_EQUAL(mdint_lambda_data, mdint_clike);
    }
    {
      SUB_TITLE("array1D as input arguments");
      utility::array1D<types::f77_integer, data_handling::IN> nptvec(
        example::nptvec.data(), example::nptvec.size());
      utility::array1D<double, data_handling::IN> weight(
        example::weight.data(), example::weight.size());
      utility::array1D<double, data_handling::IN> abscis(
        example::abscis.data(), example::abscis.size());
      double mdint_clike = quad::md_gauss(nptvec, weight, abscis, clike_arr);
      double mdint_function =
        quad::md_gauss(nptvec, weight, abscis, function_arr);
      double mdint_functor =
        quad::md_gauss(nptvec, weight, abscis, functor_arr());
      double mdint_lambda = quad::md_gauss(nptvec, weight, abscis, lambda_arr);
      double mdint_functor_data =
        quad::md_gauss(nptvec, weight, abscis,
                       functor_data_arr(example::p1, example::p2));
      double my_p1 = example::p1;
      double my_p2 = example::p2;
      auto lambda_data =
        [&](const utility::array1D<double, data_handling::IN> &x) {
          return f_base(x, my_p1, my_p2);
        };
      double mdint_lambda_data =
        quad::md_gauss(nptvec, weight, abscis, lambda_data);

      ASSERT_FLOATS_EQUAL(mdint_clike, example::mdint);
      ASSERT_EQUAL(mdint_function, mdint_clike);
      ASSERT_EQUAL(mdint_functor, mdint_clike);
      ASSERT_EQUAL(mdint_lambda, mdint_clike);
      ASSERT_EQUAL(mdint_functor_data, mdint_clike);
      ASSERT_EQUAL(mdint_lambda_data, mdint_clike);
    }
    {
      SUB_TITLE("mix of array1D and std::vector as input arguments");
      utility::array1D<types::f77_integer, data_handling::IN> nptvec(
        example::nptvec.data(), example::nptvec.size());
      utility::array1D<double, data_handling::IN> weight(
        example::weight.data(), example::weight.size());
      utility::array1D<double, data_handling::IN> abscis(
        example::abscis.data(), example::abscis.size());
      double mdint_clike =
        quad::md_gauss(example::nptvec, weight, example::abscis, clike_std);
      double mdint_function =
        quad::md_gauss(example::nptvec, example::weight, abscis, function_arr);
      double mdint_functor =
        quad::md_gauss(nptvec, weight, example::abscis, functor_std());
      double mdint_lambda =
        quad::md_gauss(nptvec, weight, example::abscis, lambda_arr);
      double mdint_functor_data =
        quad::md_gauss(example::nptvec, weight, example::abscis,
                       functor_data_std(example::p1, example::p2));
      double my_p1 = example::p1;
      double my_p2 = example::p2;
      auto lambda_data = [&](const std::vector<double> &x) {
        return f_base(x, my_p1, my_p2);
      };
      double mdint_lambda_data =
        quad::md_gauss(nptvec, weight, abscis, lambda_data);

      ASSERT_FLOATS_EQUAL(mdint_clike, example::mdint);
      ASSERT_EQUAL(mdint_function, mdint_clike);
      ASSERT_EQUAL(mdint_functor, mdint_clike);
      ASSERT_EQUAL(mdint_lambda, mdint_clike);
      ASSERT_EQUAL(mdint_functor_data, mdint_clike);
      ASSERT_EQUAL(mdint_lambda_data, mdint_clike);
    }
  }
};
// clang-format off
REGISTER_TEST(test_different_calling_types, "Test different calling types");
// clang-format on

struct test_error_exits : TestCase {
  void run() override {
    {
      SUB_TITLE("weight and abscis different size");
      std::vector<double> weight(10, 1);
      std::vector<double> abscis(12, 1);
      ASSERT_THROWS(error_handler::ErrorException,
                    quad::md_gauss(example::nptvec, weight, abscis, f));
      quad::OptionalD01FB opt;
      opt.fail.error_handler_type =
        error_handler::ErrorHandlerType::ThrowNothing;
      ASSERT_THROWS_NOTHING(
        quad::md_gauss(example::nptvec, weight, abscis, f, opt));
      ASSERT_TRUE(opt.fail.error_thrown);
      ASSERT_HAS_KEYWORD(opt.fail.msg, "vector of size 10");
      ASSERT_HAS_KEYWORD(opt.fail.msg, "vector of size 12");
    }
    {
      SUB_TITLE("weight and abscis not consistent with nptvec (lwa too small)");
      std::vector<double> weight(15, 1);
      std::vector<double> abscis(15, 1);
      ASSERT_THROWS(error_handler::ErrorException,
                    quad::md_gauss(example::nptvec, weight, abscis, f));
      quad::OptionalD01FB opt;
      opt.fail.error_handler_type =
        error_handler::ErrorHandlerType::ThrowNothing;
      ASSERT_THROWS_NOTHING(
        quad::md_gauss(example::nptvec, weight, abscis, f, opt));
      ASSERT_TRUE(opt.fail.error_thrown);
      ASSERT_HAS_KEYWORD(opt.fail.msg, "lwa = 15");
      ASSERT_HAS_KEYWORD(opt.fail.msg, "dimension: 16");
    }
    {
      SUB_TITLE("ndim too large");
      std::vector<double> weight(30, 1);
      std::vector<double> abscis(30, 1);
      std::vector<types::f77_integer> nptvec(30, 1);
      ASSERT_THROWS(error_handler::ErrorException,
                    quad::md_gauss(nptvec, weight, abscis, f));
      quad::OptionalD01FB opt;
      opt.fail.error_handler_type =
        error_handler::ErrorHandlerType::ThrowNothing;
      ASSERT_THROWS_NOTHING(quad::md_gauss(nptvec, weight, abscis, f, opt));
      ASSERT_TRUE(opt.fail.error_thrown);
      ASSERT_HAS_KEYWORD(opt.fail.msg, "ndim = 30");
      ASSERT_HAS_KEYWORD(opt.fail.msg, "ndim <= 20");
    }
  }
};
// clang-format off
REGISTER_TEST(test_error_exits, "Test error exits");
// clang-format on
