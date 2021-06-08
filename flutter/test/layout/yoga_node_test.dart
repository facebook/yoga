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
import 'package:yoga_engine/ffi/mapper.dart';
import 'package:yoga_engine/ffi/types.dart';
import 'package:yoga_engine/ffi/utils.dart';
import 'package:yoga_engine/layout/yoga_node.dart';
import 'package:yoga_engine/yoga_initializer.dart';

void main() {
  serviceLocator.registerSingleton<DynamicLibrary>(loadYoga());
  final mapper = Mapper(serviceLocator.get());
  serviceLocator.registerSingleton<Mapper>(mapper);

  final yogaNode = YogaNode();

  group('Given a YogaNode', () {

    group('When createSize is called', () {
      test('Then should create a YogaSize with the given parameters', () {
        // Given
        final width = 100.0;
        final height = 200.0;

        // When
        final result = yogaNode.createSize(width, height);

        // Then
        expect(result.width, width);
        expect(result.height, height);
      });
    });

    group('When reset is called', () {
      test('Then should reset all attributes from node', () {
        // Given
        yogaNode.setFlex(2);
        yogaNode.setFlexDirection(YGFlexDirection.YGFlexDirectionColumnReverse);

        // When
        yogaNode.reset();

        // Then
        expect(yogaNode.getFlex().isNaN, true);
        expect(yogaNode.getFlexDirection(), YGFlexDirection.YGFlexDirectionColumn);
      });
    });

    group('When insertChildAt is called', () {
      test('Then should insert the given child at the index', () {
        // Given
        final child = mapper.yGNodeNew();
        final index = 0;

        // When
        yogaNode.insertChildAt(child, index);

        // Then
        expect(yogaNode.getChildAt(index), child);
      });
    });

    // TODO cover with tests the other methods
  });
}
