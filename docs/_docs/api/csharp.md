---
docid: csharp
title: C#
layout: docs
permalink: /docs/api/csharp/
---
`YogaNode` is the main object you will be interfacing with when using Yoga in .NET. `YogaNode` is a thin [P/Invoke](https://msdn.microsoft.com/en-us/library/aa446536.aspx) wrapper around the core Yoga library.

### Lifecycle

Create a `YogaNode` via its default constructor and use `Reset` if you want to pool and re-use nodes. The native memory of a `YogaNode` will automatically be freed when the node is garbage collected.

```csharp
YogaNode();
void Reset();
```

### Children

The following methods help manage the children of a node.

```csharp
int Count { get };
YogaNode this[int index] { get };
void Insert(int index, YogaNode node);
void RemoveAt(int index);
void Clear();
int IndexOf(YogaNode node);
```

### Style getters & setters

The large part of Yoga's API consists of properties, setters, and getters for styles. These all follow the same general structure. Bellow are the function and enums used to control the various styles. For an in depth guide to how each style works see the getting started guide.

```csharp
enum YogaDirection
{
  Inherit,
  LTR,
  RTL,
}

YogaDirection StyleDirection {get, set};

enum YogaFlexDirection
{
  Column,
  ColumnReverse,
  Row,
  RowReverse,
}

YogaFlexDirection FlexDirection {get, set};

enum YogaJustify
{
  FlexStart,
  Center,
  FlexEnd,
  SpaceBetween,
  SpaceAround,
}

YogaJustify JustifyContent {get, set};

enum YogaAlign 
{
  Auto,
  FlexStart,
  Center,
  FlexEnd,
  Stretch,
  Baseline,
  SpaceBetween,
  SpaceAround
}

YogaAlign AlignItems {get, set};
YogaAlign AlignSelf {get, set};
YogaAlign AlignContent {get, set};

enum YogaPositionType 
{
  Relative,
  Absolute,
}

YogaPositionType PositionType {get, set};

enum YogaWrap 
{
  NoWrap,
  Wrap,
  WrapReverse
}

YogaWrap Wrap {get, set};

enum YogaOverflow 
{
  Visible,
  Hidden,
  Scroll,
}

YogaOverflow Overflow {get, set};

float Flex {set};
float FlexGrow {get, set};
float FlexShrink {get, set};
float FlexBasis {get, set};

enum YogaEdge 
{
  Left,
  Top,
  Right,
  Bottom,
  Start,
  End,
  Horizontal,
  Vertical,
  All,
}

float GetMargin(YogaEdge edge);
void SetMargin(YogaEdge edge, float margin);

float GetPadding(YogaEdge edge);
void SetPadding(YogaEdge edge, float padding);

float GetBorder(YogaEdge edge);
void SetBorder(YogaEdge edge, float border);

float GetPosition(YogaEdge edge);
void SetPosition(YogaEdge edge, float position);

float Width {get, set};
float Height {get, set};

float MaxWidth {get, set};
float MinWidth {get, set};

float MaxHeight {get, set};
float MinHeight {get, set};

float AspectRatio {get, set};
```

### Layout results

Once you have set up a tree of nodes with styles you will want to get the result of a layout calculation. Call `CalculateLayout()` perform layout calculation. Once this function returns the results of the layout calculation is stored on each node. Traverse the tree and retrieve the values from each node.

```csharp
void CalculateLayout();
float LayoutX {get};
float LayoutY {get};
float LayoutWidth {get};
float LayoutHeight {get};
YogaDirection LayoutDirection {get};
```

### Custom measurements

Certain nodes need to ability to measure themselves, the most common example is nodes which represent text. Text has an intrinsic size and requires measuring itself to determine that size. This is not something Yoga can do as it requires relying on the host system's text rendering engine.

- Call `MarkDirty()` if a node with a custom text measurement function needs to be re-measured during the next layout pass.

> A measure function can only be attached to a leaf node in the hierarchy.

```csharp
enum YogaMeasureMode
{
  Undefined,
  Exactly,
  AtMost,
}

public delegate YogaSize MeasureFunction(
  YogaNode node,
  float width,
  YogaMeasureMode widthMode,
  float height,
  YogaMeasureMode heightMode);

void SetMeasureFunction(MeasureFunction measureFunction);
bool IsMeasureDefined();

bool IsDirty {get};
void MarkDirty();
```

### Data

Data is important when integrating Yoga into another layout system. Data allows you to associate another object with a `YogaNode`. This data can then be retrieved from a `YogaNode` when for example its measure function is called. This is what enables Yoga to rely on the Android system implementations of text measurement in React Native.

```csharp
object Data {get, set}
```

### Experiments

Yoga has the concept of experiments. An experiment is a feature which is not yet stable. To enable a feature use the following functions. Once a feature has been tested and is ready to be released as a stable API we will remove its feature flag.

```csharp
enum YogaExperimentalFeature {
  // Current experiments
}

static void setExperimentalFeatureEnabled(
  YogaExperimentalFeature feature, 
  boolean enabled);
static boolean isExperimentalFeatureEnabled(
  YogaExperimentalFeature feature);
```
