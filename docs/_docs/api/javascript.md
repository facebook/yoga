---
docid: javascript
title: Javascript
layout: docs
permalink: /docs/api/javascript/
---

The `yoga-layout` module offers two different implementations of Yoga. The first one is a native Node module, and the second one is an asm.js fallback that can be used when native compilation isn't an option - such as web browsers.

### Lifecycle

Create a node via `Yoga.Node.create()`, and destroy it by using its `free()` or `freeRecursive()` method. Note that unlike most objects in your Javascript applications, your nodes will not get automatically garbage collected, which means that it is especially important you keep track of them so you can free them when you no longer need them.

<script src="https://gist.github.com/emilsjolander/ce73212ee5fdb543d463822c3dd172b4.js"></script>

### Children

The following methods help manage the children of a node.

<script src="https://gist.github.com/emilsjolander/2b0ea738d3c24644fa98910b276620e4.js"></script>

### Style getters & setters

The large part of Yoga's API consists of properties, setters, and getters for styles. These all follow the same general structure. Bellow are the function and enums used to control the various styles. For an in depth guide to how each style works see the getting started guide.

<script src="https://gist.github.com/emilsjolander/a84208768e0006b8421a322c40f98539.js"></script>

### Layout results

Once you have set up a tree of nodes with styles you will want to get the result of a layout calculation. Call `calculateLayout()` perform layout calculation. Once this function returns the results of the layout calculation is stored on each node. Traverse the tree and retrieve the values from each node.

<script src="https://gist.github.com/emilsjolander/b50acf9fc0877affeb0fc3e55b5c6b4c.js"></script>

### Custom measurements

Certain nodes need to ability to measure themselves, the most common example is nodes which represent text. Text has an intrinsic size and requires measuring itself to determine that size. This is not something Yoga can do as it requires relying on the host system's text rendering engine.

- Call `markDirty()` if a node with a custom text measurement function needs to be re-measured during the next layout pass.

> A measure function can only be attached to a leaf node in the hierarchy.

<script src="https://gist.github.com/emilsjolander/57178307f515e5ea1ccfbedc05df429b.js"></script>

### Experiments

Yoga has the concept of experiments. An experiment is a feature which is not yet stable. To enable a feature use the following functions. Once a feature has been tested and is ready to be released as a stable API we will remove its feature flag.

<script src="https://gist.github.com/emilsjolander/97b2500918687826cdfe9429638f2d57.js"></script>
