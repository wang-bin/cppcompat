/*
 * std c++ compat layer
 * Copyright (c) 2025 WangBin <wbsecg1 at gmail.com>
 * MIT License
 */
#include <functional>

// libc++21
#if (_LIBCPP_AVAILABILITY_HAS_HASH_MEMORY + 0)
size_t std::__hash_memory(_LIBCPP_NOESCAPE const void* ptr, size_t size) noexcept {
  return __murmur2_or_cityhash<size_t>()(ptr, size);
}
#endif
