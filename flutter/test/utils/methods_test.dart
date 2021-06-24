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
import 'package:yoga_engine/src/layout/yoga_render.dart';
import 'package:yoga_engine/src/utils/methods.dart';
import 'package:yoga_engine/src/utils/node_helper.dart';
import 'package:yoga_engine/src/yoga_initializer.dart';

void main() {
  group('Given a loadYoga method', () {
    group('When loadYoga is called', () {
      test('Then should return a DynamicLibrary', () {
        // When
        final result = loadYoga();

        // Then
        expect(result is DynamicLibrary, true);
      });
    });

    group('When loadYoga is called twice', () {
      test('Then should return the same DynamicLibrary instance', () {
        // When
        final result1 = loadYoga();
        final result2 = loadYoga();

        // Then
        expect(result1, result2);
      });
    });
  });

  group('Given a measureFunc method', () {
    serviceLocator.registerSingleton<DynamicLibrary>(loadYoga());
    final _mapper = Mapper(serviceLocator.get());
    serviceLocator.registerSingleton<Mapper>(_mapper);
    final _nodeHelper = NodeHelper(serviceLocator.get());
    serviceLocator.registerSingleton<NodeHelper>(_nodeHelper);
    final node = _mapper.yGNodeNew();
    final renderYoga = RenderYoga(nodeProperties: NodeProperties());
    _nodeHelper.setRenderBoxToNode(renderYoga, node);

    group('When measureFunc is called', () {
      test('Then should return a YGSize', () {
        // Given
        final width = 100.0;
        final widthMode = 1;
        final height = 100.0;
        final heightMode = 1;

        // When
        final result = measureFunc(node, width, widthMode, height, heightMode);

        // Then
        expect(result is YGSize, true);
        expect(width, result.width);
        expect(height, result.height);
      });
    });

    group('When measureFunc is called with YGMeasureModeExactly', () {
      test('Then should return a YGSize with the given width and height', () {
        // Given
        final width = 100.0;
        final widthMode = 1;
        final height = 100.0;
        final heightMode = 1;

        // When
        final result = measureFunc(node, width, widthMode, height, heightMode);

        // Then
        expect(width, result.width);
        expect(height, result.height);
      });
    });

    group('When measureFunc is called with YGMeasureModeAtMost', () {
      test('Then should return a YGSize with max width and height', () {
        // Given
        final width = 100.0;
        final widthMode = 2;
        final height = 100.0;
        final heightMode = 2;

        // When
        final result = measureFunc(node, width, widthMode, height, heightMode);

        // Then
        expect(0, result.width);
        expect(0, result.height);
      });
    });
  });
}
