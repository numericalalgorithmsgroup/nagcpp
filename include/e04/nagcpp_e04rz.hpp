// Header for nagcpp::opt::handle_free (e04rz)

// Copyright 2019, Numerical Algorithms Group Ltd, Oxford, UK.
// Generated by cpp-ft-wrapper.xsl
// Version 27.0.0.0
#ifndef NAGCPP_E04RZ_HPP
#define NAGCPP_E04RZ_HPP

#include "utility/nagcpp_consts.hpp"
#include "utility/nagcpp_data_handling.hpp"
#include "utility/nagcpp_engine_routines.hpp"
#include "utility/nagcpp_engine_types.hpp"
#include "utility/nagcpp_error_handler.hpp"
#include "utility/nagcpp_utility_comm.hpp"
#include "utility/nagcpp_utility_optional.hpp"

namespace nagcpp {
  namespace opt {
    // handle_free (e04rz)
    // Destroy the problem handle initialized by opt::handle_init (e04ra) and
    // deallocate all the memory used.

    // parameters:
    //   comm: opt::CommE04RA, scalar
    //     Communication structure.
    //     An object of either the derived class opt::CommE04RA or its base class
    //     utility::NoneCopyableComm can be supplied.
    //     It is recommended that the derived class is used. If the base class is
    //     supplied it must
    //     first be initialized via a call to opt::handle_init (e04ra).
    //   opt: opt::OptionalE04RZ
    //     Optional parameter container, derived from utility::Optional.
    //     contains:
    //       fail: error_handler::ErrorHandler

    // error_handler::ErrorException
    //   (errorid 1)
    //     comm.handle does not belong to the NAG optimization modelling suite,
    //     has not been initialized properly or is corrupted.
    //   (errorid 1)
    //     comm.handle has not been initialized properly or is corrupted.
    //   (errorid 10605)
    //     On entry, the communication class <value> has not been initialized
    //     correctly.
    //   (errorid -99)
    //     An unexpected error has been triggered by this routine.
    //   (errorid -399)
    //     Your licence key may have expired or may not have been installed correctly.
    //   (errorid -999)
    //     Dynamic memory allocation failed.

    extern "C" {
#if defined(_WIN32) && defined(USE_STDCALL)
#define e04rzft_(en_data, handle, errbuf, ifail, errbuf_length) \
  E04RZFT(en_data, handle, errbuf, errbuf_length, ifail)
#elif defined(_WIN32) || defined(_WIN64)
#define e04rzft_ E04RZFT
#else
#define E04RZFT e04rzft_
#endif
    extern void NAG_CALL
      E04RZFT(types::engine_data &en_data, void *handle,
              char *errbuf NAG_STDCALL_LEN(errbuf_length),
              types::f77_integer &ifail NAG_NSTDCALL_LEN(errbuf_length));
    }

    class CommE04RA;

    class OptionalE04RZ : public utility::Optional {
    public:
      OptionalE04RZ() : Optional() {}
      template <typename COMM>
      friend void handle_free(COMM &comm, opt::OptionalE04RZ &opt);
    };

    template <typename COMM>
    void handle_free(COMM &comm, opt::OptionalE04RZ &opt) {
      opt.fail.prepare("opt::handle_free (e04rz)");
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

      e04rzft_(en_data, &comm.handle, opt.fail.errbuf, opt.fail.errorid,
               opt.fail.errbuf_length);

      if (!(opt.fail.initial_error_handler(en_data))) {
        if (opt.fail.ierr == 1 && opt.fail.ifmt == 101) {
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
        } else {
          opt.fail.set_unexpected_error();
        }
        opt.fail.throw_error();
      }
      if (opt.fail.error_thrown) {
        return;
      }

      comm.handle = nullptr;
      comm.initialized = false;
      opt.fail.throw_warning();
    }

    // alt-1
    template <typename COMM>
    void handle_free(COMM &comm) {
      opt::OptionalE04RZ local_opt;

      handle_free(comm, local_opt);
    }
  }
}
#define e04rz opt::handle_free
#endif
