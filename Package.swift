// swift-tools-version:5.3
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
    name: "yoga",
    platforms: [
		.iOS(.v14),
	],
    products: [
        .library(
            name: "yoga",
            type: .dynamic,
            targets: ["yoga"]
		),
    ],
    targets: [
        .target(
            name: "yoga",
            dependencies: [],
			path: "./yoga",
//			publicHeadersPath: "./yoga",
			cxxSettings: [
				.headerSearchPath("../"),
//				.unsafeFlags([
//					"-fno-omit-frame-pointer",
//					"-fexceptions",
//					"-Wall",
//					"-Werror",
//					"-std=c++1y",
//					"-fPIC",
//				])
			],
            linkerSettings: [
                .linkedFramework("Foundation"),
                .linkedFramework("UIKit", .when(platforms: [.iOS])),
            ]
		)
    ],
    cxxLanguageStandard: .cxx14
)
