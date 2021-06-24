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
import 'package:yoga_engine/src/utils/methods.dart';
import 'package:yoga_engine/src/yoga_initializer.dart';

void main() {
  serviceLocator.registerSingleton<DynamicLibrary>(loadYoga());

  final mapper = Mapper(serviceLocator.get());

  group('Given a Mapper', () {
    group('When yGValueAuto is called', () {
      test('Then should return nan with YGUnitAuto', () {
        // Given
        final ygValue = YogaValue(YGUndefined, YGUnit.YGUnitAuto);

        // When
        final result = mapper.yGValueAuto;

        // Then
        expect(result.value.isNaN, true);
        expect(result.unit, ygValue.unit);
      });
    });

    group('When yGValueUndefined is called', () {
      test('Then should return nan with YGUnitUndefined', () {
        // Given
        final ygValue = YogaValue(YGUndefined, YGUnit.YGUnitUndefined);

        // When
        final result = mapper.yGValueUndefined;

        // Then
        expect(result.value.isNaN, true);
        expect(result.unit, ygValue.unit);
      });
    });

    group('When yGValueZero is called', () {
      test('Then should return 0 with YGUnitPoint', () {
        // Given
        final ygValue = YogaValue(0, YGUnit.YGUnitPoint);

        // When
        final result = mapper.yGValueZero;

        // Then
        expect(result.value, ygValue.value);
        expect(result.unit, ygValue.unit);
      });
    });

    group('When yGCreateSize is called', () {
      test('Then should return the given width and height', () {
        // Given
        final width = 100.0;
        final height = 200.0;

        // When
        final result = mapper.yGCreateSize(width, height);

        // Then
        expect(result.width, width);
        expect(result.height, height);
      });
    });

    group('When yGNodeNew is called', () {
      test('Then should return a Pointer<YGNode>', () {
        // Given
        final ygNode = Pointer<YGNode>.fromAddress(0);

        // When
        final result = mapper.yGNodeNew();

        // Then
        expect(result.runtimeType, ygNode.runtimeType);
      });
    });

    group('When yGNodeNewWithConfig is called', () {
      test('Then should return a Pointer<YGNode>', () {
        // Given
        final ygNode = mapper.yGNodeNew();
        final ygConfig = mapper.yGConfigNew();

        // When
        final result = mapper.yGNodeNewWithConfig(ygConfig);

        // Then
        expect(result.runtimeType, ygNode.runtimeType);
      });
    });

    group('When yGNodeClone is called', () {
      test('Then should return a Pointer<YGNode>', () {
        // Given
        final ygNode = mapper.yGNodeNew();
        final ygClone = mapper.yGNodeNew();

        // When
        final result = mapper.yGNodeClone(ygClone);

        // Then
        expect(result.runtimeType, ygNode.runtimeType);
      });
    });

    group('When yGNodeFree is called', () {
      test('Then should reset owner', () {
        // Given
        final ygOwner = mapper.yGNodeNew();
        final ygNode = mapper.yGNodeNew();
        mapper.yGNodeInsertChild(ygOwner, ygNode, 0);

        // When
        mapper.yGNodeFree(ygNode);

        // Then
        expect(mapper.yGNodeGetOwner(ygNode), nullptr);
        expect(mapper.yGNodeGetChildCount(ygOwner), 0);
      });
    });

    group('When yGNodeReset is called', () {
      test('Then should clear all properties from the given node', () {
        // Given
        final ygNode = mapper.yGNodeNew();
        mapper.yGNodeStyleSetFlex(ygNode, 10);

        // When
        mapper.yGNodeReset(ygNode);

        // Then
        expect(mapper.yGNodeStyleGetFlex(ygNode).isNaN, true);
      });
    });

    group('When yGNodeInsertChild is called', () {
      test('Then should add the child to the given index', () {
        // Given
        final ygNode = mapper.yGNodeNew();
        final ygChild = mapper.yGNodeNew();
        final index = 0;

        // When
        mapper.yGNodeInsertChild(ygNode, ygChild, index);

        // Then
        expect(mapper.yGNodeGetChild(ygNode, index), ygChild);
      });
    });

    group('When yGNodeSwapChild is called', () {
      test('Then should swap the child to the given index', () {
        // Given
        final ygNode = mapper.yGNodeNew();
        final ygChild = mapper.yGNodeNew();
        final ygChildSwap = mapper.yGNodeNew();
        final index = 0;
        mapper.yGNodeInsertChild(ygNode, ygChild, index);

        // When
        mapper.yGNodeSwapChild(ygNode, ygChildSwap, index);

        // Then
        expect(mapper.yGNodeGetChild(ygNode, index), ygChildSwap);
      });
    });

    group('When yGNodeRemoveChild is called', () {
      test('Then should remove the given child', () {
        // Given
        final ygNode = mapper.yGNodeNew();
        final ygChild = mapper.yGNodeNew();
        mapper.yGNodeInsertChild(ygNode, ygChild, 0);

        // When
        mapper.yGNodeRemoveChild(ygNode, ygChild);

        // Then
        expect(mapper.yGNodeGetChildCount(ygNode), 0);
      });
    });

    group('When yGNodeRemoveAllChildren is called', () {
      test('Then should remove all children', () {
        // Given
        final ygNode = mapper.yGNodeNew();
        final ygChild1 = mapper.yGNodeNew();
        final ygChild2 = mapper.yGNodeNew();
        mapper.yGNodeInsertChild(ygNode, ygChild1, 0);
        mapper.yGNodeInsertChild(ygNode, ygChild2, 1);

        // When
        mapper.yGNodeRemoveAllChildren(ygNode);

        // Then
        expect(mapper.yGNodeGetChildCount(ygNode), 0);
      });
    });

    group('When yGNodeGetOwner is called', () {
      test('Then should return the node\'s owner', () {
        // Given
        final ygNode = mapper.yGNodeNew();
        final ygChild = mapper.yGNodeNew();
        mapper.yGNodeInsertChild(ygNode, ygChild, 0);

        // When
        final result = mapper.yGNodeGetOwner(ygChild);

        // Then
        expect(result, ygNode);
      });
    });

    group('When yGNodeGetParent is called', () {
      test('Then should return the node\'s parent', () {
        // Given
        final ygNode = mapper.yGNodeNew();
        final ygChild = mapper.yGNodeNew();
        mapper.yGNodeInsertChild(ygNode, ygChild, 0);

        // When
        final result = mapper.yGNodeGetParent(ygChild);

        // Then
        expect(result, ygNode);
      });
    });

    group('When yGNodeGetChildCount is called', () {
      test('Then should return the quantity of children', () {
        // Given
        final ygNode = mapper.yGNodeNew();
        final ygChild1 = mapper.yGNodeNew();
        final ygChild2 = mapper.yGNodeNew();
        mapper.yGNodeInsertChild(ygNode, ygChild1, 0);
        mapper.yGNodeInsertChild(ygNode, ygChild2, 1);

        // When
        final result = mapper.yGNodeGetChildCount(ygNode);

        // Then
        expect(result, 2);
      });
    });

    group('When yGNodeSetChildren is called', () {
      test('Then should set the given children', () {
        // Given
        // final ygNode = mapper.yGNodeNew();
        // final ygChild1 = mapper.yGNodeNew();
        // final ygChild2 = mapper.yGNodeNew();
        // final ygChildren = [ygChild1, ygChild2];

        // When
        // final result = mapper.yGNodeSetChildren(ygNode, ygChildren, 2);

        // Then
        // expect(mapper.yGNodeGetChildCount(ygNode), 2);
      });
    });

    group('When yGNodeSetIsReferenceBaseline is called', () {
      test('Then should set the baseline reference with the given value', () {
        // Given
        final ygNode = mapper.yGNodeNew();
        final isReferenceBaseline = true;

        // When
        mapper.yGNodeSetIsReferenceBaseline(ygNode, isReferenceBaseline);

        // Then
        expect(mapper.yGNodeIsReferenceBaseline(ygNode), isReferenceBaseline);
      });
    });

    group('When yGNodeIsReferenceBaseline is called', () {
      test('Then should return if isReferenceBaseline', () {
        // Given
        final ygNode = mapper.yGNodeNew();
        final isReferenceBaseline = true;
        mapper.yGNodeSetIsReferenceBaseline(ygNode, isReferenceBaseline);

        // When
        final result = mapper.yGNodeIsReferenceBaseline(ygNode);

        // Then
        expect(result, isReferenceBaseline);
      });
    });

    group('When yGNodeCalculateLayout is called', () {
      test('Then should calculate the layout', () {
        // Given
        final ygNode = mapper.yGNodeNew();
        final availableWidth = 100.0;
        final availableHeight = 200.0;

        // When
        mapper.yGNodeCalculateLayout(
          ygNode,
          availableWidth,
          availableHeight,
          YGDirection.YGDirectionInherit,
        );

        // Then
        expect(mapper.yGNodeLayoutGetWidth(ygNode), availableWidth);
        expect(mapper.yGNodeLayoutGetHeight(ygNode), availableHeight);
      });
    });

    group('When yGNodeMarkDirty is called', () {
      test('Then should mark dirty the given node', () {
        // Given
        final ygNode = mapper.yGNodeNew();
        mapper.yGNodeSetMeasureFunc(ygNode, Pointer.fromFunction(measureFunc));

        // When
        mapper.yGNodeMarkDirty(ygNode);

        // Then
        expect(mapper.yGNodeIsDirty(ygNode), true);
      });
    });

    // TODO cover with tests the other methods
  });
}
