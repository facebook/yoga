# Copyright (c) Facebook, Inc. and its affiliates.
#
# This source code is licensed under the MIT license found in the
# LICENSE file in the root directory of this source tree.
load("//tools/build_defs/oss:yoga_defs.bzl", "subdir_glob", "yoga_apple_library", "yoga_apple_test", "yoga_dep")

COMPILER_FLAGS = [
    "-fobjc-arc",
    "-Wconditional-uninitialized",
    "-Wdangling-else",
    "-Wdeprecated-declarations",
    "-Wimplicit-retain-self",
    "-Wincomplete-implementation",
    "-Wobjc-method-access",
    "-Wobjc-missing-super-calls",
    "-Wmismatched-return-types",
    "-Wreturn-type",
    "-Wno-global-constructors",
    "-Wno-shadow",
    "-Wunused-const-variable",
    "-Wunused-function",
    "-Wunused-property-ivar",
    "-Wunused-result",
    "-Wunused-value",
]

yoga_apple_library(
    name = "YogaKit",
    srcs = glob(["Source/**/*.m"]),
    header_namespace = "",
    exported_headers = subdir_glob(
        [
            ("", "Source/**/*.h"),
            ("Source", "**/*.h"),
        ],
        prefix = "YogaKit",
    ),
    compiler_flags = COMPILER_FLAGS,
    frameworks = [
        "$SDKROOT/System/Library/Frameworks/Foundation.framework",
        "$SDKROOT/System/Library/Frameworks/UIKit.framework",
    ],
    header_path_prefix = "",
    link_whole = True,
    visibility = ["PUBLIC"],
    deps = [
        yoga_dep(":yoga"),
    ],
)

yoga_apple_test(
    name = "YogaKitTests",
    srcs = glob(["Tests/**/*.m"]),
    compiler_flags = COMPILER_FLAGS,
    frameworks = [
        "$PLATFORM_DIR/Developer/Library/Frameworks/XCTest.framework",
        "$SDKROOT/System/Library/Frameworks/CoreGraphics.framework",
    ],
    info_plist = "Tests/Info.plist",
    visibility = ["PUBLIC"],
    deps = [
        ":YogaKit",
    ],
)
