---
docid: c
title: C
layout: docs
permalink: /docs/api/c/
---
`YGNodeRef` is the main object you will be interfacing with when using Yoga in C. `YGNodeRef` is a pointer to an internal `YGNode` struct.

### Lifecycle

The following functions control the lifecycle of a `YGNodeRef`.

```c
YGNodeRef YGNodeNew();
void YGNodeReset(YGNodeRef node);
void YGNodeFree(YGNodeRef node);
void YGNodeFreeRecursive(YGNodeRef node);
```

- `YGNodeReset` will reset a node to its initial state so it can be re-used without needing to re-allocate a new node.
- `YGNodeFreeRecursive` is mostly used for testing and will free not only the node itself but also its children.

### Children

The following functions help manage the children of a node.

```c
void YGNodeInsertChild(YGNodeRef node, YGNodeRef child, uint32_t index);
void YGNodeRemoveChild(YGNodeRef node, YGNodeRef child);
YGNodeRef YGNodeGetChild(YGNodeRef node, uint32_t index);
uint32_t YGNodeGetChildCount(YGNodeRef node);
```

### Style getters & setters

The large part of Yoga's API consists of setters and getters for styles. These all follow the same general structure. Bellow are the function and enums used to control the various styles. For an in depth guide to how each style works see the getting started guide.

```c
typedef enum YGDirection {
  YGDirectionInherit,
  YGDirectionLTR,
  YGDirectionRTL,
} YGDirection;

void YGNodeStyleSetDirection(YGNodeRef node, YGDirection direction);
YGDirection YGNodeStyleGetDirection(YGNodeRef node);

typedef enum YGFlexDirection {
  YGFlexDirectionColumn,
  YGFlexDirectionColumnReverse,
  YGFlexDirectionRow,
  YGFlexDirectionRowReverse,
} YGFlexDirection;

void YGNodeStyleSetFlexDirection(YGNodeRef node,
                                 YGFlexDirection flexDirection);
YGFlexDirection YGNodeStyleGetFlexDirection(YGNodeRef node);

typedef enum YGJustify {
  YGJustifyFlexStart,
  YGJustifyCenter,
  YGJustifyFlexEnd,
  YGJustifySpaceBetween,
  YGJustifySpaceAround,
} YGJustify;

void YGNodeStyleSetJustifyContent(YGNodeRef node,
                                  YGJustify justifyContent);
YGJustify YGNodeStyleGetJustifyContent(YGNodeRef node);

typedef enum YGAlign {
  YGAlignAuto,
  YGAlignFlexStart,
  YGAlignCenter,
  YGAlignFlexEnd,
  YGAlignStretch,
} YGAlign;

void YGNodeStyleSetAlignContent(YGNodeRef node, YGAlign alignContent);
YGAlign YGNodeStyleGetAlignContent(YGNodeRef node);

void YGNodeStyleSetAlignItems(YGNodeRef node, YGAlign alignItems);
YGAlign YGNodeStyleGetAlignItems(YGNodeRef node);

void YGNodeStyleSetAlignSelf(YGNodeRef node, YGAlign alignSelf);
YGAlign YGNodeStyleGetAlignSelf(YGNodeRef node);

typedef enum YGPositionType {
  YGPositionTypeRelative,
  YGPositionTypeAbsolute,
} YGPositionType;

void YGNodeStyleSetPositionType(YGNodeRef node,
                                YGPositionType positionType);
YGPositionType YGNodeStyleGetPositionType(YGNodeRef node);

typedef enum YGWrap {
  YGWrapNoWrap,
  YGWrapWrap,
} YGWrap;

void YGNodeStyleSetFlexWrap(YGNodeRef node, YGWrap flexWrap);
YGWrap YGNodeStyleGetFlexWrap(YGNodeRef node);

typedef enum YGOverflow {
  YGOverflowVisible,
  YGOverflowHidden,
  YGOverflowScroll,
} YGOverflow;

void YGNodeStyleSetOverflow(YGNodeRef node, YGOverflow overflow);
YGOverflow YGNodeStyleGetOverflow(YGNodeRef node);

void YGNodeStyleSetFlex(YGNodeRef node, float flex);

void YGNodeStyleSetFlexGrow(YGNodeRef node, float flexGrow);
float YGNodeStyleGetFlexGrow(YGNodeRef node);

void YGNodeStyleSetFlexShrink(YGNodeRef node, float flexShrink);
float YGNodeStyleGetFlexShrink(YGNodeRef node);

void YGNodeStyleSetFlexBasis(YGNodeRef node, float flexBasis);
float YGNodeStyleGetFlexBasis(YGNodeRef node);

typedef enum YGEdge {
  YGEdgeLeft,
  YGEdgeTop,
  YGEdgeRight,
  YGEdgeBottom,
  YGEdgeStart,
  YGEdgeEnd,
  YGEdgeHorizontal,
  YGEdgeVertical,
  YGEdgeAll,
} YGEdge;

void YGNodeStyleSetPosition(YGNodeRef node, YGEdge edge, float position);
float YGNodeStyleGetPosition(YGNodeRef node, YGEdge edge);

void YGNodeStyleSetMargin(YGNodeRef node, YGEdge edge, float margin);
float YGNodeStyleGetMargin(YGNodeRef node, YGEdge edge);

void YGNodeStyleSetPadding(YGNodeRef node, YGEdge edge, float padding);
float YGNodeStyleGetPadding(YGNodeRef node, YGEdge edge);

void YGNodeStyleSetBorder(YGNodeRef node, YGEdge edge, float border);
float YGNodeStyleGetBorder(YGNodeRef node, YGEdge edge);

void YGNodeStyleSetWidth(YGNodeRef node, float width);
float YGNodeStyleGetWidth(YGNodeRef node);

void YGNodeStyleSetHeight(YGNodeRef node, float height);
float YGNodeStyleGetHeight(YGNodeRef node);

void YGNodeStyleSetMinWidth(YGNodeRef node, float minWidth);
float YGNodeStyleGetMinWidth(YGNodeRef node);

void YGNodeStyleSetMinHeight(YGNodeRef node, float minHeight);
float YGNodeStyleGetMinHeight(YGNodeRef node);

void YGNodeStyleSetMaxWidth(YGNodeRef node, float maxWidth);
float YGNodeStyleGetMaxWidth(YGNodeRef node);

void YGNodeStyleSetMaxHeight(YGNodeRef node, float maxHeight);
float YGNodeStyleGetMaxHeight(YGNodeRef node);

void YGNodeStyleSetAspectRatio(YGNodeRef node, float aspectRatio);
float YGNodeStyleGetAspectRatio(YGNodeRef node);
```

### Layout results

Once you have set up a tree of nodes with styles you will want to get the result of a layout calculation. Call `YGNodeCalculateLayout` with the desired width and height or `YGUndefined` to perform the layout calculation. Once this function returns the results of the layout calculation is stored on each node. Traverse the tree and retrieve the values from each node.

```c
void YGNodeCalculateLayout(YGNodeRef node,
                           float availableWidth,
                           float availableHeight,
                           YGDirection parentDirection);
float YGNodeLayoutGetLeft(YGNodeRef node);
float YGNodeLayoutGetTop(YGNodeRef node);
float YGNodeLayoutGetRight(YGNodeRef node);
float YGNodeLayoutGetBottom(YGNodeRef node);
float YGNodeLayoutGetWidth(YGNodeRef node);
float YGNodeLayoutGetHeight(YGNodeRef node);
YGDirection YGNodeLayoutGetDirection(YGNodeRef node);
```

### Custom measurements

Certain nodes need the ability to measure themselves, the most common example is nodes which represent text. Text has an intrinsic size and requires measuring itself to determine that size. This is not something Yoga can do as it requires relying on the host system's text rendering engine.

- Call `YGNodeMarkDirty` if a node with a custom text measurement function needs to be re-measured during the next layout pass.

> A measure function can only be attached to a leaf node in the hierarchy.

```c
typedef enum YGMeasureMode {
  YGMeasureModeUndefined,
  YGMeasureModeExactly,
  YGMeasureModeAtMost,
} YGMeasureMode;

typedef struct YGSize {
  float width;
  float height;
} YGSize;

typedef YGSize (*YGMeasureFunc)(YGNodeRef node,
                                float width,
                                YGMeasureMode widthMode,
                                float height,
                                YGMeasureMode heightMode);

void YGNodeSetMeasureFunc(YGNodeRef node, YGMeasureFunc measureFunc);
YGMeasureFunc YGNodeGetMeasureFunc(YGNodeRef node);

void YGNodeMarkDirty(YGNodeRef node);
bool YGNodeIsDirty(YGNodeRef node);
```

### Context

Context is important when integrating Yoga into another layout system. Context allows you to associate another object with a `YGNodeRef`. This context can then be retrieved from a `YGNodeRef` when for example its measure function is called. This is what enables Yoga to rely on the Android and iOS system implementations of text measurement in React Native.

```c
void YGNodeSetContext(YGNodeRef node, void *context);
void *YGNodeGetContext(YGNodeRef node);
```

### Logging

Yoga will by default log to stdout and stderr. You may however customize this to instead log to your own logger.

```c
typedef enum YGLogLevel {
  YGLogLevelError,
  YGLogLevelWarn,
  YGLogLevelInfo,
  YGLogLevelDebug,
  YGLogLevelVerbose,
} YGLogLevel;

typedef int (*YGLogger)(YGLogLevel level, char *format, va_list args);
void YGSetLogger(YGLogger logger);
void YGLog(YGLogLevel level, char *message, ...);
```

### Experiments

Yoga has the concept of experiments. An experiment is a feature which is not yet stable. To enable a feature use the following functions. Once a feature has been tested and is ready to be released as a stable API we will remove its feature flag.

```c
typedef enum YGExperimentalFeature {
  // Current experiments
} YGExperimentalFeature;

void YGSetExperimentalFeatureEnabled(YGExperimentalFeature feature,
                                     bool enabled);
bool YGIsExperimentalFeatureEnabled(YGExperimentalFeature feature);
```

### Printing

Yoga has some hooks to print debug information while calculating layout. With the printing APIs you can add additional information to a node when it is printed.

```c
typedef enum YGPrintOptions {
  YGPrintOptionsLayout = 1,
  YGPrintOptionsStyle = 2,
  YGPrintOptionsChildren = 4,
} YGPrintOptions;

typedef void (*YGPrintFunc)(YGNodeRef node);

void YGNodeSetPrintFunc(YGNodeRef node, YGPrintFunc printFunc);
YGPrintFunc YGNodeGetPrintFunc(YGNodeRef node);

void YGNodePrint(YGNodeRef node, YGPrintOptions options);
```
