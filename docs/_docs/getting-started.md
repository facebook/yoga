---
docid: getting-started
title: Getting Started
layout: docs
permalink: /docs/getting-started/
---

## Installation

Installation of Yoga is currently a manual process. We have plans on bringing Yoga to the many available package management systems (e.g., [Yarn](https://yarnpkg.com/), [Gradle](https://gradle.org/), [Cocoapods](https://cocoapods.org/)), but we do not have a target date at this time. We would greatly appreciate [community contributions here](https://github.com/facebook/yoga/pulls).

### Getting the Code

For now we recommend including Yoga as a [git submodule](https://git-scm.com/docs/git-submodule) in your project. Once done, you can either build Yoga using Buck (detailed [below](#building-with-buck)) or integrate it into your existing build system by including the C library from the [root `yoga` directory](https://github.com/facebook/yoga/tree/master/yoga) as well as the [language bindings](https://github.com/facebook/yoga) (e.g., Java, C#) you wish to use.

### Running the Example

Yoga ships with an [iOS example](https://github.com/facebook/yoga/tree/master/YogaKit/YogaKitSample). To get it running:

<script src="https://gist.github.com/emilsjolander/903b16185b24c957acc4cd250c6e73d9.js"></script>

### Building with Buck

Yoga uses [Buck](https://buckbuild.com/) as its build system. Buck is not required for using Yoga, but, if you already use Buck, then integrating Yoga is very simple.

If you are using Buck all you need to do is reference the language bindings you want to use in your `BUCK` file.

<script src="https://gist.github.com/emilsjolander/895b4ec79425882b8d4676b6545d6943.js"></script>
