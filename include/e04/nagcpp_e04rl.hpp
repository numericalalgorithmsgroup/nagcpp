// Header for nagcpp::opt::handle_set_nlnhess (e04rl)

// Copyright 2023, Numerical Algorithms Group Ltd, Oxford, UK.
// Generated by cpp-ft-wrapper.xsl
// Version 29.1.0.0
#ifndef NAGCPP_E04RL_HPP
#define NAGCPP_E04RL_HPP

#include "utility/nagcpp_consts.hpp"
#include "utility/nagcpp_data_handling.hpp"
#include "utility/nagcpp_engine_routines.hpp"
#include "utility/nagcpp_engine_types.hpp"
#include "utility/nagcpp_error_handler.hpp"
#include "utility/nagcpp_utility_comm.hpp"
#include "utility/nagcpp_utility_optional.hpp"

namespace nagcpp {
  namespace opt {
    // handle_set_nlnhess (e04rl)
    // Define a structure of Hessian of the objective, constraints or the
    // Lagrangian to a problem initialized by opt::handle_init (e04ra).
    // opt::handle_set_nlnhess (e04rl) is a part of the NAG optimization modelling
    // suite and defines or redefines either the structure of the Hessians of the
    // nonlinear objective and constraints or the structure of the Hessian of the
    // Lagrangian.

    // parameters:
    //   comm: opt::CommE04RA, scalar
    //     Communication structure.
    //     An object of either the derived class opt::CommE04RA or its base class
    //     utility::NoneCopyableComm can be supplied.
    //     It is recommended that the derived class is used. If the base class is
    //     supplied it must
    //     first be initialized via a call to opt::handle_init (e04ra).
    //   idf: types::f77_integer, scalar
    //     Specifies the functions for which a Hessian sparsity structure is provided
    //     in nnzh, irowh and icolh
    //   irowh: types::f77_integer, array, shape(nnzh)
    //     Arrays irowh and icolh store the nonzeros of the upper triangle of the
    //     matrix H in coordinate storage (CS) format (see the F11 Introduction)
    //   icolh: types::f77_integer, array, shape(nnzh)
    //     Arrays irowh and icolh store the nonzeros of the upper triangle of the
    //     matrix H in coordinate storage (CS) format (see the F11 Introduction)
    //   opt: opt::OptionalE04RL
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
    //     The problem cannot be modified right now, the solver is running.
    //   (errorid 2)
    //     Neither nonlinear objective nor nonlinear constraints are present.
    //     The structure of the Hessian cannot be defined.
    //   (errorid 2)
    //     No nonlinear objective has been defined, its Hessian cannot be set.
    //   (errorid 6)
    //     On entry, nnzh = <value>.
    //     Constraint: nnzh > 0.
    //   (errorid 7)
    //     On entry, idf = <value>.
    //     Constraint: -1 <= idf <= <value>.
    //   (errorid 8)
    //     On entry, i = <value>, irowh[i-1] = <value> and
    //     n = <value>.
    //     Constraint: 1 <= irowh[i-1] <= n.
    //   (errorid 8)
    //     On entry, i = <value>, icolh[i-1] = <value> and
    //     n = <value>.
    //     Constraint: 1 <= icolh[i-1] <= n.
    //   (errorid 8)
    //     On entry, i = <value>, irowh[i-1] = <value> and
    //     icolh[i-1] = <value>.
    //     Constraint: irowh[i-1] <= icolh[i-1] (elements within the upper triangle).
    //   (errorid 8)
    //     On entry, more than one element of structural matrix H has row index
    //     <value> and column index <value>.
    //     Constraint: each element of structural matrix H must have a unique row
    //     and column index.
    //   (errorid 10601)
    //     On entry, argument <value> must be a vector of size <value> array.
    //     Supplied argument has <value> dimensions.
    //   (errorid 10601)
    //     On entry, argument <value> must be a vector of size <value> array.
    //     Supplied argument was a vector of size <value>.
    //   (errorid 10601)
    //     On entry, argument <value> must be a vector of size <value> array.
    //     The size for the supplied array could not be ascertained.
    //   (errorid 10602)
    //     On entry, the raw data component of <value> is null.
    //   (errorid 10603)
    //     On entry, unable to ascertain a value for <value>.
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
#define e04rlft_(en_data, handle, idf, nnzh, irowh, icolh, errbuf, ifail,  \
                 errbuf_length)                                            \
  E04RLFT(en_data, handle, idf, nnzh, irowh, icolh, errbuf, errbuf_length, \
          ifail)
#elif defined(_WIN32) || defined(_WIN64)
#define e04rlft_ E04RLFT
#else
#define E04RLFT e04rlft_
#endif
    extern void NAG_CALL E04RLFT(
      types::engine_data &en_data, void *handle, const types::f77_integer &idf,
      const types::f77_integer &nnzh, const types::f77_integer irowh[],
      const types::f77_integer icolh[],
      char *errbuf NAG_STDCALL_LEN(errbuf_length),
      types::f77_integer &ifail NAG_NSTDCALL_LEN(errbuf_length));
    }

    class CommE04RA;

    class OptionalE04RL : public utility::Optional {
    public:
      OptionalE04RL() : Optional() {}
      template <typename COMM, typename IROWH, typename ICOLH>
      friend void handle_set_nlnhess(COMM &comm, const types::f77_integer idf,
                                     const IROWH &irowh, const ICOLH &icolh,
                                     opt::OptionalE04RL &opt);
    };

    template <typename COMM, typename IROWH, typename ICOLH>
    void handle_set_nlnhess(COMM &comm, const types::f77_integer idf,
                            const IROWH &irowh, const ICOLH &icolh,
                            opt::OptionalE04RL &opt) {
      opt.fail.prepare("opt::handle_set_nlnhess (e04rl)");
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
      data_handling::RawData<types::f77_integer,
                             data_handling::ArgIntent::IntentIN,
                             typename std::remove_reference<IROWH>::type>
        local_irowh(irowh);
      data_handling::RawData<types::f77_integer,
                             data_handling::ArgIntent::IntentIN,
                             typename std::remove_reference<ICOLH>::type>
        local_icolh(icolh);

      types::f77_integer local_nnzh;
      if (!(static_cast<bool>(local_irowh.data))) {
        local_nnzh = 0;
      } else {
        local_nnzh = data_handling::get_size(opt.fail, "nnzh", local_irowh, 1);
      }

      local_icolh.check(opt.fail, "icolh", false, local_nnzh);
      if (opt.fail.error_thrown) {
        return;
      }
      local_irowh.check(opt.fail, "irowh", false, local_nnzh);
      if (opt.fail.error_thrown) {
        return;
      }

      e04rlft_(en_data, &comm.handle, idf, local_nnzh, local_irowh.data,
               local_icolh.data, opt.fail.errbuf, opt.fail.errorid,
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
        } else if (opt.fail.ierr == 2 && opt.fail.ifmt == 201) {
          opt.fail.set_errorid(2, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "The problem cannot be modified right "
                                     "now, the solver is running.");
        } else if (opt.fail.ierr == 2 && opt.fail.ifmt == 202) {
          opt.fail.set_errorid(2, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "Neither nonlinear objective nor "
                                     "nonlinear constraints are present.");
          opt.fail.append_msg(false, "The structure of the Hessian cannot be "
                                     "defined.");
        } else if (opt.fail.ierr == 2 && opt.fail.ifmt == 203) {
          opt.fail.set_errorid(2, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "No nonlinear objective has been defined, "
                                     "its Hessian cannot be set.");
        } else if (opt.fail.ierr == 6 && opt.fail.ifmt == 601) {
          opt.fail.set_errorid(6, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(true, "On entry, nnzh = ", 1, ".");
          opt.fail.append_msg(false, "Constraint: nnzh > 0.");
        } else if (opt.fail.ierr == 7 && opt.fail.ifmt == 701) {
          opt.fail.set_errorid(7, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(true, "On entry, idf = ", 1, ".");
          opt.fail.append_msg(false, "Constraint: -1 <= idf <= ", 2, ".");
        } else if (opt.fail.ierr == 8 && opt.fail.ifmt == 801) {
          opt.fail.set_errorid(8, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "On entry, i = ", 1, ", irowh[i-1] = ", 2,
                              " and");
          opt.fail.append_msg(true, "n = ", 3, ".");
          opt.fail.append_msg(false, "Constraint: 1 <= irowh[i-1] <= n.");
        } else if (opt.fail.ierr == 8 && opt.fail.ifmt == 802) {
          opt.fail.set_errorid(8, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "On entry, i = ", 1, ", icolh[i-1] = ", 2,
                              " and");
          opt.fail.append_msg(true, "n = ", 3, ".");
          opt.fail.append_msg(false, "Constraint: 1 <= icolh[i-1] <= n.");
        } else if (opt.fail.ierr == 8 && opt.fail.ifmt == 803) {
          opt.fail.set_errorid(8, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "On entry, i = ", 1, ", irowh[i-1] = ", 2,
                              " and");
          opt.fail.append_msg(true, "icolh[i-1] = ", 3, ".");
          opt.fail.append_msg(false, "Constraint: irowh[i-1] <= icolh[i-1] "
                                     "(elements within the upper triangle).");
        } else if (opt.fail.ierr == 8 && opt.fail.ifmt == 804) {
          opt.fail.set_errorid(8, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "On entry, more than one element of "
                                     "structural matrix H has row index");
          opt.fail.append_msg(true, 1, " and column index ", 2, ".");
          opt.fail.append_msg(false, "Constraint: each element of structural "
                                     "matrix H must have a unique row");
          opt.fail.append_msg(false, "and column index.");
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
    template <typename COMM, typename IROWH, typename ICOLH>
    void handle_set_nlnhess(COMM &comm, const types::f77_integer idf,
                            const IROWH &irowh, const ICOLH &icolh) {
      opt::OptionalE04RL local_opt;

      handle_set_nlnhess(comm, idf, irowh, icolh, local_opt);
    }
  }
}
#define e04rl opt::handle_set_nlnhess
#endif
