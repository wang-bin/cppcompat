/*
 * std c++ compat layer
 * Copyright (c) 2017-2019 WangBin <wbsecg1 at gmail.com>
 * https://github.com/wang-bin/cppcompat
 * MIT License
 */
#pragma once
#include "def.hpp"
#include "type_traits.hpp"
#include <utility>

CPPCOMPAT_NS_STD_BEGIN
#if CPP_EMU_STD(14)
template <class _Tp, bool = is_enum<_Tp>::value>
struct  __enum_hash : public unary_function<_Tp, size_t>
{
    size_t operator()(_Tp __v) const noexcept
    {
        typedef typename underlying_type<_Tp>::type type;
        return hash<type>{}(static_cast<type>(__v));
    }
};
template <class _Tp>
struct  __enum_hash<_Tp, false> {
    __enum_hash() = delete;
    __enum_hash(__enum_hash const&) = delete;
    __enum_hash& operator=(__enum_hash const&) = delete;
};

template <class _Tp>
struct hash : public __enum_hash<_Tp>
{
};
#endif // CPP_EMU_STD(14)

#if CPP_EMU_STD(17)
# if !defined(_VC_CRT_MAJOR_VERSION) || (_VC_CRT_MAJOR_VERSION < 14)
// implemented in vcrt 140 unconditionally
template <class T>
constexpr add_const_t<T>& as_const(T& t) noexcept { return t; }
# endif
#endif // CPP_EMU_STD(17)
//} // namespace std
CPPCOMPAT_NS_STD_END