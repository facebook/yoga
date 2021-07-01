/*
 * Copyright 2020 ZUP IT SERVICOS EM TECNOLOGIA E INOVACAO SA
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

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
