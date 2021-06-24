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
import 'package:flutter/widgets.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:yoga_engine/src/layout/node_properties.dart';
import 'package:yoga_engine/src/layout/yoga_render.dart';
import 'package:yoga_engine/src/yoga_initializer.dart';

void main() {
  group('Given a YogaLayout and YogaNode', () {
    group('When a layout is built', () {
      testWidgets('Then the layout should be rendered',
          (WidgetTester tester) async {
        // Given
        Yoga.init();
        final child = NodeProperties();

        final rootNode = NodeProperties();
        rootNode.setWidth(100);
        rootNode.setHeight(100);

        final layout = MaterialApp(
          home: Scaffold(
            body: YogaLayout(
              nodeProperties: rootNode,
              children: [
                YogaNode(
                  nodeProperties: child,
                  child: Text('test'),
                ),
              ],
            ),
          ),
        );

        // When
        await tester.pumpWidget(layout);
        final textFinder = find.text('test');

        // Then
        expect(textFinder, findsOneWidget);
      });
    });
  });
}
