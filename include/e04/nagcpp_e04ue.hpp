// Header for nagcpp::opt::nlp1_option_string (e04ue)

// Copyright 2021, Numerical Algorithms Group Ltd, Oxford, UK.
// Generated by cpp-ft-wrapper.xsl
// Version 27.3.0.0
#ifndef NAGCPP_E04UE_HPP
#define NAGCPP_E04UE_HPP

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
    // nlp1_option_string (e04ue)
    // Supply option values to opt::nlp1_solve (e04uc) or opt::nlp1_rcomm (e04uf)
    // from a character string.
    // opt::nlp1_option_string (e04ue) may be used to supply individual options to
    // opt::nlp1_solve (e04uc)
    // opt::nlp1_option_string (e04ue) can also be used to supply individual
    // options to opt::nlp1_rcomm (e04uf).

    // parameters:
    //   optstr: std::string, scalar
    //     A single valid option string (as described in Description and in Optional
    //     Parameters).
    //   comm: opt::CommE04WB, scalar
    //     Communication structure
    //     An object of either the derived class opt::CommE04WB or its base class
    //     utility::CopyableComm can be supplied.
    //     It is recommended that the derived class is used. If the base class is
    //     supplied it must
    //     first be initialized via a call to opt::nlp1_init (e04wb).
    //   opt: opt::OptionalE04UE
    //     Optional parameter container, derived from utility::Optional.
    //     contains:
    //       fail: error_handler::ErrorHandler

    // error_handler::ErrorException
    //   (errorid 5)
    //     The supplied option string is invalid. Supplied value was:
    //     <value>.
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
#define e04ueft_(en_data, print_rec, print_rech, optstr, dlist, routine_name, \
                 lwsav, iwsav, rwsav, inform, optstr_length,                  \
                 routine_name_length)                                         \
  E04UEFT(en_data, print_rec, print_rech, optstr, str_length, dlist,          \
          routine_name, routine_name_length, lwsav, iwsav, rwsav, inform)
#elif defined(_WIN32) || defined(_WIN64)
#define e04ueft_ E04UEFT
#else
#define E04UEFT e04ueft_
#endif
    extern void NAG_CALL E04UEFT(
      types::engine_data &en_data, void *print_rec, NAG_PRINT_RECH,
      const char *optstr NAG_STDCALL_LEN(str_length),
      const types::f77_logical &dlist,
      const char *routine_name NAG_STDCALL_LEN(routine_name_length),
      types::f77_logical lwsav[], types::f77_integer iwsav[], double rwsav[],
      types::f77_integer &inform NAG_NSTDCALL_LEN(str_length)
        NAG_NSTDCALL_LEN(routine_name_length));
    }

    class CommE04WB;

    class OptionalE04UE : public utility::Optional {
    public:
      OptionalE04UE() : Optional() {}
      template <typename COMM>
      friend void nlp1_option_string(const std::string optstr, COMM &comm,
                                     opt::OptionalE04UE &opt);
    };

    template <typename COMM>
    void nlp1_option_string(const std::string optstr, COMM &comm,
                            opt::OptionalE04UE &opt) {
      opt.fail.prepare("opt::nlp1_option_string (e04ue)", false);
      types::engine_data en_data;
      engine_routines::y90haan_(en_data);
      en_data.allocate_workspace = constants::NAG_ED_YES;
      static_assert(std::is_same<COMM, utility::CopyableComm>::value ||
                      std::is_same<COMM, opt::CommE04WB>::value,
                    "Invalid type for comm: must be either "
                    "utility::CopyableComm or opt::CommE04WB");
      if (!(comm.check())) {
        opt.fail.raise_error_comm_invalid("comm");
        if (opt.fail.error_thrown) {
          return;
        }
      }

      void *local_print_rec = static_cast<void *>(&opt.iomanager);
      data_handling::StringRawData<data_handling::ArgIntent::IntentIN>
        local_optstr(optstr);
      types::f77_logical local_dlist = false;
      data_handling::StringRawData<data_handling::ArgIntent::IntentIN>
        local_routine_name("e04ue ");

      e04ueft_(en_data, local_print_rec, utility::print_rech, local_optstr.data,
               local_dlist, local_routine_name.data, comm.lcomm, comm.icomm,
               comm.rcomm, opt.fail.errorid, local_optstr.string_length,
               local_routine_name.string_length);

      if (!(opt.fail.initial_error_handler(en_data))) {
        if (opt.fail.ierr == 5) {
          opt.fail.set_errorid(5, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "The supplied option string is invalid. "
                                     "Supplied value was:");
          opt.fail.append_msg(false, optstr + ".");
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
    void nlp1_option_string(const std::string optstr, COMM &comm) {
      opt::OptionalE04UE local_opt;

      nlp1_option_string(optstr, comm, local_opt);
    }
  }
}
#define e04ue opt::nlp1_option_string
#endif
