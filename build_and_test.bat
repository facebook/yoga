@REM Copyright (c) Meta Platforms, Inc. and affiliates.
@REM
@REM This source code is licensed under the MIT license found in the
@REM LICENSE file in the root directory of this source tree.

@echo off
SETLOCAL

cd tests

if "%1" == "" (
  build_type="Debug"
) else (
  build_type="%1"
)

where ninja
if errorlevel 1 (
  cmake -B build -S . -D CMAKE_BUILD_TYPE=$build_type -G Ninja
) else  (
  cmake -B build -S . -D CMAKE_BUILD_TYPE=$build_type
)
if %errorlevel% neq 0 exit /b %errorlevel%

cmake --build build
if %errorlevel% neq 0 exit /b %errorlevel%

./build/yogatests
