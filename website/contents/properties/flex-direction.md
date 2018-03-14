---
path: "/docs/flex-direction"
title: "Flex Direction"
hasPlayground: true
---

## Flex Direction

Flex direction controls the direction in which children of a node are laid out.
This is also referred to as the main axis. The main axis is the direction in
which children are laid out. The cross axis the the axis perpendicular to the
main axis, or the axis which wrapping lines are laid out in.

**ROW (DEFAULT)** Align children from left to right. If [wrapping](/docs/flex-wrap) is enabled then
the next line will start under the first item on the left of the container.

**COLUMN** Align children from top to bottom. If [wrapping](/docs/flex-wrap) is enabled then
the next line will start to the left first item on the top of the container.

**ROW REVERSE** Align children from right to left. If [wrapping](/docs/flex-wrap) is enabled then
the next line will start under the first item on the right of the container.

**COLUMN REVERSE** Align children from bottom to top. If [wrapping](/docs/flex-wrap) is enabled then
the next line will start to the left first item on the bottom of the container.

<controls prop="flexDirection"></controls>
