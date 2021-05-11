// Header for nagcpp::correg::lars (g02ma)

// Copyright 2021, Numerical Algorithms Group Ltd, Oxford, UK.
// Generated by cpp-ft-wrapper.xsl
// Version 27.3.0.0
#ifndef NAGCPP_G02MA_HPP
#define NAGCPP_G02MA_HPP

#include "utility/nagcpp_consts.hpp"
#include "utility/nagcpp_data_handling.hpp"
#include "utility/nagcpp_engine_routines.hpp"
#include "utility/nagcpp_engine_types.hpp"
#include "utility/nagcpp_error_handler.hpp"
#include "utility/nagcpp_utility_optional.hpp"
#include "utility/nagcpp_utility_print_rec.hpp"
#include <vector>

namespace nagcpp {
  namespace correg {
    // lars (g02ma)
    // Least angle regression (LARS), least absolute shrinkage and selection
    // operator (LASSO) and forward stagewise regression.
    // correg::lars (g02ma) performs Least Angle Regression (LARS), forward
    // stagewise linear regression or Least Absolute Shrinkage and Selection
    // Operator (LASSO).

    // parameters:
    //   mtype: types::f77_integer, scalar
    //     Indicates the type of model to fit
    //   y: double, array, shape(n)
    //     y, the observations on the dependent variable
    //   ip: types::f77_integer, scalar
    //     On exit: p, number of parameter estimates
    //   nstep: types::f77_integer, scalar
    //     On exit: K, the actual number of steps carried out in the model fitting
    //     process
    //   b: double, array, shape(p, mnstep+2)
    //     On exit, if not null on entry: beta the parameter estimates, with
    //     b[j-1,k-1] = beta_{kj}, the parameter estimate for the jth variable, j =
    //     1,2,...,p at the kth step of the model fitting process, k = 1,2,...,nstep
    //   ldb: types::f77_integer, scalar
    //     The first dimension of the array b.
    //   fitsum: double, array, shape(6, mnstep+1)
    //     On exit, if not null on entry: summaries of the model fitting process
    //   n: types::f77_integer, scalar
    //     n, the number of observations
    //   m: types::f77_integer, scalar
    //     m, the total number of independent variables
    //   d: double, array, shape(n, m)
    //     D, the data, which along with pred and isx, defines the design matrix X
    //   ldd: types::f77_integer, scalar
    //     The first dimension of the array d.
    //   isx: types::f77_integer, array, shape(lisx)
    //     Indicates which independent variables from d will be included in the
    //     design matrix, X
    //   opt: correg::OptionalG02MA
    //     Optional parameter container, derived from utility::Optional.
    //     contains:
    //       pred: types::f77_integer, scalar
    //         Indicates the type of data preprocessing to perform on the independent
    //         variables supplied in d to comply with the standardized form of the
    //         design matrix
    //         default value: 3
    //       prey: types::f77_integer, scalar
    //         Indicates the type of data preprocessing to perform on the dependent
    //         variable supplied in y
    //         default value: 1
    //       mnstep: types::f77_integer, scalar
    //         The maximum number of steps to carry out in the model fitting process
    //         default value: if mtype = 1: m; otherwise: 200*m
    //       ropt: std::vector<double>, shape(lropt)
    //         Options to control various aspects of the LARS algorithm
    //       fail: error_handler::ErrorHandler

    // error_handler::ErrorException
    //   (errorid 11)
    //     On entry, mtype = <value>.
    //     Constraint: mtype = 1, 2, 3 or 4.
    //   (errorid 21)
    //     On entry, opt.pred = <value>.
    //     Constraint: opt.pred = 0, 1, 2 or 3.
    //   (errorid 31)
    //     On entry, opt.prey = <value>.
    //     Constraint: opt.prey = 0 or 1.
    //   (errorid 41)
    //     On entry, n = <value>.
    //     Constraint: n >= 1.
    //   (errorid 51)
    //     On entry, m = <value>.
    //     Constraint: m >= 1.
    //   (errorid 81)
    //     On entry, isx[<value>] = <value>.
    //     Constraint: isx[i] = 0 or 1, for all i.
    //   (errorid 82)
    //     On entry, all values of isx are zero.
    //     Constraint: at least one value of isx must be nonzero.
    //   (errorid 91)
    //     On entry, lisx = <value> and m = <value>.
    //     Constraint: lisx = 0 or m.
    //   (errorid 111)
    //     On entry, opt.mnstep = <value>.
    //     Constraint: opt.mnstep >= 1.
    //   (errorid 151)
    //     On entry, ldb = <value> and m = <value>.
    //     Constraint: if lisx = 0 then ldb >= m.
    //   (errorid 152)
    //     On entry, ldb = <value> and p = <value>.
    //     Constraint: if lisx = m then ldb >= p.
    //   (errorid 181)
    //     On entry, lropt = <value>.
    //     Constraint: 0 <= lropt <= 5.
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
    //   (errorid 10703)
    //     An exception was thrown during IO (writing).
    //   (errorid -99)
    //     An unexpected error has been triggered by this routine.
    //   (errorid -399)
    //     Your licence key may have expired or may not have been installed correctly.
    //   (errorid -999)
    //     Dynamic memory allocation failed.

    // error_handler::WarningException
    //   (errorid 112)
    //     Fitting process did not finish in opt.mnstep steps.
    //     Try increasing the size of opt.mnstep and supplying larger output arrays.
    //     All output is returned as documented, up to step opt.mnstep, however,
    //     sigma and the C_p statistics may not be meaningful.
    //   (errorid 161)
    //     sigma^2 is approximately zero and hence the C_p-type criterion
    //     cannot be calculated. All other output is returned as documented.
    //   (errorid 162)
    //     nu_K = n, therefore, sigma has been set to a large value.
    //     Output is returned as documented.
    //   (errorid 163)
    //     Degenerate model, no variables added and nstep = 0.
    //     Output is returned as documented.

    extern "C" {
#if defined(_WIN32) && defined(USE_STDCALL)
#define g02maft_(en_data, print_rec, print_rech, sorder, mtype, pred, prey, n, \
                 m, d, ldd, isx, lisx, y, mnstep, ip, nstep, b, ldb, fitsum,   \
                 ropt, lropt, monit, errbuf, ifail, errbuf_length)             \
  G02MAFT(en_data, print_rec, print_rech, sorder, mtype, pred, prey, n, m, d,  \
          ldd, isx, lisx, y, mnstep, ip, nstep, b, ldb, fitsum, ropt, lropt,   \
          monit, errbuf, errbuf_length, ifail)
#elif defined(_WIN32) || defined(_WIN64)
#define g02maft_ G02MAFT
#else
#define G02MAFT g02maft_
#endif
    extern void NAG_CALL G02MAFT(
      types::engine_data &en_data, void *print_rec, NAG_PRINT_RECH,
      const types::f77_integer &sorder, const types::f77_integer &mtype,
      const types::f77_integer &pred, const types::f77_integer &prey,
      const types::f77_integer &n, const types::f77_integer &m,
      const double d[], const types::f77_integer &ldd,
      const types::f77_integer isx[], const types::f77_integer &lisx,
      const double y[], const types::f77_integer &mnstep,
      types::f77_integer &ip, types::f77_integer &nstep, double b[],
      const types::f77_integer &ldb, double fitsum[], const double ropt[],
      const types::f77_integer &lropt, const types::f77_integer &monit,
      char *errbuf NAG_STDCALL_LEN(errbuf_length),
      types::f77_integer &ifail NAG_NSTDCALL_LEN(errbuf_length));
    }

    class OptionalG02MA : public utility::Optional {
    private:
      types::f77_integer pred_value;
      types::f77_integer prey_value;
      types::f77_integer mnstep_value;
      utility::IsSet mnstep_set;
      std::vector<double> ropt_value;

    public:
      OptionalG02MA()
        : Optional(), pred_value(3), prey_value(1),
          mnstep_set(utility::IsSet::No) {}
      OptionalG02MA &pred(types::f77_integer value) {
        pred_value = value;
        return (*this);
      }
      types::f77_integer get_pred(void) { return pred_value; }
      OptionalG02MA &prey(types::f77_integer value) {
        prey_value = value;
        return (*this);
      }
      types::f77_integer get_prey(void) { return prey_value; }
      OptionalG02MA &mnstep(types::f77_integer value) {
        mnstep_set = utility::IsSet::Yes;
        mnstep_value = value;
        return (*this);
      }
      types::f77_integer get_mnstep(void) {
        if (mnstep_set == utility::IsSet::No) {
          fail.raise_error_value_not_available("mnstep");
          return std::numeric_limits<types::f77_integer>::quiet_NaN();
        }
        return mnstep_value;
      }
      OptionalG02MA &ropt(std::vector<double> &value) {
        ropt_value = value;
        return (*this);
      }
      std::vector<double> get_ropt(void) { return ropt_value; }
      template <typename D, typename ISX, typename Y, typename B,
                typename FITSUM>
      friend void lars(const types::f77_integer mtype, const D &d,
                       const ISX &isx, const Y &y, types::f77_integer &ip,
                       types::f77_integer &nstep, B &&b, FITSUM &&fitsum,
                       correg::OptionalG02MA &opt);
    };

    template <typename D, typename ISX, typename Y, typename B, typename FITSUM>
    void lars(const types::f77_integer mtype, const D &d, const ISX &isx,
              const Y &y, types::f77_integer &ip, types::f77_integer &nstep,
              B &&b, FITSUM &&fitsum, correg::OptionalG02MA &opt) {
      opt.fail.prepare("correg::lars (g02ma)");
      types::engine_data en_data;
      engine_routines::y90haan_(en_data);
      en_data.allocate_workspace = constants::NAG_ED_YES;
      data_handling::RawData<double, data_handling::ArgIntent::IN,
                             typename std::remove_reference<D>::type>
        local_d(d);
      data_handling::RawData<types::f77_integer, data_handling::ArgIntent::IN,
                             typename std::remove_reference<ISX>::type>
        local_isx(isx);
      data_handling::RawData<double, data_handling::ArgIntent::IN,
                             typename std::remove_reference<Y>::type>
        local_y(y);
      data_handling::RawData<double, data_handling::ArgIntent::IN,
                             std::vector<double>>
        local_ropt(opt.ropt_value);

      void *local_print_rec = static_cast<void *>(&opt.iomanager);
      types::f77_integer local_sorder = 1;
      types::f77_integer local_pred = opt.pred_value;
      types::f77_integer local_prey = opt.prey_value;
      types::f77_integer local_n =
        data_handling::get_size(opt.fail, "n", local_y, 1, local_d, 1);
      if (opt.fail.error_thrown) {
        return;
      }
      types::f77_integer local_m =
        data_handling::get_size(opt.fail, "m", local_d, 2);
      if (opt.fail.error_thrown) {
        return;
      }
      types::f77_integer local_lisx;
      if (static_cast<bool>(local_isx.data)) {
        local_lisx = local_m;
      } else {
        local_lisx = 0;
      }
      if (!(opt.mnstep_set == utility::IsSet::Yes)) {
        if (mtype == 1) {
          opt.mnstep_value = local_m;
        } else {
          opt.mnstep_value = 200 * local_m;
        }
        opt.mnstep_set = utility::IsSet::Default;
      }
      types::f77_integer local_mnstep = opt.mnstep_value;
      types::f77_integer vl_p;
      if (!(static_cast<bool>(local_isx.data))) {
        vl_p = local_m;
      } else {
        vl_p = 0;
        for (types::f77_integer vl_j = 1; vl_j <= local_m; vl_j++) {
          if (local_isx(vl_j - 1) == 1) {
            vl_p++;
          }
        }
      }
      data_handling::RawData<double, data_handling::ArgIntent::OUT,
                             typename std::remove_reference<B>::type>
        local_b(b);
      local_b.resize(b, vl_p, local_mnstep + 2);
      data_handling::RawData<double, data_handling::ArgIntent::OUT,
                             typename std::remove_reference<FITSUM>::type>
        local_fitsum(fitsum);
      local_fitsum.resize(fitsum, static_cast<types::f77_integer>(6),
                          local_mnstep + 1);
      types::f77_integer local_lropt =
        data_handling::get_size(opt.fail, "lropt", local_ropt, 1);
      if (opt.fail.error_thrown) {
        return;
      }
      types::f77_integer local_monit = 0;
      types::f77_integer local_storage_order =
        data_handling::get_storage_order(opt.default_to_col_major, local_d,
                                         local_b, local_fitsum);
      en_data.storage_order = local_storage_order;

      local_ropt.check(opt.fail, "opt.ropt", false, local_lropt);
      if (opt.fail.error_thrown) {
        return;
      }
      local_fitsum.check(opt.fail, "fitsum", true, local_storage_order,
                         static_cast<types::f77_integer>(6), local_mnstep + 1);
      if (opt.fail.error_thrown) {
        return;
      }
      types::f77_integer local_ldb = local_b.get_LD(local_storage_order);
      local_b.check(opt.fail, "b", true, local_storage_order, vl_p,
                    local_mnstep + 2);
      if (opt.fail.error_thrown) {
        return;
      }
      local_y.check(opt.fail, "y", true, local_n);
      if (opt.fail.error_thrown) {
        return;
      }
      local_isx.check(opt.fail, "isx", false, local_lisx);
      if (opt.fail.error_thrown) {
        return;
      }
      types::f77_integer local_ldd = local_d.get_LD(local_storage_order);
      local_d.check(opt.fail, "d", true, local_storage_order, local_n, local_m);
      if (opt.fail.error_thrown) {
        return;
      }

      g02maft_(en_data, local_print_rec, utility::print_rech, local_sorder,
               mtype, local_pred, local_prey, local_n, local_m, local_d.data,
               local_ldd, local_isx.data, local_lisx, local_y.data,
               local_mnstep, ip, nstep, local_b.data, local_ldb,
               local_fitsum.data, local_ropt.data, local_lropt, local_monit,
               opt.fail.errbuf, opt.fail.errorid, opt.fail.errbuf_length);

      if (!(opt.fail.initial_error_handler(en_data))) {
        if (opt.fail.ierr == 11 && opt.fail.ifmt == 11) {
          opt.fail.set_errorid(11, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(true, "On entry, mtype = ", 1, ".");
          opt.fail.append_msg(false, "Constraint: mtype = 1, 2, 3 or 4.");
        } else if (opt.fail.ierr == 21 && opt.fail.ifmt == 21) {
          opt.fail.set_errorid(21, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(true, "On entry, opt.pred = ", 1, ".");
          opt.fail.append_msg(false, "Constraint: opt.pred = 0, 1, 2 or 3.");
        } else if (opt.fail.ierr == 31 && opt.fail.ifmt == 31) {
          opt.fail.set_errorid(31, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(true, "On entry, opt.prey = ", 1, ".");
          opt.fail.append_msg(false, "Constraint: opt.prey = 0 or 1.");
        } else if (opt.fail.ierr == 41 && opt.fail.ifmt == 41) {
          opt.fail.set_errorid(41, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(true, "On entry, n = ", 1, ".");
          opt.fail.append_msg(false, "Constraint: n >= 1.");
        } else if (opt.fail.ierr == 51 && opt.fail.ifmt == 51) {
          opt.fail.set_errorid(51, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(true, "On entry, m = ", 1, ".");
          opt.fail.append_msg(false, "Constraint: m >= 1.");
        } else if (opt.fail.ierr == 81 && opt.fail.ifmt == 81) {
          opt.fail.set_errorid(81, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(true, "On entry, isx[", 1, "] = ", 2, ".");
          opt.fail.append_msg(false, "Constraint: isx[i] = 0 or 1, for all i.");
        } else if (opt.fail.ierr == 82 && opt.fail.ifmt == 82) {
          opt.fail.set_errorid(82, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(true, "On entry, all values of isx are zero.");
          opt.fail.append_msg(false, "Constraint: at least one value of isx "
                                     "must be nonzero.");
        } else if (opt.fail.ierr == 91 && opt.fail.ifmt == 91) {
          opt.fail.set_errorid(91, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(true, "On entry, lisx = ", 1, " and m = ", 2,
                              ".");
          opt.fail.append_msg(false, "Constraint: lisx = 0 or m.");
        } else if (opt.fail.ierr == 111 && opt.fail.ifmt == 111) {
          opt.fail.set_errorid(111, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(true, "On entry, opt.mnstep = ", 1, ".");
          opt.fail.append_msg(false, "Constraint: opt.mnstep >= 1.");
        } else if (opt.fail.ierr == 112 && opt.fail.ifmt == 112) {
          opt.fail.set_errorid(112, error_handler::ErrorCategory::Warning,
                               error_handler::ErrorType::GeneralWarning);
          opt.fail.append_msg(false, "Fitting process did not finish in "
                                     "opt.mnstep steps.");
          opt.fail.append_msg(true, "Try increasing the size of opt.mnstep and "
                                    "supplying larger output arrays.");
          opt.fail.append_msg(false, "All output is returned as documented, up "
                                     "to step opt.mnstep, however,");
          opt.fail.append_msg(false, "sigma and the C_p statistics may not be "
                                     "meaningful.");
        } else if (opt.fail.ierr == 151 && opt.fail.ifmt == 151) {
          opt.fail.set_errorid(151, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(true, "On entry, ldb = ", 1, " and m = ", 2, ".");
          opt.fail.append_msg(false, "Constraint: if lisx = 0 then ldb >= m.");
        } else if (opt.fail.ierr == 152 && opt.fail.ifmt == 152) {
          opt.fail.set_errorid(152, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(true, "On entry, ldb = ", 1, " and p = ", 2, ".");
          opt.fail.append_msg(false, "Constraint: if lisx = m then ldb >= p.");
        } else if (opt.fail.ierr == 161 && opt.fail.ifmt == 161) {
          opt.fail.set_errorid(161, error_handler::ErrorCategory::Warning,
                               error_handler::ErrorType::GeneralWarning);
          opt.fail.append_msg(false, "sigma^2 is approximately zero and hence "
                                     "the C_p-type criterion");
          opt.fail.append_msg(false, "cannot be calculated. All other output "
                                     "is returned as documented.");
        } else if (opt.fail.ierr == 162 && opt.fail.ifmt == 162) {
          opt.fail.set_errorid(162, error_handler::ErrorCategory::Warning,
                               error_handler::ErrorType::GeneralWarning);
          opt.fail.append_msg(false, "nu_K = n, therefore, sigma has been set "
                                     "to a large value.");
          opt.fail.append_msg(false, "Output is returned as documented.");
        } else if (opt.fail.ierr == 163 && opt.fail.ifmt == 163) {
          opt.fail.set_errorid(163, error_handler::ErrorCategory::Warning,
                               error_handler::ErrorType::GeneralWarning);
          opt.fail.append_msg(false, "Degenerate model, no variables added and "
                                     "nstep = 0.");
          opt.fail.append_msg(false, "Output is returned as documented.");
        } else if (opt.fail.ierr == 164 && opt.fail.ifmt == 164) {
          opt.fail.set_errorid(163, error_handler::ErrorCategory::Warning,
                               error_handler::ErrorType::GeneralWarning);
          opt.fail.append_msg(false, "Degenerate model, no variables added and "
                                     "nstep = 0.");
          opt.fail.append_msg(false, "Output is returned as documented.");
        } else if (opt.fail.ierr == 181 && opt.fail.ifmt == 181) {
          opt.fail.set_errorid(181, error_handler::ErrorCategory::Error,
                               error_handler::ErrorType::GeneralError);
          opt.fail.append_msg(true, "On entry, lropt = ", 1, ".");
          opt.fail.append_msg(false, "Constraint: 0 <= lropt <= 5.");
        } else {
          opt.fail.set_unexpected_error();
        }
        opt.fail.throw_error();
      }
      if (opt.fail.error_thrown) {
        return;
      }

      local_b.copy_back(b, ip, nstep + 2);
      local_fitsum.copy_back(fitsum, static_cast<types::f77_integer>(6),
                             nstep + 1);
      opt.fail.throw_warning();
    }

    // alt-1
    template <typename D, typename ISX, typename Y, typename B, typename FITSUM>
    void lars(const types::f77_integer mtype, const D &d, const ISX &isx,
              const Y &y, types::f77_integer &ip, types::f77_integer &nstep,
              B &&b, FITSUM &&fitsum) {
      correg::OptionalG02MA local_opt;

      lars(mtype, d, isx, y, ip, nstep, b, fitsum, local_opt);
    }
  }
}
#define g02ma correg::lars
#endif
