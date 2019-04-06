---
path: "/docs/layout-direction"
title: "Layout Direction"
hasPlayground: false
---

## Layout Direction

Layout direction specifies the direction in which children and text
in a hierarchy should be laid out. Layout direction also effects what
edge `start` and `end` refer to. By default Yoga lays out with `LTR`
layout direction. In this mode `start` refers to `left` and `end`
refers to `right`. When localizing your apps for markets with RTL languages
you should customize this by either by passing a direction
to the `CalculateLayout` call or by setting the direction on the root node.

**LTR (DEFAULT)** Text and children and laid out from left to right. Margin and
padding applied the start of an element are applied on the left side.

**RTL** Text and children and laid out from right to left. Margin and
padding applied the start of an element are applied on the right side.

<controls prop="layoutDirection"></controls>
