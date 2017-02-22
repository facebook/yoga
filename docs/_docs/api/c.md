---
docid: c
title: C
layout: docs
permalink: /docs/api/c/
---
`YGNodeRef` is the main object you will be interfacing with when using Yoga in C. `YGNodeRef` is a pointer to an internal `YGNode` struct.

### Lifecycle

The following functions control the lifecycle of a `YGNodeRef`.

<script src="https://gist.github.com/emilsjolander/99e454d04df4765147f407bde131feca.js"></script>

- `YGNodeReset` will reset a node to its initial state so it can be re-used without needing to re-allocate a new node.
- `YGNodeFreeRecursive` is mostly used for testing and will free not only the node itself but also its children.

### Children

The following functions help manage the children of a node.

<script src="https://gist.github.com/emilsjolander/7e162314294087bb78817c064d345afb.js"></script>

### Style getters & setters

The large part of Yoga's API consists of setters and getters for styles. These all follow the same general structure. Bellow are the function and enums used to control the various styles. For an in depth guide to how each style works see the getting started guide.

<script src="https://gist.github.com/emilsjolander/74913a3326d952ff5a65dabe5ce4baf8.js"></script>

### Layout results

Once you have set up a tree of nodes with styles you will want to get the result of a layout calculation. Call `YGNodeCalculateLayout` with the desired width and height or `YGUndefined` to perform the layout calculation. Once this function returns the results of the layout calculation is stored on each node. Traverse the tree and retrieve the values from each node.

<script src="https://gist.github.com/emilsjolander/7c7c9c61b69daff5b925719065fb0dc9.js"></script>

### Custom measurements

Certain nodes need the ability to measure themselves, the most common example is nodes which represent text. Text has an intrinsic size and requires measuring itself to determine that size. This is not something Yoga can do as it requires relying on the host system's text rendering engine.

- Call `YGNodeMarkDirty` if a node with a custom text measurement function needs to be re-measured during the next layout pass.

> A measure function can only be attached to a leaf node in the hierarchy.

<script src="https://gist.github.com/emilsjolander/73f9118d8bd27f9cb3744c08f1e53a32.js"></script>

### Context

Context is important when integrating Yoga into another layout system. Context allows you to associate another object with a `YGNodeRef`. This context can then be retrieved from a `YGNodeRef` when for example its measure function is called. This is what enables Yoga to rely on the Android and iOS system implementations of text measurement in React Native.

<script src="https://gist.github.com/emilsjolander/c3d23a1b880d59627e959f3447a9511b.js"></script>

### Logging

Yoga will by default log to stdout and stderr. You may however customize this to instead log to your own logger.

<script src="https://gist.github.com/emilsjolander/b538718ffd7a55efc80845468e0f063e.js"></script>

### Experiments

Yoga has the concept of experiments. An experiment is a feature which is not yet stable. To enable a feature use the following functions. Once a feature has been tested and is ready to be released as a stable API we will remove its feature flag.

<script src="https://gist.github.com/emilsjolander/002516a55e10947e4bdcf5484eee8745.js"></script>

### Custom allocators

You may want to swap out the allocator used in Yoga. These functions allow that.

<script src="https://gist.github.com/emilsjolander/f45053d4f09a9faaf94a8fc071f0224f.js"></script>

### Printing

Yoga has some hooks to print debug information while calculating layout. With the printing APIs you can add additional information to a node when it is printed.

<script src="https://gist.github.com/emilsjolander/c9fbaba914d699ecc91841f4f5515f20.js"></script>
