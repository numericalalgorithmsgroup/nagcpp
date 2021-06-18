#ifndef NAGCPP_DATA_HANDLING_STD_VECTOR_HPP
#define NAGCPP_DATA_HANDLING_STD_VECTOR_HPP

#include "nagcpp_data_handling_base.hpp"
#include "nagcpp_utility_array.hpp"
#include <type_traits>

namespace nagcpp {
  namespace data_handling {
    // we don't need a RawData specialization as the default works for std::vector

    // handle conversion of NAG array to std::vector ...
    template <typename RT, enum ArgIntent inout,
              typename ALLOCATOR = std::allocator<RT>>
    class nag_1D_array_to_std_vector {
      using NART =
        typename add_const_if_in<utility::array1D<RT, inout>, inout>::type;
      using VRT = typename std::vector<RT, ALLOCATOR>;
      using CVRT = typename add_const_if_in<VRT, inout>::type;

    private:
      NART &nag_array;
      VRT vector;

    public:
      nag_1D_array_to_std_vector(NART &nag_array_) : nag_array(nag_array_) {
        copy_in();
      }
      ~nag_1D_array_to_std_vector() { copy_back(); }

      CVRT &get(void) { return vector; }

    private:
      template <typename DUMMY = void>
      auto copy_in(void) ->
        typename std::enable_if<is_out<inout>::value, DUMMY>::type {
        // OUT version
        size_t n = static_cast<size_t>(nag_array.size1());
        vector.resize(n);
      }
      template <typename DUMMY = void>
      auto copy_in(void) ->
        typename std::enable_if<!is_out<inout>::value, DUMMY>::type {
        // IN and INOUT version
        size_t n = static_cast<size_t>(nag_array.size1());
        vector.resize(n);
        for (size_t i = 0; i < n; ++i) {
          vector[i] = nag_array(i);
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
        size_t n = static_cast<size_t>(nag_array.size1());
        n = std::min(n, vector.size());
        for (size_t i = 0; i < n; ++i) {
          nag_array(i) = vector[i];
        }
      }
    };

    template <typename RT, enum ArgIntent inout, typename ALLOCATOR>
    struct convert_nag_array_to_user_t<utility::array1D<RT, inout>, inout,
                                       std::vector<RT, ALLOCATOR>> {
      static nag_1D_array_to_std_vector<RT, inout, ALLOCATOR> get(
        utility::array1D<RT, inout> &nag_array){
        return nag_1D_array_to_std_vector<RT, inout, ALLOCATOR>(nag_array);}
  };

  template <typename RT, typename ALLOCATOR>
  struct convert_nag_array_to_user_t<const utility::array1D<RT, IntentIN>, IntentIN,
                                     std::vector<RT, ALLOCATOR>> {
    static const nag_1D_array_to_std_vector<RT, IntentIN, ALLOCATOR>
      get(const utility::array1D<RT, IntentIN> &nag_array) {
      return nag_1D_array_to_std_vector<RT, IntentIN, ALLOCATOR>(nag_array);
    }
  };
  // ... handle conversion of NAG array to std::vector
}
}

#endif
