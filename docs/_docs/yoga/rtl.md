---
docid: rtl
title: RTL
layout: docs
permalink: /docs/rtl/
---

The web has limited support for Right-to-Left (RTL) layouts. It does a pretty good job when it comes to text alignment and text rendering, but lacks the features needed to build fully RTL compatible UIs. Therefore, Yoga has adopted `Start` and `End` values for `Margin`, `Padding`, `Border`, and `Position` properties.


## Direction

With `Start` and `End`, you can specify these properties in your UI without having to think about whether your item will show up on the left or the right side of the screen (depending on the person's language setting). Yoga automatically handles this for you.

The `Direction` property controls this behavior. `Direction` defaults to `Inherit` on all nodes except the root which defaults to `LTR`. It is up to you to detect the user's preferred direction (most platforms have a standard way of doing this) and setting this direction on the root of your layout tree.
