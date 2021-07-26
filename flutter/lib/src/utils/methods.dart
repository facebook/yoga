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
import 'dart:io';
import 'dart:math';

import 'package:flutter/rendering.dart';
import 'package:yoga_engine/src/ffi/mapper.dart';

import '../../yoga_engine.dart';
import '../yoga_initializer.dart';
import 'node_helper.dart';

DynamicLibrary loadYoga() {
  if (Platform.environment.containsKey('FLUTTER_TEST')) {
    return DynamicLibrary.open('test/libyogacore.dylib');
  }
  return Platform.isAndroid
      ? DynamicLibrary.open("libyogacore.so")
      : DynamicLibrary.process();
}

YGSize measureFunc(
  Pointer<YGNode> node,
  double width,
  int widthMode,
  double height,
  int heightMode,
) {
  final helper = serviceLocator.get<NodeHelper>();
  final mapper = serviceLocator.get<Mapper>();

  final widthMeasureMode = YGMeasureMode.values[widthMode];
  final heightMeasureMode = YGMeasureMode.values[heightMode];

  final constrainedWidth =
      (widthMeasureMode == YGMeasureMode.YGMeasureModeUndefined)
          ? double.infinity
          : width;
  final constrainedHeight =
      (heightMeasureMode == YGMeasureMode.YGMeasureModeUndefined)
          ? double.infinity
          : height;

  final renderObject = helper.getRenderBoxFromNode(node);
  final constraints = BoxConstraints.loose(
    Size(constrainedWidth, constrainedHeight),
  );
  double objectWidth;
  double objectHeight;
  if (renderObject is RenderMouseRegion) {
    objectWidth = renderObject.getMaxIntrinsicWidth(constrainedWidth);
    objectHeight = renderObject.getMaxIntrinsicHeight(constrainedHeight);
  } else {
    final renderObjectSize = renderObject?.getDryLayout(constraints);
    objectWidth = renderObjectSize?.width ?? 0;
    objectHeight = renderObjectSize?.height ?? 0;
  }

  final sanitizedWidth = _sanitizeMeasurement(
    constrainedWidth,
    objectWidth,
    widthMeasureMode,
  );
  final sanitizedHeight = _sanitizeMeasurement(
    constrainedHeight,
    objectHeight,
    heightMeasureMode,
  );

  return mapper.yGCreateSize(sanitizedWidth, sanitizedHeight);
}

double _sanitizeMeasurement(
  double constrainedSize,
  double measuredSize,
  YGMeasureMode measureMode,
) {
  double result;
  if (measureMode == YGMeasureMode.YGMeasureModeExactly) {
    result = constrainedSize;
  } else if (measureMode == YGMeasureMode.YGMeasureModeAtMost) {
    result = min(constrainedSize, measuredSize);
  } else {
    result = measuredSize;
  }
  return result;
}
