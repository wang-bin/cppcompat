/*
 * std c++ compat layer
 * Copyright (c) 2017-2019 WangBin <wbsecg1 at gmail.com>
 * https://github.com/wang-bin/cppcompat
 * MIT License
 */
#pragma once
#include "def.hpp"
#include <cstdio> // ensure _GLIBCXX_CSTDIO is defined

#if defined(__BIONIC__) && !defined(_LIBCPP_ABI_VERSION) && !defined(_GLIBCXX_USE_C99)
CPPCOMPAT_NS_STD_BEGIN
    using ::fprintf;
    using ::printf;
    using ::snprintf;
    using ::vsnprintf;
CPPCOMPAT_NS_STD_END
#elif defined(_MSC_VER) && _MSC_VER < 1900
# include <utility>
// minimal support is vs2013. vs2012 does not support variadic template parameters
// TODO: _snprintf_s
CPPCOMPAT_NS_STD_BEGIN
    template<typename... Args> int snprintf(Args&&... args) { return _snprintf(std::forward<Args>(args)...);}
    template<typename... Args> int vsnprintf(Args&&... args) { return _vsnprintf(std::forward<Args>(args)...);}
CPPCOMPAT_NS_STD_END
#endif
