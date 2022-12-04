/*
 * std c++ compat layer
 * Copyright (c) 2017-2022 WangBin <wbsecg1 at gmail.com>
 * https://github.com/wang-bin/cppcompat
 * MIT License
 */
#pragma once
#include "def.hpp"
#include <cstdlib> // _CRT_USE_WINAPI_FAMILY_DESKTOP_APP does not exist in 16299+.

#if defined(CPP_COMPAT_WINRT) && !defined(WINRT_HAS_GETENV)
CPPCOMPAT_NS_STD_BEGIN
// no export for now
char* getenv(const char* env_var); // returned ptr is valid until getting the same env again in the same thread
CPPCOMPAT_NS_STD_END
#endif // defined(CPP_COMPAT_WINRT) && !defined(WINRT_HAS_GETENV)