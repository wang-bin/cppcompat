/*
 * std c++ compat layer
 * Copyright (c) 2017 WangBin <wbsecg1 at gmail.com>
 * MIT License
 */
#pragma once
// CPP_COMPAT_STD: set by user to control which std is compatible with
#ifndef CPP_COMPAT_STD
# define CPP_COMPAT_STD 20
#endif
// use CPP_IS_STD instead of __cplusplus because __cplusplus is always 199711 in vc
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
# if (_MSVC_LANG+0) > 201402L // -std:c++17: 201703, -std:c++latest: 201704
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
// TODO: define __cpp_xxx(mostly for vc), e.g. __cpp_constexpr
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


/*
 * C99 __func__ macro
 */
#ifndef __func__
#  if (__STDC_VERSION__ >= 199901L)
     /* C99 */
#  elif defined(__SUNPRO_C) && defined(__C99FEATURES__)
     /* C99 */
#  elif defined(__GNUC__)
#    if __GNUC__ >= 2
#      define __func__ __FUNCTION__
#    else
#      define __func__ "<unknown>"
#    endif
#  elif defined(_MSC_VER)
#    if _MSC_VER >= 1300
#      define __func__ __FUNCTION__
#    else
#      define __func__ "<unknown>"
#    endif
#  else
#    define __func__ "<unknown>"
#  endif
#endif

#if defined(_MSC_VER) && _MSC_VER < 1900 // 1910 in gsl, partially support constexpr in vs2015. TODO: check clang/clang-cl?
# ifdef constexpr
#   define constexpr inline // constexpr implies inline
# endif
# define constexpr //inline // constexpr implies inline. but we can not declare a var as inline like constexpr
# ifndef noexcept
#   define noexcept //keyword, FIXME: operator?
# endif
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

