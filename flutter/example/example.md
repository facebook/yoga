# Cookbook

Simple example of how to use the yoga_engine plugin.

```dart
import 'package:flutter/material.dart';
import 'package:yoga_engine/yoga_engine.dart';

void main() {
  Yoga.init();
  runApp(MyApp());
}

class MyApp extends StatefulWidget {
  @override
  _MyAppState createState() => _MyAppState();
}

class _MyAppState extends State<MyApp> {
  @override
  void initState() {
    super.initState();
  }

  @override
  Widget build(BuildContext context) {
    NodeProperties child1 = NodeProperties();
    child1.setWidth(50);
    child1.setHeight(50);

    NodeProperties child2 = NodeProperties();

    NodeProperties child3 = NodeProperties();
    child3.setFlexDirection(YGFlexDirection.YGFlexDirectionRow);
    child3.setHeight(100);

    NodeProperties child4 = NodeProperties();
    child4.setHeight(50);

    NodeProperties root = NodeProperties();
    root.setWidth(300);
    root.setHeight(300);
    root.setFlexDirection(YGFlexDirection.YGFlexDirectionRow);
    root.setAlignItems(YGAlign.YGAlignCenter);

    return MaterialApp(
      home: Scaffold(
        appBar: AppBar(
          title: const Text('Plugin example app'),
        ),
        body: ColoredBox(
          color: Colors.orange,
          child: YogaLayout(
            nodeProperties: root,
            children: [
              YogaNode(
                nodeProperties: child1,
                child: ColoredBox(
                  color: Colors.yellow,
                  child: Text('Child 1'),
                ),
              ),
              YogaNode(
                isLeaf: false,
                nodeProperties: child2,
                child: ColoredBox(
                  color: Colors.pink,
                  child: YogaLayout(
                    nodeProperties: child3,
                    children: [
                      YogaNode(
                        nodeProperties: child4,
                        child: ColoredBox(
                          color: Colors.cyan,
                          child: Text('Child 2'),
                        ),
                      ),
                    ],
                  ),
                ),
              ),
            ],
          ),
        ),
      ),
    );
  }
}
```
