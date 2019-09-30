#ifndef NAGCPP_DATA_HANDLING_ARRAY_INFO_HPP
#define NAGCPP_DATA_HANDLING_ARRAY_INFO_HPP

#include "nagcpp_consts.hpp"
#include "nagcpp_engine_types.hpp"

namespace nagcpp {
  namespace data_handling {
    // the template <typename ST> is only here so that we can do things like
    // inline auto getDim2(M &m, int) -> array_info<decltype(m.size2())>
    // when implementing the functions that return the array_info, otherwise
    // the template could be removed from the class and just added in the
    // constructor
    template <typename ST>
    class array_info {
      // class to return meta information on an array
      // if set is false, then the information could not be ascertained
    public:
      bool set;
      types::f77_integer value;
      array_info(bool set_, ST ovalue)
        : set(set_), value(static_cast<types::f77_integer>(ovalue)) {}
      array_info(bool set_) : array_info(set_, 0) {}
      array_info(void) : array_info(false, 0) {}
      template <typename T>
      array_info<ST> &operator=(const array_info<T> &v) {
        set = v.set;
        value = v.value;
        return *this;
      }
      template <typename T>
      array_info<ST> &operator=(const T &v) {
        set = true;
        value = static_cast<types::f77_integer>(v);
        return *this;
      }

      // equal and not equal ...
      // these are written such that !(a == b) is not the same
      // as (a != b), in cases where one or more of them are not set
      // when one or more are not set the comparision always returns false
      template <typename T>
      bool operator!=(const array_info<T> &v) const {
        return (set && v.set && (value != v.value));
      }
      template <typename T>
      bool operator!=(const T &v) const {
        return (set && value != static_cast<types::f77_integer>(v));
      }
      template <typename T>
      bool operator==(const array_info<T> &v) const {
        return (set && v.set && (value == v.value));
      }
      template <typename T>
      bool operator==(const T &v) const {
        return (set && value == static_cast<types::f77_integer>(v));
      }
      // ... equal and not equal

      template <typename T>
      array_info<ST> &operator*=(const array_info<T> &v) {
        if (set && v.set) {
          value *= v.value;
        } else {
          set = false;
          value = 0;
        }
        return *this;
      }
      template <typename T>
      array_info<ST> &operator*=(const T &v) {
        if (set) {
          value *= static_cast<types::f77_integer>(v);
        }
        return *this;
      }

      template <typename T>
      bool operator>(const T &v) const noexcept {
        return (set && (value > static_cast<types::f77_integer>(v)));
      }
      template <typename T>
      bool operator>(const array_info<T> &v) const {
        return (set && v.set && (value > v.value));
      }
    };
  }
}

#endif
