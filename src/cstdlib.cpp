/*
 * std c++ compat layer
 * Copyright (c) 2017-2018 WangBin <wbsecg1 at gmail.com>
 * MIT License
 */
#include "cppcompat/cstdlib.hpp"

#ifdef CPP_COMPAT_WINRT
#include <windows.h>
#include <memory>
#include <unordered_map>
CPPCOMPAT_NS_STD_BEGIN
char* getenv(const char* env_var) {
    DWORD len = GetEnvironmentVariableA(env_var, nullptr, 0); // length including terminating '\0'
    if (len <= 0) // == 0
        return nullptr;
    std::shared_ptr<char> val(new char[len], std::default_delete<char[]>());
    GetEnvironmentVariableA(env_var, val.get(), len);
    thread_local std::unordered_map<const char*, std::shared_ptr<char>> envs;
    envs[env_var] = val; // old value memory is destroyed
    return val.get();
}
CPPCOMPAT_NS_STD_END
#endif // CPP_COMPAT_WINRT
