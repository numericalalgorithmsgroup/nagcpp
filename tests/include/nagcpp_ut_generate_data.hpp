#ifndef NAGCPP_UT_GENERATE_DATA_HPP
#define NAGCPP_UT_GENERATE_DATA_HPP
#include "nagcpp_ut_utilities.hpp"
#include <vector>

namespace nagcpp {
  namespace ut {
    // return some standard data (for vectors / 1D arrays) ...
    // should be used to populate the types being tested with standardised values
    // when writing get_test_data returned class instances should be populated with values
    // from get_expected_values with adjust = 0 (or the overload where it is not supplied)
    template <typename RT>
    std::vector<RT> get_expected_values(const size_t n1, RT adjust) {
      std::vector<RT> ac(n1);
      RT dn1 = static_cast<RT>(n1 + 2);
      for (size_t i = 0; i < n1; ++i) {
        RT di = static_cast<RT>(i + 1);
        ac[i] = di * static_cast<RT>(10.0) + di / dn1 + adjust;
      }
      return ac;
    }
    template <typename RT>
    std::vector<RT> get_expected_values(const size_t n1) {
      return get_expected_values<RT>(n1, static_cast<RT>(0));
    }
    // ... return some standard data (for vectors / 1D arrays)

    // return some standard data (for matrices / 2D arrays)  ...
    // should be used to populate the types being tested with standardised values
    // when writing get_test_data returned class instances should be populated with values
    // from get_expected_values with adjust = 0 (or the overload where it is not supplied)
    // get_expected_values returns data in a contiguous form (in a std::vector). the data
    // is packed using either column major or row major order, depending on the value of
    // the sorder template parameter
    // column major order:
    //   the values for column 1 are in the first n1 elements of the vector
    //   the values for column 2 are in the next n1 elements of the vector
    //   etc
    // row major order:
    //   the values for row 1 are in the first n2 elements of the vector
    //   the values for row 2 are in the next n2 elements of the vector
    //   etc
    template <enum ut::SORDER sorder, typename RT>
    std::vector<RT> get_expected_values(const size_t n1, const size_t n2,
                                        RT adjust) {
      std::vector<RT> ac(n1 * n2);
      RT dn1 = static_cast<RT>(n1 + 2);
      if (ut::is_col_major<sorder>::value) {
        for (size_t j = 0, p = 0; j < n2; ++j) {
          RT dj = static_cast<RT>(n1 * (j + 1)) * static_cast<RT>(10.0);
          for (size_t i = 0; i < n1; ++i, ++p) {
            RT di = static_cast<RT>(i + 1);
            ac[p] = dj + di * static_cast<RT>(10.0) + di / dn1 + adjust;
          }
        }
      } else {
        for (size_t i = 0, p = 0; i < n1; ++i) {
          RT di = static_cast<RT>(i + 1);
          for (size_t j = 0; j < n2; ++j, ++p) {
            RT dj = static_cast<RT>(n1 * (j + 1)) * static_cast<RT>(10.0);
            ac[p] = dj + di * static_cast<RT>(10.0) + di / dn1 + adjust;
          }
        }
      }
      return ac;
    }
    template <enum ut::SORDER sorder, typename RT>
    std::vector<RT> get_expected_values(const size_t n1, const size_t n2) {
      return get_expected_values<sorder, RT>(n1, n2, static_cast<RT>(0));
    }
    // ... return some standard data (for matrices / 2D arrays)

    // return some standard data (for tables / 3D arrays)  ...
    // should be used to populate the types being tested with standardised values
    // when writing get_test_data returned class instances should be populated with values
    // from get_expected_values with adjust = 0 (or the overload where it is not supplied)
    // get_expected_values returns data in a contiguous form (in a std::vector). the data
    // is packed using either column major or row major order, depending on the value of
    // the sorder template parameter
    // column major order:
    //   the values for column 1 are in the first n1 elements of the vector
    //   the values for column 2 are in the next n1 elements of the vector
    //   etc
    // row major order:
    //   the values for row 1 are in the first n2 elements of the vector
    //   the values for row 2 are in the next n2 elements of the vector
    //   etc
    template <enum ut::SORDER sorder, typename RT>
    std::vector<RT> get_expected_values(const size_t n1, const size_t n2,
                                        const size_t n3, RT adjust) {
      std::vector<RT> ac(n1 * n2 * n3);
      RT dn1 = static_cast<RT>(n1 + 2);
      if (ut::is_col_major<sorder>::value) {
        for (size_t k = 0, p = 0; k < n3; ++k) {
          RT dk = static_cast<RT>(n1 * n2 * (k + 1)) * static_cast<RT>(10.0);
          for (size_t j = 0; j < n2; ++j) {
            RT dj = static_cast<RT>(n1 * (j + 1)) * static_cast<RT>(10.0);
            for (size_t i = 0; i < n1; ++i, ++p) {
              RT di = static_cast<RT>(i + 1);
              ac[p] = dk + dj + di * static_cast<RT>(10.0) + di / dn1 + adjust;
            }
          }
        }
      } else {
        for (size_t i = 0, p = 0; i < n1; ++i) {
          RT di = static_cast<RT>(i + 1);
          for (size_t j = 0; j < n2; ++j) {
            RT dj = static_cast<RT>(n1 * (j + 1)) * static_cast<RT>(10.0);
            for (size_t k = 0; k < n3; ++k, ++p) {
              RT dk =
                static_cast<RT>(n1 * n2 * (k + 1)) * static_cast<RT>(10.0);
              ac[p] = dk + dj + di * static_cast<RT>(10.0) + di / dn1 + adjust;
            }
          }
        }
      }
      return ac;
    }
    template <enum ut::SORDER sorder, typename RT>
    std::vector<RT> get_expected_values(const size_t n1, const size_t n2,
                                        const size_t n3) {
      return get_expected_values<sorder, RT>(n1, n2, n3, static_cast<RT>(0));
    }
    // ... return some standard data (for tables / 3D arrays)

    // return sub matrices / tables ...
    // given a packed on1 x on2 matrix, return the top left n1 x n2 sub matrix
    template <enum ut::SORDER sorder, typename RT>
    std::vector<RT> top_left(RT *values, const size_t on1, const size_t on2,
                             const size_t n1, const size_t n2,
                             const RT pad = 0) {
      std::vector<RT> ac(n1 * n2);

      // no bounds checks are done, so make sure we don't go out of bounds
      size_t cn1 = std::min(on1, n1);
      size_t cn2 = std::min(on2, n2);

      if (is_col_major<sorder>::value) {
        size_t i, j, p;
        for (j = 0, p = 0; j < cn2; ++j) {
          for (i = 0; i < cn1; ++i, ++p) {
            ac[p] = values[j * on1 + i];
          }
          // initialise any row oversizes with zeros
          for (; i < n1; ++i, ++p) {
            ac[p] = pad;
          }
        }
        // initialise any column oversizes with zeros
        for (; j < n2; ++j) {
          for (i = 0; i < n1; ++i, ++p) {
            ac[p] = pad;
          }
        }

      } else {
        // row major order
        size_t i, j, p;
        for (i = 0, p = 0; i < cn1; ++i) {
          for (j = 0; j < cn2; ++j, ++p) {
            ac[p] = values[i * on2 + j];
          }

          // initialise any column oversizes with zeros
          for (; j < n2; ++j, ++p) {
            ac[p] = pad;
          }
        }
        // initialise any row oversizes with zeros
        for (; i < n1; ++i) {
          for (j = 0; j < n2; ++j, ++p) {
            ac[p] = pad;
          }
        }
      }
      return ac;
    }

    // given a packed on1 x on2 x on3 table, return the top left corner, defined
    // as the top left n1 x n2 of the first n3 matrices
    template <enum ut::SORDER sorder, typename RT>
    std::vector<RT> top_left(RT *values, const size_t on1, const size_t on2,
                             const size_t on3, const size_t n1, const size_t n2,
                             const size_t n3, const RT pad = 0) {
      std::vector<RT> ac(n1 * n2 * n3);

      // no bounds checks are done, so make sure we don't go out of bounds
      size_t cn1 = std::min(on1, n1);
      size_t cn2 = std::min(on2, n2);
      size_t cn3 = std::min(on3, n3);

      size_t on12 = on1 * on2;
      size_t on23 = on2 * on3;
      if (is_col_major<sorder>::value) {
        size_t i, j, k, p;
        for (k = 0, p = 0; k < cn3; ++k) {
          for (j = 0; j < cn2; ++j) {
            for (i = 0; i < cn1; ++i, ++p) {
              ac[p] = values[k * on12 + j * on1 + i];
            }
            // initialise any row oversizes with zeros
            for (; i < n1; ++i, ++p) {
              ac[p] = pad;
            }
          }
          // initialise any column oversizes with zeros
          for (; j < n2; ++j) {
            for (i = 0; i < n1; ++i, ++p) {
              ac[p] = pad;
            }
          }
        }
        // initialise any table oversizes with zeros
        for (; k < n3; ++k) {
          for (j = 0; j < n2; ++j) {
            for (i = 0; i < n1; ++i, ++p) {
              ac[p] = pad;
            }
          }
        }

      } else {
        // row major order
        size_t i, j, k, p;
        for (i = 0, p = 0; i < cn1; ++i) {
          for (j = 0; j < cn2; ++j) {
            for (k = 0; k < cn3; ++k, ++p) {
              ac[p] = values[i * on23 + j * on3 + k];
            }
            // initialise any table oversizes with zeros
            for (; k < n3; ++k, ++p) {
              ac[p] = pad;
            }
          }
          // initialise any column oversizes with zeros
          for (; j < n2; ++j) {
            for (k = 0; k < n3; ++k, ++p) {
              ac[p] = pad;
            }
          }
        }
        // initialise any table oversizes with zeros
        for (; i < n1; ++i) {
          for (j = 0; j < n2; ++j) {
            for (k = 0; k < n3; ++k, ++p) {
              ac[p] = pad;
            }
          }
        }
      }

      return ac;
    }
    // ... return sub matrices / tables

    // namespace generate_data {
    //   int mult = 100;
    //   template <typename T>
    //   T *gen_raw_data(int n1) {
    //     T *dx = new T[n1];
    //     T *pdx = dx;
    //     for (int i = 1; i <= n1; i++) {
    //       (*pdx) = static_cast<T>(i);
    //       pdx += 1;
    //     }
    //     return dx;
    //   }
    //   template <typename T>
    //   T *gen_raw_data(int n1, int n2) {
    //     T *dx = new T[n1*n2];
    //     T *pdx = dx;
    //     for (int j = 1; j <= n2; j++) {
    //       for (int i = 1; i <= n1; i++) {
    //         (*pdx) = static_cast<T>((mult * j) + i);
    //         pdx += 1;
    //       }
    //     }
    //     return dx;
    //   }
    //   template <typename T>
    //   T *gen_raw_data(int n1, int n2, int n3) {
    //     T *dx = new T[n1*n2*n3];
    //     T *pdx = dx;
    //     for (int k = 1; k <= n3; k++) {
    //       for (int j = 1; j <= n2; j++) {
    //         for (int i = 1; i <= n1; i++) {
    //           (*pdx) = static_cast<T>((mult * mult * k) + (mult * j) + i);
    //           pdx += 1;
    //         }
    //       }
    //     }
    //     return dx;
    //   }
    // }
  }
}
#endif
