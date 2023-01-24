---
path: "/docs/absolute-relative-layout"
title: "Absolute/Relative Layout"
hasPlayground: true
---
## Absolute/Relative Layout

The `position type` of an element defines how it is
positioned within its parent.

**RELATIVE (DEFAULT)** By default an element is positioned
relatively. This means an element is positioned according to the
normal flow of the layout, and then offset relative to that position
based on the values of `top`, `right`, `bottom`, and `left`.
The offset does not affect the position of any sibling or parent elements.

**ABSOLUTE** When positioned absolutely an element doesn't take
part in the normal layout flow. It is instead laid out independent
of its siblings. The position is determined based on the
`top`, `right`, `bottom`, and `left` values.

<controls prop="positionType"></controls>

The position values `top`, `right`, `bottom`, and `left` behave
differently depending on the `position type` of the element. For
a `relative` element they offset the position of the element in the
direction specified. For `absolute` element though these properties
specify the offset of the element's side from the same side on the parent.

<controls prop="position"></controls>
