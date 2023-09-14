// swift-tools-version:5.0
// The swift-tools-version declares the minimum version of Swift required to build this package.
/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */


import PackageDescription

let package = Package(
    name: "yoga",
    products: [
        .library(name: "yoga", targets: [ "core" ])
    ],
    targets: [
        .target(
            name: "core",
            path: ".",
            sources: [
                "yoga"
            ],
            publicHeadersPath: ".",
            cxxSettings: [
                .headerSearchPath(".")
            ],
            linkerSettings: [
                // Binaries using symbols with a weak definition crash at runtime on iOS 14/macOS 12 or older
                // when using the Xcode 15 toolchain (FB13097713)
                .unsafeFlags(["-Wl", "-ld_classic"])
            ]
        )
    ],
    cxxLanguageStandard: CXXLanguageStandard(rawValue: "c++17")
)
