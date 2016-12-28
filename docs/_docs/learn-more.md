---
docid: learn-more
title: Learn More
layout: docs
permalink: /docs/learn-more/
---

Yoga is an open-source, cross-platform layout library that implements Flexbox. Yoga's focus is on creating an expressive ***layout*** library, not implementing all of CSS. Therefore, there are no plans to include support for tables, floats, or similar CSS concepts. Yoga also does not support styling properties that have no impact on layout, such as color or background properties.

### Yoga vs Flexbox

Yoga aims to be compatible with Flexbox according to the [w3 specification](https://www.w3.org/TR/css3-flexbox). However, Yoga was not developed to strictly adhere to the specification; thus, there are aspects where Yoga differs.

#### Default values

Yoga has chosen to change the default values of some properties to better fit mobile layout use cases. The following CSS block describes the differences in default values from the [Flexbox w3 specification](https://www.w3.org/TR/css3-flexbox).

<script src="https://gist.github.com/emilsjolander/f9b3981cab44c51afa9ac446b8fdb60c.js"></script>

We have set up a [JSFiddle](https://jsfiddle.net/emilsjolander/jckmwztt/) so you can see these default values in action.

#### Right-to-Left

We believe that Right-to-Left (RTL) should be a first class citizen when it comes to layout. Therefore, Yoga implements non-standard RTL support for margin, padding, border, and position properties. This enables specifying these properties as `start` instead of `left` and `end` instead of `right`.

<div class="pluginWrapper buttonWrapper">
  <a
    class="button"
    href="/yoga/docs/rtl/"
  >Learn More about RTL</a>
</div>

#### Yoga-specific properties

The goal of Yoga is to be a library which makes layout easy. Of course, implementing Flexbox, a common and well-liked system, helps meet this goal. However, there are areas where we think Yoga can evolve beyond Flexbox and provide developers with tools not included in the [Flexbox w3 specification](https://www.w3.org/TR/css3-flexbox). Currently Yoga has added one such property, `AspectRatio`, to solve a common problem we saw in many UIs.

<div class="pluginWrapper buttonWrapper">
  <a
    class="button"
    href="/yoga/docs/aspect-ratio/"
  >Learn More about Aspect Ratio</a>
</div>
