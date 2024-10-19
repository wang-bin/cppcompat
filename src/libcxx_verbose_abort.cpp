/*
 * std c++ compat layer
 * Copyright (c) 2024 WangBin <wbsecg1 at gmail.com>
 * MIT License
 */
#include <stdexcept>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
//#include <version> // must include any libc++ header before defining the function (C compatibility headers excluded)
// no side effect if not building for libc++
#if !defined(_LIBCPP_HAS_NO_VERBOSE_ABORT_IN_LIBRARY) /*libc++17*/ \
    || ((_LIBCPP_AVAILABILITY_HAS_VERBOSE_ABORT + 0)/*libc++18*/ && !(__APPLE__ + 0))
# if (_LIBCPP_VERSION + 0) >= 170000 && (CPPCOMPAT_LIBCPP_MIN + 0) < 13
#   define CPPCOMPAT_VERBOSE_ABORT
# endif
#endif

#ifdef CPPCOMPAT_VERBOSE_ABORT
// noexcept since libc++20
void std::__libcpp_verbose_abort(char const* format, ...) noexcept(noexcept(std::__libcpp_verbose_abort(""))) {
    va_list list;
    va_start(list, format);
    std::vfprintf(stderr, format, list);
    va_end(list);

    std::abort();
}
#endif