# Copyright (c) Meta Platforms, Inc. and affiliates.
#
# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

add_compile_definitions($<$<CONFIG:DEBUG>:DEBUG>)

if(MSVC)

add_compile_options(
    # Don't omit frame pointers (e.g. for crash dumps)
    /Oy-
    # "Standard C++ exception handling" (C++ stack unwinding including extern c)
    /EHsc
    # Enable warnings and warnings as errors
    /W3
    /WX
    # Disable RTTI
    /GR[-]
    # Use /O2 (Maximize Speed)
    $<$<CONFIG:RELEASE>:/O2>)

else()

add_compile_options(
    # Don't omit frame pointers (e.g. for crash dumps)
    -fno-omit-frame-pointer
    # Enable exception handling
    -fexceptions
    # Enable warnings and warnings as errors
    -Wall
    -Werror
    # Disable RTTI
    -fno-rtti
    # Use -Os (-O2 + size savings)
    $<$<CONFIG:RELEASE>:-Os>
    # Enable separate sections per function/data item
    $<$<CONFIG:RELEASE>:-ffunction-sections>
    $<$<CONFIG:RELEASE>:-fdata-sections>)

add_link_options(
    # Discard unused sections in release
    $<$<CONFIG:RELEASE>:$<$<CXX_COMPILER_ID:Clang>:-Wl,--gc-sections>>
    $<$<CONFIG:RELEASE>:$<$<CXX_COMPILER_ID:AppleClang>:-Wl,-dead_strip>>)

endif()