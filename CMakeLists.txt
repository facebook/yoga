# Copyright (c) Facebook, Inc. and its affiliates.
#
# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.

cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_VERBOSE_MAKEFILE on)

add_compile_options(
    -fno-omit-frame-pointer
    -fexceptions
    -fvisibility=hidden
    -ffunction-sections
    -fdata-sections
    -Wall
    -std=c++11)

file(GLOB_RECURSE yogacore_SRC yoga/*.cpp)
add_library(yogacore STATIC ${yogacore_SRC})

target_include_directories(yogacore PUBLIC .)
target_link_libraries(yogacore android log)
set_target_properties(yogacore PROPERTIES CXX_STANDARD 11)
