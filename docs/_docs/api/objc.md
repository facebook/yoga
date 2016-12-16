---
docid: objc
title: Objective-C
layout: docs
permalink: /docs/api/objc/
---

> The Objective-C API is very new and still in rapid development. Please use it and [report issues, bugs or feedback](https://github.com/facebook/yoga/issues). We hope to stabilize the API over the next couple weeks / months.

Yoga for Objective-C is implemented as a [category](https://developer.apple.com/library/content/documentation/General/Conceptual/DevPedia-CocoaCore/Category.html) on [UIView](https://developer.apple.com/reference/uikit/uiview). We try to rely on the existing `UIView` properties and initializers where possible, making the Yoga API smaller for Objective-C than for other languages.

### Lifecycle

As with any `UIView` instantiate it using `-(instancetype)initWithFrame:(CGRect)frame`. With Yoga for Objective-C the frame is actually how you set the width and the height of the Yoga node, just like any other `UIView`.

Because Yoga is implemented as a category we need some way to mark the view as using Yoga as you might not want Yoga to control layout of your whole app, this is especially important if you are migrating an existing app to use Yoga. The property decides during layout/sizing whether or not `yg_*` properties should be applied. Defaults to `NO`.

<script src="https://gist.github.com/emilsjolander/b95467f51b945e906d39b66e44999806.js"></script>

### Children

Yoga relies on `UIView` subviews to build up its internal layout tree. However using properties such as `yg_includeInLayout` a View can exclude itself from layout. Therefor we provide the following method to query the number of children which are laid out using Yoga.

<script src="https://gist.github.com/emilsjolander/253d69b12bef2ee1ec899ace81b768a6.js"></script>

### Style setters

The large part of Yoga's API consists of setters for styles. These all follow the same general structure. Bellow are the function and enums used to control the various styles. For an in depth guide to how each style works see the getting started guide.

<script src="https://gist.github.com/emilsjolander/e7c7732b9465173335d2e019a6bc5941.js"></script>

### Layout
- `yg_includeInLayout` decides if we should include this view when calculating layout. Defaults to `YES`.
- `yg_intrinsicSize` returns the size of the view if no constraints were given. This is equivalent to calling `[view sizeThatFits:CGSizeMake(CGFLOAT_MAX, CGFLOAT_MAX)]`.
- `yg_applyLayout` performs layout calculation and update the frames of the views in the hierarchy with the results.
- `yg_resolvedDirection` returns the resolved layout direction of this view. Either `YGDirectionRTL` or `YGDirectionLTR`.

<script src="https://gist.github.com/emilsjolander/437661e872c1f9106b728419d5ea49e9.js"></script>
