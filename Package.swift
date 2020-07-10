// swift-tools-version:5.0

import PackageDescription

let package = Package(
    name: "YogaKit",
    platforms: [
        .macOS(.v10_10),
        .iOS(.v8),
        .tvOS(.v9),
        .watchOS(.v2)
    ],
    products: [
        .library(
            name: "YogaKit", 
            //type: .dynamic,
            targets: ["YogaKit"]
        )
    ],
    dependencies: [],
    targets: [
        .target(
            name: "YogaKit",
            path: "yoga",
            //exclude: [],
            sources: ["./"],
            publicHeadersPath: "include",
            cSettings: [ 
                .headerSearchPath("./")
            ]
        )
    ],
    swiftLanguageVersions: [
        .version("5")
    ],
    cLanguageStandard: .gnu11,
    cxxLanguageStandard: .gnucxx14
)
