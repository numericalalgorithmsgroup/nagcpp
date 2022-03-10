// Header for nagcpp::opt::handle_opt_set (e04zm)

// Copyright 2022, Numerical Algorithms Group Ltd, Oxford, UK.
// Generated by cpp-ft-wrapper.xsl
// Version 28.3.0.0
#ifndef NAGCPP_E04ZM_HPP
#define NAGCPP_E04ZM_HPP

#include "utility/nagcpp_consts.hpp"
#include "utility/nagcpp_data_handling.hpp"
#include "utility/nagcpp_engine_routines.hpp"
#include "utility/nagcpp_engine_types.hpp"
#include "utility/nagcpp_error_handler.hpp"
#include "utility/nagcpp_utility_comm.hpp"
#include "utility/nagcpp_utility_optional.hpp"
#include "utility/nagcpp_utility_print_rec.hpp"

namespace nagcpp {
  namespace opt {
    // handle_opt_set (e04zm)
    // Option setting routine for the solvers from the NAG optimization modelling
    // suite.
    // opt::handle_opt_set (e04zm) is an option setting function for all solvers
    // from the NAG optimization modelling suite.
    // It can set a single option or reset all of them to their default.

    // parameters:
    //   comm: opt::CommE04RA, scalar
    //     Communication structure.
    //     An object of either the derived class opt::CommE04RA or its base class
    //     utility::NoneCopyableComm can be supplied.
    //     It is recommended that the derived class is used. If the base class is
    //     supplied it must
    //     first be initialized via a call to opt::handle_init (e04ra).
    //   optstr: std::string, scalar
    //     A string identifying the option and its value to be set
    //   opt: opt::OptionalE04ZM
    //     Optional parameter container, derived from utility::Optional.
    //     contains:
    //       fail: error_handler::ErrorHandler

    // error_handler::ErrorException
    //   (errorid 1)
    //     comm.handle has not been initialized.
    //   (errorid 1)
    //     comm.handle does not belong to the NAG optimization modelling suite,
    //     has not been initialized properly or is corrupted.
    //   (errorid 1)
    //     comm.handle has not been initialized properly or is corrupted.
    //   (errorid 2)
    //     The options cannot be modified while solver is running.
    //   (errorid 11)
    //     On entry, the option supplied in optstr was not recognized:
    //     optstr = "<value>".
    //   (errorid 12)
    //     On entry, the expected delimiter "=" was not found in optstr:
    //     optstr = "<value>".
    //   (errorid 13)
    //     On entry, could not convert the specified optval to an integer:
    //     optval = "<value>".
    //   (errorid 13)
    //     On entry, could not convert the specified optval to a real:
    //     optval = "<value>".
    //   (errorid 15)
    //     On entry, the optval supplied for the integer option is not
    //     valid.
    //     option = "<value>",
    //     optval = <value>.
    //     Constraint: optval >= <value>.
    //   (errorid 15)
    //     On entry, the optval supplied for the integer option is not
    //     valid.
    //     option = "<value>",
    //     optval = <value>.
    //     Constraint: optval > <value>.
    //   (errorid 15)
    //     On entry, the optval supplied for the integer option is not
    //     valid.
    //     option = "<value>",
    //     optval = <value>.
    //     Constraint: optval <= <value>.
    //   (errorid 15)
    //     On entry, the optval supplied for the integer option is not
    //     valid.
    //     option = "<value>",
    //     optval = <value>.
    //     Constraint: optval < <value>.
    //   (errorid 16)
    //     On entry, the optval supplied for the real option is not valid.
    //     option = "<value>",
    //     optval = <value>.
    //     Constraint: optval >= <value>.
    //   (errorid 16)
    //     On entry, the optval supplied for the real option is not valid.
    //     option = "<value>",
    //     optval = <value>.
    //     Constraint: optval > <value>.
    //   (errorid 16)
    //     On entry, the optval supplied for the real option is not valid.
    //     option = "<value>",
    //     optval = <value>.
    //     Constraint: optval <= <value>.
    //   (errorid 16)
    //     On entry, the optval supplied for the real option is not valid.
    //     option = "<value>",
    //     optval = <value>.
    //     Constraint: optval < <value>.
    //   (errorid 17)
    //     On entry, the optval supplied for the character option is not
    //     valid.
    //     option = "<value>",
    //     optval = "<value>".
    //   (errorid 10605)
    //     On entry, the communication class <value> has not been initialized
    //     correctly.
    //   (errorid 10703)
    //     An exception was thrown during IO (writing).
    //   (errorid -99)
    //     An unexpected error has been triggered by this routine.
    //   (errorid -399)
    //     Your licence key may have expired or may not have been installed correctly.
    //   (errorid -999)
    //     Dynamic memory allocation failed.

    extern "C" {
#if defined(_WIN32) && defined(USE_STDCALL)
#define e04zmft_(en_data, print_rec, print_rech, handle, optstr, errbuf, \
                 ifail, optstr_length, errbuf_length)                    \
  E04ZMFT(en_data, print_rec, print_rech, handle, optstr, optstr_length, \
          errbuf, errbuf_length, ifail)
#elif defined(_WIN32) || defined(_WIN64)
#define e04zmft_ E04ZMFT
#else
#define E04ZMFT e04zmft_
#endif
    extern void NAG_CALL
      E04ZMFT(types::engine_data &en_data, void *print_rec, NAG_PRINT_RECH,
              void *handle, const char *optstr NAG_STDCALL_LEN(optstr_length),
              char *errbuf NAG_STDCALL_LEN(errbuf_length),
              types::f77_integer &ifail NAG_NSTDCALL_LEN(optstr_length)
                NAG_NSTDCALL_LEN(errbuf_length));
    }

    class CommE04RA;

    class OptionalE04ZM : public utility::Optional {
    public:
      OptionalE04ZM() : Optional() {}
      template <typename COMM>
      friend void handle_opt_set(COMM &comm, const std::string optstr,
                                 opt::OptionalE04ZM &opt);
    };

    template <typename COMM>
    void handle_opt_set(COMM &comm, const std::string optstr,
                        opt::OptionalE04ZM &opt) {
      opt.fail.prepare("opt::handle_opt_set (e04zm)");
      types::engine_data en_data;
      engine_routines::y90haan_(en_data);
      en_data.allocate_workspace = constants::NAG_ED_YES;
      static_assert(std::is_same<COMM, utility::NoneCopyableComm>::value ||
                      std::is_same<COMM, opt::CommE04RA>::value,
                    "Invalid type for comm: must be either "
                    "utility::NoneCopyableComm or opt::CommE04RA");
      if (!(comm.check())) {
        opt.fail.raise_error_comm_invalid("comm");
        if (opt.fail.error_thrown) {
          return;
        }
      }

      void *local_print_rec = static_cast<void *>(&opt.iomanager);
      data_handling::StringRawData<data_handling::ArgIntent::IntentIN>
        local_optstr(optstr);

      e04zmft_(en_data, local_print_rec, utility::print_rech, &comm.handle,
               local_optstr.data, opt.fail.errbuf, opt.fail.errorid,
               local_optstr.string_length, opt.fail.errbuf_length);

      if (!(opt.fail.initial_error_handler(en_data))) {
        if (opt.fail.ierr == 1 && opt.fail.ifmt == 100) {
          opt.fail.set_errorid(1, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "comm.handle has not been initialized.");
        } else if (opt.fail.ierr == 1 && opt.fail.ifmt == 101) {
          opt.fail.set_errorid(1, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "comm.handle does not belong to the NAG "
                                     "optimization modelling suite,");
          opt.fail.append_msg(false, "has not been initialized properly or is "
                                     "corrupted.");
        } else if (opt.fail.ierr == 1 && opt.fail.ifmt == 102) {
          opt.fail.set_errorid(1, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "comm.handle has not been initialized "
                                     "properly or is corrupted.");
        } else if (opt.fail.ierr == 2 && opt.fail.ifmt == 202) {
          opt.fail.set_errorid(2, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "The options cannot be modified while "
                                     "solver is running.");
        } else if (opt.fail.ierr == 11 && opt.fail.ifmt == 2) {
          opt.fail.set_errorid(11, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "On entry, the option supplied in optstr "
                                     "was not recognized:");
          opt.fail.append_msg(false, "optstr = \"" + optstr + "\".");
        } else if (opt.fail.ierr == 12 && opt.fail.ifmt == 2) {
          opt.fail.set_errorid(12, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "On entry, the expected delimiter \"=\" "
                                     "was not found in optstr:");
          opt.fail.append_msg(false, "optstr = \"" + optstr + "\".");
        } else if (opt.fail.ierr == 13 && opt.fail.ifmt == 1) {
          opt.fail.set_errorid(13, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "On entry, could not convert the "
                                     "specified optval to an integer:");
          opt.fail.append_msg(false, "optval = \"", 1, "\".");
        } else if (opt.fail.ierr == 13 && opt.fail.ifmt == 2) {
          opt.fail.set_errorid(13, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "On entry, could not convert the "
                                     "specified optval to a real:");
          opt.fail.append_msg(false, "optval = \"", 1, "\".");
        } else if (opt.fail.ierr == 15 && opt.fail.ifmt == 1) {
          opt.fail.set_errorid(15, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "On entry, the optval supplied for the "
                                     "integer option is not");
          opt.fail.append_msg(true, "valid.");
          opt.fail.append_msg(false, "option = \"", 1, "\",");
          opt.fail.append_msg(true, "optval = ", 2, ".");
          opt.fail.append_msg(false, "Constraint: optval >= ", 3, ".");
        } else if (opt.fail.ierr == 15 && opt.fail.ifmt == 2) {
          opt.fail.set_errorid(15, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "On entry, the optval supplied for the "
                                     "integer option is not");
          opt.fail.append_msg(true, "valid.");
          opt.fail.append_msg(false, "option = \"", 1, "\",");
          opt.fail.append_msg(true, "optval = ", 2, ".");
          opt.fail.append_msg(false, "Constraint: optval > ", 3, ".");
        } else if (opt.fail.ierr == 15 && opt.fail.ifmt == 11) {
          opt.fail.set_errorid(15, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "On entry, the optval supplied for the "
                                     "integer option is not");
          opt.fail.append_msg(true, "valid.");
          opt.fail.append_msg(false, "option = \"", 1, "\",");
          opt.fail.append_msg(true, "optval = ", 2, ".");
          opt.fail.append_msg(false, "Constraint: optval <= ", 3, ".");
        } else if (opt.fail.ierr == 15 && opt.fail.ifmt == 12) {
          opt.fail.set_errorid(15, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "On entry, the optval supplied for the "
                                     "integer option is not");
          opt.fail.append_msg(true, "valid.");
          opt.fail.append_msg(false, "option = \"", 1, "\",");
          opt.fail.append_msg(true, "optval = ", 2, ".");
          opt.fail.append_msg(false, "Constraint: optval < ", 3, ".");
        } else if (opt.fail.ierr == 16 && opt.fail.ifmt == 1) {
          opt.fail.set_errorid(16, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(true, "On entry, the optval supplied for the "
                                    "real option is not valid.");
          opt.fail.append_msg(false, "option = \"", 1, "\",");
          opt.fail.append_msg(true, "optval = ", 2, ".");
          opt.fail.append_msg(false, "Constraint: optval >= ", 3, ".");
        } else if (opt.fail.ierr == 16 && opt.fail.ifmt == 2) {
          opt.fail.set_errorid(16, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(true, "On entry, the optval supplied for the "
                                    "real option is not valid.");
          opt.fail.append_msg(false, "option = \"", 1, "\",");
          opt.fail.append_msg(true, "optval = ", 2, ".");
          opt.fail.append_msg(false, "Constraint: optval > ", 3, ".");
        } else if (opt.fail.ierr == 16 && opt.fail.ifmt == 11) {
          opt.fail.set_errorid(16, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(true, "On entry, the optval supplied for the "
                                    "real option is not valid.");
          opt.fail.append_msg(false, "option = \"", 1, "\",");
          opt.fail.append_msg(true, "optval = ", 2, ".");
          opt.fail.append_msg(false, "Constraint: optval <= ", 3, ".");
        } else if (opt.fail.ierr == 16 && opt.fail.ifmt == 12) {
          opt.fail.set_errorid(16, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(true, "On entry, the optval supplied for the "
                                    "real option is not valid.");
          opt.fail.append_msg(false, "option = \"", 1, "\",");
          opt.fail.append_msg(true, "optval = ", 2, ".");
          opt.fail.append_msg(false, "Constraint: optval < ", 3, ".");
        } else if (opt.fail.ierr == 17 && opt.fail.ifmt == 1) {
          opt.fail.set_errorid(17, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "On entry, the optval supplied for the "
                                     "character option is not");
          opt.fail.append_msg(true, "valid.");
          opt.fail.append_msg(false, "option = \"", 1, "\",");
          opt.fail.append_msg(false, "optval = \"", 2, "\".");
        } else {
          opt.fail.set_unexpected_error();
        }
        opt.fail.throw_error();
      }
      if (opt.fail.error_thrown) {
        return;
      }
      opt.fail.throw_warning();
    }

    // alt-1
    template <typename COMM>
    void handle_opt_set(COMM &comm, const std::string optstr) {
      opt::OptionalE04ZM local_opt;

      handle_opt_set(comm, optstr, local_opt);
    }
  }
}
#define e04zm opt::handle_opt_set
#endif
