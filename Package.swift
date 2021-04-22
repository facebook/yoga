// swift-tools-version:5.1
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
  name: "YogaKit",
  platforms: [
    .iOS(.v10)
  ],
  products: [
    .library(name: "YogaKit", targets: ["YogaKit"])
  ],
  dependencies: [
  ],
  targets: [
    .target(
      name: "yoga",
      dependencies: [],
      path: "yoga",
      cxxSettings: [
        .headerSearchPath("yoga")
      ]
    ),
    .target(
      name: "YogaObjectiveC",
      dependencies: ["yoga"],
      path: "YogaKit/Source",
      exclude: ["swift"],
      cxxSettings: [
        .headerSearchPath("YogaKit/Source")
      ] 
    ),
    .target(
      name: "YogaKit",
      dependencies: ["YogaObjectiveC"],
      path: "YogaKit/Source/swift"
    )
  ],
  cxxLanguageStandard: .cxx14
)
