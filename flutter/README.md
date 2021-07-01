# yoga_engine

A plugin that uses yoga to implements flexbox layout in Flutter.

## Installation

To use this plugin, add `yoga_engine` as a dependency in your `pubspec.yalm` file.

## Usage

First, import the dependency `package:yoga_engine/yoga_engine.dart` to your dart code to be able 
to use all the widgets and helpers provided by the Yoga Engine. Then, before `runApp` 
method, call `Yoga.init()` to initialize all Yoga Engine dependencies.

All that done, just configure each `NodeProperties` instance to all `YogaLayout` and `YogaNode` 
widgets in your layout, to yoga calculate each widget size and position them.

## Flutter layout comparison

At first, understanding how to set up the layout using `yoga_engine` might seem a bit complicated. 
To make building the layout more natural with the platform, 
think of `YogaLayout` as a `Row` or `Column` and the `YogaNode` as a `Flexible` or `Expanded`.
The concept of flex that Flutter applies is very similar to the flexbox that yoga implements. 
Both solutions were built in a similar way, so they can basically be thought of in the same way.

## Example

### Import
```dart
import 'package:yoga_engine/yoga_engine.dart';
```

### Initialization
```dart
void main() {
  Yoga.init();
}
```

### Configuration
```dart
NodeProperties root = NodeProperties();
root.setWidth(300);
root.setHeight(300);
root.setFlexDirection(YGFlexDirection.YGFlexDirectionRow);
root.setAlignItems(YGAlign.YGAlignCenter);

NodeProperties child = NodeProperties();
```

### Placement
```dart
YogaLayout(
  nodeProperties: root,
  children: [
    YogaNode(
      nodeProperties: child,
      child: Text('Child'),
    ),
  ],
 )
```

## Yoga engine rules
- `YogaLayout` widgets can only have children of `YogaLayout` or `YogaNode` types.
- `YogaNode` widgets can have any type of child, except themselves.
- `YogaNode` widgets cannot be placed outside `YogaLayout`.
