#!/bin/sh
# Copyright (c) Meta Platforms, Inc. and affiliates.
#
# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.

cd tests

if [ "$#" -eq 0 ]; then
  build_type="Debug"
else
  build_type="$1"
fi

if which ninja; then
  cmake -B build -S . -D CMAKE_BUILD_TYPE=$build_type -G Ninja
else
  cmake -B build -S . -D CMAKE_BUILD_TYPE=$build_type
fi

cmake --build build

./build/yogatests
