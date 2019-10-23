// Header for nagcpp::sparse::real_gen_matvec (f11xa)

// Copyright 2019, Numerical Algorithms Group Ltd, Oxford, UK.
// Generated by cpp-ft-wrapper.xsl
// Version 27.0.0.1
#ifndef NAGCPP_F11XA_HPP
#define NAGCPP_F11XA_HPP

#include "utility/nagcpp_consts.hpp"
#include "utility/nagcpp_data_handling.hpp"
#include "utility/nagcpp_engine_routines.hpp"
#include "utility/nagcpp_engine_types.hpp"
#include "utility/nagcpp_error_handler.hpp"
#include "utility/nagcpp_utility_optional.hpp"

namespace nagcpp {
  namespace sparse {
    // real_gen_matvec (f11xa)
    // Real, sparse, nonsymmetric matrix-vector multiply.
    // sparse::real_gen_matvec (f11xa) computes a matrix-vector or transposed
    // matrix-vector product involving a real sparse nonsymmetric matrix stored in
    // coordinate storage format.

    // parameters:
    //   trans: std::string, scalar
    //     Specifies whether or not the matrix A is transposed
    //   n: types::f77_integer, scalar
    //     n, the order of the matrix A
    //   nnz: types::f77_integer, scalar
    //     The number of nonzero elements in the matrix A
    //   a: double, array, shape(nnz)
    //     The nonzero elements in the matrix A, ordered by increasing row index, and
    //     by increasing column index within each row
    //   irow: types::f77_integer, array, shape(nnz)
    //     The row indices of the nonzero elements supplied in array a
    //   icol: types::f77_integer, array, shape(nnz)
    //     The column indices of the nonzero elements supplied in array a
    //   x: double, array, shape(n)
    //     The vector x
    //   y: double, array, shape(n)
    //     On exit, if not null on entry: the vector y
    //   opt: sparse::OptionalF11XA
    //     Optional parameter container, derived from utility::Optional.
    //     contains:
    //       check: std::string, scalar
    //         Specifies whether or not the CS representation of the matrix A, values
    //         of n, nnz, irow and icol should be checked
    //         default value: "N"
    //       fail: error_handler::ErrorHandler

    // error_handler::ErrorException
    //   (errorid 1)
    //     On entry, trans = "<value>".
    //     Constraint: trans = "N" or "T".
    //   (errorid 1)
    //     On entry, opt.check = "<value>".
    //     Constraint: opt.check = "C" or "N".
    //   (errorid 2)
    //     On entry, nnz = <value> and n = <value>.
    //     Constraint: nnz <= n^2.
    //   (errorid 2)
    //     On entry, nnz = <value>.
    //     Constraint: nnz >= 1.
    //   (errorid 2)
    //     On entry, n = <value>.
    //     Constraint: n >= 1.
    //   (errorid 3)
    //     On entry, the location (irow[I-1],icol[I-1]) is a duplicate:
    //     I = <value>.
    //   (errorid 3)
    //     On entry, a[i-1] is out of order:
    //     i = <value>.
    //   (errorid 3)
    //     On entry, i = <value>, icol[i-1] = <value>
    //     and n = <value>.
    //     Constraint: icol[i-1] >= 1 and icol[i-1] <= n.
    //   (errorid 3)
    //     On entry, i = <value>, irow[i-1] = <value>
    //     and n = <value>.
    //     Constraint: irow[i-1] >= 1 and irow[i-1] <= n.
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
    //   (errorid -99)
    //     An unexpected error has been triggered by this routine.
    //   (errorid -399)
    //     Your licence key may have expired or may not have been installed correctly.
    //   (errorid -999)
    //     Dynamic memory allocation failed.

    extern "C" {
#if defined(_WIN32) && defined(USE_STDCALL)
#define f11xaft_(en_data, trans, n, nnz, a, irow, icol, check, x, y, errbuf, \
                 ifail, trans_length, check_length, errbuf_length)           \
  F11XAFT(en_data, trans, trans_length, n, nnz, a, irow, icol, check,        \
          check_length, x, y, errbuf, errbuf_length, ifail)
#elif defined(_WIN32) || defined(_WIN64)
#define f11xaft_ F11XAFT
#else
#define F11XAFT f11xaft_
#endif
    extern void NAG_CALL
      F11XAFT(types::engine_data &en_data,
              const char *trans NAG_STDCALL_LEN(trans_length),
              const types::f77_integer &n, const types::f77_integer &nnz,
              const double a[], const types::f77_integer irow[],
              const types::f77_integer icol[],
              const char *check NAG_STDCALL_LEN(check_length), const double x[],
              double y[], char *errbuf NAG_STDCALL_LEN(errbuf_length),
              types::f77_integer &ifail NAG_NSTDCALL_LEN(trans_length)
                NAG_NSTDCALL_LEN(check_length) NAG_NSTDCALL_LEN(errbuf_length));
    }

    class OptionalF11XA : public utility::Optional {
    private:
      std::string check_value;

    public:
      OptionalF11XA() : Optional(), check_value("N") {}
      OptionalF11XA &check(std::string value) {
        check_value = value;
        return (*this);
      }
      std::string get_check(void) { return check_value; }
      template <typename A, typename IROW, typename ICOL, typename X,
                typename Y>
      friend void real_gen_matvec(const std::string trans, const A &a,
                                  const IROW &irow, const ICOL &icol,
                                  const X &x, Y &&y,
                                  sparse::OptionalF11XA &opt);
    };

    template <typename A, typename IROW, typename ICOL, typename X, typename Y>
    void real_gen_matvec(const std::string trans, const A &a, const IROW &irow,
                         const ICOL &icol, const X &x, Y &&y,
                         sparse::OptionalF11XA &opt) {
      opt.fail.prepare("sparse::real_gen_matvec (f11xa)");
      types::engine_data en_data;
      engine_routines::y90haan_(en_data);
      en_data.allocate_workspace = constants::NAG_ED_YES;
      data_handling::RawData<double, data_handling::ArgIntent::IN,
                             typename std::remove_reference<A>::type>
        local_a(a);
      data_handling::RawData<types::f77_integer, data_handling::ArgIntent::IN,
                             typename std::remove_reference<IROW>::type>
        local_irow(irow);
      data_handling::RawData<types::f77_integer, data_handling::ArgIntent::IN,
                             typename std::remove_reference<ICOL>::type>
        local_icol(icol);
      data_handling::RawData<double, data_handling::ArgIntent::IN,
                             typename std::remove_reference<X>::type>
        local_x(x);

      data_handling::StringRawData<data_handling::ArgIntent::IN> local_trans(
        trans);
      types::f77_integer local_n =
        data_handling::get_size(opt.fail, "n", local_x, 1);
      if (opt.fail.error_thrown) {
        return;
      }
      types::f77_integer local_nnz =
        data_handling::get_size(opt.fail, "nnz", local_a, 1, local_irow, 1,
                                local_icol, 1);
      if (opt.fail.error_thrown) {
        return;
      }
      data_handling::StringRawData<data_handling::ArgIntent::IN> local_check(
        opt.check_value);
      data_handling::RawData<double, data_handling::ArgIntent::OUT,
                             typename std::remove_reference<Y>::type>
        local_y(y);
      local_y.resize(y, local_n);

      local_y.check(opt.fail, "y", true, local_n);
      if (opt.fail.error_thrown) {
        return;
      }
      local_x.check(opt.fail, "x", true, local_n);
      if (opt.fail.error_thrown) {
        return;
      }
      local_icol.check(opt.fail, "icol", true, local_nnz);
      if (opt.fail.error_thrown) {
        return;
      }
      local_irow.check(opt.fail, "irow", true, local_nnz);
      if (opt.fail.error_thrown) {
        return;
      }
      local_a.check(opt.fail, "a", true, local_nnz);
      if (opt.fail.error_thrown) {
        return;
      }

      f11xaft_(en_data, local_trans.data, local_n, local_nnz, local_a.data,
               local_irow.data, local_icol.data, local_check.data, local_x.data,
               local_y.data, opt.fail.errbuf, opt.fail.errorid,
               local_trans.string_length, local_check.string_length,
               opt.fail.errbuf_length);

      if (!(opt.fail.initial_error_handler(en_data))) {
        if (opt.fail.ierr == 1 && opt.fail.ifmt == 99991) {
          opt.fail.set_errorid(1, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(true, "On entry, trans = \"", 1, "\".");
          opt.fail.append_msg(false, "Constraint: trans = \"N\" or \"T\".");
        } else if (opt.fail.ierr == 1 && opt.fail.ifmt == 99999) {
          opt.fail.set_errorid(1, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(true, "On entry, opt.check = \"", 1, "\".");
          opt.fail.append_msg(false, "Constraint: opt.check = \"C\" or \"N\".");
        } else if (opt.fail.ierr == 2 && opt.fail.ifmt == 99996) {
          opt.fail.set_errorid(2, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(true, "On entry, nnz = ", 1, " and n = ", 2, ".");
          opt.fail.append_msg(false, "Constraint: nnz <= n^2.");
        } else if (opt.fail.ierr == 2 && opt.fail.ifmt == 99997) {
          opt.fail.set_errorid(2, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(true, "On entry, nnz = ", 1, ".");
          opt.fail.append_msg(false, "Constraint: nnz >= 1.");
        } else if (opt.fail.ierr == 2 && opt.fail.ifmt == 99998) {
          opt.fail.set_errorid(2, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(true, "On entry, n = ", 1, ".");
          opt.fail.append_msg(false, "Constraint: n >= 1.");
        } else if (opt.fail.ierr == 3 && opt.fail.ifmt == 99992) {
          opt.fail.set_errorid(3, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "On entry, the location "
                                     "(irow[I-1],icol[I-1]) is a duplicate:");
          opt.fail.append_msg(false, "I = ", 1, ".");
        } else if (opt.fail.ierr == 3 && opt.fail.ifmt == 99993) {
          opt.fail.set_errorid(3, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "On entry, a[i-1] is out of order:");
          opt.fail.append_msg(false, "i = ", 1, ".");
        } else if (opt.fail.ierr == 3 && opt.fail.ifmt == 99994) {
          opt.fail.set_errorid(3, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "On entry, i = ", 1, ", icol[i-1] = ", 2);
          opt.fail.append_msg(true, "and n = ", 3, ".");
          opt.fail.append_msg(false, "Constraint: icol[i-1] >= 1 and icol[i-1] "
                                     "<= n.");
        } else if (opt.fail.ierr == 3 && opt.fail.ifmt == 99995) {
          opt.fail.set_errorid(3, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(false, "On entry, i = ", 1, ", irow[i-1] = ", 2);
          opt.fail.append_msg(true, "and n = ", 3, ".");
          opt.fail.append_msg(false, "Constraint: irow[i-1] >= 1 and irow[i-1] "
                                     "<= n.");
        } else {
          opt.fail.set_unexpected_error();
        }
        opt.fail.throw_error();
      }
      if (opt.fail.error_thrown) {
        return;
      }

      local_y.copy_back(y);
      opt.fail.throw_warning();
    }

    // alt-1
    template <typename A, typename IROW, typename ICOL, typename X, typename Y>
    void real_gen_matvec(const std::string trans, const A &a, const IROW &irow,
                         const ICOL &icol, const X &x, Y &&y) {
      sparse::OptionalF11XA local_opt;

      real_gen_matvec(trans, a, irow, icol, x, y, local_opt);
    }
  }
}
#define f11xa sparse::real_gen_matvec
#endif
