/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

var _measure = Yoga.addFunction(
function (retAddr, node, width, widthMode, height, heightMode) {
  Yoga.setValue(retAddr + 0, widthMode === Yoga.MeasureModeExactly ? width : 50, 'float');
  Yoga.setValue(retAddr + 4, heightMode === Yoga.MeasureModeExactly ? height : 50, 'float');
});


(function() {
  const root = Yoga.nodeNew();
  Yoga.nodeStyleSetAlignItems(root, Yoga.AlignFlexStart);
  Yoga.nodeStyleSetWidth(root, 100);
  Yoga.nodeStyleSetHeight(root, 100);

  const root_child0 = Yoga.nodeNew();
  Yoga.nodeStyleSetWidth(root_child0, 50);
  Yoga.nodeStyleSetAspectRatio(root_child0, 1);
  Yoga.nodeInsertChild(root, root_child0, 0);

  Yoga.nodeCalculateLayout(root, Yoga.Undefined, Yoga.Undefined, Yoga.DirectionLTR);

  ASSERT_EQ(0, Yoga.nodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, Yoga.nodeLayoutGetTop(root_child0));
  ASSERT_EQ(50, Yoga.nodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, Yoga.nodeLayoutGetHeight(root_child0));

  Yoga.nodeFreeRecursive(root);
})();

(function() {
  const root = Yoga.nodeNew();
  Yoga.nodeStyleSetAlignItems(root, Yoga.AlignFlexStart);
  Yoga.nodeStyleSetWidth(root, 100);
  Yoga.nodeStyleSetHeight(root, 100);

  const root_child0 = Yoga.nodeNew();
  Yoga.nodeStyleSetHeight(root_child0, 50);
  Yoga.nodeStyleSetAspectRatio(root_child0, 1);
  Yoga.nodeInsertChild(root, root_child0, 0);

  Yoga.nodeCalculateLayout(root, Yoga.Undefined, Yoga.Undefined, Yoga.DirectionLTR);

  ASSERT_EQ(0, Yoga.nodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, Yoga.nodeLayoutGetTop(root_child0));
  ASSERT_EQ(50, Yoga.nodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, Yoga.nodeLayoutGetHeight(root_child0));

  Yoga.nodeFreeRecursive(root);
})();

(function() {
  const root = Yoga.nodeNew();
  Yoga.nodeStyleSetFlexDirection(root, Yoga.FlexDirectionRow);
  Yoga.nodeStyleSetAlignItems(root, Yoga.AlignFlexStart);
  Yoga.nodeStyleSetWidth(root, 100);
  Yoga.nodeStyleSetHeight(root, 100);

  const root_child0 = Yoga.nodeNew();
  Yoga.nodeStyleSetWidth(root_child0, 100);
  Yoga.nodeStyleSetHeight(root_child0, 50);
  Yoga.nodeStyleSetAspectRatio(root_child0, 1);
  Yoga.nodeInsertChild(root, root_child0, 0);

  Yoga.nodeCalculateLayout(root, Yoga.Undefined, Yoga.Undefined, Yoga.DirectionLTR);

  ASSERT_EQ(0, Yoga.nodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, Yoga.nodeLayoutGetTop(root_child0));
  ASSERT_EQ(100, Yoga.nodeLayoutGetWidth(root_child0));
  ASSERT_EQ(100, Yoga.nodeLayoutGetHeight(root_child0));

  Yoga.nodeFreeRecursive(root);
})();

(function() {
  const root = Yoga.nodeNew();
  Yoga.nodeStyleSetAlignItems(root, Yoga.AlignFlexStart);
  Yoga.nodeStyleSetWidth(root, 100);
  Yoga.nodeStyleSetHeight(root, 100);

  const root_child0 = Yoga.nodeNew();
  Yoga.nodeStyleSetWidth(root_child0, 100);
  Yoga.nodeStyleSetHeight(root_child0, 50);
  Yoga.nodeStyleSetAspectRatio(root_child0, 1);
  Yoga.nodeInsertChild(root, root_child0, 0);

  Yoga.nodeCalculateLayout(root, Yoga.Undefined, Yoga.Undefined, Yoga.DirectionLTR);

  ASSERT_EQ(0, Yoga.nodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, Yoga.nodeLayoutGetTop(root_child0));
  ASSERT_EQ(50, Yoga.nodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, Yoga.nodeLayoutGetHeight(root_child0));

  Yoga.nodeFreeRecursive(root);
})();

(function() {
  const root = Yoga.nodeNew();
  Yoga.nodeStyleSetWidth(root, 100);
  Yoga.nodeStyleSetHeight(root, 100);

  const root_child0 = Yoga.nodeNew();
  Yoga.nodeStyleSetAspectRatio(root_child0, 1);
  Yoga.nodeInsertChild(root, root_child0, 0);

  Yoga.nodeCalculateLayout(root, Yoga.Undefined, Yoga.Undefined, Yoga.DirectionLTR);

  ASSERT_EQ(0, Yoga.nodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, Yoga.nodeLayoutGetTop(root_child0));
  ASSERT_EQ(100, Yoga.nodeLayoutGetWidth(root_child0));
  ASSERT_EQ(100, Yoga.nodeLayoutGetHeight(root_child0));

  Yoga.nodeFreeRecursive(root);
})();

(function() {
  const root = Yoga.nodeNew();
  Yoga.nodeStyleSetAlignItems(root, Yoga.AlignFlexStart);
  Yoga.nodeStyleSetWidth(root, 100);
  Yoga.nodeStyleSetHeight(root, 100);

  const root_child0 = Yoga.nodeNew();
  Yoga.nodeStyleSetHeight(root_child0, 50);
  Yoga.nodeStyleSetFlexGrow(root_child0, 1);
  Yoga.nodeStyleSetAspectRatio(root_child0, 1);
  Yoga.nodeInsertChild(root, root_child0, 0);

  Yoga.nodeCalculateLayout(root, Yoga.Undefined, Yoga.Undefined, Yoga.DirectionLTR);

  ASSERT_EQ(0, Yoga.nodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, Yoga.nodeLayoutGetTop(root_child0));
  ASSERT_EQ(100, Yoga.nodeLayoutGetWidth(root_child0));
  ASSERT_EQ(100, Yoga.nodeLayoutGetHeight(root_child0));

  Yoga.nodeFreeRecursive(root);
})();

(function() {
  const root = Yoga.nodeNew();
  Yoga.nodeStyleSetAlignItems(root, Yoga.AlignFlexStart);
  Yoga.nodeStyleSetWidth(root, 100);
  Yoga.nodeStyleSetHeight(root, 100);

  const root_child0 = Yoga.nodeNew();
  Yoga.nodeStyleSetHeight(root_child0, 150);
  Yoga.nodeStyleSetFlexShrink(root_child0, 1);
  Yoga.nodeStyleSetAspectRatio(root_child0, 1);
  Yoga.nodeInsertChild(root, root_child0, 0);

  Yoga.nodeCalculateLayout(root, Yoga.Undefined, Yoga.Undefined, Yoga.DirectionLTR);

  ASSERT_EQ(0, Yoga.nodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, Yoga.nodeLayoutGetTop(root_child0));
  ASSERT_EQ(100, Yoga.nodeLayoutGetWidth(root_child0));
  ASSERT_EQ(100, Yoga.nodeLayoutGetHeight(root_child0));

  Yoga.nodeFreeRecursive(root);
})();

(function() {
  const root = Yoga.nodeNew();
  Yoga.nodeStyleSetAlignItems(root, Yoga.AlignFlexStart);
  Yoga.nodeStyleSetWidth(root, 100);
  Yoga.nodeStyleSetHeight(root, 100);

  const root_child0 = Yoga.nodeNew();
  Yoga.nodeStyleSetFlexBasis(root_child0, 50);
  Yoga.nodeStyleSetAspectRatio(root_child0, 1);
  Yoga.nodeInsertChild(root, root_child0, 0);

  Yoga.nodeCalculateLayout(root, Yoga.Undefined, Yoga.Undefined, Yoga.DirectionLTR);

  ASSERT_EQ(0, Yoga.nodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, Yoga.nodeLayoutGetTop(root_child0));
  ASSERT_EQ(50, Yoga.nodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, Yoga.nodeLayoutGetHeight(root_child0));

  Yoga.nodeFreeRecursive(root);
})();

(function() {
  const root = Yoga.nodeNew();
  Yoga.nodeStyleSetWidth(root, 100);
  Yoga.nodeStyleSetHeight(root, 100);

  const root_child0 = Yoga.nodeNew();
  Yoga.nodeStyleSetPositionType(root_child0, Yoga.PositionTypeAbsolute);
  Yoga.nodeStyleSetPosition(root_child0, Yoga.EdgeLeft, 0);
  Yoga.nodeStyleSetPosition(root_child0, Yoga.EdgeTop, 0);
  Yoga.nodeStyleSetWidth(root_child0, 50);
  Yoga.nodeStyleSetAspectRatio(root_child0, 1);
  Yoga.nodeInsertChild(root, root_child0, 0);

  Yoga.nodeCalculateLayout(root, Yoga.Undefined, Yoga.Undefined, Yoga.DirectionLTR);

  ASSERT_EQ(0, Yoga.nodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, Yoga.nodeLayoutGetTop(root_child0));
  ASSERT_EQ(50, Yoga.nodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, Yoga.nodeLayoutGetHeight(root_child0));

  Yoga.nodeFreeRecursive(root);
})();

(function() {
  const root = Yoga.nodeNew();
  Yoga.nodeStyleSetWidth(root, 100);
  Yoga.nodeStyleSetHeight(root, 100);

  const root_child0 = Yoga.nodeNew();
  Yoga.nodeStyleSetPositionType(root_child0, Yoga.PositionTypeAbsolute);
  Yoga.nodeStyleSetPosition(root_child0, Yoga.EdgeLeft, 0);
  Yoga.nodeStyleSetPosition(root_child0, Yoga.EdgeTop, 0);
  Yoga.nodeStyleSetHeight(root_child0, 50);
  Yoga.nodeStyleSetAspectRatio(root_child0, 1);
  Yoga.nodeInsertChild(root, root_child0, 0);

  Yoga.nodeCalculateLayout(root, Yoga.Undefined, Yoga.Undefined, Yoga.DirectionLTR);

  ASSERT_EQ(0, Yoga.nodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, Yoga.nodeLayoutGetTop(root_child0));
  ASSERT_EQ(50, Yoga.nodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, Yoga.nodeLayoutGetHeight(root_child0));

  Yoga.nodeFreeRecursive(root);
})();

(function() {
  const root = Yoga.nodeNew();
  Yoga.nodeStyleSetAlignItems(root, Yoga.AlignFlexStart);
  Yoga.nodeStyleSetWidth(root, 100);
  Yoga.nodeStyleSetHeight(root, 100);

  const root_child0 = Yoga.nodeNew();
  Yoga.nodeStyleSetHeight(root_child0, 50);
  Yoga.nodeStyleSetMaxWidth(root_child0, 40);
  Yoga.nodeStyleSetAspectRatio(root_child0, 1);
  Yoga.nodeInsertChild(root, root_child0, 0);

  Yoga.nodeCalculateLayout(root, Yoga.Undefined, Yoga.Undefined, Yoga.DirectionLTR);

  ASSERT_EQ(0, Yoga.nodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, Yoga.nodeLayoutGetTop(root_child0));
  ASSERT_EQ(40, Yoga.nodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, Yoga.nodeLayoutGetHeight(root_child0));

  Yoga.nodeFreeRecursive(root);
})();

(function() {
  const root = Yoga.nodeNew();
  Yoga.nodeStyleSetAlignItems(root, Yoga.AlignFlexStart);
  Yoga.nodeStyleSetWidth(root, 100);
  Yoga.nodeStyleSetHeight(root, 100);

  const root_child0 = Yoga.nodeNew();
  Yoga.nodeStyleSetWidth(root_child0, 50);
  Yoga.nodeStyleSetMaxHeight(root_child0, 40);
  Yoga.nodeStyleSetAspectRatio(root_child0, 1);
  Yoga.nodeInsertChild(root, root_child0, 0);

  Yoga.nodeCalculateLayout(root, Yoga.Undefined, Yoga.Undefined, Yoga.DirectionLTR);

  ASSERT_EQ(0, Yoga.nodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, Yoga.nodeLayoutGetTop(root_child0));
  ASSERT_EQ(50, Yoga.nodeLayoutGetWidth(root_child0));
  ASSERT_EQ(40, Yoga.nodeLayoutGetHeight(root_child0));

  Yoga.nodeFreeRecursive(root);
})();

(function() {
  const root = Yoga.nodeNew();
  Yoga.nodeStyleSetAlignItems(root, Yoga.AlignFlexStart);
  Yoga.nodeStyleSetWidth(root, 100);
  Yoga.nodeStyleSetHeight(root, 100);

  const root_child0 = Yoga.nodeNew();
  Yoga.nodeStyleSetHeight(root_child0, 30);
  Yoga.nodeStyleSetMinWidth(root_child0, 40);
  Yoga.nodeStyleSetAspectRatio(root_child0, 1);
  Yoga.nodeInsertChild(root, root_child0, 0);

  Yoga.nodeCalculateLayout(root, Yoga.Undefined, Yoga.Undefined, Yoga.DirectionLTR);

  ASSERT_EQ(0, Yoga.nodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, Yoga.nodeLayoutGetTop(root_child0));
  ASSERT_EQ(40, Yoga.nodeLayoutGetWidth(root_child0));
  ASSERT_EQ(30, Yoga.nodeLayoutGetHeight(root_child0));

  Yoga.nodeFreeRecursive(root);
})();

(function() {
  const root = Yoga.nodeNew();
  Yoga.nodeStyleSetAlignItems(root, Yoga.AlignFlexStart);
  Yoga.nodeStyleSetWidth(root, 100);
  Yoga.nodeStyleSetHeight(root, 100);

  const root_child0 = Yoga.nodeNew();
  Yoga.nodeStyleSetWidth(root_child0, 30);
  Yoga.nodeStyleSetMinHeight(root_child0, 40);
  Yoga.nodeStyleSetAspectRatio(root_child0, 1);
  Yoga.nodeInsertChild(root, root_child0, 0);

  Yoga.nodeCalculateLayout(root, Yoga.Undefined, Yoga.Undefined, Yoga.DirectionLTR);

  ASSERT_EQ(0, Yoga.nodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, Yoga.nodeLayoutGetTop(root_child0));
  ASSERT_EQ(30, Yoga.nodeLayoutGetWidth(root_child0));
  ASSERT_EQ(40, Yoga.nodeLayoutGetHeight(root_child0));

  Yoga.nodeFreeRecursive(root);
})();

(function() {
  const root = Yoga.nodeNew();
  Yoga.nodeStyleSetAlignItems(root, Yoga.AlignFlexStart);
  Yoga.nodeStyleSetWidth(root, 100);
  Yoga.nodeStyleSetHeight(root, 100);

  const root_child0 = Yoga.nodeNew();
  Yoga.nodeStyleSetHeight(root_child0, 50);
  Yoga.nodeStyleSetAspectRatio(root_child0, 2);
  Yoga.nodeInsertChild(root, root_child0, 0);

  Yoga.nodeCalculateLayout(root, Yoga.Undefined, Yoga.Undefined, Yoga.DirectionLTR);

  ASSERT_EQ(0, Yoga.nodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, Yoga.nodeLayoutGetTop(root_child0));
  ASSERT_EQ(100, Yoga.nodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, Yoga.nodeLayoutGetHeight(root_child0));

  Yoga.nodeFreeRecursive(root);
})();

(function() {
  const root = Yoga.nodeNew();
  Yoga.nodeStyleSetAlignItems(root, Yoga.AlignFlexStart);
  Yoga.nodeStyleSetWidth(root, 100);
  Yoga.nodeStyleSetHeight(root, 100);

  const root_child0 = Yoga.nodeNew();
  Yoga.nodeStyleSetHeight(root_child0, 100);
  Yoga.nodeStyleSetAspectRatio(root_child0, 0.5);
  Yoga.nodeInsertChild(root, root_child0, 0);

  Yoga.nodeCalculateLayout(root, Yoga.Undefined, Yoga.Undefined, Yoga.DirectionLTR);

  ASSERT_EQ(0, Yoga.nodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, Yoga.nodeLayoutGetTop(root_child0));
  ASSERT_EQ(50, Yoga.nodeLayoutGetWidth(root_child0));
  ASSERT_EQ(100, Yoga.nodeLayoutGetHeight(root_child0));

  Yoga.nodeFreeRecursive(root);
})();

(function() {
  const root = Yoga.nodeNew();
  Yoga.nodeStyleSetAlignItems(root, Yoga.AlignFlexStart);
  Yoga.nodeStyleSetWidth(root, 100);
  Yoga.nodeStyleSetHeight(root, 100);

  const root_child0 = Yoga.nodeNew();
  Yoga.nodeStyleSetWidth(root_child0, 50);
  Yoga.nodeStyleSetAspectRatio(root_child0, 0.5);
  Yoga.nodeInsertChild(root, root_child0, 0);

  Yoga.nodeCalculateLayout(root, Yoga.Undefined, Yoga.Undefined, Yoga.DirectionLTR);

  ASSERT_EQ(0, Yoga.nodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, Yoga.nodeLayoutGetTop(root_child0));
  ASSERT_EQ(50, Yoga.nodeLayoutGetWidth(root_child0));
  ASSERT_EQ(100, Yoga.nodeLayoutGetHeight(root_child0));

  Yoga.nodeFreeRecursive(root);
})();

(function() {
  const root = Yoga.nodeNew();
  Yoga.nodeStyleSetAlignItems(root, Yoga.AlignFlexStart);
  Yoga.nodeStyleSetWidth(root, 100);
  Yoga.nodeStyleSetHeight(root, 100);

  const root_child0 = Yoga.nodeNew();
  Yoga.nodeStyleSetWidth(root_child0, 100);
  Yoga.nodeStyleSetAspectRatio(root_child0, 2);
  Yoga.nodeInsertChild(root, root_child0, 0);

  Yoga.nodeCalculateLayout(root, Yoga.Undefined, Yoga.Undefined, Yoga.DirectionLTR);

  ASSERT_EQ(0, Yoga.nodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, Yoga.nodeLayoutGetTop(root_child0));
  ASSERT_EQ(100, Yoga.nodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, Yoga.nodeLayoutGetHeight(root_child0));

  Yoga.nodeFreeRecursive(root);
})();

(function() {
  const root = Yoga.nodeNew();
  Yoga.nodeStyleSetAlignItems(root, Yoga.AlignFlexStart);
  Yoga.nodeStyleSetWidth(root, 100);
  Yoga.nodeStyleSetHeight(root, 100);

  const root_child0 = Yoga.nodeNew();
  Yoga.nodeSetMeasureFunc(root_child0, _measure);
  Yoga.nodeStyleSetAspectRatio(root_child0, 1);
  Yoga.nodeInsertChild(root, root_child0, 0);

  Yoga.nodeCalculateLayout(root, Yoga.Undefined, Yoga.Undefined, Yoga.DirectionLTR);

  ASSERT_EQ(0, Yoga.nodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, Yoga.nodeLayoutGetTop(root_child0));
  ASSERT_EQ(50, Yoga.nodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, Yoga.nodeLayoutGetHeight(root_child0));

  Yoga.nodeFreeRecursive(root);
})();

(function() {
  const root = Yoga.nodeNew();
  Yoga.nodeStyleSetFlexDirection(root, Yoga.FlexDirectionRow);
  Yoga.nodeStyleSetAlignItems(root, Yoga.AlignFlexStart);
  Yoga.nodeStyleSetWidth(root, 100);
  Yoga.nodeStyleSetHeight(root, 200);

  const root_child0 = Yoga.nodeNew();
  Yoga.nodeStyleSetWidth(root_child0, 50);
  Yoga.nodeStyleSetHeight(root_child0, 50);
  Yoga.nodeStyleSetFlexGrow(root_child0, 1);
  Yoga.nodeStyleSetAspectRatio(root_child0, 1);
  Yoga.nodeInsertChild(root, root_child0, 0);

  Yoga.nodeCalculateLayout(root, Yoga.Undefined, Yoga.Undefined, Yoga.DirectionLTR);

  ASSERT_EQ(0, Yoga.nodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, Yoga.nodeLayoutGetTop(root_child0));
  ASSERT_EQ(100, Yoga.nodeLayoutGetWidth(root_child0));
  ASSERT_EQ(100, Yoga.nodeLayoutGetHeight(root_child0));

  Yoga.nodeFreeRecursive(root);
})();

(function() {
  const root = Yoga.nodeNew();
  Yoga.nodeStyleSetAlignItems(root, Yoga.AlignFlexStart);
  Yoga.nodeStyleSetWidth(root, 200);
  Yoga.nodeStyleSetHeight(root, 100);

  const root_child0 = Yoga.nodeNew();
  Yoga.nodeStyleSetWidth(root_child0, 50);
  Yoga.nodeStyleSetHeight(root_child0, 50);
  Yoga.nodeStyleSetFlexGrow(root_child0, 1);
  Yoga.nodeStyleSetAspectRatio(root_child0, 1);
  Yoga.nodeInsertChild(root, root_child0, 0);

  Yoga.nodeCalculateLayout(root, Yoga.Undefined, Yoga.Undefined, Yoga.DirectionLTR);

  ASSERT_EQ(0, Yoga.nodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, Yoga.nodeLayoutGetTop(root_child0));
  ASSERT_EQ(100, Yoga.nodeLayoutGetWidth(root_child0));
  ASSERT_EQ(100, Yoga.nodeLayoutGetHeight(root_child0));

  Yoga.nodeFreeRecursive(root);
})();

(function() {
  const root = Yoga.nodeNew();
  Yoga.nodeStyleSetAlignItems(root, Yoga.AlignFlexStart);
  Yoga.nodeStyleSetFlexDirection(root, Yoga.FlexDirectionRow);
  Yoga.nodeStyleSetWidth(root, 200);
  Yoga.nodeStyleSetHeight(root, 200);

  const root_child0 = Yoga.nodeNew();
  Yoga.nodeStyleSetHeight(root_child0, 50);
  Yoga.nodeStyleSetFlexGrow(root_child0, 1);
  Yoga.nodeStyleSetAspectRatio(root_child0, 1);
  Yoga.nodeInsertChild(root, root_child0, 0);

  const root_child1 = Yoga.nodeNew();
  Yoga.nodeStyleSetHeight(root_child1, 100);
  Yoga.nodeStyleSetFlexGrow(root_child1, 1);
  Yoga.nodeStyleSetAspectRatio(root_child1, 1);
  Yoga.nodeInsertChild(root, root_child1, 1);

  Yoga.nodeCalculateLayout(root, Yoga.Undefined, Yoga.Undefined, Yoga.DirectionLTR);

  ASSERT_EQ(0, Yoga.nodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, Yoga.nodeLayoutGetTop(root_child0));
  ASSERT_EQ(75, Yoga.nodeLayoutGetWidth(root_child0));
  ASSERT_EQ(75, Yoga.nodeLayoutGetHeight(root_child0));

  ASSERT_EQ(75, Yoga.nodeLayoutGetLeft(root_child1));
  ASSERT_EQ(0, Yoga.nodeLayoutGetTop(root_child1));
  ASSERT_EQ(125, Yoga.nodeLayoutGetWidth(root_child1));
  ASSERT_EQ(125, Yoga.nodeLayoutGetHeight(root_child1));

  Yoga.nodeFreeRecursive(root);
})();

(function() {
  const root = Yoga.nodeNew();
  Yoga.nodeStyleSetAlignItems(root, Yoga.AlignFlexStart);
  Yoga.nodeStyleSetWidth(root, 200);
  Yoga.nodeStyleSetHeight(root, 200);

  const root_child0 = Yoga.nodeNew();
  Yoga.nodeStyleSetWidth(root_child0, 50);
  Yoga.nodeStyleSetFlexGrow(root_child0, 1);
  Yoga.nodeStyleSetAspectRatio(root_child0, 1);
  Yoga.nodeInsertChild(root, root_child0, 0);

  const root_child1 = Yoga.nodeNew();
  Yoga.nodeStyleSetWidth(root_child1, 100);
  Yoga.nodeStyleSetFlexGrow(root_child1, 1);
  Yoga.nodeStyleSetAspectRatio(root_child1, 1);
  Yoga.nodeInsertChild(root, root_child1, 1);

  Yoga.nodeCalculateLayout(root, Yoga.Undefined, Yoga.Undefined, Yoga.DirectionLTR);

  ASSERT_EQ(0, Yoga.nodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, Yoga.nodeLayoutGetTop(root_child0));
  ASSERT_EQ(75, Yoga.nodeLayoutGetWidth(root_child0));
  ASSERT_EQ(75, Yoga.nodeLayoutGetHeight(root_child0));

  ASSERT_EQ(0, Yoga.nodeLayoutGetLeft(root_child1));
  ASSERT_EQ(75, Yoga.nodeLayoutGetTop(root_child1));
  ASSERT_EQ(125, Yoga.nodeLayoutGetWidth(root_child1));
  ASSERT_EQ(125, Yoga.nodeLayoutGetHeight(root_child1));

  Yoga.nodeFreeRecursive(root);
})();

(function() {
  const root = Yoga.nodeNew();
  Yoga.nodeStyleSetAlignItems(root, Yoga.AlignFlexStart);
  Yoga.nodeStyleSetFlexDirection(root, Yoga.FlexDirectionRow);
  Yoga.nodeStyleSetWidth(root, 100);
  Yoga.nodeStyleSetHeight(root, 100);

  const root_child0 = Yoga.nodeNew();
  Yoga.nodeStyleSetWidth(root_child0, 50);
  Yoga.nodeStyleSetFlexGrow(root_child0, 1);
  Yoga.nodeStyleSetAspectRatio(root_child0, 0.5);
  Yoga.nodeInsertChild(root, root_child0, 0);

  Yoga.nodeCalculateLayout(root, Yoga.Undefined, Yoga.Undefined, Yoga.DirectionLTR);

  ASSERT_EQ(0, Yoga.nodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, Yoga.nodeLayoutGetTop(root_child0));
  ASSERT_EQ(50, Yoga.nodeLayoutGetWidth(root_child0));
  ASSERT_EQ(100, Yoga.nodeLayoutGetHeight(root_child0));

  Yoga.nodeFreeRecursive(root);
})();

(function() {
  const root = Yoga.nodeNew();
  Yoga.nodeStyleSetAlignItems(root, Yoga.AlignFlexStart);
  Yoga.nodeStyleSetWidth(root, 100);
  Yoga.nodeStyleSetHeight(root, 100);

  const root_child0 = Yoga.nodeNew();
  Yoga.nodeStyleSetHeight(root_child0, 50);
  Yoga.nodeStyleSetFlexGrow(root_child0, 1);
  Yoga.nodeStyleSetAspectRatio(root_child0, 2);
  Yoga.nodeInsertChild(root, root_child0, 0);

  Yoga.nodeCalculateLayout(root, Yoga.Undefined, Yoga.Undefined, Yoga.DirectionLTR);

  ASSERT_EQ(0, Yoga.nodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, Yoga.nodeLayoutGetTop(root_child0));
  ASSERT_EQ(100, Yoga.nodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, Yoga.nodeLayoutGetHeight(root_child0));

  Yoga.nodeFreeRecursive(root);
})();

(function() {
  const root = Yoga.nodeNew();
  Yoga.nodeStyleSetWidth(root, 100);
  Yoga.nodeStyleSetHeight(root, 100);

  const root_child0 = Yoga.nodeNew();
  Yoga.nodeStyleSetPositionType(root_child0, Yoga.PositionTypeAbsolute);
  Yoga.nodeStyleSetPosition(root_child0, Yoga.EdgeLeft, 10);
  Yoga.nodeStyleSetPosition(root_child0, Yoga.EdgeTop, 10);
  Yoga.nodeStyleSetPosition(root_child0, Yoga.EdgeRight, 10);
  Yoga.nodeStyleSetAspectRatio(root_child0, 1);
  Yoga.nodeInsertChild(root, root_child0, 0);

  Yoga.nodeCalculateLayout(root, Yoga.Undefined, Yoga.Undefined, Yoga.DirectionLTR);

  ASSERT_EQ(10, Yoga.nodeLayoutGetLeft(root_child0));
  ASSERT_EQ(10, Yoga.nodeLayoutGetTop(root_child0));
  ASSERT_EQ(80, Yoga.nodeLayoutGetWidth(root_child0));
  ASSERT_EQ(80, Yoga.nodeLayoutGetHeight(root_child0));

  Yoga.nodeFreeRecursive(root);
})();

(function() {
  const root = Yoga.nodeNew();
  Yoga.nodeStyleSetWidth(root, 100);
  Yoga.nodeStyleSetHeight(root, 100);

  const root_child0 = Yoga.nodeNew();
  Yoga.nodeStyleSetPositionType(root_child0, Yoga.PositionTypeAbsolute);
  Yoga.nodeStyleSetPosition(root_child0, Yoga.EdgeLeft, 10);
  Yoga.nodeStyleSetPosition(root_child0, Yoga.EdgeTop, 10);
  Yoga.nodeStyleSetPosition(root_child0, Yoga.EdgeBottom, 10);
  Yoga.nodeStyleSetAspectRatio(root_child0, 1);
  Yoga.nodeInsertChild(root, root_child0, 0);

  Yoga.nodeCalculateLayout(root, Yoga.Undefined, Yoga.Undefined, Yoga.DirectionLTR);

  ASSERT_EQ(10, Yoga.nodeLayoutGetLeft(root_child0));
  ASSERT_EQ(10, Yoga.nodeLayoutGetTop(root_child0));
  ASSERT_EQ(80, Yoga.nodeLayoutGetWidth(root_child0));
  ASSERT_EQ(80, Yoga.nodeLayoutGetHeight(root_child0));

  Yoga.nodeFreeRecursive(root);
})();

(function() {
  const root = Yoga.nodeNew();
  Yoga.nodeStyleSetFlexDirection(root, Yoga.FlexDirectionRow);
  Yoga.nodeStyleSetWidth(root, 100);
  Yoga.nodeStyleSetHeight(root, 100);

  const root_child0 = Yoga.nodeNew();
  Yoga.nodeStyleSetWidth(root_child0, 50);
  Yoga.nodeStyleSetAspectRatio(root_child0, 1);
  Yoga.nodeInsertChild(root, root_child0, 0);

  Yoga.nodeCalculateLayout(root, Yoga.Undefined, Yoga.Undefined, Yoga.DirectionLTR);

  ASSERT_EQ(0, Yoga.nodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, Yoga.nodeLayoutGetTop(root_child0));
  ASSERT_EQ(50, Yoga.nodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, Yoga.nodeLayoutGetHeight(root_child0));

  Yoga.nodeFreeRecursive(root);
})();

(function() {
  const root = Yoga.nodeNew();
  Yoga.nodeStyleSetWidth(root, 100);
  Yoga.nodeStyleSetHeight(root, 100);

  const root_child0 = Yoga.nodeNew();
  Yoga.nodeStyleSetHeight(root_child0, 50);
  Yoga.nodeStyleSetAspectRatio(root_child0, 1);
  Yoga.nodeInsertChild(root, root_child0, 0);

  Yoga.nodeCalculateLayout(root, Yoga.Undefined, Yoga.Undefined, Yoga.DirectionLTR);

  ASSERT_EQ(0, Yoga.nodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, Yoga.nodeLayoutGetTop(root_child0));
  ASSERT_EQ(50, Yoga.nodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, Yoga.nodeLayoutGetHeight(root_child0));

  Yoga.nodeFreeRecursive(root);
})();
