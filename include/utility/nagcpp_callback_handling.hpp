#ifndef NAGCPP_CALLBACK_HANDLING_HPP
#define NAGCPP_CALLBACK_HANDLING_HPP

#include <functional>

namespace nagcpp {
  namespace callback_handling {
    // series of utility routines used by wrappers to
    // handle callbacks

    namespace internal {
      template <typename... Args>
      struct identity {};

      template <typename Function>
      struct unwrap_function_impl;

      template <typename _RTy, typename... _ATy>
      struct unwrap_function_impl<_RTy(_ATy...)> {
        typedef _RTy return_type;
        typedef identity<_ATy...> argument_type;
        typedef std::function<_RTy(_ATy...)> function_type;
        typedef _RTy (*function_ptr)(_ATy...);
      };

      // allow std::nullptr to be passed instead of a callback
      template <>
      struct unwrap_function_impl<std::nullptr_t> {
        typedef std::nullptr_t return_type;
        typedef std::nullptr_t argument_type;
        typedef std::nullptr_t function_type;
      };

      // lambdas
      template <typename Function>
      struct unwrap_function_impl
        : public unwrap_function_impl<decltype(&Function::operator())> {};

      // std::function
      template <typename _RTy, typename... _ATy>
      struct unwrap_function_impl<std::function<_RTy(_ATy...)>>
        : public unwrap_function_impl<_RTy(_ATy...)> {};
      template <typename _RTy, typename... _ATy>
      struct unwrap_function_impl<std::function<_RTy(_ATy...)> const>
        : public unwrap_function_impl<_RTy(_ATy...)> {};

      // std::tuple
      template <typename _RTy, typename... _ATy>
      struct unwrap_function_impl<std::tuple<_RTy, _ATy...>>
        : public unwrap_function_impl<_RTy(_ATy...)> {};
      template <typename _RTy, typename... _ATy>
      struct unwrap_function_impl<std::tuple<_RTy, _ATy...> const>
        : public unwrap_function_impl<_RTy(_ATy...)> {};

      // function pointers
      template <typename _RTy, typename... _ATy>
      struct unwrap_function_impl<_RTy (*)(_ATy...)>
        : public unwrap_function_impl<_RTy(_ATy...)> {};

      // class method pointers
      template <typename _CTy, typename _RTy, typename... _ATy>
      struct unwrap_function_impl<_RTy (_CTy::*)(_ATy...)>
        : public unwrap_function_impl<_RTy(_ATy...)> {};
      template <typename _CTy, typename _RTy, typename... _ATy>
      struct unwrap_function_impl<_RTy (_CTy::*)(_ATy...) const>
        : public unwrap_function_impl<_RTy(_ATy...)> {};

      // pack in identity
      template <typename _RTy, typename... _ATy>
      struct unwrap_function_impl<identity<_RTy, _ATy...>>
        : public unwrap_function_impl<_RTy(_ATy...)> {};

      // unwrap through pointer of functor.
      template <typename Function>
      static auto select_best_unwrap_unary_arg(int)
        -> unwrap_function_impl<decltype(&Function::operator())>;

      // unwrap through plain type.
      template <typename Function>
      static auto select_best_unwrap_unary_arg(long)
        -> unwrap_function_impl<Function>;

      template <typename... _FTy>
      struct select_best_unwrap;

      // enable only if 1 template argument is given
      template <typename _FTy>
      struct select_best_unwrap<_FTy> {
        typedef decltype(select_best_unwrap_unary_arg<_FTy>(0)) type;
      };

      template <typename _FTy, typename... _FTargs>
      struct select_best_unwrap<std::function<_FTy(_FTargs...)>> {
        typedef unwrap_function_impl<std::function<_FTy(_FTargs...)>> type;
      };

      template <typename... Function>
      using unwrap_function = typename select_best_unwrap<Function...>::type;

      // extract i-th argument type ...
      template <size_t i, typename T>
      struct get_argument_type;

      template <size_t i>
      struct get_argument_type<i, std::nullptr_t> {
        static const size_t nargs = 0;
        typedef std::nullptr_t type;
      };

      template <size_t i, typename... Args>
      struct get_argument_type<i, identity<Args...>> {
        static const size_t nargs = sizeof...(Args);
        typedef typename std::tuple_element<i, std::tuple<Args...>>::type type;
      };
      // ... extract i-th argument type
    }

    // trait which defines the return type of the function
    template <typename... Function>
    using return_type_of_t =
      typename internal::select_best_unwrap<Function...>::type::return_type;

    // trait which defines the argument types of the function
    template <typename... Function>
    using argument_type_of_t =
      typename internal::select_best_unwrap<Function...>::type::argument_type;

    // trait which defines the std::function type of the function
    template <typename... Function>
    using function_type_of_t =
      typename internal::select_best_unwrap<Function...>::type::function_type;

    // trait which defines the function pointer type of the function
    template <typename... Function>
    using function_ptr_of_t =
      typename internal::select_best_unwrap<Function...>::type::function_ptr;

    // extract i-th argument type
    template <size_t i, typename... Args>
    using get_argument_type_t =
      typename internal::get_argument_type<i, Args...>::type;

    // get void * pointer to address of a callback
    template <typename CB>
    inline void *function_to_void_pointer(CB &f) {
      return static_cast<void *>(std::addressof(f));
    }
    // XXXX is this always portable??
    template <typename CB>
    inline void *function_to_void_pointer(CB *f) {
      return (void *) f;
    }
    template <>
    inline void *function_to_void_pointer(std::nullptr_t &f) {
      return static_cast<void *>(nullptr);
    }
  }
}
#endif
