#ifndef NAGCPP_UT_UTILITY_ARRAY_WRAPPER_HPP
#define NAGCPP_UT_UTILITY_ARRAY_WRAPPER_HPP

#include "utility/nagcpp_utility_array.hpp"
#include <memory>

namespace nagcpp {
  namespace ut {
    // the ut::arrayXD_wrapper classes iare a wrappers around the
    // data_handling::arrayXD classes used when doing the unit tests
    // used because data_handling::array1D etc are wrapper classes themselves,
    // wrapping raw pointers and so arrayXD is used to hold the
    // actual data during testing (when testing callback functionality
    // the actually class, i.e. data_handling::array1D, is used instead)

    template <typename RT, enum data_handling::INOUT inout>
    class array1D_wrapper {
      using CRT = typename data_handling::add_const_if_in<RT, inout>::type;
      using UA = typename utility::array1D<RT, inout>;

    private:
      std::vector<RT> raw_data;
      std::unique_ptr<UA> ua;

    public:
      template <typename IT1>
      array1D_wrapper(const std::vector<RT> initial_values, const IT1 size1_) {
        raw_data = initial_values;
        ua = std::unique_ptr<UA>(new UA(raw_data.data(), size1_));
      }
      template <typename IT1>
      array1D_wrapper(const IT1 size1_) {
        raw_data.resize(size1_);
        ua = std::unique_ptr<UA>(new UA(raw_data.data(), size1_));
      }
      array1D_wrapper() : array1D_wrapper(0) {}

      CRT *data(void) { return (*ua).data(); }
      CRT *data(void) const { return (*ua).data(); }
      types::f77_integer size1(void) const { return (*ua).size1(); }
      types::f77_integer ndims(void) const { return (*ua).ndims(); }

      template <typename IT1>
      CRT &operator()(const IT1 i) const {
        return (*ua)(i);
      }
      template <typename IT1>
      CRT &operator[](const IT1 i) const {
        return (*ua)[i];
      }
      template <typename IT1>
      CRT &operator()(const IT1 i) {
        return (*ua)(i);
      }
      template <typename IT1>
      CRT &operator[](const IT1 i) {
        return (*ua)[i];
      }

      // disable the copy constructor and operator as this is
      // supposed to test the behaviour of array1D etc in
      // nagcpp::utility, and that is what happens there
      array1D_wrapper &operator=(const array1D_wrapper &) = delete;
      array1D_wrapper(const array1D_wrapper &) = delete;
    };

    template <typename RT, enum data_handling::INOUT inout,
              enum ut::SORDER sorder>
    class array2D_wrapper {
      using CRT = typename data_handling::add_const_if_in<RT, inout>::type;
      using UA = typename utility::array2D<RT, inout>;

    private:
      std::vector<RT> raw_data;
      std::unique_ptr<UA> ua;

    public:
      template <typename IT1, typename IT2>
      array2D_wrapper(const std::vector<RT> initial_values, const IT1 size1_,
                      const IT2 size2_) {
        raw_data = initial_values;
        ua = std::unique_ptr<UA>(new UA(raw_data.data(), size1_, size2_,
                                        ut::is_col_major<sorder>::value));
      }
      template <typename IT1, typename IT2>
      array2D_wrapper(const IT1 size1_, const IT2 size2_) {
        raw_data.resize(size1_ * size2_);
        ua = std::unique_ptr<UA>(new UA(raw_data.data(), size1_, size2_,
                                        ut::is_col_major<sorder>::value));
      }
      array2D_wrapper() : array2D_wrapper(0, 0) {}

      CRT *data(void) { return (*ua).data(); }
      CRT *data(void) const { return (*ua).data(); }
      types::f77_integer size1(void) const { return (*ua).size1(); }
      types::f77_integer size2(void) const { return (*ua).size2(); }
      types::f77_integer ndims(void) const { return (*ua).ndims(); }
      bool is_col_major(void) const { return (*ua).is_col_major(); }

      template <typename IT1, typename IT2>
      CRT &operator()(const IT1 i, const IT2 j) const {
        return (*ua)(i, j);
      }
      template <typename IT1, typename IT2>
      CRT &operator()(const IT1 i, const IT2 j) {
        return (*ua)(i, j);
      }

      template <typename IT>
      CRT &operator[](const IT i) const {
        return (*ua)[i];
      }
      template <typename IT>
      CRT &operator[](const IT i) {
        return (*ua)[i];
      }

      // disable the copy constructor and operator as this is
      // supposed to test the behaviour of array2D etc in
      // nagcpp::utility, and that is what happens there
      array2D_wrapper &operator=(const array2D_wrapper &) = delete;
      array2D_wrapper(const array2D_wrapper &) = delete;
    };

    template <typename RT, enum data_handling::INOUT inout,
              enum ut::SORDER sorder>
    class array3D_wrapper {
      using CRT = typename data_handling::add_const_if_in<RT, inout>::type;
      using UA = typename utility::array3D<RT, inout>;

    private:
      std::vector<RT> raw_data;
      std::unique_ptr<UA> ua;

    public:
      template <typename IT1, typename IT2, typename IT3>
      array3D_wrapper(const std::vector<RT> initial_values, const IT1 size1_,
                      const IT2 size2_, const IT3 size3_) {
        raw_data = initial_values;
        ua = std::unique_ptr<UA>(new UA(raw_data.data(), size1_, size2_, size3_,
                                        ut::is_col_major<sorder>::value));
      }
      template <typename IT1, typename IT2, typename IT3>
      array3D_wrapper(const IT1 size1_, const IT2 size2_, const IT3 size3_) {
        raw_data.resize(size1_ * size2_ * size3_);
        ua = std::unique_ptr<UA>(new UA(raw_data.data(), size1_, size2_, size3_,
                                        ut::is_col_major<sorder>::value));
      }
      array3D_wrapper() : array3D_wrapper(0, 0, 0) {}

      CRT *data(void) { return (*ua).data(); }
      CRT *data(void) const { return (*ua).data(); }
      types::f77_integer size1(void) const { return (*ua).size1(); }
      types::f77_integer size2(void) const { return (*ua).size2(); }
      types::f77_integer size3(void) const { return (*ua).size3(); }
      types::f77_integer ndims(void) const { return (*ua).ndims(); }
      bool is_col_major(void) const { return (*ua).is_col_major(); }

      template <typename IT1, typename IT2, typename IT3>
      CRT &operator()(const IT1 i, const IT2 j, const IT3 k) const {
        return (*ua)(i, j, k);
      }
      template <typename IT1, typename IT2, typename IT3>
      CRT &operator()(const IT1 i, const IT2 j, const IT3 k) {
        return (*ua)(i, j, k);
      }

      template <typename IT>
      CRT &operator[](const IT i) const {
        return (*ua)[i];
      }
      template <typename IT>
      CRT &operator[](const IT i) {
        return (*ua)[i];
      }

      // disable the copy constructor and operator as this is
      // supposed to test the behaviour of array3D etc in
      // nagcpp::utility, and that is what happens there
      array3D_wrapper &operator=(const array3D_wrapper &) = delete;
      array3D_wrapper(const array3D_wrapper &) = delete;
    };
  }
}
#endif
