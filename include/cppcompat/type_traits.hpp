/*
 * std c++ compat layer
 * Copyright (c) 2017-2018 WangBin <wbsecg1 at gmail.com>
 * https://github.com/wang-bin/cppcompat
 * MIT License
 */
#pragma once
#include "def.hpp"
#include <type_traits>

#if CPP_EMU_STD(14)
CPPCOMPAT_NS_STD_BEGIN
// const-volatile modifications:
template<typename T>
using remove_const_t = typename remove_const<T>::type;
template<typename T>
using remove_volatile_t = typename remove_volatile<T>::type;
template<typename T>
using remove_cv_t = typename remove_cv<T>::type;
template<typename T>
using add_const_t = typename add_const<T>::type;
template<typename T>
using add_volatile_t = typename add_volatile<T>::type;
template<typename T>
using add_cv_t = typename add_cv<T>::type;

// reference modifications:
template<typename T>
using remove_reference_t = typename remove_reference<T>::type;
template<typename T>
using add_lvalue_reference_t = typename add_lvalue_reference<T>::type;
template<typename T>
using add_rvalue_reference_t = typename add_rvalue_reference<T>::type;

// sign modifications:
template<typename T>
using make_signed_t = typename make_signed<T>::type;
template<typename T>
using make_unsigned_t = typename make_unsigned<T>::type;
// array modifications:
template<typename T>
using remove_extent_t = typename remove_extent<T>::type;
template<typename T>
using remove_all_extents_t = typename remove_all_extents<T>::type;

// pointer modifications:
template<typename T>
using remove_pointer_t = typename remove_pointer<T>::type;
template<typename T>
using add_pointer_t = typename add_pointer<T>::type;

// other transformations:
template <size_t Len, std::size_t Align=alignment_of<typename aligned_storage<Len>::type>::value>
using aligned_storage_t = typename aligned_storage<Len,Align>::type;
template <std::size_t Len, class... Types>
using aligned_union_t = typename aligned_union<Len,Types...>::type;
template<typename T>
using decay_t = typename decay<T>::type;
template <bool b, class T=void>
using enable_if_t = typename enable_if<b,T>::type;
template <bool b, class T, class F>
using conditional_t = typename conditional<b,T,F>::type;
template<typename... T>
using common_type_t = typename common_type<T...>::type;
template<typename T>
using underlying_type_t = typename underlying_type<T>::type;
template<typename T>
using result_of_t = typename result_of<T>::type;
//template<typename Fn, class... ArgTypes> using invoke_result_t = typename invoke_result<Fn, ArgTypes...>::type
CPPCOMPAT_NS_STD_END
#endif //CPP_EMU_STD(14)


#if CPP_EMU_STD(17)
CPPCOMPAT_NS_STD_BEGIN
# if (__GNUC__+0) < 5 && !defined __clang__
// http://stackoverflow.com/a/28967049/1353549
template <typename...>
struct make_void { using type = void; };
template <typename...Ts>
using void_t = typename make_void<Ts...>::type;
# else
template <typename...>
using void_t = void;
# endif
CPPCOMPAT_NS_STD_END
#endif // CPP_EMU_STD(17)

#if CPP_EMU_STD_IN(17, 14) // variable templates requires C++14. inline variables require c++17 which we are emulating, so no inline
CPPCOMPAT_NS_STD_BEGIN
# if !defined(__cpp_lib_type_trait_variable_templates)/*vc*/ && !defined(__cpp_variable_templates) /*clang,gnu*/
#  define CPPCOMPAT_VAR_TMPL 1
# endif
#if (CPPCOMPAT_VAR_TMPL+0)
// See C++14 20.10.4.1, primary type categories
template<typename T>
constexpr bool is_void_v = is_void<T>::value;
template<typename T>
constexpr bool is_null_pointer_v = is_null_pointer<T>::value;
template<typename T>
constexpr bool is_integral_v = is_integral<T>::value;
template<typename T>
constexpr bool is_floating_point_v = is_floating_point<T>::value;
template<typename T>
constexpr bool is_array_v = is_array<T>::value;
template<typename T>
constexpr bool is_pointer_v = is_pointer<T>::value;
template<typename T>
constexpr bool is_lvalue_reference_v = is_lvalue_reference<T>::value;
template<typename T>
constexpr bool is_rvalue_reference_v = is_rvalue_reference<T>::value;
template<typename T>
constexpr bool is_member_object_pointer_v = is_member_object_pointer<T>::value;
template<typename T>
constexpr bool is_member_function_pointer_v = is_member_function_pointer<T>::value;
template<typename T>
constexpr bool is_enum_v = is_enum<T>::value;
template<typename T>
constexpr bool is_union_v = is_union<T>::value;
template<typename T>
constexpr bool is_class_v = is_class<T>::value;
template<typename T>
constexpr bool is_function_v = is_function<T>::value;

// See C++14 20.10.4.2, composite type categories
template<typename T> constexpr bool is_reference_v = is_reference<T>::value;
template<typename T> constexpr bool is_arithmetic_v = is_arithmetic<T>::value;
template<typename T> constexpr bool is_fundamental_v = is_fundamental<T>::value;
template<typename T> constexpr bool is_object_v = is_object<T>::value;
template<typename T> constexpr bool is_scalar_v = is_scalar<T>::value;
template<typename T> constexpr bool is_compound_v = is_compound<T>::value;
template<typename T> constexpr bool is_member_pointer_v = is_member_pointer<T>::value;

// See C++14 20.10.4.3, type properties
template<typename T> constexpr bool is_const_v = is_const<T>::value;
template<typename T> constexpr bool is_volatile_v = is_volatile<T>::value;
template<typename T> constexpr bool is_trivial_v = is_trivial<T>::value;
template<typename T> constexpr bool is_trivially_copyable_v = is_trivially_copyable<T>::value;
template<typename T> constexpr bool is_standard_layout_v = is_standard_layout<T>::value;
template<typename T> constexpr bool is_pod_v = is_pod<T>::value;
template<typename T> constexpr bool is_literal_type_v = is_literal_type<T>::value;
template<typename T> constexpr bool is_empty_v = is_empty<T>::value;
template<typename T> constexpr bool is_polymorphic_v = is_polymorphic<T>::value;
template<typename T> constexpr bool is_abstract_v = is_abstract<T>::value;
template<typename T> constexpr bool is_final_v = is_final<T>::value;
//template<typename T> constexpr bool is_aggregate_v = is_aggregate<T>::value;
template<typename T> constexpr bool is_signed_v = is_signed<T>::value;
template<typename T> constexpr bool is_unsigned_v = is_unsigned<T>::value;
template<typename T, class... Args> constexpr bool is_constructible_v = is_constructible<T, Args...>::value;
template<typename T> constexpr bool is_default_constructible_v = is_default_constructible<T>::value;
template<typename T> constexpr bool is_copy_constructible_v = is_copy_constructible<T>::value;
template<typename T> constexpr bool is_move_constructible_v = is_move_constructible<T>::value;
template<typename T, class U> constexpr bool is_assignable_v = is_assignable<T, U>::value;
template<typename T> constexpr bool is_copy_assignable_v = is_copy_assignable<T>::value;
template<typename T> constexpr bool is_move_assignable_v = is_move_assignable<T>::value;
//template<typename T, class U> constexpr bool is_swappable_with_v = is_swappable_with<T, U>::value;

//template<typename T> constexpr bool is_swappable_v = is_swappable<T>::value;
template<typename T> constexpr bool is_destructible_v = is_destructible<T>::value;
template<typename T, class... Args> constexpr bool is_trivially_constructible_v = is_trivially_constructible<T, Args...>::value;
template<typename T> constexpr bool is_trivially_default_constructible_v = is_trivially_default_constructible<T>::value;
template<typename T> constexpr bool is_trivially_copy_constructible_v = is_trivially_copy_constructible<T>::value;
template<typename T> constexpr bool is_trivially_move_constructible_v = is_trivially_move_constructible<T>::value;
template<typename T, class U> constexpr bool is_trivially_assignable_v = is_trivially_assignable<T, U>::value;
template<typename T> constexpr bool is_trivially_copy_assignable_v = is_trivially_copy_assignable<T>::value;
template<typename T> constexpr bool is_trivially_move_assignable_v = is_trivially_move_assignable<T>::value;
template<typename T> constexpr bool is_trivially_destructible_v = is_trivially_destructible<T>::value;
template<typename T, class... Args> constexpr bool is_nothrow_constructible_v = is_nothrow_constructible<T, Args...>::value;
template<typename T> constexpr bool is_nothrow_default_constructible_v = is_nothrow_default_constructible<T>::value;
template<typename T> constexpr bool is_nothrow_copy_constructible_v = is_nothrow_copy_constructible<T>::value;
template<typename T> constexpr bool is_nothrow_move_constructible_v = is_nothrow_move_constructible<T>::value;
template<typename T, class U> constexpr bool is_nothrow_assignable_v = is_nothrow_assignable<T, U>::value;
template<typename T> constexpr bool is_nothrow_copy_assignable_v = is_nothrow_copy_assignable<T>::value;
template<typename T> constexpr bool is_nothrow_move_assignable_v = is_nothrow_move_assignable<T>::value;
//template<typename T, class U> constexpr bool is_nothrow_swappable_with_v = is_nothrow_swappable_with<T, U>::value;
//template<typename T> constexpr bool is_nothrow_swappable_v = is_nothrow_swappable<T>::value;
template<typename T> constexpr bool is_nothrow_destructible_v = is_nothrow_destructible<T>::value;
template<typename T> constexpr bool has_virtual_destructor_v = has_virtual_destructor<T>::value;
//template<class T> constexpr bool has_unique_object_representations_v = has_unique_object_representations<T>::value;

// See C++14 20.10.5, type property queries
template<typename T> constexpr size_t alignment_of_v = alignment_of<T>::value;
template<typename T> constexpr size_t rank_v = rank<T>::value;
template<typename T, unsigned I = 0> constexpr size_t extent_v = extent<T, I>::value;

// See C++14 20.10.6, type relations
template<typename T, class U> constexpr bool is_same_v = is_same<T, U>::value;
template<typename Base, class Derived> constexpr bool is_base_of_v = is_base_of<Base, Derived>::value;
template<typename From, class To> constexpr bool is_convertible_v = is_convertible<From, To>::value;
#if 0 // c++17 structures
template<typename Fn, class... ArgTypes> constexpr bool is_invocable_v = is_invocable<Fn, ArgTypes...>::value;
template<typename R, class Fn, class... ArgTypes> constexpr bool is_invocable_r_v = is_invocable_r<R, Fn, ArgTypes...>::value;
template<typename Fn, class... ArgTypes> constexpr bool is_nothrow_invocable_v = is_nothrow_invocable<Fn, ArgTypes...>::value;
template<typename R, class Fn, class... ArgTypes> constexpr bool is_nothrow_invocable_r_v = is_nothrow_invocable_r<R, Fn, ArgTypes...>::value;

// [meta.logical], logical operator traits:
template<class... B> struct conjunction
template<class... B>
constexpr bool conjunction_v = conjunction<B...>::value;
template<class... B> struct disjunction
template<class... B>
constexpr bool disjunction_v = disjunction<B...>::value;
template<class B> struct negation
template<class B>
constexpr bool negation_v = negation<B>::value;
#endif
# endif // (CPPCOMPAT_VAR_TMPL+0)
CPPCOMPAT_NS_STD_END
#endif // CPP_EMU_STD_IN(17, 14)

#if CPP_EMU_STD(20)
CPPCOMPAT_NS_STD_BEGIN
template<typename T>
struct remove_cvref {
    typedef remove_cv_t<remove_reference_t<T>> type;
};
template<typename T>
using remove_cvref_t = typename remove_cvref<T>::type;
CPPCOMPAT_NS_STD_END
#endif // CPP_EMU_STD(20)