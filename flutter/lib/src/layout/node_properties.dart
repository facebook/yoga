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

import 'package:yoga_engine/src/ffi/mapper.dart';
import 'package:yoga_engine/src/ffi/types.dart';
import 'package:yoga_engine/src/utils/methods.dart';
import 'package:yoga_engine/src/yoga_initializer.dart';

/// Class responsible to holder the pointer to YGNode used in yoga core.
/// This also expose all methods needed to configure the yoga params.
class NodeProperties {
  final _mapper = serviceLocator.get<Mapper>();

  final _node = serviceLocator.get<Mapper>().yGNodeNew();

  Pointer<YGNode> get node => _node;

  YGSize createSize(
    double width,
    double height,
  ) {
    return _mapper.yGCreateSize(width, height);
  }

  void reset() {
    _mapper.yGNodeReset(_node);
  }

  void insertChildAt(NodeProperties child, int index) {
    _mapper.yGNodeInsertChild(_node, child.node, index);
  }

  Pointer<YGNode> getChildAt(int index) {
    return _mapper.yGNodeGetChild(_node, index);
  }

  Pointer<YGNode> getOwner() {
    return _mapper.yGNodeGetOwner(_node);
  }

  int getChildCount() {
    return _mapper.yGNodeGetChildCount(_node);
  }

  void calculateLayout(
    double availableWidth,
    double availableHeight,
  ) {
    _mapper.yGNodeCalculateLayout(
      _node,
      availableWidth,
      availableHeight,
      YGDirection.YGDirectionInherit,
    );
  }

  bool hasMeasureFunc() {
    return _mapper.yGNodeHasMeasureFunc(_node);
  }

  void setMeasureFunc() {
    _mapper.yGNodeSetMeasureFunc(_node, Pointer.fromFunction(measureFunc));
  }

  void setDirection(YGDirection direction) {
    _mapper.yGNodeStyleSetDirection(_node, direction);
  }

  YGDirection getDirection() {
    return _mapper.yGNodeStyleGetDirection(_node);
  }

  void setFlexDirection(YGFlexDirection flexDirection) {
    _mapper.yGNodeStyleSetFlexDirection(_node, flexDirection);
  }

  YGFlexDirection getFlexDirection() {
    return _mapper.yGNodeStyleGetFlexDirection(_node);
  }

  void setJustifyContent(YGJustify justify) {
    _mapper.yGNodeStyleSetJustifyContent(_node, justify);
  }

  YGJustify getJustifyContent() {
    return _mapper.yGNodeStyleGetJustifyContent(_node);
  }

  void setAlignContent(YGAlign align) {
    _mapper.yGNodeStyleSetAlignContent(_node, align);
  }

  YGAlign getAlignContent() {
    return _mapper.yGNodeStyleGetAlignContent(_node);
  }

  void setAlignItems(YGAlign align) {
    _mapper.yGNodeStyleSetAlignItems(_node, align);
  }

  YGAlign getAlignItems() {
    return _mapper.yGNodeStyleGetAlignItems(_node);
  }

  void setAlignSelf(YGAlign align) {
    _mapper.yGNodeStyleSetAlignSelf(_node, align);
  }

  YGAlign getAlignSelf() {
    return _mapper.yGNodeStyleGetAlignSelf(_node);
  }

  void setPositionType(YGPositionType positionType) {
    _mapper.yGNodeStyleSetPositionType(_node, positionType);
  }

  YGPositionType getPositionType() {
    return _mapper.yGNodeStyleGetPositionType(_node);
  }

  void setFlexWrap(YGWrap wrap) {
    _mapper.yGNodeStyleSetFlexWrap(_node, wrap);
  }

  YGWrap getFlexWrap() {
    return _mapper.yGNodeStyleGetFlexWrap(_node);
  }

  void setOverflow(YGOverflow overflow) {
    _mapper.yGNodeStyleSetOverflow(_node, overflow);
  }

  YGOverflow getOverflow() {
    return _mapper.yGNodeStyleGetOverflow(_node);
  }

  void setDisplay(YGDisplay display) {
    _mapper.yGNodeStyleSetDisplay(_node, display);
  }

  YGDisplay getDisplay() {
    return _mapper.yGNodeStyleGetDisplay(_node);
  }

  void setFlex(double flex) {
    _mapper.yGNodeStyleSetFlex(_node, flex);
  }

  double getFlex() {
    return _mapper.yGNodeStyleGetFlex(_node);
  }

  void setGrow(double grow) {
    _mapper.yGNodeStyleSetFlexGrow(_node, grow);
  }

  double getGrow() {
    return _mapper.yGNodeStyleGetFlexGrow(_node);
  }

  void setShrink(double shrink) {
    _mapper.yGNodeStyleSetFlexShrink(_node, shrink);
  }

  double getShrink() {
    return _mapper.yGNodeStyleGetFlexShrink(_node);
  }

  void setBasis(double basis) {
    _mapper.yGNodeStyleSetFlexBasis(_node, basis);
  }

  void setBasisPercent(double basis) {
    _mapper.yGNodeStyleSetFlexBasisPercent(_node, basis);
  }

  void setBasisAuto() {
    _mapper.yGNodeStyleSetFlexBasisAuto(_node);
  }

  YogaValue getBasis() {
    return _mapper.yGNodeStyleGetFlexBasis(_node);
  }

  void setPosition(YGEdge edge, double position) {
    _mapper.yGNodeStyleSetPosition(_node, edge, position);
  }

  void setPositionPercent(YGEdge edge, double position) {
    _mapper.yGNodeStyleSetPositionPercent(_node, edge, position);
  }

  YogaValue getPosition(YGEdge edge) {
    return _mapper.yGNodeStyleGetPosition(_node, edge);
  }

  void setMargin(YGEdge edge, double margin) {
    _mapper.yGNodeStyleSetMargin(_node, edge, margin);
  }

  void setMarginPercent(YGEdge edge, double margin) {
    _mapper.yGNodeStyleSetMarginPercent(_node, edge, margin);
  }

  void setMarginAuto(YGEdge edge) {
    _mapper.yGNodeStyleSetMarginAuto(_node, edge);
  }

  YogaValue getMargin(YGEdge edge) {
    return _mapper.yGNodeStyleGetMargin(_node, edge);
  }

  void setPadding(YGEdge edge, double padding) {
    _mapper.yGNodeStyleSetPadding(_node, edge, padding);
  }

  void setPaddingPercent(YGEdge edge, double padding) {
    _mapper.yGNodeStyleSetPaddingPercent(_node, edge, padding);
  }

  YogaValue getPadding(YGEdge edge, double padding) {
    return _mapper.yGNodeStyleGetPadding(_node, edge);
  }

  void setBorder(YGEdge edge, double border) {
    _mapper.yGNodeStyleSetBorder(_node, edge, border);
  }

  void getBorder(YGEdge edge) {
    _mapper.yGNodeStyleGetBorder(_node, edge);
  }

  void setWidth(double width) {
    _mapper.yGNodeStyleSetWidth(_node, width);
  }

  void setWidthPercent(double width) {
    _mapper.yGNodeStyleSetWidthPercent(_node, width);
  }

  void setWidthAuto() {
    _mapper.yGNodeStyleSetWidthAuto(_node);
  }

  YogaValue getWidth() {
    return _mapper.yGNodeStyleGetWidth(_node);
  }

  void setHeight(double height) {
    _mapper.yGNodeStyleSetHeight(_node, height);
  }

  void setHeightPercent(double height) {
    _mapper.yGNodeStyleSetHeightPercent(_node, height);
  }

  void setHeightAuto() {
    _mapper.yGNodeStyleSetHeightAuto(_node);
  }

  YogaValue getHeight() {
    return _mapper.yGNodeStyleGetHeight(_node);
  }

  void setMinWidth(double minWidth) {
    _mapper.yGNodeStyleSetMinWidth(_node, minWidth);
  }

  void setMinWidthPercent(double minWidth) {
    _mapper.yGNodeStyleSetMinWidthPercent(_node, minWidth);
  }

  YogaValue getMinWidth() {
    return _mapper.yGNodeStyleGetMinWidth(_node);
  }

  void setMinHeight(double minHeight) {
    _mapper.yGNodeStyleSetMinHeight(_node, minHeight);
  }

  void setMinHeightPercent(double minHeight) {
    _mapper.yGNodeStyleSetMinHeightPercent(_node, minHeight);
  }

  YogaValue getMinHeight() {
    return _mapper.yGNodeStyleGetMinHeight(_node);
  }

  void setMaxWidth(double maxWidth) {
    _mapper.yGNodeStyleSetMaxWidth(_node, maxWidth);
  }

  void setMaxWidthPercent(double maxWidth) {
    _mapper.yGNodeStyleSetMaxWidthPercent(_node, maxWidth);
  }

  YogaValue getMaxWidth() {
    return _mapper.yGNodeStyleGetMaxWidth(_node);
  }

  void setMaxHeight(double maxHeight) {
    _mapper.yGNodeStyleSetMaxHeight(_node, maxHeight);
  }

  void setMaxHeightPercent(double maxHeight) {
    _mapper.yGNodeStyleSetMaxHeightPercent(_node, maxHeight);
  }

  YogaValue getMaxHeight() {
    return _mapper.yGNodeStyleGetMaxHeight(_node);
  }

  void setAspectRatio(double aspectRatio) {
    _mapper.yGNodeStyleSetAspectRatio(_node, aspectRatio);
  }

  double getLeft() {
    return _mapper.yGNodeLayoutGetLeft(_node);
  }

  double getTop() {
    return _mapper.yGNodeLayoutGetTop(_node);
  }

  double getRight() {
    return _mapper.yGNodeLayoutGetRight(_node);
  }

  double getBottom() {
    return _mapper.yGNodeLayoutGetBottom(_node);
  }

  double getLayoutWidth() {
    return _mapper.yGNodeLayoutGetWidth(_node);
  }

  double getLayoutHeight() {
    return _mapper.yGNodeLayoutGetHeight(_node);
  }

  YGDirection getLayoutDirection() {
    return _mapper.yGNodeLayoutGetDirection(_node);
  }

  double getLayoutMargin(YGEdge edge) {
    return _mapper.yGNodeLayoutGetMargin(_node, edge);
  }

  double getLayoutBorder(YGEdge edge) {
    return _mapper.yGNodeLayoutGetBorder(_node, edge);
  }

  double getLayoutPadding(YGEdge edge) {
    return _mapper.yGNodeLayoutGetPadding(_node, edge);
  }

  bool isCalculated() {
    return !_mapper.yGNodeLayoutGetWidth(_node).isNaN &&
    !_mapper.yGNodeLayoutGetHeight(_node).isNaN;
  }
}
