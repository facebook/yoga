#
# Copyright (c) Facebook, Inc. and its affiliates.
#
# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.
#

cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_VERBOSE_MAKEFILE on)

file(GLOB yogacore_SRC yoga/*.cpp)
add_library(yogacore STATIC ${yogacore_SRC})

add_compile_options(
    -fno-omit-frame-pointer
    -fexceptions
    -Wall
    -std=c++14)
    
target_link_libraries(yogacore android log)
