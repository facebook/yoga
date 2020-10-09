// swift-tools-version:5.3
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "yoga",
    platforms: [
        .iOS(.v9),
        .macOS(.v10_10),
        .watchOS(.v2),
        .tvOS(.v10),
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
            publicHeadersPath: "./swiftpm-support",
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
