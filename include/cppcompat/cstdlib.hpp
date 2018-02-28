/*
 * std c++ compat layer
 * Copyright (c) 2017-2018 WangBin <wbsecg1 at gmail.com>
 * https://github.com/wang-bin/cppcompat
 * MIT License
 */
#pragma once
#include "def.hpp"
#include <cstdlib>

#ifdef CPP_COMPAT_WINRT
namespace std {
// no export for now
char* getenv(const char* env_var); // returned ptr is valid until getting the same env again in the same thread
} // namespace std
#endif // CPP_COMPAT_WINRT