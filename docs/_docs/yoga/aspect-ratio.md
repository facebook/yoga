---
docid: aspect-ratio
title: Aspect ratio
layout: docs
permalink: /docs/aspect-ratio/
---

`AspectRatio` is a property introduced by Yoga. `AspectRatio` solves the problem of knowing one dimension of an element and an aspect ratio, this is very common when it comes to videos, images, and other media types. `AspectRatio` accepts any floating point value > 0, the default is undefined.

- `AspectRatio` is defined as the ratio between the width and the height of a node e.g. if a node has an aspect ratio of 2 then its width is twice the size of its height.
- `AspectRatio` respects the `Min` and `Max` dimensions of an item.
- `AspectRatio` has higher priority than `FlexGrow`
- If `AspectRatio`, `Width`, and `Height` are set then the cross dimension is overridden.

#### Width = 100; AspectRatio = 2;

<div class="yoga" style="align-items: flex-start;">
  <div class="yoga sample" style="background-color: white; width: 300px; height: 300px;">
    <div class="yoga" style="background-color: #303846; width: 100px; height: 50px;"></div>
  </div>
</div>

#### Width = 100; AspectRatio = 0.5;

<div class="yoga" style="align-items: flex-start;">
  <div class="yoga sample" style="background-color: white; width: 300px; height: 300px;">
    <div class="yoga" style="background-color: #303846; width: 100px; height: 200px;"></div>
  </div>
</div>

#### FlexDirection = Row; FlexGrow = 1; AspectRatio = 2;

<div class="yoga" style="align-items: flex-start;">
  <div class="yoga sample" style="background-color: white; width: 300px; height: 300px; flex-direction: row;">
    <div class="yoga" style="background-color: #303846; flex-grow: 1; height: 150px;"></div>
  </div>
</div>

#### FlexDirection = Row; AlignItems = Stretch; AspectRatio = 0.5;

<div class="yoga" style="align-items: flex-start;">
  <div class="yoga sample" style="background-color: white; width: 300px; height: 300px; flex-direction: row;">
    <div class="yoga" style="background-color: #303846; width: 150px;"></div>
  </div>
</div>
