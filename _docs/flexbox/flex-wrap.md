---
docid: flex-wrap
title: Flex wrap
layout: docs
permalink: /docs/flex-wrap/
---

The `FlexWrap` property is set on containers and controls what happens when children overflow the size of the container along the main axis. There are 2 options:

* `Nowrap` (default)
* `Wrap`

If a container specifies `FlexWrap = Wrap` then its children will wrap to the next line instead of overflowing. The next line will have the same `FlexDirection` as the first line and will appear next to the first line along the cross axis -- below it if using `FlexDirection = Column` and to the right if using `FlexDirection = Row`.

#### FlexWrap = Nowrap

<div class="yoga" style="align-items: flex-start;">
  <div class="yoga sample" style="background-color: white; padding: 20px; flex-direction: row; width: 300px;">
    <div class="yoga" style="background-color: #303846; width: 50px; height: 50px; margin-right: 20px;"></div>
    <div class="yoga" style="background-color: #303846; width: 50px; height: 50px; margin-right: 20px;"></div>
    <div class="yoga" style="background-color: #303846; width: 50px; height: 50px; margin-right: 20px;"></div>
    <div class="yoga" style="background-color: #303846; width: 50px; height: 50px; margin-right: 20px;"></div>
    <div class="yoga" style="background-color: #303846; width: 50px; height: 50px; margin-right: 20px;"></div>
    <div class="yoga" style="background-color: #303846; width: 50px; height: 50px;"></div>
  </div>
</div>

#### FlexWrap = Wrap

<div class="yoga" style="align-items: flex-start;">
  <div class="yoga sample" style="background-color: white; padding: 20px; flex-direction: row; width: 300px; flex-wrap: wrap;">
    <div class="yoga" style="background-color: #303846; width: 50px; height: 50px; margin-right: 20px; margin-bottom: 20px;"></div>
    <div class="yoga" style="background-color: #303846; width: 50px; height: 50px; margin-right: 20px; margin-bottom: 20px;"></div>
    <div class="yoga" style="background-color: #303846; width: 50px; height: 50px; margin-right: 20px; margin-bottom: 20px;"></div>
    <div class="yoga" style="background-color: #303846; width: 50px; height: 50px; margin-right: 20px;"></div>
    <div class="yoga" style="background-color: #303846; width: 50px; height: 50px; margin-right: 20px;"></div>
    <div class="yoga" style="background-color: #303846; width: 50px; height: 50px;"></div>
  </div>
</div>
