---
docid: justify-content
title: Justify content
layout: docs
permalink: /docs/justify-content/
---

The `JustifyContent` property describes how to align children within the main axis of a container. For example, you can use this property to center a child horizontally within a container with `FlexDirection = Row` or vertically within a container with `FlexDirection = Column`.

`JustifyContent` accepts 1 of the following 5 options:

* `FlexStart` (default)
* `FlexEnd`
* `Center`
* `SpaceBetween`
* `SpaceAround`

#### JustifyContent = FlexStart

<div class="yoga" style="align-items: flex-start;">
  <div class="yoga sample" style="background-color: white; padding: 20px; flex-direction: row; width: 500px;">
    <div class="yoga" style="background-color: #303846; width: 50px; height: 50px; margin-right: 20px;"></div>
    <div class="yoga" style="background-color: #303846; width: 50px; height: 50px;"></div>
  </div>
</div>

#### JustifyContent = FlexEnd

<div class="yoga" style="align-items: flex-start;">
  <div class="yoga sample" style="background-color: white; padding: 20px; flex-direction: row; width: 500px; justify-content: flex-end;">
    <div class="yoga" style="background-color: #303846; width: 50px; height: 50px; margin-right: 20px;"></div>
    <div class="yoga" style="background-color: #303846; width: 50px; height: 50px;"></div>
  </div>
</div>

#### JustifyContent = Center

<div class="yoga" style="align-items: flex-start;">
  <div class="yoga sample" style="background-color: white; padding: 20px; flex-direction: row; width: 500px; justify-content: center;">
    <div class="yoga" style="background-color: #303846; width: 50px; height: 50px; margin-right: 20px;"></div>
    <div class="yoga" style="background-color: #303846; width: 50px; height: 50px;"></div>
  </div>
</div>

#### JustifyContent = SpaceBetween

<div class="yoga" style="align-items: flex-start;">
  <div class="yoga sample" style="background-color: white; padding: 20px; flex-direction: row; width: 500px; justify-content: space-between;">
    <div class="yoga" style="background-color: #303846; width: 50px; height: 50px;"></div>
    <div class="yoga" style="background-color: #303846; width: 50px; height: 50px;"></div>
  </div>
</div>

#### JustifyContent = SpaceAround

<div class="yoga" style="align-items: flex-start;">
  <div class="yoga sample" style="background-color: white; padding: 20px; flex-direction: row; width: 500px; justify-content: space-around;">
    <div class="yoga" style="background-color: #303846; width: 50px; height: 50px;"></div>
    <div class="yoga" style="background-color: #303846; width: 50px; height: 50px;"></div>
  </div>
</div>
