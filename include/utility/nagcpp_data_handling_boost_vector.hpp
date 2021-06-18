#ifndef NAGCPP_DATA_HANDLING_BOOST_VECTOR_HPP
#define NAGCPP_DATA_HANDLING_BOOST_VECTOR_HPP

#include "nagcpp_available_data_containers.hpp"

#ifdef HAVE_BOOST_VECTOR
#include "nagcpp_data_handling_base.hpp"
#include <boost/numeric/ublas/vector.hpp>

namespace nagcpp {
  namespace data_handling {

    template <typename RT, enum ArgIntent inout>
    class RawData<RT, inout, boost::numeric::ublas::vector<RT>>
      : public BaseRawData<RT, inout> {
        using CRT = typename add_const_if_in<RT, inout>::type;
        using BVRT = typename boost::numeric::ublas::vector<RT>;

        public : RawData(){}

        RawData(const BVRT &array_container){get_data(array_container);}

    virtual ~RawData(void) {}

    void get_data(const BVRT &array_container) {
      // NB: getData requires the data method to be implemented, we
      // do not check that it is, i.e. using a static_assert with
      // has_data<AC, int> == true as the condition
      // because we want to allow arrays to be passed as nulltpr
      // in some circumstances - so checks for null data have
      // to be runtime and not compile time
      this->ndims = 1;
      this->size1 = array_container.size();
      this->nelements = this->size1.value;
      this->allocate();

      for (types::f77_integer i = 0; i < this->size1.value; ++i) {
        this->ldata[i] = array_container(i);
      }
    }

    template <typename DUMMY = void>
    auto resize(BVRT &array_container, types::f77_integer size1_) ->
      typename std::enable_if<!is_in<inout>::value, DUMMY>::type {
      // we don't need to resize the array container at this point
      // as the copy_back method will always be called prior to
      // returning the results
      this->size1 = (size1_ < 0) ? 0 : size1_;
      this->nelements = this->size1.value;
      this->allocate();
    }

    template <typename DUMMY = void>
    auto copy_back(BVRT &array_container) ->
      typename std::enable_if<!is_in<inout>::value, DUMMY>::type const {
      copy_back(array_container, this->size1.value);
    }

    template <typename DUMMY = void>
    auto copy_back(BVRT &array_container, types::f77_integer size1_) ->
      typename std::enable_if<!is_in<inout>::value, DUMMY>::type const {

      // size1_ and size2_ should always be non -ve, but just in case ...
      types::f77_integer rn1 = (size1_ < 0) ? 0 : size1_;

      array_container.resize(rn1);

      // size1_ should always be <= the values stored in this, but just in case ...
      types::f77_integer cn1 = std::min(this->size1.value, rn1);

      for (types::f77_integer i = 0; i < cn1; ++i) {
        array_container(i) = this->ldata[i];
      }
    }
  };

  // handle conversion of NAG array to boost::numeric::ublas::vector ...
  template <typename RT, enum ArgIntent inout>
  class nag_1D_array_to_boost_vector {
    using NART =
      typename add_const_if_in<utility::array1D<RT, inout>, inout>::type;
    using BVRT = typename boost::numeric::ublas::vector<RT>;
    using CBVRT = typename add_const_if_in<BVRT, inout>::type;

    private : NART & nag_array;
    BVRT vector;

    public : nag_1D_array_to_boost_vector(NART & nag_array_) :
      nag_array(nag_array_){copy_in();}
  ~nag_1D_array_to_boost_vector() { copy_back(); }

  CBVRT &get(void) { return vector; }

private:
  template <typename DUMMY = void>
  auto copy_in(void) ->
    typename std::enable_if<is_out<inout>::value, DUMMY>::type {
    // OUT version
    size_t n1 = static_cast<size_t>(nag_array.size1());
    vector.resize(n1);
  }
  template <typename DUMMY = void>
  auto copy_in(void) ->
    typename std::enable_if<!is_out<inout>::value, DUMMY>::type {
    // IN and INOUT version
    size_t n1 = static_cast<size_t>(nag_array.size1());
    vector.resize(n1);
    for (size_t i = 0; i < n1; ++i) {
      vector(i) = nag_array(i);
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
    n1 = std::min(n1, vector.size());
    for (size_t i = 0; i < n1; ++i) {
      nag_array(i) = vector(i);
    }
  }
};

template <typename RT, enum ArgIntent inout>
struct convert_nag_array_to_user_t<utility::array1D<RT, inout>, inout,
                                   boost::numeric::ublas::vector<RT>> {
  static nag_1D_array_to_boost_vector<RT, inout> get(
    utility::array1D<RT, inout> &nag_array){
    return nag_1D_array_to_boost_vector<RT, inout>(nag_array);}
}
;

template <typename RT>
struct convert_nag_array_to_user_t<const utility::array1D<RT, IntentIN>, IntentIN,
                                   boost::numeric::ublas::vector<RT>> {
  static const nag_1D_array_to_boost_vector<RT, IntentIN>
    get(const utility::array1D<RT, IntentIN> &nag_array) {
    return nag_1D_array_to_boost_vector<RT, IntentIN>(nag_array);
  }
};
// ... handle conversion of NAG array to boost::numeric::ublas::vector
}
}
#endif

#endif
