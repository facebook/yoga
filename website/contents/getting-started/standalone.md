---
path: "/getting-started/standalone"
title: "Standalone"
hasPlayground: false
---

# Standalone

Adding Yoga to a project is as simple as adding the dependency to your package manager of choice.

### Android

```groovy
dependencies {
	compile 'com.facebook.yoga.android:yoga-layout:x.x.x'
}
```

### Javascript

```
$> yarn add yoga-layout
```

### iOS

```
pod 'YogaKit', '~> 1.7'
```

## Including Yoga From Source

If you plan to include Yoga from Source in a C++ project then all you have to do is inlude
the top level `yoga` folder. Make sure to look at the top level `BUCK` file to ensure you build
using the same compiler flags.
