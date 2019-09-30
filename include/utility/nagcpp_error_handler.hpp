#ifndef NAGCPP_ERROR_HANDLER_HPP
#define NAGCPP_ERROR_HANDLER_HPP

#include <algorithm>
#include <regex>
#include <string>
#include <vector>

#include "nagcpp_consts.hpp"
#include "nagcpp_data_handling_array_info.hpp"
#include "nagcpp_engine_types.hpp"

namespace nagcpp {
  namespace error_handler {
    static const types::f77_integer IERR_ALLOC_FAIL = -999;
    static const types::f77_integer IERR_NO_LIC = -399;
    static const types::f77_integer IERR_UNEXPECTED = -99;
    static const types::f77_integer IERR_SUCCESS = 0;

    static const types::f77_integer IERR_HLPERR_USER_EXCEPTION = 10701;
    static const types::f77_integer IERR_HLPERR_ARRAY_POINTER_CHANGED = 10702;
    static const types::f77_integer IERR_HLPERR_PRINT_REC_EXCEPTION = 10703;
    static const types::f77_integer IERR_HLPERR_READ_REC_EXCEPTION = 10704;

    static const types::f77_integer IERR_ARRAY_ERROR_IFMT = -1111;
    static const types::f77_integer IERR_CALLBACK_ERROR_IFMT = -1112;
    static const types::f77_integer IERR_COMM_ERROR_IFMT = -1113;
    static const types::f77_integer IERR_VALUE_ERROR_IFMT = -1114;
    static const types::f77_integer IERR_OPTIONAL_GROUP_IFMT = -1115;

    static const types::f77_integer IERR_ARRAY_SIZE_INVALID = 10601;
    static const types::f77_integer IERR_ARRAY_NULL = 10602;
    static const types::f77_integer IERR_ARRAY_NO_SIZE_INFO = 10603;
    static const types::f77_integer IERR_ARRAY_SORDER = 10604;
    static const types::f77_integer IERR_COMM_INVALID = 10605;
    static const types::f77_integer IERR_VALUE_NOT_AVAILABLE = 10606;
    static const types::f77_integer IERR_OPTIONAL_GROUP = 10607;

    static const types::f77_integer IERR_IOMANAGER_TOO_MANY_UNIT_NUMBERS =
      20001;

    // these need to tie up with cpp-common-constants.xsl ...
    const types::c_int HLPERR_SUCCESS = 0;
    const types::c_int HLPERR_USER_EXCEPTION =
      static_cast<types::c_int>(IERR_HLPERR_USER_EXCEPTION);
    const types::c_int HLPERR_ARRAY_POINTER_CHANGED =
      static_cast<types::c_int>(IERR_HLPERR_ARRAY_POINTER_CHANGED);
    const types::c_int HLPERR_PRINT_REC_EXCEPTION =
      static_cast<types::c_int>(IERR_HLPERR_PRINT_REC_EXCEPTION);
    const types::c_int HLPERR_READ_REC_EXCEPTION =
      static_cast<types::c_int>(IERR_HLPERR_READ_REC_EXCEPTION);
    // ... these need to tie up with cpp-common-constants.xsl

    // string used in error messages if requested data is not in errbuf
    const std::string unknown_data_msg = "<UNKNOWN DATA>";
    // ASCII character 1 is used as a delimiter in errbuf
    const char errbuf_delim(1);

    enum class ErrorType {
      NoError,
      MemoryError,
      LicenceError,
      UnexpectedError,
      GeneralError,
      GeneralWarning,
      CallbackError,
      GenericError
    };
    enum class ErrorCategory { None, Error, Warning };
    enum class ErrorHandlerType { ThrowNothing, ThrowErrors, ThrowAll };
    enum class HandleInvalidMetaInfo {
      MissingAsError,
      MissingAsWarning,
      IgnoreMissing,
      Ignore
    };

    struct ExceptionPointer {
      std::exception_ptr eptr;
    };

    class Exception : public std::exception {
    public:
      ErrorCategory category;
      std::string fun_name;
      std::string msg;
      ErrorType type;
      types::f77_integer errorid;
      types::f77_integer ierr;
      types::f77_integer ifmt;

      Exception(ErrorCategory category_, std::string fun_name_,
                std::string msg_, ErrorType type_, types::f77_integer errorid_,
                types::f77_integer ierr_, types::f77_integer ifmt_)
        : category(category_), fun_name(fun_name_), msg(msg_), type(type_),
          errorid(errorid_), ierr(ierr_), ifmt(ifmt_) {}
      const char *what() const noexcept { return msg.c_str(); }
    };

    class NotImplementedException : public Exception {
    public:
      NotImplementedException(std::string thing_)
        : Exception(ErrorCategory::Error, "", "", ErrorType::UnexpectedError,
                    IERR_UNEXPECTED, IERR_UNEXPECTED, 0) {
        msg = thing_ + " is not implemented";
      }
    };

    class ErrorException : public Exception {
    public:
      ErrorException(std::string fun_name_, std::string msg_, ErrorType type_,
                     types::f77_integer errorid_, types::f77_integer ierr_,
                     types::f77_integer ifmt_)
        : Exception(ErrorCategory::Error, fun_name_, msg_, type_, errorid_,
                    ierr_, ifmt_) {}
    };

    class CallbackException : public Exception {
    public:
      std::exception_ptr eptr;
      CallbackException(std::string fun_name_, std::string msg_,
                        ErrorType type_, std::exception_ptr eptr_,
                        types::f77_integer errorid_, types::f77_integer ierr_,
                        types::f77_integer ifmt_)
        : Exception(ErrorCategory::Error, fun_name_, msg_, type_, errorid_,
                    ierr_, ifmt_),
          eptr(eptr_) {}
    };

    class CallbackEarlyTermination : public Exception {
    public:
      std::exception_ptr eptr;
      CallbackEarlyTermination(std::string fun_name_, std::string msg_,
                               ErrorType type_, std::exception_ptr eptr_)
        : Exception(ErrorCategory::Error, fun_name_, msg_, type_, 0, 0, 0),
          eptr(eptr_) {}
      CallbackEarlyTermination(std::string fun_name_, std::string msg_)
        : CallbackEarlyTermination(fun_name_, msg_, ErrorType::CallbackError,
                                   nullptr) {}
      CallbackEarlyTermination(std::string msg_)
        : CallbackEarlyTermination("", msg_, ErrorType::CallbackError,
                                   nullptr) {}
    };

    class WarningException : public Exception {
    private:
      double drvalue;
      types::f77_integer divalue;
      void get_return_value(double &y) { y = drvalue; }
      template <typename T>
      void get_return_value(T &y) {
        y = static_cast<T>(divalue);
      }

    public:
      template <typename T>
      WarningException(std::string fun_name_, std::string msg_, ErrorType type_,
                       double drvalue_, T divalue_, types::f77_integer errorid_,
                       types::f77_integer ierr_, types::f77_integer ifmt_)
        : Exception(ErrorCategory::Warning, fun_name_, msg_, type_, errorid_,
                    ierr_, ifmt_),
          drvalue(drvalue_),
          divalue(static_cast<types::f77_integer>(divalue_)) {}
      WarningException(std::string fun_name_, std::string msg_, ErrorType type_,
                       double drvalue_, types::f77_integer errorid_,
                       types::f77_integer ierr_, types::f77_integer ifmt_)
        : WarningException(fun_name_, msg_, type_, drvalue_, 0, errorid_, ierr_,
                           ifmt_) {}
      template <typename T>
      WarningException(std::string fun_name_, std::string msg_, ErrorType type_,
                       T divalue_, types::f77_integer errorid_,
                       types::f77_integer ierr_, types::f77_integer ifmt_)
        : WarningException(fun_name_, msg_, type_, 0, divalue_, errorid_, ierr_,
                           ifmt_) {}

      template <typename T>
      T return_value(void) {
        T y;
        get_return_value(y);
        return y;
      }
    };

    std::string decode_sorder(types::f77_integer sorder) {
      return ((sorder == constants::NAG_ED_COL_MAJOR) ? "Column Major Order"
                                                      : "Row Major Order");
    }

    class ErrorHandlerControl {
    public:
      // class that holds the global error handling control arguments
      ErrorHandlerType error_handler_type;

    private:
      // this is currently not used, but may in the future
      HandleInvalidMetaInfo invalid_meta;

    public:
      ErrorHandlerControl(ErrorHandlerType eht = ErrorHandlerType::ThrowErrors)
        : error_handler_type(eht),
          invalid_meta(HandleInvalidMetaInfo::MissingAsError) {}

      friend class ErrorHandler;
    };

    // global variable that defines the default behaviour of the ErrorHandler
    ErrorHandlerControl GLOBAL_ERROR_HANDLER_CONTROL = ErrorHandlerControl();

    // class that does the error handler from the engine / wrappers
    class ErrorHandler {
    public:
      // variables controlling how the class behaves ...
      ErrorHandlerType error_handler_type;

      // currently only value that is used is MissingAsError it is
      // not a constant as that may change in the future
      // not private as we test the associated code in the unit tests
      HandleInvalidMetaInfo invalid_meta;
      // ... variables controlling how the class behaves

    public:
      // variables describing any errors / warnings that have occurred ...
      std::string fun_name;
      std::string msg;
      ErrorType type;
      ErrorCategory category;
      // true if an error has occurred
      bool error_thrown;
      // true if a warning has occurred
      bool warning_thrown;
      // numeric code associated with the error / warning
      // (note: this is not necessarily unique - but is documented)
      types::f77_integer errorid;
      // true if the is a "contact NAG" type error - these should
      // not occur in standard usage
      bool contact_nag;
      // pointer to any exceptions thrown in a callback
      std::exception_ptr eptr;
      // ... variables describing any errors / warnings that have occurred

      // engine variables ...
      // ierr / ifmt are additional numeric codes associated with an error
      // (note: the combination of these and errorid are unique, but not
      // documented)
      // these are not private as they are used in every wrapper
    public:
      types::f77_integer ierr;
      types::f77_integer ifmt;
      // engine expects this to be length 200, making the
      // actual array one bigger so that it can be null terminated
      static const types::f77_charlen errbuf_length = 200;
      char errbuf[errbuf_length + 1];
      // parsed data from errbuf (this is not private due to ease of
      // unit testing)
      std::vector<std::string> eb_data;
      // ... engine variables

    private:
      bool errbuf_present;
      // position of the last carriage return added to the error message
      size_t last_pos;
      // if true then the last carriage return is "fixed"
      bool last_fixed;

      // the error message lines in the wrapper are set to approximately
      // 80 characters, however that is assuming maximum width data
      // if the data isn't maximum width (so an integer is say, 1)
      // then that can lead to error messages with very short lines
      // the adjust_line methods attempts to remedy that using
      // errmsg_length
      static const size_t errmsg_length = 80;

    public:
      ErrorHandler(ErrorHandlerType eht)
        : error_handler_type(eht),
          invalid_meta(HandleInvalidMetaInfo::MissingAsError) {
        reset();
      }
      ErrorHandler(ErrorHandlerControl &ehc)
        : ErrorHandler(ehc.error_handler_type) {
        invalid_meta = ehc.invalid_meta;
      }
      ErrorHandler() : ErrorHandler(GLOBAL_ERROR_HANDLER_CONTROL) {}

    public:
      // methods that a user may want to call ...
      void reset() {
        last_pos = 0;
        last_fixed = false;
        // reset the error handler back to indicating no error
        prepare(fun_name);
      }
      // ... methods that a user may want to call
      // all other public classes are only public to allow them to be used directly
      // in the individual wrappers without having to list each as a friend

      // methods to generate the error message string ...
    private:
      void append_to_line(void) {
        msg += "MISSING ERROR INFORMATION\n";
        contact_nag = true;
      }
      void append_to_line(std::string msg_) { msg += msg_; }
      void append_to_line(int dn) {
        // append eb_data[dn-1] to error message, trimming off
        // leading white space
        if (dn > 0 && dn <= (int)eb_data.size()) {
          std::size_t pos = eb_data.at(dn - 1).find_first_not_of(" ");
          msg += eb_data.at(dn - 1).substr(pos);
        } else {
          msg += unknown_data_msg;
          contact_nag = true;
        }
      }
      template <typename... Targs>
      void append_to_line(int dn, Targs &&... Fargs) {
        append_to_line(dn);
        append_to_line(Fargs...);
      }
      template <typename... Targs>
      void append_to_line(std::string msg_, Targs &&... Fargs) {
        append_to_line(msg_);
        append_to_line(Fargs...);
      }
      size_t append_newline(void) {
        size_t pos = msg.size();
        if (pos > 0) {
          msg += "\n";
        }
        return pos;
      }
      void adjust_line(bool fixed, size_t pos) {
        // if last_fixed is false, then check that we are not
        // going to be appending two short error message lines
        if (!last_fixed && pos > 0) {
          if (msg.size() - last_pos < errmsg_length) {
            // concatenate the two short lines (by overwriting
            // the carriage return)
            msg[pos] = ' ';
          }
        } else {
          // update the position of the last carriage return
          last_pos = pos;
        }
        // save whether the line we have just added has a fixed
        // carriage return or not
        last_fixed = fixed;
      }

    public:
      // these are the same as the append_to_line, except they put a line
      // break if the msg already has some text in it
      void append_msg(bool fixed) {
        size_t pos = append_newline();
        append_to_line();
        adjust_line(fixed, pos);
      }
      void append_msg(bool fixed, std::string msg_) {
        size_t pos = append_newline();
        append_to_line(msg_);
        adjust_line(fixed, pos);
      }
      void append_msg(bool fixed, int dn) {
        size_t pos = append_newline();
        append_to_line(dn);
        adjust_line(fixed, pos);
      }
      template <typename... Targs>
      void append_msg(bool fixed, std::string msg_, Targs &&... Fargs) {
        size_t pos = append_newline();
        append_to_line(msg_, Fargs...);
        adjust_line(fixed, pos);
      }
      template <typename... Targs>
      void append_msg(bool fixed, int dn, Targs &&... Fargs) {
        size_t pos = append_newline();
        append_to_line(dn, Fargs...);
        adjust_line(fixed, pos);
      }
      // ... methods to generate the error message string

    public:
      void prepare(std::string fun_name_ = "", bool errbuf_present_ = true) {
        fun_name = fun_name_;
        errbuf_present = errbuf_present_;
        ierr = 0;
        ifmt = 0;
        msg = "";
        type = ErrorType::NoError;
        category = ErrorCategory::None;
        errorid = IERR_SUCCESS;
        eb_data.clear();
        std::memset(errbuf, '\0', 201 * sizeof(char));
        contact_nag = false;
        error_thrown = false;
        warning_thrown = false;
      }

      void set_calling_function(std::string fun_name_) { fun_name = fun_name_; }

      bool initial_error_handler(types::engine_data &en_data) {
        // handle common errors. if the error is not a common one, then
        // eb_data is populated
        // returns true if the error was a common one (in which case
        // all error information is populated ready for throwing)
        bool handled = handle_global_errors(en_data);

        if (!handled) {
          // not a global error, so parse errbuf
          // after this call, handled will only be true if an internal
          // error occurred in populate_eb_data
          handled = populate_eb_data();
        }

        if (handled) {
          throw_error();
        }

        return handled;
      }

      void append_exception_msg(types::engine_data &en_data) {
        // append any message associated with the exception in en_data
        eptr = nullptr;
        if (en_data.wrapptr1) {
          error_handler::ExceptionPointer *p_eptr =
            static_cast<error_handler::ExceptionPointer *>(en_data.wrapptr1);
          eptr = p_eptr->eptr;
          try {
            std::rethrow_exception(eptr);
          } catch (const error_handler::Exception &e) {
            if (e.msg.length() > 0) {
              append_msg(true, "Exception message:");
              append_msg(true, e.msg);
            }
          } catch (...) {
            // this should not be possible
            raise_error_unexpected_error();
          }
        }
      }

      // standard error checking and messages ...
      // array size checks ...
      // the behaviour of the array size checking functions is defined by
      // *this->invalid_meta:
      //   HandleInvalidMetaInfo::Ignore => no checks are performed
      //   HandleInvalidMetaInfo::IgnoreMissing => missing values are ignored,
      //   none missing are checked HandleInvalidMetaInfo::MissingAsWarning =>
      //   missing values are treated as warnings, none missing are checked
      //   HandleInvalidMetaInfo::MissingAsErrors => missing values are treated
      //   as errors, none missing are checked
      template <typename MI1, typename MI2>
      bool is_error_array_size(std::string argname,
                               data_handling::array_info<MI1> ndims,
                               data_handling::array_info<MI2> size1,
                               types::f77_integer esize1) {
        // check dimensions of a 1D array and throw an error if they are invalid
        reset();
        bool set_message = false;
        if (invalid_meta != HandleInvalidMetaInfo::Ignore) {
          bool all_present = (ndims.set && size1.set);
          if (invalid_meta != HandleInvalidMetaInfo::IgnoreMissing &&
              !all_present) {
            set_errorid(IERR_ARRAY_SIZE_INVALID,
                        (invalid_meta == HandleInvalidMetaInfo::MissingAsWarning
                           ? ErrorCategory::Warning
                           : ErrorCategory::Error),
                        ErrorType::GenericError);
            set_message = true;
          }
          if (esize1 > 0) {
            if ((ndims != 1) || (size1 != esize1)) {
              set_errorid(IERR_ARRAY_SIZE_INVALID, ErrorCategory::Error,
                          ErrorType::GenericError);
              set_message = true;
            }
          }
          if (set_message) {
            ierr = IERR_ARRAY_SIZE_INVALID;
            ifmt = IERR_ARRAY_ERROR_IFMT;
            append_msg(true, "On entry, argument " + argname +
                               " must be a vector of size " +
                               std::to_string(esize1) + ".");
            if (ndims.set && ndims != 1) {
              append_msg(true, "Supplied argument has " +
                                 std::to_string(ndims.value) + " dimension" +
                                 ((ndims.value > 1) ? "s" : "") + ".");
            } else if (all_present) {
              append_msg(true, "Supplied argument was a vector of size " +
                                 std::to_string(size1.value) + ".");
            } else if (!all_present &&
                       invalid_meta != HandleInvalidMetaInfo::IgnoreMissing) {
              append_msg(true, "The size of the supplied array could not be "
                               "ascertained");
            }
            throw_error();
          }
        }
        return error_thrown;
      }
      template <typename MI1, typename MI2, typename MI3>
      bool is_error_array_size(std::string argname,
                               data_handling::array_info<MI1> ndims,
                               data_handling::array_info<MI2> size1,
                               types::f77_integer esize1,
                               data_handling::array_info<MI3> size2,
                               types::f77_integer esize2) {
        // check dimensions of a 2D array and throw an error if they are invalid
        reset();
        bool set_message = false;
        if (invalid_meta != HandleInvalidMetaInfo::Ignore) {
          bool all_present = (ndims.set && size1.set && size2.set);
          if (invalid_meta != HandleInvalidMetaInfo::IgnoreMissing &&
              !all_present) {
            set_errorid(IERR_ARRAY_SIZE_INVALID,
                        (invalid_meta == HandleInvalidMetaInfo::MissingAsWarning
                           ? ErrorCategory::Warning
                           : ErrorCategory::Error),
                        ErrorType::GenericError);
            set_message = true;
          }
          if (esize1 > 0 && esize2 > 0) {
            if ((ndims != 2) || (size1 != esize1) || (size2 != esize2)) {
              set_errorid(IERR_ARRAY_SIZE_INVALID, ErrorCategory::Error,
                          ErrorType::GenericError);
              set_message = true;
            }
          }
          if (set_message) {
            ierr = IERR_ARRAY_SIZE_INVALID;
            ifmt = IERR_ARRAY_ERROR_IFMT;
            append_msg(true, "On entry, argument " + argname + " must be a " +
                               std::to_string(esize1) + " x " +
                               std::to_string(esize2) + " array.");
            if (ndims.set && ndims.value != 2) {
              append_msg(true, "Supplied argument has " +
                                 std::to_string(ndims.value) + " dimension" +
                                 ((ndims.value > 1) ? "s" : "") + ".");
            } else if (all_present) {
              append_msg(true, "Supplied argument was a " +
                                 std::to_string(size1.value) + " x " +
                                 std::to_string(size2.value) + " array.");
            } else if (!all_present &&
                       invalid_meta != HandleInvalidMetaInfo::IgnoreMissing) {
              append_msg(true,
                         "Not all of the sizes for the supplied array could "
                         "be ascertained");
            }
            throw_error();
          }
        }
        return error_thrown;
      }
      template <typename MI1, typename MI2, typename MI3, typename MI4>
      bool is_error_array_size(
        std::string argname, data_handling::array_info<MI1> ndims,
        data_handling::array_info<MI2> size1, types::f77_integer esize1,
        data_handling::array_info<MI3> size2, types::f77_integer esize2,
        data_handling::array_info<MI4> size3, types::f77_integer esize3) {
        // check dimensions of a 3D array and throw an error if they are invalid
        reset();
        bool set_message = false;
        if (invalid_meta != HandleInvalidMetaInfo::Ignore) {
          bool all_present = (ndims.set && size1.set && size2.set && size3.set);
          if (invalid_meta != HandleInvalidMetaInfo::IgnoreMissing &&
              !all_present) {
            set_errorid(IERR_ARRAY_SIZE_INVALID,
                        (invalid_meta == HandleInvalidMetaInfo::MissingAsWarning
                           ? ErrorCategory::Warning
                           : ErrorCategory::Error),
                        ErrorType::GenericError);
            set_message = true;
          }
          if (esize1 > 0 && esize2 > 0 && esize3 > 0) {
            if ((ndims != 3) || (size1 != esize1) || (size2 != esize2) ||
                (size3 != esize3)) {
              set_errorid(IERR_ARRAY_SIZE_INVALID, ErrorCategory::Error,
                          ErrorType::GenericError);
              set_message = true;
            }
          }
          if (set_message) {
            ierr = IERR_ARRAY_SIZE_INVALID;
            ifmt = IERR_ARRAY_ERROR_IFMT;
            append_msg(true, "On entry, argument " + argname + " must be a " +
                               std::to_string(esize1) + " x " +
                               std::to_string(esize2) + " x " +
                               std::to_string(esize3) + " array.");
            if (ndims.set && ndims.value != 3) {
              append_msg(true, "Supplied argument has " +
                                 std::to_string(ndims.value) + " dimension" +
                                 ((ndims.value > 1) ? "s" : "") + ".");
            } else if (all_present) {
              append_msg(true, "Supplied argument was a " +
                                 std::to_string(size1.value) + " x " +
                                 std::to_string(size2.value) + " x " +
                                 std::to_string(size3.value) + " array.");
            } else if (!all_present &&
                       invalid_meta != HandleInvalidMetaInfo::IgnoreMissing) {
              append_msg(true,
                         "Not all of the sizes for the supplied array could "
                         "not be ascertained");
            }
            throw_error();
          }
        }
        return error_thrown;
      }
      // ... array size checks

      void raise_error_array_sorder(std::string argname,
                                    types::f77_integer esorder,
                                    types::f77_integer sorder) {
        set_errorid(IERR_ARRAY_SORDER, ErrorCategory::Error,
                    ErrorType::GenericError);
        ierr = IERR_ARRAY_SORDER;
        ifmt = IERR_ARRAY_ERROR_IFMT;
        append_msg(true, "On entry, the data in " + argname + " is stored in " +
                           decode_sorder(sorder) + ".");
        append_msg(true, "The data was expected to be in " +
                           decode_sorder(esorder) + ".");
        throw_error();
      }
      void raise_error_array_null(std::string argname) {
        set_errorid(IERR_ARRAY_NULL, ErrorCategory::Error,
                    ErrorType::GenericError);
        ierr = IERR_ARRAY_NULL;
        ifmt = IERR_ARRAY_ERROR_IFMT;
        append_msg(true, "On entry, the raw data component of " + argname +
                           " is null.");
        throw_error();
      }
      void raise_error_comm_invalid(std::string argname) {
        set_errorid(IERR_COMM_INVALID, ErrorCategory::Error,
                    ErrorType::GenericError);
        ierr = IERR_COMM_INVALID;
        ifmt = IERR_COMM_ERROR_IFMT;
        append_msg(true, "On entry, the communication class " + argname +
                           " has not been initialized correctly.");
        throw_error();
      }
      void raise_error_no_size_info(std::string argname) {
        set_errorid(IERR_ARRAY_NO_SIZE_INFO, ErrorCategory::Error,
                    ErrorType::GenericError);
        ierr = IERR_ARRAY_NO_SIZE_INFO;
        ifmt = IERR_ARRAY_ERROR_IFMT;
        append_msg(true, "On entry, unable to ascertain a value for " +
                           argname + ".");
        throw_error();
      }
      void raise_error_value_not_available(std::string argname) {
        set_errorid(IERR_VALUE_NOT_AVAILABLE, ErrorCategory::Error,
                    ErrorType::GenericError);
        ierr = IERR_VALUE_NOT_AVAILABLE;
        ifmt = IERR_VALUE_ERROR_IFMT;
        append_msg(true, "A value is not yet available for " + argname + ".");
        throw_error();
      }
      void raise_error_null_group(std::string argnames) {
        set_errorid(IERR_OPTIONAL_GROUP, ErrorCategory::Error,
                    ErrorType::GenericError);
        ierr = IERR_OPTIONAL_GROUP;
        ifmt = IERR_OPTIONAL_GROUP_IFMT;
        append_msg(true, "On entry, " + argnames +
                           " must either all be supplied, or none of them "
                           "should be supplied.");
        throw_error();
      }

      void raise_error_allocation_failure(void) {
        set_allocation_failure();
        throw_error();
      }
      void raise_error_unexpected_error(void) {
        set_unexpected_error();
        throw_error();
      }
      void set_unexpected_error(void) {
        set_errorid(IERR_UNEXPECTED, ErrorCategory::Error,
                    ErrorType::UnexpectedError);
        if (ierr == 0 && ifmt == 0) {
          ierr = ifmt = IERR_UNEXPECTED;
        }
        append_msg(true, "An unexpected error has been triggered by this "
                         "function.");
        contact_nag = true;
      }
      void set_allocation_failure(void) {
        set_errorid(IERR_ALLOC_FAIL, ErrorCategory::Error,
                    ErrorType::MemoryError);
        if (ierr == 0 && ifmt == 0) {
          ierr = ifmt = IERR_ALLOC_FAIL;
        }
        append_msg(true, "Dynamic memory allocation failed.");
      }
      void set_errorid(int id, ErrorCategory category_, ErrorType type_) {
        category = category_;
        type = type_;
        errorid = id;
      }
      // ... standard error messages

    private:
      std::string full_error_string(void) {
        return ((category == ErrorCategory::Warning) ? std::string("Warning: ")
                                                     : std::string("Error: ")) +
               "function " + fun_name + " returned with errorid " +
               std::to_string(errorid) + " (" + std::to_string(ierr) + ", " +
               std::to_string(ifmt) + ")\n" + msg;
      }

      bool handle_global_errors(types::engine_data &en_data) {
        // handle errors that can be thrown by all functions (ifail or en_data)
        bool handled = true;
        if (en_data.hlperr != HLPERR_SUCCESS) {
          if (en_data.hlperr == HLPERR_USER_EXCEPTION ||
              en_data.hlperr == HLPERR_PRINT_REC_EXCEPTION) {
            if (en_data.hlperr == HLPERR_USER_EXCEPTION) {
              set_errorid(IERR_HLPERR_USER_EXCEPTION, ErrorCategory::Error,
                          ErrorType::CallbackError);
              ierr = IERR_HLPERR_USER_EXCEPTION;
              append_msg(true, "An exception was thrown in a callback.");
            } else if (en_data.hlperr == HLPERR_PRINT_REC_EXCEPTION) {
              set_errorid(IERR_HLPERR_PRINT_REC_EXCEPTION, ErrorCategory::Error,
                          ErrorType::CallbackError);
              ierr = IERR_HLPERR_PRINT_REC_EXCEPTION;
              append_msg(true, "An exception was thrown during IO (writing).");
            } else {
              set_errorid(IERR_HLPERR_READ_REC_EXCEPTION, ErrorCategory::Error,
                          ErrorType::CallbackError);
              ierr = IERR_HLPERR_READ_REC_EXCEPTION;
              append_msg(true, "An exception was thrown during IO (reading).");
            }
            ifmt = IERR_CALLBACK_ERROR_IFMT;
            if (en_data.wrapptr1) {
              error_handler::ExceptionPointer *p_eptr =
                static_cast<error_handler::ExceptionPointer *>(
                  en_data.wrapptr1);
              eptr = p_eptr->eptr;
            } else {
              eptr = nullptr;
            }

          } else if (en_data.hlperr == HLPERR_ARRAY_POINTER_CHANGED) {
            set_errorid(IERR_HLPERR_ARRAY_POINTER_CHANGED, ErrorCategory::Error,
                        ErrorType::CallbackError);
            ierr = IERR_HLPERR_ARRAY_POINTER_CHANGED;
            ifmt = IERR_CALLBACK_ERROR_IFMT;
            append_msg(true,
                       "The memory address for an array in a callback has "
                       "changed.");

          } else {
            set_unexpected_error();
          }

        } else {
          handled = handle_global_errors();
        }

        return handled;
      }

      bool handle_global_errors() {
        // handle errors that can be thrown by all functions (ifail only)
        bool handled = true;

        if (errorid != IERR_SUCCESS) {
          if (errorid == IERR_ALLOC_FAIL) {
            set_allocation_failure();

          } else if (errorid == IERR_NO_LIC) {
            set_errorid(IERR_NO_LIC, ErrorCategory::Error,
                        ErrorType::LicenceError);
            ierr = ifmt = IERR_NO_LIC;
            append_msg(true,
                       "Your licence key may have expired or may not have been "
                       "installed correctly.");

          } else if (errorid == IERR_UNEXPECTED) {
            set_unexpected_error();

          } else {
            handled = false;
          }
        }

        return handled;
      }

    public:
      // originally had all of this private - but it makes unit testing
      // difficult
      bool populate_eb_data(void) {
        // parse errbuf to get ierr, ifmt and ndata and to populate eb_data
        // returns true if there is an internal error
        bool internal_error = false;

        if (!errbuf_present) {
          // algorithmic function does not use errbuf when reporting errors
          ierr = errorid;
          ifmt = 0;
          return internal_error;
        }

        try {
          // tokenize errbuf
          std::regex reg(std::string(1, errbuf_delim));
          std::string serrbuf(errbuf);
          std::sregex_token_iterator iter(serrbuf.begin(), serrbuf.end(), reg,
                                          -1);
          std::sregex_token_iterator end;

          // skip any blank entries at the start
          for (; iter != end && *iter == ""; iter++)
            ;

          // first two elements of errbuf are integer codes
          if (iter != end) {
            ierr = std::stoi((*iter).str());
            iter++;
          }
          if (iter != end) {
            ifmt = std::stoi((*iter).str());
            iter++;
          }
          // third element of errbuf is a count of data items
          if (iter != end) {
            int ndata = std::stoi((*iter).str());
            iter++;
            if (ndata > 0) {
              // get the rest of the data items
              eb_data.assign(iter, end);
              // we are truncating if ndata < number of data items supplied
              // padding with the unknown data message if ndata > number of data
              // items (neither of these case should occur)
              eb_data.resize(ndata, unknown_data_msg);
            }
          } else {
            // errbuf doesn't contain at least three values (should never
            // happen)
            internal_error = true;
          }
        } catch (...) {
          // something has gone wrong parsing errbuf (should never happen)
          internal_error = true;
        }

        if (internal_error) {
          set_unexpected_error();
        }

        return internal_error;
      }

    public:
      void throw_error() {
        // throws an error exception if one is required
        // does not throw any warnings, irrespective of the value of
        // ErrorHandlerType (to get errors and warnings thrown you
        // need to call throw_error and throw_warning
        warning_thrown = (category == ErrorCategory::Warning);
        error_thrown = !(category == ErrorCategory::None || warning_thrown);
        if (category != ErrorCategory::None &&
            category != ErrorCategory::Warning &&
            error_handler_type != ErrorHandlerType::ThrowNothing) {
          if (errorid == IERR_HLPERR_USER_EXCEPTION) {
            throw CallbackException(fun_name, full_error_string(), type, eptr,
                                    errorid, ierr, ifmt);
          } else {
            throw ErrorException(fun_name, full_error_string(), type, errorid,
                                 ierr, ifmt);
          }
        }
      }

      void throw_warning(void) { throw_warning(0); }

      template <typename TR>
      void throw_warning(TR &&return_value) {
        // throw a warning if one is required
        // it is assumed that a call to throw_error has been made before
        // the call to throw_warning
        if (warning_thrown && category != ErrorCategory::None &&
            category != ErrorCategory::Error &&
            error_handler_type == ErrorHandlerType::ThrowAll) {
          throw WarningException(fun_name, full_error_string(), type,
                                 return_value, errorid, ierr, ifmt);
        }
      }
    };
  }
}
#endif
