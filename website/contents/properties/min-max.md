---
path: "docs/min-max"
title: "Max / Min Width and Height"
hasPlayground: true
---

## Max / Min Width and Height

### Max Width

The `maxWidth` property sets the maximum width of an element. It prevents the used value of the width property from becoming larger than the value specified by `maxWidth `

### Min Width

The `minWidth` property sets the minimum width of an element. It prevents the used value of the width property from becoming smaller than the value specified by `width `.

`minWidth` overrides both `maxWidth` and `width`. Try out this in playground.

### Max Height

The `maxHeight` property sets the maximum height of an element. It prevents the used value of the height property from becoming larger than the value specified by `maxHeight`.

### Min Width

The `minHeight` property sets the minimum height of an element. It prevents the used value of the height property from becoming smaller than the value specified by `height`.

`minHeight ` overrides both `maxHeight` and `height`. Try out this in playground.

Each of the above properties can take the following values

### Pixel

One can specify the pixel values for each of the above properties

### Percentages

One can specifiy min/max values in terms of the percentage of its parent.

Try out the above properties in playground.

#### Max Width
<controls prop="maxWidth"></controls>
#### Min Width
<controls prop="minWidth"></controls>
#### Max Height
<controls prop="maxHeight"></controls>
#### Min Height
<controls prop="minHeight"></controls>
