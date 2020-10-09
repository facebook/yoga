// swift-tools-version:5.3
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "yoga",
    platforms: [
        .iOS(.v11),
    ],
    products: [
        .library(
            name: "yoga",
            targets: ["yoga"]
        ),
    ],
    targets: [
        .target(
            name: "yoga",
            dependencies: [],
            path: "./yoga",
            publicHeadersPath: "./apple-public",
            cxxSettings: [
                .headerSearchPath("../"),
            ],
            linkerSettings: [
                .linkedFramework("Foundation"),
            ]
        )
    ],
    cxxLanguageStandard: .cxx14
)