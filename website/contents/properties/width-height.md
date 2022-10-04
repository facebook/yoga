---
path: "/docs/width-height"
title: "Width and Height"
hasPlayground: true
---

## Width and Height

The `width` property in Yoga specifies the width of the element's content area.
Similarly `height` property specifies the height of the element's content area.

Both `width` and `height` can take following values:

**AUTO** Is the default Value, Yoga calculates the width/height for the element based
on its content, whether that is other children, text, or an image.

**PIXELS** Defines the width/height in absolute pixels. Depending on other properties set on
the Yoga node this may or may not be the final dimension of the node.

**PERCENTAGE** Defines the width or height in percentage of its parent's width or height respectively.

### Width
<controls prop="width"></controls>

### Height
<controls prop="height"></controls>
