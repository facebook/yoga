# Yoga [![Support Ukraine](https://img.shields.io/badge/Support-Ukraine-FFD500?style=flat&labelColor=005BBB)](https://opensource.fb.com/support-ukraine) [![CocoaPods](https://img.shields.io/cocoapods/v/Yoga.svg)](http://cocoapods.org/pods/Yoga) [![npm](https://img.shields.io/npm/v/yoga-layout.svg)](https://www.npmjs.com/package/yoga-layout) [![Maven Central](https://img.shields.io/maven-central/v/com.facebook.yoga/yoga)](https://search.maven.org/artifact/com.facebook.yoga/yoga)

Yoga is an embeddable and performant flexbox layout engine with bindings for multiple languages.
Yoga allows users to build flexible layouts on any platform with ease of use in mind.

The technologies used in this project are Litho, React Native, Component, and Standalone. Reference our documentation for step-by-step instructions to setting up these technologies on your device.

In the future, we would like to add more properties that the user can implement to make their layout more complex. Please consider contributing documentation, code, or tests to help with this effort.

## Building

Yoga's main implementation targets C++ 20 with accompanying build logic in CMake. A wrapper is provided to build the main library and run unit tests.

```sh
./unit_tests <Debug|Release>
```

While not required, this script will use [ninja](https://ninja-build.org/) if it is installed for faster builds.

Yoga is additionally part of the [vcpkg](https://github.com/Microsoft/vcpkg/) collection of ports maintained by Microsoft and community contributors. If the version is out of date, please [create an issue or pull request](https://github.com/Microsoft/vcpkg) on the vcpkg repository.

## Example of the Project in Use
[![Screen-Shot-2024-02-14-at-8-15-37-PM.png](https://i.postimg.cc/fTZBZtbz/Screen-Shot-2024-02-14-at-8-15-37-PM.png)](https://postimg.cc/QV4pJM5w)

[![Screen-Shot-2024-02-14-at-8-19-30-PM.png](https://i.postimg.cc/htNmD60L/Screen-Shot-2024-02-14-at-8-19-30-PM.png)](https://postimg.cc/Sn7RVZ3R)

## Adding Tests

Many of Yoga's tests are automatically generated, using HTML fixtures describing node structure. These are rendered in Chrome to generate an expected layout result for the tree. New fixtures can be added to `gentest/fixtures`.

```html
<div id="my_test" style="width: 100px; height: 100px; align-items: center;">
  <div style="width: 50px; height: 50px;"></div>
</div>
```

To generate new tests from added fixtures:

1. Ensure you have [yarn classic](https://classic.yarnpkg.com) installed.
2. Run `yarn install` to install dependencies for the test generator.
3. Run `yarn gentest` in the `yoga` directory.

## Debugging

Yoga provides a VSCode "launch.json" configuration which allows debugging unit tests. Simply add your breakpoints, and run "Debug C++ Unit tests (lldb)" (or "Debug C++ Unit tests (vsdbg)" on Windows).

Please take a look at the following link if you need further instruction for debugging.
[in-depth debugging instructions](https://code.visualstudio.com/docs/editor/debugging)

## License 
This program is licensed by GPL License. Therefore, the general public is allowed to contribute to this code. 
