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

import 'dart:ffi';

import 'package:flutter_test/flutter_test.dart';
import 'package:yoga_engine/src/ffi/mapper.dart';
import 'package:yoga_engine/src/ffi/types.dart';
import 'package:yoga_engine/src/layout/node_properties.dart';
import 'package:yoga_engine/src/utils/methods.dart';
import 'package:yoga_engine/src/yoga_initializer.dart';

void main() {
  serviceLocator.registerSingleton<DynamicLibrary>(loadYoga());
  final mapper = Mapper(serviceLocator.get());
  serviceLocator.registerSingleton<Mapper>(mapper);

  final nodeProperties = NodeProperties();

  group('Given a NodeProperties', () {
    group('When createSize is called', () {
      test('Then should create a YogaSize with the given parameters', () {
        // Given
        final width = 100.0;
        final height = 200.0;

        // When
        final result = nodeProperties.createSize(width, height);

        // Then
        expect(result.width, width);
        expect(result.height, height);
      });
    });

    group('When reset is called', () {
      test('Then should reset all attributes from node', () {
        // Given
        nodeProperties.setFlex(2);
        nodeProperties
            .setFlexDirection(YGFlexDirection.YGFlexDirectionColumnReverse);

        // When
        nodeProperties.reset();

        // Then
        expect(nodeProperties.getFlex().isNaN, true);
        expect(nodeProperties.getFlexDirection(),
            YGFlexDirection.YGFlexDirectionColumn);
      });
    });

    group('When insertChildAt is called', () {
      test('Then should insert the given child at the index', () {
        // Given
        final child = NodeProperties();
        final index = 0;

        // When
        nodeProperties.insertChildAt(child, index);

        // Then
        expect(nodeProperties.getChildAt(index), child.node);
      });
    });

    // TODO cover with tests the other methods
  });
}
