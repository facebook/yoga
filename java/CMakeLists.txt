# Copyright (c) Facebook, Inc. and its affiliates.
#
# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.

cmake_minimum_required(VERSION 3.4.1)

set(CMAKE_VERBOSE_MAKEFILE on)

# configure import libs
set(yogacore_DIR ${CMAKE_SOURCE_DIR}/..)
set(build_DIR ${CMAKE_SOURCE_DIR}/build)

set(yogacore_build_DIR ${build_DIR}/yogacore/${ANDROID_ABI})

file(MAKE_DIRECTORY ${build_DIR})

add_subdirectory(${yogacore_DIR} ${yogacore_build_DIR})

add_compile_options(
    -fno-omit-frame-pointer
    -fexceptions
    -fvisibility=hidden
    -ffunction-sections
    -fdata-sections
    -Wall
    -std=c++11)

file(GLOB jni_SRC
        jni/*.cpp)

file(GLOB yogajni_version_script
        yogajni.version)

add_library(yoga SHARED ${jni_SRC})

target_include_directories(yoga PRIVATE
    ${yogacore_DIR})

target_link_libraries(yoga -Wl,--gc-sections,--version-script=${yogajni_version_script} yogacore)
