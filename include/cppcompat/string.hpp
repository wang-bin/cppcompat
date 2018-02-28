/*
 * std c++ compat layer
 * Copyright (c) 2017-2018 WangBin <wbsecg1 at gmail.com>
 * https://github.com/wang-bin/cppcompat
 * MIT License
 */
#pragma once
#include "def.hpp"
#include <cstdlib> // strtol
#include <string>

#if defined(__ANDROID__) || defined(ANDROID)
#if defined(_GLIBCXX_STRING) && !defined(_GLIBCXX_USE_C99)
#include <sstream>
template<typename To> struct cast_to {
    template<typename From>
    static To from(const From& x) {
        std::stringstream s;
        To v;
        if ((s << x).fail() || (s >> v).fail()) {
            return v;
        }
        return v;
    }
    static To from(const To& x) { return x;}
};

template<>
struct cast_to<std::string> {
    template<typename From>
    static std::string from(const From& x) {
        std::stringstream s;
        if ((s << x).fail()) {
            return std::string();
        }
        return s.str();
    }
    static std::string from(const std::string& x) { return x;}
};

namespace std {
template<typename T>
inline string to_string(T t) {
    return cast_to<std::string>::from(t);
}

static inline int stoi(const std::string& str, std::size_t* pos = nullptr, int base = 10) {
    char* s_end = nullptr;
    auto v = std::strtol(str.c_str(), &s_end, base);
    if (pos)
        *pos = s_end - str.c_str();
    return v;
}
} //namespace std
#endif // !defined(__clang__) && !defined(_GLIBCXX_USE_C99)
#endif //defined(__ANDROID__) || defined(ANDROID)