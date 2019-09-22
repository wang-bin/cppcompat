/*
 * std c++ compat layer
 * Copyright (c) 2017-2019 WangBin <wbsecg1 at gmail.com>
 * https://github.com/wang-bin/cppcompat
 * MIT License
 */
#pragma once

// c++20 <version>(libc++, msvc only now) // http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2018/p0754r2.pdf
#if defined(__has_include)/*c++17*/ && __has_include(<version>)
# include <version>
#else
# if (__GNUC__+0) && !defined(__clang__)
#   include <bits/c++config.h> // included in gcc6.1+ ciso646. https://en.cppreference.com/w/cpp/header/ciso646
# else
#   include <ciso646> // to include yvals.h(vc), __config(libc++), bits/c++config.h(gnu) to get defination of std namespace. cstdbool is deprecated in c++17
# endif
#endif

// CPP_COMPAT_STD: set by user to control which std is compatible with
#ifndef CPP_COMPAT_STD
# define CPP_COMPAT_STD 20
#endif
// use CPP_IS_STD instead of __cplusplus because __cplusplus is always 199711 in vc (vs15.7+ can fix it by /Zc:__cplusplus)
#if __cplusplus >= 201707L
# define CPP_IS_STD 20
#elif __cplusplus >= 201703L
# define CPP_IS_STD 17
#elif __cplusplus >= 201402L
# define CPP_IS_STD 14
#elif __cplusplus >= 201103L
# define CPP_IS_STD 11
#else
// vc140(vs2015) defines _HAVE_CXX17 (_MSVC_LANG>201402) in yvals.h. _MSVC_LANG is defined since cl 19.00(what about clang/clang-cl? added in e71aa18)
# if (_MSVC_LANG+0) > 201703L
#   define CPP_IS_STD 20
# elif (_MSVC_LANG+0) > 201402L // -std:c++17: 201703, -std:c++latest: 201704
#   define CPP_IS_STD 17
# elif (_MSVC_LANG+0) >= 201402L // since vs2015update3  -std:c++14: 201402
#   define CPP_IS_STD 14
# elif (_MSC_VER+0) >= 1900 // vs2015 < update3
#   define CPP_IS_STD 14
# elif (_MSC_VER+0) >= 1800 // vs2013, no _MSVC_LANG
#   define CPP_IS_STD 11
# else
#   define CPP_IS_STD 03
# endif
#endif
// CPP_EMU_STD(X): emulate std version X if current version is older and requested version is at least X
#define CPP_EMU_STD(X) ((CPP_IS_STD < X) && (CPP_COMPAT_STD >= X))
// CPP_EMU_STD_IN(X, Y): emulate std X in std Y. Y is required
#define CPP_EMU_STD_IN(X, Y) ((CPP_IS_STD < X && CPP_IS_STD >= Y) && (CPP_COMPAT_STD >= X))

// macros, pp, keywords
// TODO: define __cpp_xxx(mostly for vc), e.g. __cpp_constexpr. move into version.hpp
/*
#define __cpp_alias_templates 200704
#define __cpp_attributes 200809
#define __cpp_constexpr 200704
#define __cpp_decltype 200707
#define __cpp_delegating_constructors 200604
#define __cpp_exceptions 199711
#define __cpp_inheriting_constructors 201511
#define __cpp_initializer_lists 200806
#define __cpp_lambdas 200907
#define __cpp_nsdmi 200809
#define __cpp_range_based_for 200907
#define __cpp_raw_strings 200710
#define __cpp_ref_qualifiers 200710
#define __cpp_rtti 199711
#define __cpp_rvalue_references 200610
#define __cpp_static_assert 200410
#define __cpp_unicode_characters 200704
#define __cpp_unicode_literals 200710
#define __cpp_user_defined_literals 200809
#define __cpp_variadic_templates 200704
*/
// gsl/gsl_util pop_macro("noexcept")


// C99 __func__ macro
#if (__STDC_VERSION__ >= 199901L)
#elif defined(__SUNPRO_C) && defined(__C99FEATURES__)
#elif defined(__clang__) // clang-cl defines __func__
#elif (__GNUC__+0) >= 2 || (_MSC_VER+0) >= 1300
#  define __func__ __FUNCTION__
#else
#  define __func__ "<unknown>"
#endif

#if defined(_MSC_VER) && !defined(__clang__) && _MSC_VER < 1900 // 1910 in gsl, partially support constexpr in vs2015
# ifdef constexpr
#   undef constexpr
# endif
# define constexpr //inline // constexpr implies inline. but we can not declare a var as inline like constexpr
# ifndef noexcept
#   define noexcept //keyword, FIXME: operator?
# endif
// aligment specifier
# define alignas(N) __declspec(align(N)) // gcc4.8 clang3.0 vc19. 
# define alignof(T) __alignof(T) // gcc4.5 clang2.9 vc19. std::alignment_of<T>::value is available in vc18
#endif //defined(_MSC_VER) && _MSC_VER < 1900


#if CPP_IS_STD < 17
# define constexpr17
#else
# define constexpr17 constexpr
#endif

#ifdef WINAPI_FAMILY
# include <winapifamily.h>
# if !WINAPI_FAMILY_PARTITION(WINAPI_PARTITION_DESKTOP)
#  define CPP_COMPAT_WINRT 1
# endif
#endif //WINAPI_FAMILY

#ifdef _MSC_VER // check vcrt version instead of _MSC_VER, because stl is defined in crt, and clang supports different combinations of msc version + crt
# include <crtversion.h>
#endif

// namespace macros are defined <version>, <bits/c++config.h>yvals.h(vc), __config(libc++)
#if defined(_LIBCPP_END_NAMESPACE_STD) // libc++, already defined as inline namespace
#define CPPCOMPAT_NS_STD_BEGIN _LIBCPP_BEGIN_NAMESPACE_STD
#define CPPCOMPAT_NS_STD_END _LIBCPP_END_NAMESPACE_STD
#elif defined(_GLIBCXX_BEGIN_NAMESPACE_VERSION) // gnu stl, inline namespace declaration in c++config.h
#define CPPCOMPAT_NS_STD_BEGIN namespace std { _GLIBCXX_BEGIN_NAMESPACE_VERSION
#define CPPCOMPAT_NS_STD_END _GLIBCXX_END_NAMESPACE_VERSION }
#elif defined(_STD_BEGIN) // vc
#define CPPCOMPAT_NS_STD_BEGIN _STD_BEGIN
#define CPPCOMPAT_NS_STD_END _STD_END
#else
#define CPPCOMPAT_NS_STD_BEGIN namespace std {
#define CPPCOMPAT_NS_STD_END }
#endif

