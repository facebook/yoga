css-layout [![Build Status](https://travis-ci.org/facebook/css-layout.svg?branch=master)](https://travis-ci.org/facebook/css-layout)
==========

This project implements a subset of CSS including flexbox and the box model using pure JavaScript, then transpiled to C and Java. The goal is to have a small standalone library to layout elements. It doesn't rely on the DOM at all.

In order to make sure that the code is correct, it is developed in JavaScript using TDD where each commit adds a unit test and the associated code to make it work. All the unit tests are tested against Chrome's implementation of CSS.

The JavaScript version has been implemented in a way that can be easily transpiled to C and Java via regexes. The layout function doesn't do any allocation nor uses any of the dynamic aspect of JavaScript. The tests are also transpiled to make sure that the implementations are correct everywhere.


Usage
-----

A single function `computeLayout` is exposed and
 - takes a tree of nodes: `{ style: { ... }, children: [ nodes ] }`
 - returns a tree of rectangles: `{ width: ..., height: ..., top: ..., left: ..., children: [ rects ] }`

For example,

```javascript
computeLayout(
  {style: {padding: 50}, children: [
    {style: {padding: 10, alignSelf: 'stretch'}}
  ]}
);
// =>
{width: 120, height: 120, top: 0, left: 0, children: [
  {width: 20, height: 20, top: 50, left: 50}
]}
```

To run the tests

- For the JS tests: Open `RunLayoutTests.html` and `RunLayoutRandomTests.html` in Chrome or run `$ npm test`
- For the C and Java tests: run `make` in your terminal. It will also transpile the JS code

Supported Attributes
--------------------

Name | Value
----:|------
width, height | positive number
minWidth, minHeight | positive number
maxWidth, maxHeight | positive number
left, right, top, bottom | number
margin, marginLeft, marginRight, marginTop, marginBottom | number
padding, paddingLeft, paddingRight, paddingTop, paddingBottom | positive number
borderWidth, borderLeftWidth, borderRightWidth, borderTopWidth, borderBottomWidth | positive number
flexDirection | 'column', 'row'
justifyContent | 'flex-start', 'center', 'flex-end', 'space-between', 'space-around'
alignItems, alignSelf | 'flex-start', 'center', 'flex-end', 'stretch'
flex | positive number
flexWrap | 'wrap', 'nowrap'
position | 'relative', 'absolute'

- `inherit` value is not implemented because it's a way to disambiguate between multiple colliding rules. This should be done in a pre-processing step, not in the actual layout algorithm.



Default values
--------------
Since we are only using flexbox, we can use defaults that are much more sensible. This is the configuration to use in order to get the same behavior using the DOM and CSS. You can try those default settings with the [following JSFiddle](http://jsfiddle.net/vjeux/y11txxv9/).

```css
div, span {
  box-sizing: border-box;
  position: relative;

  display: flex;
  flex-direction: column;
  align-items: stretch;
  flex-shrink: 0;

  border: 0 solid black;
  margin: 0;
  padding: 0;
}
```

- `box-sizing: border-box` is the most convenient way to express the relation between `width` and `borderWidth`.
- Everything is `display: flex` by default. All the behaviors of `block` and `inline-block` can be expressed in term of `flex` but not the opposite.
- All the flex elements are oriented from top to bottom, left to right and do not shrink. This is how things are laid out using the default CSS settings and what you'd expect.
- Everything is `position: relative`. This makes `position: absolute` target the direct parent and not some parent which is either `relative` or `absolute`. If you want to position an element relative to something else, you should move it in the DOM instead of relying of CSS. It also makes `top, left, right, bottom` do something when not specifying `position: absolute`.
