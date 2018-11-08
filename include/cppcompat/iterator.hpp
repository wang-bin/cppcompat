/*
 * std c++ compat layer
 * Copyright (c) 2017-2018 WangBin <wbsecg1 at gmail.com>
 * https://github.com/wang-bin/cppcompat
 * MIT License
 */
#pragma once
#include "def.hpp"
#include <iterator>

#if CPP_EMU_STD(14)
# if !defined(_VC_CRT_MAJOR_VERSION) || (_VC_CRT_MAJOR_VERSION < 12)
CPPCOMPAT_NS_STD_BEGIN
//std::cbegin,cend,rbegin,rend,crbegin,crend
template<class C>
constexpr17 auto cbegin(const C& c) /*noexcep(noexcept(std::begin(c)))*/
    ->decltype(std::begin(c))
{
    return std::begin(c);
}
template<class C>
constexpr17 auto cend(const C& c) /*noexcep(noexcept(std::end(c)))*/
    ->decltype(std::end(c))
{
    return std::end(c);
}
CPPCOMPAT_NS_STD_END
# endif //!defined(_MSC_VER) || (_VC_CRT_MAJOR_VERSION < 12)
#endif // CPP_EMU_STD(14)

#if CPP_EMU_STD(17)
# if !defined(_VC_CRT_MAJOR_VERSION) || (_VC_CRT_MAJOR_VERSION < 14) || defined(_LIBCPP_VERSION)
CPPCOMPAT_NS_STD_BEGIN
template<class C>
constexpr auto size(const C& c) -> decltype(c.size())
{
    return c.size();
}

template<class T, std::size_t N>
constexpr std::size_t size(const T (&array)[N]) noexcept
{
    return N;
}
CPPCOMPAT_NS_STD_END
# endif
#endif // CPP_EMU_STD(17)

