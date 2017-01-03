---
docid: margin-padding-border
title: Margin, Padding, Border
layout: docs
permalink: /docs/margin-padding-border/
---

`Margin`, `Padding` are similar but have some important differences. By applying `Margin` to an item you specify the offset a certain edge of the item should have from it's closest sibling or parent. With `Padding` on the other hand you specify the offset children should have from a certain edge on the parent. `Border` behaves nearly identically to `Padding` and is only separate from `Padding` to make it easier to implement border effect such as color. In the below illustrations the green box is a child of the dark gray box.

#### MarginStart = 50;

<div class="yoga" style="align-items: flex-start;">
  <div class="yoga sample" style="background-color: white; width: 300px; height: 300px;">
    <div class="yoga" style="background-color: #303846; flex: 1; margin-left: 50px;">
      <div style="width: 50px; height: 50px; background-color: #97dccf;"></div>
    </div>
  </div>
</div>

#### MarginEnd = 50;

<div class="yoga" style="align-items: flex-start;">
  <div class="yoga sample" style="background-color: white; width: 300px; height: 300px;">
    <div class="yoga" style="background-color: #303846; flex: 1; margin-right: 50px;">
      <div style="width: 50px; height: 50px; background-color: #97dccf;"></div>
    </div>
  </div>
</div>

#### MarginAll = 50;

<div class="yoga" style="align-items: flex-start;">
  <div class="yoga sample" style="background-color: white; width: 300px; height: 300px;">
    <div class="yoga" style="background-color: #303846; flex: 1; margin: 50px;">
      <div style="width: 50px; height: 50px; background-color: #97dccf;"></div>
    </div>
  </div>
</div>

#### PaddingAll = 50;

<div class="yoga" style="align-items: flex-start;">
  <div class="yoga sample" style="background-color: white; width: 300px; height: 300px;">
    <div class="yoga" style="background-color: #303846; flex: 1; padding: 50px;">
      <div style="width: 50px; height: 50px; background-color: #97dccf;"></div>
    </div>
  </div>
</div>

#### BorderWidth = 50;

<div class="yoga" style="align-items: flex-start;">
  <div class="yoga sample" style="background-color: white; width: 300px; height: 300px;">
    <div class="yoga" style="background-color: #303846; flex: 1; border-width: 50px; border-color: transparent;">
      <div style="width: 50px; height: 50px; background-color: #97dccf;"></div>
    </div>
  </div>
</div>
