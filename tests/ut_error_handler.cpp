// unit tests for code in error_handler
#include "include/cxxunit_testing.hpp"
#include "utility/nagcpp_data_handling_default.hpp"
#include "utility/nagcpp_engine_routines.hpp"
#include "utility/nagcpp_engine_types.hpp"
#include "utility/nagcpp_error_handler.hpp"
#include <algorithm>
#include <exception>
#include <sstream>
#include <stdio.h>

using namespace nagcpp;

namespace errbuf_setup {
  void append_to_buffer(std::stringstream &buffer) {}
  template <typename T>
  void append_to_buffer(std::stringstream &buffer, T t) {
    buffer << t << error_handler::errbuf_delim;
    ;
  }
  template <typename T, typename... Targs>
  void append_to_buffer(std::stringstream &buffer, T t, Targs... Fargs) {
    append_to_buffer(buffer, t);
    append_to_buffer(buffer, Fargs...);
  }
  template <typename... Targs>
  void generate_errbuf(char errbuf[], int ierr, int ifmt, int count,
                       Targs... Fargs) {
    std::stringstream buffer;
    buffer << ierr << error_handler::errbuf_delim << ifmt
           << error_handler::errbuf_delim << count
           << error_handler::errbuf_delim;
    append_to_buffer(buffer, Fargs...);
    strncpy(errbuf, buffer.str().c_str(), 200);

    // NB: ERRBUF is not usually null terminated
    errbuf[std::max(200, (int)buffer.str().length() + 1)] = '\0';
  }
  template <typename... Targs>
  void generate_errbuf(error_handler::ErrorHandler &eh, int count,
                       Targs... Fargs) {
    generate_errbuf(eh.errbuf, eh.errorid, eh.errorid, count, Fargs...);
  }
  template <typename... Targs>
  void generate_errbuf(error_handler::ErrorHandler &eh) {
    generate_errbuf(eh, 0);
  }
}

struct test_populate_eb_data : public TestCase {
  void run() override {
    using namespace errbuf_setup;
    {
      SUB_TEST("standard usage, no additional data");
      error_handler::ErrorHandler eh;
      generate_errbuf(eh.errbuf, 1, 2, 0);
      bool failed = eh.populate_eb_data();
      ASSERT_FALSE(failed);
      ASSERT_EQUAL(eh.ierr, 1);
      ASSERT_EQUAL(eh.ifmt, 2);
      ASSERT_EQUAL((int)eh.eb_data.size(), 0);
    }
    {
      SUB_TEST("standard usage, various additional data");
      error_handler::ErrorHandler eh;
      generate_errbuf(eh.errbuf, 3, 4, 3, "HELLO", 1.4, 5);
      bool failed = eh.populate_eb_data();
      ASSERT_FALSE(failed);
      ASSERT_EQUAL(eh.ierr, 3);
      ASSERT_EQUAL(eh.ifmt, 4);
      ASSERT_EQUAL((int)eh.eb_data.size(), 3);
      ASSERT_STRINGS_EQUAL(eh.eb_data[0], "HELLO");
      ASSERT_STRINGS_EQUAL(eh.eb_data[1], "1.4");
      ASSERT_STRINGS_EQUAL(eh.eb_data[2], "5");
    }
    {
      SUB_TEST("invalid usage, blank errbuf");
      error_handler::ErrorHandler eh;
      for (size_t i = 0; i < 200; i++)
        eh.errbuf[i] = error_handler::errbuf_delim;
      bool failed = eh.populate_eb_data();
      ASSERT_TRUE(failed);
      ASSERT_EQUAL(eh.ierr, error_handler::IERR_UNEXPECTED);
      ASSERT_EQUAL(eh.ifmt, error_handler::IERR_UNEXPECTED);
      ASSERT_EQUAL((int)eh.eb_data.size(), 0);
      ASSERT_TRUE((eh.type == error_handler::ErrorType::UnexpectedError));
      ASSERT_TRUE((eh.category == error_handler::ErrorCategory::Error));
    }
    {
      SUB_TEST("unexpected usage, too much data");
      error_handler::ErrorHandler eh;
      generate_errbuf(eh.errbuf, 5, 6, 2, "HELLO", 1.4, 5);
      bool failed = eh.populate_eb_data();
      ASSERT_FALSE(failed);
      ASSERT_EQUAL(eh.ierr, 5);
      ASSERT_EQUAL(eh.ifmt, 6);
      ASSERT_EQUAL((int)eh.eb_data.size(), 2);
      ASSERT_STRINGS_EQUAL(eh.eb_data[0], "HELLO");
      ASSERT_STRINGS_EQUAL(eh.eb_data[1], "1.4");
    }
    {
      SUB_TEST("unexpected usage, not enough data");
      error_handler::ErrorHandler eh;
      generate_errbuf(eh.errbuf, 7, 8, 3, "HELLO", 1.4);
      bool failed = eh.populate_eb_data();
      ASSERT_FALSE(failed);
      ASSERT_EQUAL(eh.ierr, 7);
      ASSERT_EQUAL(eh.ifmt, 8);
      ASSERT_EQUAL((int)eh.eb_data.size(), 3);
      ASSERT_STRINGS_EQUAL(eh.eb_data[0], "HELLO");
      ASSERT_STRINGS_EQUAL(eh.eb_data[1], "1.4");
      ASSERT_STRINGS_EQUAL(eh.eb_data[2], error_handler::unknown_data_msg);
    }
  }
};
// clang-format off
REGISTER_TEST(test_populate_eb_data, "Test populate_eb_data");
// clang-format on

struct test_initial_error_handler_en_data : public TestCase {
  void run() override {
    using namespace errbuf_setup;
    {
      SUB_TEST("user exception");
      error_handler::ErrorHandler eh;
      eh.prepare("test1");
      eh.error_handler_type = error_handler::ErrorHandlerType::ThrowNothing;
      generate_errbuf(eh.errbuf, 1, 2, 0);
      types::engine_data en_data;
      engine_routines::y90haan_(en_data);
      en_data.hlperr = error_handler::HLPERR_USER_EXCEPTION;
      bool handled = eh.initial_error_handler(en_data);
      ASSERT_TRUE(handled);
      ASSERT_TRUE((eh.type == error_handler::ErrorType::CallbackError));
      ASSERT_TRUE((eh.category == error_handler::ErrorCategory::Error));
      ASSERT_STRINGS_EQUAL(eh.fun_name, "test1");
      ASSERT_EQUAL(eh.errorid, error_handler::IERR_HLPERR_USER_EXCEPTION);
      ASSERT_EQUAL(eh.ierr, error_handler::IERR_HLPERR_USER_EXCEPTION);
      ASSERT_EQUAL(eh.ifmt, error_handler::IERR_CALLBACK_ERROR_IFMT);
      ASSERT_EQUAL((int)eh.eb_data.size(), 0);
      ASSERT_FALSE(eh.contact_nag);
      // only checking for keyword(s) in the error message to allow actual wording
      // to change at a later date
      ASSERT_HAS_KEYWORD(eh.msg, "exception");
    }
    {
      SUB_TEST("array pointer changed");
      error_handler::ErrorHandler eh;
      eh.prepare("test2");
      eh.error_handler_type = error_handler::ErrorHandlerType::ThrowNothing;
      generate_errbuf(eh.errbuf, 3, 4, 0);
      types::engine_data en_data;
      engine_routines::y90haan_(en_data);
      en_data.hlperr = error_handler::HLPERR_ARRAY_POINTER_CHANGED;
      bool handled = eh.initial_error_handler(en_data);
      ASSERT_TRUE(handled);
      ASSERT_TRUE((eh.type == error_handler::ErrorType::CallbackError));
      ASSERT_TRUE((eh.category == error_handler::ErrorCategory::Error));
      ASSERT_STRINGS_EQUAL(eh.fun_name, "test2");
      ASSERT_EQUAL(eh.errorid,
                   error_handler::IERR_HLPERR_ARRAY_POINTER_CHANGED);
      ASSERT_EQUAL(eh.ierr, error_handler::IERR_HLPERR_ARRAY_POINTER_CHANGED);
      ASSERT_EQUAL(eh.ifmt, error_handler::IERR_CALLBACK_ERROR_IFMT);
      ASSERT_EQUAL((int)eh.eb_data.size(), 0);
      ASSERT_FALSE(eh.contact_nag);
      // only checking for keyword(s) in the error message to allow actual wording
      // to change at a later date
      ASSERT_HAS_KEYWORD(eh.msg, "array");
      ASSERT_HAS_KEYWORD(eh.msg, "changed");
    }
    {
      SUB_TEST("unexpected error");
      error_handler::ErrorHandler eh;
      eh.prepare("test3");
      eh.error_handler_type = error_handler::ErrorHandlerType::ThrowNothing;
      generate_errbuf(eh.errbuf, 5, 6, 0);
      types::engine_data en_data;
      engine_routines::y90haan_(en_data);
      // this is any value that is not error_handler::HLPERR_ARRAY_POINTER_CHANGED or
      // error_handler::HLPERR_USER_EXCEPTION
      en_data.hlperr = abs(error_handler::HLPERR_ARRAY_POINTER_CHANGED) +
                       abs(error_handler::HLPERR_USER_EXCEPTION) + 1;
      bool handled = eh.initial_error_handler(en_data);
      ASSERT_TRUE(handled);
      ASSERT_TRUE((eh.type == error_handler::ErrorType::UnexpectedError));
      ASSERT_TRUE((eh.category == error_handler::ErrorCategory::Error));
      ASSERT_STRINGS_EQUAL(eh.fun_name, "test3");
      ASSERT_EQUAL(eh.errorid, error_handler::IERR_UNEXPECTED);
      ASSERT_EQUAL(eh.ierr, error_handler::IERR_UNEXPECTED);
      ASSERT_EQUAL(eh.ifmt, error_handler::IERR_UNEXPECTED);
      ASSERT_EQUAL((int)eh.eb_data.size(), 0);
      ASSERT_TRUE(eh.contact_nag);
      // only checking for keyword(s) in the error message to allow actual wording
      // to change at a later date
      ASSERT_HAS_KEYWORD(eh.msg, "unexpected");
    }
  }
};
// clang-format off
REGISTER_TEST(test_initial_error_handler_en_data, "Test initial_error_handler (en_data triggered error)");
// clang-format on

struct test_initial_error_handler_global : public TestCase {
  void run() override {
    using namespace errbuf_setup;
    {
      SUB_TEST("memory allocation");
      error_handler::ErrorHandler eh;
      eh.prepare("test2");
      eh.error_handler_type = error_handler::ErrorHandlerType::ThrowNothing;
      eh.errorid = error_handler::IERR_ALLOC_FAIL;
      generate_errbuf(eh);
      types::engine_data en_data;
      engine_routines::y90haan_(en_data);
      bool handled = eh.initial_error_handler(en_data);
      ASSERT_TRUE(handled);
      ASSERT_TRUE((eh.type == error_handler::ErrorType::MemoryError));
      ASSERT_TRUE((eh.category == error_handler::ErrorCategory::Error));
      ASSERT_STRINGS_EQUAL(eh.fun_name, "test2");
      ASSERT_EQUAL(eh.errorid, error_handler::IERR_ALLOC_FAIL);
      ASSERT_EQUAL(eh.ierr, error_handler::IERR_ALLOC_FAIL);
      ASSERT_EQUAL(eh.ifmt, error_handler::IERR_ALLOC_FAIL);
      ASSERT_EQUAL((int)eh.eb_data.size(), 0);
      ASSERT_FALSE(eh.contact_nag);
      // only checking for keyword(s) in the error message to allow actual wording
      // to change at a later date
      ASSERT_HAS_KEYWORD(eh.msg, "memory");
    }
    {
      SUB_TEST("licence failure");
      error_handler::ErrorHandler eh;
      eh.prepare("test1");
      eh.error_handler_type = error_handler::ErrorHandlerType::ThrowNothing;
      eh.errorid = error_handler::IERR_NO_LIC;
      generate_errbuf(eh);
      types::engine_data en_data;
      engine_routines::y90haan_(en_data);
      bool handled = eh.initial_error_handler(en_data);
      ASSERT_TRUE(handled);
      ASSERT_TRUE((eh.type == error_handler::ErrorType::LicenceError));
      ASSERT_TRUE((eh.category == error_handler::ErrorCategory::Error));
      ASSERT_STRINGS_EQUAL(eh.fun_name, "test1");
      ASSERT_EQUAL(eh.errorid, error_handler::IERR_NO_LIC);
      ASSERT_EQUAL(eh.ierr, error_handler::IERR_NO_LIC);
      ASSERT_EQUAL(eh.ifmt, error_handler::IERR_NO_LIC);
      ASSERT_EQUAL((int)eh.eb_data.size(), 0);
      ASSERT_FALSE(eh.contact_nag);
      // only checking for keyword(s) in the error message to allow actual wording
      // to change at a later date
      ASSERT_HAS_KEYWORD(eh.msg, "licence");
    }
    {
      SUB_TEST("unexpected error");
      error_handler::ErrorHandler eh;
      eh.prepare("test3");
      eh.error_handler_type = error_handler::ErrorHandlerType::ThrowNothing;
      eh.errorid = error_handler::IERR_UNEXPECTED;
      generate_errbuf(eh);
      eh.ierr = 55;
      eh.ifmt = 77;
      types::engine_data en_data;
      engine_routines::y90haan_(en_data);
      bool handled = eh.initial_error_handler(en_data);
      ASSERT_TRUE(handled);
      ASSERT_TRUE((eh.type == error_handler::ErrorType::UnexpectedError));
      ASSERT_TRUE((eh.category == error_handler::ErrorCategory::Error));
      ASSERT_STRINGS_EQUAL(eh.fun_name, "test3");
      ASSERT_EQUAL(eh.errorid, error_handler::IERR_UNEXPECTED);
      ASSERT_EQUAL(eh.ierr, 55);
      ASSERT_EQUAL(eh.ifmt, 77);
      ASSERT_EQUAL((int)eh.eb_data.size(), 0);
      ASSERT_TRUE(eh.contact_nag);
      // only checking for keyword(s) in the error message to allow actual wording
      // to change at a later date
      ASSERT_HAS_KEYWORD(eh.msg, "unexpected");
    }
  }
};
// clang-format off
REGISTER_TEST(test_initial_error_handler_global, "Test initial_error_handler (global error)");
// clang-format on

struct test_initial_error_handler_routine : public TestCase {
  void run() override {
    using namespace errbuf_setup;
    {
      error_handler::ErrorHandler eh;
      eh.prepare("test1");
      eh.error_handler_type = error_handler::ErrorHandlerType::ThrowNothing;
      eh.errorid = 55;
      generate_errbuf(eh, 3, "HELLO", 1.4, 5);
      types::engine_data en_data;
      engine_routines::y90haan_(en_data);
      bool handled = eh.initial_error_handler(en_data);
      ASSERT_FALSE(handled);
      ASSERT_TRUE((eh.type == error_handler::ErrorType::NoError));
      ASSERT_TRUE((eh.category == error_handler::ErrorCategory::None));
      ASSERT_FALSE(eh.contact_nag);
      ASSERT_STRINGS_EQUAL(eh.fun_name, "test1");
      ASSERT_EQUAL(eh.ierr, 55);
      ASSERT_EQUAL(eh.ifmt, 55);
      ASSERT_EQUAL((int)eh.eb_data.size(), 3);
      ASSERT_STRINGS_EQUAL(eh.eb_data[0], "HELLO");
      ASSERT_STRINGS_EQUAL(eh.eb_data[1], "1.4");
      ASSERT_STRINGS_EQUAL(eh.eb_data[2], "5");
    }
  }
};
// clang-format off
REGISTER_TEST(test_initial_error_handler_routine, "Test initial_error_handler (routine specific error)");
// clang-format on

struct test_append_msg : public TestCase {
  void run() override {
    using namespace errbuf_setup;
    types::engine_data en_data;
    engine_routines::y90haan_(en_data);
    {
      error_handler::ErrorHandler eh;
      eh.errorid = 3;
      generate_errbuf(eh);
      bool handled = eh.initial_error_handler(en_data);
      eh.append_msg(true, "First line");
      eh.append_msg(true, "Second line");
      ASSERT_FALSE(handled);
      ASSERT_STRINGS_EQUAL(eh.msg, std::string("First line\nSecond line"));
    }
    {
      error_handler::ErrorHandler eh;
      eh.errorid = 5;
      generate_errbuf(eh, 3, "HELLO", 1.4, 5);
      bool handled = eh.initial_error_handler(en_data);
      eh.append_msg(true, "First line ", 1, " more ", 2);
      eh.append_msg(true, "Second line");
      eh.append_msg(true, 3, " more text");
      ASSERT_FALSE(handled);
      ASSERT_STRINGS_EQUAL(eh.msg, std::string("First line HELLO more "
                                               "1.4\nSecond line\n5 more "
                                               "text"));
    }
    {
      error_handler::ErrorHandler eh;
      eh.errorid = 5;
      generate_errbuf(eh, 3, "FFF", 4, "BBB");
      bool handled = eh.initial_error_handler(en_data);
      eh.append_msg(true, 2, "First line ", 3, " more ");
      eh.append_msg(true, 1, 2, "Second line", 3);
      eh.append_msg(true, " more text", " and then ", 2, "A", "B", "CC");
      ASSERT_FALSE(handled);
      ASSERT_STRINGS_EQUAL(eh.msg, std::string("4First line BBB more "
                                               "\nFFF4Second lineBBB\n more "
                                               "text "
                                               "and then 4ABCC"));
    }
  }
};
// clang-format off
REGISTER_TEST(test_append_msg, "Test append_msg");
// clang-format on

struct test_throw_error : public TestCase {
  void run() override {
    using namespace errbuf_setup;
    types::engine_data en_data;
    engine_routines::y90haan_(en_data);
    error_handler::ErrorHandler eh;
    eh.errorid = 5;
    generate_errbuf(eh, 2, "HELLO", 1.4);
    bool handled = eh.initial_error_handler(en_data);
    eh.append_msg(true, "First line ", 1, " more ", 2);
    eh.append_msg(true, "Second line");
    ASSERT_FALSE(handled);
    eh.category = error_handler::ErrorCategory::Error;
    eh.error_handler_type = error_handler::ErrorHandlerType::ThrowAll;
    eh.type = error_handler::ErrorType::GeneralError;
    {
      SUB_TEST("not class as error or warning (nothing thrown)");
      auto prev_value1 = eh.category;
      eh.category = error_handler::ErrorCategory::None;
      ASSERT_THROWS_NOTHING(eh.throw_error());
      ASSERT_FALSE(eh.error_thrown);
      ASSERT_FALSE(eh.warning_thrown);
      eh.category = prev_value1;
    }
    {
      SUB_TEST("error but nothing thrown");
      auto prev_value2 = eh.error_handler_type;
      eh.error_handler_type = error_handler::ErrorHandlerType::ThrowNothing;
      ASSERT_THROWS_NOTHING(eh.throw_error());
      ASSERT_TRUE(eh.error_thrown);
      ASSERT_FALSE(eh.warning_thrown);
      eh.error_handler_type = prev_value2;
    }
    {
      SUB_TEST("warning (should not be thrown)");
      auto prev_value1 = eh.category;
      auto prev_value2 = eh.error_handler_type;
      eh.category = error_handler::ErrorCategory::Warning;
      ASSERT_THROWS_NOTHING(eh.throw_error());
      ASSERT_FALSE(eh.error_thrown);
      ASSERT_TRUE(eh.warning_thrown);
      eh.category = prev_value1;
      eh.error_handler_type = prev_value2;
    }
    {
      SUB_TEST("error thrown");
      eh.set_calling_function("test1");
      ASSERT_THROWS(error_handler::ErrorException, eh.throw_error());
      ASSERT_THROWS(error_handler::Exception, eh.throw_error());
      try {
        eh.throw_error();
      } catch (error_handler::ErrorException &e) {
        ASSERT_STRINGS_EQUAL(e.fun_name, "test1");
        ASSERT_HAS_KEYWORD(e.msg, "Error");
        ASSERT_HAS_KEYWORD(e.msg, "test1");
        ASSERT_HAS_KEYWORD(e.msg, std::string("First line HELLO more "
                                              "1.4\nSecond "
                                              "line"));
        ASSERT_TRUE((e.category == error_handler::ErrorCategory::Error));
        ASSERT_TRUE((e.type == error_handler::ErrorType::GeneralError));
      }
      ASSERT_TRUE(eh.error_thrown);
      ASSERT_FALSE(eh.warning_thrown);
    }
  }
};
// clang-format off
REGISTER_TEST(test_throw_error, "Test throw_error");
// clang-format on

struct test_throw_warning : public TestCase {
  void run() override {
    using namespace errbuf_setup;
    types::engine_data en_data;
    engine_routines::y90haan_(en_data);
    error_handler::ErrorHandler eh;
    eh.errorid = 5;
    generate_errbuf(eh, 2, "HELLO", 1.4);
    bool handled = eh.initial_error_handler(en_data);
    eh.append_msg(true, "First line ", 1, " more ", 2);
    eh.append_msg(true, "Second line");
    ASSERT_FALSE(handled);
    eh.category = error_handler::ErrorCategory::Warning;
    eh.error_handler_type = error_handler::ErrorHandlerType::ThrowAll;
    eh.type = error_handler::ErrorType::GeneralWarning;
    ASSERT_THROWS_NOTHING(eh.throw_error());
    {
      SUB_TEST("warning not been flagged as having been thrown");
      auto prev_value1 = eh.warning_thrown;
      eh.warning_thrown = false;
      ASSERT_THROWS_NOTHING(eh.throw_warning());
      eh.warning_thrown = prev_value1;
    }
    {
      SUB_TEST("error, but not throwing anything");
      auto prev_value1 = eh.category;
      auto prev_value2 = eh.error_handler_type;
      eh.category = error_handler::ErrorCategory::Error;
      eh.error_handler_type = error_handler::ErrorHandlerType::ThrowNothing;
      ASSERT_THROWS_NOTHING(eh.throw_warning());
      eh.category = prev_value1;
      eh.error_handler_type = prev_value2;
    }
    {
      SUB_TEST("error, throwing all (this isn't thrown)");
      auto prev_value1 = eh.category;
      eh.category = error_handler::ErrorCategory::Error;
      ASSERT_THROWS_NOTHING(eh.throw_warning());
      eh.category = prev_value1;
    }

    {
      SUB_TEST("warning, but not throwing anything");
      auto prev_value2 = eh.error_handler_type;
      eh.error_handler_type = error_handler::ErrorHandlerType::ThrowNothing;
      ASSERT_THROWS_NOTHING(eh.throw_warning());
      eh.error_handler_type = prev_value2;
    }
    {
      SUB_TEST("warning thrown - void initializer");
      eh.set_calling_function("test1");
      ASSERT_THROWS(error_handler::WarningException, eh.throw_warning());
      ASSERT_THROWS(error_handler::Exception, eh.throw_warning());
      try {
        eh.throw_warning();
      } catch (error_handler::WarningException &e) {
        ASSERT_STRINGS_EQUAL(e.fun_name, "test1");
        ASSERT_HAS_KEYWORD(e.msg, "Warning");
        ASSERT_HAS_KEYWORD(e.msg, "test1");
        ASSERT_HAS_KEYWORD(e.msg, std::string("First line HELLO more "
                                              "1.4\nSecond "
                                              "line"));
        ASSERT_TRUE((e.category == error_handler::ErrorCategory::Warning));
        ASSERT_TRUE((e.type == error_handler::ErrorType::GeneralWarning));
      }
    }
    {
      SUB_TEST("warning thrown - double value");
      eh.set_calling_function("test2");
      double ret_val = 3.3123;
      ASSERT_THROWS(error_handler::WarningException, eh.throw_warning(ret_val));
      ASSERT_THROWS(error_handler::Exception, eh.throw_warning(ret_val));
      try {
        eh.throw_warning(ret_val);
      } catch (error_handler::WarningException &e) {
        ASSERT_STRINGS_EQUAL(e.fun_name, "test2");
        ASSERT_HAS_KEYWORD(e.msg, "Warning");
        ASSERT_HAS_KEYWORD(e.msg, "test2");
        ASSERT_HAS_KEYWORD(e.msg, std::string("First line HELLO more "
                                              "1.4\nSecond "
                                              "line"));
        ASSERT_TRUE((e.category == error_handler::ErrorCategory::Warning));
        ASSERT_TRUE((e.type == error_handler::ErrorType::GeneralWarning));
        ASSERT_EQUAL(e.return_value<double>(), ret_val);
      }
    }
    {
      SUB_TEST("warning thrown - int value");
      eh.set_calling_function("test3");
      int ret_val = 333;
      ASSERT_THROWS(error_handler::WarningException, eh.throw_warning(ret_val));
      ASSERT_THROWS(error_handler::Exception, eh.throw_warning(ret_val));
      try {
        eh.throw_warning(ret_val);
      } catch (error_handler::WarningException &e) {
        ASSERT_STRINGS_EQUAL(e.fun_name, "test3");
        ASSERT_HAS_KEYWORD(e.msg, "Warning");
        ASSERT_HAS_KEYWORD(e.msg, "test3");
        ASSERT_HAS_KEYWORD(e.msg, std::string("First line HELLO more "
                                              "1.4\nSecond "
                                              "line"));
        ASSERT_TRUE((e.category == error_handler::ErrorCategory::Warning));
        ASSERT_TRUE((e.type == error_handler::ErrorType::GeneralWarning));
        ASSERT_EQUAL(e.return_value<int>(), ret_val);
      }
    }
  }
};
// clang-format off
REGISTER_TEST(test_throw_warning, "Test throw_warning");
// clang-format on

struct test_raise_error_array_null : public TestCase {
  void run() override {
    {
      error_handler::ErrorHandler eh;
      eh.error_handler_type = error_handler::ErrorHandlerType::ThrowNothing;
      eh.raise_error_array_null("FRED");
      ASSERT_HAS_KEYWORD(eh.msg, "FRED");
      ASSERT_HAS_KEYWORD(eh.msg, "is null");
      ASSERT_TRUE((eh.type == error_handler::ErrorType::GenericError));
      ASSERT_TRUE((eh.category == error_handler::ErrorCategory::Error));
      ASSERT_EQUAL(eh.errorid, error_handler::IERR_ARRAY_NULL);
    }
    {
      error_handler::ErrorHandler eh;
      eh.error_handler_type = error_handler::ErrorHandlerType::ThrowAll;
      ASSERT_THROWS(error_handler::Exception, eh.raise_error_array_null("FRE"
                                                                        "D"));
    }
  }
};
// clang-format off
REGISTER_TEST(test_raise_error_array_null, "Test raise_error_array_null");
// clang-format on

struct test_raise_error_array_sorder : public TestCase {
  void run() override {
    {
      error_handler::ErrorHandler eh;
      eh.error_handler_type = error_handler::ErrorHandlerType::ThrowNothing;
      eh.raise_error_array_sorder("FRED", constants::NAG_ED_COL_MAJOR,
                                  constants::NAG_ED_ROW_MAJOR);
      ASSERT_HAS_KEYWORD(eh.msg, "FRED");
      ASSERT_HAS_KEYWORD(eh.msg, "stored in Row Major");
      ASSERT_HAS_KEYWORD(eh.msg, "expected to be in Column Major");
      ASSERT_TRUE((eh.type == error_handler::ErrorType::GenericError));
      ASSERT_TRUE((eh.category == error_handler::ErrorCategory::Error));
      ASSERT_EQUAL(eh.errorid, error_handler::IERR_ARRAY_SORDER);
    }
    {
      error_handler::ErrorHandler eh;
      eh.error_handler_type = error_handler::ErrorHandlerType::ThrowAll;
      ASSERT_THROWS(error_handler::Exception,
                    eh.raise_error_array_sorder("FRED",
                                                constants::NAG_ED_COL_MAJOR,
                                                constants::NAG_ED_ROW_MAJOR));
    }
  }
};
// clang-format off
REGISTER_TEST(test_raise_error_array_sorder, "Test raise_error_array_sorder");
// clang-format on

struct test_raise_error_no_size_info : public TestCase {
  void run() override {
    {
      error_handler::ErrorHandler eh;
      eh.error_handler_type = error_handler::ErrorHandlerType::ThrowNothing;
      eh.raise_error_no_size_info("FRED");
      ASSERT_HAS_KEYWORD(eh.msg, "FRED");
      ASSERT_HAS_KEYWORD(eh.msg, "unable to ascertain");
      ASSERT_TRUE((eh.type == error_handler::ErrorType::GenericError));
      ASSERT_TRUE((eh.category == error_handler::ErrorCategory::Error));
      ASSERT_EQUAL(eh.errorid, error_handler::IERR_ARRAY_NO_SIZE_INFO);
    }
    {
      error_handler::ErrorHandler eh;
      eh.error_handler_type = error_handler::ErrorHandlerType::ThrowAll;
      ASSERT_THROWS(error_handler::Exception, eh.raise_error_no_size_info("FRE"
                                                                          "D"));
    }
  }
};
// clang-format off
REGISTER_TEST(test_raise_error_no_size_info, "Test raise_error_no_size_info");
// clang-format on

struct test_is_error_array_size_1 : public TestCase {
  class AA0 {
    int n;

  public:
    AA0(int n_) : n(n_) {}
    int ndims(void) { return n; }
  };
  class AA1 {
    int n;

  public:
    AA1(int n_) : n(n_) {}
    int size1(void) { return n; }
  };
  void run() override {
    AA0 a0(1);
    auto ndims_0 = data_handling::getNDims(a0, 0);
    auto size1_0 = data_handling::getDim1(a0, 0);
    types::f77_integer esize1_0 = 99;

    AA1 a1(5);
    auto ndims_1 = data_handling::getNDims(a1, 0);
    auto size1_1 = data_handling::getDim1(a1, 0);
    types::f77_integer esize1_1 = static_cast<types::f77_integer>(a1.size1());

    {
      SUB_TEST("size1 missing, ignoring missing");
      error_handler::ErrorHandler eh;
      eh.error_handler_type = error_handler::ErrorHandlerType::ThrowNothing;
      eh.invalid_meta = error_handler::HandleInvalidMetaInfo::IgnoreMissing;
      bool is_error =
        eh.is_error_array_size("FRED", ndims_0, size1_0, esize1_0);
      ASSERT_FALSE(is_error);
      ASSERT_TRUE((eh.category == error_handler::ErrorCategory::None));
      ASSERT_FALSE(eh.error_thrown);
      ASSERT_FALSE(eh.warning_thrown);
      ASSERT_EQUAL(eh.errorid, 0);
    }
    {
      SUB_TEST("size1 missing, missing as warnings");
      error_handler::ErrorHandler eh;
      eh.error_handler_type = error_handler::ErrorHandlerType::ThrowNothing;
      eh.invalid_meta = error_handler::HandleInvalidMetaInfo::MissingAsWarning;
      bool is_error =
        eh.is_error_array_size("HARRY", ndims_0, size1_0, esize1_0);
      ASSERT_FALSE(is_error);
      ASSERT_FALSE(eh.error_thrown);
      ASSERT_TRUE(eh.warning_thrown);
      ASSERT_HAS_KEYWORD(eh.msg, "HARRY");
      ASSERT_HAS_KEYWORD(eh.msg, "vector");
      ASSERT_HAS_KEYWORD(eh.msg, "ascertained");
      ASSERT_EQUAL(eh.errorid, error_handler::IERR_ARRAY_SIZE_INVALID);
    }
    {
      SUB_TEST("size1 missing, ndims is wrong, missing as warnings - should "
               "report an error");
      error_handler::ErrorHandler eh;
      eh.error_handler_type = error_handler::ErrorHandlerType::ThrowNothing;
      eh.invalid_meta = error_handler::HandleInvalidMetaInfo::MissingAsWarning;
      bool is_error =
        eh.is_error_array_size("HARRY2", size1_1, size1_0, esize1_0);
      ASSERT_TRUE(is_error);
      ASSERT_TRUE(eh.error_thrown);
      ASSERT_FALSE(eh.warning_thrown);
      ASSERT_HAS_KEYWORD(eh.msg, "HARRY2");
      ASSERT_HAS_KEYWORD(eh.msg, "vector");
      std::string expected_phrase =
        std::to_string(size1_1.value) + " dimension";
      ASSERT_HAS_KEYWORD(eh.msg, expected_phrase);
      ASSERT_EQUAL(eh.errorid, error_handler::IERR_ARRAY_SIZE_INVALID);
    }
    {
      SUB_TEST("size1 missing, ndims is wrong, ignore everything");
      error_handler::ErrorHandler eh;
      eh.error_handler_type = error_handler::ErrorHandlerType::ThrowNothing;
      eh.invalid_meta = error_handler::HandleInvalidMetaInfo::Ignore;
      bool is_error =
        eh.is_error_array_size("HARRY3", size1_1, size1_0, esize1_0);
      ASSERT_FALSE(is_error);
      ASSERT_FALSE(eh.error_thrown);
      ASSERT_FALSE(eh.warning_thrown);
      ASSERT_EQUAL(eh.errorid, 0);
    }
    {
      SUB_TEST("size1 missing, missing as errors");
      error_handler::ErrorHandler eh;
      eh.error_handler_type = error_handler::ErrorHandlerType::ThrowNothing;
      eh.invalid_meta = error_handler::HandleInvalidMetaInfo::MissingAsError;
      bool is_error =
        eh.is_error_array_size("GEORGE", ndims_0, size1_0, esize1_0);
      ASSERT_TRUE(is_error);
      ASSERT_TRUE(eh.error_thrown);
      ASSERT_FALSE(eh.warning_thrown);
      ASSERT_HAS_KEYWORD(eh.msg, "GEORGE");
      ASSERT_HAS_KEYWORD(eh.msg, "vector");
      ASSERT_HAS_KEYWORD(eh.msg, "ascertained");
      ASSERT_EQUAL(eh.errorid, error_handler::IERR_ARRAY_SIZE_INVALID);
    }
    {
      SUB_TEST("size1 wrong");
      error_handler::ErrorHandler eh;
      eh.error_handler_type = error_handler::ErrorHandlerType::ThrowNothing;
      eh.invalid_meta = error_handler::HandleInvalidMetaInfo::MissingAsError;
      bool is_error =
        eh.is_error_array_size("GEORGE", ndims_1, size1_1, esize1_0);
      ASSERT_TRUE(is_error);
      ASSERT_TRUE(eh.error_thrown);
      ASSERT_FALSE(eh.warning_thrown);
      ASSERT_HAS_KEYWORD(eh.msg, "GEORGE");
      ASSERT_HAS_KEYWORD(eh.msg, "vector");
      ASSERT_NO_KEYWORD(eh.msg, "ascertained");
      ASSERT_EQUAL(eh.errorid, error_handler::IERR_ARRAY_SIZE_INVALID);
    }
    {
      SUB_TEST("ndims wrong");
      AA0 a2(4);
      auto ndims_2 = data_handling::getNDims(a2, 0);
      error_handler::ErrorHandler eh;
      eh.error_handler_type = error_handler::ErrorHandlerType::ThrowNothing;
      eh.invalid_meta = error_handler::HandleInvalidMetaInfo::MissingAsError;
      bool is_error =
        eh.is_error_array_size("GEORGE", ndims_2, size1_1, esize1_0);
      ASSERT_TRUE(is_error);
      ASSERT_TRUE(eh.error_thrown);
      ASSERT_FALSE(eh.warning_thrown);
      ASSERT_EQUAL(eh.errorid, error_handler::IERR_ARRAY_SIZE_INVALID);
    }
    {
      SUB_TEST("everything OK - dont throw errors");
      error_handler::ErrorHandler eh;
      eh.error_handler_type = error_handler::ErrorHandlerType::ThrowNothing;
      bool is_error =
        eh.is_error_array_size("GEORGE", ndims_1, size1_1, esize1_1);
      ASSERT_FALSE(is_error);
      ASSERT_FALSE(eh.error_thrown);
      ASSERT_FALSE(eh.warning_thrown);
      ASSERT_EQUAL(eh.errorid, 0);
    }
    {
      SUB_TEST("everything OK - throw errors");
      error_handler::ErrorHandler eh;
      eh.error_handler_type = error_handler::ErrorHandlerType::ThrowAll;
      ASSERT_THROWS_NOTHING(
        eh.is_error_array_size("GEORGE", ndims_1, size1_1, esize1_1));
    }
    {
      SUB_TEST("size1 wrong - throws errors");
      error_handler::ErrorHandler eh;
      eh.error_handler_type = error_handler::ErrorHandlerType::ThrowAll;
      ASSERT_THROWS(error_handler::Exception,
                    eh.is_error_array_size("GEORGE", ndims_1, size1_1,
                                           esize1_0));
    }
  }
};
// clang-format off
REGISTER_TEST(test_is_error_array_size_1, "Test is_error_array_size_1");
// clang-format on

struct test_is_error_array_size_2 : public TestCase {
  class AA0 {
    int n;

  public:
    AA0(int n_) : n(n_) {}
    int ndims(void) { return n; }
  };
  class AA1 {
    int n1, n2;

  public:
    AA1(int n1_, int n2_) : n1(n1_), n2(n2_) {}
    int size1(void) { return n1; }
    int size2(void) { return n2; }
  };
  void run() override {
    AA0 a0(2);
    auto ndims_0 = data_handling::getNDims(a0, 0);
    auto size1_0 = data_handling::getDim1(a0, 0);
    auto size2_0 = data_handling::getDim2(a0, 0);
    types::f77_integer esize1_0 = 99;
    types::f77_integer esize2_0 = 99;

    AA1 a1(5, 6);
    auto ndims_1 = data_handling::getNDims(a1, 0);
    auto size1_1 = data_handling::getDim1(a1, 0);
    auto size2_1 = data_handling::getDim2(a1, 0);
    types::f77_integer esize1_1 = static_cast<types::f77_integer>(a1.size1());
    types::f77_integer esize2_1 = static_cast<types::f77_integer>(a1.size2());

    {
      SUB_TEST("sizes missing, ignoring missing");
      error_handler::ErrorHandler eh;
      eh.error_handler_type = error_handler::ErrorHandlerType::ThrowNothing;
      eh.invalid_meta = error_handler::HandleInvalidMetaInfo::IgnoreMissing;
      bool is_error = eh.is_error_array_size("FRED", ndims_0, size1_0, esize1_0,
                                             size2_0, esize2_0);
      ASSERT_FALSE(is_error);
      ASSERT_TRUE((eh.category == error_handler::ErrorCategory::None));
      ASSERT_FALSE(eh.error_thrown);
      ASSERT_FALSE(eh.warning_thrown);
      ASSERT_EQUAL(eh.errorid, 0);
    }
    {
      SUB_TEST("size1 missing, missing as warnings");
      error_handler::ErrorHandler eh;
      eh.error_handler_type = error_handler::ErrorHandlerType::ThrowNothing;
      eh.invalid_meta = error_handler::HandleInvalidMetaInfo::MissingAsWarning;
      bool is_error = eh.is_error_array_size("HARRY", ndims_0, size1_0,
                                             esize1_0, size2_0, esize2_0);
      ASSERT_FALSE(is_error);
      ASSERT_FALSE(eh.error_thrown);
      ASSERT_TRUE(eh.warning_thrown);
      ASSERT_HAS_KEYWORD(eh.msg, "HARRY");
      ASSERT_HAS_KEYWORD(eh.msg, "array");
      ASSERT_HAS_KEYWORD(eh.msg, "ascertained");
      ASSERT_EQUAL(eh.errorid, error_handler::IERR_ARRAY_SIZE_INVALID);
    }
    {
      SUB_TEST("size1 missing, ndims is wrong, missing as warnings - should "
               "report an error");
      error_handler::ErrorHandler eh;
      eh.error_handler_type = error_handler::ErrorHandlerType::ThrowNothing;
      eh.invalid_meta = error_handler::HandleInvalidMetaInfo::MissingAsWarning;
      bool is_error = eh.is_error_array_size("HARRY2", size1_1, size1_0,
                                             esize1_0, size2_0, esize2_0);
      ASSERT_TRUE(is_error);
      ASSERT_TRUE(eh.error_thrown);
      ASSERT_FALSE(eh.warning_thrown);
      ASSERT_HAS_KEYWORD(eh.msg, "HARRY2");
      ASSERT_HAS_KEYWORD(eh.msg, "array");
      std::string expected_phrase =
        std::to_string(size1_1.value) + " dimension";
      ASSERT_HAS_KEYWORD(eh.msg, expected_phrase);
      ASSERT_EQUAL(eh.errorid, error_handler::IERR_ARRAY_SIZE_INVALID);
    }
    {
      SUB_TEST("size1 missing, ndims is wrong, ignore everything");
      error_handler::ErrorHandler eh;
      eh.error_handler_type = error_handler::ErrorHandlerType::ThrowNothing;
      eh.invalid_meta = error_handler::HandleInvalidMetaInfo::Ignore;
      bool is_error = eh.is_error_array_size("HARRY3", size1_1, size1_0,
                                             esize1_0, size2_0, esize2_0);
      ASSERT_FALSE(is_error);
      ASSERT_FALSE(eh.error_thrown);
      ASSERT_FALSE(eh.warning_thrown);
      ASSERT_EQUAL(eh.errorid, 0);
    }
    {
      SUB_TEST("size1 missing, missing as errors");
      error_handler::ErrorHandler eh;
      eh.error_handler_type = error_handler::ErrorHandlerType::ThrowNothing;
      eh.invalid_meta = error_handler::HandleInvalidMetaInfo::MissingAsError;
      bool is_error = eh.is_error_array_size("GEORGE", ndims_0, size1_0,
                                             esize1_0, size2_0, esize2_0);
      ASSERT_TRUE(is_error);
      ASSERT_TRUE(eh.error_thrown);
      ASSERT_FALSE(eh.warning_thrown);
      ASSERT_HAS_KEYWORD(eh.msg, "GEORGE");
      ASSERT_HAS_KEYWORD(eh.msg, "array");
      ASSERT_HAS_KEYWORD(eh.msg, "ascertained");
      ASSERT_EQUAL(eh.errorid, error_handler::IERR_ARRAY_SIZE_INVALID);
    }
    {
      SUB_TEST("size1 wrong");
      error_handler::ErrorHandler eh;
      eh.error_handler_type = error_handler::ErrorHandlerType::ThrowNothing;
      eh.invalid_meta = error_handler::HandleInvalidMetaInfo::MissingAsError;
      bool is_error = eh.is_error_array_size("GEORGE", ndims_1, size1_1,
                                             esize1_0, size2_1, esize2_1);
      ASSERT_TRUE(is_error);
      ASSERT_TRUE(eh.error_thrown);
      ASSERT_FALSE(eh.warning_thrown);
      ASSERT_HAS_KEYWORD(eh.msg, "GEORGE");
      ASSERT_HAS_KEYWORD(eh.msg, "array");
      ASSERT_NO_KEYWORD(eh.msg, "ascertained");
      ASSERT_EQUAL(eh.errorid, error_handler::IERR_ARRAY_SIZE_INVALID);
    }
    {
      SUB_TEST("size2 wrong");
      error_handler::ErrorHandler eh;
      eh.error_handler_type = error_handler::ErrorHandlerType::ThrowNothing;
      eh.invalid_meta = error_handler::HandleInvalidMetaInfo::MissingAsError;
      bool is_error = eh.is_error_array_size("GEORGE", ndims_1, size1_1,
                                             esize1_1, size2_1, esize2_0);
      ASSERT_TRUE(is_error);
      ASSERT_TRUE(eh.error_thrown);
      ASSERT_FALSE(eh.warning_thrown);
      ASSERT_EQUAL(eh.errorid, error_handler::IERR_ARRAY_SIZE_INVALID);
    }
    {
      SUB_TEST("ndims wrong");
      AA0 a2(4);
      auto ndims_2 = data_handling::getNDims(a2, 0);
      error_handler::ErrorHandler eh;
      eh.error_handler_type = error_handler::ErrorHandlerType::ThrowNothing;
      eh.invalid_meta = error_handler::HandleInvalidMetaInfo::MissingAsError;
      bool is_error = eh.is_error_array_size("GEORGE", ndims_2, size1_1,
                                             esize1_1, size2_1, esize2_0);
      ASSERT_TRUE(is_error);
      ASSERT_TRUE(eh.error_thrown);
      ASSERT_FALSE(eh.warning_thrown);
      ASSERT_EQUAL(eh.errorid, error_handler::IERR_ARRAY_SIZE_INVALID);
    }
    {
      SUB_TEST("everything OK - dont throw errors");
      error_handler::ErrorHandler eh;
      eh.error_handler_type = error_handler::ErrorHandlerType::ThrowNothing;
      bool is_error = eh.is_error_array_size("GEORGE", ndims_1, size1_1,
                                             esize1_1, size2_1, esize2_1);
      ASSERT_FALSE(is_error);
      ASSERT_FALSE(eh.error_thrown);
      ASSERT_FALSE(eh.warning_thrown);
      ASSERT_EQUAL(eh.errorid, 0);
    }
    {
      SUB_TEST("everything OK - throw errors");
      error_handler::ErrorHandler eh;
      eh.error_handler_type = error_handler::ErrorHandlerType::ThrowAll;
      ASSERT_THROWS_NOTHING(eh.is_error_array_size(
        "GEORGE", ndims_1, size1_1, esize1_1, size2_1, esize2_1));
    }
    {
      SUB_TEST("size1 wrong - throws errors");
      error_handler::ErrorHandler eh;
      eh.error_handler_type = error_handler::ErrorHandlerType::ThrowAll;
      ASSERT_THROWS(error_handler::Exception,
                    eh.is_error_array_size("GEORGE", ndims_1, size1_1, esize1_0,
                                           size2_1, esize2_1));
    }
  }
};
// clang-format off
REGISTER_TEST(test_is_error_array_size_2, "Test is_error_array_size_2");
// clang-format on

struct test_is_error_array_size_3 : public TestCase {
  class AA0 {
    int n;

  public:
    AA0(int n_) : n(n_) {}
    int ndims(void) { return n; }
  };
  class AA1 {
    int n1, n2, n3;

  public:
    AA1(int n1_, int n2_, int n3_) : n1(n1_), n2(n2_), n3(n3_) {}
    int size1(void) { return n1; }
    int size2(void) { return n2; }
    int size3(void) { return n3; }
  };
  void run() override {
    AA0 a0(3);
    auto ndims_0 = data_handling::getNDims(a0, 0);
    auto size1_0 = data_handling::getDim1(a0, 0);
    auto size2_0 = data_handling::getDim2(a0, 0);
    auto size3_0 = data_handling::getDim3(a0, 0);
    types::f77_integer esize1_0 = 99;
    types::f77_integer esize2_0 = 99;
    types::f77_integer esize3_0 = 99;

    AA1 a1(5, 6, 7);
    auto ndims_1 = data_handling::getNDims(a1, 0);
    auto size1_1 = data_handling::getDim1(a1, 0);
    auto size2_1 = data_handling::getDim2(a1, 0);
    auto size3_1 = data_handling::getDim3(a1, 0);
    types::f77_integer esize1_1 = static_cast<types::f77_integer>(a1.size1());
    types::f77_integer esize2_1 = static_cast<types::f77_integer>(a1.size2());
    types::f77_integer esize3_1 = static_cast<types::f77_integer>(a1.size3());

    {
      SUB_TEST("sizes missing, ignoring missing");
      error_handler::ErrorHandler eh;
      eh.error_handler_type = error_handler::ErrorHandlerType::ThrowNothing;
      eh.invalid_meta = error_handler::HandleInvalidMetaInfo::IgnoreMissing;
      bool is_error =
        eh.is_error_array_size("FRED", ndims_0, size1_0, esize1_0, size2_0,
                               esize2_0, size3_0, esize3_0);
      ASSERT_FALSE(is_error);
      ASSERT_TRUE((eh.category == error_handler::ErrorCategory::None));
      ASSERT_FALSE(eh.error_thrown);
      ASSERT_FALSE(eh.warning_thrown);
      ASSERT_EQUAL(eh.errorid, 0);
    }
    {
      SUB_TEST("size1 missing, missing as warnings");
      error_handler::ErrorHandler eh;
      eh.error_handler_type = error_handler::ErrorHandlerType::ThrowNothing;
      eh.invalid_meta = error_handler::HandleInvalidMetaInfo::MissingAsWarning;
      bool is_error =
        eh.is_error_array_size("HARRY", ndims_0, size1_0, esize1_0, size2_0,
                               esize2_0, size3_0, esize3_0);
      ASSERT_FALSE(is_error);
      ASSERT_FALSE(eh.error_thrown);
      ASSERT_TRUE(eh.warning_thrown);
      ASSERT_HAS_KEYWORD(eh.msg, "HARRY");
      ASSERT_HAS_KEYWORD(eh.msg, "array");
      ASSERT_HAS_KEYWORD(eh.msg, "ascertained");
      ASSERT_EQUAL(eh.errorid, error_handler::IERR_ARRAY_SIZE_INVALID);
    }
    {
      SUB_TEST("size1 missing, ndims is wrong, missing as warnings - should "
               "report an error");
      error_handler::ErrorHandler eh;
      eh.error_handler_type = error_handler::ErrorHandlerType::ThrowNothing;
      eh.invalid_meta = error_handler::HandleInvalidMetaInfo::MissingAsWarning;
      bool is_error =
        eh.is_error_array_size("HARRY2", size1_1, size1_0, esize1_0, size2_0,
                               esize2_0, size3_0, esize3_0);
      ASSERT_TRUE(is_error);
      ASSERT_TRUE(eh.error_thrown);
      ASSERT_FALSE(eh.warning_thrown);
      ASSERT_HAS_KEYWORD(eh.msg, "HARRY2");
      ASSERT_HAS_KEYWORD(eh.msg, "array");
      std::string expected_phrase =
        std::to_string(size1_1.value) + " dimension";
      ASSERT_HAS_KEYWORD(eh.msg, expected_phrase);
      ASSERT_EQUAL(eh.errorid, error_handler::IERR_ARRAY_SIZE_INVALID);
    }
    {
      SUB_TEST("size1 missing, ndims is wrong, ignore everything");
      error_handler::ErrorHandler eh;
      eh.error_handler_type = error_handler::ErrorHandlerType::ThrowNothing;
      eh.invalid_meta = error_handler::HandleInvalidMetaInfo::Ignore;
      bool is_error =
        eh.is_error_array_size("HARRY3", size1_1, size1_0, esize1_0, size2_0,
                               esize2_0, size3_0, esize3_0);
      ASSERT_FALSE(is_error);
      ASSERT_FALSE(eh.error_thrown);
      ASSERT_FALSE(eh.warning_thrown);
      ASSERT_EQUAL(eh.errorid, 0);
    }
    {
      SUB_TEST("size1 missing, missing as errors");
      error_handler::ErrorHandler eh;
      eh.error_handler_type = error_handler::ErrorHandlerType::ThrowNothing;
      eh.invalid_meta = error_handler::HandleInvalidMetaInfo::MissingAsError;
      bool is_error =
        eh.is_error_array_size("GEORGE", ndims_0, size1_0, esize1_0, size2_0,
                               esize2_0, size3_0, esize3_0);
      ASSERT_TRUE(is_error);
      ASSERT_TRUE(eh.error_thrown);
      ASSERT_FALSE(eh.warning_thrown);
      ASSERT_HAS_KEYWORD(eh.msg, "GEORGE");
      ASSERT_HAS_KEYWORD(eh.msg, "array");
      ASSERT_HAS_KEYWORD(eh.msg, "ascertained");
      ASSERT_EQUAL(eh.errorid, error_handler::IERR_ARRAY_SIZE_INVALID);
    }
    {
      SUB_TEST("size1 wrong");
      error_handler::ErrorHandler eh;
      eh.error_handler_type = error_handler::ErrorHandlerType::ThrowNothing;
      eh.invalid_meta = error_handler::HandleInvalidMetaInfo::MissingAsError;
      bool is_error =
        eh.is_error_array_size("GEORGE", ndims_1, size1_1, esize1_0, size2_1,
                               esize2_1, size3_1, esize3_1);
      ASSERT_TRUE(is_error);
      ASSERT_TRUE(eh.error_thrown);
      ASSERT_FALSE(eh.warning_thrown);
      ASSERT_HAS_KEYWORD(eh.msg, "GEORGE");
      ASSERT_HAS_KEYWORD(eh.msg, "array");
      ASSERT_NO_KEYWORD(eh.msg, "ascertained");
      ASSERT_EQUAL(eh.errorid, error_handler::IERR_ARRAY_SIZE_INVALID);
    }
    {
      SUB_TEST("size2 wrong");
      error_handler::ErrorHandler eh;
      eh.error_handler_type = error_handler::ErrorHandlerType::ThrowNothing;
      eh.invalid_meta = error_handler::HandleInvalidMetaInfo::MissingAsError;
      bool is_error =
        eh.is_error_array_size("GEORGE", ndims_1, size1_1, esize1_1, size2_1,
                               esize2_0, size3_1, esize3_1);
      ASSERT_TRUE(is_error);
      ASSERT_TRUE(eh.error_thrown);
      ASSERT_FALSE(eh.warning_thrown);
      ASSERT_EQUAL(eh.errorid, error_handler::IERR_ARRAY_SIZE_INVALID);
    }
    {
      SUB_TEST("size3 wrong");
      error_handler::ErrorHandler eh;
      eh.error_handler_type = error_handler::ErrorHandlerType::ThrowNothing;
      eh.invalid_meta = error_handler::HandleInvalidMetaInfo::MissingAsError;
      bool is_error =
        eh.is_error_array_size("GEORGE", ndims_1, size1_1, esize1_1, size2_1,
                               esize2_1, size3_1, esize3_0);
      ASSERT_TRUE(is_error);
      ASSERT_TRUE(eh.error_thrown);
      ASSERT_FALSE(eh.warning_thrown);
      ASSERT_EQUAL(eh.errorid, error_handler::IERR_ARRAY_SIZE_INVALID);
    }
    {
      SUB_TEST("ndims wrong");
      AA0 a2(5);
      auto ndims_2 = data_handling::getNDims(a2, 0);
      error_handler::ErrorHandler eh;
      eh.error_handler_type = error_handler::ErrorHandlerType::ThrowNothing;
      eh.invalid_meta = error_handler::HandleInvalidMetaInfo::MissingAsError;
      bool is_error =
        eh.is_error_array_size("GEORGE", ndims_2, size1_1, esize1_0, size2_1,
                               esize2_1, size3_1, esize3_1);
      ASSERT_TRUE(is_error);
      ASSERT_TRUE(eh.error_thrown);
      ASSERT_FALSE(eh.warning_thrown);
      ASSERT_EQUAL(eh.errorid, error_handler::IERR_ARRAY_SIZE_INVALID);
    }
    {
      SUB_TEST("everything OK - dont throw errors");
      error_handler::ErrorHandler eh;
      eh.error_handler_type = error_handler::ErrorHandlerType::ThrowNothing;
      bool is_error =
        eh.is_error_array_size("GEORGE", ndims_1, size1_1, esize1_1, size2_1,
                               esize2_1, size3_1, esize3_1);
      ASSERT_FALSE(is_error);
      ASSERT_FALSE(eh.error_thrown);
      ASSERT_FALSE(eh.warning_thrown);
      ASSERT_EQUAL(eh.errorid, 0);
    }
    {
      SUB_TEST("everything OK - throw errors");
      error_handler::ErrorHandler eh;
      eh.error_handler_type = error_handler::ErrorHandlerType::ThrowAll;
      ASSERT_THROWS_NOTHING(eh.is_error_array_size("GEORGE", ndims_1, size1_1,
                                                   esize1_1, size2_1, esize2_1,
                                                   size3_1, esize3_1));
    }
    {
      SUB_TEST("size1 wrong - throws errors");
      error_handler::ErrorHandler eh;
      eh.error_handler_type = error_handler::ErrorHandlerType::ThrowAll;
      ASSERT_THROWS(error_handler::Exception,
                    eh.is_error_array_size("GEORGE", ndims_1, size1_1, esize1_0,
                                           size2_1, esize2_1, size3_1,
                                           esize3_1));
    }
  }
};
// clang-format off
REGISTER_TEST(test_is_error_array_size_3, "Test is_error_array_size_3");
// clang-format on
