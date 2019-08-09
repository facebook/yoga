---
path: "/docs/justify-content"
title: "Justify Content"
hasPlayground: true
---

## Justify Content

Justify content describes how to align children within the main axis of their container.
For example, you can use this property to center a child horizontally within a container
with `flex direction` set to `row` or vertically within a container with `flex direction`
set to `column`.

**FLEX START (DEFAULT)** Align children of a container to the start of the container's main axis.

**FLEX END** Align children of a container to the end of the container's main axis.

**CENTER** Align children of a container in the center of the container's main axis.

**SPACE BETWEEN** Evenly space of children across the container's main axis, distributing
remaining space between the children.

**SPACE AROUND** Evenly space of children across the container's main axis, distributing
remaining space around the children. Compared to `space between` using
`space around` will result in space being distributed to the beginning of
the first child and end of the last child.

**SPACE EVENLY** Evenly distributed within the alignment container along the main axis. The spacing between each pair of adjacent items, the main-start edge and the first item, and the main-end edge and the last item, are all exactly the same.

<controls prop="justifyContent"></controls>
