cmake_minimum_required(VERSION 3.15)

project(cppcompat VERSION 0.0.1 DESCRIPTION "c++ compatibility library" LANGUAGES CXX)
set(PROJECT_VERSION_TWEAK 0)

option(CPPCOMPAT_LIBCXX_MIN "min compatible libc++ version" 3)

if(CPPCOMPAT_LIBCXX_MIN)
  add_definitions(-DCPPCOMPAT_LIBCXX_MIN=${CPPCOMPAT_LIBCXX_MIN})
endif()
include_directories(include)
add_library(${PROJECT_NAME} STATIC
    src/cstdlib.cpp
    src/libcxx_verbose_abort.cpp
    src/libcxx_iostream_instantiations.cpp
    src/libcxx_functional.cpp
    )

install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR} # *.dll
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  FRAMEWORK DESTINATION ${CMAKE_INSTALL_LIBDIR}
  )
install(EXPORT ${PROJECT_NAME} DESTINATION lib/cmake)

# can merge libcppcompat.a built with libstdc++ and libc++, only inline std namespace symbols