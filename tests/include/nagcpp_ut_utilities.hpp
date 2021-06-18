#ifndef NAGCPP_UT_UTILITIES_HPP
#define NAGCPP_UT_UTILITIES_HPP

#include "utility/nagcpp_data_handling_base.hpp"

namespace nagcpp {
  namespace ut {
    // enum used only for specializing unit tests
    // for different storage orders
    enum SORDER { COL_MAJOR, ROW_MAJOR };

    // test value of the SORDER enum ...
    template <enum SORDER sorder>
    struct is_col_major : public std::false_type {};
    template <>
    struct is_col_major<SORDER::COL_MAJOR> : public std::true_type {};
    template <enum SORDER sorder>
    struct is_row_major : public std::false_type {};
    template <>
    struct is_row_major<SORDER::ROW_MAJOR> : public std::true_type {};
    // ... test value of the SORDER enum

    // convert is_col_major boolean into an integer
    template <enum ut::SORDER sorder>
    types::f77_integer sorder_flag(void) {
      return data_handling::set_sorder(ut::is_col_major<sorder>::value);
    }

    // enum used only for specializing unit tests
    // for internal vs non-internal types
    enum TYPE_IS { INTERNAL, GENERAL, CONST_DATA_POINTER, NO_RESIZE };

    // test value of the TYPE_IS enum ...
    template <enum TYPE_IS type_is>
    struct is_internal_type : public std::false_type {};
    template <>
    struct is_internal_type<TYPE_IS::INTERNAL> : public std::true_type {};
    template <enum TYPE_IS type_is>
    struct is_general_type : public std::false_type {};
    template <>
    struct is_general_type<TYPE_IS::GENERAL> : public std::true_type {};
    template <enum TYPE_IS type_is>
    struct is_const_data_pointer_type : public std::false_type {};
    template <>
    struct is_const_data_pointer_type<TYPE_IS::CONST_DATA_POINTER>
      : public std::true_type {};
    template <enum TYPE_IS type_is>
    struct is_no_resize_type : public std::false_type {};
    template <>
    struct is_no_resize_type<TYPE_IS::NO_RESIZE> : public std::true_type {};
    // ... test value of the TYPE_IS enum

    // test combinations of input / output and TYPE_IS ...
    template <enum data_handling::ArgIntent inout, TYPE_IS type_is>
    struct index_operator_lhs : public std::true_type {};
    template <>
    struct index_operator_lhs<data_handling::ArgIntent::IntentIN, TYPE_IS::CONST_DATA_POINTER>
      : public std::false_type {};

    template <enum data_handling::ArgIntent inout, TYPE_IS type_is>
    struct has_resize : public std::false_type {};
    template <>
    struct has_resize<data_handling::ArgIntent::IntentOUT, TYPE_IS::GENERAL>
      : public std::true_type {};
    template <>
    struct has_resize<data_handling::ArgIntent::IntentINOUT, TYPE_IS::GENERAL>
      : public std::true_type {};
    // ... test combinations of input / output and TYPE_IS

  }
}
#endif
