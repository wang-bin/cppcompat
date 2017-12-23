/*
 * std c++ compat layer
 * Copyright (c) 2017 WangBin <wbsecg1 at gmail.com>
 * MIT License
 */
#pragma once
#include "def.hpp"

#ifdef CPP_COMPAT_WINRT
namespace std {
// no export for now
char* getenv(const char* env_var); // returned ptr is invalid until get the same env again in the same thread
} // namespace std
#endif // CPP_COMPAT_WINRT