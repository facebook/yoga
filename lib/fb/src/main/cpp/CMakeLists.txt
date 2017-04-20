#
# Copyright (c) 2014-present, Facebook, Inc.
# All rights reserved.
#
# This source code is licensed under the BSD-style license found in the
# LICENSE file in the root directory of this source tree. An additional grant
# of patent rights can be found in the PATENTS file in the same directory.
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
    lyra/*.cpp)

add_library(fb SHARED
    ${fb_SRC})

target_include_directories(fb PRIVATE
    include)

target_link_libraries(fb android log)
