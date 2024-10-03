// Header for nagcpp::opt::handle_print (e04ry)

// Copyright 2024, Numerical Algorithms Group Ltd, Oxford, UK.
// Generated by cpp-ft-wrapper.xsl
// Version 30.2.0.0
#ifndef NAGCPP_E04RY_HPP
#define NAGCPP_E04RY_HPP

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
    // handle_print (e04ry)
    // Print information about a problem handle initialized by opt::handle_init
    // (e04ra).
    // opt::handle_print (e04ry) is a part of the NAG optimization modelling suite.
    // It allows you to print information about the problem, stored as a handle,
    // such as which parts have already been defined or details of the constraints.

    // parameters:
    //   comm: opt::CommE04RA, scalar
    //     Communication structure.
    //     An object of either the derived class opt::CommE04RA or its base class
    //     utility::NoneCopyableComm can be supplied.
    //     It is recommended that the derived class is used. If the base class is
    //     supplied it must
    //     first be initialized via a call to opt::handle_init (e04ra).
    //   nout: types::f77_integer, scalar
    //     The Fortran unit number which identifies the file to be written to.
    //   cmdstr: std::string, scalar
    //     A command string which contains one or more keywords which identify the
    //     piece of information about the handle to be printed
    //   opt: opt::OptionalE04RY
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
    //   (errorid 6)
    //     On entry, nout = <value>.
    //     Constraint: nout >= 0.
    //   (errorid 7)
    //     Keyword number <value> is not recognized.
    //   (errorid 7)
    //     Keyword number <value> is not recognized, it is too long.
    //   (errorid 7)
    //     cmdstr does not contain any keywords or is empty.
    //   (errorid 199)
    //     An error occurred when writing to output.
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
#define e04ryft_(en_data, print_rec, print_rech, handle, nout, cmdstr, errbuf, \
                 ifail, cmdstr_length, errbuf_length)                          \
  E04RYFT(en_data, print_rec, print_rech, handle, nout, cmdstr, cmdstr_length, \
          errbuf, errbuf_length, ifail)
#elif defined(_WIN32) || defined(_WIN64)
#define e04ryft_ E04RYFT
#else
#define E04RYFT e04ryft_
#endif
    extern void NAG_CALL
      E04RYFT(types::engine_data &en_data, void *print_rec, NAG_PRINT_RECH,
              void *handle, const types::f77_integer &nout,
              const char *cmdstr NAG_STDCALL_LEN(cmdstr_length),
              char *errbuf NAG_STDCALL_LEN(errbuf_length),
              types::f77_integer &ifail NAG_NSTDCALL_LEN(cmdstr_length)
                NAG_NSTDCALL_LEN(errbuf_length));
    }

    class CommE04RA;

    class OptionalE04RY : public utility::Optional {
    public:
      OptionalE04RY() : Optional() {}
      template <typename COMM>
      friend void handle_print(COMM &comm, const types::f77_integer nout,
                               const std::string cmdstr,
                               opt::OptionalE04RY &opt);
    };

    template <typename COMM>
    void handle_print(COMM &comm, const types::f77_integer nout,
                      const std::string cmdstr, opt::OptionalE04RY &opt) {
      opt.fail.prepare("opt::handle_print (e04ry)");
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
        local_cmdstr(cmdstr);

      e04ryft_(en_data, local_print_rec, utility::print_rech, &comm.handle,
               nout, local_cmdstr.data, opt.fail.errbuf, opt.fail.errorid,
               local_cmdstr.string_length, opt.fail.errbuf_length);

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
        } else if (opt.fail.ierr == 6 && opt.fail.ifmt == 620) {
          opt.fail.set_errorid(6, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(true, "On entry, nout = ", 1, ".");
          opt.fail.append_msg(false, "Constraint: nout >= 0.");
        } else if (opt.fail.ierr == 7 && opt.fail.ifmt == 720) {
          opt.fail.set_errorid(7, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "Keyword number ", 1,
                              " is not recognized.");
        } else if (opt.fail.ierr == 7 && opt.fail.ifmt == 721) {
          opt.fail.set_errorid(7, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "Keyword number ", 1,
                              " is not recognized, it is too long.");
        } else if (opt.fail.ierr == 7 && opt.fail.ifmt == 722) {
          opt.fail.set_errorid(7, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "cmdstr does not contain any keywords or "
                                     "is empty.");
        } else if (opt.fail.ierr == 199 && opt.fail.ifmt == 0) {
          opt.fail.set_errorid(199, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "An error occurred when writing to "
                                     "output.");
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
    void handle_print(COMM &comm, const types::f77_integer nout,
                      const std::string cmdstr) {
      opt::OptionalE04RY local_opt;

      handle_print(comm, nout, cmdstr, local_opt);
    }
  }
}
#define e04ry opt::handle_print
#endif
