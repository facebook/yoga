// swift-tools-version:5.0
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "yoga",
    platforms: [
        .macOS(.v10_10), .iOS(.v9), .tvOS(.v9)
    ],
    products: [
        // Products define the executables and libraries a package produces, and make them visible to other packages.
        .library(
            name: "YogaKit",
            targets: ["YogaKit"]),
        .library(
            name: "Yoga",
            targets: ["Yoga"])
    ],
    dependencies: [
        // Dependencies declare other packages that this package depends on.
        // .package(url: /* package url */, from: "1.0.0"),
    ],
    targets: [
        // Targets are the basic building blocks of a package. A target can define a module or a test suite.
        // Targets can depend on other targets in this package, and on products in packages this package depends on.
        .target(
            name: "YogaKit",
            dependencies: ["Yoga"],
            path: "YogaKit",
            exclude: ["Source/YGLayoutExtensions.swift"],
            sources: ["Source"],
            publicHeadersPath: "Source/modulemap",
            cSettings: [
                .headerSearchPath("..")
            ]),
        .target(
            name: "Yoga",
            path: "yoga",
            sources: ["."],
            publicHeadersPath: "modulemap",
            cSettings: [
                .headerSearchPath("..")
            ])
    ],
    cLanguageStandard: .gnu11,
    cxxLanguageStandard: .gnucxx14
)
