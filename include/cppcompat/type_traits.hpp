/*
 * std c++ compat layer
 * Copyright (c) 2017 WangBin <wbsecg1 at gmail.com>
 * MIT License
 */
#pragma once
#include "def.hpp"
#include <type_traits>

#if CPP_EMU_STD(14)
namespace std {
// c++14 helper types
template<bool B, class T = void>
using enable_if_t = typename enable_if<B,T>::type;
template<typename T>
using add_cv_t       = typename add_cv<T>::type;
template<typename T>
using add_const_t    = typename add_const<T>::type;
template<typename T>
using add_volatile_t = typename add_volatile<T>::type;
template<typename T>
using add_lvalue_reference_t = typename add_lvalue_reference<T>::type;
template<typename T>
using add_rvalue_reference_t = typename add_rvalue_reference<T>::type;
template<typename T>
using remove_cv_t       = typename remove_cv<T>::type;
template<typename T>
using remove_const_t    = typename remove_const<T>::type;
template<typename T>
using remove_volatile_t = typename remove_volatile<T>::type;
template<typename T>
using remove_reference_t = typename remove_reference<T>::type;
} // namespace std
#endif //CPP_EMU_STD(14)


#if CPP_EMU_STD_IN(17, 14)
namespace std {
template<typename T> // inline
constexpr bool is_const_v = is_const<T>::value; // inline var: c++17
} // namespace std
#endif // CPP_EMU_STD_IN(17, 14)

#if CPP_EMU_STD(17)
namespace std {
# if __GNUC__ < 5 && !defined __clang__
// http://stackoverflow.com/a/28967049/1353549
template <typename...>
struct make_void { using type = void; };
template <typename...Ts>
using void_t = typename make_void<Ts...>::type;
# else
template <typename...>
using void_t = void;
# endif
} // namespace std
#endif // CPP_EMU_STD(17)

#if CPP_EMU_STD(20)
namespace std {
template<typename T>
struct remove_cvref {
    typedef remove_cv_t<remove_reference_t<T>> type;
};
template<typename T>
using remove_cvref_t = typename remove_cvref<T>::type;
}
#endif // CPP_EMU_STD(20)