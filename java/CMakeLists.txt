#
# Copyright (c) Facebook, Inc. and its affiliates.
#
# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.
#

cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_VERBOSE_MAKEFILE on)

# configure import libs
set(libfb_DIR ${CMAKE_SOURCE_DIR}/../lib/fb/src/main/cpp)
set(yogacore_DIR ${CMAKE_SOURCE_DIR}/..)

set(build_DIR ${CMAKE_SOURCE_DIR}/build)

set(libfb_build_DIR ${build_DIR}/libfb/${ANDROID_ABI})
set(yogacore_build_DIR ${build_DIR}/yogacore/${ANDROID_ABI})

file(MAKE_DIRECTORY ${build_DIR})

add_subdirectory(${libfb_DIR} ${libfb_build_DIR})
add_subdirectory(${yogacore_DIR} ${yogacore_build_DIR})

add_compile_options(
    -fno-omit-frame-pointer
    -fexceptions
    -Wall
    -std=c++11)

add_library(yoga SHARED jni/YGJNI.cpp jni/YGJTypes.cpp)

target_include_directories(yoga PRIVATE
    ${libfb_DIR}/include
    ${yogacore_DIR})

target_link_libraries(yoga yogacore fb)
