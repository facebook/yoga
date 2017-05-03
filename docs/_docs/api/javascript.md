---
docid: javascript
title: Javascript
layout: docs
permalink: /docs/api/javascript/
---

The `yoga-layout` module offers two different implementations of Yoga. The first one is a native Node module, and the second one is an asm.js fallback that can be used when native compilation isn't an option - such as web browsers.

> Because this module is compiled from a C++ codebase, the function prototypes below will use the C++-syntax. Nevertheless, the corresponding methods all exist on the JS side, with the same arguments (`Node *` being a node object).

### Installing
Installing through NPM
```sh
npm install yoga-layout
```
By default this will install the library and try to build for all platforms (node, browser asm, and standalone webpack). You may receive errors if you do not have the required platform development tools already installed. To preset the platform you'd like to build for you can set a .npmrc property first.
```sh
npm config set yoga-layout:platform standalone
```
This will now only run the standalone webpack build upon install.

### Build Platforms

| name           | description                                     |
|----------------|-------------------------------------------------|
| all (default)  | Builds all of these platforms.                  |
| browser        | Builds asm js browser version.                  |
| node           | Builds node js version.                         |
| standalone     | Runs webpack.                                   |
| none           | Does nothing. You can use the prepackaged libs. |

### Lifecycle

Create a node via `Yoga.Node.create()`, and destroy it by using its `free()` or `freeRecursive()` method. Note that unlike most objects in your Javascript applications, your nodes will not get automatically garbage collected, which means that it is especially important you keep track of them so you can free them when you no longer need them.

<script src="http://gist-it.appspot.com/facebook/yoga/raw/master/javascript/sources/Node.hh?slice=14:17"></script>

### Children

The following methods help manage the children of a node.

<script src="http://gist-it.appspot.com/facebook/yoga/raw/master/javascript/sources/Node.hh?slice=114:126"></script>

### Style getters & setters

The large part of Yoga's API consists of properties, setters, and getters for styles. These all follow the same general structure. Bellow are the function and enums used to control the various styles. For an in depth guide to how each style works see the getting started guide.

<script src="http://gist-it.appspot.com/facebook/yoga/raw/master/javascript/sources/Node.hh?slice=41:77"></script>

<script src="http://gist-it.appspot.com/facebook/yoga/raw/master/javascript/sources/Node.hh?slice=79:112"></script>

### Layout results

Once you have set up a tree of nodes with styles you will want to get the result of a layout calculation. Call `calculateLayout()` perform layout calculation. Once this function returns the results of the layout calculation is stored on each node. Traverse the tree and retrieve the values from each node.

<script src="http://gist-it.appspot.com/facebook/yoga/raw/master/javascript/sources/Node.hh?slice=142:157"></script>

### Custom measurements

Certain nodes need to ability to measure themselves, the most common example is nodes which represent text. Text has an intrinsic size and requires measuring itself to determine that size. This is not something Yoga can do as it requires relying on the host system's text rendering engine.

- Call `markDirty()` if a node with a custom text measurement function needs to be re-measured during the next layout pass.
- Note that in the prototype below, `Size` is an object that contain both `width` and `height` properties.

> A measure function can only be attached to a leaf node in the hierarchy.

<script src="http://gist-it.appspot.com/facebook/yoga/raw/master/javascript/sources/Node.hh?slice=128:131"></script>

### Experiments

Yoga has the concept of experiments. An experiment is a feature which is not yet stable. To enable a feature use the following functions. Once a feature has been tested and is ready to be released as a stable API we will remove its feature flag.

<script src="http://gist-it.appspot.com/facebook/yoga/raw/master/javascript/sources/global.hh?slice=3:4"></script>

### Example Usage

```javascript
import yoga, { Node } from 'yoga-layout';

let rootNode = Node.create();
rootNode.setWidth(1024);
rootNode.setHeight(768);
rootNode.setPadding(yoga.EDGE_ALL, 20);
rootNode.setDisplay(yoga.DISPLAY_FLEX);
rootNode.setFlexDirection(yoga.FLEX_DIRECTION_ROW);

let child1 = Node.create();
child1.setWidth(250);
child1.setHeight(400);
child1.setFlex(0);

let child2 = Node.create();
child2.setWidth(400);
child2.setHeight(500);
child2.setFlex(1);

rootNode.insertChild(child1, 0);
rootNode.insertChild(child2, 1);

rootNode.calculateLayout(1024, 768, yoga.DIRECTION_LTR);

console.log(`root pos: {${rootNode.getComputedLeft()}, ${rootNode.getComputedTop()}, ${rootNode.getComputedWidth()}, ${rootNode.getComputedHeight()}}`);
for (let i = 0, l = rootNode.getChildCount(); i < l; ++i) {
    let child = rootNode.getChild(i);
    console.log(`child ${i} pos: {${child.getComputedLeft()}, ${child.getComputedTop()}, ${child.getComputedWidth()}, ${child.getComputedHeight()}}`);
    console.log(child.getComputedLayout().toString());
}

rootNode.removeChild(child1);
rootNode.removeChild(child2);

console.log(`There are ${yoga.getInstanceCount()} nodes`);
Node.destroy(child2);
console.log(`There are ${yoga.getInstanceCount()} nodes left`);
child1.free();
console.log(`There are ${yoga.getInstanceCount()} nodes left`);
rootNode.freeRecursive();
console.log(`There are ${yoga.getInstanceCount()} nodes left`);

---------------------------------
Output:

root pos: {0, 0, 1024, 768}
child 0 pos: {20, 20, 250, 400}
<Layout#20:0;20:0;250:400>
child 1 pos: {270, 20, 734, 500}
<Layout#270:0;20:0;734:500>
There are 3 nodes
There are 2 nodes left
There are 1 nodes left
There are 0 nodes left

```
