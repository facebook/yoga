/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

var _measure = Runtime.addFunction(
function (retAddr, node, width, widthMode, height, heightMode) {
  setValue(retAddr + 0, widthMode === _YGMeasureModeExactly ? width : 50, 'float');
  setValue(retAddr + 4, heightMode === _YGMeasureModeExactly ? height : 50, 'float');
});


(function() {
  const root = _YGNodeNew();
  _YGNodeStyleSetAlignItems(root, _YGAlignFlexStart);
  _YGNodeStyleSetWidth(root, 100);
  _YGNodeStyleSetHeight(root, 100);

  const root_child0 = _YGNodeNew();
  _YGNodeStyleSetWidth(root_child0, 50);
  _YGNodeStyleSetAspectRatio(root_child0, 1);
  _YGNodeInsertChild(root, root_child0, 0);

  _YGNodeCalculateLayout(root, _YGUndefined, _YGUndefined, _YGDirectionLTR);

  ASSERT_EQ(0, _YGNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, _YGNodeLayoutGetTop(root_child0));
  ASSERT_EQ(50, _YGNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, _YGNodeLayoutGetHeight(root_child0));

  _YGNodeFreeRecursive(root);
})();

(function() {
  const root = _YGNodeNew();
  _YGNodeStyleSetAlignItems(root, _YGAlignFlexStart);
  _YGNodeStyleSetWidth(root, 100);
  _YGNodeStyleSetHeight(root, 100);

  const root_child0 = _YGNodeNew();
  _YGNodeStyleSetHeight(root_child0, 50);
  _YGNodeStyleSetAspectRatio(root_child0, 1);
  _YGNodeInsertChild(root, root_child0, 0);

  _YGNodeCalculateLayout(root, _YGUndefined, _YGUndefined, _YGDirectionLTR);

  ASSERT_EQ(0, _YGNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, _YGNodeLayoutGetTop(root_child0));
  ASSERT_EQ(50, _YGNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, _YGNodeLayoutGetHeight(root_child0));

  _YGNodeFreeRecursive(root);
})();

(function() {
  const root = _YGNodeNew();
  _YGNodeStyleSetFlexDirection(root, _YGFlexDirectionRow);
  _YGNodeStyleSetAlignItems(root, _YGAlignFlexStart);
  _YGNodeStyleSetWidth(root, 100);
  _YGNodeStyleSetHeight(root, 100);

  const root_child0 = _YGNodeNew();
  _YGNodeStyleSetWidth(root_child0, 100);
  _YGNodeStyleSetHeight(root_child0, 50);
  _YGNodeStyleSetAspectRatio(root_child0, 1);
  _YGNodeInsertChild(root, root_child0, 0);

  _YGNodeCalculateLayout(root, _YGUndefined, _YGUndefined, _YGDirectionLTR);

  ASSERT_EQ(0, _YGNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, _YGNodeLayoutGetTop(root_child0));
  ASSERT_EQ(100, _YGNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(100, _YGNodeLayoutGetHeight(root_child0));

  _YGNodeFreeRecursive(root);
})();

(function() {
  const root = _YGNodeNew();
  _YGNodeStyleSetAlignItems(root, _YGAlignFlexStart);
  _YGNodeStyleSetWidth(root, 100);
  _YGNodeStyleSetHeight(root, 100);

  const root_child0 = _YGNodeNew();
  _YGNodeStyleSetWidth(root_child0, 100);
  _YGNodeStyleSetHeight(root_child0, 50);
  _YGNodeStyleSetAspectRatio(root_child0, 1);
  _YGNodeInsertChild(root, root_child0, 0);

  _YGNodeCalculateLayout(root, _YGUndefined, _YGUndefined, _YGDirectionLTR);

  ASSERT_EQ(0, _YGNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, _YGNodeLayoutGetTop(root_child0));
  ASSERT_EQ(50, _YGNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, _YGNodeLayoutGetHeight(root_child0));

  _YGNodeFreeRecursive(root);
})();

(function() {
  const root = _YGNodeNew();
  _YGNodeStyleSetWidth(root, 100);
  _YGNodeStyleSetHeight(root, 100);

  const root_child0 = _YGNodeNew();
  _YGNodeStyleSetAspectRatio(root_child0, 1);
  _YGNodeInsertChild(root, root_child0, 0);

  _YGNodeCalculateLayout(root, _YGUndefined, _YGUndefined, _YGDirectionLTR);

  ASSERT_EQ(0, _YGNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, _YGNodeLayoutGetTop(root_child0));
  ASSERT_EQ(100, _YGNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(100, _YGNodeLayoutGetHeight(root_child0));

  _YGNodeFreeRecursive(root);
})();

(function() {
  const root = _YGNodeNew();
  _YGNodeStyleSetAlignItems(root, _YGAlignFlexStart);
  _YGNodeStyleSetWidth(root, 100);
  _YGNodeStyleSetHeight(root, 100);

  const root_child0 = _YGNodeNew();
  _YGNodeStyleSetHeight(root_child0, 50);
  _YGNodeStyleSetFlexGrow(root_child0, 1);
  _YGNodeStyleSetAspectRatio(root_child0, 1);
  _YGNodeInsertChild(root, root_child0, 0);

  _YGNodeCalculateLayout(root, _YGUndefined, _YGUndefined, _YGDirectionLTR);

  ASSERT_EQ(0, _YGNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, _YGNodeLayoutGetTop(root_child0));
  ASSERT_EQ(100, _YGNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(100, _YGNodeLayoutGetHeight(root_child0));

  _YGNodeFreeRecursive(root);
})();

(function() {
  const root = _YGNodeNew();
  _YGNodeStyleSetAlignItems(root, _YGAlignFlexStart);
  _YGNodeStyleSetWidth(root, 100);
  _YGNodeStyleSetHeight(root, 100);

  const root_child0 = _YGNodeNew();
  _YGNodeStyleSetHeight(root_child0, 150);
  _YGNodeStyleSetFlexShrink(root_child0, 1);
  _YGNodeStyleSetAspectRatio(root_child0, 1);
  _YGNodeInsertChild(root, root_child0, 0);

  _YGNodeCalculateLayout(root, _YGUndefined, _YGUndefined, _YGDirectionLTR);

  ASSERT_EQ(0, _YGNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, _YGNodeLayoutGetTop(root_child0));
  ASSERT_EQ(100, _YGNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(100, _YGNodeLayoutGetHeight(root_child0));

  _YGNodeFreeRecursive(root);
})();

(function() {
  const root = _YGNodeNew();
  _YGNodeStyleSetAlignItems(root, _YGAlignFlexStart);
  _YGNodeStyleSetWidth(root, 100);
  _YGNodeStyleSetHeight(root, 100);

  const root_child0 = _YGNodeNew();
  _YGNodeStyleSetFlexBasis(root_child0, 50);
  _YGNodeStyleSetAspectRatio(root_child0, 1);
  _YGNodeInsertChild(root, root_child0, 0);

  _YGNodeCalculateLayout(root, _YGUndefined, _YGUndefined, _YGDirectionLTR);

  ASSERT_EQ(0, _YGNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, _YGNodeLayoutGetTop(root_child0));
  ASSERT_EQ(50, _YGNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, _YGNodeLayoutGetHeight(root_child0));

  _YGNodeFreeRecursive(root);
})();

(function() {
  const root = _YGNodeNew();
  _YGNodeStyleSetWidth(root, 100);
  _YGNodeStyleSetHeight(root, 100);

  const root_child0 = _YGNodeNew();
  _YGNodeStyleSetPositionType(root_child0, _YGPositionTypeAbsolute);
  _YGNodeStyleSetPosition(root_child0, _YGEdgeLeft, 0);
  _YGNodeStyleSetPosition(root_child0, _YGEdgeTop, 0);
  _YGNodeStyleSetWidth(root_child0, 50);
  _YGNodeStyleSetAspectRatio(root_child0, 1);
  _YGNodeInsertChild(root, root_child0, 0);

  _YGNodeCalculateLayout(root, _YGUndefined, _YGUndefined, _YGDirectionLTR);

  ASSERT_EQ(0, _YGNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, _YGNodeLayoutGetTop(root_child0));
  ASSERT_EQ(50, _YGNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, _YGNodeLayoutGetHeight(root_child0));

  _YGNodeFreeRecursive(root);
})();

(function() {
  const root = _YGNodeNew();
  _YGNodeStyleSetWidth(root, 100);
  _YGNodeStyleSetHeight(root, 100);

  const root_child0 = _YGNodeNew();
  _YGNodeStyleSetPositionType(root_child0, _YGPositionTypeAbsolute);
  _YGNodeStyleSetPosition(root_child0, _YGEdgeLeft, 0);
  _YGNodeStyleSetPosition(root_child0, _YGEdgeTop, 0);
  _YGNodeStyleSetHeight(root_child0, 50);
  _YGNodeStyleSetAspectRatio(root_child0, 1);
  _YGNodeInsertChild(root, root_child0, 0);

  _YGNodeCalculateLayout(root, _YGUndefined, _YGUndefined, _YGDirectionLTR);

  ASSERT_EQ(0, _YGNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, _YGNodeLayoutGetTop(root_child0));
  ASSERT_EQ(50, _YGNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, _YGNodeLayoutGetHeight(root_child0));

  _YGNodeFreeRecursive(root);
})();

(function() {
  const root = _YGNodeNew();
  _YGNodeStyleSetAlignItems(root, _YGAlignFlexStart);
  _YGNodeStyleSetWidth(root, 100);
  _YGNodeStyleSetHeight(root, 100);

  const root_child0 = _YGNodeNew();
  _YGNodeStyleSetHeight(root_child0, 50);
  _YGNodeStyleSetMaxWidth(root_child0, 40);
  _YGNodeStyleSetAspectRatio(root_child0, 1);
  _YGNodeInsertChild(root, root_child0, 0);

  _YGNodeCalculateLayout(root, _YGUndefined, _YGUndefined, _YGDirectionLTR);

  ASSERT_EQ(0, _YGNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, _YGNodeLayoutGetTop(root_child0));
  ASSERT_EQ(40, _YGNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, _YGNodeLayoutGetHeight(root_child0));

  _YGNodeFreeRecursive(root);
})();

(function() {
  const root = _YGNodeNew();
  _YGNodeStyleSetAlignItems(root, _YGAlignFlexStart);
  _YGNodeStyleSetWidth(root, 100);
  _YGNodeStyleSetHeight(root, 100);

  const root_child0 = _YGNodeNew();
  _YGNodeStyleSetWidth(root_child0, 50);
  _YGNodeStyleSetMaxHeight(root_child0, 40);
  _YGNodeStyleSetAspectRatio(root_child0, 1);
  _YGNodeInsertChild(root, root_child0, 0);

  _YGNodeCalculateLayout(root, _YGUndefined, _YGUndefined, _YGDirectionLTR);

  ASSERT_EQ(0, _YGNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, _YGNodeLayoutGetTop(root_child0));
  ASSERT_EQ(50, _YGNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(40, _YGNodeLayoutGetHeight(root_child0));

  _YGNodeFreeRecursive(root);
})();

(function() {
  const root = _YGNodeNew();
  _YGNodeStyleSetAlignItems(root, _YGAlignFlexStart);
  _YGNodeStyleSetWidth(root, 100);
  _YGNodeStyleSetHeight(root, 100);

  const root_child0 = _YGNodeNew();
  _YGNodeStyleSetHeight(root_child0, 30);
  _YGNodeStyleSetMinWidth(root_child0, 40);
  _YGNodeStyleSetAspectRatio(root_child0, 1);
  _YGNodeInsertChild(root, root_child0, 0);

  _YGNodeCalculateLayout(root, _YGUndefined, _YGUndefined, _YGDirectionLTR);

  ASSERT_EQ(0, _YGNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, _YGNodeLayoutGetTop(root_child0));
  ASSERT_EQ(40, _YGNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(30, _YGNodeLayoutGetHeight(root_child0));

  _YGNodeFreeRecursive(root);
})();

(function() {
  const root = _YGNodeNew();
  _YGNodeStyleSetAlignItems(root, _YGAlignFlexStart);
  _YGNodeStyleSetWidth(root, 100);
  _YGNodeStyleSetHeight(root, 100);

  const root_child0 = _YGNodeNew();
  _YGNodeStyleSetWidth(root_child0, 30);
  _YGNodeStyleSetMinHeight(root_child0, 40);
  _YGNodeStyleSetAspectRatio(root_child0, 1);
  _YGNodeInsertChild(root, root_child0, 0);

  _YGNodeCalculateLayout(root, _YGUndefined, _YGUndefined, _YGDirectionLTR);

  ASSERT_EQ(0, _YGNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, _YGNodeLayoutGetTop(root_child0));
  ASSERT_EQ(30, _YGNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(40, _YGNodeLayoutGetHeight(root_child0));

  _YGNodeFreeRecursive(root);
})();

(function() {
  const root = _YGNodeNew();
  _YGNodeStyleSetAlignItems(root, _YGAlignFlexStart);
  _YGNodeStyleSetWidth(root, 100);
  _YGNodeStyleSetHeight(root, 100);

  const root_child0 = _YGNodeNew();
  _YGNodeStyleSetHeight(root_child0, 50);
  _YGNodeStyleSetAspectRatio(root_child0, 2);
  _YGNodeInsertChild(root, root_child0, 0);

  _YGNodeCalculateLayout(root, _YGUndefined, _YGUndefined, _YGDirectionLTR);

  ASSERT_EQ(0, _YGNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, _YGNodeLayoutGetTop(root_child0));
  ASSERT_EQ(100, _YGNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, _YGNodeLayoutGetHeight(root_child0));

  _YGNodeFreeRecursive(root);
})();

(function() {
  const root = _YGNodeNew();
  _YGNodeStyleSetAlignItems(root, _YGAlignFlexStart);
  _YGNodeStyleSetWidth(root, 100);
  _YGNodeStyleSetHeight(root, 100);

  const root_child0 = _YGNodeNew();
  _YGNodeStyleSetHeight(root_child0, 100);
  _YGNodeStyleSetAspectRatio(root_child0, 0.5);
  _YGNodeInsertChild(root, root_child0, 0);

  _YGNodeCalculateLayout(root, _YGUndefined, _YGUndefined, _YGDirectionLTR);

  ASSERT_EQ(0, _YGNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, _YGNodeLayoutGetTop(root_child0));
  ASSERT_EQ(50, _YGNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(100, _YGNodeLayoutGetHeight(root_child0));

  _YGNodeFreeRecursive(root);
})();

(function() {
  const root = _YGNodeNew();
  _YGNodeStyleSetAlignItems(root, _YGAlignFlexStart);
  _YGNodeStyleSetWidth(root, 100);
  _YGNodeStyleSetHeight(root, 100);

  const root_child0 = _YGNodeNew();
  _YGNodeStyleSetWidth(root_child0, 50);
  _YGNodeStyleSetAspectRatio(root_child0, 0.5);
  _YGNodeInsertChild(root, root_child0, 0);

  _YGNodeCalculateLayout(root, _YGUndefined, _YGUndefined, _YGDirectionLTR);

  ASSERT_EQ(0, _YGNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, _YGNodeLayoutGetTop(root_child0));
  ASSERT_EQ(50, _YGNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(100, _YGNodeLayoutGetHeight(root_child0));

  _YGNodeFreeRecursive(root);
})();

(function() {
  const root = _YGNodeNew();
  _YGNodeStyleSetAlignItems(root, _YGAlignFlexStart);
  _YGNodeStyleSetWidth(root, 100);
  _YGNodeStyleSetHeight(root, 100);

  const root_child0 = _YGNodeNew();
  _YGNodeStyleSetWidth(root_child0, 100);
  _YGNodeStyleSetAspectRatio(root_child0, 2);
  _YGNodeInsertChild(root, root_child0, 0);

  _YGNodeCalculateLayout(root, _YGUndefined, _YGUndefined, _YGDirectionLTR);

  ASSERT_EQ(0, _YGNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, _YGNodeLayoutGetTop(root_child0));
  ASSERT_EQ(100, _YGNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, _YGNodeLayoutGetHeight(root_child0));

  _YGNodeFreeRecursive(root);
})();

(function() {
  const root = _YGNodeNew();
  _YGNodeStyleSetAlignItems(root, _YGAlignFlexStart);
  _YGNodeStyleSetWidth(root, 100);
  _YGNodeStyleSetHeight(root, 100);

  const root_child0 = _YGNodeNew();
  _YGNodeSetMeasureFunc(root_child0, _measure);
  _YGNodeStyleSetAspectRatio(root_child0, 1);
  _YGNodeInsertChild(root, root_child0, 0);

  _YGNodeCalculateLayout(root, _YGUndefined, _YGUndefined, _YGDirectionLTR);

  ASSERT_EQ(0, _YGNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, _YGNodeLayoutGetTop(root_child0));
  ASSERT_EQ(50, _YGNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, _YGNodeLayoutGetHeight(root_child0));

  _YGNodeFreeRecursive(root);
})();

(function() {
  const root = _YGNodeNew();
  _YGNodeStyleSetFlexDirection(root, _YGFlexDirectionRow);
  _YGNodeStyleSetAlignItems(root, _YGAlignFlexStart);
  _YGNodeStyleSetWidth(root, 100);
  _YGNodeStyleSetHeight(root, 200);

  const root_child0 = _YGNodeNew();
  _YGNodeStyleSetWidth(root_child0, 50);
  _YGNodeStyleSetHeight(root_child0, 50);
  _YGNodeStyleSetFlexGrow(root_child0, 1);
  _YGNodeStyleSetAspectRatio(root_child0, 1);
  _YGNodeInsertChild(root, root_child0, 0);

  _YGNodeCalculateLayout(root, _YGUndefined, _YGUndefined, _YGDirectionLTR);

  ASSERT_EQ(0, _YGNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, _YGNodeLayoutGetTop(root_child0));
  ASSERT_EQ(100, _YGNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(100, _YGNodeLayoutGetHeight(root_child0));

  _YGNodeFreeRecursive(root);
})();

(function() {
  const root = _YGNodeNew();
  _YGNodeStyleSetAlignItems(root, _YGAlignFlexStart);
  _YGNodeStyleSetWidth(root, 200);
  _YGNodeStyleSetHeight(root, 100);

  const root_child0 = _YGNodeNew();
  _YGNodeStyleSetWidth(root_child0, 50);
  _YGNodeStyleSetHeight(root_child0, 50);
  _YGNodeStyleSetFlexGrow(root_child0, 1);
  _YGNodeStyleSetAspectRatio(root_child0, 1);
  _YGNodeInsertChild(root, root_child0, 0);

  _YGNodeCalculateLayout(root, _YGUndefined, _YGUndefined, _YGDirectionLTR);

  ASSERT_EQ(0, _YGNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, _YGNodeLayoutGetTop(root_child0));
  ASSERT_EQ(100, _YGNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(100, _YGNodeLayoutGetHeight(root_child0));

  _YGNodeFreeRecursive(root);
})();

(function() {
  const root = _YGNodeNew();
  _YGNodeStyleSetAlignItems(root, _YGAlignFlexStart);
  _YGNodeStyleSetFlexDirection(root, _YGFlexDirectionRow);
  _YGNodeStyleSetWidth(root, 200);
  _YGNodeStyleSetHeight(root, 200);

  const root_child0 = _YGNodeNew();
  _YGNodeStyleSetHeight(root_child0, 50);
  _YGNodeStyleSetFlexGrow(root_child0, 1);
  _YGNodeStyleSetAspectRatio(root_child0, 1);
  _YGNodeInsertChild(root, root_child0, 0);

  const root_child1 = _YGNodeNew();
  _YGNodeStyleSetHeight(root_child1, 100);
  _YGNodeStyleSetFlexGrow(root_child1, 1);
  _YGNodeStyleSetAspectRatio(root_child1, 1);
  _YGNodeInsertChild(root, root_child1, 1);

  _YGNodeCalculateLayout(root, _YGUndefined, _YGUndefined, _YGDirectionLTR);

  ASSERT_EQ(0, _YGNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, _YGNodeLayoutGetTop(root_child0));
  ASSERT_EQ(75, _YGNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(75, _YGNodeLayoutGetHeight(root_child0));

  ASSERT_EQ(75, _YGNodeLayoutGetLeft(root_child1));
  ASSERT_EQ(0, _YGNodeLayoutGetTop(root_child1));
  ASSERT_EQ(125, _YGNodeLayoutGetWidth(root_child1));
  ASSERT_EQ(125, _YGNodeLayoutGetHeight(root_child1));

  _YGNodeFreeRecursive(root);
})();

(function() {
  const root = _YGNodeNew();
  _YGNodeStyleSetAlignItems(root, _YGAlignFlexStart);
  _YGNodeStyleSetWidth(root, 200);
  _YGNodeStyleSetHeight(root, 200);

  const root_child0 = _YGNodeNew();
  _YGNodeStyleSetWidth(root_child0, 50);
  _YGNodeStyleSetFlexGrow(root_child0, 1);
  _YGNodeStyleSetAspectRatio(root_child0, 1);
  _YGNodeInsertChild(root, root_child0, 0);

  const root_child1 = _YGNodeNew();
  _YGNodeStyleSetWidth(root_child1, 100);
  _YGNodeStyleSetFlexGrow(root_child1, 1);
  _YGNodeStyleSetAspectRatio(root_child1, 1);
  _YGNodeInsertChild(root, root_child1, 1);

  _YGNodeCalculateLayout(root, _YGUndefined, _YGUndefined, _YGDirectionLTR);

  ASSERT_EQ(0, _YGNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, _YGNodeLayoutGetTop(root_child0));
  ASSERT_EQ(75, _YGNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(75, _YGNodeLayoutGetHeight(root_child0));

  ASSERT_EQ(0, _YGNodeLayoutGetLeft(root_child1));
  ASSERT_EQ(75, _YGNodeLayoutGetTop(root_child1));
  ASSERT_EQ(125, _YGNodeLayoutGetWidth(root_child1));
  ASSERT_EQ(125, _YGNodeLayoutGetHeight(root_child1));

  _YGNodeFreeRecursive(root);
})();

(function() {
  const root = _YGNodeNew();
  _YGNodeStyleSetAlignItems(root, _YGAlignFlexStart);
  _YGNodeStyleSetFlexDirection(root, _YGFlexDirectionRow);
  _YGNodeStyleSetWidth(root, 100);
  _YGNodeStyleSetHeight(root, 100);

  const root_child0 = _YGNodeNew();
  _YGNodeStyleSetWidth(root_child0, 50);
  _YGNodeStyleSetFlexGrow(root_child0, 1);
  _YGNodeStyleSetAspectRatio(root_child0, 0.5);
  _YGNodeInsertChild(root, root_child0, 0);

  _YGNodeCalculateLayout(root, _YGUndefined, _YGUndefined, _YGDirectionLTR);

  ASSERT_EQ(0, _YGNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, _YGNodeLayoutGetTop(root_child0));
  ASSERT_EQ(50, _YGNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(100, _YGNodeLayoutGetHeight(root_child0));

  _YGNodeFreeRecursive(root);
})();

(function() {
  const root = _YGNodeNew();
  _YGNodeStyleSetAlignItems(root, _YGAlignFlexStart);
  _YGNodeStyleSetWidth(root, 100);
  _YGNodeStyleSetHeight(root, 100);

  const root_child0 = _YGNodeNew();
  _YGNodeStyleSetHeight(root_child0, 50);
  _YGNodeStyleSetFlexGrow(root_child0, 1);
  _YGNodeStyleSetAspectRatio(root_child0, 2);
  _YGNodeInsertChild(root, root_child0, 0);

  _YGNodeCalculateLayout(root, _YGUndefined, _YGUndefined, _YGDirectionLTR);

  ASSERT_EQ(0, _YGNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, _YGNodeLayoutGetTop(root_child0));
  ASSERT_EQ(100, _YGNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, _YGNodeLayoutGetHeight(root_child0));

  _YGNodeFreeRecursive(root);
})();

(function() {
  const root = _YGNodeNew();
  _YGNodeStyleSetWidth(root, 100);
  _YGNodeStyleSetHeight(root, 100);

  const root_child0 = _YGNodeNew();
  _YGNodeStyleSetPositionType(root_child0, _YGPositionTypeAbsolute);
  _YGNodeStyleSetPosition(root_child0, _YGEdgeLeft, 10);
  _YGNodeStyleSetPosition(root_child0, _YGEdgeTop, 10);
  _YGNodeStyleSetPosition(root_child0, _YGEdgeRight, 10);
  _YGNodeStyleSetAspectRatio(root_child0, 1);
  _YGNodeInsertChild(root, root_child0, 0);

  _YGNodeCalculateLayout(root, _YGUndefined, _YGUndefined, _YGDirectionLTR);

  ASSERT_EQ(10, _YGNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(10, _YGNodeLayoutGetTop(root_child0));
  ASSERT_EQ(80, _YGNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(80, _YGNodeLayoutGetHeight(root_child0));

  _YGNodeFreeRecursive(root);
})();

(function() {
  const root = _YGNodeNew();
  _YGNodeStyleSetWidth(root, 100);
  _YGNodeStyleSetHeight(root, 100);

  const root_child0 = _YGNodeNew();
  _YGNodeStyleSetPositionType(root_child0, _YGPositionTypeAbsolute);
  _YGNodeStyleSetPosition(root_child0, _YGEdgeLeft, 10);
  _YGNodeStyleSetPosition(root_child0, _YGEdgeTop, 10);
  _YGNodeStyleSetPosition(root_child0, _YGEdgeBottom, 10);
  _YGNodeStyleSetAspectRatio(root_child0, 1);
  _YGNodeInsertChild(root, root_child0, 0);

  _YGNodeCalculateLayout(root, _YGUndefined, _YGUndefined, _YGDirectionLTR);

  ASSERT_EQ(10, _YGNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(10, _YGNodeLayoutGetTop(root_child0));
  ASSERT_EQ(80, _YGNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(80, _YGNodeLayoutGetHeight(root_child0));

  _YGNodeFreeRecursive(root);
})();

(function() {
  const root = _YGNodeNew();
  _YGNodeStyleSetFlexDirection(root, _YGFlexDirectionRow);
  _YGNodeStyleSetWidth(root, 100);
  _YGNodeStyleSetHeight(root, 100);

  const root_child0 = _YGNodeNew();
  _YGNodeStyleSetWidth(root_child0, 50);
  _YGNodeStyleSetAspectRatio(root_child0, 1);
  _YGNodeInsertChild(root, root_child0, 0);

  _YGNodeCalculateLayout(root, _YGUndefined, _YGUndefined, _YGDirectionLTR);

  ASSERT_EQ(0, _YGNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, _YGNodeLayoutGetTop(root_child0));
  ASSERT_EQ(50, _YGNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, _YGNodeLayoutGetHeight(root_child0));

  _YGNodeFreeRecursive(root);
})();

(function() {
  const root = _YGNodeNew();
  _YGNodeStyleSetWidth(root, 100);
  _YGNodeStyleSetHeight(root, 100);

  const root_child0 = _YGNodeNew();
  _YGNodeStyleSetHeight(root_child0, 50);
  _YGNodeStyleSetAspectRatio(root_child0, 1);
  _YGNodeInsertChild(root, root_child0, 0);

  _YGNodeCalculateLayout(root, _YGUndefined, _YGUndefined, _YGDirectionLTR);

  ASSERT_EQ(0, _YGNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, _YGNodeLayoutGetTop(root_child0));
  ASSERT_EQ(50, _YGNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, _YGNodeLayoutGetHeight(root_child0));

  _YGNodeFreeRecursive(root);
})();
