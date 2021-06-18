#ifndef NAGCPP_DATA_HANDLING_BOOST_MATRIX_HPP
#define NAGCPP_DATA_HANDLING_BOOST_MATRIX_HPP

#include "nagcpp_available_data_containers.hpp"

#ifdef HAVE_BOOST_MATRIX
#include "nagcpp_data_handling_base.hpp"
#include <boost/numeric/ublas/matrix.hpp>

namespace nagcpp {
  namespace data_handling {

    template <typename RT, enum ArgIntent inout, typename SO>
    class RawData<RT, inout, boost::numeric::ublas::matrix<RT, SO>>
      : public BaseRawData<RT, inout> {
        using CRT = typename add_const_if_in<RT, inout>::type;
        using BMRT = typename boost::numeric::ublas::matrix<RT, SO>;
        using BMRT_ROW = typename boost::numeric::ublas::matrix<
          RT, boost::numeric::ublas::row_major>;
        using BMRT_COLUMN = typename boost::numeric::ublas::matrix<
          RT, boost::numeric::ublas::column_major>;

        public : RawData(){}

        RawData(const BMRT &array_container){get_data(array_container);}

    virtual ~RawData(void) {}

    void get_data(const BMRT &array_container) {
      // NB: getData requires the data method to be implemented, we
      // do not check that it is, i.e. using a static_assert with
      // has_data<AC, int> == true as the condition
      // because we want to allow arrays to be passed as nulltpr
      // in some circumstances - so checks for null data have
      // to be runtime and not compile time
      this->ndims = 2;
      this->size1 = array_container.size1();
      this->size2 = array_container.size2();
      this->nelements = this->size1.value * this->size2.value;
      this->allocate();

      // as we are copying the data anyway, ideally we would
      // always use column major order. However, multi-dimensional
      // arrays to the algorithmic engine need to use consistent storage
      // (i.e. they all need to either be row major order, or all
      // column major order) - if we force these to always be
      // column major order then that may cause issues when mixing
      // container types
      this->is_col_major = this_is_col_major(array_container);

      if (this->is_col_major.value) {
        for (types::f77_integer j = 0, p = 0; j < this->size2.value; ++j) {
          for (types::f77_integer i = 0; i < this->size1.value; ++i, ++p) {
            this->ldata[p] = array_container(i, j);
          }
        }
      } else {
        for (types::f77_integer i = 0, p = 0; i < this->size1.value; ++i) {
          for (types::f77_integer j = 0; j < this->size2.value; ++j, ++p) {
            this->ldata[p] = array_container(i, j);
          }
        }
      }
    }

    template <typename DUMMY = void>
    auto resize(BMRT &array_container, types::f77_integer size1_,
                types::f77_integer size2_) ->
      typename std::enable_if<!is_in<inout>::value, DUMMY>::type {
      // we don't need to resize the array container at this point
      // as the copy_back method will always be called prior to
      // returning the results
      this->size1 = (size1_ < 0) ? 0 : size1_;
      this->size2 = (size2_ < 0) ? 0 : size2_;
      this->nelements = this->size1.value * this->size2.value;
      this->allocate();
    }

    template <typename DUMMY = void>
    auto copy_back(BMRT &array_container) ->
      typename std::enable_if<!is_in<inout>::value, DUMMY>::type const {
      copy_back(array_container, this->size1.value, this->size2.value);
    }

    template <typename DUMMY = void>
    auto copy_back(BMRT &array_container, types::f77_integer size1_,
                   types::f77_integer size2_) ->
      typename std::enable_if<!is_in<inout>::value, DUMMY>::type const {

      // size1_ and size2_ should always be non -ve, but just in case ...
      types::f77_integer rn1 = (size1_ < 0) ? 0 : size1_;
      types::f77_integer rn2 = (size2_ < 0) ? 0 : size2_;

      array_container.resize(rn1, rn2);

      // size1_ and size2_ should always be <= the values stored in this, but just in case ...
      types::f77_integer cn1 = std::min(this->size1.value, rn1);
      types::f77_integer cn2 = std::min(this->size2.value, rn2);

      if (this->is_col_major.value) {
        for (types::f77_integer j = 0, p = 0; j < cn2; ++j) {
          for (types::f77_integer i = 0; i < cn1; ++i, ++p) {
            array_container(i, j) = this->ldata[p];
          }
          p += (this->size1.value - cn1);
        }
      } else {
        for (types::f77_integer i = 0, p = 0; i < cn1; ++i) {
          for (types::f77_integer j = 0; j < cn2; ++j, ++p) {
            array_container(i, j) = this->ldata[p];
          }
          p += (this->size2.value - cn2);
        }
      }
    }

  private:
    inline static bool this_is_col_major(const BMRT_COLUMN &array_container) {
      return true;
    }
    inline static bool this_is_col_major(const BMRT_ROW &array_container) {
      return false;
    }
  };

  // handle conversion of NAG array to boost::numeric::ublas::matrix ...
  template <typename RT, enum ArgIntent inout, typename SO>
  class nag_2D_array_to_boost_matrix {
    using NART =
      typename add_const_if_in<utility::array2D<RT, inout>, inout>::type;
    using BMRT = typename boost::numeric::ublas::matrix<RT, SO>;
    using CBMRT = typename add_const_if_in<BMRT, inout>::type;

    private : NART & nag_array;
    BMRT matrix;

    public : nag_2D_array_to_boost_matrix(NART & nag_array_) :
      nag_array(nag_array_){copy_in();}
  ~nag_2D_array_to_boost_matrix() { copy_back(); }

  CBMRT &get(void) { return matrix; }

private:
  template <typename DUMMY = void>
  auto copy_in(void) ->
    typename std::enable_if<is_out<inout>::value, DUMMY>::type {
    // OUT version
    size_t n1 = static_cast<size_t>(nag_array.size1());
    size_t n2 = static_cast<size_t>(nag_array.size2());
    matrix.resize(n1, n2);
  }
  template <typename DUMMY = void>
  auto copy_in(void) ->
    typename std::enable_if<!is_out<inout>::value, DUMMY>::type {
    // IN and INOUT version
    size_t n1 = static_cast<size_t>(nag_array.size1());
    size_t n2 = static_cast<size_t>(nag_array.size2());
    matrix.resize(n1, n2);
    for (size_t i = 0; i < n1; ++i) {
      for (size_t j = 0; j < n2; ++j) {
        matrix(i, j) = nag_array(i, j);
      }
    }
  }

  template <typename DUMMY = void>
  auto copy_back(void) ->
    typename std::enable_if<is_in<inout>::value, DUMMY>::type {
    // IN version
  }
  template <typename DUMMY = void>
  auto copy_back(void) ->
    typename std::enable_if<!is_in<inout>::value, DUMMY>::type {
    // OUT and INOUT version
    size_t n1 = static_cast<size_t>(nag_array.size1());
    size_t n2 = static_cast<size_t>(nag_array.size2());
    n1 = std::min(n1, matrix.size1());
    n2 = std::min(n2, matrix.size2());
    for (size_t i = 0; i < n1; ++i) {
      for (size_t j = 0; j < n2; ++j) {
        nag_array(i, j) = matrix(i, j);
      }
    }
  }
};

template <typename RT, enum ArgIntent inout, typename SO>
struct convert_nag_array_to_user_t<utility::array2D<RT, inout>, inout,
                                   boost::numeric::ublas::matrix<RT, SO>> {
  static nag_2D_array_to_boost_matrix<RT, inout, SO> get(
    utility::array2D<RT, inout> &nag_array){
    return nag_2D_array_to_boost_matrix<RT, inout, SO>(nag_array);}
}
;

template <typename RT, typename SO>
struct convert_nag_array_to_user_t<const utility::array2D<RT, IntentIN>, IntentIN,
                                   boost::numeric::ublas::matrix<RT, SO>> {
  static const nag_2D_array_to_boost_matrix<RT, IntentIN, SO>
    get(const utility::array2D<RT, IntentIN> &nag_array) {
    return nag_2D_array_to_boost_matrix<RT, IntentIN, SO>(nag_array);
  }
};
// ... handle conversion of NAG array to boost::numeric::ublas::matrix
}
}
#endif

#endif
