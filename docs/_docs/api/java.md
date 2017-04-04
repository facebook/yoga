---
docid: java
title: Java
layout: docs
permalink: /docs/api/java/
---
`YogaNode` is the main object you will be interfacing with when using Yoga in Java. `YogaNode` is a thin [JNI](https://en.wikipedia.org/wiki/Java_Native_Interface) wrapper around the core Yoga library.

### Lifecycle

Create a `YogaNode` via its default constructor and use `reset` if you want to pool and re-use nodes. The native memory of a `YogaNode` will automatically be freed when the node is garbage collected.

```java
YogaNode();
void reset();
```

### Children

The following methods help manage the children of a node.

```java
int getChildCount();
YogaNodeType getChildAt(int i);
void addChildAt(YogaNodeType child, int i);
YogaNodeType removeChildAt(int i);
YogaNodeType getParent();
int indexOf(YogaNodeType child);
```

### Style getters & setters

The large part of Yoga's API consists of setters and getters for styles. These all follow the same general structure. Bellow are the function and enums used to control the various styles. For an in depth guide to how each style works see the getting started guide.

```java
enum YogaDirection {
  INHERIT,
  LTR,
  RTL
}

YogaDirection getStyleDirection();
void setDirection(YogaDirection direction);

enum YogaFlexDirection {
  COLUMN,
  COLUMN_REVERSE,
  ROW,
  ROW_REVERSE
}

YogaFlexDirection getFlexDirection();
void setFlexDirection(YogaFlexDirection flexDirection);

enum YogaJustify {
  FLEX_START,
  CENTER,
  FLEX_END,
  SPACE_BETWEEN,
  SPACE_AROUND
}

YogaJustify getJustifyContent();
void setJustifyContent(YogaJustify justifyContent);

enum YogaAlign {
  AUTO,
  FLEX_START,
  CENTER,
  FLEX_END,
  STRETCH
}

YogaAlign getAlignItems();
void setAlignItems(YogaAlign alignItems);

YogaAlign getAlignSelf();
void setAlignSelf(YogaAlign alignSelf);

YogaAlign getAlignContent();
void setAlignContent(YogaAlign alignContent);

enum YogaPositionType {
  RELATIVE,
  ABSOLUTE
}

YogaPositionType getPositionType();
void setPositionType(YogaPositionType positionType);

enum YogaWrap {
  NO_WRAP,
  WRAP
}

void setWrap(YogaWrap flexWrap);

enum YogaOverflow {
  VISIBLE,
  HIDDEN,
  SCROLL
}

YogaOverflow getOverflow();
void setOverflow(YogaOverflow overflow);

void setFlex(float flex);
float getFlexGrow();
void setFlexGrow(float flexGrow);
float getFlexShrink();
void setFlexShrink(float flexShrink);
float getFlexBasis();
void setFlexBasis(float flexBasis);

enum YogaEdge {
  LEFT,
  TOP,
  RIGHT,
  BOTTOM,
  START,
  END,
  HORIZONTAL,
  VERTICAL,
  ALL
}

float getMargin(YogaEdge edge);
void setMargin(YogaEdge edge, float margin);

float getPadding(YogaEdge edge);
void setPadding(YogaEdge edge, float padding);

float getBorder(YogaEdge edge);
void setBorder(YogaEdge edge, float border);

float getPosition(YogaEdge edge);
void setPosition(YogaEdge edge, float position);

float getWidth();
void setWidth(float width);

float getHeight();
void setHeight(float height);

float getMaxWidth();
void setMaxWidth(float maxWidth);

float getMinWidth();
void setMinWidth(float minWidth);

float getMaxHeight();
void setMaxHeight(float maxHeight);

float getMinHeight();
void setMinHeight(float minHeight);

float getAspectRatio();
void setAspectRatio(float aspectRatio);
```

### Layout results

Once you have set up a tree of nodes with styles you will want to get the result of a layout calculation. Call `calculateLayout()` perform layout calculation. Once this function returns the results of the layout calculation is stored on each node. Traverse the tree and retrieve the values from each node.

```java
void calculateLayout();
float getLayoutX();
float getLayoutY();
float getLayoutWidth();
float getLayoutHeight();
YogaDirection getLayoutDirection();
```

### Custom measurements

Certain nodes need to ability to measure themselves, the most common example is nodes which represent text. Text has an intrinsic size and requires measuring itself to determine that size. This is not something Yoga can do as it requires relying on the host system's text rendering engine.

- Call `dirty()` if a node with a custom text measurement function needs to be re-measured during the next layout pass.

> A measure function can only be attached to a leaf node in the hierarchy.

```java
enum YogaMeasureMode {
  UNDEFINED,
  EXACTLY,
  AT_MOST
}

interface YogaMeasureFunction {
  long measure(
      YogaNodeAPI node,
      float width,
      YogaMeasureMode widthMode,
      float height,
      YogaMeasureMode heightMode);
}

class YogaMeasureOutput {
  static long make(int width, int height);
}

void setMeasureFunction(YogaMeasureFunction measureFunction);
boolean isMeasureDefined();

boolean isDirty();
void dirty();
```

### Data

Data is important when integrating Yoga into another layout system. Data allows you to associate another object with a `YogaNode`. This data can then be retrieved from a `YogaNode` when for example its measure function is called. This is what enables Yoga to rely on the Android system implementations of text measurement in React Native.

```java
void setData(Object data);
Object getData();
```

### Logging

Yoga will by default log to stdout and stderr (or logcat on Android). You may however customize this to instead log to your own logger.

```java
enum YogaLogLevel {
  ERROR,
  WARN,
  INFO,
  DEBUG,
  VERBOSE
}

interface YogaLogger {
  void log(YogaLogLevel level, String message);
}

void setLogger(YogaLogger logger);
```

### Experiments

Yoga has the concept of experiments. An experiment is a feature which is not yet stable. To enable a feature use the following functions. Once a feature has been tested and is ready to be released as a stable API we will remove its feature flag.

```java
enum YogaExperimentalFeature {
  // Current experiments
}

static void setExperimentalFeatureEnabled(
  YogaExperimentalFeature feature, 
  boolean enabled);
static boolean isExperimentalFeatureEnabled(
  YogaExperimentalFeature feature);
```
