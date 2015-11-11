css-layout [![Build Status](https://travis-ci.org/facebook/css-layout.svg?branch=master)](https://travis-ci.org/facebook/css-layout)
==========

This project implements a subset of CSS including flexbox and the box model using pure JavaScript, then transpiled to C and Java. The goal is to have a small standalone library to layout elements. It doesn't rely on the DOM at all.

The Java, C and JavaScript version of the code is available via [npm](https://www.npmjs.com/package/css-layout) or directly from the `dist` folder of this repo. The JavaScript version is also available via [cdnjs](https://cdnjs.com/libraries/css-layout).

In order to make sure that the code is correct, it is developed in JavaScript using TDD where each commit adds a unit test and the associated code to make it work. All the unit tests are tested against Chrome's implementation of CSS.

The JavaScript version has been implemented in a way that can be easily transpiled to C and Java via regexes. The layout function doesn't do any allocation nor uses any of the dynamic aspects of JavaScript. The tests are also transpiled to make sure that the implementations are correct everywhere.


Usage
-----

A single function `computeLayout` is exposed that
 - takes a tree of nodes: `{ style: { ... }, children: [ nodes ] }`
 - computes the layout and writes it back to the node tree.

For example,

```javascript
// create an initial tree of nodes
var nodeTree = {
    "style": {
      "padding": 50
    },
    "children": [
      {
        "style": {
          "padding": 10,
          "alignSelf": "stretch"
        }
      }
    ]
  };

// compute the layout
computeLayout(nodeTree);

// the layout information is written back to the node tree, with
// each node now having a layout property: 

// JSON.stringify(nodeTree, null, 2);
{
  "style": {
    "padding": 50
  },
  "children": [
    {
      "style": {
        "padding": 10,
        "alignSelf": "stretch"
      },
      "layout": {
        "width": 20,
        "height": 20,
        "top": 50,
        "left": 50,
        "right": 50,
        "bottom": 50,
        "direction": "ltr"
      },
      "children": [],
      "lineIndex": 0
    }
  ],
  "layout": {
    "width": 120,
    "height": 120,
    "top": 0,
    "left": 0,
    "right": 0,
    "bottom": 0,
    "direction": "ltr"
  }
}
```

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
  align-content: flex-start;

  border: 0 solid black;
  margin: 0;
  padding: 0;
}
```

- `box-sizing: border-box` is the most convenient way to express the relation between `width` and `borderWidth`.
- Everything is `display: flex` by default. All the behaviors of `block` and `inline-block` can be expressed in term of `flex` but not the opposite.
- All the flex elements are oriented from top to bottom, left to right and do not shrink. This is how things are laid out using the default CSS settings and what you'd expect.
- Everything is `position: relative`. This makes `position: absolute` target the direct parent and not some parent which is either `relative` or `absolute`. If you want to position an element relative to something else, you should move it in the DOM instead of relying of CSS. It also makes `top, left, right, bottom` do something when not specifying `position: absolute`.

Native Usage Notes
------------------

The C equivalent of `computeLayout` is [`layoutNode`](dist/css-layout.h#L1378).

In order for layout to properly layout reflowable text, the `measure` function must be set on the `css_node` structure. The property can be found in [`css-layout.h`](dist/css-layout.h#L146). This function must take a void pointer to a `context` that will affect the size of the node and the `width` as computed by the layout engine, and must return a `css_dim_t` structure defining the actual needed size of the node. For the most part, the `context` field can be the text inside the node. No C implementation of this function is provided in provided - it depends on your use of css-layout. However an implementation of the function in JavaScript can be used for reference in the [test utilities](src/Layout-test-utils.js#L383).

Development
-----------

The core logic resides with `Layout.js`, which is transpiled into equivalent C and Java implementations.

The JavaScript build process is managed via Grunt. The build performs linting, runs the tests against Chrome, transpiles and packages the code (JavaScript and Java) into the `dist` folder. For JavaScript, the build output uses the Universal Module Format (UMD) so that it can be used via AMD / RequireJS, CommonJS or included directly into an HTML page.

While developing you can just run the lint / Chrome-based tests a follows:

```
grunt test-javascript
```
