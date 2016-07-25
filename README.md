CSSLayout [![Build Status](https://travis-ci.org/facebook/css-layout.svg?branch=master)](https://travis-ci.org/facebook/css-layout)
====================================================================================================
```
css-layout is currently in the process of big changes. If you are looking at using the latest stable version please have a look at the `deprecated` branch. This includes a js version and a C-sharp version not currently available on master.
```

CSSLayout is a cross platform implementation of the flexbox specification. CSSLayout targets native mobile development and is therefor disconnected from the web browser. CSSLayout is implemented in C for portability reasons and uses JNI to expose public methods to Java.

See CSSLayout/CSSLayout.h for a look at the public API being exposed.

Building
--------
CSSLayout builds with buck (buckbuild.com). To build run `buck build //:CSSLayout` and run `buck test //:CSSLayout` to run the test suite.
