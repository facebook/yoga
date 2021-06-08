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

import 'package:yoga_engine/ffi/types.dart';
import 'package:yoga_engine/yoga_initializer.dart';

import 'mapper.dart';

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
  final mapper = serviceLocator.get<Mapper>();
  // TODO this will be implemented in next PR
  return mapper.yGCreateSize(50, 50);
}
