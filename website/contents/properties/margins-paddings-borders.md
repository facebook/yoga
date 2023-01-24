---
path: "/docs/margins-paddings-borders"
title: "Margins, Paddings, and Borders"
hasPlayground: true
---

## Margins, Paddings, and Borders

**MARGIN** effects the spacing around the outside of a node. A node with margin
will offset itself from the bounds of its parent but also offset the
location of any siblings. The margin of a node contributes to the total size
of its parent if the parent is auto sized.

<controls prop="margin"></controls>

**PADDING** affects the size of the node it is applied to. Padding in Yoga acts as if
`box-sizing: border-box;` was set. That is padding will not add to the total size
of an element if it has an explicit size set. For auto sized nodes padding will increase
the size of the node as well as offset the location of any children.

<controls prop="padding"></controls>

**BORDER** in Yoga acts exactly like padding and only exists as a seperate property so
that higher level frameworks get a hint as to how thick to draw a border. Yoga however
does not do any drawing so just uses this information during layout where border
acts exactly like padding.

<controls prop="border"></controls>
