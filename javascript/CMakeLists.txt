# Copyright (c) Meta Platforms, Inc. and affiliates.
#
# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.

cmake_minimum_required(VERSION 3.13)
set(CMAKE_VERBOSE_MAKEFILE on)
project(yoga)

file(GLOB SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/../yoga/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../yoga/**/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src_native/*.cc)

include_directories(..)

set(CMAKE_CXX_STANDARD 14)

add_compile_definitions(
    EMSCRIPTEN_HAS_UNBOUND_TYPE_NAMES=0)

set(COMPILE_OPTIONS
    -flto
    -fno-exceptions
    -fno-rtti
    -g0
    -Os
    "SHELL:-s STRICT=1")

add_compile_options(${COMPILE_OPTIONS})

add_link_options(
    ${COMPILE_OPTIONS}
    --closure 1
    --memory-init-file 0
    --no-entry
    "SHELL:-s ALLOW_MEMORY_GROWTH=1"
    "SHELL:-s ASSERTIONS=0"
    "SHELL:-s DYNAMIC_EXECUTION=0"
    "SHELL:-s ENVIRONMENT='web,node'"
    "SHELL:-s EXPORT_NAME='loadYoga'"
    "SHELL:-s FETCH_SUPPORT_INDEXEDDB=0"
    "SHELL:-s FILESYSTEM=0"
    "SHELL:-s MALLOC='emmalloc'"
    "SHELL:-s MODULARIZE=1"
    "SHELL:-s TEXTDECODER=0")

link_libraries(embind)

add_library(yogaObjLib OBJECT ${SOURCES})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/dist/build)

add_executable(asmjs-sync $<TARGET_OBJECTS:yogaObjLib>)
target_link_options(asmjs-sync PUBLIC
    "SHELL:-s WASM=0"
    "SHELL:-s WASM_ASYNC_COMPILATION=0")

add_executable(asmjs-async $<TARGET_OBJECTS:yogaObjLib>)
target_link_options(asmjs-async PUBLIC
    "SHELL:-s WASM=0"
    "SHELL:-s WASM_ASYNC_COMPILATION=1")

add_executable(wasm-sync $<TARGET_OBJECTS:yogaObjLib>)
target_link_options(wasm-sync PUBLIC
    "SHELL:-s WASM=1"
    "SHELL:-s WASM_ASYNC_COMPILATION=0")

add_executable(wasm-async $<TARGET_OBJECTS:yogaObjLib>)
target_link_options(wasm-async PUBLIC
    "SHELL:-s WASM=1"
    "SHELL:-s WASM_ASYNC_COMPILATION=1")
