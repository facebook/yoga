# CSSLayout [![Build Status](https://travis-ci.org/facebook/css-layout.svg?branch=master)](https://travis-ci.org/facebook/css-layout)

## Goals
CSSLayout is a cross-platform implementation of flexbox. The goal of CSSLayout is allow native developers to have the same expressive layout system as developers developing for the modern web are used to. CSSLayout allows developers for web, android, iOS, and windows to use the same layout primitives across platforms. This saves time, increases collaboration between platform teams, and makes it easier for developers to work on multiple platforms.

The goal of CSSLayout is not to re-implement all of css. CSSLayout only targets flexbox, and does not have any plans on implementing support for tables, floats, or any other css concepts. CSSLayout also does not plan on supporting styling properties which do not affect layout such as color or background properties.


## Differences from web
CSSLayout tries to stay as close as possible to the web implementation of flexbox. There are however certain cases where CSSLayout differs from the web implementation.

### Default values
CSSLayout has chosen to make changes to the default values of certain properties. These default values were chosen based on our usage of the library. When testing layout with tools such as JSFiddle you can apply the following css style to ensure the defaults match those of CSSLayout. Or fork the [following JSFiddle](http://jsfiddle.net/vjeux/y11txxv9/).

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
  min-width: 0;
}
```

- `box-sizing: border-box` is the most convenient way to express the relation between `width` and `borderWidth`.
- Everything is `display: flex` by default. All the behaviors of `block` and `inline-block` can be expressed in term of `flex` but not the opposite.
- All the flex elements are oriented from top to bottom, left to right and do not shrink. This is how things are laid out using the default CSS settings and what you'd expect.
- Everything is `position: relative`. This makes `position: absolute` target the direct parent and not some parent which is either `relative` or `absolute`. If you want to position an element relative to something else, you should move it in the DOM instead of relying of CSS. It also makes `top, left, right, bottom` do something when not specifying `position: absolute`.


### Flex
CSSLayout currently only supports a simplified flex model. CSSLayout does not support `flex-grow`, `flex-shrink`, or `flex-basis`. Instead CSSLayout only supports `flex` which takes a negative value for shrinking and a positive value for growing. Flex basis is defaulted to `0` when a non-zero `flex` value is provided and is otherwise set to `auto`. These limitations were made for sake of simplicity and we plan on supporting the full range of flex properties in the future.

### Size units
CSSLayout currently only supports pixel sizes. The reason being that we have not seen the need for any other units. We would like to support percentage units sometime in the future.

### -start and -end properties
We think supporting RTL locales is very important. Therefor CSSLayout supports non-standards -start and -end suffixed versions of margin, padding, border, and position.


## Usage

### C
The full API can be found in `CSSLayout/CSSLayout.h`.

```html
CSSNodeRef root = CSSNodeNew();
CSSNodeStyleSetWidth(root, 100);
CSSNodeStyleSetHeight(root, 100);

for (uint32_t i = 0; i < 10; i++) {
  CSSNodeRef child = CSSNodeNew();
  CSSNodeStyleSetHeight(child, 10);
  CSSNodeInsertChild(root, child, 0);
}

CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionLTR);

// Get for resulting layout
CSSNodeLayoutGetLeft(root);
CSSNodeLayoutGetTop(root);
CSSNodeLayoutGetWidth(root);
CSSNodeLayoutGetHeight(root);
```

### Java
The full API can be found in `java/com/facebook/csslayout/CSSNode.java`.

```java
CSSNode root = new CSSNode();
root.init();
root.setStyleWidth(100);
root.setStyleHeight(100);

for (int i = 0; i < 10; i++) {
  CSSNodeRef child = CSSNodeNew();
  child.setStyleHeight(10);
  root.addChildAt(child, 0);
}

root.calculateLayout(new CSSLayoutContext());

// Get for resulting layout
root.getLayoutX();
root.getLayoutY();
root.getLayoutWidth();
root.getLayoutHeight();
```

## Contributing
To contribute to CSSLayout you need to first install [buck](https://buckbuild.com) which is the build system used by CSSLayout. CSSLayout is implemented in C with language bindings for Java. When making changes to `CSSLayout/CSSLayout.h` please ensure to update `java/jni/CSSJNI.h` and `java/com/facebook/csslayout/CSSNode.java` to reflect the API change. Before submitting any code please run `format.sh` to ensure the code matches the project's code style.

Before making any larger changes to CSSLayout please open an issue with a RFC so the changes can be discussed first. Generally we are very open to changes and improvements that will benefit the community.

### Testing
For any changes you make you should ensure that all the tests are passing. In case you make any fixes or additions to the library please also add at least one test to ensure we don't break anything in the future. Tests are located in `tests/CSSLayoutTest.cpp`. Run the tests by executing `buck test //:CSSLayout`.

Instead of manually writing a test which ensures parity with web implementations of flexbox you can run `gentest/gentest.sh` to generated a test for you. After running `gentest/gentest.sh` a editor window should pop open (make sure you have `$EDITOR` env variable exported). Here you can write html which you want to verify in CSSLayout, such as the following.

```html
<div style="width: 100px; height: 100px; align-items: center;">
  <div style="width: 50px; height: 50px;"></div>
</div>
```

Once saving and exiting the editor window the script will open a browser window. From here open the developer console and you should see that the web page has output a test file. Copy this into a file and save it in the `tests` folder. Re-run `buck test //:CSSLayout` to validate the behavior. One test case will be generated for every root `div` in the input html.

### Benchmarks
Benchmarks are located in `benchmarks/CSSBenchmark.c` and can be run with `buck run //:benchmark`. If you think your change has affected performance please run this before and after your change to validate that nothing has regressed.
