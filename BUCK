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
JNI_COMPILER_FLAGS = BASE_COMPILER_FLAGS + ['-std=c++11']
TEST_COMPILER_FLAGS = BASE_COMPILER_FLAGS + GMOCK_OVERRIDE_FLAGS + ['-std=c++11']

cxx_library(
  name = 'CSSLayout',
  srcs = glob(['CSSLayout/*.c']),
  tests=[':CSSLayout_tests'],
  xcode_public_headers_symlinks = True,
  exported_headers = subdir_glob([('', 'CSSLayout/*.h')]),
  header_namespace = '',
  force_static = True,
  compiler_flags = COMPILER_FLAGS,
  deps = [],
  visibility = ['PUBLIC'],
)

cxx_library(
  name = 'CSSLayout_jni',
  soname = 'libcsslayout.$(ext)',
  srcs = glob(['java/jni/*.cpp']),
  header_namespace = '',
  compiler_flags = JNI_COMPILER_FLAGS,
  deps = [
    ':CSSLayout',
    css_layout_dep('lib/fb:fbjni'),
  ],
  visibility = ['PUBLIC'],
)

cxx_binary(
  name = 'benchmark',
  srcs = glob(['benchmarks/*.c']),
  headers = subdir_glob([('', 'benchmarks/*.h')]),
  header_namespace = '',
  compiler_flags = COMPILER_FLAGS,
  deps = [
    ':CSSLayout',
  ],
  visibility = ['PUBLIC'],
)

cxx_library(
  name = 'CSSLayoutTestUtils',
  srcs = glob(['tests/CSSLayoutTestUtils/*.c']),
  xcode_public_headers_symlinks = True,
  exported_headers = subdir_glob([('tests', 'CSSLayoutTestUtils/*.h')]),
  header_namespace = '',
  compiler_flags = COMPILER_FLAGS,
  deps = [
    ':CSSLayout',
  ],
  visibility = ['PUBLIC'],
)

cxx_test(
  name = 'CSSLayout_tests',
  contacts = ['emilsj@fb.com'],
  srcs = glob(['tests/*.cpp']),
  compiler_flags = TEST_COMPILER_FLAGS,
  deps = [
    ':CSSLayout',
    ':CSSLayoutTestUtils',
    GTEST_TARGET,
  ],
  visibility = ['PUBLIC'],
)

java_library(
  name = 'CSSLayout_java',
  srcs = glob(['java/com/facebook/csslayout/*.java']),
  tests=[':CSSLayout_java_tests'],
  source = '1.7',
  target = '1.7',
  deps = [
    ':CSSLayout_jni',
    INFER_ANNOTATIONS_TARGET,
    JSR_305_TARGET,
    PROGRUARD_ANNOTATIONS_TARGET,
    SOLOADER_TARGET,
  ],
  visibility = ['PUBLIC'],
)

java_test(
  name = 'CSSLayout_java_tests',
  srcs = glob(['tests/java/**/*.java']),
  deps = [
    ':CSSLayout_java',
    JUNIT_TARGET,
  ],
)
