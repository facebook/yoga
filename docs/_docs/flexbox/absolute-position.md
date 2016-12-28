---
docid: absolute-position
title: Absolute positioning
layout: docs
permalink: /docs/absolute-position/
---

The `Position` property tells Flexbox how you want your item to be positioned within its parent. There are 2 options:

* `Relative` (default)
* `Absolute`

An item marked with `Position = Absolute` is positioned absolutely in regards to its parent. This is done through 6 properties:

* `Left` - controls the distance a child's left edge is from the parent's left edge
* `Top` - controls the distance a child's top edge is from the parent's top edge
* `Right` - controls the distance a child's right edge is from the parent's right edge
* `Bottom` - controls the distance a child's bottom edge is from the parent's bottom edge
* `Start` - controls the distance a child's start edge is from the parent's start edge
* `End` - controls the distance a child's end edge is from the parent's end edge

Using these options you can control the size and position of an absolute item within its parent. Because absolutely positioned children don't effect their siblings layout `Position = Absolute` can be used to create overlays and stack children in the Z axis.

#### Position = Absolute; Start = 0; Top = 0; Width = 50; Height = 50;

<div class="yoga" style="align-items: flex-start;">
  <div class="yoga sample" style="background-color: white; width: 300px; height: 300px;">
    <div class="yoga" style="background-color: #303846; width: 50px; height: 50px; left: 0px; top: 0px; position: absolute;"></div>
  </div>
</div>

#### Position = Absolute; Start = 10; Top = 10; End = 10; Bottom = 10;

<div class="yoga" style="align-items: flex-start;">
  <div class="yoga sample" style="background-color: white; width: 300px; height: 300px;">
    <div class="yoga" style="background-color: #303846; left: 10px; top: 10px; bottom: 10px; right: 10px; position: absolute;"></div>
  </div>
</div>
