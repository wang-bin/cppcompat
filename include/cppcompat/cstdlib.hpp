/*
 * std c++ compat layer
 * Copyright (c) 2017-2023 WangBin <wbsecg1 at gmail.com>
 * https://github.com/wang-bin/cppcompat
 * MIT License
 */
#pragma once
#include "def.hpp"
#include <cstdlib> // _CRT_USE_WINAPI_FAMILY_DESKTOP_APP does not exist in 16299+.

// https://github.com/microsoft/STL/pull/2850
// uwp getenv declared in vcrt(> 202207L), definded in ucrt(2017-11-09). assume ucrt is not so ancient

#if defined(CPP_COMPAT_WINRT) && defined(_MSC_VER)
# if (_MSVC_STL_UPDATE + 0) <= 202207L // not defined or too old. _MSVC_STL_UPDATE is defined since _MSC_VER 1912(201709, VS 2017 15.5)
#   define CRT_HAS_GETENV_ 0
# else
#   define CRT_HAS_GETENV_ 1
# endif
#else
# define CRT_HAS_GETENV_ 1
#endif

#if !(CRT_HAS_GETENV_ + 0)
CPPCOMPAT_NS_STD_BEGIN
// no export for now
char* getenv(const char* env_var); // returned ptr is valid until getting the same env again in the same thread
CPPCOMPAT_NS_STD_END
#endif // !(CRT_HAS_GETENV_ + 0)