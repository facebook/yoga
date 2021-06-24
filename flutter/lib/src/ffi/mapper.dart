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

import 'bindings.dart';
import 'types.dart';

class Mapper {
  final Pointer<T> Function<T extends NativeType>(String symbolName) _lookup;

  Mapper(DynamicLibrary dynamicLibrary) : _lookup = dynamicLibrary.lookup;

  late final Pointer<YGValue> _yGValueAuto = _lookup<YGValue>('YGValueAuto');

  YogaValue get yGValueAuto => YogaValue(
        _yGValueAuto.ref.value,
        YGUnit.values[_yGValueAuto.ref.unit],
      );

  late final Pointer<YGValue> _yGValueUndefined =
      _lookup<YGValue>('YGValueUndefined');

  YogaValue get yGValueUndefined => YogaValue(
        _yGValueUndefined.ref.value,
        YGUnit.values[_yGValueUndefined.ref.unit],
      );

  late final Pointer<YGValue> _yGValueZero = _lookup<YGValue>('YGValueZero');

  YogaValue get yGValueZero => YogaValue(
        _yGValueZero.ref.value,
        YGUnit.values[_yGValueZero.ref.unit],
      );

  YGSize yGCreateSize(
    double width,
    double height,
  ) {
    return _yGCreateSize(width, height);
  }

  late final _yGCreateSizePtr =
      _lookup<NativeFunction<CYgCreateSize>>('YGCreateSize');
  late final DartYgCreateSize _yGCreateSize =
      _yGCreateSizePtr.asFunction<DartYgCreateSize>();

  Pointer<YGNode> yGNodeNew() {
    return _yGNodeNew();
  }

  late final _yGNodeNewPtr = _lookup<NativeFunction<CYgNodeNew>>('YGNodeNew');
  late final DartYgNodeNew _yGNodeNew =
      _yGNodeNewPtr.asFunction<DartYgNodeNew>();

  Pointer<YGNode> yGNodeNewWithConfig(
    Pointer<YGConfig> config,
  ) {
    return _yGNodeNewWithConfig(
      config,
    );
  }

  late final _yGNodeNewWithConfigPtr =
      _lookup<NativeFunction<CYgNodeNewWithConfig>>('YGNodeNewWithConfig');
  late final DartYgNodeNewWithConfig _yGNodeNewWithConfig =
      _yGNodeNewWithConfigPtr.asFunction<DartYgNodeNewWithConfig>();

  Pointer<YGNode> yGNodeClone(
    Pointer<YGNode> node,
  ) {
    return _yGNodeClone(
      node,
    );
  }

  late final _yGNodeClonePtr =
      _lookup<NativeFunction<CYgNodeClone>>('YGNodeClone');
  late final DartYgNodeClone _yGNodeClone =
      _yGNodeClonePtr.asFunction<DartYgNodeClone>();

  void yGNodeFree(
    Pointer<YGNode> node,
  ) {
    return _yGNodeFree(
      node,
    );
  }

  late final _yGNodeFreePtr =
      _lookup<NativeFunction<CYgNodeFree>>('YGNodeFree');
  late final DartYgNodeFree _yGNodeFree =
      _yGNodeFreePtr.asFunction<DartYgNodeFree>();

  void yGNodeFreeRecursiveWithCleanupFunc(
    Pointer<YGNode> node,
    Pointer<NativeFunction<YGNodeCleanupFunc>> cleanup,
  ) {
    return _yGNodeFreeRecursiveWithCleanupFunc(
      node,
      cleanup,
    );
  }

  late final _yGNodeFreeRecursiveWithCleanupFuncPtr =
      _lookup<NativeFunction<CYgNodeFreeRecursiveWithCleanupFunc>>(
          'YGNodeFreeRecursiveWithCleanupFunc');
  late final DartYgNodeFreeRecursiveWithCleanupFunc
      _yGNodeFreeRecursiveWithCleanupFunc =
      _yGNodeFreeRecursiveWithCleanupFuncPtr
          .asFunction<DartYgNodeFreeRecursiveWithCleanupFunc>();

  void yGNodeFreeRecursive(
    Pointer<YGNode> node,
  ) {
    return _yGNodeFreeRecursive(
      node,
    );
  }

  late final _yGNodeFreeRecursivePtr =
      _lookup<NativeFunction<CYgNodeFreeRecursive>>('YGNodeFreeRecursive');
  late final DartYgNodeFreeRecursive _yGNodeFreeRecursive =
      _yGNodeFreeRecursivePtr.asFunction<DartYgNodeFreeRecursive>();

  void yGNodeReset(
    Pointer<YGNode> node,
  ) {
    return _yGNodeReset(
      node,
    );
  }

  late final _yGNodeResetPtr =
      _lookup<NativeFunction<CYgNodeReset>>('YGNodeReset');
  late final DartYgNodeReset _yGNodeReset =
      _yGNodeResetPtr.asFunction<DartYgNodeReset>();

  void yGNodeInsertChild(
    Pointer<YGNode> node,
    Pointer<YGNode> child,
    int index,
  ) {
    return _yGNodeInsertChild(
      node,
      child,
      index,
    );
  }

  late final _yGNodeInsertChildPtr =
      _lookup<NativeFunction<CYgNodeInsertChild>>('YGNodeInsertChild');
  late final DartYgNodeInsertChild _yGNodeInsertChild =
      _yGNodeInsertChildPtr.asFunction<DartYgNodeInsertChild>();

  void yGNodeSwapChild(
    Pointer<YGNode> node,
    Pointer<YGNode> child,
    int index,
  ) {
    return _yGNodeSwapChild(
      node,
      child,
      index,
    );
  }

  late final _yGNodeSwapChildPtr =
      _lookup<NativeFunction<CYgNodeSwapChild>>('YGNodeSwapChild');
  late final DartYgNodeSwapChild _yGNodeSwapChild =
      _yGNodeSwapChildPtr.asFunction<DartYgNodeSwapChild>();

  void yGNodeRemoveChild(
    Pointer<YGNode> node,
    Pointer<YGNode> child,
  ) {
    return _yGNodeRemoveChild(
      node,
      child,
    );
  }

  late final _yGNodeRemoveChildPtr =
      _lookup<NativeFunction<CYgNodeRemoveChild>>('YGNodeRemoveChild');
  late final DartYgNodeRemoveChild _yGNodeRemoveChild =
      _yGNodeRemoveChildPtr.asFunction<DartYgNodeRemoveChild>();

  void yGNodeRemoveAllChildren(
    Pointer<YGNode> node,
  ) {
    return _yGNodeRemoveAllChildren(
      node,
    );
  }

  late final _yGNodeRemoveAllChildrenPtr =
      _lookup<NativeFunction<CYgNodeRemoveAllChildren>>(
          'YGNodeRemoveAllChildren');
  late final DartYgNodeRemoveAllChildren _yGNodeRemoveAllChildren =
      _yGNodeRemoveAllChildrenPtr.asFunction<DartYgNodeRemoveAllChildren>();

  Pointer<YGNode> yGNodeGetChild(
    Pointer<YGNode> node,
    int index,
  ) {
    return _yGNodeGetChild(
      node,
      index,
    );
  }

  late final _yGNodeGetChildPtr =
      _lookup<NativeFunction<CYgNodeGetChild>>('YGNodeGetChild');
  late final DartYgNodeGetChild _yGNodeGetChild =
      _yGNodeGetChildPtr.asFunction<DartYgNodeGetChild>();

  Pointer<YGNode> yGNodeGetOwner(
    Pointer<YGNode> node,
  ) {
    return _yGNodeGetOwner(
      node,
    );
  }

  late final _yGNodeGetOwnerPtr =
      _lookup<NativeFunction<CYgNodeGetOwner>>('YGNodeGetOwner');
  late final DartYgNodeGetOwner _yGNodeGetOwner =
      _yGNodeGetOwnerPtr.asFunction<DartYgNodeGetOwner>();

  Pointer<YGNode> yGNodeGetParent(
    Pointer<YGNode> node,
  ) {
    return _yGNodeGetParent(
      node,
    );
  }

  late final _yGNodeGetParentPtr =
      _lookup<NativeFunction<CYgNodeGetParent>>('YGNodeGetParent');
  late final DartYgNodeGetParent _yGNodeGetParent =
      _yGNodeGetParentPtr.asFunction<DartYgNodeGetParent>();

  int yGNodeGetChildCount(
    Pointer<YGNode> node,
  ) {
    return _yGNodeGetChildCount(
      node,
    );
  }

  late final _yGNodeGetChildCountPtr =
      _lookup<NativeFunction<CYgNodeGetChildCount>>('YGNodeGetChildCount');
  late final DartYgNodeGetChildCount _yGNodeGetChildCount =
      _yGNodeGetChildCountPtr.asFunction<DartYgNodeGetChildCount>();

  void yGNodeSetChildren(
    Pointer<YGNode> owner,
    Pointer<Pointer<YGNode>> children,
    int count,
  ) {
    return _yGNodeSetChildren(
      owner,
      children,
      count,
    );
  }

  late final _yGNodeSetChildrenPtr =
      _lookup<NativeFunction<CYgNodeSetChildren>>('YGNodeSetChildren');
  late final DartYgNodeSetChildren _yGNodeSetChildren =
      _yGNodeSetChildrenPtr.asFunction<DartYgNodeSetChildren>();

  void yGNodeSetIsReferenceBaseline(
    Pointer<YGNode> node,
    bool isReferenceBaseline,
  ) {
    return _yGNodeSetIsReferenceBaseline(
      node,
      isReferenceBaseline ? 1 : 0,
    );
  }

  late final _yGNodeSetIsReferenceBaselinePtr =
      _lookup<NativeFunction<CYgNodeSetIsReferenceBaseline>>(
          'YGNodeSetIsReferenceBaseline');
  late final DartYgNodeSetIsReferenceBaseline _yGNodeSetIsReferenceBaseline =
      _yGNodeSetIsReferenceBaselinePtr
          .asFunction<DartYgNodeSetIsReferenceBaseline>();

  bool yGNodeIsReferenceBaseline(
    Pointer<YGNode> node,
  ) {
    return _yGNodeIsReferenceBaseline(node) != 0;
  }

  late final _yGNodeIsReferenceBaselinePtr =
      _lookup<NativeFunction<CYgNodeIsReferenceBaseline>>(
          'YGNodeIsReferenceBaseline');
  late final DartYgNodeIsReferenceBaseline _yGNodeIsReferenceBaseline =
      _yGNodeIsReferenceBaselinePtr.asFunction<DartYgNodeIsReferenceBaseline>();

  void yGNodeCalculateLayout(
    Pointer<YGNode> node,
    double availableWidth,
    double availableHeight,
    YGDirection ownerDirection,
  ) {
    return _yGNodeCalculateLayout(
      node,
      availableWidth,
      availableHeight,
      ownerDirection.index,
    );
  }

  late final _yGNodeCalculateLayoutPtr =
      _lookup<NativeFunction<CYgNodeCalculateLayout>>('YGNodeCalculateLayout');
  late final DartYgNodeCalculateLayout _yGNodeCalculateLayout =
      _yGNodeCalculateLayoutPtr.asFunction<DartYgNodeCalculateLayout>();

  void yGNodeMarkDirty(
    Pointer<YGNode> node,
  ) {
    return _yGNodeMarkDirty(node);
  }

  late final _yGNodeMarkDirtyPtr =
      _lookup<NativeFunction<CYgNodeMarkDirty>>('YGNodeMarkDirty');
  late final DartYgNodeMarkDirty _yGNodeMarkDirty =
      _yGNodeMarkDirtyPtr.asFunction<DartYgNodeMarkDirty>();

  void yGNodeMarkDirtyAndPropagateToDescendants(
    Pointer<YGNode> node,
  ) {
    return _yGNodeMarkDirtyAndPropagateToDescendants(
      node,
    );
  }

  late final _yGNodeMarkDirtyAndPropagateToDescendantsPtr =
      _lookup<NativeFunction<CYgNodeMarkDirtyAndPropagateToDescendants>>(
          'YGNodeMarkDirtyAndPropogateToDescendants');
  late final DartYgNodeMarkDirtyAndPropagateToDescendants
      _yGNodeMarkDirtyAndPropagateToDescendants =
      _yGNodeMarkDirtyAndPropagateToDescendantsPtr
          .asFunction<DartYgNodeMarkDirtyAndPropagateToDescendants>();

  void yGNodePrint(
    Pointer<YGNode> node,
    YGPrintOptions options,
  ) {
    return _yGNodePrint(
      node,
      options.index,
    );
  }

  late final _yGNodePrintPtr =
      _lookup<NativeFunction<CYgNodePrint>>('YGNodePrint');
  late final DartYgNodePrint _yGNodePrint =
      _yGNodePrintPtr.asFunction<DartYgNodePrint>();

  bool yGFloatIsUndefined(
    double value,
  ) {
    return _yGFloatIsUndefined(value) != 0;
  }

  late final _yGFloatIsUndefinedPtr =
      _lookup<NativeFunction<CYgFloatIsUndefined>>('YGFloatIsUndefined');
  late final DartYgFloatIsUndefined _yGFloatIsUndefined =
      _yGFloatIsUndefinedPtr.asFunction<DartYgFloatIsUndefined>();

  bool yGNodeCanUseCachedMeasurement(
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
  ) {
    return _yGNodeCanUseCachedMeasurement(
          widthMode,
          width,
          heightMode,
          height,
          lastWidthMode,
          lastWidth,
          lastHeightMode,
          lastHeight,
          lastComputedWidth,
          lastComputedHeight,
          marginRow,
          marginColumn,
          config,
        ) !=
        0;
  }

  late final _yGNodeCanUseCachedMeasurementPtr =
      _lookup<NativeFunction<CYgNodeCanUseCachedMeasurement>>(
          'YGNodeCanUseCachedMeasurement');
  late final DartYgNodeCanUseCachedMeasurement _yGNodeCanUseCachedMeasurement =
      _yGNodeCanUseCachedMeasurementPtr
          .asFunction<DartYgNodeCanUseCachedMeasurement>();

  void yGNodeCopyStyle(
    Pointer<YGNode> dstNode,
    Pointer<YGNode> srcNode,
  ) {
    return _yGNodeCopyStyle(
      dstNode,
      srcNode,
    );
  }

  late final _yGNodeCopyStylePtr =
      _lookup<NativeFunction<CYgNodeCopyStyle>>('YGNodeCopyStyle');
  late final DartYgNodeCopyStyle _yGNodeCopyStyle =
      _yGNodeCopyStylePtr.asFunction<DartYgNodeCopyStyle>();

  Pointer<Void> yGNodeGetContext(
    Pointer<YGNode> node,
  ) {
    return _yGNodeGetContext(
      node,
    );
  }

  late final _yGNodeGetContextPtr =
      _lookup<NativeFunction<CYgNodeGetContext>>('YGNodeGetContext');
  late final DartYgNodeGetContext _yGNodeGetContext =
      _yGNodeGetContextPtr.asFunction<DartYgNodeGetContext>();

  void yGNodeSetContext(
    Pointer<YGNode> node,
    Pointer<Void> context,
  ) {
    return _yGNodeSetContext(
      node,
      context,
    );
  }

  late final _yGNodeSetContextPtr =
      _lookup<NativeFunction<CYgNodeSetContext>>('YGNodeSetContext');
  late final DartYgNodeSetContext _yGNodeSetContext =
      _yGNodeSetContextPtr.asFunction<DartYgNodeSetContext>();

  void yGConfigSetPrintTreeFlag(
    Pointer<YGConfig> config,
    bool enabled,
  ) {
    return _yGConfigSetPrintTreeFlag(
      config,
      enabled ? 1 : 0,
    );
  }

  late final _yGConfigSetPrintTreeFlagPtr =
      _lookup<NativeFunction<CYgConfigSetPrintTreeFlag>>(
          'YGConfigSetPrintTreeFlag');
  late final DartYgConfigSetPrintTreeFlag _yGConfigSetPrintTreeFlag =
      _yGConfigSetPrintTreeFlagPtr.asFunction<DartYgConfigSetPrintTreeFlag>();

  bool yGNodeHasMeasureFunc(
    Pointer<YGNode> node,
  ) {
    return _yGNodeHasMeasureFunc(node) != 0;
  }

  late final _yGNodeHasMeasureFuncPtr =
      _lookup<NativeFunction<CYgNodeHasMeasureFunc>>('YGNodeHasMeasureFunc');
  late final DartYgNodeHasMeasureFunc _yGNodeHasMeasureFunc =
      _yGNodeHasMeasureFuncPtr.asFunction<DartYgNodeHasMeasureFunc>();

  void yGNodeSetMeasureFunc(
    Pointer<YGNode> node,
    Pointer<NativeFunction<YGMeasureFunc>> measureFunc,
  ) {
    return _yGNodeSetMeasureFunc(
      node,
      measureFunc,
    );
  }

  late final _yGNodeSetMeasureFuncPtr =
      _lookup<NativeFunction<CYgNodeSetMeasureFunc>>('YGNodeSetMeasureFunc');
  late final DartYgNodeSetMeasureFunc _yGNodeSetMeasureFunc =
      _yGNodeSetMeasureFuncPtr.asFunction<DartYgNodeSetMeasureFunc>();

  bool yGNodeHasBaselineFunc(
    Pointer<YGNode> node,
  ) {
    return _yGNodeHasBaselineFunc(node) != 0;
  }

  late final _yGNodeHasBaselineFuncPtr =
      _lookup<NativeFunction<CYgNodeHasBaselineFunc>>('YGNodeHasBaselineFunc');
  late final DartYgNodeHasBaselineFunc _yGNodeHasBaselineFunc =
      _yGNodeHasBaselineFuncPtr.asFunction<DartYgNodeHasBaselineFunc>();

  void yGNodeSetBaselineFunc(
    Pointer<YGNode> node,
    Pointer<NativeFunction<YGBaselineFunc>> baselineFunc,
  ) {
    return _yGNodeSetBaselineFunc(
      node,
      baselineFunc,
    );
  }

  late final _yGNodeSetBaselineFuncPtr =
      _lookup<NativeFunction<CYgNodeSetBaselineFunc>>('YGNodeSetBaselineFunc');
  late final DartYgNodeSetBaselineFunc _yGNodeSetBaselineFunc =
      _yGNodeSetBaselineFuncPtr.asFunction<DartYgNodeSetBaselineFunc>();

  Pointer<NativeFunction<YGDirtiedFunc>> yGNodeGetDirtiedFunc(
    Pointer<YGNode> node,
  ) {
    return _yGNodeGetDirtiedFunc(
      node,
    );
  }

  late final _yGNodeGetDirtiedFuncPtr =
      _lookup<NativeFunction<CYgNodeGetDirtiedFunc>>('YGNodeGetDirtiedFunc');
  late final DartYgNodeGetDirtiedFunc _yGNodeGetDirtiedFunc =
      _yGNodeGetDirtiedFuncPtr.asFunction<DartYgNodeGetDirtiedFunc>();

  void yGNodeSetDirtiedFunc(
    Pointer<YGNode> node,
    Pointer<NativeFunction<YGDirtiedFunc>> dirtiedFunc,
  ) {
    return _yGNodeSetDirtiedFunc(
      node,
      dirtiedFunc,
    );
  }

  late final _yGNodeSetDirtiedFuncPtr =
      _lookup<NativeFunction<CYgNodeSetDirtiedFunc>>('YGNodeSetDirtiedFunc');
  late final DartYgNodeSetDirtiedFunc _yGNodeSetDirtiedFunc =
      _yGNodeSetDirtiedFuncPtr.asFunction<DartYgNodeSetDirtiedFunc>();

  void yGNodeSetPrintFunc(
    Pointer<YGNode> node,
    Pointer<NativeFunction<YGPrintFunc>> printFunc,
  ) {
    return _yGNodeSetPrintFunc(
      node,
      printFunc,
    );
  }

  late final _yGNodeSetPrintFuncPtr =
      _lookup<NativeFunction<CYgNodeSetPrintFunc>>('YGNodeSetPrintFunc');
  late final DartYgNodeSetPrintFunc _yGNodeSetPrintFunc =
      _yGNodeSetPrintFuncPtr.asFunction<DartYgNodeSetPrintFunc>();

  bool yGNodeGetHasNewLayout(
    Pointer<YGNode> node,
  ) {
    return _yGNodeGetHasNewLayout(node) != 0;
  }

  late final _yGNodeGetHasNewLayoutPtr =
      _lookup<NativeFunction<CYgNodeGetHasNewLayout>>('YGNodeGetHasNewLayout');
  late final DartYgNodeGetHasNewLayout _yGNodeGetHasNewLayout =
      _yGNodeGetHasNewLayoutPtr.asFunction<DartYgNodeGetHasNewLayout>();

  void yGNodeSetHasNewLayout(
    Pointer<YGNode> node,
    bool hasNewLayout,
  ) {
    return _yGNodeSetHasNewLayout(
      node,
      hasNewLayout ? 1 : 0,
    );
  }

  late final _yGNodeSetHasNewLayoutPtr =
      _lookup<NativeFunction<CYgNodeSetHasNewLayout>>('YGNodeSetHasNewLayout');
  late final DartYgNodeSetHasNewLayout _yGNodeSetHasNewLayout =
      _yGNodeSetHasNewLayoutPtr.asFunction<DartYgNodeSetHasNewLayout>();

  YGNodeType yGNodeGetNodeType(
    Pointer<YGNode> node,
  ) {
    return YGNodeType.values[_yGNodeGetNodeType(
      node,
    )];
  }

  late final _yGNodeGetNodeTypePtr =
      _lookup<NativeFunction<CYgNodeGetNodeType>>('YGNodeGetNodeType');
  late final DartYgNodeGetNodeType _yGNodeGetNodeType =
      _yGNodeGetNodeTypePtr.asFunction<DartYgNodeGetNodeType>();

  void yGNodeSetNodeType(
    Pointer<YGNode> node,
    YGNodeType nodeType,
  ) {
    return _yGNodeSetNodeType(
      node,
      nodeType.index,
    );
  }

  late final _yGNodeSetNodeTypePtr =
      _lookup<NativeFunction<CYgNodeSetNodeType>>('YGNodeSetNodeType');
  late final DartYgNodeSetNodeType _yGNodeSetNodeType =
      _yGNodeSetNodeTypePtr.asFunction<DartYgNodeSetNodeType>();

  bool yGNodeIsDirty(
    Pointer<YGNode> node,
  ) {
    return _yGNodeIsDirty(node) != 0;
  }

  late final _yGNodeIsDirtyPtr =
      _lookup<NativeFunction<CYgNodeIsDirty>>('YGNodeIsDirty');
  late final DartYgNodeIsDirty _yGNodeIsDirty =
      _yGNodeIsDirtyPtr.asFunction<DartYgNodeIsDirty>();

  bool yGNodeLayoutGetDidUseLegacyFlag(
    Pointer<YGNode> node,
  ) {
    return _yGNodeLayoutGetDidUseLegacyFlag(node) != 0;
  }

  late final _yGNodeLayoutGetDidUseLegacyFlagPtr =
      _lookup<NativeFunction<CYgNodeLayoutGetDidUseLegacyFlag>>(
          'YGNodeLayoutGetDidUseLegacyFlag');
  late final DartYgNodeLayoutGetDidUseLegacyFlag
      _yGNodeLayoutGetDidUseLegacyFlag = _yGNodeLayoutGetDidUseLegacyFlagPtr
          .asFunction<DartYgNodeLayoutGetDidUseLegacyFlag>();

  void yGNodeStyleSetDirection(
    Pointer<YGNode> node,
    YGDirection direction,
  ) {
    return _yGNodeStyleSetDirection(
      node,
      direction.index,
    );
  }

  late final _yGNodeStyleSetDirectionPtr =
      _lookup<NativeFunction<CYgNodeStyleSetDirection>>(
          'YGNodeStyleSetDirection');
  late final DartYgNodeStyleSetDirection _yGNodeStyleSetDirection =
      _yGNodeStyleSetDirectionPtr.asFunction<DartYgNodeStyleSetDirection>();

  YGDirection yGNodeStyleGetDirection(
    Pointer<YGNode> node,
  ) {
    return YGDirection.values[_yGNodeStyleGetDirection(node)];
  }

  late final _yGNodeStyleGetDirectionPtr =
      _lookup<NativeFunction<CYgNodeStyleGetDirection>>(
          'YGNodeStyleGetDirection');
  late final DartYgNodeStyleGetDirection _yGNodeStyleGetDirection =
      _yGNodeStyleGetDirectionPtr.asFunction<DartYgNodeStyleGetDirection>();

  void yGNodeStyleSetFlexDirection(
    Pointer<YGNode> node,
    YGFlexDirection flexDirection,
  ) {
    return _yGNodeStyleSetFlexDirection(
      node,
      flexDirection.index,
    );
  }

  late final _yGNodeStyleSetFlexDirectionPtr =
      _lookup<NativeFunction<CYgNodeStyleSetFlexDirection>>(
          'YGNodeStyleSetFlexDirection');
  late final DartYgNodeStyleSetFlexDirection _yGNodeStyleSetFlexDirection =
      _yGNodeStyleSetFlexDirectionPtr
          .asFunction<DartYgNodeStyleSetFlexDirection>();

  YGFlexDirection yGNodeStyleGetFlexDirection(
    Pointer<YGNode> node,
  ) {
    return YGFlexDirection.values[_yGNodeStyleGetFlexDirection(
      node,
    )];
  }

  late final _yGNodeStyleGetFlexDirectionPtr =
      _lookup<NativeFunction<CYgNodeStyleGetFlexDirection>>(
          'YGNodeStyleGetFlexDirection');
  late final DartYgNodeStyleGetFlexDirection _yGNodeStyleGetFlexDirection =
      _yGNodeStyleGetFlexDirectionPtr
          .asFunction<DartYgNodeStyleGetFlexDirection>();

  void yGNodeStyleSetJustifyContent(
    Pointer<YGNode> node,
    YGJustify justifyContent,
  ) {
    return _yGNodeStyleSetJustifyContent(
      node,
      justifyContent.index,
    );
  }

  late final _yGNodeStyleSetJustifyContentPtr =
      _lookup<NativeFunction<CYgNodeStyleSetJustifyContent>>(
          'YGNodeStyleSetJustifyContent');
  late final DartYgNodeStyleSetJustifyContent _yGNodeStyleSetJustifyContent =
      _yGNodeStyleSetJustifyContentPtr
          .asFunction<DartYgNodeStyleSetJustifyContent>();

  YGJustify yGNodeStyleGetJustifyContent(
    Pointer<YGNode> node,
  ) {
    return YGJustify.values[_yGNodeStyleGetJustifyContent(
      node,
    )];
  }

  late final _yGNodeStyleGetJustifyContentPtr =
      _lookup<NativeFunction<CYgNodeStyleGetJustifyContent>>(
          'YGNodeStyleGetJustifyContent');
  late final DartYgNodeStyleGetJustifyContent _yGNodeStyleGetJustifyContent =
      _yGNodeStyleGetJustifyContentPtr
          .asFunction<DartYgNodeStyleGetJustifyContent>();

  void yGNodeStyleSetAlignContent(
    Pointer<YGNode> node,
    YGAlign alignContent,
  ) {
    return _yGNodeStyleSetAlignContent(
      node,
      alignContent.index,
    );
  }

  late final _yGNodeStyleSetAlignContentPtr =
      _lookup<NativeFunction<CYgNodeStyleSetAlignContent>>(
          'YGNodeStyleSetAlignContent');
  late final DartYgNodeStyleSetAlignContent _yGNodeStyleSetAlignContent =
      _yGNodeStyleSetAlignContentPtr
          .asFunction<DartYgNodeStyleSetAlignContent>();

  YGAlign yGNodeStyleGetAlignContent(
    Pointer<YGNode> node,
  ) {
    return YGAlign.values[_yGNodeStyleGetAlignContent(
      node,
    )];
  }

  late final _yGNodeStyleGetAlignContentPtr =
      _lookup<NativeFunction<CYgNodeStyleGetAlignContent>>(
          'YGNodeStyleGetAlignContent');
  late final DartYgNodeStyleGetAlignContent _yGNodeStyleGetAlignContent =
      _yGNodeStyleGetAlignContentPtr
          .asFunction<DartYgNodeStyleGetAlignContent>();

  void yGNodeStyleSetAlignItems(
    Pointer<YGNode> node,
    YGAlign alignItems,
  ) {
    return _yGNodeStyleSetAlignItems(
      node,
      alignItems.index,
    );
  }

  late final _yGNodeStyleSetAlignItemsPtr =
      _lookup<NativeFunction<CYgNodeStyleSetAlignItems>>(
          'YGNodeStyleSetAlignItems');
  late final DartYgNodeStyleSetAlignItems _yGNodeStyleSetAlignItems =
      _yGNodeStyleSetAlignItemsPtr.asFunction<DartYgNodeStyleSetAlignItems>();

  YGAlign yGNodeStyleGetAlignItems(
    Pointer<YGNode> node,
  ) {
    return YGAlign.values[_yGNodeStyleGetAlignItems(
      node,
    )];
  }

  late final _yGNodeStyleGetAlignItemsPtr =
      _lookup<NativeFunction<CYgNodeStyleGetAlignItems>>(
          'YGNodeStyleGetAlignItems');
  late final DartYgNodeStyleGetAlignItems _yGNodeStyleGetAlignItems =
      _yGNodeStyleGetAlignItemsPtr.asFunction<DartYgNodeStyleGetAlignItems>();

  void yGNodeStyleSetAlignSelf(
    Pointer<YGNode> node,
    YGAlign alignSelf,
  ) {
    return _yGNodeStyleSetAlignSelf(
      node,
      alignSelf.index,
    );
  }

  late final _yGNodeStyleSetAlignSelfPtr =
      _lookup<NativeFunction<CYgNodeStyleSetAlignSelf>>(
          'YGNodeStyleSetAlignSelf');
  late final DartYgNodeStyleSetAlignSelf _yGNodeStyleSetAlignSelf =
      _yGNodeStyleSetAlignSelfPtr.asFunction<DartYgNodeStyleSetAlignSelf>();

  YGAlign yGNodeStyleGetAlignSelf(
    Pointer<YGNode> node,
  ) {
    return YGAlign.values[_yGNodeStyleGetAlignSelf(
      node,
    )];
  }

  late final _yGNodeStyleGetAlignSelfPtr =
      _lookup<NativeFunction<CYgNodeStyleGetAlignSelf>>(
          'YGNodeStyleGetAlignSelf');
  late final DartYgNodeStyleGetAlignSelf _yGNodeStyleGetAlignSelf =
      _yGNodeStyleGetAlignSelfPtr.asFunction<DartYgNodeStyleGetAlignSelf>();

  void yGNodeStyleSetPositionType(
    Pointer<YGNode> node,
    YGPositionType positionType,
  ) {
    return _yGNodeStyleSetPositionType(
      node,
      positionType.index,
    );
  }

  late final _yGNodeStyleSetPositionTypePtr =
      _lookup<NativeFunction<CYgNodeStyleSetPositionType>>(
          'YGNodeStyleSetPositionType');
  late final DartYgNodeStyleSetPositionType _yGNodeStyleSetPositionType =
      _yGNodeStyleSetPositionTypePtr
          .asFunction<DartYgNodeStyleSetPositionType>();

  YGPositionType yGNodeStyleGetPositionType(
    Pointer<YGNode> node,
  ) {
    return YGPositionType.values[_yGNodeStyleGetPositionType(
      node,
    )];
  }

  late final _yGNodeStyleGetPositionTypePtr =
      _lookup<NativeFunction<CYgNodeStyleGetPositionType>>(
          'YGNodeStyleGetPositionType');
  late final DartYgNodeStyleGetPositionType _yGNodeStyleGetPositionType =
      _yGNodeStyleGetPositionTypePtr
          .asFunction<DartYgNodeStyleGetPositionType>();

  void yGNodeStyleSetFlexWrap(
    Pointer<YGNode> node,
    YGWrap flexWrap,
  ) {
    return _yGNodeStyleSetFlexWrap(
      node,
      flexWrap.index,
    );
  }

  late final _yGNodeStyleSetFlexWrapPtr =
      _lookup<NativeFunction<CYgNodeStyleSetFlexWrap>>(
          'YGNodeStyleSetFlexWrap');
  late final DartYgNodeStyleSetFlexWrap _yGNodeStyleSetFlexWrap =
      _yGNodeStyleSetFlexWrapPtr.asFunction<DartYgNodeStyleSetFlexWrap>();

  YGWrap yGNodeStyleGetFlexWrap(
    Pointer<YGNode> node,
  ) {
    return YGWrap.values[_yGNodeStyleGetFlexWrap(
      node,
    )];
  }

  late final _yGNodeStyleGetFlexWrapPtr =
      _lookup<NativeFunction<CYgNodeStyleGetFlexWrap>>(
          'YGNodeStyleGetFlexWrap');
  late final DartYgNodeStyleGetFlexWrap _yGNodeStyleGetFlexWrap =
      _yGNodeStyleGetFlexWrapPtr.asFunction<DartYgNodeStyleGetFlexWrap>();

  void yGNodeStyleSetOverflow(
    Pointer<YGNode> node,
    YGOverflow overflow,
  ) {
    return _yGNodeStyleSetOverflow(
      node,
      overflow.index,
    );
  }

  late final _yGNodeStyleSetOverflowPtr =
      _lookup<NativeFunction<CYgNodeStyleSetOverflow>>(
          'YGNodeStyleSetOverflow');
  late final DartYgNodeStyleSetOverflow _yGNodeStyleSetOverflow =
      _yGNodeStyleSetOverflowPtr.asFunction<DartYgNodeStyleSetOverflow>();

  YGOverflow yGNodeStyleGetOverflow(
    Pointer<YGNode> node,
  ) {
    return YGOverflow.values[_yGNodeStyleGetOverflow(
      node,
    )];
  }

  late final _yGNodeStyleGetOverflowPtr =
      _lookup<NativeFunction<CYgNodeStyleGetOverflow>>(
          'YGNodeStyleGetOverflow');
  late final DartYgNodeStyleGetOverflow _yGNodeStyleGetOverflow =
      _yGNodeStyleGetOverflowPtr.asFunction<DartYgNodeStyleGetOverflow>();

  void yGNodeStyleSetDisplay(
    Pointer<YGNode> node,
    YGDisplay display,
  ) {
    return _yGNodeStyleSetDisplay(
      node,
      display.index,
    );
  }

  late final _yGNodeStyleSetDisplayPtr =
      _lookup<NativeFunction<CYgNodeStyleSetDisplay>>('YGNodeStyleSetDisplay');
  late final DartYgNodeStyleSetDisplay _yGNodeStyleSetDisplay =
      _yGNodeStyleSetDisplayPtr.asFunction<DartYgNodeStyleSetDisplay>();

  YGDisplay yGNodeStyleGetDisplay(
    Pointer<YGNode> node,
  ) {
    return YGDisplay.values[_yGNodeStyleGetDisplay(
      node,
    )];
  }

  late final _yGNodeStyleGetDisplayPtr =
      _lookup<NativeFunction<CYgNodeStyleGetDisplay>>('YGNodeStyleGetDisplay');
  late final DartYgNodeStyleGetDisplay _yGNodeStyleGetDisplay =
      _yGNodeStyleGetDisplayPtr.asFunction<DartYgNodeStyleGetDisplay>();

  void yGNodeStyleSetFlex(
    Pointer<YGNode> node,
    double flex,
  ) {
    return _yGNodeStyleSetFlex(
      node,
      flex,
    );
  }

  late final _yGNodeStyleSetFlexPtr =
      _lookup<NativeFunction<CYgNodeStyleSetFlex>>('YGNodeStyleSetFlex');
  late final DartYgNodeStyleSetFlex _yGNodeStyleSetFlex =
      _yGNodeStyleSetFlexPtr.asFunction<DartYgNodeStyleSetFlex>();

  double yGNodeStyleGetFlex(
    Pointer<YGNode> node,
  ) {
    return _yGNodeStyleGetFlex(node);
  }

  late final _yGNodeStyleGetFlexPtr =
      _lookup<NativeFunction<CYgNodeStyleGetFlex>>('YGNodeStyleGetFlex');
  late final DartYgNodeStyleGetFlex _yGNodeStyleGetFlex =
      _yGNodeStyleGetFlexPtr.asFunction<DartYgNodeStyleGetFlex>();

  void yGNodeStyleSetFlexGrow(
    Pointer<YGNode> node,
    double flexGrow,
  ) {
    return _yGNodeStyleSetFlexGrow(
      node,
      flexGrow,
    );
  }

  late final _yGNodeStyleSetFlexGrowPtr =
      _lookup<NativeFunction<CYgNodeStyleSetFlexGrow>>(
          'YGNodeStyleSetFlexGrow');
  late final DartYgNodeStyleSetFlexGrow _yGNodeStyleSetFlexGrow =
      _yGNodeStyleSetFlexGrowPtr.asFunction<DartYgNodeStyleSetFlexGrow>();

  double yGNodeStyleGetFlexGrow(
    Pointer<YGNode> node,
  ) {
    return _yGNodeStyleGetFlexGrow(
      node,
    );
  }

  late final _yGNodeStyleGetFlexGrowPtr =
      _lookup<NativeFunction<CYgNodeStyleGetFlexGrow>>(
          'YGNodeStyleGetFlexGrow');
  late final DartYgNodeStyleGetFlexGrow _yGNodeStyleGetFlexGrow =
      _yGNodeStyleGetFlexGrowPtr.asFunction<DartYgNodeStyleGetFlexGrow>();

  void yGNodeStyleSetFlexShrink(
    Pointer<YGNode> node,
    double flexShrink,
  ) {
    return _yGNodeStyleSetFlexShrink(
      node,
      flexShrink,
    );
  }

  late final _yGNodeStyleSetFlexShrinkPtr =
      _lookup<NativeFunction<CYgNodeStyleSetFlexShrink>>(
          'YGNodeStyleSetFlexShrink');
  late final DartYgNodeStyleSetFlexShrink _yGNodeStyleSetFlexShrink =
      _yGNodeStyleSetFlexShrinkPtr.asFunction<DartYgNodeStyleSetFlexShrink>();

  double yGNodeStyleGetFlexShrink(
    Pointer<YGNode> node,
  ) {
    return _yGNodeStyleGetFlexShrink(
      node,
    );
  }

  late final _yGNodeStyleGetFlexShrinkPtr =
      _lookup<NativeFunction<CYgNodeStyleGetFlexShrink>>(
          'YGNodeStyleGetFlexShrink');
  late final DartYgNodeStyleGetFlexShrink _yGNodeStyleGetFlexShrink =
      _yGNodeStyleGetFlexShrinkPtr.asFunction<DartYgNodeStyleGetFlexShrink>();

  void yGNodeStyleSetFlexBasis(
    Pointer<YGNode> node,
    double flexBasis,
  ) {
    return _yGNodeStyleSetFlexBasis(
      node,
      flexBasis,
    );
  }

  late final _yGNodeStyleSetFlexBasisPtr =
      _lookup<NativeFunction<CYgNodeStyleSetFlexBasis>>(
          'YGNodeStyleSetFlexBasis');
  late final DartYgNodeStyleSetFlexBasis _yGNodeStyleSetFlexBasis =
      _yGNodeStyleSetFlexBasisPtr.asFunction<DartYgNodeStyleSetFlexBasis>();

  void yGNodeStyleSetFlexBasisPercent(
    Pointer<YGNode> node,
    double flexBasis,
  ) {
    return _yGNodeStyleSetFlexBasisPercent(
      node,
      flexBasis,
    );
  }

  late final _yGNodeStyleSetFlexBasisPercentPtr =
      _lookup<NativeFunction<CYgNodeStyleSetFlexBasisPercent>>(
          'YGNodeStyleSetFlexBasisPercent');
  late final DartYgNodeStyleSetFlexBasisPercent
      _yGNodeStyleSetFlexBasisPercent = _yGNodeStyleSetFlexBasisPercentPtr
          .asFunction<DartYgNodeStyleSetFlexBasisPercent>();

  void yGNodeStyleSetFlexBasisAuto(
    Pointer<YGNode> node,
  ) {
    return _yGNodeStyleSetFlexBasisAuto(
      node,
    );
  }

  late final _yGNodeStyleSetFlexBasisAutoPtr =
      _lookup<NativeFunction<CYgNodeStyleSetFlexBasisAuto>>(
          'YGNodeStyleSetFlexBasisAuto');
  late final DartYgNodeStyleSetFlexBasisAuto _yGNodeStyleSetFlexBasisAuto =
      _yGNodeStyleSetFlexBasisAutoPtr
          .asFunction<DartYgNodeStyleSetFlexBasisAuto>();

  YogaValue yGNodeStyleGetFlexBasis(
    Pointer<YGNode> node,
  ) {
    final ygValue = _yGNodeStyleGetFlexBasis(node);
    return YogaValue(
      ygValue.value,
      YGUnit.values[ygValue.unit],
    );
  }

  late final _yGNodeStyleGetFlexBasisPtr =
      _lookup<NativeFunction<CYgNodeStyleGetFlexBasis>>(
          'YGNodeStyleGetFlexBasis');
  late final DartYgNodeStyleGetFlexBasis _yGNodeStyleGetFlexBasis =
      _yGNodeStyleGetFlexBasisPtr.asFunction<DartYgNodeStyleGetFlexBasis>();

  void yGNodeStyleSetPosition(
    Pointer<YGNode> node,
    YGEdge edge,
    double position,
  ) {
    return _yGNodeStyleSetPosition(
      node,
      edge.index,
      position,
    );
  }

  late final _yGNodeStyleSetPositionPtr =
      _lookup<NativeFunction<CYgNodeStyleSetPosition>>(
          'YGNodeStyleSetPosition');
  late final DartYgNodeStyleSetPosition _yGNodeStyleSetPosition =
      _yGNodeStyleSetPositionPtr.asFunction<DartYgNodeStyleSetPosition>();

  void yGNodeStyleSetPositionPercent(
    Pointer<YGNode> node,
    YGEdge edge,
    double position,
  ) {
    return _yGNodeStyleSetPositionPercent(
      node,
      edge.index,
      position,
    );
  }

  late final _yGNodeStyleSetPositionPercentPtr =
      _lookup<NativeFunction<CYgNodeStyleSetPositionPercent>>(
          'YGNodeStyleSetPositionPercent');
  late final DartYgNodeStyleSetPositionPercent _yGNodeStyleSetPositionPercent =
      _yGNodeStyleSetPositionPercentPtr
          .asFunction<DartYgNodeStyleSetPositionPercent>();

  YogaValue yGNodeStyleGetPosition(
    Pointer<YGNode> node,
    YGEdge edge,
  ) {
    final ygValue = _yGNodeStyleGetPosition(node, edge.index);
    return YogaValue(
      ygValue.value,
      YGUnit.values[ygValue.unit],
    );
  }

  late final _yGNodeStyleGetPositionPtr =
      _lookup<NativeFunction<CYgNodeStyleGetPosition>>(
          'YGNodeStyleGetPosition');
  late final DartYgNodeStyleGetPosition _yGNodeStyleGetPosition =
      _yGNodeStyleGetPositionPtr.asFunction<DartYgNodeStyleGetPosition>();

  void yGNodeStyleSetMargin(
    Pointer<YGNode> node,
    YGEdge edge,
    double margin,
  ) {
    return _yGNodeStyleSetMargin(
      node,
      edge.index,
      margin,
    );
  }

  late final _yGNodeStyleSetMarginPtr =
      _lookup<NativeFunction<CYgNodeStyleSetMargin>>('YGNodeStyleSetMargin');
  late final DartYgNodeStyleSetMargin _yGNodeStyleSetMargin =
      _yGNodeStyleSetMarginPtr.asFunction<DartYgNodeStyleSetMargin>();

  void yGNodeStyleSetMarginPercent(
    Pointer<YGNode> node,
    YGEdge edge,
    double margin,
  ) {
    return _yGNodeStyleSetMarginPercent(
      node,
      edge.index,
      margin,
    );
  }

  late final _yGNodeStyleSetMarginPercentPtr =
      _lookup<NativeFunction<CYgNodeStyleSetMarginPercent>>(
          'YGNodeStyleSetMarginPercent');
  late final DartYgNodeStyleSetMarginPercent _yGNodeStyleSetMarginPercent =
      _yGNodeStyleSetMarginPercentPtr
          .asFunction<DartYgNodeStyleSetMarginPercent>();

  void yGNodeStyleSetMarginAuto(
    Pointer<YGNode> node,
    YGEdge edge,
  ) {
    return _yGNodeStyleSetMarginAuto(
      node,
      edge.index,
    );
  }

  late final _yGNodeStyleSetMarginAutoPtr =
      _lookup<NativeFunction<CYgNodeStyleSetMarginAuto>>(
          'YGNodeStyleSetMarginAuto');
  late final DartYgNodeStyleSetMarginAuto _yGNodeStyleSetMarginAuto =
      _yGNodeStyleSetMarginAutoPtr.asFunction<DartYgNodeStyleSetMarginAuto>();

  YogaValue yGNodeStyleGetMargin(
    Pointer<YGNode> node,
    YGEdge edge,
  ) {
    final ygValue = _yGNodeStyleGetMargin(node, edge.index);
    return YogaValue(
      ygValue.value,
      YGUnit.values[ygValue.unit],
    );
  }

  late final _yGNodeStyleGetMarginPtr =
      _lookup<NativeFunction<CYgNodeStyleGetMargin>>('YGNodeStyleGetMargin');
  late final DartYgNodeStyleGetMargin _yGNodeStyleGetMargin =
      _yGNodeStyleGetMarginPtr.asFunction<DartYgNodeStyleGetMargin>();

  void yGNodeStyleSetPadding(
    Pointer<YGNode> node,
    YGEdge edge,
    double padding,
  ) {
    return _yGNodeStyleSetPadding(
      node,
      edge.index,
      padding,
    );
  }

  late final _yGNodeStyleSetPaddingPtr =
      _lookup<NativeFunction<CYgNodeStyleSetPadding>>('YGNodeStyleSetPadding');
  late final DartYgNodeStyleSetPadding _yGNodeStyleSetPadding =
      _yGNodeStyleSetPaddingPtr.asFunction<DartYgNodeStyleSetPadding>();

  void yGNodeStyleSetPaddingPercent(
    Pointer<YGNode> node,
    YGEdge edge,
    double padding,
  ) {
    return _yGNodeStyleSetPaddingPercent(
      node,
      edge.index,
      padding,
    );
  }

  late final _yGNodeStyleSetPaddingPercentPtr =
      _lookup<NativeFunction<CYgNodeStyleSetPaddingPercent>>(
          'YGNodeStyleSetPaddingPercent');
  late final DartYgNodeStyleSetPaddingPercent _yGNodeStyleSetPaddingPercent =
      _yGNodeStyleSetPaddingPercentPtr
          .asFunction<DartYgNodeStyleSetPaddingPercent>();

  YogaValue yGNodeStyleGetPadding(
    Pointer<YGNode> node,
    YGEdge edge,
  ) {
    final ygValue = _yGNodeStyleGetPadding(node, edge.index);
    return YogaValue(
      ygValue.value,
      YGUnit.values[ygValue.unit],
    );
  }

  late final _yGNodeStyleGetPaddingPtr =
      _lookup<NativeFunction<CYgNodeStyleGetPadding>>('YGNodeStyleGetPadding');
  late final DartYgNodeStyleGetPadding _yGNodeStyleGetPadding =
      _yGNodeStyleGetPaddingPtr.asFunction<DartYgNodeStyleGetPadding>();

  void yGNodeStyleSetBorder(
    Pointer<YGNode> node,
    YGEdge edge,
    double border,
  ) {
    return _yGNodeStyleSetBorder(
      node,
      edge.index,
      border,
    );
  }

  late final _yGNodeStyleSetBorderPtr =
      _lookup<NativeFunction<CYgNodeStyleSetBorder>>('YGNodeStyleSetBorder');
  late final DartYgNodeStyleSetBorder _yGNodeStyleSetBorder =
      _yGNodeStyleSetBorderPtr.asFunction<DartYgNodeStyleSetBorder>();

  double yGNodeStyleGetBorder(
    Pointer<YGNode> node,
    YGEdge edge,
  ) {
    return _yGNodeStyleGetBorder(
      node,
      edge.index,
    );
  }

  late final _yGNodeStyleGetBorderPtr =
      _lookup<NativeFunction<CYgNodeStyleGetBorder>>('YGNodeStyleGetBorder');
  late final DartYgNodeStyleGetBorder _yGNodeStyleGetBorder =
      _yGNodeStyleGetBorderPtr.asFunction<DartYgNodeStyleGetBorder>();

  void yGNodeStyleSetWidth(
    Pointer<YGNode> node,
    double width,
  ) {
    return _yGNodeStyleSetWidth(
      node,
      width,
    );
  }

  late final _yGNodeStyleSetWidthPtr =
      _lookup<NativeFunction<CYgNodeStyleSetWidth>>('YGNodeStyleSetWidth');
  late final DartYgNodeStyleSetWidth _yGNodeStyleSetWidth =
      _yGNodeStyleSetWidthPtr.asFunction<DartYgNodeStyleSetWidth>();

  void yGNodeStyleSetWidthPercent(
    Pointer<YGNode> node,
    double width,
  ) {
    return _yGNodeStyleSetWidthPercent(
      node,
      width,
    );
  }

  late final _yGNodeStyleSetWidthPercentPtr =
      _lookup<NativeFunction<CYgNodeStyleSetWidthPercent>>(
          'YGNodeStyleSetWidthPercent');
  late final DartYgNodeStyleSetWidthPercent _yGNodeStyleSetWidthPercent =
      _yGNodeStyleSetWidthPercentPtr
          .asFunction<DartYgNodeStyleSetWidthPercent>();

  void yGNodeStyleSetWidthAuto(
    Pointer<YGNode> node,
  ) {
    return _yGNodeStyleSetWidthAuto(
      node,
    );
  }

  late final _yGNodeStyleSetWidthAutoPtr =
      _lookup<NativeFunction<CYgNodeStyleSetWidthAuto>>(
          'YGNodeStyleSetWidthAuto');
  late final DartYgNodeStyleSetWidthAuto _yGNodeStyleSetWidthAuto =
      _yGNodeStyleSetWidthAutoPtr.asFunction<DartYgNodeStyleSetWidthAuto>();

  YogaValue yGNodeStyleGetWidth(
    Pointer<YGNode> node,
  ) {
    final ygValue = _yGNodeStyleGetWidth(node);
    return YogaValue(
      ygValue.value,
      YGUnit.values[ygValue.unit],
    );
  }

  late final _yGNodeStyleGetWidthPtr =
      _lookup<NativeFunction<CYgNodeStyleGetWidth>>('YGNodeStyleGetWidth');
  late final DartYgNodeStyleGetWidth _yGNodeStyleGetWidth =
      _yGNodeStyleGetWidthPtr.asFunction<DartYgNodeStyleGetWidth>();

  void yGNodeStyleSetHeight(
    Pointer<YGNode> node,
    double height,
  ) {
    return _yGNodeStyleSetHeight(
      node,
      height,
    );
  }

  late final _yGNodeStyleSetHeightPtr =
      _lookup<NativeFunction<CYgNodeStyleSetHeight>>('YGNodeStyleSetHeight');
  late final DartYgNodeStyleSetHeight _yGNodeStyleSetHeight =
      _yGNodeStyleSetHeightPtr.asFunction<DartYgNodeStyleSetHeight>();

  void yGNodeStyleSetHeightPercent(
    Pointer<YGNode> node,
    double height,
  ) {
    return _yGNodeStyleSetHeightPercent(
      node,
      height,
    );
  }

  late final _yGNodeStyleSetHeightPercentPtr =
      _lookup<NativeFunction<CYgNodeStyleSetHeightPercent>>(
          'YGNodeStyleSetHeightPercent');
  late final DartYgNodeStyleSetHeightPercent _yGNodeStyleSetHeightPercent =
      _yGNodeStyleSetHeightPercentPtr
          .asFunction<DartYgNodeStyleSetHeightPercent>();

  void yGNodeStyleSetHeightAuto(
    Pointer<YGNode> node,
  ) {
    return _yGNodeStyleSetHeightAuto(
      node,
    );
  }

  late final _yGNodeStyleSetHeightAutoPtr =
      _lookup<NativeFunction<CYgNodeStyleSetHeightAuto>>(
          'YGNodeStyleSetHeightAuto');
  late final DartYgNodeStyleSetHeightAuto _yGNodeStyleSetHeightAuto =
      _yGNodeStyleSetHeightAutoPtr.asFunction<DartYgNodeStyleSetHeightAuto>();

  YogaValue yGNodeStyleGetHeight(
    Pointer<YGNode> node,
  ) {
    final ygValue = _yGNodeStyleGetHeight(node);
    return YogaValue(
      ygValue.value,
      YGUnit.values[ygValue.unit],
    );
  }

  late final _yGNodeStyleGetHeightPtr =
      _lookup<NativeFunction<CYgNodeStyleGetHeight>>('YGNodeStyleGetHeight');
  late final DartYgNodeStyleGetHeight _yGNodeStyleGetHeight =
      _yGNodeStyleGetHeightPtr.asFunction<DartYgNodeStyleGetHeight>();

  void yGNodeStyleSetMinWidth(
    Pointer<YGNode> node,
    double minWidth,
  ) {
    return _yGNodeStyleSetMinWidth(
      node,
      minWidth,
    );
  }

  late final _yGNodeStyleSetMinWidthPtr =
      _lookup<NativeFunction<CYgNodeStyleSetMinWidth>>(
          'YGNodeStyleSetMinWidth');
  late final DartYgNodeStyleSetMinWidth _yGNodeStyleSetMinWidth =
      _yGNodeStyleSetMinWidthPtr.asFunction<DartYgNodeStyleSetMinWidth>();

  void yGNodeStyleSetMinWidthPercent(
    Pointer<YGNode> node,
    double minWidth,
  ) {
    return _yGNodeStyleSetMinWidthPercent(
      node,
      minWidth,
    );
  }

  late final _yGNodeStyleSetMinWidthPercentPtr =
      _lookup<NativeFunction<CYgNodeStyleSetMinWidthPercent>>(
          'YGNodeStyleSetMinWidthPercent');
  late final DartYgNodeStyleSetMinWidthPercent _yGNodeStyleSetMinWidthPercent =
      _yGNodeStyleSetMinWidthPercentPtr
          .asFunction<DartYgNodeStyleSetMinWidthPercent>();

  YogaValue yGNodeStyleGetMinWidth(
    Pointer<YGNode> node,
  ) {
    final ygValue = _yGNodeStyleGetMinWidth(node);
    return YogaValue(
      ygValue.value,
      YGUnit.values[ygValue.unit],
    );
  }

  late final _yGNodeStyleGetMinWidthPtr =
      _lookup<NativeFunction<CYgNodeStyleGetMinWidth>>(
          'YGNodeStyleGetMinWidth');
  late final DartYgNodeStyleGetMinWidth _yGNodeStyleGetMinWidth =
      _yGNodeStyleGetMinWidthPtr.asFunction<DartYgNodeStyleGetMinWidth>();

  void yGNodeStyleSetMinHeight(
    Pointer<YGNode> node,
    double minHeight,
  ) {
    return _yGNodeStyleSetMinHeight(
      node,
      minHeight,
    );
  }

  late final _yGNodeStyleSetMinHeightPtr =
      _lookup<NativeFunction<CYgNodeStyleSetMinHeight>>(
          'YGNodeStyleSetMinHeight');
  late final DartYgNodeStyleSetMinHeight _yGNodeStyleSetMinHeight =
      _yGNodeStyleSetMinHeightPtr.asFunction<DartYgNodeStyleSetMinHeight>();

  void yGNodeStyleSetMinHeightPercent(
    Pointer<YGNode> node,
    double minHeight,
  ) {
    return _yGNodeStyleSetMinHeightPercent(
      node,
      minHeight,
    );
  }

  late final _yGNodeStyleSetMinHeightPercentPtr =
      _lookup<NativeFunction<CYgNodeStyleSetMinHeightPercent>>(
          'YGNodeStyleSetMinHeightPercent');
  late final DartYgNodeStyleSetMinHeightPercent
      _yGNodeStyleSetMinHeightPercent = _yGNodeStyleSetMinHeightPercentPtr
          .asFunction<DartYgNodeStyleSetMinHeightPercent>();

  YogaValue yGNodeStyleGetMinHeight(
    Pointer<YGNode> node,
  ) {
    final ygValue = _yGNodeStyleGetMinHeight(node);
    return YogaValue(
      ygValue.value,
      YGUnit.values[ygValue.unit],
    );
  }

  late final _yGNodeStyleGetMinHeightPtr =
      _lookup<NativeFunction<CYgNodeStyleGetMinHeight>>(
          'YGNodeStyleGetMinHeight');
  late final DartYgNodeStyleGetMinHeight _yGNodeStyleGetMinHeight =
      _yGNodeStyleGetMinHeightPtr.asFunction<DartYgNodeStyleGetMinHeight>();

  void yGNodeStyleSetMaxWidth(
    Pointer<YGNode> node,
    double maxWidth,
  ) {
    return _yGNodeStyleSetMaxWidth(
      node,
      maxWidth,
    );
  }

  late final _yGNodeStyleSetMaxWidthPtr =
      _lookup<NativeFunction<CYgNodeStyleSetMaxWidth>>(
          'YGNodeStyleSetMaxWidth');
  late final DartYgNodeStyleSetMaxWidth _yGNodeStyleSetMaxWidth =
      _yGNodeStyleSetMaxWidthPtr.asFunction<DartYgNodeStyleSetMaxWidth>();

  void yGNodeStyleSetMaxWidthPercent(
    Pointer<YGNode> node,
    double maxWidth,
  ) {
    return _yGNodeStyleSetMaxWidthPercent(
      node,
      maxWidth,
    );
  }

  late final _yGNodeStyleSetMaxWidthPercentPtr =
      _lookup<NativeFunction<CYgNodeStyleSetMaxWidthPercent>>(
          'YGNodeStyleSetMaxWidthPercent');
  late final DartYgNodeStyleSetMaxWidthPercent _yGNodeStyleSetMaxWidthPercent =
      _yGNodeStyleSetMaxWidthPercentPtr
          .asFunction<DartYgNodeStyleSetMaxWidthPercent>();

  YogaValue yGNodeStyleGetMaxWidth(
    Pointer<YGNode> node,
  ) {
    final ygValue = _yGNodeStyleGetMaxWidth(node);
    return YogaValue(
      ygValue.value,
      YGUnit.values[ygValue.unit],
    );
  }

  late final _yGNodeStyleGetMaxWidthPtr =
      _lookup<NativeFunction<CYgNodeStyleGetMaxWidth>>(
          'YGNodeStyleGetMaxWidth');
  late final DartYgNodeStyleGetMaxWidth _yGNodeStyleGetMaxWidth =
      _yGNodeStyleGetMaxWidthPtr.asFunction<DartYgNodeStyleGetMaxWidth>();

  void yGNodeStyleSetMaxHeight(
    Pointer<YGNode> node,
    double maxHeight,
  ) {
    return _yGNodeStyleSetMaxHeight(
      node,
      maxHeight,
    );
  }

  late final _yGNodeStyleSetMaxHeightPtr =
      _lookup<NativeFunction<CYgNodeStyleSetMaxHeight>>(
          'YGNodeStyleSetMaxHeight');
  late final DartYgNodeStyleSetMaxHeight _yGNodeStyleSetMaxHeight =
      _yGNodeStyleSetMaxHeightPtr.asFunction<DartYgNodeStyleSetMaxHeight>();

  void yGNodeStyleSetMaxHeightPercent(
    Pointer<YGNode> node,
    double maxHeight,
  ) {
    return _yGNodeStyleSetMaxHeightPercent(
      node,
      maxHeight,
    );
  }

  late final _yGNodeStyleSetMaxHeightPercentPtr =
      _lookup<NativeFunction<CYgNodeStyleSetMaxHeightPercent>>(
          'YGNodeStyleSetMaxHeightPercent');
  late final DartYgNodeStyleSetMaxHeightPercent
      _yGNodeStyleSetMaxHeightPercent = _yGNodeStyleSetMaxHeightPercentPtr
          .asFunction<DartYgNodeStyleSetMaxHeightPercent>();

  YogaValue yGNodeStyleGetMaxHeight(
    Pointer<YGNode> node,
  ) {
    final ygValue = _yGNodeStyleGetMaxHeight(node);
    return YogaValue(
      ygValue.value,
      YGUnit.values[ygValue.unit],
    );
  }

  late final _yGNodeStyleGetMaxHeightPtr =
      _lookup<NativeFunction<CYgNodeStyleGetMaxHeight>>(
          'YGNodeStyleGetMaxHeight');
  late final DartYgNodeStyleGetMaxHeight _yGNodeStyleGetMaxHeight =
      _yGNodeStyleGetMaxHeightPtr.asFunction<DartYgNodeStyleGetMaxHeight>();

  void yGNodeStyleSetAspectRatio(
    Pointer<YGNode> node,
    double aspectRatio,
  ) {
    return _yGNodeStyleSetAspectRatio(
      node,
      aspectRatio,
    );
  }

  late final _yGNodeStyleSetAspectRatioPtr =
      _lookup<NativeFunction<CYgNodeStyleSetAspectRatio>>(
          'YGNodeStyleSetAspectRatio');
  late final DartYgNodeStyleSetAspectRatio _yGNodeStyleSetAspectRatio =
      _yGNodeStyleSetAspectRatioPtr.asFunction<DartYgNodeStyleSetAspectRatio>();

  double yGNodeStyleGetAspectRatio(
    Pointer<YGNode> node,
  ) {
    return _yGNodeStyleGetAspectRatio(
      node,
    );
  }

  late final _yGNodeStyleGetAspectRatioPtr =
      _lookup<NativeFunction<CYgNodeStyleGetAspectRatio>>(
          'YGNodeStyleGetAspectRatio');
  late final DartYgNodeStyleGetAspectRatio _yGNodeStyleGetAspectRatio =
      _yGNodeStyleGetAspectRatioPtr.asFunction<DartYgNodeStyleGetAspectRatio>();

  double yGNodeLayoutGetLeft(
    Pointer<YGNode> node,
  ) {
    return _yGNodeLayoutGetLeft(
      node,
    );
  }

  late final _yGNodeLayoutGetLeftPtr =
      _lookup<NativeFunction<CYgNodeLayoutGetLeft>>('YGNodeLayoutGetLeft');
  late final DartYgNodeLayoutGetLeft _yGNodeLayoutGetLeft =
      _yGNodeLayoutGetLeftPtr.asFunction<DartYgNodeLayoutGetLeft>();

  double yGNodeLayoutGetTop(
    Pointer<YGNode> node,
  ) {
    return _yGNodeLayoutGetTop(
      node,
    );
  }

  late final _yGNodeLayoutGetTopPtr =
      _lookup<NativeFunction<CYgNodeLayoutGetTop>>('YGNodeLayoutGetTop');
  late final DartYgNodeLayoutGetTop _yGNodeLayoutGetTop =
      _yGNodeLayoutGetTopPtr.asFunction<DartYgNodeLayoutGetTop>();

  double yGNodeLayoutGetRight(
    Pointer<YGNode> node,
  ) {
    return _yGNodeLayoutGetRight(
      node,
    );
  }

  late final _yGNodeLayoutGetRightPtr =
      _lookup<NativeFunction<CYgNodeLayoutGetRight>>('YGNodeLayoutGetRight');
  late final DartYgNodeLayoutGetRight _yGNodeLayoutGetRight =
      _yGNodeLayoutGetRightPtr.asFunction<DartYgNodeLayoutGetRight>();

  double yGNodeLayoutGetBottom(
    Pointer<YGNode> node,
  ) {
    return _yGNodeLayoutGetBottom(
      node,
    );
  }

  late final _yGNodeLayoutGetBottomPtr =
      _lookup<NativeFunction<CYgNodeLayoutGetBottom>>('YGNodeLayoutGetBottom');
  late final DartYgNodeLayoutGetBottom _yGNodeLayoutGetBottom =
      _yGNodeLayoutGetBottomPtr.asFunction<DartYgNodeLayoutGetBottom>();

  double yGNodeLayoutGetWidth(
    Pointer<YGNode> node,
  ) {
    return _yGNodeLayoutGetWidth(
      node,
    );
  }

  late final _yGNodeLayoutGetWidthPtr =
      _lookup<NativeFunction<CYgNodeLayoutGetWidth>>('YGNodeLayoutGetWidth');
  late final DartYgNodeLayoutGetWidth _yGNodeLayoutGetWidth =
      _yGNodeLayoutGetWidthPtr.asFunction<DartYgNodeLayoutGetWidth>();

  double yGNodeLayoutGetHeight(
    Pointer<YGNode> node,
  ) {
    return _yGNodeLayoutGetHeight(
      node,
    );
  }

  late final _yGNodeLayoutGetHeightPtr =
      _lookup<NativeFunction<CYgNodeLayoutGetHeight>>('YGNodeLayoutGetHeight');
  late final DartYgNodeLayoutGetHeight _yGNodeLayoutGetHeight =
      _yGNodeLayoutGetHeightPtr.asFunction<DartYgNodeLayoutGetHeight>();

  YGDirection yGNodeLayoutGetDirection(
    Pointer<YGNode> node,
  ) {
    return YGDirection.values[_yGNodeLayoutGetDirection(node)];
  }

  late final _yGNodeLayoutGetDirectionPtr =
      _lookup<NativeFunction<CYgNodeLayoutGetDirection>>(
          'YGNodeLayoutGetDirection');
  late final DartYgNodeLayoutGetDirection _yGNodeLayoutGetDirection =
      _yGNodeLayoutGetDirectionPtr.asFunction<DartYgNodeLayoutGetDirection>();

  bool yGNodeLayoutGetHadOverflow(
    Pointer<YGNode> node,
  ) {
    return _yGNodeLayoutGetHadOverflow(node) != 0;
  }

  late final _yGNodeLayoutGetHadOverflowPtr =
      _lookup<NativeFunction<CYgNodeLayoutGetHadOverflow>>(
          'YGNodeLayoutGetHadOverflow');
  late final DartYgNodeLayoutGetHadOverflow _yGNodeLayoutGetHadOverflow =
      _yGNodeLayoutGetHadOverflowPtr
          .asFunction<DartYgNodeLayoutGetHadOverflow>();

  bool yGNodeLayoutGetDidLegacyStretchFlagAffectLayout(
    Pointer<YGNode> node,
  ) {
    return _yGNodeLayoutGetDidLegacyStretchFlagAffectLayout(node) != 0;
  }

  late final _yGNodeLayoutGetDidLegacyStretchFlagAffectLayoutPtr =
      _lookup<NativeFunction<CYgNodeLayoutGetDidLegacyStretchFlagAffectLayout>>(
          'YGNodeLayoutGetDidLegacyStretchFlagAffectLayout');
  late final DartYgNodeLayoutGetDidLegacyStretchFlagAffectLayout
      _yGNodeLayoutGetDidLegacyStretchFlagAffectLayout =
      _yGNodeLayoutGetDidLegacyStretchFlagAffectLayoutPtr
          .asFunction<DartYgNodeLayoutGetDidLegacyStretchFlagAffectLayout>();

  double yGNodeLayoutGetMargin(
    Pointer<YGNode> node,
    YGEdge edge,
  ) {
    return _yGNodeLayoutGetMargin(
      node,
      edge.index,
    );
  }

  late final _yGNodeLayoutGetMarginPtr =
      _lookup<NativeFunction<CYgNodeLayoutGetMargin>>('YGNodeLayoutGetMargin');
  late final DartYgNodeLayoutGetMargin _yGNodeLayoutGetMargin =
      _yGNodeLayoutGetMarginPtr.asFunction<DartYgNodeLayoutGetMargin>();

  double yGNodeLayoutGetBorder(
    Pointer<YGNode> node,
    YGEdge edge,
  ) {
    return _yGNodeLayoutGetBorder(
      node,
      edge.index,
    );
  }

  late final _yGNodeLayoutGetBorderPtr =
      _lookup<NativeFunction<CYgNodeLayoutGetBorder>>('YGNodeLayoutGetBorder');
  late final DartYgNodeLayoutGetBorder _yGNodeLayoutGetBorder =
      _yGNodeLayoutGetBorderPtr.asFunction<DartYgNodeLayoutGetBorder>();

  double yGNodeLayoutGetPadding(
    Pointer<YGNode> node,
    YGEdge edge,
  ) {
    return _yGNodeLayoutGetPadding(
      node,
      edge.index,
    );
  }

  late final _yGNodeLayoutGetPaddingPtr =
      _lookup<NativeFunction<CYgNodeLayoutGetPadding>>(
          'YGNodeLayoutGetPadding');
  late final DartYgNodeLayoutGetPadding _yGNodeLayoutGetPadding =
      _yGNodeLayoutGetPaddingPtr.asFunction<DartYgNodeLayoutGetPadding>();

  void yGConfigSetLogger(
    Pointer<YGConfig> config,
    Pointer<NativeFunction<YGLogger>> logger,
  ) {
    return _yGConfigSetLogger(
      config,
      logger,
    );
  }

  late final _yGConfigSetLoggerPtr =
      _lookup<NativeFunction<CYgConfigSetLogger>>('YGConfigSetLogger');
  late final DartYgConfigSetLogger _yGConfigSetLogger =
      _yGConfigSetLoggerPtr.asFunction<DartYgConfigSetLogger>();

  void yGAssert(
    bool condition,
    Pointer<Int8> message,
  ) {
    return _yGAssert(
      condition ? 1 : 0,
      message,
    );
  }

  late final _yGAssertPtr = _lookup<NativeFunction<CYgAssert>>('YGAssert');
  late final DartYgAssert _yGAssert = _yGAssertPtr.asFunction<DartYgAssert>();

  void yGAssertWithNode(
    Pointer<YGNode> node,
    bool condition,
    Pointer<Int8> message,
  ) {
    return _yGAssertWithNode(
      node,
      condition ? 1 : 0,
      message,
    );
  }

  late final _yGAssertWithNodePtr =
      _lookup<NativeFunction<CYgAssertWithNode>>('YGAssertWithNode');
  late final DartYgAssertWithNode _yGAssertWithNode =
      _yGAssertWithNodePtr.asFunction<DartYgAssertWithNode>();

  void yGAssertWithConfig(
    Pointer<YGConfig> config,
    bool condition,
    Pointer<Int8> message,
  ) {
    return _yGAssertWithConfig(
      config,
      condition ? 1 : 0,
      message,
    );
  }

  late final _yGAssertWithConfigPtr =
      _lookup<NativeFunction<CYgAssertWithConfig>>('YGAssertWithConfig');
  late final DartYgAssertWithConfig _yGAssertWithConfig =
      _yGAssertWithConfigPtr.asFunction<DartYgAssertWithConfig>();

  void yGConfigSetPointScaleFactor(
    Pointer<YGConfig> config,
    double pixelsInPoint,
  ) {
    return _yGConfigSetPointScaleFactor(
      config,
      pixelsInPoint,
    );
  }

  late final _yGConfigSetPointScaleFactorPtr =
      _lookup<NativeFunction<CYgConfigSetPointScaleFactor>>(
          'YGConfigSetPointScaleFactor');
  late final DartYgConfigSetPointScaleFactor _yGConfigSetPointScaleFactor =
      _yGConfigSetPointScaleFactorPtr
          .asFunction<DartYgConfigSetPointScaleFactor>();

  void yGConfigSetShouldDiffLayoutWithoutLegacyStretchBehaviour(
    Pointer<YGConfig> config,
    bool shouldDiffLayout,
  ) {
    return _yGConfigSetShouldDiffLayoutWithoutLegacyStretchBehaviour(
      config,
      shouldDiffLayout ? 1 : 0,
    );
  }

  late final _yGConfigSetShouldDiffLayoutWithoutLegacyStretchBehaviourPtr =
      _lookup<
              NativeFunction<
                  CYgConfigSetShouldDiffLayoutWithoutLegacyStretchBehaviour>>(
          'YGConfigSetShouldDiffLayoutWithoutLegacyStretchBehaviour');
  late final DartYgConfigSetShouldDiffLayoutWithoutLegacyStretchBehaviour
      _yGConfigSetShouldDiffLayoutWithoutLegacyStretchBehaviour =
      _yGConfigSetShouldDiffLayoutWithoutLegacyStretchBehaviourPtr.asFunction<
          DartYgConfigSetShouldDiffLayoutWithoutLegacyStretchBehaviour>();

  void yGConfigSetUseLegacyStretchBehaviour(
    Pointer<YGConfig> config,
    bool useLegacyStretchBehaviour,
  ) {
    return _yGConfigSetUseLegacyStretchBehaviour(
      config,
      useLegacyStretchBehaviour ? 1 : 0,
    );
  }

  late final _yGConfigSetUseLegacyStretchBehaviourPtr =
      _lookup<NativeFunction<CYgConfigSetUseLegacyStretchBehaviour>>(
          'YGConfigSetUseLegacyStretchBehaviour');
  late final DartYgConfigSetUseLegacyStretchBehaviour
      _yGConfigSetUseLegacyStretchBehaviour =
      _yGConfigSetUseLegacyStretchBehaviourPtr
          .asFunction<DartYgConfigSetUseLegacyStretchBehaviour>();

  Pointer<YGConfig> yGConfigNew() {
    return _yGConfigNew();
  }

  late final _yGConfigNewPtr =
      _lookup<NativeFunction<CYgConfigNew>>('YGConfigNew');
  late final DartYgConfigNew _yGConfigNew =
      _yGConfigNewPtr.asFunction<DartYgConfigNew>();

  void yGConfigFree(
    Pointer<YGConfig> config,
  ) {
    return _yGConfigFree(
      config,
    );
  }

  late final _yGConfigFreePtr =
      _lookup<NativeFunction<CYgConfigFree>>('YGConfigFree');
  late final DartYgConfigFree _yGConfigFree =
      _yGConfigFreePtr.asFunction<DartYgConfigFree>();

  void yGConfigCopy(
    Pointer<YGConfig> dest,
    Pointer<YGConfig> src,
  ) {
    return _yGConfigCopy(
      dest,
      src,
    );
  }

  late final _yGConfigCopyPtr =
      _lookup<NativeFunction<CYgConfigCopy>>('YGConfigCopy');
  late final DartYgConfigCopy _yGConfigCopy =
      _yGConfigCopyPtr.asFunction<DartYgConfigCopy>();

  int yGConfigGetInstanceCount() {
    return _yGConfigGetInstanceCount();
  }

  late final _yGConfigGetInstanceCountPtr =
      _lookup<NativeFunction<CYgConfigGetInstanceCount>>(
          'YGConfigGetInstanceCount');
  late final DartYgConfigGetInstanceCount _yGConfigGetInstanceCount =
      _yGConfigGetInstanceCountPtr.asFunction<DartYgConfigGetInstanceCount>();

  void yGConfigSetExperimentalFeatureEnabled(
    Pointer<YGConfig> config,
    int feature,
    bool enabled,
  ) {
    return _yGConfigSetExperimentalFeatureEnabled(
      config,
      feature,
      enabled ? 1 : 0,
    );
  }

  late final _yGConfigSetExperimentalFeatureEnabledPtr =
      _lookup<NativeFunction<CYgConfigSetExperimentalFeatureEnabled>>(
          'YGConfigSetExperimentalFeatureEnabled');
  late final DartYgConfigSetExperimentalFeatureEnabled
      _yGConfigSetExperimentalFeatureEnabled =
      _yGConfigSetExperimentalFeatureEnabledPtr
          .asFunction<DartYgConfigSetExperimentalFeatureEnabled>();

  bool yGConfigIsExperimentalFeatureEnabled(
    Pointer<YGConfig> config,
    int feature,
  ) {
    return _yGConfigIsExperimentalFeatureEnabled(
          config,
          feature,
        ) !=
        0;
  }

  late final _yGConfigIsExperimentalFeatureEnabledPtr =
      _lookup<NativeFunction<CYgConfigIsExperimentalFeatureEnabled>>(
          'YGConfigIsExperimentalFeatureEnabled');
  late final DartYgConfigIsExperimentalFeatureEnabled
      _yGConfigIsExperimentalFeatureEnabled =
      _yGConfigIsExperimentalFeatureEnabledPtr
          .asFunction<DartYgConfigIsExperimentalFeatureEnabled>();

  void yGConfigSetUseWebDefaults(
    Pointer<YGConfig> config,
    bool enabled,
  ) {
    return _yGConfigSetUseWebDefaults(
      config,
      enabled ? 1 : 0,
    );
  }

  late final _yGConfigSetUseWebDefaultsPtr =
      _lookup<NativeFunction<CYgConfigSetUseWebDefaults>>(
          'YGConfigSetUseWebDefaults');
  late final DartYgConfigSetUseWebDefaults _yGConfigSetUseWebDefaults =
      _yGConfigSetUseWebDefaultsPtr.asFunction<DartYgConfigSetUseWebDefaults>();

  bool yGConfigGetUseWebDefaults(
    Pointer<YGConfig> config,
  ) {
    return _yGConfigGetUseWebDefaults(
          config,
        ) !=
        0;
  }

  late final _yGConfigGetUseWebDefaultsPtr =
      _lookup<NativeFunction<CYgConfigGetUseWebDefaults>>(
          'YGConfigGetUseWebDefaults');
  late final DartYgConfigGetUseWebDefaults _yGConfigGetUseWebDefaults =
      _yGConfigGetUseWebDefaultsPtr.asFunction<DartYgConfigGetUseWebDefaults>();

  void yGConfigSetCloneNodeFunc(
    Pointer<YGConfig> config,
    Pointer<NativeFunction<YGCloneNodeFunc>> callback,
  ) {
    return _yGConfigSetCloneNodeFunc(
      config,
      callback,
    );
  }

  late final _yGConfigSetCloneNodeFuncPtr =
      _lookup<NativeFunction<CYgConfigSetCloneNodeFunc>>(
          'YGConfigSetCloneNodeFunc');
  late final DartYgConfigSetCloneNodeFunc _yGConfigSetCloneNodeFunc =
      _yGConfigSetCloneNodeFuncPtr.asFunction<DartYgConfigSetCloneNodeFunc>();

  Pointer<YGConfig> yGConfigGetDefault() {
    return _yGConfigGetDefault();
  }

  late final _yGConfigGetDefaultPtr =
      _lookup<NativeFunction<CYgConfigGetDefault>>('YGConfigGetDefault');
  late final DartYgConfigGetDefault _yGConfigGetDefault =
      _yGConfigGetDefaultPtr.asFunction<DartYgConfigGetDefault>();

  void yGConfigSetContext(
    Pointer<YGConfig> config,
    Pointer<Void> context,
  ) {
    return _yGConfigSetContext(
      config,
      context,
    );
  }

  late final _yGConfigSetContextPtr =
      _lookup<NativeFunction<CYgConfigSetContext>>('YGConfigSetContext');
  late final DartYgConfigSetContext _yGConfigSetContext =
      _yGConfigSetContextPtr.asFunction<DartYgConfigSetContext>();

  Pointer<Void> yGConfigGetContext(
    Pointer<YGConfig> config,
  ) {
    return _yGConfigGetContext(config);
  }

  late final _yGConfigGetContextPtr =
      _lookup<NativeFunction<CYgConfigGetContext>>('YGConfigGetContext');
  late final DartYgConfigGetContext _yGConfigGetContext =
      _yGConfigGetContextPtr.asFunction<DartYgConfigGetContext>();

  double yGRoundValueToPixelGrid(
    double value,
    double pointScaleFactor,
    bool forceCeil,
    bool forceFloor,
  ) {
    return _yGRoundValueToPixelGrid(
      value,
      pointScaleFactor,
      forceCeil ? 1 : 0,
      forceFloor ? 1 : 0,
    );
  }

  late final _yGRoundValueToPixelGridPtr =
      _lookup<NativeFunction<CYgRoundValueToPixelGrid>>(
          'YGRoundValueToPixelGrid');
  late final DartYgRoundValueToPixelGrid _yGRoundValueToPixelGrid =
      _yGRoundValueToPixelGridPtr.asFunction<DartYgRoundValueToPixelGrid>();
}
