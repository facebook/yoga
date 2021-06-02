# yoga_engine

A plugin that uses yoga to implements flexbox layout in Flutter.

## Installation

To use this plugin, add `yoga_engine` as a dependency in your pubspec.yalm file.

## Usage

First, import the dependency `package:yoga_engine/yoga_engine.dart` to your dart code to be able 
to use all the widgets and helpers provided by the Yoga Engine. Then, configure each `YogaNode` to 
all `YogaTree` and `YogaLeaf` widgets in your layout.

All that done, just call `calculateLayout()` from de root node of your layout, to yoga calculate 
each widget size and position them.

## Example

```dart

```
