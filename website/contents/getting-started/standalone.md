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

The JavaScript bindings for Yoga can be used from node.js and within the browser.
When using Yoga from node.js the native library is used, in browsers a pure JS
version is used (cross-compiled using [emscripten](http://kripken.github.io/emscripten-site/)).

```
$> yarn add yoga-layout
```

This is an example on how to use Yoga in JavaScript, for a full API reference,
have a look at the [flow-type definitions](https://github.com/facebook/yoga/blob/master/javascript/sources/entry-common.js#L123).

```js
import yoga, {Node} from 'yoga-layout';

const root = Node.create();
root.setWidth(500);
root.setHeight(300);
root.setJustifyContent(yoga.JUSTIFY_CENTER);

const node1 = Node.create();
node1.setWidth(100);
node1.setHeight(100);

const node2 = Node.create();
node2.setWidth(100);
node2.setHeight(100);

root.insertChild(node1, 0);
root.insertChild(node2, 1);

root.calculateLayout(500, 300, yoga.DIRECTION_LTR);
console.log(root.getComputedLayout());
// {left: 0, top: 0, width: 500, height: 300}
console.log(node1.getComputedLayout());
// {left: 150, top: 0, width: 100, height: 100}
console.log(node2.getComputedLayout());
// {left: 250, top: 0, width: 100, height: 100}
```

### iOS

```
pod 'YogaKit', '~> 1.7'
```

## Including Yoga From Source

If you plan to include Yoga from Source in a C++ project then all you have to do is inlude
the top level `yoga` folder. Make sure to look at the top level `BUCK` file to ensure you build
using the same compiler flags.
