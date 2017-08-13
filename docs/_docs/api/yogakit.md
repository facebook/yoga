---
docid: yogakit
title: YogaKit
layout: docs
permalink: /docs/api/yogakit/
---

> The YogaKit API is still in rapid development. Please use it and [report issues, bugs or feedback](https://github.com/facebook/yoga/issues).

YogaKit is a Objective-C (and Swift-compatible) wrapper for Yoga. It allows iOS Developers to manage the layout of their views using the power of Yoga.

Layout configuration is done via the [YGLayout](https://github.com/facebook/yoga/blob/master/YogaKit/Source/YGLayout.h) object. YogaKit exposes `YGLayout` via a [category](https://developer.apple.com/library/content/documentation/General/Conceptual/DevPedia-CocoaCore/Category.html) on [UIView](https://developer.apple.com/reference/uikit/uiview).

### Lifecycle

As with any `UIView`, instantiate it using `-(instancetype)initWithFrame:(CGRect)frame`. YogaKit uses the frame of the parent view to determine the space that is available for children in layout.

### Children

Yoga relies on `UIView` subviews to build up its internal layout tree. However, a subview can exclude itself from layout by setting the `isIncludedInLayout` property on `YGLayout` to `NO`.

It is also possible to query the number of children **included** in layout via `numberOfChildren`.

### Layout
To apply a layout to a view (and its' subviews) you need to call `[view.yoga applyLayoutPreservingOrigin:NO]`. This will do a layout calculation (if needed) and apply the calculated frames to every view included in the layout.

In the event that you need to another layout pass on a view you can mark it dirty via `[view.yoga markDirty]`.
