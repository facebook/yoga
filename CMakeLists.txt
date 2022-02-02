# Copyright (c) Facebook, Inc. and its affiliates.
#
# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.

cmake_minimum_required(VERSION 3.4.1)

project(yoga)
set(CMAKE_VERBOSE_MAKEFILE on)

add_compile_options(
    -fno-omit-frame-pointer
    -fexceptions
    -fvisibility=hidden
    -ffunction-sections
    -fdata-sections
    -fPIC
    -Wall
    -std=c++11)

file(GLOB_RECURSE YOGA_SRC yoga/*.cpp)
add_library(${CMAKE_PROJECT_NAME} STATIC ${YOGA_SRC})

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC .)
target_link_libraries(${CMAKE_PROJECT_NAME} android log)
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES CXX_STANDARD 11)
