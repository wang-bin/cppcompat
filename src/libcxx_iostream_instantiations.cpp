/*
 * std c++ compat layer
 * Copyright (c) 2024 WangBin <wbsecg1 at gmail.com>
 * MIT License
 *
 * explicit instantiation of iostream, broken in libc++18
 */
#include <fstream>
#include <sstream>

#if (_LIBCPP_VERSION + 0) >= 180000 && (CPPCOMPAT_LIBCXX_MIN + 0) < 18
#if _LIBCPP_STD_VER <= 17 || defined(_LIBCPP_BUILDING_LIBRARY)
#error _LIBCPP_STD_VER
#endif
// MUST build user code with c++20 or later if cppcompat is built with c++20+, basic_ostringstream.str() in libc++18 is not inline in c++17.
template class std::basic_stringbuf<char>;
template class std::basic_stringstream<char>;
template class std::basic_ostringstream<char>;
template class std::basic_istringstream<char>;

# ifndef _LIBCPP_HAS_NO_FILESYSTEM
template class std::basic_ifstream<char>;
template class std::basic_ofstream<char>;
template class std::basic_filebuf<char>;
# endif
#endif
