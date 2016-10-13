# Copyright (c) 2014-present, Facebook, Inc.
# All rights reserved.
#
# This source code is licensed under the BSD-style license found in the
# LICENSE file in the root directory of this source tree. An additional grant
# of patent rights can be found in the PATENTS file in the same directory.

include_defs('//CSSLAYOUT_DEFS')

BASE_COMPILER_FLAGS = [
  '-fno-omit-frame-pointer',
  '-fexceptions',
  '-Wall',
  '-Werror',
  '-O3',
]

GMOCK_OVERRIDE_FLAGS = [
  # gmock does not mark mocked methods as override, ignore the warnings in tests
  '-Wno-inconsistent-missing-override',
]

COMPILER_FLAGS = BASE_COMPILER_FLAGS + ['-std=c11']
TEST_COMPILER_FLAGS = BASE_COMPILER_FLAGS + GMOCK_OVERRIDE_FLAGS + ['-std=c++11']

cxx_library(
  name = 'CSSLayout',
  srcs = glob(['CSSLayout/*.c']),
  tests=[':tests'],
  exported_headers = subdir_glob([('', 'CSSLayout/*.h')]),
  header_namespace = '',
  force_static = True,
  compiler_flags = COMPILER_FLAGS,
  deps = [],
  visibility = ['PUBLIC'],
)

cxx_test(
  name = 'tests',
  contacts = ['emilsj@fb.com'],
  srcs = glob(['tests/*.cpp']),
  compiler_flags = TEST_COMPILER_FLAGS,
  deps = [
    ':CSSLayout',
    GTEST_TARGET,
  ],
  visibility = ['PUBLIC'],
)
