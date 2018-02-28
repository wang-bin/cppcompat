/*
 * std c++ compat layer
 * Copyright (c) 2017-2018 WangBin <wbsecg1 at gmail.com>
 * https://github.com/wang-bin/cppcompat
 * MIT License
 */
#pragma once
#include "def.hpp"
#include "type_traits.hpp"
#include <utility>

#if CPP_EMU_STD(17)
namespace std {
template <class T>
constexpr add_const_t<T>& as_const(T& t) noexcept { return t; }
} // namespace std
#endif // CPP_EMU_STD(17)
