---
docid: javascript
title: Javascript
layout: docs
permalink: /docs/api/javascript/
---

The `yoga-layout` module offers two different implementations of Yoga. The first one is a native Node module, and the second one is an asm.js fallback that can be used when native compilation isn't an option - such as web browsers.

> Because this module is compiled from a C++ codebase, the function prototypes below will use the C++-syntax. Nevertheless, the corresponding methods all exist on the JS side, with the same arguments (`Node *` being a node object).

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
