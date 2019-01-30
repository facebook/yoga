---
path: "/docs/justify-content"
title: "Justify Content"
hasPlayground: true
---

## Justify Content

Justify content describes how to align children within the main axis of their
container. For example, you can use this property to center a child horizontally
within a container with `flex direction` set to `row` or vertically within a
container with `flex direction` set to `column`.

**FLEX START (DEFAULT)** Aligns the children to be flush with the edge of the
parent corresponding to the flex container’s main-start or cross-start side, as
appropriate.

**FLEX END** Aligns the children to be flush with the edge of the parent
corresponding to the flex container’s main-end or cross-end side, as
appropriate.

**CENTER** Centers the children within its parent.

**SPACE BETWEEN** The children are evenly distributed in the parent. The first
child is placed flush with the start edge of the parent, the last child is
placed flush with the end edge of the parent, and the remaining children are
distributed so that the spacing between any two adjacent children is the same.

**SPACE AROUND** The children are evenly distributed in the parent, with a
half-size space on either end. The children are distributed so that the spacing
between any two adjacent children is the same, and the spacing before the first
and after the last child is half the size of the other spacing..

**SPACE EVENLY** The children are evenly distributed in the parent, with a
full-size space on either end. The children are distributed so that the spacing
between any two adjacent children, before the first child, and after the last
child is the same.

<controls prop="justifyContent"></controls>
