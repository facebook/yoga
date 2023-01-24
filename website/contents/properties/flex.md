---
path: "/docs/flex"
title: "Flex Basis, Grow, and Shrink"
hasPlayground: true
---

## Flex Basis, Grow, and Shrink

**FLEX BASIS** is an axis-independent way of providing the default size of an item
along the main axis. Setting the flex basis of a child is similar to setting the `width` of that
child if its parent is a container with `flex direction: row` or setting the `height` of a child
if its parent is a container with `flex direction: column`. The flex basis of an item is the
default size of that item, the size of the item before any flex grow and flex shrink
calculations are performed.

<controls prop="flexBasis"></controls>

**FLEX GROW** describes how any space within a container should be distributed
among its children along the main axis. After laying out its children, a container will
distribute any remaining space according to the flex grow values specified by its children.

Flex grow accepts any floating point value >= 0, with 0 being the default value.
A container will distribute any remaining space among its children weighted by the child’s flex grow value.

<controls prop="flexGrow"></controls>

**FLEX SHRINK** describes how to shrink children along the main axis in the
case that the total size of the children overflow the size of the container on the main axis.
flex shrink is very similar to flex grow and can be thought of in the same way if
any overflowing size is considered to be negative remaining space.
These two properties also work well together by allowing children to grow and shrink as needed.

Flex shrink accepts any floating point value >= 0, with 1 being the default value.
A container will shrink its children weighted by the child’s flex shrink value.

<controls prop="flexShrink"></controls>
