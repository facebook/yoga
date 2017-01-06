---
docid: alignment
title: Alignment
layout: docs
permalink: /docs/alignment/
---

### AlignItems

The `AlignItems` property describes how to align children along the cross axis of their container. `AlignItems` is very similar to `JustifyContent` but instead of applying to the main axis, it applies to the cross axis. There are 4 options for `AlignItems`:

* `Stretch` (default)
* `FlexStart`
* `FlexEnd`
* `Center`

The only non-obvious option of the four is `Stretch`. With `AlignItems = Stretch` you instruct children to match the size of their container in the cross axis.

#### AlignItems = Stretch

<div class="yoga" style="align-items: flex-start;">
  <div class="yoga sample" style="background-color: white; padding: 20px; flex-direction: row; width: 500px; height: 200px;">
    <div class="yoga" style="background-color: #303846; width: 50px; margin-right: 20px;"></div>
    <div class="yoga" style="background-color: #303846; width: 50px; "></div>
  </div>
</div>

#### AlignItems = FlexStart

<div class="yoga" style="align-items: flex-start;">
  <div class="yoga sample" style="background-color: white; padding: 20px; flex-direction: row; width: 500px; height: 200px; align-items: flex-start;">
    <div class="yoga" style="background-color: #303846; height: 50px; width: 50px; margin-right: 20px;"></div>
    <div class="yoga" style="background-color: #303846; height: 50px; width: 50px; "></div>
  </div>
</div>

#### AlignItems = FlexEnd

<div class="yoga" style="align-items: flex-start;">
  <div class="yoga sample" style="background-color: white; padding: 20px; flex-direction: row; width: 500px; height: 200px; align-items: flex-end;">
    <div class="yoga" style="background-color: #303846; height: 50px; width: 50px; margin-right: 20px;"></div>
    <div class="yoga" style="background-color: #303846; height: 50px; width: 50px; "></div>
  </div>
</div>

#### AlignItems = Center

<div class="yoga" style="align-items: flex-start;">
  <div class="yoga sample" style="background-color: white; padding: 20px; flex-direction: row; width: 500px; height: 200px; align-items: center;">
    <div class="yoga" style="background-color: #303846; height: 50px; width: 50px; margin-right: 20px;"></div>
    <div class="yoga" style="background-color: #303846; height: 50px; width: 50px; "></div>
  </div>
</div>

### AlignSelf

The `AlignSelf` property has the same options and effect as `AlignItems` but instead of affecting the children within a container, you can apply this property to a single child to change its alignment within its parent.

This property overrides any option set by the parent via the `AlignItems` property.

#### AlignItems = FlexEnd; AlignSelf = FlexStart;

<div class="yoga" style="align-items: flex-start;">
  <div class="yoga sample" style="background-color: white; padding: 20px; flex-direction: row; width: 500px; height: 200px; align-items: flex-end;">
    <div class="yoga" style="background-color: #303846; height: 50px; width: 50px; margin-right: 20px;"></div>
    <div class="yoga" style="background-color: #303846; height: 50px; width: 50px; align-self: flex-start;"></div>
  </div>
</div>

### AlignContent

The `AlignContent` property is used to control how multiple lines of content are aligned within a container which uses `FlexWrap = wrap`. There are 6 options:

* `FlexStart` (default)
* `FlexEnd`
* `Center`
* `Stretch`
* `SpaceBetween`
* `SpaceAround`

#### AlignContent = FlexEnd

<div class="yoga" style="align-items: flex-start;">
  <div class="yoga sample" style="background-color: white; padding: 20px; flex-direction: row; width: 300px; flex-wrap: wrap; height: 300px; align-content: flex-end;">
    <div class="yoga" style="background-color: #303846; width: 50px; height: 50px; margin-right: 20px; margin-bottom: 20px;"></div>
    <div class="yoga" style="background-color: #303846; width: 50px; height: 50px; margin-right: 20px; margin-bottom: 20px;"></div>
    <div class="yoga" style="background-color: #303846; width: 50px; height: 50px; margin-right: 20px; margin-bottom: 20px;"></div>
    <div class="yoga" style="background-color: #303846; width: 50px; height: 50px; margin-right: 20px;"></div>
    <div class="yoga" style="background-color: #303846; width: 50px; height: 50px; margin-right: 20px;"></div>
    <div class="yoga" style="background-color: #303846; width: 50px; height: 50px;"></div>
  </div>
</div>
