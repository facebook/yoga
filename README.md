# **Yoga** [![CocoaPods](https://img.shields.io/cocoapods/v/YogaKit.svg)](http://cocoapods.org/pods/YogaKit) [![npm](https://img.shields.io/npm/v/yoga-layout.svg)](https://www.npmjs.com/package/yoga-layout) [![bintray](https://img.shields.io/bintray/v/facebook/maven/com.facebook.yoga:yoga.svg)](https://bintray.com/facebook/maven/com.facebook.yoga%3Ayoga/_latestVersion) [![NuGet](https://img.shields.io/nuget/v/Facebook.Yoga.svg)](https://www.nuget.org/packages/Facebook.Yoga)

## **Table of Contents**

### 1. [**About**](#about)
### 2. [**Testing**](#testing)
### 3. [**Benchmarks**](#benchmarks)
### 4. [**Build Platforms**](#build-platforms)
### 5. [**Documentation**](#documentation)
### 6. [**Contributing**](#contributing)
### 7. [**Code of Conduct**](#code-of-conduct)
### 8. [**License**](#license)
### 9. [**Community**](#community)

## **About**
### **Building**
Yoga builds with [**Buck**](https://buckbuild.com). Make sure you install Buck before contributing to Yoga. Yoga's main implementation is in C++, with bindings to supported languages and frameworks. When making changes to Yoga please ensure the changes are also propagated to these bindings when applicable.

## **Testing**
We rely on [**gtest**](https://github.com/google/googletest) as a submodule for testing. After cloning Yoga run:

```
git submodule init
```
Then:

```
git submodule update
```

For any changes you make, make sure all tests are passing. If you make any fixes or additions to the library, add tests for the changes, this won't break anything in the future. Tests are located in the **`tests`** directory. 
Run the tests with: **`buck test //:yoga`**.

Instead of manually writing a test that ensures parity with web implementations of Flexbox, you can run **`gentest/gentest.rb`** to generate a test for you. 

You can write HTML you want to verify in Yoga, in **`gentest/fixtures`** folder, such as the following:

```html
<div id="my_test" style="width: 100px; height: 100px; align-items: center;">
  <div style="width: 50px; height: 50px;"></div>
</div>
```

- Run **`gentest/gentest.rb`** to generate test code 
- Re-run **`buck test //:yoga`** to validate the behavior. 
One test case will be generated for every root `div` in the input html.

You may need to install the latest watir-webdriver gem (**`gem install watir-webdriver`**) and [**ChromeDriver**](https://sites.google.com/a/chromium.org/chromedriver/) to run **`gentest/gentest.rb`** Ruby script.

### **.NET**
.NET testing is not integrated in buck yet, you might need to set up .NET testing environment. We have a script which to launch C# test on macOS, **`csharp/tests/Facebook.Yoga/test_macos.sh`**.

## **Benchmarks**
Benchmarks are located in **`benchmark/YGBenchmark.c`**. You can run with **`buck run //benchmark:benchmark`**. 
If you think your change has affected performance please run this before and after your change to validate that nothing has regressed. Benchmarks are run on every commit in CI.

### **JavaScript**
Installing through NPM:

```sh
npm install yoga-layout
```
By default this will install the library and try to build for all platforms (node, browser asm, and standalone webpack). You may receive errors if you do not have the required platform development tools already installed. To preset the platform you'd like to build for you can set a .npmrc property first.
```sh
npm config set yoga-layout:platform standalone
```
This will now only run the standalone webpack build upon install.

## **Build Platforms**

| name           | description                                     |
|----------------|-------------------------------------------------|
| all (default)  | Builds all of these platforms.                  |
| browser        | Builds asm js browser version.                  |
| node           | Builds node js version.                         |
| standalone     | Runs webpack.                                   |
| none           | Does nothing. You can use the prepackaged libs. |

## **Documentation**

You can find Beagle's documentation on our [**website**][site].

Beagle's documentation discusses components, APIs, and topics that are specific to [**Beagle documentation**][b-docs].

[site]: https://usebeagle.io/
[b-docs]: https://docs.usebeagle.io/


## **Contributing**

If you want to contribute to this module, access our [**Contributing Guide**][contribute] to learn about our development process, how to propose bug fixes and improvements, and how to build and test your changes to Beagle.

[contribute]: https://github.com/ZupIT/beagle/blob/main/CONTRIBUTING.md

### **Developer Certificate of Origin - DCO**

 This is a security layer for the project and for the developers. It is mandatory.
 
 Follow one of these two methods to add DCO to your commits:
 
**1. Command line**
 Follow the steps: 
 **Step 1:** Configure your local git environment adding the same name and e-mail configured at your GitHub account. It helps to sign commits manually during reviews and suggestions.

 ```
git config --global user.name “Name”
git config --global user.email “email@domain.com.br”
```

**Step 2:** Add the Signed-off-by line with the `'-s'` flag in the git commit command:

```
$ git commit -s -m "This is my commit message"
```

**2. GitHub website**
You can also manually sign your commits during GitHub reviews and suggestions, follow the steps below: 

**Step 1:** When the commit changes box opens, manually type or paste your signature in the comment box, see the example:

```
Signed-off-by: Name < e-mail address >
```

For this method, your name and e-mail must be the same registered on your GitHub account.

## **Code of Conduct**

Please read the [**code of conduct**](https://github.com/ZupIT/beagle/blob/main/CODE_OF_CONDUCT.md).

## **License**

[**Apache License 2.0**](https://github.com/ZupIT/yoga/blob/master/LICENSE).

## **Community**
Do you have any question about Beagle? Let's chat in our [**forum**](https://forum.zup.com.br/).