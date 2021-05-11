// Header for nagcpp::opt::handle_set_simplebounds (e04rh)

// Copyright 2021, Numerical Algorithms Group Ltd, Oxford, UK.
// Generated by cpp-ft-wrapper.xsl
// Version 27.2.0.0
#ifndef NAGCPP_E04RH_HPP
#define NAGCPP_E04RH_HPP

#include "utility/nagcpp_consts.hpp"
#include "utility/nagcpp_data_handling.hpp"
#include "utility/nagcpp_engine_routines.hpp"
#include "utility/nagcpp_engine_types.hpp"
#include "utility/nagcpp_error_handler.hpp"
#include "utility/nagcpp_utility_comm.hpp"
#include "utility/nagcpp_utility_optional.hpp"

namespace nagcpp {
  namespace opt {
    // handle_set_simplebounds (e04rh)
    // Define bounds of variables of a problem initialized by opt::handle_init
    // (e04ra).
    // opt::handle_set_simplebounds (e04rh) is a part of the NAG optimization
    // modelling suite and sets bounds on the variables of the problem.

    // parameters:
    //   comm: opt::CommE04RA, scalar
    //     Communication structure.
    //     An object of either the derived class opt::CommE04RA or its base class
    //     utility::NoneCopyableComm can be supplied.
    //     It is recommended that the derived class is used. If the base class is
    //     supplied it must
    //     first be initialized via a call to opt::handle_init (e04ra).
    //   nvar: types::f77_integer, scalar
    //     n, the current number of decision variables x in the model
    //   bl: double, array, shape(nvar)
    //     bl defines the lower bounds on the variables
    //   bu: double, array, shape(nvar)
    //     bu defines the upper bounds on the variables
    //   opt: opt::OptionalE04RH
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
    //   (errorid 4)
    //     On entry, nvar = <value>,
    //     expected value = <value>.
    //     Constraint: nvar must match the current number of variables
    //     of the model in the comm.handle.
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
#define e04rhft_(en_data, handle, nvar, bl, bu, errbuf, ifail, errbuf_length) \
  E04RHFT(en_data, handle, nvar, bl, bu, errbuf, errbuf_length, ifail)
#elif defined(_WIN32) || defined(_WIN64)
#define e04rhft_ E04RHFT
#else
#define E04RHFT e04rhft_
#endif
    extern void NAG_CALL
      E04RHFT(types::engine_data &en_data, void *handle,
              const types::f77_integer &nvar, const double bl[],
              const double bu[], char *errbuf NAG_STDCALL_LEN(errbuf_length),
              types::f77_integer &ifail NAG_NSTDCALL_LEN(errbuf_length));
    }

    class CommE04RA;

    class OptionalE04RH : public utility::Optional {
    public:
      OptionalE04RH() : Optional() {}
      template <typename COMM, typename BL, typename BU>
      friend void handle_set_simplebounds(COMM &comm, const BL &bl,
                                          const BU &bu,
                                          opt::OptionalE04RH &opt);
    };

    template <typename COMM, typename BL, typename BU>
    void handle_set_simplebounds(COMM &comm, const BL &bl, const BU &bu,
                                 opt::OptionalE04RH &opt) {
      opt.fail.prepare("opt::handle_set_simplebounds (e04rh)");
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
      data_handling::RawData<double, data_handling::ArgIntent::IN,
                             typename std::remove_reference<BL>::type>
        local_bl(bl);
      data_handling::RawData<double, data_handling::ArgIntent::IN,
                             typename std::remove_reference<BU>::type>
        local_bu(bu);

      types::f77_integer local_nvar =
        data_handling::get_size(opt.fail, "nvar", local_bl, 1, local_bu, 1);
      if (opt.fail.error_thrown) {
        return;
      }

      local_bu.check(opt.fail, "bu", true, local_nvar);
      if (opt.fail.error_thrown) {
        return;
      }
      local_bl.check(opt.fail, "bl", true, local_nvar);
      if (opt.fail.error_thrown) {
        return;
      }

      e04rhft_(en_data, &comm.handle, local_nvar, local_bl.data, local_bu.data,
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
        } else if (opt.fail.ierr == 4 && opt.fail.ifmt == 401) {
          opt.fail.set_errorid(4, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "On entry, nvar = ", 1, ",");
          opt.fail.append_msg(true, "expected value = ", 2, ".");
          opt.fail.append_msg(false, "Constraint: nvar must match the current "
                                     "number of variables");
          opt.fail.append_msg(false, "of the model in the comm.handle.");
        } else if (opt.fail.ierr == 10 && opt.fail.ifmt == 1004) {
          opt.fail.set_errorid(10, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "On entry, j = ", 1, ", bl[j-1] = ", 2,
                              " and");
          opt.fail.append_msg(true, "bu[j-1] = ", 3, ".");
          opt.fail.append_msg(false, "Constraint: bl[j-1] <= bu[j-1].");
        } else if (opt.fail.ierr == 10 && opt.fail.ifmt == 1005) {
          opt.fail.set_errorid(10, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "On entry, j = ", 1, ", bl[j-1] = ", 2,
                              ",");
          opt.fail.append_msg(true, "bigbnd = ", 3, ".");
          opt.fail.append_msg(false, "Constraint: bl[j-1] < bigbnd.");
        } else if (opt.fail.ierr == 10 && opt.fail.ifmt == 1006) {
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
    template <typename COMM, typename BL, typename BU>
    void handle_set_simplebounds(COMM &comm, const BL &bl, const BU &bu) {
      opt::OptionalE04RH local_opt;

      handle_set_simplebounds(comm, bl, bu, local_opt);
    }
  }
}
#define e04rh opt::handle_set_simplebounds
#endif
