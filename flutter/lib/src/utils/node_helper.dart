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

import 'package:flutter/widgets.dart';
import 'package:yoga_engine/src/ffi/mapper.dart';

import '../../yoga_engine.dart';

class NodeHelper {

  final Mapper _mapper;

  NodeHelper(Mapper mapper) : _mapper = mapper;

  final _binding = Map<Pointer<YGNode>, RenderBox>();

  void setRenderBoxToNode(RenderBox renderBox, Pointer<YGNode> node) {
    _binding[node] = renderBox;
  }

  void removeNodeReference(Pointer<YGNode> node) {
    _binding.remove(node);
  }

  RenderBox? getRenderBoxFromNode(Pointer<YGNode> node) {
    return _binding[node];
  }

  double getLeft(Pointer<YGNode> node) {
    return _mapper.yGNodeLayoutGetLeft(node);
  }

  double getTop(Pointer<YGNode> node) {
    return _mapper.yGNodeLayoutGetTop(node);
  }

  double getLayoutWidth(Pointer<YGNode> node) {
    return _mapper.yGNodeLayoutGetWidth(node);
  }

  double getLayoutHeight(Pointer<YGNode> node) {
    return _mapper.yGNodeLayoutGetHeight(node);
  }
}
