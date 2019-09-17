#
# Copyright (c) Facebook, Inc. and its affiliates.
#
# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.
#

cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_VERBOSE_MAKEFILE on)

add_compile_options(
    -fno-omit-frame-pointer
    -fexceptions
    -Wall
    -std=c++11
    -DDISABLE_CPUCAP
    -DDISABLE_XPLAT)

file(GLOB fb_SRC
    *.cpp
    jni/*.cpp
    jni/detail/*.cpp
    lyra/*.cpp)

add_library(fb SHARED
    ${fb_SRC})

target_include_directories(fb PRIVATE
    include)

target_link_libraries(fb android log)
