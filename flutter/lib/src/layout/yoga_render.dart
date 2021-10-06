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

import 'package:flutter/foundation.dart';
import 'package:flutter/rendering.dart';
import 'package:flutter/widgets.dart';
import 'package:yoga_engine/src/ffi/types.dart';
import 'package:yoga_engine/src/layout/node_properties.dart';
import 'package:yoga_engine/src/utils/node_helper.dart';
import 'package:yoga_engine/src/utils/node_properties_extensions.dart';

import '../yoga_initializer.dart';

class YogaParentData extends ContainerBoxParentData<RenderBox> {
  NodeProperties? nodeProperties;

  @override
  String toString() => '${super.toString()}; nodeProperties=$nodeProperties';
}

/// Class responsible to measure any flutter widget by the NodeProperties.
/// This can only be placed inside a YogaLayout widget and cannot have another
/// YogaNode as a direct child.
/// Use this class to wrap around any flutter widget. The yoga will be able
/// to calculate the layout size and the children offsets,
/// given this wrapped widget's size.
class YogaNode extends ParentDataWidget<YogaParentData> {
  const YogaNode({
    Key? key,
    required this.nodeProperties,
    required Widget child,
  }) : super(key: key, child: child);

  final NodeProperties nodeProperties;

  @override
  void applyParentData(RenderObject renderObject) {
    assert(renderObject.parentData is YogaParentData);
    final parentData = renderObject.parentData! as YogaParentData;
    bool needsLayout = false;

    if (parentData.nodeProperties != nodeProperties) {
      parentData.nodeProperties = nodeProperties;
      needsLayout = true;
    }

    if (needsLayout) {
      final AbstractNode? targetParent = renderObject.parent;
      if (targetParent is RenderObject) targetParent.markNeedsLayout();
    }
  }

  @override
  Type get debugTypicalAncestorWidgetClass => YogaLayout;

  @override
  void debugFillProperties(DiagnosticPropertiesBuilder properties) {
    super.debugFillProperties(properties);
    properties.add(StringProperty('nodeProperties', nodeProperties.toString()));
  }
}

class RenderYoga extends RenderBox
    with
        ContainerRenderObjectMixin<RenderBox, YogaParentData>,
        RenderBoxContainerDefaultsMixin<RenderBox, YogaParentData>,
        DebugOverflowIndicatorMixin {
  RenderYoga({
    List<RenderBox>? children,
    required NodeProperties nodeProperties,
  }) : _nodeProperties = nodeProperties {
    addAll(children);
  }

  NodeProperties get nodeProperties => _nodeProperties;
  NodeProperties _nodeProperties;

  set nodeProperties(NodeProperties value) {
    if (_nodeProperties != value) {
      _nodeProperties = value;
      markNeedsLayout();
    }
  }

  final _helper = serviceLocator.get<NodeHelper>();

  @override
  void setupParentData(covariant RenderObject child) {
    if (child.parentData is! YogaParentData) {
      child.parentData = YogaParentData();
    }
  }

  NodeProperties _getNodeProperties(YogaParentData yogaParentData) {
    return yogaParentData.nodeProperties!;
  }

  @override
  Size computeDryLayout(BoxConstraints constraints) {
    if (!nodeProperties.isCalculated()) {
      _attachNodesFromWidgetsHierarchy(this);
      nodeProperties.calculateLayout(YGUndefined, YGUndefined);
    }
    return Size(
      nodeProperties.getLayoutWidth(),
      nodeProperties.getLayoutHeight(),
    );
  }

  @override
  void performLayout() {
    if (!nodeProperties.isCalculated()) {
      _attachNodesFromWidgetsHierarchy(this);
      final maxWidth = constraints.maxWidth.isInfinite
          ? YGUndefined
          : constraints.maxWidth.floorToDouble();
      final maxHeight = constraints.maxHeight.isInfinite
          ? YGUndefined
          : constraints.maxHeight.floorToDouble();
      nodeProperties.calculateLayout(maxWidth, maxHeight);
    }
    _applyLayoutToWidgetsHierarchy(getChildrenAsList());

    size = Size(
        nodeProperties.getSanitizedWidth(constraints.maxWidth),
        nodeProperties.getSanitizedHeight(constraints.maxHeight),
    );
  }

  void _attachNodesFromWidgetsHierarchy(RenderYoga renderYoga) {
    final children = renderYoga.getChildrenAsList();
    for (var i = 0; i < children.length; i++) {
      final child = children[i];
      if (child is RenderYoga) {
        renderYoga.nodeProperties.insertChildAt(child.nodeProperties, i);
        _attachNodesFromWidgetsHierarchy(child);
      } else {
        final yogaParentData = child.parentData as YogaParentData;
        assert(() {
          if (yogaParentData.nodeProperties != null) {
            return true;
          }
          throw FlutterError('To use YogaLayout, you must declare every child '
              'inside a YogaNode or YogaLayout component');
        }());
        final childYogaNode = _getNodeProperties(yogaParentData);
        renderYoga.nodeProperties.insertChildAt(childYogaNode, i);
        _setMeasureFunction(child, childYogaNode);
      }
    }
  }

  void _setMeasureFunction(RenderBox child, NodeProperties childYogaNode) {
    _helper.setRenderBoxToNode(child, childYogaNode.node);
    childYogaNode.setMeasureFunc();
  }

  void _applyLayoutToWidgetsHierarchy(List<RenderBox> children) {
    for (var i = 0; i < children.length; i++) {
      final child = children[i];
      final yogaParentData = child.parentData as YogaParentData;
      late Pointer<YGNode> node;
      if (child is RenderYoga) {
        node = child.nodeProperties.node;
      } else {
        node = _getNodeProperties(yogaParentData).node;
      }
      yogaParentData.offset = Offset(
        _helper.getLeft(node),
        _helper.getTop(node),
      );
      late BoxConstraints childConstraints;
      childConstraints = BoxConstraints.tight(
        Size(
          _helper.getLayoutWidth(node),
          _helper.getLayoutHeight(node),
        ),
      );
      child.layout(childConstraints, parentUsesSize: true);
      _helper.removeNodeReference(node);
    }
  }

  @override
  bool hitTestChildren(BoxHitTestResult result, {required Offset position}) {
    return defaultHitTestChildren(result, position: position);
  }

  @override
  void paint(PaintingContext context, Offset offset) {
    defaultPaint(context, offset);
  }
}

/// Class responsible to measure each YogaNode by the NodeProperties param.
/// Only YogaNode or YogaLayout widgets are enabled to be children.
/// This widget has no restriction to be positioned.
class YogaLayout extends MultiChildRenderObjectWidget {
  YogaLayout({
    Key? key,
    required this.nodeProperties,
    List<Widget> children = const <Widget>[],
  }) : super(key: key, children: children);

  final NodeProperties nodeProperties;

  @override
  RenderObject createRenderObject(BuildContext context) {
    return RenderYoga(nodeProperties: nodeProperties);
  }

  @override
  void updateRenderObject(
    BuildContext context,
    covariant RenderYoga renderObject,
  ) {
    renderObject.nodeProperties = nodeProperties;
  }

  @override
  void debugFillProperties(DiagnosticPropertiesBuilder properties) {
    super.debugFillProperties(properties);
    properties.add(StringProperty('nodeProperties', nodeProperties.toString()));
  }
}
