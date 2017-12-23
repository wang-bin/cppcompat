/*
 * std c++ compat layer
 * Copyright (c) 2017 WangBin <wbsecg1 at gmail.com>
 * MIT License
 */
#pragma once
#include "def.hpp"
#include "type_traits.hpp"

#if CPP_EMU_STD(17)
namespace std {
template <class T>
constexpr add_const_t<T>& as_const(T& t) noexcept { return t; }
} // namespace std
#endif // CPP_EMU_STD(17)
