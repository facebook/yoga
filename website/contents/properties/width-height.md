---
path: "docs/width-height"
title: "Width and Height"
hasPlayground: true
---

## Width and Height

The `width` property in flexbox specifies the width of the element's content area. Similarly `height` property specifies the height of the element's content area.

Both `width` and `height` can take following values

### Auto
It is the default Value, Yoga calculates the width/height for the element
 
### Pixels
Defines the width/height in px

### Percentage
Defines the width or height in percentage of its parents width or height respectively

Lets start to play with playground. For starter, lets try fiddling with `width`:

1. Click on the root view and set `width = auto`, you would see that it would shrink to fit its children. 
2. Lets try giving pixel value. Click on any child view, and change its width(say 300), you would now see child view's width is updated
3. Say you want to make your child view half of root view's width. Type 50% in your view's width field, and voila, your view is 50% of its parent.

You can do similar things with `height` too. Keep fiddling 😉

### Width
<controls prop="width"></controls>

### Height
<controls prop="height"></controls>

