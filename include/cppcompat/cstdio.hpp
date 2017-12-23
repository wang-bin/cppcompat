/*
 * std c++ compat layer
 * Copyright (c) 2017 WangBin <wbsecg1 at gmail.com>
 * MIT License
 */
#pragma once
#include "def.hpp"
#include <cstdio> // ensure _GLIBCXX_CSTDIO is defined

#if (defined(__ANDROID__) || defined(ANDROID)) && !defined(__clang__) && !defined(_GLIBCXX_USE_C99)
namespace std {
    using ::fprintf;
    using ::printf;
    using ::snprintf;
    using ::vsnprintf;
}
#elif defined(_MSC_VER) && _MSC_VER < 1900
# include <utility>
// minimal support is vs2013. vs2012 does not support variadic template parameters
namespace std {
    template<typename... Args> int snprintf(Args&&... args) { return _snprintf(std::forward<Args>(args)...);}
    template<typename... Args> int vsnprintf(Args&&... args) { return _vsnprintf(std::forward<Args>(args)...);}
}
#endif
