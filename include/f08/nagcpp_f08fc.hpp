// Header for nagcpp::lapackeig::dsyevd (f08fc)

// Copyright 2023, Numerical Algorithms Group Ltd, Oxford, UK.
// Generated by cpp-ft-wrapper.xsl
// Version 29.1.0.0
#ifndef NAGCPP_F08FC_HPP
#define NAGCPP_F08FC_HPP

#include "utility/nagcpp_consts.hpp"
#include "utility/nagcpp_data_handling.hpp"
#include "utility/nagcpp_engine_routines.hpp"
#include "utility/nagcpp_engine_types.hpp"
#include "utility/nagcpp_error_handler.hpp"
#include "utility/nagcpp_utility_functions.hpp"
#include "utility/nagcpp_utility_optional.hpp"
#include <algorithm>

namespace nagcpp {
  namespace lapackeig {
    // dsyevd (f08fc)
    // Computes all eigenvalues and, optionally, all eigenvectors of real symmetric
    // matrix (divide-and-conquer).
    // lapackeig::dsyevd (f08fc) computes all the eigenvalues and, optionally, all
    // the eigenvectors of a real symmetric matrix. If the eigenvectors are
    // requested, then it uses a divide-and-conquer algorithm to compute
    // eigenvalues and eigenvectors.
    // However, if only eigenvalues are required, then it uses the
    // Pal--Walker--Kahan variant of the QL or QR algorithm.

    // parameters:
    //   job: std::string, scalar
    //     Indicates whether eigenvectors are computed
    //   uplo: std::string, scalar
    //     Indicates whether the upper or lower triangular part of A is stored
    //   n: types::f77_integer, scalar
    //     n, the order of the matrix A
    //   a: double, array, shape(n, n)
    //     On entry: the n*n symmetric matrix A
    //     On exit: if job = "V", a is overwritten by the orthogonal matrix Z which
    //     contains the eigenvectors of A
    //   w: double, array, shape(n)
    //     On exit, if not null on entry: the eigenvalues of the matrix A in
    //     ascending order
    //   opt: lapackeig::OptionalF08FC
    //     Optional parameter container, derived from utility::Optional.
    //     contains:
    //       fail: error_handler::ErrorHandler

    // error_handler::ErrorException
    //   (errorid i > 0)
    //     If info = <value> and job = "N", the algorithm failed to
    //     converge; <value> elements of an intermediate tridiagonal
    //     form did not converge to zero; if info = <value> and
    //     job = "V", then the algorithm failed to compute an eigenvalue while working
    //     on the submatrix lying in rows and column <value>/(n+1)
    //     through mod(<value>, n+1).
    //   (errorid 10601)
    //     On entry, argument <value> must be a vector of size <value> array.
    //     Supplied argument has <value> dimensions.
    //   (errorid 10601)
    //     On entry, argument <value> must be a vector of size <value> array.
    //     Supplied argument was a vector of size <value>.
    //   (errorid 10601)
    //     On entry, argument <value> must be a vector of size <value> array.
    //     The size for the supplied array could not be ascertained.
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
    //   (errorid -99)
    //     An unexpected error has been triggered by this routine.
    //   (errorid -999)
    //     Dynamic memory allocation failed.
    //   (errorid -1)
    //     On entry, error in parameter job.
    //     Constraint: job = "N" or "V".
    //   (errorid -2)
    //     On entry, error in parameter uplo.
    //     Constraint: uplo = "U" or "L".
    //   (errorid -3)
    //     On entry, error in parameter n.
    //     Constraint: n >= 0.

    extern "C" {
#if defined(_WIN32) && defined(USE_STDCALL)
#define f08fcft_(call_vendor, en_data, job, uplo, n, a, lda, w, work, lwork,   \
                 iwork, liwork, info, job_length, uplo_length)                 \
  F08FCFT(call_vendor, en_data, job, job_length, uplo, uplo_length, n, a, lda, \
          w, work, lwork, iwork, liwork, info)
#elif defined(_WIN32) || defined(_WIN64)
#define f08fcft_ F08FCFT
#else
#define F08FCFT f08fcft_
#endif
    extern void NAG_CALL F08FCFT(
      const types::f77_logical &call_vendor, types::engine_data &en_data,
      const char *job NAG_STDCALL_LEN(job_length),
      const char *uplo NAG_STDCALL_LEN(uplo_length),
      const types::f77_integer &n, double a[], const types::f77_integer &lda,
      double w[], double work[], const types::f77_integer &lwork,
      types::f77_integer iwork[], const types::f77_integer &liwork,
      types::f77_integer &info NAG_NSTDCALL_LEN(job_length)
        NAG_NSTDCALL_LEN(uplo_length));
    }

    class OptionalF08FC : public utility::Optional {
    public:
      OptionalF08FC() : Optional() {}
      template <typename A, typename W>
      friend void dsyevd(const std::string job, const std::string uplo, A &&a,
                         W &&w, lapackeig::OptionalF08FC &opt);
    };

    template <typename A, typename W>
    void dsyevd(const std::string job, const std::string uplo, A &&a, W &&w,
                lapackeig::OptionalF08FC &opt) {
      opt.fail.prepare("lapackeig::dsyevd (f08fc)", false);
      types::engine_data en_data;
      engine_routines::y90haan_(en_data);
      en_data.allocate_workspace = constants::NAG_ED_YES;
      data_handling::RawData<double, data_handling::ArgIntent::IntentINOUT,
                             typename std::remove_reference<A>::type>
        local_a(a);

      types::f77_logical local_call_vendor = 1;
      data_handling::StringRawData<data_handling::ArgIntent::IntentIN>
        local_job(job);
      data_handling::StringRawData<data_handling::ArgIntent::IntentIN>
        local_uplo(uplo);
      types::f77_integer local_n =
        data_handling::get_size(opt.fail, "n", local_a, 2);
      if (opt.fail.error_thrown) {
        return;
      }
      data_handling::RawData<double, data_handling::ArgIntent::IntentOUT,
                             typename std::remove_reference<W>::type>
        local_w(w);
      local_w.resize(w, local_n);
      data_handling::RawData<double, data_handling::ArgIntent::IntentOUT>
        local_work(static_cast<types::f77_integer>(0));
      types::f77_integer local_lwork = 0;
      data_handling::RawData<types::f77_integer,
                             data_handling::ArgIntent::IntentOUT>
        local_iwork(static_cast<types::f77_integer>(0));
      types::f77_integer local_liwork = 0;
      types::f77_integer local_storage_order =
        data_handling::get_storage_order(opt.default_to_col_major, local_a);
      en_data.storage_order = local_storage_order;

      local_w.check(opt.fail, "w", true, local_n);
      if (opt.fail.error_thrown) {
        return;
      }
      types::f77_integer local_lda =
        std::max(static_cast<types::f77_integer>(1),
                 local_a.get_LD(local_storage_order));
      local_a.check(opt.fail, "a", true, local_storage_order, local_n, local_n);
      if (opt.fail.error_thrown) {
        return;
      }

      if (!((utility::streq(job, "N", 1) || utility::streq(job, "V", 1)))) {
        opt.fail.set_errorid(-1, error_handler::ErrorCategory::Error,
                             error_handler::ErrorType::GeneralError);
        opt.fail.append_msg(true, "On entry, error in parameter job.");
        opt.fail.append_msg(false, "Constraint: job = \"N\" or \"V\".");
        opt.fail.throw_error();
      }
      if (!((utility::streq(uplo, "U", 1) || utility::streq(uplo, "L", 1)))) {
        opt.fail.set_errorid(-2, error_handler::ErrorCategory::Error,
                             error_handler::ErrorType::GeneralError);
        opt.fail.append_msg(true, "On entry, error in parameter uplo.");
        opt.fail.append_msg(false, "Constraint: uplo = \"U\" or \"L\".");
        opt.fail.throw_error();
      }
      if (!(local_n >= 0)) {
        opt.fail.set_errorid(-3, error_handler::ErrorCategory::Error,
                             error_handler::ErrorType::GeneralError);
        opt.fail.append_msg(true, "On entry, error in parameter n.");
        opt.fail.append_msg(false, "Constraint: n >= 0.");
        opt.fail.throw_error();
      }

      f08fcft_(local_call_vendor, en_data, local_job.data, local_uplo.data,
               local_n, local_a.data, local_lda, local_w.data, local_work.data,
               local_lwork, local_iwork.data, local_liwork, opt.fail.errorid,
               local_job.string_length, local_uplo.string_length);

      if (!(opt.fail.initial_error_handler(en_data))) {
        if (opt.fail.ierr > 0) {
          opt.fail.set_errorid(opt.fail.ierr,
                               error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "If info = ",
                              " and job = \"N\", the algorithm failed to");
          opt.fail.append_msg(false, "converge; ",
                              " elements of an intermediate tridiagonal");
          opt.fail.append_msg(
            false, "form did not converge to zero; if info = ", " and");
          opt.fail.append_msg(false, "job = \"V\", then the algorithm failed "
                                     "to compute an eigenvalue while working");
          opt.fail.append_msg(false,
                              "on the submatrix lying in rows and column ",
                              "/(n+1)");
          opt.fail.append_msg(false, "through mod(", ", n+1).");
        } else {
          opt.fail.set_unexpected_error();
        }
        opt.fail.throw_error();
      }
      if (opt.fail.error_thrown) {
        return;
      }

      local_a.copy_back(a);
      local_w.copy_back(w);
      opt.fail.throw_warning();
    }

    // alt-1
    template <typename A, typename W>
    void dsyevd(const std::string job, const std::string uplo, A &&a, W &&w) {
      lapackeig::OptionalF08FC local_opt;

      dsyevd(job, uplo, a, w, local_opt);
    }
  }
}
#define f08fc lapackeig::dsyevd
#endif
