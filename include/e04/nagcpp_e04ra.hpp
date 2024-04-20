// Header for nagcpp::opt::handle_init (e04ra)

// Copyright 2024, Numerical Algorithms Group Ltd, Oxford, UK.
// Generated by cpp-ft-wrapper.xsl
// Version 30.0.0.0
#ifndef NAGCPP_E04RA_HPP
#define NAGCPP_E04RA_HPP

#include "utility/nagcpp_consts.hpp"
#include "utility/nagcpp_data_handling.hpp"
#include "utility/nagcpp_engine_routines.hpp"
#include "utility/nagcpp_engine_types.hpp"
#include "utility/nagcpp_error_handler.hpp"
#include "utility/nagcpp_utility_comm.hpp"
#include "utility/nagcpp_utility_optional.hpp"

namespace nagcpp {
  namespace opt {
    // handle_init (e04ra)
    // Initialization of a handle for the NAG optimization modelling suite for
    // problems, such as, linear programming (LP), quadratic programming (QP),
    // nonlinear programming (NLP), least squares (LSQ) problems, linear
    // semidefinite programming (SDP) or SDP with bilinear matrix inequalities
    // (BMI-SDP).
    // opt::handle_init (e04ra) initializes a data structure for the NAG
    // optimization modelling suite for problems such as, Linear Programming (LP),
    // Quadratic Programming (QP), Nonlinear Programming (NLP), Least Squares (LSQ)
    // problems, Second-order Cone Programming (SOCP), linear Semidefinite
    // Programming (SDP) and Semidefinite Programming with Bilinear Matrix
    // Inequalities (BMI-SDP).

    // parameters:
    //   comm: opt::CommE04RA, scalar
    //     Communication structure.
    //   nvar: types::f77_integer, scalar
    //     n, the initial number of decision variables defining the problem
    //   opt: opt::OptionalE04RA
    //     Optional parameter container, derived from utility::Optional.
    //     contains:
    //       fail: error_handler::ErrorHandler

    // error_handler::ErrorException
    //   (errorid 6)
    //     On entry, nvar = <value>.
    //     Constraint: nvar >= 0.
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
#define e04raft_(en_data, handle, nvar, errbuf, ifail, errbuf_length) \
  E04RAFT(en_data, handle, nvar, errbuf, errbuf_length, ifail)
#elif defined(_WIN32) || defined(_WIN64)
#define e04raft_ E04RAFT
#else
#define E04RAFT e04raft_
#endif
    extern void NAG_CALL E04RAFT(
      types::engine_data &en_data, void *handle, const types::f77_integer &nvar,
      char *errbuf NAG_STDCALL_LEN(errbuf_length),
      types::f77_integer &ifail NAG_NSTDCALL_LEN(errbuf_length));
    }

    class CommE04RA;

    class OptionalE04RA : public utility::Optional {
    public:
      OptionalE04RA() : Optional() {}
      template <typename COMM>
      friend void handle_init(COMM &comm, const types::f77_integer nvar,
                              opt::OptionalE04RA &opt);
    };

    template <typename COMM>
    void handle_init(COMM &comm, const types::f77_integer nvar,
                     opt::OptionalE04RA &opt) {
      opt.fail.prepare("opt::handle_init (e04ra)");
      types::engine_data en_data;
      engine_routines::y90haan_(en_data);
      en_data.allocate_workspace = constants::NAG_ED_YES;
      static_assert(std::is_same<COMM, utility::NoneCopyableComm>::value ||
                      std::is_same<COMM, opt::CommE04RA>::value,
                    "Invalid type for comm: must be either "
                    "utility::NoneCopyableComm or opt::CommE04RA");

      e04raft_(en_data, &comm.handle, nvar, opt.fail.errbuf, opt.fail.errorid,
               opt.fail.errbuf_length);

      if (!(opt.fail.initial_error_handler(en_data))) {
        if (opt.fail.ierr == 6 && opt.fail.ifmt == 600) {
          opt.fail.set_errorid(6, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(true, "On entry, nvar = ", 1, ".");
          opt.fail.append_msg(false, "Constraint: nvar >= 0.");
        } else {
          opt.fail.set_unexpected_error();
        }
        opt.fail.throw_error();
      }
      if (opt.fail.error_thrown) {
        return;
      }

      comm.initialized = true;
      opt.fail.throw_warning();
    }

    // alt-1
    template <typename COMM>
    void handle_init(COMM &comm, const types::f77_integer nvar) {
      opt::OptionalE04RA local_opt;

      handle_init(comm, nvar, local_opt);
    }
  }
}
#define e04ra opt::handle_init
#endif
