/*
 * std c++ compat layer
 * Copyright (c) 2017 WangBin <wbsecg1 at gmail.com>
 * MIT License
 */
#pragma once
#include "def.hpp"
#include <iterator>

#if CPP_EMU_STD(14)
namespace std {
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
} // namespace std
#endif // CPP_EMU_STD(14)

#if CPP_EMU_STD(17)
# ifdef _MSC_VER // check vcrt version instead of _MSC_VER, because stl is defined in crt, and clang supports different combinations of msc version + crt 
#   include <crtversion.h>
# endif
# if !defined(_MSC_VER) || (_VC_CRT_MAJOR_VERSION < 14)
namespace std {
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
} // namespace std
# endif
#endif // CPP_EMU_STD(17)

