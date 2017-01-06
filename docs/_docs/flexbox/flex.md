---
docid: flex
title: Flex
layout: docs
permalink: /docs/flex/
---

### FlexGrow

The `FlexGrow` property describes how any space within a container should be distributed among its children along the main axis. After laying out its children, a container will distribute any remaining space according to the `FlexGrow` values specified by its children.

`FlexGrow` accepts any floating point value >= 0, with 0 being the default value. A container will distribute any remaining space among its children weighted by the child's `FlexGrow` value.

<div class="yoga" style="align-items: flex-start;">
  <div class="yoga sample" style="background-color: white; padding: 20px; flex-direction: row; width: 500px;">
    <div class="yoga" style="background-color: #303846; width: 50px; height: 50px; margin-right: 20px;"></div>
    <div class="yoga" style="background-color: #303846; width: 50px; height: 50px;"></div>
  </div>
</div>

<div class="yoga" style="align-items: flex-start;">
  <div class="yoga sample" style="background-color: white; padding: 20px; flex-direction: row; width: 500px;">
    <div class="yoga" style="background-color: #303846; width: 50px; height: 50px; margin-right: 20px;"></div>
    <div class="yoga" style="background-color: #303846; width: 50px; height: 50px; flex-grow: 1;">
      <span><span>FlexGrow = 1</span></span>
    </div>
  </div>
</div>

<div class="yoga" style="align-items: flex-start;">
  <div class="yoga sample" style="background-color: white; padding: 20px; flex-direction: row; width: 500px;">
    <div class="yoga" style="background-color: #303846; width: 50px; height: 50px; margin-right: 20px; flex-grow: 1;">
      <span><span>FlexGrow = 1</span></span>
    </div>
    <div class="yoga" style="background-color: #303846; width: 50px; height: 50px; flex-grow: 1;">
      <span><span>FlexGrow = 1</span></span>
    </div>
  </div>
</div>

<div class="yoga" style="align-items: flex-start;">
  <div class="yoga sample" style="background-color: white; padding: 20px; flex-direction: row; width: 500px;">
    <div class="yoga" style="background-color: #303846; width: 50px; height: 50px; margin-right: 20px; flex-grow: 1;">
      <span><span>FlexGrow = 1</span></span>
    </div>
    <div class="yoga" style="background-color: #303846; width: 50px; height: 50px; flex-grow: 2;">
      <span><span>FlexGrow = 2</span></span>
    </div>
  </div>
</div>

### FlexShrink

The `FlexShrink` property describes how to shrink children along the main axis in the case that the total size of the children overflow the size of the container on the main axis.

`FlexShrink` is very similar to `FlexGrow` and can be thought of in the same way if any overflowing size is considered to be negative remaining space. These two properties also work well together by allowing children to grow and shrink as needed.

`FlexShrink` accepts any floating point value >= 0, with 0 being the default value. A container will shrink its children weighted by the child's `FlexShrink` value.

<div class="yoga" style="align-items: flex-start;">
  <div class="yoga sample" style="background-color: white; padding: 20px; flex-direction: row; width: 500px;">
    <div class="yoga" style="background-color: #303846; width: 300px; height: 50px; margin-right: 20px;"></div>
    <div class="yoga" style="background-color: #303846; width: 300px; height: 50px;"></div>
  </div>
</div>

<div class="yoga" style="align-items: flex-start;">
  <div class="yoga sample" style="background-color: white; padding: 20px; flex-direction: row; width: 500px;">
    <div class="yoga" style="background-color: #303846; width: 300px; height: 50px; margin-right: 20px;"></div>
    <div class="yoga" style="background-color: #303846; width: 300px; height: 50px; flex-shrink: 1;">
      <span><span>FlexShrink = 1</span></span>
    </div>
  </div>
</div>

<div class="yoga" style="align-items: flex-start;">
  <div class="yoga sample" style="background-color: white; padding: 20px; flex-direction: row; width: 500px;">
    <div class="yoga" style="background-color: #303846; width: 300px; height: 50px; margin-right: 20px; flex-shrink: 1;">
      <span><span>FlexShrink = 1</span></span>
    </div>
    <div class="yoga" style="background-color: #303846; width: 300px; height: 50px; flex-shrink: 1;">
      <span><span>FlexShrink = 1</span></span>
    </div>
  </div>
</div>

<div class="yoga" style="align-items: flex-start;">
  <div class="yoga sample" style="background-color: white; padding: 20px; flex-direction: row; width: 500px;">
    <div class="yoga" style="background-color: #303846; width: 300px; height: 50px; margin-right: 20px; flex-shrink: 1;">
      <span><span>FlexShrink = 1</span></span>
    </div>
    <div class="yoga" style="background-color: #303846; width: 300px; height: 50px; flex-shrink: 2;">
      <span><span>FlexShrink = 2</span></span>
    </div>
  </div>
</div>

### FlexBasis

The `FlexBasis` property is an axis-independent way of providing the default size of an item on the main axis. Setting the `FlexBasis` of a child is similar to setting the `Width` of that child if its parent is a container with `FlexDirection = row` or setting the `Height` of a child if its parent is a container with `FlexDirection = column`. The `FlexBasis` of an item is the default size of that item, the size of the item before any `FlexGrow` and `FlexShrink` calculations are performed.
