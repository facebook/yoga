---
docid: aspect-ratio
title: Aspect ratio
layout: docs
permalink: /docs/aspect-ratio/
---

`AspectRatio` is a property introduced by Yoga. `AspectRatio` solves the problem of knowing one dimension of an element and an aspect ratio, this is very common when it comes to videos, images, and other media types. `AspectRatio` accepts any floating point value > 0, the default is undefined. `AspectRatio` can apply to either the width or the height of an item, it depends on which dimension is fixed. `AspectRatio` Also respects the `Min` and `Max` dimensions of an item.

- If an item has a `Width` set then `AspectRatio` controls the item's height.
- If an item has a `Height` set then `AspectRatio` controls the item's width.
- If an item has a `FlexBasis` set then `AspectRatio` controls the item's cross axis dimension.
- If an item's alignment is `Stretch` and its main axis is undefined then `AspectRatio` controls the item's main axis dimension.
- If an item has `FlexGrow` or `FlexShrink` set then `AspectRatio` controls the item's cross axis dimension if it is undefined.
- If both dimensions of an item are fixed then `AspectRatio` is ignored.

#### Width = 100; AspectRatio = 2;

<div class="yoga" style="align-items: flex-start;">
  <div class="yoga sample" style="background-color: white; width: 300px; height: 300px;">
    <div class="yoga" style="background-color: #303846; width: 100px; height: 200px;"></div>
  </div>
</div>

#### Width = 100; AspectRatio = 0.5;

<div class="yoga" style="align-items: flex-start;">
  <div class="yoga sample" style="background-color: white; width: 300px; height: 300px;">
    <div class="yoga" style="background-color: #303846; width: 100px; height: 50px;"></div>
  </div>
</div>

#### FlexDirection = Row; FlexGrow = 1; AspectRatio = 0.5;

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
