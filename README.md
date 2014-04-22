css-layout
==========

This project implements a subset of CSS including flexbox and the box model using pure JavaScript. The goal is to have a small standalone library to layout elements. It doesn't rely on the DOM at all.

In order to make sure that the code is correct, it is developped using TDD where each commit adds a unit test and the associated code to make it work. All the unit tests are tested against Chrome's implementation of CSS.


Supported Attributes
--------------------

Name | Value
----:|------
width, height | number
left, right, top, bottom | number
margin, marginLeft, marginRight, marginTop, marginBottom | positive number
padding, paddingLeft, paddingRight, paddingTop, paddingBottom | positive number
borderWidth, borderLeftWidth, borderRightWidth, borderTopWidth, borderBottomWidth | positive number
flexDirection | 'column', 'row'
justifyContent | 'flex-start', 'center', 'flex-end', 'space-between', 'space-around'
alignItems, alignSelf | 'flex-start', 'center', 'flex-end', 'stretch'
flex | 'none', 1
position | 'relative', 'absolute'

- `inherit` value is not implemented because it's a way to disambiguate between multiple colliding rules. This should be done in a pre-processing step, not in the actual layout algorithm.


Usage
-----

A single function `computeLayout` is exposed and 
 - takes a tree of nodes: `{ style: { ... }, children: [ nodes ] }`
 - returns a tree of rectanges: `{ width: ..., height: ..., top: ..., left: ..., children: [ rects ] }`

For example, 

```javascript
computeLayout(
  {style: {height: 100, justifyContent: 'flex-end'}, children: [
    {style: {marginTop: 10}}
  ]}
)
// =>
{width: 0, height: 100, top: 0, left: 0, children: [
  {width: 0, height: 0, top: 100, left: 0}
]}
```


Default values
--------------
Since we are only using flexbox, we can use defaults that are much more sensible. This is the configuration to use in order to get the same behavior using the DOM and CSS.

```css
div {
  box-sizing: border-box;
  position: relative;
  margin: 0;
  padding: 0;
  
  display: flex;
  flex-direction: column;
  align-items: flex-start;
  justify-content: flex-start;
  flex-shrink: 0;
}
```

- `box-sizing: border-box` is the most convenient way to express the relation between `width` and `borderWidth`.
- Everything is `display: flex` by default. All the behaviors of `block` and `inline-block` can be expressed in term of `flex` but not the opposite.
- All the flex elements are oriented from top to bottom, left to right and do not shrink. This is how things are laid out using the default CSS settings and what you'd expect.
- Everything is `position: relative`. This makes `position: absolute` target the direct parent and not some parent which is either `relative` or `absolute`. If you want to position an element relative to something else, you should move it in the DOM instead of relying of CSS. It also makes `top, left, right, bottom` do something when not specifying `position: absolute`.
