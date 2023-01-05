# Copyright (c) Meta Platforms, Inc. and affiliates.
#
# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.

cmake_minimum_required(VERSION 3.4.1)

project(yoga)

set(CMAKE_VERBOSE_MAKEFILE on)

# configure import libs
add_compile_definitions($<$<CONFIG:Debug>:DEBUG>)
if (MSVC)
    add_compile_definitions(_WINDLL)
endif()

set(yogacore_DIR ${CMAKE_SOURCE_DIR}/../.. yogacore)
set(build_DIR ${CMAKE_SOURCE_DIR}/build)

file(MAKE_DIRECTORY ${build_DIR})

add_subdirectory(${yogacore_DIR})

if (MSVC)
    add_compile_options(
        # Don't omit frame pointers (e.g. for crash dumps)
        /Oy-
        # "Standard C++ exception handling" (C++ stack unwinding including extern c)
        /EHsc
        # Enable warnings and warnings as errors
        /W3
        /WX
        # Disable RTTI
        $<$<COMPILE_LANGUAGE:CXX>:/GR->
        # Use /O2 (Maximize Speed)
        $<$<CONFIG:RELEASE>:/O2>)
else()
    add_compile_options(
        -fno-omit-frame-pointer
        -fexceptions
        -fvisibility=hidden
        -ffunction-sections
        -fdata-sections
        -Wall
        -std=c++11)
endif()

set(SOURCES YGInterop.cpp)

if (MSVC)
    list(APPEND SOURCES Yoga.rc)
endif()

file(GLOB yogajni_version_script
        yogajni.version)

add_library(yoga SHARED ${SOURCES})

target_include_directories(yoga PRIVATE
    ${yogacore_DIR})

target_link_libraries(yoga yogacore)

if (NOT MSVC)
    target_link_libraries(yoga -Wl,--gc-sections)
endif()

install(TARGETS yoga DESTINATION .)