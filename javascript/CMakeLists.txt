# Copyright (c) Meta Platforms, Inc. and affiliates.
#
# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.

cmake_minimum_required(VERSION 3.13...3.26)
set(CMAKE_VERBOSE_MAKEFILE on)
project(yoga)

file(GLOB SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/../yoga/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/../yoga/**/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

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
    "SHELL:-s EXPORT_NAME='loadYoga'"
    "SHELL:-s FETCH_SUPPORT_INDEXEDDB=0"
    "SHELL:-s FILESYSTEM=0"
    "SHELL:-s MALLOC='emmalloc'"
    "SHELL:-s MODULARIZE=1"
    "SHELL:-s TEXTDECODER=0"
    "SHELL:-s SINGLE_FILE=1")

link_libraries(embind)

add_library(yogaObjLib OBJECT ${SOURCES})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/binaries)

add_executable(asmjs-sync-node $<TARGET_OBJECTS:yogaObjLib>)
target_link_options(asmjs-sync-node PUBLIC
    "SHELL:-s ENVIRONMENT='node'"
    "SHELL:-s WASM=0"
    "SHELL:-s WASM_ASYNC_COMPILATION=0")

add_executable(asmjs-async-node $<TARGET_OBJECTS:yogaObjLib>)
target_link_options(asmjs-async-node PUBLIC
    "SHELL:-s ENVIRONMENT='node'"
    "SHELL:-s WASM=0"
    "SHELL:-s WASM_ASYNC_COMPILATION=1")

add_executable(asmjs-sync-web $<TARGET_OBJECTS:yogaObjLib>)
target_link_options(asmjs-sync-web PUBLIC
    "SHELL:-s ENVIRONMENT='web'"
    "SHELL:-s WASM=0"
    "SHELL:-s WASM_ASYNC_COMPILATION=0")

add_executable(asmjs-async-web $<TARGET_OBJECTS:yogaObjLib>)
target_link_options(asmjs-async-web PUBLIC
    "SHELL:-s ENVIRONMENT='web'"
    "SHELL:-s WASM=0"
    "SHELL:-s WASM_ASYNC_COMPILATION=1")

add_executable(asmjs-sync $<TARGET_OBJECTS:yogaObjLib>)
target_link_options(asmjs-sync PUBLIC
    "SHELL:-s ENVIRONMENT='web,node'"
    "SHELL:-s WASM=0"
    "SHELL:-s WASM_ASYNC_COMPILATION=0")

add_executable(asmjs-async $<TARGET_OBJECTS:yogaObjLib>)
target_link_options(asmjs-async PUBLIC
    "SHELL:-s ENVIRONMENT='web,node'"
    "SHELL:-s WASM=0"
    "SHELL:-s WASM_ASYNC_COMPILATION=1")

add_executable(wasm-sync-node $<TARGET_OBJECTS:yogaObjLib>)
target_link_options(wasm-sync-node PUBLIC
    "SHELL:-s ENVIRONMENT='node'"
    "SHELL:-s WASM=1"
    "SHELL:-s WASM_ASYNC_COMPILATION=0")

add_executable(wasm-async-node $<TARGET_OBJECTS:yogaObjLib>)
target_link_options(wasm-async-node PUBLIC
    "SHELL:-s ENVIRONMENT='node'"
    "SHELL:-s WASM=1"
    "SHELL:-s WASM_ASYNC_COMPILATION=1")

add_executable(wasm-sync-web $<TARGET_OBJECTS:yogaObjLib>)
target_link_options(wasm-sync-web PUBLIC
    "SHELL:-s ENVIRONMENT='web'"
    "SHELL:-s WASM=1"
    "SHELL:-s WASM_ASYNC_COMPILATION=0")

add_executable(wasm-async-web $<TARGET_OBJECTS:yogaObjLib>)
target_link_options(wasm-async-web PUBLIC
    "SHELL:-s ENVIRONMENT='web'"
    "SHELL:-s WASM=1"
    "SHELL:-s WASM_ASYNC_COMPILATION=1")
