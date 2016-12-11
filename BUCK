# Copyright (c) 2014-present, Facebook, Inc.
# All rights reserved.
#
# This source code is licensed under the BSD-style license found in the
# LICENSE file in the root directory of this source tree. An additional grant
# of patent rights can be found in the PATENTS file in the same directory.

include_defs('//YOGA_DEFS')

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

COMPILER_FLAGS = BASE_COMPILER_FLAGS + ['-std=c11', '-fPIC']
TEST_COMPILER_FLAGS = BASE_COMPILER_FLAGS + GMOCK_OVERRIDE_FLAGS + ['-std=c++11']

cxx_library(
  name = 'yoga',
  soname = 'libyogacore.$(ext)',
  srcs = glob(['yoga/*.c']),
  tests=[':YogaTests'],
  exported_headers = subdir_glob([('', 'yoga/*.h')]),
  header_namespace = '',
  compiler_flags = COMPILER_FLAGS,
  deps = [] if THIS_IS_FBOBJC else [
    yoga_dep('lib/fb:ndklog'),
  ],
  visibility = ['PUBLIC'],
)

cxx_test(
  name = 'YogaTests',
  contacts = ['emilsj@fb.com'],
  srcs = glob(['tests/*.cpp']),
  compiler_flags = TEST_COMPILER_FLAGS,
  deps = [
    ':yoga',
    GTEST_TARGET,
  ],
  visibility = ['PUBLIC'],
)
