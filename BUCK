# Copyright (c) Facebook, Inc. and its affiliates.
#
# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.
load("//tools/build_defs/oss:yoga_defs.bzl", "BASE_COMPILER_FLAGS", "GTEST_TARGET", "LIBRARY_COMPILER_FLAGS", "YOGA_ROOTS", "subdir_glob", "yoga_cxx_library", "yoga_cxx_test", "yoga_dep", "yoga_prebuilt_cxx_library")

GMOCK_OVERRIDE_FLAGS = [
    # gmock does not mark mocked methods as override, ignore the warnings in tests
    "-Wno-inconsistent-missing-override",
]

TEST_COMPILER_FLAGS = BASE_COMPILER_FLAGS + GMOCK_OVERRIDE_FLAGS + [
    "-DDEBUG",
    "-DYG_ENABLE_EVENTS",
]

yoga_prebuilt_cxx_library(
    name = "ndklog",
    exported_platform_linker_flags = [
        (
            "^android.*",
            ["-llog"],
        ),
    ],
    header_only = True,
    visibility = YOGA_ROOTS,
)

yoga_cxx_library(
    name = "yoga",
    srcs = glob(["yoga/**/*.cpp"]),
    compiler_flags = LIBRARY_COMPILER_FLAGS,
    public_include_directories = ["."],
    raw_headers = glob(["yoga/**/*.h"]),
    soname = "libyogacore.$(ext)",
    tests = [":YogaTests"],
    visibility = ["PUBLIC"],
    deps = [
        ":ndklog",
    ],
)

yoga_cxx_library(
    name = "yogaForDebug",
    srcs = glob(["yoga/**/*.cpp"]),
    compiler_flags = TEST_COMPILER_FLAGS,
    public_include_directories = ["."],
    raw_headers = glob(["yoga/**/*.h"]),
    soname = "libyogacore.$(ext)",
    tests = [":YogaTests"],
    visibility = ["PUBLIC"],
    deps = [
        ":yoga",
    ],
)

yoga_cxx_test(
    name = "YogaTests",
    srcs = glob(["tests/*.cpp"]),
    headers = subdir_glob([("", "yoga/**/*.h")]),
    compiler_flags = TEST_COMPILER_FLAGS,
    contacts = ["emilsj@fb.com"],
    visibility = ["PUBLIC"],
    deps = [
        ":yogaForDebug",
        yoga_dep("testutil:testutil"),
        GTEST_TARGET,
    ],
)
