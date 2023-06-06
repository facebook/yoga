# Yoga [![Support Ukraine](https://img.shields.io/badge/Support-Ukraine-FFD500?style=flat&labelColor=005BBB)](https://opensource.fb.com/support-ukraine) [![CocoaPods](https://img.shields.io/cocoapods/v/YogaKit.svg)](http://cocoapods.org/pods/YogaKit) [![npm](https://img.shields.io/npm/v/yoga-layout.svg)](https://www.npmjs.com/package/yoga-layout) [![Maven Central](https://img.shields.io/maven-central/v/com.facebook.yoga/yoga)](https://search.maven.org/artifact/com.facebook.yoga/yoga)

Yoga is an embeddable and performant flexbox layout engine with bindings for multiple languages.


## Building
Yoga's main implementation targets C++ 14 with accompanying build logic in CMake. A wrapper is provided to build the main library and run unit tests.

```sh
./unit_tests <Debug|Release>
```

While not required, this script will use [ninja](https://ninja-build.org/) if it is installed for faster builds.

Yoga is additionally part of the [vcpkg](https://github.com/Microsoft/vcpkg/) collection of ports maintained by Microsoft and community contributors. If the version is out of date, please [create an issue or pull request](https://github.com/Microsoft/vcpkg) on the vcpkg repository.



## Adding Tests

Many of Yoga's tests are automatically generated, using HTML fixtures describing node structure. These are rendered in Chrome to generate an expected layout result for the tree. New fixtures can be added to `gentest/fixtures`.

```html
<div id="my_test" style="width: 100px; height: 100px; align-items: center;">
  <div style="width: 50px; height: 50px;"></div>
</div>
```

To generate new tests from added fixtures:
1. Run `bundle install` in the `gentest` directory to install dependencies of the test generator.
2. Run `ruby gentest.rb` in the `gentest` directory.


## Debugging

Yoga provides a VSCode "launch.json" configuration which allows debugging unit tests. Simply add your breakpoints, and run "Debug C++ Unit tests (lldb)" (or "Debug C++ Unit tests (vsdbg)" on Windows).
