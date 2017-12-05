# Copyright (c) 2014-present, Facebook, Inc.
# All rights reserved.
#
# This source code is licensed under the BSD-style license found in the
# LICENSE file in the root directory of this source tree. An additional grant
# of patent rights can be found in the PATENTS file in the same directory.

include_defs("//yoga_defs.bzl")

GMOCK_OVERRIDE_FLAGS = [
    # gmock does not mark mocked methods as override, ignore the warnings in tests
    "-Wno-inconsistent-missing-override",
]

COMPILER_FLAGS = LIBRARY_COMPILER_FLAGS + [
    "-std=c++1y",
    "-Wno-global-constructors",
]

TEST_COMPILER_FLAGS = BASE_COMPILER_FLAGS + GMOCK_OVERRIDE_FLAGS + [
    "-std=c++1y",
]

cxx_library(
    name = "yoga",
    srcs = glob(["yoga/*.cpp"]),
    header_namespace = "",
    exported_headers = subdir_glob([("", "yoga/*.h")]),
    compiler_flags = COMPILER_FLAGS,
    soname = "libyogacore.$(ext)",
    tests = [":YogaTests"],
    visibility = ["PUBLIC"],
    deps = [] if THIS_IS_FBOBJC else [
        yoga_dep("lib/fb:ndklog"),
    ],
)

cxx_test(
    name = "YogaTests",
    srcs = glob(["tests/*.cpp"]),
    compiler_flags = TEST_COMPILER_FLAGS,
    contacts = ["emilsj@fb.com"],
    visibility = ["PUBLIC"],
    deps = [
        ":yoga",
        GTEST_TARGET,
    ],
)
