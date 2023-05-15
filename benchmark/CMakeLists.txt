# Copyright (c) Meta Platforms, Inc. and affiliates.
#
# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.


cmake_minimum_required(VERSION 3.13...3.26)
project(benchmark)
set(CMAKE_VERBOSE_MAKEFILE on)

set(YOGA_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/..)
include(${YOGA_ROOT}/cmake/project-defaults.cmake)

add_subdirectory(${YOGA_ROOT}/yoga ${CMAKE_CURRENT_BINARY_DIR}/yoga)

file(GLOB SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.c)
add_executable(benchmark ${SOURCES})
target_link_libraries(benchmark yogacore)
