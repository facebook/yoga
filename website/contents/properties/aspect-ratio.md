---
path: "/docs/aspect-ratio"
title: "Aspect Ratio"
hasPlayground: true
---

## Aspect Ratio

AspectRatio is a property introduced by Yoga and is not present as a settable
property in the css flexbox specification. Flexbox does has the notion of
aspect ratio though for things with intrinsic aspect ratio such as images.

The `aspect ratio` property in Yoga has the following properties:

- Accepts any floating point value > 0, the default is undefined.
- Defined as the ratio between the `width` and the `height` of a node e.g. if a node has an aspect ratio of 2 then its `width` is twice the size of its `height`.
- Respects the `min` and `max` dimensions of an item.
- Has higher priority than `flex grow`
- If `aspect ratio`, `width`, and `height` are set then the cross axis dimension is overridden.

<controls prop="aspectRatio"></controls>
