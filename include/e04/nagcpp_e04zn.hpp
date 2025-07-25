// Header for nagcpp::opt::handle_opt_get (e04zn)

// Copyright 2025, Numerical Algorithms Group Ltd, Oxford, UK.
// Generated by cpp-ft-wrapper.xsl
// Version 31.1.0.0
#ifndef NAGCPP_E04ZN_HPP
#define NAGCPP_E04ZN_HPP

#include "utility/nagcpp_consts.hpp"
#include "utility/nagcpp_data_handling.hpp"
#include "utility/nagcpp_engine_routines.hpp"
#include "utility/nagcpp_engine_types.hpp"
#include "utility/nagcpp_error_handler.hpp"
#include "utility/nagcpp_utility_comm.hpp"
#include "utility/nagcpp_utility_optional.hpp"

namespace nagcpp {
  namespace opt {
    // handle_opt_get (e04zn)
    // Option getting routine for the solvers from the NAG optimization modelling
    // suite.
    // opt::handle_opt_get (e04zn) is an option getting function for all solvers
    // from the NAG optimization modelling suite.
    // It is used to query the value of options.

    // parameters:
    //   comm: opt::CommE04RA, scalar
    //     Communication structure.
    //     An object of either the derived class opt::CommE04RA or its base class
    //     utility::NoneCopyableComm can be supplied.
    //     It is recommended that the derived class is used. If the base class is
    //     supplied it must
    //     first be initialized via a call to opt::handle_init (e04ra).
    //   optstr: std::string, scalar
    //     A string identifying the option whose current value is required
    //   ivalue: types::f77_integer, scalar
    //     On exit: if the option supplied in optstr is an integer-valued parameter,
    //     ivalue will hold its current value
    //   rvalue: double, scalar
    //     On exit: if the option supplied in optstr is a real-valued parameter,
    //     rvalue will hold its current value
    //   cvalue: std::string, scalar
    //     Note: the string returned in cvalue will never exceed 40 characters in
    //     length.
    //     On exit: if the option supplied in optstr is a character-valued parameter,
    //     cvalue will hold its current value
    //   optype: types::f77_integer, scalar
    //     On exit: indicates whether the option supplied in optstr is an integer-,
    //     real - or character-valued parameter and hence which of ivalue, rvalue or
    //     cvalue holds the current value
    //   opt: opt::OptionalE04ZN
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
    //   (errorid 11)
    //     On entry, the option supplied in optstr was not recognized:
    //     optstr = "<value>".
    //   (errorid 10605)
    //     On entry, the communication class <value> has not been initialized
    //     correctly.
    //   (errorid -99)
    //     An unexpected error has been triggered by this routine.
    //   (errorid -399)
    //     Your licence key may have expired or may not have been installed correctly.
    //   (errorid -999)
    //     Dynamic memory allocation failed.

    // error_handler::WarningException
    //   (errorid 41)
    //     On entry, optstr indicates a character option, but cvalue is
    //     too short to hold the stored value. The returned value will be truncated.

    extern "C" {
#if defined(_WIN32) && defined(USE_STDCALL)
#define e04znft_(en_data, handle, optstr, ivalue, rvalue, cvalue, optype,    \
                 errbuf, ifail, optstr_length, cvalue_length, errbuf_length) \
  E04ZNFT(en_data, handle, optstr, optstr_length, ivalue, rvalue, cvalue,    \
          cvalue_length, optype, errbuf, errbuf_length, ifail)
#elif defined(_WIN32) || defined(_WIN64)
#define e04znft_ E04ZNFT
#else
#define E04ZNFT e04znft_
#endif
    extern void NAG_CALL E04ZNFT(
      types::engine_data &en_data, void *handle,
      const char *optstr NAG_STDCALL_LEN(optstr_length),
      types::f77_integer &ivalue, double &rvalue,
      char *cvalue NAG_STDCALL_LEN(cvalue_length), types::f77_integer &optype,
      char *errbuf NAG_STDCALL_LEN(errbuf_length),
      types::f77_integer &ifail NAG_NSTDCALL_LEN(optstr_length)
        NAG_NSTDCALL_LEN(cvalue_length) NAG_NSTDCALL_LEN(errbuf_length));
    }

    class CommE04RA;

    class OptionalE04ZN : public utility::Optional {
    public:
      OptionalE04ZN() : Optional() {}
      template <typename COMM>
      friend void handle_opt_get(COMM &comm, const std::string optstr,
                                 types::f77_integer &ivalue, double &rvalue,
                                 std::string &cvalue,
                                 types::f77_integer &optype,
                                 opt::OptionalE04ZN &opt);
    };

    template <typename COMM>
    void handle_opt_get(COMM &comm, const std::string optstr,
                        types::f77_integer &ivalue, double &rvalue,
                        std::string &cvalue, types::f77_integer &optype,
                        opt::OptionalE04ZN &opt) {
      opt.fail.prepare("opt::handle_opt_get (e04zn)");
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

      data_handling::StringRawData<data_handling::ArgIntent::IntentIN>
        local_optstr(optstr);
      data_handling::StringRawData<data_handling::ArgIntent::IntentOUT>
        local_cvalue(39);

      e04znft_(en_data, &comm.handle, local_optstr.data, ivalue, rvalue,
               local_cvalue.data, optype, opt.fail.errbuf, opt.fail.errorid,
               local_optstr.string_length, local_cvalue.string_length,
               opt.fail.errbuf_length);

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
        } else if (opt.fail.ierr == 11 && opt.fail.ifmt == 1101) {
          opt.fail.set_errorid(11, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "On entry, the option supplied in optstr "
                                     "was not recognized:");
          opt.fail.append_msg(false, "optstr = \"" + optstr + "\".");
        } else if (opt.fail.ierr == 41 && opt.fail.ifmt == 1801) {
          opt.fail.set_errorid(41, error_handler::ErrorCategory::Warning,
                               error_handler::ErrorType::GeneralWarning);
          opt.fail.append_msg(false, "On entry, optstr indicates a character "
                                     "option, but cvalue is");
          opt.fail.append_msg(false, "too short to hold the stored value. The "
                                     "returned value will be truncated.");
        } else {
          opt.fail.set_unexpected_error();
        }
        opt.fail.throw_error();
      }
      if (opt.fail.error_thrown) {
        return;
      }

      local_cvalue.copy_back(cvalue);
      opt.fail.throw_warning();
    }

    // alt-1
    template <typename COMM>
    void handle_opt_get(COMM &comm, const std::string optstr,
                        types::f77_integer &ivalue, double &rvalue,
                        std::string &cvalue, types::f77_integer &optype) {
      opt::OptionalE04ZN local_opt;

      handle_opt_get(comm, optstr, ivalue, rvalue, cvalue, optype, local_opt);
    }
  }
}
#define e04zn opt::handle_opt_get
#endif
