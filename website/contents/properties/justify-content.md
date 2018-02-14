---
path: "docs/justify-content"
title: "Justify Content"
hasPlayground: true
---

## Justify Content

Justify content describes how to align children within the main axis of their container.
For example, you can use this property to center a child horizontally within a container
with `flex direction` set to `Row` or vertically within a container with `flex direction`
set to  `Column`.

**FLEX START (DEFAULT)** Align children of a container to the start of the container's main axis.

**FLEX END** Align children of a container to the end of the container's main axis.

**CENTER** Align children of a container in the center of the container's main axis.

**SPACE BETWEEN** Evenly space of children across the container's main axis, distrubuting
remaining space between the children.

**SPACE AROUND** Evenly space of children across the container's main axis, distrubuting
remaining space around the children. Compared to `Space Between` using
`Space Around` will result in space being distributed to the begining of
the first child and end of the last child.

<controls prop="justifyContent"></controls>
