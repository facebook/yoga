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
import 'package:yoga_engine/src/ffi/types.dart';

void main() {

  group('Given a yoga type', () {
    group('When YGConfig', () {
      test('Then should be Opaque', () {
        // When
        final ygConfig = YGConfig();

        // Then
        expect(ygConfig is Opaque, true);
      });
    });

    group('When YGNode', () {
      test('Then should be Opaque', () {
        // When
        final yGNode = YGNode();

        // Then
        expect(yGNode is Opaque, true);
      });
    });

    group('When YGValue', () {
      test('Then should be Struct', () {
        // When
        final yGValue = YGValue();

        // Then
        expect(yGValue is Struct, true);
      });
    });

    group('When YGSize', () {
      test('Then should be Struct', () {
        // When
        final yGSize = YGSize();

        // Then
        expect(yGSize is Struct, true);
      });
    });

    group('When VaListTag', () {
      test('Then should be Struct', () {
        // When
        final vaListTag = VaListTag();

        // Then
        expect(vaListTag is Struct, true);
      });
    });

    group('When YGUndefined', () {
      test('Then should be double.nan', () {
        // When
        final yGUndefined = YGUndefined;

        // Then
        expect(yGUndefined.isNaN, true);
      });
    });
  });

  group('Given a YGAlign', () {
    group('When it is YGAlignAuto', () {
      test('Then should be index 0', () {
        // When
        final yGAlign = YGAlign.YGAlignAuto;

        // Then
        expect(yGAlign.index, 0);
      });
    });

    group('When it is YGAlignFlexStart', () {
      test('Then should be index 1', () {
        // When
        final yGAlign = YGAlign.YGAlignFlexStart;

        // Then
        expect(yGAlign.index, 1);
      });
    });

    group('When it is YGAlignCenter', () {
      test('Then should be index 2', () {
        // When
        final yGAlign = YGAlign.YGAlignCenter;

        // Then
        expect(yGAlign.index, 2);
      });
    });

    group('When it is YGAlignFlexEnd', () {
      test('Then should be index 3', () {
        // When
        final yGAlign = YGAlign.YGAlignFlexEnd;

        // Then
        expect(yGAlign.index, 3);
      });
    });

    group('When it is YGAlignStretch', () {
      test('Then should be index 4', () {
        // When
        final yGAlign = YGAlign.YGAlignStretch;

        // Then
        expect(yGAlign.index, 4);
      });
    });

    group('When it is YGAlignBaseline', () {
      test('Then should be index 5', () {
        // When
        final yGAlign = YGAlign.YGAlignBaseline;

        // Then
        expect(yGAlign.index, 5);
      });
    });

    group('When it is YGAlignSpaceBetween', () {
      test('Then should be index 6', () {
        // When
        final yGAlign = YGAlign.YGAlignSpaceBetween;

        // Then
        expect(yGAlign.index, 6);
      });
    });

    group('When it is YGAlignSpaceAround', () {
      test('Then should be index 7', () {
        // When
        final yGAlign = YGAlign.YGAlignSpaceAround;

        // Then
        expect(yGAlign.index, 7);
      });
    });
  });

  group('Given a YGDimension', () {
    group('When it is YGDimensionWidth', () {
      test('Then should be index 0', () {
        // When
        final yGDimension = YGDimension.YGDimensionWidth;

        // Then
        expect(yGDimension.index, 0);
      });
    });

    group('When it is YGDimensionHeight', () {
      test('Then should be index 1', () {
        // When
        final yGDimension = YGDimension.YGDimensionHeight;

        // Then
        expect(yGDimension.index, 1);
      });
    });
  });

  group('Given a YGDirection', () {
    group('When it is YGDirectionInherit', () {
      test('Then should be index 0', () {
        // When
        final yGDirection = YGDirection.YGDirectionInherit;

        // Then
        expect(yGDirection.index, 0);
      });
    });

    group('When it is YGDirectionLTR', () {
      test('Then should be index 1', () {
        // When
        final yGDirection = YGDirection.YGDirectionLTR;

        // Then
        expect(yGDirection.index, 1);
      });
    });

    group('When it is YGDirectionRTL', () {
      test('Then should be index 2', () {
        // When
        final yGDirection = YGDirection.YGDirectionRTL;

        // Then
        expect(yGDirection.index, 2);
      });
    });
  });

  group('Given a YGDisplay', () {
    group('When it is YGDisplayFlex', () {
      test('Then should be index 0', () {
        // When
        final yGDisplay = YGDisplay.YGDisplayFlex;

        // Then
        expect(yGDisplay.index, 0);
      });
    });

    group('When it is YGDisplayNone', () {
      test('Then should be index 1', () {
        // When
        final yGDisplay = YGDisplay.YGDisplayNone;

        // Then
        expect(yGDisplay.index, 1);
      });
    });
  });

  group('Given a YGEdge', () {
    group('When it is YGEdgeLeft', () {
      test('Then should be index 0', () {
        // When
        final yGEdge = YGEdge.YGEdgeLeft;

        // Then
        expect(yGEdge.index, 0);
      });
    });

    group('When it is YGEdgeTop', () {
      test('Then should be index 1', () {
        // When
        final yGEdge = YGEdge.YGEdgeTop;

        // Then
        expect(yGEdge.index, 1);
      });
    });

    group('When it is YGEdgeRight', () {
      test('Then should be index 2', () {
        // When
        final yGEdge = YGEdge.YGEdgeRight;

        // Then
        expect(yGEdge.index, 2);
      });
    });

    group('When it is YGEdgeBottom', () {
      test('Then should be index 3', () {
        // When
        final yGEdge = YGEdge.YGEdgeBottom;

        // Then
        expect(yGEdge.index, 3);
      });
    });

    group('When it is YGEdgeStart', () {
      test('Then should be index 4', () {
        // When
        final yGEdge = YGEdge.YGEdgeStart;

        // Then
        expect(yGEdge.index, 4);
      });
    });

    group('When it is YGEdgeEnd', () {
      test('Then should be index 5', () {
        // When
        final yGEdge = YGEdge.YGEdgeEnd;

        // Then
        expect(yGEdge.index, 5);
      });
    });

    group('When it is YGEdgeHorizontal', () {
      test('Then should be index 6', () {
        // When
        final yGEdge = YGEdge.YGEdgeHorizontal;

        // Then
        expect(yGEdge.index, 6);
      });
    });

    group('When it is YGEdgeVertical', () {
      test('Then should be index 7', () {
        // When
        final yGEdge = YGEdge.YGEdgeVertical;

        // Then
        expect(yGEdge.index, 7);
      });
    });

    group('When it is YGEdgeAll', () {
      test('Then should be index 8', () {
        // When
        final yGEdge = YGEdge.YGEdgeAll;

        // Then
        expect(yGEdge.index, 8);
      });
    });
  });

  group('Given a YGFlexDirection', () {
    group('When it is YGFlexDirectionColumn', () {
      test('Then should be index 0', () {
        // When
        final yGFlexDirection = YGFlexDirection.YGFlexDirectionColumn;

        // Then
        expect(yGFlexDirection.index, 0);
      });
    });

    group('When it is YGFlexDirectionColumnReverse', () {
      test('Then should be index 1', () {
        // When
        final yGFlexDirection = YGFlexDirection.YGFlexDirectionColumnReverse;

        // Then
        expect(yGFlexDirection.index, 1);
      });
    });

    group('When it is YGFlexDirectionRow', () {
      test('Then should be index 2', () {
        // When
        final yGFlexDirection = YGFlexDirection.YGFlexDirectionRow;

        // Then
        expect(yGFlexDirection.index, 2);
      });
    });

    group('When it is YGFlexDirectionRowReverse', () {
      test('Then should be index 3', () {
        // When
        final yGFlexDirection = YGFlexDirection.YGFlexDirectionRowReverse;

        // Then
        expect(yGFlexDirection.index, 3);
      });
    });
  });

  group('Given a YGJustify', () {
    group('When it is YGJustifyFlexStart', () {
      test('Then should be index 0', () {
        // When
        final yGJustify = YGJustify.YGJustifyFlexStart;

        // Then
        expect(yGJustify.index, 0);
      });
    });

    group('When it is YGJustifyCenter', () {
      test('Then should be index 1', () {
        // When
        final yGJustify = YGJustify.YGJustifyCenter;

        // Then
        expect(yGJustify.index, 1);
      });
    });

    group('When it is YGJustifyFlexEnd', () {
      test('Then should be index 2', () {
        // When
        final yGJustify = YGJustify.YGJustifyFlexEnd;

        // Then
        expect(yGJustify.index, 2);
      });
    });

    group('When it is YGJustifySpaceBetween', () {
      test('Then should be index 3', () {
        // When
        final yGJustify = YGJustify.YGJustifySpaceBetween;

        // Then
        expect(yGJustify.index, 3);
      });
    });

    group('When it is YGJustifySpaceAround', () {
      test('Then should be index 4', () {
        // When
        final yGJustify = YGJustify.YGJustifySpaceAround;

        // Then
        expect(yGJustify.index, 4);
      });
    });

    group('When it is YGJustifySpaceEvenly', () {
      test('Then should be index 5', () {
        // When
        final yGJustify = YGJustify.YGJustifySpaceEvenly;

        // Then
        expect(yGJustify.index, 5);
      });
    });
  });

  group('Given a YGLogLevel', () {
    group('When it is YGLogLevelError', () {
      test('Then should be index 0', () {
        // When
        final yGLogLevel = YGLogLevel.YGLogLevelError;

        // Then
        expect(yGLogLevel.index, 0);
      });
    });

    group('When it is YGLogLevelWarn', () {
      test('Then should be index 1', () {
        // When
        final yGLogLevel = YGLogLevel.YGLogLevelWarn;

        // Then
        expect(yGLogLevel.index, 1);
      });
    });

    group('When it is YGLogLevelInfo', () {
      test('Then should be index 2', () {
        // When
        final yGLogLevel = YGLogLevel.YGLogLevelInfo;

        // Then
        expect(yGLogLevel.index, 2);
      });
    });

    group('When it is YGLogLevelDebug', () {
      test('Then should be index 3', () {
        // When
        final yGLogLevel = YGLogLevel.YGLogLevelDebug;

        // Then
        expect(yGLogLevel.index, 3);
      });
    });

    group('When it is YGLogLevelVerbose', () {
      test('Then should be index 4', () {
        // When
        final yGLogLevel = YGLogLevel.YGLogLevelVerbose;

        // Then
        expect(yGLogLevel.index, 4);
      });
    });

    group('When it is YGLogLevelFatal', () {
      test('Then should be index 5', () {
        // When
        final yGLogLevel = YGLogLevel.YGLogLevelFatal;

        // Then
        expect(yGLogLevel.index, 5);
      });
    });
  });

  group('Given a YGMeasureMode', () {
    group('When it is YGMeasureModeUndefined', () {
      test('Then should be index 0', () {
        // When
        final yGMeasureMode = YGMeasureMode.YGMeasureModeUndefined;

        // Then
        expect(yGMeasureMode.index, 0);
      });
    });

    group('When it is YGMeasureModeExactly', () {
      test('Then should be index 1', () {
        // When
        final yGMeasureMode = YGMeasureMode.YGMeasureModeExactly;

        // Then
        expect(yGMeasureMode.index, 1);
      });
    });

    group('When it is YGMeasureModeAtMost', () {
      test('Then should be index 2', () {
        // When
        final yGMeasureMode = YGMeasureMode.YGMeasureModeAtMost;

        // Then
        expect(yGMeasureMode.index, 2);
      });
    });
  });

  group('Given a YGNodeType', () {
    group('When it is YGNodeTypeDefault', () {
      test('Then should be index 0', () {
        // When
        final yGNodeType = YGNodeType.YGNodeTypeDefault;

        // Then
        expect(yGNodeType.index, 0);
      });
    });

    group('When it is YGNodeTypeText', () {
      test('Then should be index 1', () {
        // When
        final yGNodeType = YGNodeType.YGNodeTypeText;

        // Then
        expect(yGNodeType.index, 1);
      });
    });
  });

  group('Given a YGOverflow', () {
    group('When it is YGOverflowVisible', () {
      test('Then should be index 0', () {
        // When
        final yGOverflow = YGOverflow.YGOverflowVisible;

        // Then
        expect(yGOverflow.index, 0);
      });
    });

    group('When it is YGOverflowHidden', () {
      test('Then should be index 1', () {
        // When
        final yGOverflow = YGOverflow.YGOverflowHidden;

        // Then
        expect(yGOverflow.index, 1);
      });
    });

    group('When it is YGOverflowScroll', () {
      test('Then should be index 2', () {
        // When
        final yGOverflow = YGOverflow.YGOverflowScroll;

        // Then
        expect(yGOverflow.index, 2);
      });
    });
  });

  group('Given a YGPositionType', () {
    group('When it is YGPositionTypeStatic', () {
      test('Then should be index 0', () {
        // When
        final yGPositionType = YGPositionType.YGPositionTypeStatic;

        // Then
        expect(yGPositionType.index, 0);
      });
    });

    group('When it is YGPositionTypeRelative', () {
      test('Then should be index 1', () {
        // When
        final yGPositionType = YGPositionType.YGPositionTypeRelative;

        // Then
        expect(yGPositionType.index, 1);
      });
    });

    group('When it is YGPositionTypeAbsolute', () {
      test('Then should be index 2', () {
        // When
        final yGPositionType = YGPositionType.YGPositionTypeAbsolute;

        // Then
        expect(yGPositionType.index, 2);
      });
    });
  });

  group('Given a YGPrintOptions', () {
    group('When it is YGPositionTypeStatic', () {
      test('Then should be index 0', () {
        // When
        final yGPrintOptions = YGPrintOptions.YGPrintOptionsLayout;

        // Then
        expect(yGPrintOptions.index, 0);
      });
    });

    group('When it is YGPrintOptionsStyle', () {
      test('Then should be index 1', () {
        // When
        final yGPrintOptions = YGPrintOptions.YGPrintOptionsStyle;

        // Then
        expect(yGPrintOptions.index, 1);
      });
    });

    group('When it is YGPrintOptionsChildren', () {
      test('Then should be index 2', () {
        // When
        final yGPrintOptions = YGPrintOptions.YGPrintOptionsChildren;

        // Then
        expect(yGPrintOptions.index, 2);
      });
    });
  });

  group('Given a YGUnit', () {
    group('When it is YGUnitUndefined', () {
      test('Then should be index 0', () {
        // When
        final yGUnit = YGUnit.YGUnitUndefined;

        // Then
        expect(yGUnit.index, 0);
      });
    });

    group('When it is YGUnitPoint', () {
      test('Then should be index 1', () {
        // When
        final yGUnit = YGUnit.YGUnitPoint;

        // Then
        expect(yGUnit.index, 1);
      });
    });

    group('When it is YGUnitPercent', () {
      test('Then should be index 2', () {
        // When
        final yGUnit = YGUnit.YGUnitPercent;

        // Then
        expect(yGUnit.index, 2);
      });
    });

    group('When it is YGUnitAuto', () {
      test('Then should be index 3', () {
        // When
        final yGUnit = YGUnit.YGUnitAuto;

        // Then
        expect(yGUnit.index, 3);
      });
    });
  });

  group('Given a YGWrap', () {
    group('When it is YGWrapNoWrap', () {
      test('Then should be index 0', () {
        // When
        final yGWrap = YGWrap.YGWrapNoWrap;

        // Then
        expect(yGWrap.index, 0);
      });
    });

    group('When it is YGWrapWrap', () {
      test('Then should be index 1', () {
        // When
        final yGWrap = YGWrap.YGWrapWrap;

        // Then
        expect(yGWrap.index, 1);
      });
    });

    group('When it is YGWrapWrapReverse', () {
      test('Then should be index 2', () {
        // When
        final yGWrap = YGWrap.YGWrapWrapReverse;

        // Then
        expect(yGWrap.index, 2);
      });
    });
  });
}
