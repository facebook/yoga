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

import 'types.dart';

typedef CYgCreateSize = YGSize Function(
  Float width,
  Float height,
);

typedef DartYgCreateSize = YGSize Function(
  double width,
  double height,
);

typedef CYgNodeNew = Pointer<YGNode> Function();

typedef DartYgNodeNew = Pointer<YGNode> Function();

typedef CYgNodeNewWithConfig = Pointer<YGNode> Function(
  Pointer<YGConfig> config,
);

typedef DartYgNodeNewWithConfig = Pointer<YGNode> Function(
  Pointer<YGConfig> config,
);

typedef CYgNodeClone = Pointer<YGNode> Function(
  Pointer<YGNode> node,
);

typedef DartYgNodeClone = Pointer<YGNode> Function(
  Pointer<YGNode> node,
);

typedef CYgNodeFree = Void Function(
  Pointer<YGNode> node,
);

typedef DartYgNodeFree = void Function(
  Pointer<YGNode> node,
);

typedef YGNodeCleanupFunc = Void Function(
  Pointer<YGNode>,
);

typedef CYgNodeFreeRecursiveWithCleanupFunc = Void Function(
  Pointer<YGNode> node,
  Pointer<NativeFunction<YGNodeCleanupFunc>> cleanup,
);

typedef DartYgNodeFreeRecursiveWithCleanupFunc = void Function(
  Pointer<YGNode> node,
  Pointer<NativeFunction<YGNodeCleanupFunc>> cleanup,
);

typedef CYgNodeFreeRecursive = Void Function(
  Pointer<YGNode> node,
);

typedef DartYgNodeFreeRecursive = void Function(
  Pointer<YGNode> node,
);

typedef CYgNodeReset = Void Function(
  Pointer<YGNode> node,
);

typedef DartYgNodeReset = void Function(
  Pointer<YGNode> node,
);

typedef CYgNodeInsertChild = Void Function(
  Pointer<YGNode> node,
  Pointer<YGNode> child,
  Uint32 index,
);

typedef DartYgNodeInsertChild = void Function(
  Pointer<YGNode> node,
  Pointer<YGNode> child,
  int index,
);

typedef CYgNodeSwapChild = Void Function(
  Pointer<YGNode> node,
  Pointer<YGNode> child,
  Uint32 index,
);

typedef DartYgNodeSwapChild = void Function(
  Pointer<YGNode> node,
  Pointer<YGNode> child,
  int index,
);

typedef CYgNodeRemoveChild = Void Function(
  Pointer<YGNode> node,
  Pointer<YGNode> child,
);

typedef DartYgNodeRemoveChild = void Function(
  Pointer<YGNode> node,
  Pointer<YGNode> child,
);

typedef CYgNodeRemoveAllChildren = Void Function(
  Pointer<YGNode> node,
);

typedef DartYgNodeRemoveAllChildren = void Function(
  Pointer<YGNode> node,
);

typedef CYgNodeGetChild = Pointer<YGNode> Function(
  Pointer<YGNode> node,
  Uint32 index,
);

typedef DartYgNodeGetChild = Pointer<YGNode> Function(
  Pointer<YGNode> node,
  int index,
);

typedef CYgNodeGetOwner = Pointer<YGNode> Function(
  Pointer<YGNode> node,
);

typedef DartYgNodeGetOwner = Pointer<YGNode> Function(
  Pointer<YGNode> node,
);

typedef CYgNodeGetParent = Pointer<YGNode> Function(
  Pointer<YGNode> node,
);

typedef DartYgNodeGetParent = Pointer<YGNode> Function(
  Pointer<YGNode> node,
);

typedef CYgNodeGetChildCount = Uint32 Function(
  Pointer<YGNode> node,
);

typedef DartYgNodeGetChildCount = int Function(
  Pointer<YGNode> node,
);

typedef CYgNodeSetChildren = Void Function(
  Pointer<YGNode> owner,
  Pointer<Pointer<YGNode>> children,
  Uint32 count,
);

typedef DartYgNodeSetChildren = void Function(
  Pointer<YGNode> owner,
  Pointer<Pointer<YGNode>> children,
  int count,
);

typedef CYgNodeSetIsReferenceBaseline = Void Function(
  Pointer<YGNode> node,
  Uint8 isReferenceBaseline,
);

typedef DartYgNodeSetIsReferenceBaseline = void Function(
  Pointer<YGNode> node,
  int isReferenceBaseline,
);

typedef CYgNodeIsReferenceBaseline = Uint8 Function(
  Pointer<YGNode> node,
);

typedef DartYgNodeIsReferenceBaseline = int Function(
  Pointer<YGNode> node,
);

typedef CYgNodeCalculateLayout = Void Function(
  Pointer<YGNode> node,
  Float availableWidth,
  Float availableHeight,
  Int32 ownerDirection,
);

typedef DartYgNodeCalculateLayout = void Function(
  Pointer<YGNode> node,
  double availableWidth,
  double availableHeight,
  int ownerDirection,
);

typedef CYgNodeMarkDirty = Void Function(
  Pointer<YGNode> node,
);

typedef DartYgNodeMarkDirty = void Function(
  Pointer<YGNode> node,
);

typedef CYgNodeMarkDirtyAndPropagateToDescendants = Void Function(
  Pointer<YGNode> node,
);

typedef DartYgNodeMarkDirtyAndPropagateToDescendants = void Function(
  Pointer<YGNode> node,
);

typedef CYgNodePrint = Void Function(
  Pointer<YGNode> node,
  Int32 options,
);

typedef DartYgNodePrint = void Function(
  Pointer<YGNode> node,
  int options,
);

typedef CYgFloatIsUndefined = Uint8 Function(
  Float value,
);

typedef DartYgFloatIsUndefined = int Function(
  double value,
);

typedef CYgNodeCanUseCachedMeasurement = Uint8 Function(
  Int32 widthMode,
  Float width,
  Int32 heightMode,
  Float height,
  Int32 lastWidthMode,
  Float lastWidth,
  Int32 lastHeightMode,
  Float lastHeight,
  Float lastComputedWidth,
  Float lastComputedHeight,
  Float marginRow,
  Float marginColumn,
  Pointer<YGConfig> config,
);

typedef DartYgNodeCanUseCachedMeasurement = int Function(
  int widthMode,
  double width,
  int heightMode,
  double height,
  int lastWidthMode,
  double lastWidth,
  int lastHeightMode,
  double lastHeight,
  double lastComputedWidth,
  double lastComputedHeight,
  double marginRow,
  double marginColumn,
  Pointer<YGConfig> config,
);

typedef CYgNodeCopyStyle = Void Function(
  Pointer<YGNode> dstNode,
  Pointer<YGNode> srcNode,
);

typedef DartYgNodeCopyStyle = void Function(
  Pointer<YGNode> dstNode,
  Pointer<YGNode> srcNode,
);

typedef CYgNodeGetContext = Pointer<Void> Function(
  Pointer<YGNode> node,
);

typedef DartYgNodeGetContext = Pointer<Void> Function(
  Pointer<YGNode> node,
);

typedef CYgNodeSetContext = Void Function(
  Pointer<YGNode> node,
  Pointer<Void> context,
);

typedef DartYgNodeSetContext = void Function(
  Pointer<YGNode> node,
  Pointer<Void> context,
);

typedef CYgConfigSetPrintTreeFlag = Void Function(
  Pointer<YGConfig> config,
  Uint8 enabled,
);

typedef DartYgConfigSetPrintTreeFlag = void Function(
  Pointer<YGConfig> config,
  int enabled,
);

typedef CYgNodeHasMeasureFunc = Uint8 Function(
  Pointer<YGNode> node,
);

typedef DartYgNodeHasMeasureFunc = int Function(
  Pointer<YGNode> node,
);

typedef YGMeasureFunc = YGSize Function(
  Pointer<YGNode>,
  Float,
  Int32,
  Float,
  Int32,
);

typedef CYgNodeSetMeasureFunc = Void Function(
  Pointer<YGNode> node,
  Pointer<NativeFunction<YGMeasureFunc>> measureFunc,
);

typedef DartYgNodeSetMeasureFunc = void Function(
  Pointer<YGNode> node,
  Pointer<NativeFunction<YGMeasureFunc>> measureFunc,
);

typedef CYgNodeHasBaselineFunc = Uint8 Function(
  Pointer<YGNode> node,
);

typedef DartYgNodeHasBaselineFunc = int Function(
  Pointer<YGNode> node,
);

typedef YGBaselineFunc = Float Function(
  Pointer<YGNode>,
  Float,
  Float,
);

typedef CYgNodeSetBaselineFunc = Void Function(
  Pointer<YGNode> node,
  Pointer<NativeFunction<YGBaselineFunc>> baselineFunc,
);

typedef DartYgNodeSetBaselineFunc = void Function(
  Pointer<YGNode> node,
  Pointer<NativeFunction<YGBaselineFunc>> baselineFunc,
);

typedef YGDirtiedFunc = Void Function(
  Pointer<YGNode>,
);

typedef CYgNodeGetDirtiedFunc = Pointer<NativeFunction<YGDirtiedFunc>> Function(
  Pointer<YGNode> node,
);

typedef DartYgNodeGetDirtiedFunc = Pointer<NativeFunction<YGDirtiedFunc>>
    Function(
  Pointer<YGNode> node,
);

typedef CYgNodeSetDirtiedFunc = Void Function(
  Pointer<YGNode> node,
  Pointer<NativeFunction<YGDirtiedFunc>> dirtiedFunc,
);

typedef DartYgNodeSetDirtiedFunc = void Function(
  Pointer<YGNode> node,
  Pointer<NativeFunction<YGDirtiedFunc>> dirtiedFunc,
);

typedef YGPrintFunc = Void Function(
  Pointer<YGNode>,
);

typedef CYgNodeSetPrintFunc = Void Function(
  Pointer<YGNode> node,
  Pointer<NativeFunction<YGPrintFunc>> printFunc,
);

typedef DartYgNodeSetPrintFunc = void Function(
  Pointer<YGNode> node,
  Pointer<NativeFunction<YGPrintFunc>> printFunc,
);

typedef CYgNodeGetHasNewLayout = Uint8 Function(
  Pointer<YGNode> node,
);

typedef DartYgNodeGetHasNewLayout = int Function(
  Pointer<YGNode> node,
);

typedef CYgNodeSetHasNewLayout = Void Function(
  Pointer<YGNode> node,
  Uint8 hasNewLayout,
);

typedef DartYgNodeSetHasNewLayout = void Function(
  Pointer<YGNode> node,
  int hasNewLayout,
);

typedef CYgNodeGetNodeType = Int32 Function(
  Pointer<YGNode> node,
);

typedef DartYgNodeGetNodeType = int Function(
  Pointer<YGNode> node,
);

typedef CYgNodeSetNodeType = Void Function(
  Pointer<YGNode> node,
  Int32 nodeType,
);

typedef DartYgNodeSetNodeType = void Function(
  Pointer<YGNode> node,
  int nodeType,
);

typedef CYgNodeIsDirty = Uint8 Function(
  Pointer<YGNode> node,
);

typedef DartYgNodeIsDirty = int Function(
  Pointer<YGNode> node,
);

typedef CYgNodeLayoutGetDidUseLegacyFlag = Uint8 Function(
  Pointer<YGNode> node,
);

typedef DartYgNodeLayoutGetDidUseLegacyFlag = int Function(
  Pointer<YGNode> node,
);

typedef CYgNodeStyleSetDirection = Void Function(
  Pointer<YGNode> node,
  Int32 direction,
);

typedef DartYgNodeStyleSetDirection = void Function(
  Pointer<YGNode> node,
  int direction,
);

typedef CYgNodeStyleGetDirection = Int32 Function(
  Pointer<YGNode> node,
);

typedef DartYgNodeStyleGetDirection = int Function(
  Pointer<YGNode> node,
);

typedef CYgNodeStyleSetFlexDirection = Void Function(
  Pointer<YGNode> node,
  Int32 flexDirection,
);

typedef DartYgNodeStyleSetFlexDirection = void Function(
  Pointer<YGNode> node,
  int flexDirection,
);

typedef CYgNodeStyleGetFlexDirection = Int32 Function(
  Pointer<YGNode> node,
);

typedef DartYgNodeStyleGetFlexDirection = int Function(
  Pointer<YGNode> node,
);

typedef CYgNodeStyleSetJustifyContent = Void Function(
  Pointer<YGNode> node,
  Int32 justifyContent,
);

typedef DartYgNodeStyleSetJustifyContent = void Function(
  Pointer<YGNode> node,
  int justifyContent,
);

typedef CYgNodeStyleGetJustifyContent = Int32 Function(
  Pointer<YGNode> node,
);

typedef DartYgNodeStyleGetJustifyContent = int Function(
  Pointer<YGNode> node,
);

typedef CYgNodeStyleSetAlignContent = Void Function(
  Pointer<YGNode> node,
  Int32 alignContent,
);

typedef DartYgNodeStyleSetAlignContent = void Function(
  Pointer<YGNode> node,
  int alignContent,
);

typedef CYgNodeStyleGetAlignContent = Int32 Function(
  Pointer<YGNode> node,
);

typedef DartYgNodeStyleGetAlignContent = int Function(
  Pointer<YGNode> node,
);

typedef CYgNodeStyleSetAlignItems = Void Function(
  Pointer<YGNode> node,
  Int32 alignItems,
);

typedef DartYgNodeStyleSetAlignItems = void Function(
  Pointer<YGNode> node,
  int alignItems,
);

typedef CYgNodeStyleGetAlignItems = Int32 Function(
  Pointer<YGNode> node,
);

typedef DartYgNodeStyleGetAlignItems = int Function(
  Pointer<YGNode> node,
);

typedef CYgNodeStyleSetAlignSelf = Void Function(
  Pointer<YGNode> node,
  Int32 alignSelf,
);

typedef DartYgNodeStyleSetAlignSelf = void Function(
  Pointer<YGNode> node,
  int alignSelf,
);

typedef CYgNodeStyleGetAlignSelf = Int32 Function(
  Pointer<YGNode> node,
);

typedef DartYgNodeStyleGetAlignSelf = int Function(
  Pointer<YGNode> node,
);

typedef CYgNodeStyleSetPositionType = Void Function(
  Pointer<YGNode> node,
  Int32 positionType,
);

typedef DartYgNodeStyleSetPositionType = void Function(
  Pointer<YGNode> node,
  int positionType,
);

typedef CYgNodeStyleGetPositionType = Int32 Function(
  Pointer<YGNode> node,
);

typedef DartYgNodeStyleGetPositionType = int Function(
  Pointer<YGNode> node,
);

typedef CYgNodeStyleSetFlexWrap = Void Function(
  Pointer<YGNode> node,
  Int32 flexWrap,
);

typedef DartYgNodeStyleSetFlexWrap = void Function(
  Pointer<YGNode> node,
  int flexWrap,
);

typedef CYgNodeStyleGetFlexWrap = Int32 Function(
  Pointer<YGNode> node,
);

typedef DartYgNodeStyleGetFlexWrap = int Function(
  Pointer<YGNode> node,
);

typedef CYgNodeStyleSetOverflow = Void Function(
  Pointer<YGNode> node,
  Int32 overflow,
);

typedef DartYgNodeStyleSetOverflow = void Function(
  Pointer<YGNode> node,
  int overflow,
);

typedef CYgNodeStyleGetOverflow = Int32 Function(
  Pointer<YGNode> node,
);

typedef DartYgNodeStyleGetOverflow = int Function(
  Pointer<YGNode> node,
);

typedef CYgNodeStyleSetDisplay = Void Function(
  Pointer<YGNode> node,
  Int32 display,
);

typedef DartYgNodeStyleSetDisplay = void Function(
  Pointer<YGNode> node,
  int display,
);

typedef CYgNodeStyleGetDisplay = Int32 Function(
  Pointer<YGNode> node,
);

typedef DartYgNodeStyleGetDisplay = int Function(
  Pointer<YGNode> node,
);

typedef CYgNodeStyleSetFlex = Void Function(
  Pointer<YGNode> node,
  Float flex,
);

typedef DartYgNodeStyleSetFlex = void Function(
  Pointer<YGNode> node,
  double flex,
);

typedef CYgNodeStyleGetFlex = Float Function(
  Pointer<YGNode> node,
);

typedef DartYgNodeStyleGetFlex = double Function(
  Pointer<YGNode> node,
);

typedef CYgNodeStyleSetFlexGrow = Void Function(
  Pointer<YGNode> node,
  Float flexGrow,
);

typedef DartYgNodeStyleSetFlexGrow = void Function(
  Pointer<YGNode> node,
  double flexGrow,
);

typedef CYgNodeStyleGetFlexGrow = Float Function(
  Pointer<YGNode> node,
);

typedef DartYgNodeStyleGetFlexGrow = double Function(
  Pointer<YGNode> node,
);

typedef CYgNodeStyleSetFlexShrink = Void Function(
  Pointer<YGNode> node,
  Float flexShrink,
);

typedef DartYgNodeStyleSetFlexShrink = void Function(
  Pointer<YGNode> node,
  double flexShrink,
);

typedef CYgNodeStyleGetFlexShrink = Float Function(
  Pointer<YGNode> node,
);

typedef DartYgNodeStyleGetFlexShrink = double Function(
  Pointer<YGNode> node,
);

typedef CYgNodeStyleSetFlexBasis = Void Function(
  Pointer<YGNode> node,
  Float flexBasis,
);

typedef DartYgNodeStyleSetFlexBasis = void Function(
  Pointer<YGNode> node,
  double flexBasis,
);

typedef CYgNodeStyleSetFlexBasisPercent = Void Function(
  Pointer<YGNode> node,
  Float flexBasis,
);

typedef DartYgNodeStyleSetFlexBasisPercent = void Function(
  Pointer<YGNode> node,
  double flexBasis,
);

typedef CYgNodeStyleSetFlexBasisAuto = Void Function(
  Pointer<YGNode> node,
);

typedef DartYgNodeStyleSetFlexBasisAuto = void Function(
  Pointer<YGNode> node,
);

typedef CYgNodeStyleGetFlexBasis = YGValue Function(
  Pointer<YGNode> node,
);

typedef DartYgNodeStyleGetFlexBasis = YGValue Function(
  Pointer<YGNode> node,
);

typedef CYgNodeStyleSetPosition = Void Function(
  Pointer<YGNode> node,
  Int32 edge,
  Float position,
);

typedef DartYgNodeStyleSetPosition = void Function(
  Pointer<YGNode> node,
  int edge,
  double position,
);

typedef CYgNodeStyleSetPositionPercent = Void Function(
  Pointer<YGNode> node,
  Int32 edge,
  Float position,
);

typedef DartYgNodeStyleSetPositionPercent = void Function(
  Pointer<YGNode> node,
  int edge,
  double position,
);

typedef CYgNodeStyleGetPosition = YGValue Function(
  Pointer<YGNode> node,
  Int32 edge,
);

typedef DartYgNodeStyleGetPosition = YGValue Function(
  Pointer<YGNode> node,
  int edge,
);

typedef CYgNodeStyleSetMargin = Void Function(
  Pointer<YGNode> node,
  Int32 edge,
  Float margin,
);

typedef DartYgNodeStyleSetMargin = void Function(
  Pointer<YGNode> node,
  int edge,
  double margin,
);

typedef CYgNodeStyleSetMarginPercent = Void Function(
  Pointer<YGNode> node,
  Int32 edge,
  Float margin,
);

typedef DartYgNodeStyleSetMarginPercent = void Function(
  Pointer<YGNode> node,
  int edge,
  double margin,
);

typedef CYgNodeStyleSetMarginAuto = Void Function(
  Pointer<YGNode> node,
  Int32 edge,
);

typedef DartYgNodeStyleSetMarginAuto = void Function(
  Pointer<YGNode> node,
  int edge,
);

typedef CYgNodeStyleGetMargin = YGValue Function(
  Pointer<YGNode> node,
  Int32 edge,
);

typedef DartYgNodeStyleGetMargin = YGValue Function(
  Pointer<YGNode> node,
  int edge,
);

typedef CYgNodeStyleSetPadding = Void Function(
  Pointer<YGNode> node,
  Int32 edge,
  Float padding,
);

typedef DartYgNodeStyleSetPadding = void Function(
  Pointer<YGNode> node,
  int edge,
  double padding,
);

typedef CYgNodeStyleSetPaddingPercent = Void Function(
  Pointer<YGNode> node,
  Int32 edge,
  Float padding,
);

typedef DartYgNodeStyleSetPaddingPercent = void Function(
  Pointer<YGNode> node,
  int edge,
  double padding,
);

typedef CYgNodeStyleGetPadding = YGValue Function(
  Pointer<YGNode> node,
  Int32 edge,
);

typedef DartYgNodeStyleGetPadding = YGValue Function(
  Pointer<YGNode> node,
  int edge,
);

typedef CYgNodeStyleSetBorder = Void Function(
  Pointer<YGNode> node,
  Int32 edge,
  Float border,
);

typedef DartYgNodeStyleSetBorder = void Function(
  Pointer<YGNode> node,
  int edge,
  double border,
);

typedef CYgNodeStyleGetBorder = Float Function(
  Pointer<YGNode> node,
  Int32 edge,
);

typedef DartYgNodeStyleGetBorder = double Function(
  Pointer<YGNode> node,
  int edge,
);

typedef CYgNodeStyleSetWidth = Void Function(
  Pointer<YGNode> node,
  Float width,
);

typedef DartYgNodeStyleSetWidth = void Function(
  Pointer<YGNode> node,
  double width,
);

typedef CYgNodeStyleSetWidthPercent = Void Function(
  Pointer<YGNode> node,
  Float width,
);

typedef DartYgNodeStyleSetWidthPercent = void Function(
  Pointer<YGNode> node,
  double width,
);

typedef CYgNodeStyleSetWidthAuto = Void Function(
  Pointer<YGNode> node,
);

typedef DartYgNodeStyleSetWidthAuto = void Function(
  Pointer<YGNode> node,
);

typedef CYgNodeStyleGetWidth = YGValue Function(
  Pointer<YGNode> node,
);

typedef DartYgNodeStyleGetWidth = YGValue Function(
  Pointer<YGNode> node,
);

typedef CYgNodeStyleSetHeight = Void Function(
  Pointer<YGNode> node,
  Float height,
);

typedef DartYgNodeStyleSetHeight = void Function(
  Pointer<YGNode> node,
  double height,
);

typedef CYgNodeStyleSetHeightPercent = Void Function(
  Pointer<YGNode> node,
  Float height,
);

typedef DartYgNodeStyleSetHeightPercent = void Function(
  Pointer<YGNode> node,
  double height,
);

typedef CYgNodeStyleSetHeightAuto = Void Function(
  Pointer<YGNode> node,
);

typedef DartYgNodeStyleSetHeightAuto = void Function(
  Pointer<YGNode> node,
);

typedef CYgNodeStyleGetHeight = YGValue Function(
  Pointer<YGNode> node,
);

typedef DartYgNodeStyleGetHeight = YGValue Function(
  Pointer<YGNode> node,
);

typedef CYgNodeStyleSetMinWidth = Void Function(
  Pointer<YGNode> node,
  Float minWidth,
);

typedef DartYgNodeStyleSetMinWidth = void Function(
  Pointer<YGNode> node,
  double minWidth,
);

typedef CYgNodeStyleSetMinWidthPercent = Void Function(
  Pointer<YGNode> node,
  Float minWidth,
);

typedef DartYgNodeStyleSetMinWidthPercent = void Function(
  Pointer<YGNode> node,
  double minWidth,
);

typedef CYgNodeStyleGetMinWidth = YGValue Function(
  Pointer<YGNode> node,
);

typedef DartYgNodeStyleGetMinWidth = YGValue Function(
  Pointer<YGNode> node,
);

typedef CYgNodeStyleSetMinHeight = Void Function(
  Pointer<YGNode> node,
  Float minHeight,
);

typedef DartYgNodeStyleSetMinHeight = void Function(
  Pointer<YGNode> node,
  double minHeight,
);

typedef CYgNodeStyleSetMinHeightPercent = Void Function(
  Pointer<YGNode> node,
  Float minHeight,
);

typedef DartYgNodeStyleSetMinHeightPercent = void Function(
  Pointer<YGNode> node,
  double minHeight,
);

typedef CYgNodeStyleGetMinHeight = YGValue Function(
  Pointer<YGNode> node,
);

typedef DartYgNodeStyleGetMinHeight = YGValue Function(
  Pointer<YGNode> node,
);

typedef CYgNodeStyleSetMaxWidth = Void Function(
  Pointer<YGNode> node,
  Float maxWidth,
);

typedef DartYgNodeStyleSetMaxWidth = void Function(
  Pointer<YGNode> node,
  double maxWidth,
);

typedef CYgNodeStyleSetMaxWidthPercent = Void Function(
  Pointer<YGNode> node,
  Float maxWidth,
);

typedef DartYgNodeStyleSetMaxWidthPercent = void Function(
  Pointer<YGNode> node,
  double maxWidth,
);

typedef CYgNodeStyleGetMaxWidth = YGValue Function(
  Pointer<YGNode> node,
);

typedef DartYgNodeStyleGetMaxWidth = YGValue Function(
  Pointer<YGNode> node,
);

typedef CYgNodeStyleSetMaxHeight = Void Function(
  Pointer<YGNode> node,
  Float maxHeight,
);

typedef DartYgNodeStyleSetMaxHeight = void Function(
  Pointer<YGNode> node,
  double maxHeight,
);

typedef CYgNodeStyleSetMaxHeightPercent = Void Function(
  Pointer<YGNode> node,
  Float maxHeight,
);

typedef DartYgNodeStyleSetMaxHeightPercent = void Function(
  Pointer<YGNode> node,
  double maxHeight,
);

typedef CYgNodeStyleGetMaxHeight = YGValue Function(
  Pointer<YGNode> node,
);

typedef DartYgNodeStyleGetMaxHeight = YGValue Function(
  Pointer<YGNode> node,
);

typedef CYgNodeStyleSetAspectRatio = Void Function(
  Pointer<YGNode> node,
  Float aspectRatio,
);

typedef DartYgNodeStyleSetAspectRatio = void Function(
  Pointer<YGNode> node,
  double aspectRatio,
);

typedef CYgNodeStyleGetAspectRatio = Float Function(
  Pointer<YGNode> node,
);

typedef DartYgNodeStyleGetAspectRatio = double Function(
  Pointer<YGNode> node,
);

typedef CYgNodeLayoutGetLeft = Float Function(
  Pointer<YGNode> node,
);

typedef DartYgNodeLayoutGetLeft = double Function(
  Pointer<YGNode> node,
);

typedef CYgNodeLayoutGetTop = Float Function(
  Pointer<YGNode> node,
);

typedef DartYgNodeLayoutGetTop = double Function(
  Pointer<YGNode> node,
);

typedef CYgNodeLayoutGetRight = Float Function(
  Pointer<YGNode> node,
);

typedef DartYgNodeLayoutGetRight = double Function(
  Pointer<YGNode> node,
);

typedef CYgNodeLayoutGetBottom = Float Function(
  Pointer<YGNode> node,
);

typedef DartYgNodeLayoutGetBottom = double Function(
  Pointer<YGNode> node,
);

typedef CYgNodeLayoutGetWidth = Float Function(
  Pointer<YGNode> node,
);

typedef DartYgNodeLayoutGetWidth = double Function(
  Pointer<YGNode> node,
);

typedef CYgNodeLayoutGetHeight = Float Function(
  Pointer<YGNode> node,
);

typedef DartYgNodeLayoutGetHeight = double Function(
  Pointer<YGNode> node,
);

typedef CYgNodeLayoutGetDirection = Int32 Function(
  Pointer<YGNode> node,
);

typedef DartYgNodeLayoutGetDirection = int Function(
  Pointer<YGNode> node,
);

typedef CYgNodeLayoutGetHadOverflow = Uint8 Function(
  Pointer<YGNode> node,
);

typedef DartYgNodeLayoutGetHadOverflow = int Function(
  Pointer<YGNode> node,
);

typedef CYgNodeLayoutGetDidLegacyStretchFlagAffectLayout = Uint8 Function(
  Pointer<YGNode> node,
);

typedef DartYgNodeLayoutGetDidLegacyStretchFlagAffectLayout = int Function(
  Pointer<YGNode> node,
);

typedef CYgNodeLayoutGetMargin = Float Function(
  Pointer<YGNode> node,
  Int32 edge,
);

typedef DartYgNodeLayoutGetMargin = double Function(
  Pointer<YGNode> node,
  int edge,
);

typedef CYgNodeLayoutGetBorder = Float Function(
  Pointer<YGNode> node,
  Int32 edge,
);

typedef DartYgNodeLayoutGetBorder = double Function(
  Pointer<YGNode> node,
  int edge,
);

typedef CYgNodeLayoutGetPadding = Float Function(
  Pointer<YGNode> node,
  Int32 edge,
);

typedef DartYgNodeLayoutGetPadding = double Function(
  Pointer<YGNode> node,
  int edge,
);

typedef YGLogger = Int32 Function(
  Pointer<YGConfig>,
  Pointer<YGNode>,
  Int32,
  Pointer<Int8>,
  Pointer<VaListTag>,
);

typedef CYgConfigSetLogger = Void Function(
  Pointer<YGConfig> config,
  Pointer<NativeFunction<YGLogger>> logger,
);

typedef DartYgConfigSetLogger = void Function(
  Pointer<YGConfig> config,
  Pointer<NativeFunction<YGLogger>> logger,
);

typedef CYgAssert = Void Function(
  Uint8 condition,
  Pointer<Int8> message,
);

typedef DartYgAssert = void Function(
  int condition,
  Pointer<Int8> message,
);

typedef CYgAssertWithNode = Void Function(
  Pointer<YGNode> node,
  Uint8 condition,
  Pointer<Int8> message,
);

typedef DartYgAssertWithNode = void Function(
  Pointer<YGNode> node,
  int condition,
  Pointer<Int8> message,
);

typedef CYgAssertWithConfig = Void Function(
  Pointer<YGConfig> config,
  Uint8 condition,
  Pointer<Int8> message,
);

typedef DartYgAssertWithConfig = void Function(
  Pointer<YGConfig> config,
  int condition,
  Pointer<Int8> message,
);

typedef CYgConfigSetPointScaleFactor = Void Function(
  Pointer<YGConfig> config,
  Float pixelsInPoint,
);

typedef DartYgConfigSetPointScaleFactor = void Function(
  Pointer<YGConfig> config,
  double pixelsInPoint,
);

typedef CYgConfigSetShouldDiffLayoutWithoutLegacyStretchBehaviour = Void
    Function(
  Pointer<YGConfig> config,
  Uint8 shouldDiffLayout,
);

typedef DartYgConfigSetShouldDiffLayoutWithoutLegacyStretchBehaviour = void
    Function(
  Pointer<YGConfig> config,
  int shouldDiffLayout,
);

typedef CYgConfigSetUseLegacyStretchBehaviour = Void Function(
  Pointer<YGConfig> config,
  Uint8 useLegacyStretchBehaviour,
);

typedef DartYgConfigSetUseLegacyStretchBehaviour = void Function(
  Pointer<YGConfig> config,
  int useLegacyStretchBehaviour,
);

typedef CYgConfigNew = Pointer<YGConfig> Function();

typedef DartYgConfigNew = Pointer<YGConfig> Function();

typedef CYgConfigFree = Void Function(
  Pointer<YGConfig> config,
);

typedef DartYgConfigFree = void Function(
  Pointer<YGConfig> config,
);

typedef CYgConfigCopy = Void Function(
  Pointer<YGConfig> dest,
  Pointer<YGConfig> src,
);

typedef DartYgConfigCopy = void Function(
  Pointer<YGConfig> dest,
  Pointer<YGConfig> src,
);

typedef CYgConfigGetInstanceCount = Int32 Function();

typedef DartYgConfigGetInstanceCount = int Function();

typedef CYgConfigSetExperimentalFeatureEnabled = Void Function(
  Pointer<YGConfig> config,
  Int32 feature,
  Uint8 enabled,
);

typedef DartYgConfigSetExperimentalFeatureEnabled = void Function(
  Pointer<YGConfig> config,
  int feature,
  int enabled,
);

typedef CYgConfigIsExperimentalFeatureEnabled = Uint8 Function(
  Pointer<YGConfig> config,
  Int32 feature,
);

typedef DartYgConfigIsExperimentalFeatureEnabled = int Function(
  Pointer<YGConfig> config,
  int feature,
);

typedef CYgConfigSetUseWebDefaults = Void Function(
  Pointer<YGConfig> config,
  Uint8 enabled,
);

typedef DartYgConfigSetUseWebDefaults = void Function(
  Pointer<YGConfig> config,
  int enabled,
);

typedef CYgConfigGetUseWebDefaults = Uint8 Function(
  Pointer<YGConfig> config,
);

typedef DartYgConfigGetUseWebDefaults = int Function(
  Pointer<YGConfig> config,
);

typedef YGCloneNodeFunc = Pointer<YGNode> Function(
  Pointer<YGNode>,
  Pointer<YGNode>,
  Int32,
);

typedef CYgConfigSetCloneNodeFunc = Void Function(
  Pointer<YGConfig> config,
  Pointer<NativeFunction<YGCloneNodeFunc>> callback,
);

typedef DartYgConfigSetCloneNodeFunc = void Function(
  Pointer<YGConfig> config,
  Pointer<NativeFunction<YGCloneNodeFunc>> callback,
);

typedef CYgConfigGetDefault = Pointer<YGConfig> Function();

typedef DartYgConfigGetDefault = Pointer<YGConfig> Function();

typedef CYgConfigSetContext = Void Function(
  Pointer<YGConfig> config,
  Pointer<Void> context,
);

typedef DartYgConfigSetContext = void Function(
  Pointer<YGConfig> config,
  Pointer<Void> context,
);

typedef CYgConfigGetContext = Pointer<Void> Function(
  Pointer<YGConfig> config,
);

typedef DartYgConfigGetContext = Pointer<Void> Function(
  Pointer<YGConfig> config,
);

typedef CYgRoundValueToPixelGrid = Float Function(
  Double value,
  Double pointScaleFactor,
  Uint8 forceCeil,
  Uint8 forceFloor,
);

typedef DartYgRoundValueToPixelGrid = double Function(
  double value,
  double pointScaleFactor,
  int forceCeil,
  int forceFloor,
);
