# Yoga [![Support Ukraine](https://img.shields.io/badge/Support-Ukraine-FFD500?style=flat&labelColor=005BBB)](https://opensource.fb.com/support-ukraine) [![CocoaPods](https://img.shields.io/cocoapods/v/Yoga.svg)](http://cocoapods.org/pods/Yoga) [![npm](https://img.shields.io/npm/v/yoga-layout.svg)](https://www.npmjs.com/package/yoga-layout) [![Maven Central](https://img.shields.io/maven-central/v/com.facebook.yoga/yoga)](https://search.maven.org/artifact/com.facebook.yoga/yoga)

Yoga is an embeddable and performant flexbox layout engine with bindings for multiple languages. It provides a high-performance solution for creating responsive layouts across web and mobile applications.

## Table of Contents
- [Introduction](#introduction)
- [Prerequisites](#prerequisites)
- [Installation](#installation)
- [Building](#building)
- [Running Unit Tests](#running-unit-tests)
- [Adding Tests](#adding-tests)
- [Debugging](#debugging)
- [Contributing](#contributing)
- [License](#license)

## Introduction
Yoga implements the flexbox layout system in C++, making it a crucial component for layout and styling in projects like React Native.

Its embeddable design allows for seamless integration into various platforms and programming languages.

## Prerequisites
Before you begin, ensure you have the following installed:

- CMake (3.18 or above): [Download it here](https://cmake.org/download/).
- Ninja (Optional, for faster builds): [Install it following the guide here](https://ninja-build.org/).
- A C++20 compatible compiler.

On Linux, you can install these using:
sudo apt-get install cmake ninja-build g++

On Windows, install Visual Studio with C++ build tools or Microsoft Visual C++ Build Tools.

## Installation
To set up the Yoga project, follow these steps:
Clone the Repository
git clone https://github.com/facebook/yoga.git
cd yoga

## Building
Generate the build files using CMake. If Ninja is installed, you can utilize it for faster builds:
cmake -S . -B build -G Ninja
cmake --build build --config Release

## Running Unit Tests
After building the project, you can run the unit tests to ensure everything works as expected:
cd build
./unit_tests <Debug|Release>

## Adding Tests
Many of Yoga's tests are automatically generated using HTML fixtures that describe node structures. These fixtures are rendered in Chrome to generate an expected layout result for the tree.

To add new fixtures, simply include them in 'gentest/fixtures':
<div id="my_test" style="width: 100px; height: 100px; align-items: center;">
  <div style="width: 50px; height: 50px;"></div>
</div>

To generate new tests from added fixtures:
- Ensure you have yarn classic installed.
- Run 'yarn install' to install dependencies for the test generator.
- Run 'yarn gentest' in the yoga directory.

## Debugging
Yoga includes a pre-configured launch.json for VSCode, allowing you to debug unit tests easily.
- Open the project in VSCode.
- Add breakpoints in your code.
- Run "Debug C++ Unit Tests (lldb)" or "Debug C++ Unit Tests (vsdbg)" on Windows.

## Contributing
We welcome contributions to Yoga! To get started, follow these steps:

Step 1: Fork the Repository
Fork the Yoga repository.
Clone your fork:
git clone https://github.com/your-username/yoga.git

Step 2: Create a Feature Branch
Create a new branch for your feature or bugfix:
git checkout -b my-feature-branch

Step 3: Make Changes and Test
Make sure to:
- Follow the project's coding style.
- Write unit tests for any new functionality.
- Run all existing tests to ensure nothing breaks:
./unit_tests

Step 4: Submit Your Pull Request
When you're ready to submit your changes:
- Push your branch to GitHub:
git push origin my-feature-branch
- Open a Pull Request on the Yoga repository, ensuring your PR includes:
- - A clear title, e.g., "Enhanced README Documentation and Added Setup Guide."
- - A detailed description of the changes.
- - Links to any related issues, if applicable.

## License
Yoga is licensed under the BSD License. See the LICENSE file for more details.