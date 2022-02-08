# Copyright (c) Facebook, Inc. and its affiliates.
#
# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.

cmake_minimum_required(VERSION 3.4.1)

project(yogacore)

set(CMAKE_VERBOSE_MAKEFILE on)

file(GLOB_RECURSE yogacore_SRC yoga/*.cpp)

if (!WIN32)
    add_compile_options(
            -fno-omit-frame-pointer
            -fexceptions
            -fvisibility=hidden
            -ffunction-sections
            -fdata-sections
            -Wall
            -std=c++11)

    add_library(yogacore STATIC ${yogacore_SRC})

    target_include_directories(yogacore PUBLIC .)
    if( ANDROID )
        target_link_libraries(yogacore android log)
    endif ()
    set_target_properties(yogacore PROPERTIES CXX_STANDARD 11)

else()

    # for windows
    ### STATIC, SHARED, or MODULE may be given to specify the type of library to be created.
    # STATIC libraries are archives of object files for use when linking other targets.
    # SHARED libraries are linked dynamically and loaded at runtime.
    # MODULE libraries are plugins that are not linked into other targets but may be loaded dynamically at runtime using dlopen-like functionality.
    ### so we choose MODULE
    add_library(yogacore MODULE ${yogacore_SRC})

    # windows target
    target_include_directories(yogacore PUBLIC .)
    target_compile_options(yogacore PRIVATE /D_WINDLL)
    set_target_properties(yogacore PROPERTIES CXX_STANDARD 11)
    # target_compile_options(yogacore-win PRIVATE /D_WINDOWS /GR /EHsc /MDd /Zi /O2 /W4 /O2 /Be /Bd /EP)
endif ()

