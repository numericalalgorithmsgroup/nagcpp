// Header for nagcpp::opt::handle_set_nlnconstr (e04rk)

// Copyright 2022, Numerical Algorithms Group Ltd, Oxford, UK.
// Generated by cpp-ft-wrapper.xsl
// Version 28.3.0.0
#ifndef NAGCPP_E04RK_HPP
#define NAGCPP_E04RK_HPP

#include "utility/nagcpp_consts.hpp"
#include "utility/nagcpp_data_handling.hpp"
#include "utility/nagcpp_engine_routines.hpp"
#include "utility/nagcpp_engine_types.hpp"
#include "utility/nagcpp_error_handler.hpp"
#include "utility/nagcpp_utility_comm.hpp"
#include "utility/nagcpp_utility_optional.hpp"

namespace nagcpp {
  namespace opt {
    // handle_set_nlnconstr (e04rk)
    // Define a block of nonlinear constraints to a problem initialized by
    // opt::handle_init (e04ra).
    // opt::handle_set_nlnconstr (e04rk) is a part of the NAG optimization
    // modelling suite and defines or overwrites nonlinear constraints in the
    // model, their number as well as the sparsity structure of their first
    // derivatives.

    // parameters:
    //   comm: opt::CommE04RA, scalar
    //     Communication structure.
    //     An object of either the derived class opt::CommE04RA or its base class
    //     utility::NoneCopyableComm can be supplied.
    //     It is recommended that the derived class is used. If the base class is
    //     supplied it must
    //     first be initialized via a call to opt::handle_init (e04ra).
    //   bl: double, array, shape(ncnln)
    //     bl and bu define lower and upper bounds of the nonlinear constraints, l_g
    //     and u_g, respectively
    //   bu: double, array, shape(ncnln)
    //     bl and bu define lower and upper bounds of the nonlinear constraints, l_g
    //     and u_g, respectively
    //   irowgd: types::f77_integer, array, shape(nnzgd)
    //     Arrays irowgd and icolgd store the sparsity structure (pattern) of the
    //     Jacobian matrix as nnzgd nonzeros in coordinate storage (CS) format (see
    //     the F11 Introduction)
    //   icolgd: types::f77_integer, array, shape(nnzgd)
    //     Arrays irowgd and icolgd store the sparsity structure (pattern) of the
    //     Jacobian matrix as nnzgd nonzeros in coordinate storage (CS) format (see
    //     the F11 Introduction)
    //   opt: opt::OptionalE04RK
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
    //     On entry, nnzgd = <value>.
    //     Constraint: nnzgd > 0.
    //   (errorid 6)
    //     On entry, ncnln = <value>.
    //     Constraint: ncnln >= 0.
    //   (errorid 8)
    //     On entry, i = <value>, irowgd[i-1] = <value> and
    //     ncnln = <value>.
    //     Constraint: 1 <= irowgd[i-1] <= ncnln.
    //   (errorid 8)
    //     On entry, i = <value>, icolgd[i-1] = <value> and
    //     n = <value>.
    //     Constraint: 1 <= icolgd[i-1] <= n.
    //   (errorid 8)
    //     On entry, more than one element of structural Jacobian matrix has row index
    //     <value> and column index <value>.
    //     Constraint: each element of structural Jacobian matrix must have a unique
    //     row and column index.
    //   (errorid 10)
    //     On entry, j = <value>, bl[j-1] = <value> and
    //     bu[j-1] = <value>.
    //     Constraint: bl[j-1] <= bu[j-1].
    //   (errorid 10)
    //     On entry, j = <value>, bl[j-1] = <value>,
    //     bigbnd = <value>.
    //     Constraint: bl[j-1] < bigbnd.
    //   (errorid 10)
    //     On entry, j = <value>, bu[j-1] = <value>,
    //     bigbnd = <value>.
    //     Constraint: bu[j-1] > -bigbnd.
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
#define e04rkft_(en_data, handle, ncnln, bl, bu, nnzgd, irowgd, icolgd,  \
                 errbuf, ifail, errbuf_length)                           \
  E04RKFT(en_data, handle, ncnln, bl, bu, nnzgd, irowgd, icolgd, errbuf, \
          errbuf_length, ifail)
#elif defined(_WIN32) || defined(_WIN64)
#define e04rkft_ E04RKFT
#else
#define E04RKFT e04rkft_
#endif
    extern void NAG_CALL E04RKFT(
      types::engine_data &en_data, void *handle,
      const types::f77_integer &ncnln, const double bl[], const double bu[],
      const types::f77_integer &nnzgd, const types::f77_integer irowgd[],
      const types::f77_integer icolgd[],
      char *errbuf NAG_STDCALL_LEN(errbuf_length),
      types::f77_integer &ifail NAG_NSTDCALL_LEN(errbuf_length));
    }

    class CommE04RA;

    class OptionalE04RK : public utility::Optional {
    public:
      OptionalE04RK() : Optional() {}
      template <typename COMM, typename BL, typename BU, typename IROWGD,
                typename ICOLGD>
      friend void handle_set_nlnconstr(COMM &comm, const BL &bl, const BU &bu,
                                       const IROWGD &irowgd,
                                       const ICOLGD &icolgd,
                                       opt::OptionalE04RK &opt);
    };

    template <typename COMM, typename BL, typename BU, typename IROWGD,
              typename ICOLGD>
    void handle_set_nlnconstr(COMM &comm, const BL &bl, const BU &bu,
                              const IROWGD &irowgd, const ICOLGD &icolgd,
                              opt::OptionalE04RK &opt) {
      opt.fail.prepare("opt::handle_set_nlnconstr (e04rk)");
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
      data_handling::RawData<double, data_handling::ArgIntent::IntentIN,
                             typename std::remove_reference<BL>::type>
        local_bl(bl);
      data_handling::RawData<double, data_handling::ArgIntent::IntentIN,
                             typename std::remove_reference<BU>::type>
        local_bu(bu);
      data_handling::RawData<types::f77_integer,
                             data_handling::ArgIntent::IntentIN,
                             typename std::remove_reference<IROWGD>::type>
        local_irowgd(irowgd);
      data_handling::RawData<types::f77_integer,
                             data_handling::ArgIntent::IntentIN,
                             typename std::remove_reference<ICOLGD>::type>
        local_icolgd(icolgd);

      types::f77_integer local_ncnln =
        data_handling::get_size(opt.fail, "ncnln", local_bl, 1, local_bu, 1);
      types::f77_integer local_nnzgd;
      if (!(static_cast<bool>(local_irowgd.data))) {
        local_nnzgd = 0;
      } else {
        local_nnzgd =
          data_handling::get_size(opt.fail, "nnzgd", local_irowgd, 1);
      }

      local_icolgd.check(opt.fail, "icolgd", false, local_nnzgd);
      if (opt.fail.error_thrown) {
        return;
      }
      local_irowgd.check(opt.fail, "irowgd", false, local_nnzgd);
      if (opt.fail.error_thrown) {
        return;
      }
      local_bu.check(opt.fail, "bu", false, local_ncnln);
      if (opt.fail.error_thrown) {
        return;
      }
      local_bl.check(opt.fail, "bl", false, local_ncnln);
      if (opt.fail.error_thrown) {
        return;
      }

      e04rkft_(en_data, &comm.handle, local_ncnln, local_bl.data, local_bu.data,
               local_nnzgd, local_irowgd.data, local_icolgd.data,
               opt.fail.errbuf, opt.fail.errorid, opt.fail.errbuf_length);

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
        } else if (opt.fail.ierr == 6 && opt.fail.ifmt == 601) {
          opt.fail.set_errorid(6, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(true, "On entry, nnzgd = ", 1, ".");
          opt.fail.append_msg(false, "Constraint: nnzgd > 0.");
        } else if (opt.fail.ierr == 6 && opt.fail.ifmt == 611) {
          opt.fail.set_errorid(6, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(true, "On entry, ncnln = ", 1, ".");
          opt.fail.append_msg(false, "Constraint: ncnln >= 0.");
        } else if (opt.fail.ierr == 8 && opt.fail.ifmt == 811) {
          opt.fail.set_errorid(8, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "On entry, i = ", 1, ", irowgd[i-1] = ", 2,
                              " and");
          opt.fail.append_msg(true, "ncnln = ", 3, ".");
          opt.fail.append_msg(false, "Constraint: 1 <= irowgd[i-1] <= ncnln.");
        } else if (opt.fail.ierr == 8 && opt.fail.ifmt == 812) {
          opt.fail.set_errorid(8, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "On entry, i = ", 1, ", icolgd[i-1] = ", 2,
                              " and");
          opt.fail.append_msg(true, "n = ", 3, ".");
          opt.fail.append_msg(false, "Constraint: 1 <= icolgd[i-1] <= n.");
        } else if (opt.fail.ierr == 8 && opt.fail.ifmt == 813) {
          opt.fail.set_errorid(8, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "On entry, more than one element of "
                                     "structural Jacobian matrix has row "
                                     "index");
          opt.fail.append_msg(true, 1, " and column index ", 2, ".");
          opt.fail.append_msg(false, "Constraint: each element of structural "
                                     "Jacobian matrix must have a unique");
          opt.fail.append_msg(false, "row and column index.");
        } else if (opt.fail.ierr == 10 && opt.fail.ifmt == 1001) {
          opt.fail.set_errorid(10, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "On entry, j = ", 1, ", bl[j-1] = ", 2,
                              " and");
          opt.fail.append_msg(true, "bu[j-1] = ", 3, ".");
          opt.fail.append_msg(false, "Constraint: bl[j-1] <= bu[j-1].");
        } else if (opt.fail.ierr == 10 && opt.fail.ifmt == 1002) {
          opt.fail.set_errorid(10, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "On entry, j = ", 1, ", bl[j-1] = ", 2,
                              ",");
          opt.fail.append_msg(true, "bigbnd = ", 3, ".");
          opt.fail.append_msg(false, "Constraint: bl[j-1] < bigbnd.");
        } else if (opt.fail.ierr == 10 && opt.fail.ifmt == 1003) {
          opt.fail.set_errorid(10, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "On entry, j = ", 1, ", bu[j-1] = ", 2,
                              ",");
          opt.fail.append_msg(true, "bigbnd = ", 3, ".");
          opt.fail.append_msg(false, "Constraint: bu[j-1] > -bigbnd.");
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
    template <typename COMM, typename BL, typename BU, typename IROWGD,
              typename ICOLGD>
    void handle_set_nlnconstr(COMM &comm, const BL &bl, const BU &bu,
                              const IROWGD &irowgd, const ICOLGD &icolgd) {
      opt::OptionalE04RK local_opt;

      handle_set_nlnconstr(comm, bl, bu, irowgd, icolgd, local_opt);
    }
  }
}
#define e04rk opt::handle_set_nlnconstr
#endif
