/* Simple C++ testing library.
 * Copyright: 2014-2017, Dmitry Shachnev.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * original version taken from https://github.com/mitya57/cxxunit
 */

// clang-format off
/* Additional information:
   the bool variable last_assert_passed can be used within methods
   of the test structure and is true if the last assert performed
   passed (was true)
*/

/* Available asserts:
   ASSERT_MULTI_LINE_STRING_EQUAL(e1, e2)
   ASSERT_HAS_KEYWORD(line, keyword)
   ASSERT_NO_KEYWORD(line, keyword)
   ASSERT_TRUE(expression)
   ASSERT_TRUE_LABELLED(label,expression)
   ASSERT_FALSE(expression)
   ASSERT_RELATION(e1, rel, e2) (where rel is <=, >=, <, > etc etc)
   ASSERT_EQUAL(e1, e2)
   ASSERT_EQUAL_ONLY_COUNT_FAILURE(e1, e2) (as per ASSERT_EQUAL, but only reports failures)
   ASSERT_EQUAL_UNSIGNED(e1, e2)
   ASSERT_NOT_EQUAL(e1, e2)
   ASSERT_ARRAY_EQUAL(n, e1, e2)
   ASSERT_ARRAY_NOT_EQUAL(n, e1, e2)
   ASSERT_ALMOST_EQUAL(e1, e2, precision)
   ASSERT_ARRAY_ALMOST_EQUAL(n, e1, e2, precision)
   ASSERT_2DARRAY_ALMOST_EQUAL_ROW_VS_COL(n,m,erm,ecm,precision)
   ASSERT_STRINGS_EQUAL(e1, e2)
   ASSERT_STRINGS_NOT_EQUAL(e1, e2)
   ASSERT_NULL_TERMINATED_STRINGS_EQUAL(e1, e2)
   ASSERT_FLOATS_EQUAL(e1, e2)
   ASSERT_FLOATS_NOT_EQUAL(e1, e2)
   ASSERT_ARRAY_FLOATS_EQUAL(n, e1, e2)
   ASSERT_THROWS_NOTHING(expression)
   ASSERT_THROWS(exception_class, expression)
   ASSERT_CPOINTER_IS_NULL(e1)
   ASSERT_CPOINTER_IS_NOT_NULL(e1)
   ASSERT_FILE_EXISTS(filename)
   ASSERT_FILE_DOES_NOT_EXIST(filename)
*/

#ifndef CXXUNIT_TESTING_HPP
#define CXXUNIT_TESTING_HPP

#include <cfenv>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <exception>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "cxxunit_printing.hpp"
#ifdef __linux__
#  include <csignal>
#  include <execinfo.h>
#endif

#ifdef _MSC_VER
#  define __PRETTY_FUNCTION__ __FUNCTION__
#endif

#define CXX_UNUSED_PARAMETER(x) (void)x;

#define INDENT_STRING0 "  "
#define INDENT_STRING1 "    "
#define INDENT_STRING2 "      "

// SUB_TEST is being used to self document sub tests where a single
// TestCase has multiple tests in it
#define SUB_TEST(title) \
  sub_test = title; \
  add_sub_test = true;

// SUB_TITLE is being used as a category between TestCase and SUB_TEST
// it will also produce a summary of the number of TestCase's that
// contain each SUB_TITLE (this is useful if each TestCase runs the tests
// multiple times for different types (i.e. the tests are templated and run
// for (say) double, long and int. SUB_TITLE can then indicate the type
#define SUB_TITLE(title) \
  sub_title = title; \
  add_sub_title = true; \
  global_toc.push_back(title);

#define REGISTER_TEST(cls, name) \
  static TestCaseProcessor _##cls({new cls(), name})

#define PRINT_ERROR(PASSED) \
  if (display_line_details(PASSED)) { \
    if (!PASSED) { \
      std::cerr << INDENT_STRING1 << E_ERROR("ERROR"); \
    } else { \
      std::cerr << INDENT_STRING1 << E_INFO("SUCCESS"); \
    } \
    std::cerr << " in `" << __PRETTY_FUNCTION__ << "' at " << __FILE__ \
            << " line " << __LINE__ << ":" << std::endl; \
  }

#define ASSERT_NULL_TERMINATED_STRINGS_EQUAL(e1, e2) \
  do { \
    auto _l1 = e1; \
    auto _l2 = e2; \
    bool _passed = ((*_l1) == (*_l2)); \
    for (; (*_l1) != '\0' && (*_l2) != '\0' && _passed; _l1++, _l2++) \
      _passed = ((*_l1) == (*_l2)); \
    do_assert(_passed); \
    PRINT_ERROR(_passed); \
    print_error(_passed, "Strings `" #e1 "' (1) and `" #e2 "' (2) are", "equal"); \
    if (display_test_details(_passed)) { \
      std::cerr << INDENT_STRING2 << "(1): '" << e1 << "'," << std::endl; \
      std::cerr << INDENT_STRING2 << "(2): '" << e2 << "'"  << std::endl; \
    } \
    handle_failfast(_passed); \
  } while (0)

#define ASSERT_NULL_TERMINATED_STRINGS_NOT_EQUAL(e1, e2) \
  do { \
    auto _l1 = e1; \
    auto _l2 = e2; \
    bool _passed = ((*_l1) == (*_l2)); \
    for (; (*_l1) != '\0' && (*_l2) != '\0' && _passed; _l1++, _l2++) \
      _passed = ((*_l1) == (*_l2)); \
    _passed = !_passed; \
    do_assert(_passed); \
    PRINT_ERROR(_passed); \
    print_error(_passed, "Strings `" #e1 "' (1) and `" #e2 "' (2) are", "not equal", "equal"); \
    if (display_test_details(_passed)) { \
      std::cerr << INDENT_STRING2 << "(1): '" << e1 << "'," << std::endl; \
      std::cerr << INDENT_STRING2 << "(2): '" << e2 << "'"  << std::endl; \
    } \
    handle_failfast(_passed); \
  } while (0)

// this might not be required - it replaces carriage returns in a string
// with '@' before the comparison
#define ASSERT_MULTI_LINE_STRING_EQUAL(e1, e2) \
  do { \
    auto _l1 = e1; \
    auto _l2 = e2; \
    for (size_t i = 0; i < _l1.size(); i++) \
      _l1.at(i) = (_l1.at(i) == '\n' ? '@' : _l1.at(i)); \
    for (size_t i = 0; i < _l2.size(); i++) \
      _l2.at(i) = (_l2.at(i) == '\n' ? '@' : _l2.at(i)); \
    ASSERT_STRINGS_EQUAL(_l1, _l2); \
  } while (0)
// asserts true if the line (a std::string) contains the keyword (a std::string)
#define ASSERT_HAS_KEYWORD(line, keyword) \
  do { \
    bool _passed = do_assert(line.find(keyword)!=std::string::npos); \
    PRINT_ERROR(_passed); \
    print_error(_passed, "Keyword `" #keyword "' was", "found"); \
    if (display_test_details(_passed)) { \
      std::cerr << INDENT_STRING2  << "Line   : " << line << std::endl;  \
      std::cerr << INDENT_STRING2  << "Keyword: " << keyword << std::endl;  \
    } \
    handle_failfast(_passed); \
  } while (0)
#define ASSERT_NO_KEYWORD(line, keyword) \
  do { \
    bool _passed = do_assert(line.find(keyword)==std::string::npos); \
    PRINT_ERROR(_passed); \
    print_error(_passed, "Keyword `" #keyword "' was", "not found", "found"); \
    if (display_test_details(_passed)) { \
      std::cerr << INDENT_STRING2  << "Line   : " << line << std::endl;  \
      std::cerr << INDENT_STRING2  << "Keyword: " << keyword << std::endl;  \
    } \
    handle_failfast(_passed); \
  } while (0)
#define ASSERT_CPOINTER_IS_NULL(expression) \
  do { \
    auto _value = !static_cast<bool>(expression); \
    bool _passed = do_assert(_value); \
    PRINT_ERROR(_passed); \
    print_error(_passed, "Expression `" #expression "' is", "null", "not null"); \
    if (display_test_details(_passed)) { \
      std::cerr << INDENT_STRING2  << "Value is " << repr(_value) << std::endl; \
    } \
    handle_failfast(_passed); \
  } while (0)
#define ASSERT_CPOINTER_IS_NOT_NULL(expression) \
  do { \
    auto _value = static_cast<bool>(expression); \
    bool _passed = do_assert(_value); \
    PRINT_ERROR(_passed); \
    print_error(_passed, "Expression `" #expression "' is", "not null", "null"); \
    if (display_test_details(_passed)) { \
      std::cerr << INDENT_STRING2  << "Value is " << repr(_value) << std::endl; \
    } \
    handle_failfast(_passed); \
  } while (0)
#define ASSERT_FILE_EXISTS(filename) \
  do { \
    std::ifstream ifile(filename); \
    bool _passed = do_assert(ifile.is_open()); \
    ifile.close(); \
    PRINT_ERROR(_passed); \
    print_error(_passed, "File " #filename " ", "exists", "doesn't exist"); \
    handle_failfast(_passed); \
  } while (0)
#define ASSERT_FILE_DOES_NOT_EXIST(filename) \
  do { \
    std::ifstream ifile(filename); \
    bool _passed = do_assert(!(ifile.is_open())); \
    ifile.close(); \
    PRINT_ERROR(_passed); \
    print_error(_passed, "File " #filename " ", "doesn't exist", "exists"); \
    handle_failfast(_passed); \
  } while (0)
#define ASSERT_TRUE_LABELLED(label,expression) \
  do { \
    auto _value = (expression); \
    bool _passed = do_assert(_value); \
    PRINT_ERROR(_passed); \
    print_error(_passed, label, "passed"); \
    if (display_test_details(_passed)) { \
      std::cerr << INDENT_STRING2  << "Value is " << repr(_value) << std::endl; \
    } \
    handle_failfast(_passed); \
  } while (0)
#define ASSERT_TRUE(expression) \
  do { \
    auto _value = (expression); \
    bool _passed = do_assert(_value); \
    PRINT_ERROR(_passed); \
    print_error(_passed, "Expression `" #expression "' is", "true"); \
    if (display_test_details(_passed)) { \
      std::cerr << INDENT_STRING2  << "Value is " << repr(_value) << std::endl; \
    } \
    handle_failfast(_passed); \
  } while (0)
#define ASSERT_FALSE(expression) \
  do { \
    auto _value = (expression); \
    bool _passed = do_assert(!_value); \
    PRINT_ERROR(_passed); \
    print_error(_passed, "Expression `" #expression "' is", "false"); \
    if (display_test_details(_passed)) { \
      std::cerr << INDENT_STRING2 << "Value is " << repr(_value) << std::endl; \
    } \
    handle_failfast(_passed); \
  } while (0)
#define ASSERT_RELATION(e1, rel, e2) \
  do { \
    auto _v1 = (e1); \
    auto _v2 = (e2); \
    bool _passed = do_assert(_v1 rel _v2); \
    PRINT_ERROR(_passed); \
    print_error(_passed, "Expression `" #e1 " " #rel " " #e2 "' is", "true"); \
    if (display_test_details(_passed)) { \
      std::cerr << INDENT_STRING2 << #e1 " = " << repr(_v1) << ", " #e2 " = " << repr(_v2) << std::endl; \
    } \
    handle_failfast(_passed); \
  } while (0)
#define ASSERT_EQUAL_UNSIGNED(e1, e2) ASSERT_EQUAL(static_cast<size_t>(e1), static_cast<size_t>(e2))
#define ASSERT_EQUAL_ONLY_COUNT_FAILURE(e1, e2) \
  do { \
    auto _v1 = (e1); \
    auto _v2 = (e2); \
    bool _passed = do_assert(std::fabs(_v1 - _v2) <= 0.0); \
    if (!_passed) { \
      PRINT_ERROR(_passed); \
      print_error(_passed, "Expressions `" #e1 "' and `" #e2 "' are", "equal"); \
      if (display_test_details(_passed)) { \
        std::cerr << INDENT_STRING2 << #e1 " = " << repr(_v1) << ", " #e2 " = " << repr(_v2) << std::endl; \
      } \
      handle_failfast(_passed); \
    } \
  } while (0)
#define ASSERT_EQUAL(e1, e2) \
  do { \
    auto _v1 = (e1); \
    auto _v2 = (e2); \
    bool _passed = do_assert(std::fabs(_v1 - _v2) <= 0.0); \
    PRINT_ERROR(_passed); \
    print_error(_passed, "Expressions `" #e1 "' and `" #e2 "' are", "equal"); \
    if (display_test_details(_passed)) { \
      std::cerr << INDENT_STRING2 << #e1 " = " << repr(_v1) << ", " #e2 " = " << repr(_v2) << std::endl; \
    } \
    handle_failfast(_passed); \
  } while (0)
#define ASSERT_NOT_EQUAL(e1, e2) \
  do { \
    auto _v1 = (e1); \
    auto _v2 = (e2); \
    bool _passed = do_assert(std::fabs(_v1 - _v2) > 0.0); \
    PRINT_ERROR(_passed); \
    print_error(_passed, "Expressions `" #e1 "' and `" #e2 "' are", "not equal", "equal"); \
    if (display_test_details(_passed)) { \
      std::cerr << INDENT_STRING2 << #e1 " = " << repr(_v1) << ", " #e2 " = " << repr(_v2) << std::endl; \
    } \
    handle_failfast(_passed); \
  } while (0)
#define ASSERT_ARRAY_EQUAL(n, e1, e2) \
  do { \
    auto _n = (n); \
    auto _v1 = (e1); \
    auto _v2 = (e2); \
    bool _passed = true; \
    for (int _i = 0; _i < static_cast<int>(_n) && _passed; _i++) { \
      _passed = (std::fabs(_v1[_i] - _v2[_i]) <= 0.0); \
    } \
    do_assert(_passed); \
    PRINT_ERROR(_passed); \
    print_error(_passed, "Arrays `" #e1 "' and `" #e2 "' are", "equal"); \
    if (display_test_details(_passed)) { \
      int _ti = 0; \
      for (int _i = 0; _i < static_cast<int>(_n) && _ti < 10; _i++) { \
        bool _tpassed = (std::fabs(_v1[_i] - _v2[_i]) <= 0.0); \
        if ((!_passed && !_tpassed) || _passed) { \
          _ti += 1; \
          std::cerr << INDENT_STRING2 << "i = " << _i << ", " << #e1 " = " << repr(_v1[_i]) << ", " #e2 " = " << \
            repr(_v2[_i]) << "  (" << (_tpassed ? "equal" : "different") << ")" << std::endl; \
        } \
      } \
    } \
    handle_failfast(_passed); \
  } while (0)
#define ASSERT_ARRAY_NOT_EQUAL(n, e1, e2) \
  do { \
    auto _n = (n); \
    auto _v1 = (e1); \
    auto _v2 = (e2); \
    bool _passed = false; \
    for (int _i = 0; _i < static_cast<int>(_n) && !_passed; _i++) { \
      _passed = (std::fabs(_v1[_i] - _v2[_i]) > 0.0); \
    } \
    do_assert(_passed); \
    PRINT_ERROR(_passed); \
    print_error(_passed, "Arrays `" #e1 "' and `" #e2 "' are", "not equal", "equal"); \
    if (display_test_details(_passed)) { \
      int _ti = 0; \
      for (int _i = 0; _i < static_cast<int>(_n) && _ti < 10; _i++) { \
        bool _tpassed = (std::fabs(_v1[_i] - _v2[_i]) > 0.0); \
        if (!_tpassed || !_passed) { \
          _ti += 1; \
          std::cerr << INDENT_STRING2 << "i = " << _i << ", " << #e1 " = " << repr(_v1[_i]) << ", " #e2 " = " << \
            repr(_v2[_i]) << "  (" << (_tpassed ? "different" : "equal") << ")" << std::endl; \
        } \
      } \
    } \
    handle_failfast(_passed); \
  } while (0)
#define ASSERT_ALMOST_EQUAL(e1, e2, precision) \
  do { \
    auto _v1 = (e1); \
    auto _v2 = (e2); \
    auto _diff = calc_diff(_v1, _v2); \
    bool _passed = do_assert(_diff < precision); \
    PRINT_ERROR(_passed); \
    print_error(_passed, "Expressions `" #e1 "' and `" #e2 "' are", "almost equal"); \
    if (display_test_details(_passed)) { \
      std::cerr << INDENT_STRING2 << #e1 " = " << repr(_v1) << ", " #e2 " = " << repr(_v2) << ", diff = " << repr(_diff) << "  (" << (_tpassed ? "almost equal" : "different") << ")" << std::endl; \
      std::cerr << INDENT_STRING2 << "precision = " << precision << std::endl; \
    } \
    handle_failfast(_passed); \
  } while (0)
#define ASSERT_ARRAY_ALMOST_EQUAL(n, e1, e2, precision) \
  do { \
    auto _n = (n); \
    auto _v1 = (e1); \
    auto _v2 = (e2); \
    bool _passed = true; \
    for (int _i = 0; _i < static_cast<int>(_n) && _passed; _i++) { \
      auto _diff = calc_diff(_v1[_i], _v2[_i]); \
      _passed = (_diff < precision); \
    } \
    do_assert(_passed); \
    PRINT_ERROR(_passed); \
    print_error(_passed, "Arrays `" #e1 "' and `" #e2 "' are", "almost equal"); \
    if (display_test_details(_passed)) { \
      int _ti = 0; \
      for (int _i = 0; _i < static_cast<int>(_n) && _ti < 10; _i++) { \
        auto _diff = calc_diff(_v1[_i], _v2[_i]);                    \
        bool _tpassed = (_diff < precision); \
        if ((!_passed && !_tpassed) || _passed) { \
          _ti += 1; \
          std::cerr << INDENT_STRING2 << "i = " << _i << ", " << #e1 " = " << repr(_v1[_i]) << ", " #e2 " = " << \
            repr(_v2[_i]) << ", diff = " << repr(_diff) << "  (" << (_tpassed ? "almost equal" : "different") << ")" << std::endl; \
        } \
      } \
      std::cerr << INDENT_STRING2 << "precision = " << precision << std::endl; \
    } \
    handle_failfast(_passed); \
  } while (0)

// this assumes erm is in row major order, ecm in col major
#define ASSERT_2DARRAY_ALMOST_EQUAL_ROW_VS_COL(n, m, erm, ecm, precision) \
  do { \
    auto _n = (n); \
    auto _m = (m); \
    auto _v1 = (erm); \
    auto _v2 = (ecm); \
    bool _passed = true; \
    for (int _i = 0; _i < static_cast<int>(_n) && _passed; _i++) { \
      for (int _j = 0; _j < static_cast<int>(_m) && _passed; _j++) { \
        int _p1 = (_i*_m) + _j; \
        int _p2 = (_j*_n) + _i; \
        auto _diff = calc_diff(_v1[_p1], _v2[_p2]); \
        _passed = (_diff < precision); \
      } \
    } \
    do_assert(_passed); \
    PRINT_ERROR(_passed); \
    print_error(_passed, "Arrays `" #erm "' and `" #ecm "' are", "almost equal"); \
    if (display_test_details(_passed)) { \
      int _ti = 0; \
      for (int _i = 0; _i < static_cast<int>(n) && _ti < 10; _i++) { \
        for (int _j = 0; _j < static_cast<int>(_m) && _ti < 10; _j++) { \
          int _p1 = (_i*_m) + _j; \
          int _p2 = (_j*_n) + _i; \
          auto _diff = calc_diff(_v1[_p1], _v2[_p2]); \
          bool _tpassed = (_diff < precision); \
          if ((!_passed && !_tpassed) || _passed) { \
            _ti += 1; \
            std::cerr << INDENT_STRING2 << "i = " << _i << ", j = " << _j << ", " << #erm " = " << repr(_v1[_p1]) << ", " #ecm " = " << \
              repr(_v2[_p2]) << ", diff = " << repr(_diff) << "  (" << (_tpassed ? "almost equal" : "different") << ")" << std::endl; \
          } \
        } \
      } \
      std::cerr << INDENT_STRING2 << "precision = " << precision << std::endl; \
    } \
    handle_failfast(_passed); \
  } while (0)
#define ASSERT_STRINGS_EQUAL(e1, e2) \
  do { \
    std::string _v1 = (e1); \
    std::string _v2 = (e2); \
    bool _passed = do_assert(_v1 == _v2); \
    PRINT_ERROR(_passed); \
    print_error(_passed, "Strings `" #e1 "' (1) and `" #e2 "' (2) are", "equal"); \
    if (display_test_details(_passed)) { \
      std::cerr << INDENT_STRING2 << "(1): '" << _v1 << "'," << std::endl; \
      std::cerr << INDENT_STRING2 << "(2): '" << _v2 << "'"  << std::endl; \
    } \
    handle_failfast(_passed); \
  } while (0)
#define ASSERT_STRINGS_NOT_EQUAL(e1, e2) \
  do { \
    std::string _v1 = (e1); \
    std::string _v2 = (e2); \
    bool _passed = do_assert(_v1 != _v2); \
    PRINT_ERROR(_passed); \
    print_error(_passed, "Strings `" #e1 "' (1) and `" #e2 "' (2) are", "not equal", "equal"); \
    if (display_test_details(_passed)) { \
      std::cerr << INDENT_STRING2 << "(1): '" << _v1 << "'," << std::endl; \
      std::cerr << INDENT_STRING2 << "(2): '" << _v2 << "'"  << std::endl; \
    } \
    handle_failfast(_passed); \
  } while (0)
#define ASSERT_FLOATS_EQUAL(e1, e2) \
  do { \
    auto _v1 = (e1); \
    auto _v2 = (e2); \
    bool _passed = do_assert(compare_floats(_v1, _v2)); \
    PRINT_ERROR(_passed); \
    print_error(_passed, "Floating point numbers `" #e1 "' and `" #e2 "' are", "equal"); \
    if (display_test_details(_passed)) { \
      std::cerr << INDENT_STRING2 << #e1 " = " << repr(_v1) << ", " #e2 " = " << repr(_v2) << std::endl; \
    } \
    handle_failfast(_passed); \
  } while (0)
#define ASSERT_FLOATS_NOT_EQUAL(e1, e2) \
  do { \
    auto _v1 = (e1); \
    auto _v2 = (e2); \
    bool _passed = do_assert(!compare_floats(_v1, _v2)); \
    PRINT_ERROR(_passed); \
    print_error(_passed, "Floating point numbers `" #e1 "' and `" #e2 "' are", "not equal", "equal"); \
    if (display_test_details(_passed)) { \
      std::cerr << INDENT_STRING2 << #e1 " = " << repr(_v1) << ", " #e2 " = " << repr(_v2) << std::endl; \
    } \
    handle_failfast(_passed); \
  } while (0)
#define ASSERT_ARRAY_FLOATS_EQUAL(n, e1, e2) \
  do { \
    auto _v1 = (e1); \
    auto _v2 = (e2); \
    bool _passed = true; \
    for (int _i = 0; _i < static_cast<int>(n) && _passed; _i++) { \
      _passed = (compare_floats(_v1[_i], _v2[_i])); \
    } \
    do_assert(_passed); \
    PRINT_ERROR(_passed); \
    print_error(_passed, "Arrays `" #e1 "' and `" #e2 "' are", "equal"); \
    if (display_test_details(_passed)) { \
      int _ti = 0; \
      for (int _i = 0; _i < static_cast<int>(n) && _ti < 10; _i++) { \
        bool _tpassed = (compare_floats(_v1[_i], _v2[_i])); \
        if ((!_passed && !_tpassed) || _passed) { \
          _ti += 1; \
          std::cerr << INDENT_STRING2 << "i = " << _i << ", " << #e1 " = " << repr(_v1[_i]) << ", " #e2 " = " << \
            repr(_v2[_i]) << "  (" << (_tpassed ? "equal" : "different") << ")" << std::endl; \
        } \
      } \
    } \
    handle_failfast(_passed); \
  } while (0)

#define ASSERT_THROWS_NOTHING(expression) \
  do { \
    bool caught = false; \
    try { \
      (void)(expression); \
    } catch (...) { \
      caught = true; \
    } \
    bool _passed = do_assert(!caught); \
    std::stringstream buffer; \
    PRINT_ERROR(_passed); \
    print_error(_passed, "An exception was", "not thrown", "thrown"); \
    handle_failfast(_passed); \
  } while(0)

#define ASSERT_THROWS(exception_class, expression) \
  do { \
    bool caught = false; \
    try { \
      (void)(expression); \
    } catch (const exception_class &_exc) { \
      CXX_UNUSED_PARAMETER(_exc); \
      caught = true; \
    } \
    bool _passed = do_assert(caught); \
    std::stringstream buffer; \
    buffer << "Exception " << #exception_class; \
    PRINT_ERROR(_passed); \
    print_error(_passed, buffer.str(), "thrown"); \
    handle_failfast(_passed); \
  } while(0)
// clang-format on

// hold a global list of subtitles (as added by SUB_TITLE)
std::vector<std::string> global_toc;

template <typename T>
T calc_diff(T e1, T e2) {
  // if e1 > 1, returns the relative difference, otherwise the absolute difference
  T _diff = std::fabs(e1 - e2);
  return (std::fabs(e1) > 1.0) ? _diff / std::fabs(e1) : _diff;
}

template <typename T>
T repr(const T value) {
  return value;
}

uint16_t repr(const uint8_t value) { return value; }

template <typename IV>
bool compare_floats(IV v1, IV v2) {
  // this is to cover integers etc, whilst it is a bit weird to
  // have a function called compare_floats handle integers, it is
  // useful when the unit tests are templated and sometimes called
  // on doubles and sometimes on integers
  return (v1 == v2);
}

template <>
bool compare_floats(float v1, float v2) {
  return (std::fabs(v1 - v2) * 100000.f <= std::min(fabs(v1), fabs(v2)));
}

template <>
bool compare_floats(double v1, double v2) {
  return (std::fabs(v1 - v2) * 1000000000000. <= std::min(fabs(v1), fabs(v2)));
}

struct TestCase {
  unsigned assertions_total;
  unsigned assertions_successful;
  bool failfast;
  int print_level;
  bool last_assert_passed;
  bool add_sub_title;
  std::string sub_title;
  bool add_sub_test;
  std::string sub_test;

  TestCase()
    : assertions_total(0), assertions_successful(0), failfast(false),
      print_level(2), last_assert_passed(true), add_sub_title(false),
      add_sub_test(true) {}

  bool do_assert(bool condition) {
    ++assertions_total;
    if (condition) {
      ++assertions_successful;
    }
    return condition;
  }

  void handle_failfast(bool passed) {
    last_assert_passed = passed;
    if (failfast && !passed) {
      std::cerr << "Exiting immediately because failfast = true." << std::endl;
      exit(1);
    }
  }

  void print_sub_title(void) {
    if (add_sub_title && sub_title != "") {
      add_sub_title = false;
      std::cerr << INDENT_STRING0 << "** " << sub_title << std::endl;
    }
  }

  void print_sub_test(void) {
    if (add_sub_test && sub_test != "") {
      add_sub_test = false;
      std::cerr << INDENT_STRING1 << "*** " << sub_test << std::endl;
    }
  }

  void print_error(bool passed, const std::string desc1,
                   const std::string desc2, const std::string desc3) {
    if (display_title(passed)) {
      print_sub_title();
      print_sub_test();
      std::cerr << INDENT_STRING2 << desc1 << " " << (passed ? desc2 : desc3)
                << "." << std::endl;
    }
  }
  void print_error(bool passed, const std::string desc1,
                   const std::string desc2) {
    if (display_title(passed)) {
      print_sub_title();
      print_sub_test();
      std::cerr << INDENT_STRING2 << desc1 << (passed ? " " : " not ") << desc2
                << "." << std::endl;
    }
  }

  bool display_assertion_summary() {
    // if true number of assertions passed / failed is output
    return (print_level > 1);
  }

  bool display_title(bool passed) {
    // if true title for each test is output
    return ((!passed && print_level > 1) || print_level > 2);
  }

  bool display_line_details(bool passed) {
    // if true details of the code line for the test is output
    return ((!passed && print_level > 1) || print_level > 3);
  }

  bool display_test_details(bool passed) {
    // if true details of the values compared are output
    return ((!passed && print_level > 1) || print_level > 4);
  }

  virtual void run() = 0;
  virtual ~TestCase() {}
};

struct TestCaseInfo {
  TestCase *test_case;
  std::string name;
};

static std::vector<TestCaseInfo> storage;

struct TestCaseProcessor {
  TestCaseProcessor(TestCaseInfo info) { storage.push_back(info); }
};

#ifdef __linux__
void signal_handler(int signum) {
  std::cerr << E_ERROR("Signal occurred") << ": " << strsignal(signum)
            << std::endl;
  /* Print the backtrace */
  void *buffer[10];
  size_t size = backtrace(buffer, 10);
  backtrace_symbols_fd(buffer, size, STDERR_FILENO);
  /* Now call the default handler */
  signal(signum, SIG_DFL);
  exit(128 + signum);
}
#endif

void print_help(const char *command_name) {
  std::cout << "Usage: " << command_name << " [-f] [-n] [-p <n>]" << std::endl;
  std::cout << std::endl;
  std::cout << "  -f, --fail-fast: Exit after first failure" << std::endl;
  std::cout << "  -n, --no-catch:  Do not catch C++ exceptions (useful for "
               "debugging)"
            << std::endl;
  std::cout << "  -p <n>, --print-level <n>:  Print level (0, 1, 2, 3, 4 or 5)"
            << std::endl;
  std::cout << "          0 = No output" << std::endl;
  std::cout << "          1 = Overall summary only" << std::endl;
  std::cout << "          2 = Summary per test, details of errors output "
               "(default)"
            << std::endl;
  std::cout << "          3 = Summary of all expressions / assertions checked"
            << std::endl;
  std::cout << "          4 = Line numbers for all tests output" << std::endl;
  std::cout << "          5 = Full details for all tests output" << std::endl;
  std::cout << std::endl;
  std::cout << "Return value is the number of failed tests" << std::endl;
}

void display_toc(std::vector<std::string> toc, const std::string title) {
  // output a toc (for some definition of toc)
  if (toc.size() > 0) {
    std::cout << std::endl;
    std::cout << title << std::endl;
    std::sort(toc.begin(), toc.end());
    std::vector<size_t> noccur(toc.size(), 0);
    size_t n = 0;
    size_t cnt = 1;
    for (auto iter = toc.begin() + 1; iter != toc.end(); ++iter) {
      if ((*iter) != (*(iter - 1))) {
        noccur[n] = cnt;
        ++n;
        cnt = 1;
      } else {
        ++cnt;
      }
    }
    noccur[n] = cnt;

    std::cout << "      Count   Title" << std::endl;
    auto last_unique = std::unique(toc.begin(), toc.end());
    n = 0;
    for (auto iter = toc.begin(); iter != last_unique; ++iter, ++n) {
      std::cout << " " << std::left << std::setw(3) << n + 1 << "    "
                << std::left << std::setw(6) << noccur[n] << *iter << std::endl;
    }
  }
}

int main(int argc, char **argv) {
  bool failfast = false;
  bool nocatch = false;
  int default_print_level = 2;
  int print_level = default_print_level;

  for (int i = 1; i < argc; ++i) {
    char *arg = argv[i];
    bool invalid = false;
    if (!strcmp(arg, "--fail-fast") || !strcmp(arg, "-f")) {
      failfast = true;
    } else if (!strcmp(arg, "--no-catch") || !strcmp(arg, "-n")) {
      nocatch = true;
    } else if (!strcmp(arg, "--print_level") || !strcmp(arg, "-p")) {
      i++;
      if (i < argc) {
        print_level = atoi(argv[i]);
        if ((invalid = (print_level < 0 || print_level > 5))) {
          std::cout << "ERROR: Invalid value (" << print_level
                    << ") for print_level supplied" << std::endl
                    << std::endl;
        }
      } else {
        invalid = true;
        std::cout << "ERROR: No print_level supplied" << std::endl << std::endl;
      }
    } else {
      invalid = true;
    }
    if (invalid) {
      print_help(argv[0]);

      // clean up
      for (const TestCaseInfo &info : storage) {
        TestCase *test_case = info.test_case;
        delete test_case;
      }

      return 0;
    }
  }

#ifdef __USE_GNU
  feenableexcept(FE_DIVBYZERO | FE_INVALID | FE_OVERFLOW | FE_UNDERFLOW);
#endif
#ifdef __linux__
  signal(SIGSEGV, signal_handler);
#endif

  bool quite = (print_level == 0);
  int nsuccess = 0;
  int nfail = 0;
  int nndone = 0;
  for (const TestCaseInfo &info : storage) {
    TestCase *test_case = info.test_case;
    test_case->failfast = failfast;
    test_case->print_level = print_level;
    if (test_case->display_assertion_summary()) {
      std::cout << " * " << info.name << std::endl;
    }
    bool success = true;
    if (nocatch) {
      test_case->run();
    } else {
      try {
        test_case->run();
      } catch (const std::exception &e) {
        success = false;
        test_case->do_assert(false);
        std::cerr << "   " << E_ERROR("Exception occurred") << ": " << e.what()
                  << std::endl;
      }
    }
    if (test_case->assertions_successful < test_case->assertions_total) {
      success = false;
      nfail += 1;
    } else if (test_case->assertions_total == 0) {
      nndone += 1;
    } else {
      nsuccess += 1;
    }
    if (test_case->display_assertion_summary()) {
      if (test_case->assertions_total == 0) {
        std::cout << INDENT_STRING1 << "Result: " << O_INFO("NOT DONE") << " ("
                  << test_case->assertions_total << " assertions run)"
                  << std::endl;
      } else if (success) {
        std::cout << INDENT_STRING1 << "Result: " << O_SUCCESS("SUCCESS")
                  << " (" << test_case->assertions_total
                  << " assertions passed)" << std::endl;
      } else {
        std::cout << INDENT_STRING1 << "Result: " << O_ERROR("FAIL") << " ("
                  << test_case->assertions_successful << " of "
                  << test_case->assertions_total << " assertions passed)"
                  << std::endl;
      }
    }

    if (test_case->display_assertion_summary()) {
      std::cout << std::endl;
    }

    delete test_case;
  }

  if (!quite) {
    std::cout << "* Overall Summary: "
              << (nfail == 0 ? O_SUCCESS("PASSED") : O_ERROR("FAILED"))
              << std::endl;
    std::cout << INDENT_STRING1 << "Number of successful tests : " << nsuccess
              << std::endl;
    std::cout << INDENT_STRING1 << "Number of failed tests     : " << nfail
              << std::endl;
    if (nndone > 0) {
      std::cout << INDENT_STRING1 << "Number of tests not done   : " << nndone
                << std::endl;
    }

    if (print_level > default_print_level) {
      display_toc(global_toc, "Tests with the following subtitle ran:");
    }
  }

  return nfail;
}

#endif /* CXXUNIT_TESTING_HPP */
