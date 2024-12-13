// Header for nagcpp::matop::real_nmf_rcomm (f01sb)

// Copyright 2024, Numerical Algorithms Group Ltd, Oxford, UK.
// Generated by cpp-ft-wrapper.xsl
// Version 30.3.0.0
#ifndef NAGCPP_F01SB_HPP
#define NAGCPP_F01SB_HPP

#include "utility/nagcpp_consts.hpp"
#include "utility/nagcpp_data_handling.hpp"
#include "utility/nagcpp_engine_routines.hpp"
#include "utility/nagcpp_engine_types.hpp"
#include "utility/nagcpp_error_handler.hpp"
#include "utility/nagcpp_utility_comm.hpp"
#include "utility/nagcpp_utility_optional.hpp"

namespace nagcpp {
  namespace matop {
    // real_nmf_rcomm (f01sb)
    // Non-negative matrix factorization of real non-negative matrix (reverse
    // communication).
    // matop::real_nmf_rcomm (f01sb) computes a non-negative matrix factorization
    // for a real non-negative m*n matrix A.
    // It uses reverse communication for evaluating matrix products, so that the
    // matrix A is not accessed explicitly.

    // parameters:
    //   irevcm: types::f77_integer, scalar
    //     On initial entry: must be set to 0
    //     On intermediate exit: specifies what action you must take before
    //     re-entering matop::real_nmf_rcomm (f01sb) with irevcm unchanged
    //     On final exit: irevcm = 0
    //   ldht: types::f77_integer, scalar
    //     The first dimension of the array ht.
    //   m: types::f77_integer, scalar
    //     m, the number of rows of the matrix A
    //   n: types::f77_integer, scalar
    //     n, the number of columns of the matrix A
    //   k: types::f77_integer, scalar
    //     k, the number of columns of the matrix W
    //   w: double, array, shape(m, k)
    //     On initial entry:
    //     if seed <= 0, w should be set to an initial iterate for the non-negative
    //     matrix factor, W
    //     If seed >= 1, w need not be set
    //     On intermediate exit: if irevcm = 1 or 2, w contains the current iterate
    //     of the m*k non-negative matrix W
    //     On intermediate entry:
    //     if irevcm = 3, w must contain AH^T, where H^T is stored in ht
    //     If irevcm = 0, 1 or 2, w must not be changed
    //     On final exit: w contains the m*k non-negative matrix W
    //   ldw: types::f77_integer, scalar
    //     The first dimension of the array w.
    //   h: double, array, shape(k, n)
    //     On initial entry:
    //     if seed <= 0, h should be set to an initial iterate for the non-negative
    //     matrix factor, H
    //     If seed >= 1, h need not be set
    //     On intermediate exit: if irevcm = 1, h contains the current iterate of the
    //     k*n non-negative matrix H
    //     On intermediate entry: h must not be changed
    //     On final exit: h contains the k*n non-negative matrix H
    //   ldh: types::f77_integer, scalar
    //     The first dimension of the array h.
    //   ht: double, array, shape(n, k)
    //     On initial entry: ht need not be set
    //     On intermediate exit: if irevcm = 3, ht contains the n*k non-negative
    //     matrix H^T, which is required in order to form AH^T
    //     On intermediate entry: if irevcm = 2, ht must contain A^TW
    //     On final exit: ht is undefined
    //   comm: utility::CopyableComm
    //     Communication structure.
    //     On initial entry: need not be set.
    //   opt: matop::OptionalF01SB
    //     Optional parameter container, derived from utility::Optional.
    //     contains:
    //       seed: types::f77_integer, scalar
    //         On initial entry:
    //         if seed <= 0, the supplied values of W and H are used for the initial
    //         iterate
    //         If seed >= 1, the value of seed is used to seed a random number
    //         generator for the initial iterates W and H
    //         default value: 1
    //       errtol: double, scalar
    //         The convergence tolerance for when the Hierarchical Alternating Least
    //         Squares iteration has reached a stationary point
    //         default value: 0.0
    //       fail: error_handler::ErrorHandler

    // error_handler::ErrorException
    //   (errorid 1)
    //     On intermediate re-entry, irevcm = <value>.
    //     Constraint: irevcm = 1, 2 or 3.
    //   (errorid 1)
    //     On initial entry, irevcm = <value>.
    //     Constraint: irevcm = 0.
    //   (errorid 2)
    //     On entry, m = <value>.
    //     Constraint: m >= 2.
    //   (errorid 3)
    //     On entry, n = <value>.
    //     Constraint: n >= 2.
    //   (errorid 4)
    //     On entry, k = <value>, m = <value> and
    //     n = <value>.
    //     Constraint: 1 <= k < min(m, n).
    //   (errorid 8)
    //     An internal error occurred when generating initial values for w and h.
    //     Please contact NAG.
    //   (errorid 9)
    //     On entry, one of more of the elements of w or h were negative.
    //   (errorid 10601)
    //     On entry, argument <value> must be a <value> x <value> array.
    //     Supplied argument has <value> dimensions.
    //   (errorid 10601)
    //     On entry, argument <value> must be a <value> x <value> array.
    //     Supplied argument was a <value> x <value> array.
    //   (errorid 10601)
    //     On entry, argument <value> must be a <value> x <value> array.
    //     Not all of the sizes for the supplied array could be ascertained.
    //   (errorid 10602)
    //     On entry, the raw data component of <value> is null.
    //   (errorid 10603)
    //     On entry, unable to ascertain a value for <value>.
    //   (errorid 10604)
    //     On entry, the data in <value> is stored in <value> Major Order.
    //     The data was expected to be in <value> Major Order.
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
#define f01sbft_(en_data, irevcm, m, n, k, w, ldw, h, ldh, ht, ldht, seed,  \
                 errtol, comm, icomm, errbuf, ifail, errbuf_length)         \
  F01SBFT(en_data, irevcm, m, n, k, w, ldw, h, ldh, ht, ldht, seed, errtol, \
          comm, icomm, errbuf, errbuf_length, ifail)
#elif defined(_WIN32) || defined(_WIN64)
#define f01sbft_ F01SBFT
#else
#define F01SBFT f01sbft_
#endif
    extern void NAG_CALL F01SBFT(
      types::engine_data &en_data, types::f77_integer &irevcm,
      const types::f77_integer &m, const types::f77_integer &n,
      const types::f77_integer &k, double w[], const types::f77_integer &ldw,
      double h[], const types::f77_integer &ldh, double ht[],
      const types::f77_integer &ldht, const types::f77_integer &seed,
      const double &errtol, double comm[], types::f77_integer icomm[],
      char *errbuf NAG_STDCALL_LEN(errbuf_length),
      types::f77_integer &ifail NAG_NSTDCALL_LEN(errbuf_length));
    }

    class OptionalF01SB : public utility::Optional {
    private:
      types::f77_integer seed_value;
      double errtol_value;

    public:
      OptionalF01SB() : Optional(), seed_value(1), errtol_value(0.0) {}
      OptionalF01SB &seed(types::f77_integer value) {
        seed_value = value;
        return (*this);
      }
      types::f77_integer get_seed(void) { return seed_value; }
      OptionalF01SB &errtol(double value) {
        errtol_value = value;
        return (*this);
      }
      double get_errtol(void) { return errtol_value; }
      template <typename W, typename H, typename HT>
      friend void real_nmf_rcomm(types::f77_integer &irevcm, W &&w, H &&h,
                                 HT &&ht, utility::CopyableComm &comm,
                                 matop::OptionalF01SB &opt);
    };

    template <typename W, typename H, typename HT>
    void real_nmf_rcomm(types::f77_integer &irevcm, W &&w, H &&h, HT &&ht,
                        utility::CopyableComm &comm,
                        matop::OptionalF01SB &opt) {
      opt.fail.prepare("matop::real_nmf_rcomm (f01sb)");
      types::engine_data en_data;
      engine_routines::y90haan_(en_data);
      en_data.allocate_workspace = constants::NAG_ED_YES;
      data_handling::RawData<double, data_handling::ArgIntent::IntentINOUT,
                             typename std::remove_reference<W>::type>
        local_w(w);
      data_handling::RawData<double, data_handling::ArgIntent::IntentINOUT,
                             typename std::remove_reference<H>::type>
        local_h(h);
      data_handling::RawData<double, data_handling::ArgIntent::IntentINOUT,
                             typename std::remove_reference<HT>::type>
        local_ht(ht);

      types::f77_integer local_m =
        data_handling::get_size(opt.fail, "m", local_w, 1);
      if (opt.fail.error_thrown) {
        return;
      }
      types::f77_integer local_n =
        data_handling::get_size(opt.fail, "n", local_h, 2, local_ht, 1);
      if (opt.fail.error_thrown) {
        return;
      }
      types::f77_integer local_k =
        data_handling::get_size(opt.fail, "k", local_h, 1, local_w, 2);
      if (opt.fail.error_thrown) {
        return;
      }
      types::f77_integer local_seed = opt.seed_value;
      double local_errtol = opt.errtol_value;
      types::f77_integer local_comm_dim1 =
        (2 * local_m + local_n) * local_k + 3;
      if (!(comm.initialized)) {
        comm.allocate(opt.fail, local_comm_dim1, 9);
        if (opt.fail.error_thrown) {
          return;
        }
      } else if (!(comm.check(local_comm_dim1, 9))) {
        opt.fail.raise_error_comm_invalid("comm");
        if (opt.fail.error_thrown) {
          return;
        }
      }
      types::f77_integer local_storage_order =
        data_handling::get_storage_order(opt.default_to_col_major, local_w,
                                         local_h, local_ht);
      en_data.storage_order = local_storage_order;

      types::f77_integer local_ldht = local_ht.get_LD(local_storage_order);
      local_ht.check(opt.fail, "ht", true, local_storage_order, local_n,
                     local_k);
      if (opt.fail.error_thrown) {
        return;
      }
      types::f77_integer local_ldh = local_h.get_LD(local_storage_order);
      local_h.check(opt.fail, "h", true, local_storage_order, local_k, local_n);
      if (opt.fail.error_thrown) {
        return;
      }
      types::f77_integer local_ldw = local_w.get_LD(local_storage_order);
      local_w.check(opt.fail, "w", true, local_storage_order, local_m, local_k);
      if (opt.fail.error_thrown) {
        return;
      }

      f01sbft_(en_data, irevcm, local_m, local_n, local_k, local_w.data,
               local_ldw, local_h.data, local_ldh, local_ht.data, local_ldht,
               local_seed, local_errtol, comm.rcomm, comm.icomm,
               opt.fail.errbuf, opt.fail.errorid, opt.fail.errbuf_length);

      if (!(opt.fail.initial_error_handler(en_data))) {
        if (opt.fail.ierr == 1 && opt.fail.ifmt == 99998) {
          opt.fail.set_errorid(1, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(true, "On intermediate re-entry, irevcm = ", 1,
                              ".");
          opt.fail.append_msg(false, "Constraint: irevcm = 1, 2 or 3.");
        } else if (opt.fail.ierr == 1 && opt.fail.ifmt == 99999) {
          opt.fail.set_errorid(1, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(true, "On initial entry, irevcm = ", 1, ".");
          opt.fail.append_msg(false, "Constraint: irevcm = 0.");
        } else if (opt.fail.ierr == 2 && opt.fail.ifmt == 99997) {
          opt.fail.set_errorid(2, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(true, "On entry, m = ", 1, ".");
          opt.fail.append_msg(false, "Constraint: m >= 2.");
        } else if (opt.fail.ierr == 3 && opt.fail.ifmt == 99996) {
          opt.fail.set_errorid(3, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(true, "On entry, n = ", 1, ".");
          opt.fail.append_msg(false, "Constraint: n >= 2.");
        } else if (opt.fail.ierr == 4 && opt.fail.ifmt == 99995) {
          opt.fail.set_errorid(4, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "On entry, k = ", 1, ", m = ", 2, " and");
          opt.fail.append_msg(true, "n = ", 3, ".");
          opt.fail.append_msg(false, "Constraint: 1 <= k < min(m, n).");
        } else if (opt.fail.ierr == 8 && opt.fail.ifmt == 99990) {
          opt.fail.set_errorid(8, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "An internal error occurred when "
                                     "generating initial values for w and h.");
          opt.fail.append_msg(false, "Please contact NAG.");
        } else if (opt.fail.ierr == 9 && opt.fail.ifmt == 99989) {
          opt.fail.set_errorid(9, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "On entry, one of more of the elements of "
                                     "w or h were negative.");
        } else {
          opt.fail.set_unexpected_error();
        }
        opt.fail.throw_error();
      }
      if (opt.fail.error_thrown) {
        return;
      }

      local_w.copy_back(w);
      local_h.copy_back(h);
      local_ht.copy_back(ht);
      comm.initialized = true;
      opt.fail.throw_warning();
    }

    // alt-1
    template <typename W, typename H, typename HT>
    void real_nmf_rcomm(types::f77_integer &irevcm, W &&w, H &&h, HT &&ht,
                        utility::CopyableComm &comm) {
      matop::OptionalF01SB local_opt;

      real_nmf_rcomm(irevcm, w, h, ht, comm, local_opt);
    }
  }
}
#define f01sb matop::real_nmf_rcomm
#endif
