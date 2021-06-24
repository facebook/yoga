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
import 'package:flutter_test/flutter_test.dart';
import 'package:yoga_engine/yoga_engine.dart';
import 'package:yoga_engine_example/main.dart';

void main() {
  testWidgets('Verify example', (WidgetTester tester) async {
    Yoga.init();
    await tester.pumpWidget(MyApp());

    expect(
      find.byWidgetPredicate(
        (Widget widget) => widget is Text && widget.data!.startsWith('Child'),
      ),
      findsNWidgets(2),
    );
  });
}
