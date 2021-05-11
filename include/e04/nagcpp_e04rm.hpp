// Header for nagcpp::opt::handle_set_nlnls (e04rm)

// Copyright 2021, Numerical Algorithms Group Ltd, Oxford, UK.
// Generated by cpp-ft-wrapper.xsl
// Version 27.2.0.0
#ifndef NAGCPP_E04RM_HPP
#define NAGCPP_E04RM_HPP

#include "utility/nagcpp_consts.hpp"
#include "utility/nagcpp_data_handling.hpp"
#include "utility/nagcpp_engine_routines.hpp"
#include "utility/nagcpp_engine_types.hpp"
#include "utility/nagcpp_error_handler.hpp"
#include "utility/nagcpp_utility_comm.hpp"
#include "utility/nagcpp_utility_optional.hpp"

namespace nagcpp {
  namespace opt {
    // handle_set_nlnls (e04rm)
    // Define a nonlinear least squares objective function for a problem
    // initialized by opt::handle_init (e04ra).
    // opt::handle_set_nlnls (e04rm) is a part of the NAG optimization modelling
    // suite and declares the objective function of the problem as a sum of squares
    // (for nonlinear least squares problems) with the given number of residuals
    // and, optionally, the sparsity structure of their first derivatives.

    // parameters:
    //   comm: opt::CommE04RA, scalar
    //     Communication structure.
    //     An object of either the derived class opt::CommE04RA or its base class
    //     utility::NoneCopyableComm can be supplied.
    //     It is recommended that the derived class is used. If the base class is
    //     supplied it must
    //     first be initialized via a call to opt::handle_init (e04ra).
    //   nres: types::f77_integer, scalar
    //     m_r, the number of residuals in the objective function
    //   irowrd: types::f77_integer, array, shape(nnzrd)
    //     Arrays irowrd and icolrd store the sparsity structure (pattern) of the
    //     first derivative matrix as nnzrd nonzeros in coordinate storage (CS)
    //     format (see the F11 Introduction)
    //   icolrd: types::f77_integer, array, shape(nnzrd)
    //     Arrays irowrd and icolrd store the sparsity structure (pattern) of the
    //     first derivative matrix as nnzrd nonzeros in coordinate storage (CS)
    //     format (see the F11 Introduction)
    //   opt: opt::OptionalE04RM
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
    //   (errorid 6)
    //     On entry, nres = <value>.
    //     Constraint: nres >= 0.
    //   (errorid 6)
    //     On entry, nnzrd = <value>.
    //     Constraint: nnzrd > 0.
    //   (errorid 8)
    //     On entry, i = <value>, irowrd[i-1] = <value> and
    //     n = <value>.
    //     Constraint: 1 <= irowrd[i-1] <= n.
    //   (errorid 8)
    //     On entry, i = <value>, icolrd[i-1] = <value> and
    //     nres = <value>.
    //     Constraint: 1 <= icolrd[i-1] <= nres.
    //   (errorid 8)
    //     On entry, more than one element of first derivative matrix has row index
    //     <value> and column index <value>.
    //     Constraint: each element of first derivative matrix must have a unique
    //     row and column index.
    //   (errorid 9)
    //     All of the following must be provided if one is provided:
    //     irowrd, icolrd.
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
#define e04rmft_(en_data, handle, nres, isparse, nnzrd, irowrd, icolrd,  \
                 errbuf, ifail, errbuf_length)                           \
  E04RMFT(en_data, handle, nres, isparse, nnzrd, irowrd, icolrd, errbuf, \
          errbuf_length, ifail)
#elif defined(_WIN32) || defined(_WIN64)
#define e04rmft_ E04RMFT
#else
#define E04RMFT e04rmft_
#endif
    extern void NAG_CALL E04RMFT(
      types::engine_data &en_data, void *handle, const types::f77_integer &nres,
      const types::f77_integer &isparse, const types::f77_integer &nnzrd,
      const types::f77_integer irowrd[], const types::f77_integer icolrd[],
      char *errbuf NAG_STDCALL_LEN(errbuf_length),
      types::f77_integer &ifail NAG_NSTDCALL_LEN(errbuf_length));
    }

    class CommE04RA;

    class OptionalE04RM : public utility::Optional {
    public:
      OptionalE04RM() : Optional() {}
      template <typename COMM, typename IROWRD, typename ICOLRD>
      friend void handle_set_nlnls(COMM &comm, const types::f77_integer nres,
                                   const IROWRD &irowrd, const ICOLRD &icolrd,
                                   opt::OptionalE04RM &opt);
    };

    template <typename COMM, typename IROWRD, typename ICOLRD>
    void handle_set_nlnls(COMM &comm, const types::f77_integer nres,
                          const IROWRD &irowrd, const ICOLRD &icolrd,
                          opt::OptionalE04RM &opt) {
      opt.fail.prepare("opt::handle_set_nlnls (e04rm)");
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
      data_handling::RawData<types::f77_integer, data_handling::ArgIntent::IN,
                             typename std::remove_reference<IROWRD>::type>
        local_irowrd(irowrd);
      data_handling::RawData<types::f77_integer, data_handling::ArgIntent::IN,
                             typename std::remove_reference<ICOLRD>::type>
        local_icolrd(icolrd);

      types::f77_integer local_isparse;
      if (!(static_cast<bool>(local_irowrd.data))) {
        local_isparse = 0;
      } else {
        local_isparse = 1;
      }
      types::f77_integer local_nnzrd;
      if (!(static_cast<bool>(local_irowrd.data))) {
        local_nnzrd = 0;
      } else {
        local_nnzrd =
          data_handling::get_size(opt.fail, "nnzrd", local_irowrd, 1);
      }

      local_icolrd.check(opt.fail, "icolrd", false, local_nnzrd);
      if (opt.fail.error_thrown) {
        return;
      }
      local_irowrd.check(opt.fail, "irowrd", false, local_nnzrd);
      if (opt.fail.error_thrown) {
        return;
      }
      if (!(static_cast<bool>(local_irowrd.data)) !=
          !(static_cast<bool>(local_icolrd.data))) {
        opt.fail.set_errorid(9, error_handler::ErrorCategory::Error,
                             error_handler::ErrorType::GeneralError);
        opt.fail.append_msg(false, "All of the following must be provided if "
                                   "one is provided:");
        opt.fail.append_msg(false, "irowrd, icolrd.");
        opt.fail.throw_error();
      }

      e04rmft_(en_data, &comm.handle, nres, local_isparse, local_nnzrd,
               local_irowrd.data, local_icolrd.data, opt.fail.errbuf,
               opt.fail.errorid, opt.fail.errbuf_length);

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
        } else if (opt.fail.ierr == 6 && opt.fail.ifmt == 602) {
          opt.fail.set_errorid(6, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(true, "On entry, nres = ", 1, ".");
          opt.fail.append_msg(false, "Constraint: nres >= 0.");
        } else if (opt.fail.ierr == 6 && opt.fail.ifmt == 603) {
          opt.fail.set_errorid(6, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(true, "On entry, nnzrd = ", 1, ".");
          opt.fail.append_msg(false, "Constraint: nnzrd > 0.");
        } else if (opt.fail.ierr == 8 && opt.fail.ifmt == 811) {
          opt.fail.set_errorid(8, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "On entry, i = ", 1, ", irowrd[i-1] = ", 2,
                              " and");
          opt.fail.append_msg(true, "n = ", 3, ".");
          opt.fail.append_msg(false, "Constraint: 1 <= irowrd[i-1] <= n.");
        } else if (opt.fail.ierr == 8 && opt.fail.ifmt == 812) {
          opt.fail.set_errorid(8, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "On entry, i = ", 1, ", icolrd[i-1] = ", 2,
                              " and");
          opt.fail.append_msg(true, "nres = ", 3, ".");
          opt.fail.append_msg(false, "Constraint: 1 <= icolrd[i-1] <= nres.");
        } else if (opt.fail.ierr == 8 && opt.fail.ifmt == 813) {
          opt.fail.set_errorid(8, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "On entry, more than one element of first "
                                     "derivative matrix has row index");
          opt.fail.append_msg(true, 1, " and column index ", 2, ".");
          opt.fail.append_msg(false, "Constraint: each element of first "
                                     "derivative matrix must have a unique");
          opt.fail.append_msg(false, "row and column index.");
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
    template <typename COMM, typename IROWRD, typename ICOLRD>
    void handle_set_nlnls(COMM &comm, const types::f77_integer nres,
                          const IROWRD &irowrd, const ICOLRD &icolrd) {
      opt::OptionalE04RM local_opt;

      handle_set_nlnls(comm, nres, irowrd, icolrd, local_opt);
    }
  }
}
#define e04rm opt::handle_set_nlnls
#endif
