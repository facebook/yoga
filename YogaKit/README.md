# YogaKit

[![CocoaPods](https://img.shields.io/cocoapods/v/YogaKit.svg?style=flat)](https://cocoapods.org/pods/YogaKit)
[![Platform](https://img.shields.io/badge/platforms-iOS-orange.svg)](https://facebook.github.io/yoga/docs/api/yogakit/)
[![Languages](https://img.shields.io/badge/languages-ObjC%20%7C%20Swift-orange.svg)](https://facebook.github.io/yoga/docs/api/yogakit/)

## Installation

### CocoaPods
YogaKit is available to install via [CocoaPods](https://cocoapods.org/).

```
pod 'YogaKit', '~> 1.6'
```

### Carthage

To integrate YogaKit into your Xcode project using Carthage:

1. Specify it in your `Cartfile`:  
```
github "facebook/yoga"
```

2. Run `carthage update` to build the framework.
3. Add the built `YogaKit.framework` into your Xcode project.
4. Add the preprocessor macro `USE_YOGAKIT_PACKAGE` in your Xcode project. Target > Build Settings > Preprocessor Macros. add `USE_YOGAKIT_PACKAGE` in the **Debug** and the **Release** entry.



## Getting Started
Checkout the docs [here](https://facebook.github.io/yoga/docs/api/yogakit/).

We also have a sample project. To try it out, clone this repo and open `YogaKitSample.xcodeproj` in the [YogaKitSample](https://github.com/facebook/yoga/tree/master/YogaKit/YogaKitSample) directory.

## Contributing
We welcome all pull-requests! At Facebook we sync the open source version of `YogaKit` daily, so we're always testing the latest changes.

See the [CONTRIBUTING.md](https://github.com/facebook/yoga/blob/master/CONTRIBUTING.md) file for how to help out.
