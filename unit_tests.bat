@REM Copyright (c) Meta Platforms, Inc. and affiliates.
@REM
@REM This source code is licensed under the MIT license found in the
@REM LICENSE file in the root directory of this source tree.

@echo off
SETLOCAL

cd "%0\..\tests"

if "%1" == "" (
  set build_type="Debug"
) else (
  set build_type="%1"
)

where ninja
if errorlevel 1 (
  cmake -B build -S . -D CMAKE_BUILD_TYPE="%build_type%"
) else  (
  cmake -B build -S . -D CMAKE_BUILD_TYPE="%build_type%" -G Ninja
)
if %errorlevel% neq 0 exit /b %errorlevel%

cmake --build build
if %errorlevel% neq 0 exit /b %errorlevel%

.\build\yogatests.exe
