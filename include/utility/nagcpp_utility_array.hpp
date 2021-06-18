#ifndef NAGCPP_UTILITY_ARRAY_HPP
#define NAGCPP_UTILITY_ARRAY_HPP
#include "nagcpp_data_handling_base.hpp"
#include "nagcpp_engine_types.hpp"

namespace nagcpp {
  namespace utility {
    template <typename RT,
              enum data_handling::ArgIntent inout = data_handling::ArgIntent::IntentINOUT>
    class array1D {
      using CRT = typename data_handling::add_const_if_in<RT, inout>::type;

    private:
      CRT *const raw_data;
      types::f77_integer asize1;

    public:
      template <typename IT>
      array1D(CRT *raw_data_, const IT size_)
        : raw_data(raw_data_), asize1(static_cast<types::f77_integer>(size_)) {}

      // disable the copy constructor and operator as we are
      // using raw pointers and have not implemented them
      array1D &operator=(const array1D &) = delete;
      array1D(const array1D &) = delete;

      CRT *data(void) { return raw_data; }
      const CRT *data(void) const { return raw_data; }

      types::f77_integer size1(void) const { return asize1; }
      types::f77_integer ndims(void) const { return 1; }

      template <typename IT>
      CRT &operator()(const IT i) const {
        return raw_data[i];
      }
      template <typename IT>
      CRT &operator[](const IT i) const {
        return raw_data[i];
      }
      template <typename IT>
      CRT &operator()(const IT i) {
        return raw_data[i];
      }
      template <typename IT>
      CRT &operator[](const IT i) {
        return raw_data[i];
      }
    };

    template <typename RT,
              enum data_handling::ArgIntent inout = data_handling::ArgIntent::IntentINOUT>
    class array2D {
      using CRT = typename data_handling::add_const_if_in<RT, inout>::type;

    private:
      CRT *const raw_data;
      types::f77_integer asize1;
      types::f77_integer asize2;
      bool col_major;
      types::f77_integer astride1;

    public:
      template <typename IT1, typename IT2>
      array2D(CRT *raw_data_, const IT1 size1_, const IT2 size2_,
              const bool col_major_ = true)
        : raw_data(raw_data_), asize1(static_cast<types::f77_integer>(size1_)),
          asize2(static_cast<types::f77_integer>(size2_)),
          col_major(col_major_) {
        if (col_major_) {
          astride1 = static_cast<types::f77_integer>(size1_);
        } else {
          astride1 = static_cast<types::f77_integer>(size2_);
        }
      }

      // disable the copy constructor and operator as we are
      // using raw pointers and have not implemented them
      array2D &operator=(const array2D &) = delete;
      array2D(const array2D &) = delete;

      CRT *data(void) { return raw_data; }
      const CRT *data(void) const { return raw_data; }

      types::f77_integer size1(void) const { return asize1; }
      types::f77_integer size2(void) const { return asize2; }
      types::f77_integer stride(void) const { return astride1; }
      bool is_col_major(void) const { return col_major; }
      types::f77_integer ndims(void) const { return 2; }

      template <typename IT1, typename IT2>
      CRT &operator()(const IT1 i, const IT2 j) const {
        if (col_major) {
          return raw_data[j * astride1 + i];
        } else {
          return raw_data[i * astride1 + j];
        }
      }
      template <typename IT1, typename IT2>
      CRT &operator()(const IT1 i, const IT2 j) {
        if (col_major) {
          return raw_data[j * astride1 + i];
        } else {
          return raw_data[i * astride1 + j];
        }
      }
      template <typename IT>
      CRT &operator[](const IT i) const {
        return raw_data[i];
      }
      template <typename IT>
      CRT &operator[](const IT i) {
        return raw_data[i];
      }
    };

    template <typename RT,
              enum data_handling::ArgIntent inout = data_handling::ArgIntent::IntentINOUT>
    class array3D {
      using CRT = typename data_handling::add_const_if_in<RT, inout>::type;

    private:
      CRT *const raw_data;
      types::f77_integer asize1;
      types::f77_integer asize2;
      types::f77_integer asize3;
      bool col_major;
      types::f77_integer astride1;
      types::f77_integer astride2;
      types::f77_integer tstride;

    public:
      template <typename IT1, typename IT2, typename IT3>
      array3D(CRT *raw_data_, const IT1 size1_, const IT2 size2_,
              const IT3 size3_, const bool col_major_ = true)
        : raw_data(raw_data_), asize1(static_cast<types::f77_integer>(size1_)),
          asize2(static_cast<types::f77_integer>(size2_)),
          asize3(static_cast<types::f77_integer>(size3_)),
          col_major(col_major_) {
        if (col_major_) {
          astride1 = static_cast<types::f77_integer>(size1_);
        } else {
          astride1 = static_cast<types::f77_integer>(size3_);
        }
        astride2 = static_cast<types::f77_integer>(size2_);
        tstride = astride1 * astride2;
      }

      // disable the copy constructor and operator as we are
      // using raw pointers and have not implemented them
      array3D &operator=(const array3D &) = delete;
      array3D(const array3D &) = delete;

      CRT *data(void) { return raw_data; }
      const CRT *data(void) const { return raw_data; }

      types::f77_integer size1(void) const { return asize1; }
      types::f77_integer size2(void) const { return asize2; }
      types::f77_integer size3(void) const { return asize3; }
      types::f77_integer stride1(void) const { return astride1; }
      types::f77_integer stride2(void) const { return astride2; }
      bool is_col_major(void) const { return col_major; }
      types::f77_integer ndims(void) const { return 3; }

      template <typename IT1, typename IT2, typename IT3>
      CRT &operator()(const IT1 i, const IT2 j, const IT3 k) const {
        if (col_major) {
          return raw_data[k * tstride + j * astride1 + i];
        } else {
          return raw_data[i * tstride + j * astride1 + k];
        }
      }
      template <typename IT1, typename IT2, typename IT3>
      CRT &operator()(const IT1 i, const IT2 j, const IT3 k) {
        if (col_major) {
          return raw_data[k * tstride + j * astride1 + i];
        } else {
          return raw_data[i * tstride + j * astride1 + k];
        }
      }
      template <typename IT>
      CRT &operator[](const IT i) const {
        return raw_data[i];
      }
    };

  }
}
#endif
