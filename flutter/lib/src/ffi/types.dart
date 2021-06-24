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

class YGConfig extends Opaque {}

class YGNode extends Opaque {}

const double YGUndefined = double.nan;

enum YGAlign {
  YGAlignAuto,
  YGAlignFlexStart,
  YGAlignCenter,
  YGAlignFlexEnd,
  YGAlignStretch,
  YGAlignBaseline,
  YGAlignSpaceBetween,
  YGAlignSpaceAround
}

enum YGDimension {
  YGDimensionWidth,
  YGDimensionHeight,
}

enum YGDirection {
  YGDirectionInherit,
  YGDirectionLTR,
  YGDirectionRTL,
}

enum YGDisplay {
  YGDisplayFlex,
  YGDisplayNone,
}

enum YGEdge {
  YGEdgeLeft,
  YGEdgeTop,
  YGEdgeRight,
  YGEdgeBottom,
  YGEdgeStart,
  YGEdgeEnd,
  YGEdgeHorizontal,
  YGEdgeVertical,
  YGEdgeAll,
}

enum YGFlexDirection {
  YGFlexDirectionColumn,
  YGFlexDirectionColumnReverse,
  YGFlexDirectionRow,
  YGFlexDirectionRowReverse,
}

enum YGJustify {
  YGJustifyFlexStart,
  YGJustifyCenter,
  YGJustifyFlexEnd,
  YGJustifySpaceBetween,
  YGJustifySpaceAround,
  YGJustifySpaceEvenly,
}

enum YGLogLevel {
  YGLogLevelError,
  YGLogLevelWarn,
  YGLogLevelInfo,
  YGLogLevelDebug,
  YGLogLevelVerbose,
  YGLogLevelFatal,
}

enum YGMeasureMode {
  YGMeasureModeUndefined,
  YGMeasureModeExactly,
  YGMeasureModeAtMost,
}

enum YGNodeType {
  YGNodeTypeDefault,
  YGNodeTypeText,
}

enum YGOverflow {
  YGOverflowVisible,
  YGOverflowHidden,
  YGOverflowScroll,
}

enum YGPositionType {
  YGPositionTypeStatic,
  YGPositionTypeRelative,
  YGPositionTypeAbsolute,
}

enum YGPrintOptions {
  YGPrintOptionsLayout,
  YGPrintOptionsStyle,
  YGPrintOptionsChildren,
}

enum YGUnit {
  YGUnitUndefined,
  YGUnitPoint,
  YGUnitPercent,
  YGUnitAuto,
}

enum YGWrap {
  YGWrapNoWrap,
  YGWrapWrap,
  YGWrapWrapReverse,
}

class YGValue extends Struct {
  @Float()
  external double value;

  @Int32()
  external int unit;
}

class YogaValue {
  final double value;
  final YGUnit unit;

  YogaValue(this.value, this.unit);
}

class YGSize extends Struct {
  @Float()
  external double width;

  @Float()
  external double height;
}

class YogaSize {
  final double width;
  final double height;

  YogaSize(this.width, this.height);
}

class VaListTag extends Struct {
  @Uint32()
  // ignore: non_constant_identifier_names
  external int gp_offset;

  @Uint32()
  // ignore: non_constant_identifier_names
  external int fp_offset;

  // ignore: non_constant_identifier_names
  external Pointer<Void> overflow_arg_area;

  // ignore: non_constant_identifier_names
  external Pointer<Void> reg_save_area;
}
