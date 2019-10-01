# C++11  Interfaces for the NAG Library

This is version 27.0.0.0 of a set of C++11 interfaces for the NAG Library, supplied as a series of header files.

In order to make use of this product you will need a copy of [Mark 27.0 of the NAG Library](https://www.nag.co.uk/content/nag-library) installed on your system.

Currently only interfaces for a small subset of routines from the NAG Library are
available in this form. These interfaces are automatically generated, and their
primary purpose is to elicit feedback on their design prior to rolling the
process out across the whole library.

## Quickstart using NLL6I27DBL for Linux

[NLL6I27DBL](https://www.nag.co.uk/content/downloads-nag-library-nll6i27dbl) is Mark 27 of the NAG Unified Library for Linux.  
Assuming that you have this installed at `/opt/NAG/nll6i27dbl/` and are using the Bash shell, here's how to obtain the C++ wrappers and compile one of the examples

```
# Set up the environment for the NAG Library
# 64 bit Integers using vendor provided (MKL) BLAS, dynamic linking
source /opt/NAG/nll6i27dbl/scripts/nagvars.sh int64 vendor dynamic

# Download the C++ wrappers
git clone https://github.com/numericalalgorithmsgroup/nagcpp

# Navigate to examples and compile
cd nagcpp/examples/
g++ ex_e04pt.cpp -I../include ${NAGLIB_INCLUDE} ${NAGLIB_LINK} -o ex_e04pt

#Run compiled example
./ex_e04pt
```

In the above, `-I../include` is the relative path to the NAG C++ include directory from the examples directory.  You will need to include the full path to this directory if you compile from anywhere else.
`${NAGLIB_INCLUDE}` and  `${NAGLIB_LINK}` are include and link flags set by the `nagvars.sh` script for the main Library.


## Examples supplied with this repo

* [contfn_brent (c05ay)](./examples/ex_c05ay.cpp) - locates a simple zero of a continuous function in a given interval using Brent’s method.
* [md_gauss (d01fb)](./examples/ex_d01fb.cpp) - computes an estimate of a multidimensional integral (1 to 20), given the analytic form of the integrand and suitable Gaussian weights and abscissae.
* [dim1_spline (e01ba)](./examples/ex_e01ba.cpp) - determines a cubic spline interpolant to a given set of data.
* [dim1_spline_eval (e02bb)](./examples/ex_e02bb.cpp) - evaluates a cubic spline from its B-spline representation.
* [handle_solve_dfls_rcomm (e04fg)](./examples/ex_e04fg_boost.cpp) -  a reverse communication Derivative-free Optimization (DFO) solver  for small to medium-scale nonlinear least squares problems with bound constraints.
* [handle_solve_bounds_foas (e04kf)](./examples/ex_e04kf.cpp) - solver for bound-constrained large-scale nonlinear programming (NLP) problems. 
* [handle_solve_lp_ipm (e04mt)](./examples/ex_e04mt.cpp) -  solver for large-scale linear programming (LP) problems
* [handle_solve_socp_ipm (e04pt)](./examples/ex_e04pt.cpp) - solver for large-scale second-order cone programming (SOCP) problems
* [handle_solve_ipopt (e04st)](./examples/ex_e04st.cpp) - solver for large scale nonlinear programming (NLP) problems.
* [nlp1_solve (e04uc)](./examples/ex_e04uc.cpp) - minimize an arbitrary smooth function subject to constraints (which may include simple bounds on the variables, linear constraints and smooth nonlinear constraints) using a sequential quadratic programming (SQP) method. 
* [real_nmf_rcomm (f01sb)](./examples/ex_f01sb.cpp)- real_nmf_rcomm computes a non-negative matrix factorization for a real non-negative 
m by n matrix A. It uses reverse communication for evaluating matrix products, so that the matrix A is not accessed explicitly
* [quantiles (g01am)](./examples/ex_g01am.cpp) - finds specified quantiles from a vector of unsorted data.
* [prob_students_t_noncentral](./examples/ex_g01gb.cpp) - returns the lower tail probability for the noncentral Student’s t-distribution.
* [corrmat_nearest_rank (g02ak)](./examples/ex_g02ak.cpp) - computes the nearest correlation matrix of maximum prescribed rank, in the Frobenius norm, to a given square, input matrix.
* [lars (g02ma)](./examples/ex_g02ma.cpp) - performs Least Angle Regression (LARS), forward stagewise linear regression or Least Absolute Shrinkage and Selection Operator (LASSO).

## Basic documentation

Assuming that you have installed the C++ interfaces into the directory called
`[NAGCPP_INSTALL_DIR]` then you should have four subdirectories:

* `[NAGCPP_INSTALL_DIR]/include`

  Contains the C++ wrappers and all required utility headers.
* `[NAGCPP_INSTALL_DIR]/examples`

  Contains a sample of examples calling the interfaces.
* `[NAGCPP_INSTALL_DIR]/tests`

  Contains a series of unit tests that have been used to test the supplied
  wrappers.
* `[NAGCPP_INSTALL_DIR]/scripts`

  Contains a number of Linux scripts for compiling and running the examples
  and unit tests. These scripts can also be run from WSL or cygwin. Prior to
  running any of these scripts you should ensure that your environment is set
  up correctly by, for example, running either envvars.bat, nagvars.sh or
  nagvars.csh, supplied with the NAG Library. Which is supplied / required
  depends on whether you are on Windows or Linux and, if on Linux, which shell
  you are using.

When using the C++ interfaces supplied with this Readme you will need to add the
directory `[NAGCPP_INSTALL_DIR]/include` to the list of directories your compiler
searches for header files in addition to using any compiler flags usually
required by the NAG Library (as specified in the Users' Notes supplied with your
version of the library and also available from the NAG website at
https://www.nag.co.uk/content/nag-library-mark-27).

## Full documentation for the C+11 interfaces

A more comprehensive set of documentation is available from the NAG website: https://www.nag.com/numeric/nl/nagdoc_27cpp/cpphtml/frontmatter/manconts.html
