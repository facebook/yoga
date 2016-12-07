---
docid: java
title: Java
layout: docs
permalink: /docs/api/java/
---
`YogaNode` is the main object you will be interfacing with when using Yoga in Java. `YogaNode` is a thin [JNI](https://en.wikipedia.org/wiki/Java_Native_Interface) wrapper around the core Yoga library.

### Lifecycle

Create a `YogaNode` via its default constructor and use `reset` if you want to pool and re-use nodes. The native memory of a `YogaNode` will automatically be freed when the node is garbage collected.

<script src="https://gist.github.com/emilsjolander/8775de8c778eb99a05a38e8257f0b4a7.js"></script>

### Children

The following methods help manage the children of a node.

<script src="https://gist.github.com/emilsjolander/5d1c64d8d3be7f7942435c4f5bec45a5.js"></script>

### Style getters & setters

The large part of Yoga's API consists of setters and getters for styles. These all follow the same general structure. Bellow are the function and enums used to control the various styles. For an in depth guide to how each style works see the getting started guide.

<script src="https://gist.github.com/emilsjolander/f94ca2aa69441a3060a7c9f5126f202f.js"></script>

### Layout results

Once you have set up a tree of nodes with styles you will want to get the result of a layout calculation. Call `calculateLayout()` perform layout calculation. Once this function returns the results of the layout calculation is stored on each node. Traverse the tree and retrieve the values from each node.

<script src="https://gist.github.com/emilsjolander/613a80ae11abce423a4806521e1e315b.js"></script>

### Custom measurements

Certain nodes need to ability to measure themselves, the most common example is nodes which represent text. Text has an intrinsic size and requires measuring itself to determine that size. This is not something Yoga can do as it requires relying on the host system's text rendering engine.

- Call `dirty()` if a node with a custom text measurement function needs to be re-measured during the next layout pass.

> A measure function can only be attached to a leaf node in the hierarchy.

<script src="https://gist.github.com/emilsjolander/70fd958b87647abbba604956709a9026.js"></script>

### Data

Data is important when integrating Yoga into another layout system. Data allows you to associate another object with a `YogaNode`. This data can then be retrieved from a `YogaNode` when for example its measure function is called. This is what enables Yoga to rely on the Android system implementations of text measurement in React Native.

<script src="https://gist.github.com/emilsjolander/3f10f3fa91120960b71783780f528973.js"></script>

### Logging

Yoga will by default log to stdout and stderr (or logcat on Android). You may however customize this to instead log to your own logger.

<script src="https://gist.github.com/emilsjolander/6d012f5d48be0e98b7f9c2225c358f6e.js"></script>

### Experiments

Yoga has the concept of experiments. An experiment is a feature which is not yet stable. To enable a feature use the following functions. Once a feature has been tested and is ready to be released as a stable API we will remove its feature flag.

<script src="https://gist.github.com/emilsjolander/97b2500918687826cdfe9429638f2d57.js"></script>
