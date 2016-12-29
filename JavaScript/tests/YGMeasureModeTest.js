/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

var constraintList = [];

var _measure = Yoga.addFunction(
function (retAddr, node, width, widthMode, height, heightMode) {
  var currentIndex = constraintList.length;
  constraintList[currentIndex] = {
    width : width,
    widthMode : widthMode,
    height : height,
    heightMode : heightMode };
  Yoga.setValue(retAddr + 0, widthMode == Yoga.MeasureModeUndefined ? 10 : width, 'float');
  Yoga.setValue(retAddr + 4, heightMode == Yoga.MeasureModeUndefined ? 10 : width, 'float');
});

(function() {
  constraintList = [];

  const root = Yoga.nodeNew();
  Yoga.nodeStyleSetWidth(root, 100);
  Yoga.nodeStyleSetHeight(root, 100);

  const root_child0 = Yoga.nodeNew();
  Yoga.nodeSetMeasureFunc(root_child0, _measure);
  Yoga.nodeInsertChild(root, root_child0, 0);

  Yoga.nodeCalculateLayout(root, Yoga.Undefined, Yoga.Undefined, Yoga.DirectionLTR);

  ASSERT_EQ(1, constraintList.length);

  ASSERT_FLOAT_EQ(100, constraintList[0].width);
  ASSERT_EQ(Yoga.MeasureModeExactly, constraintList[0].widthMode);

  Yoga.nodeFreeRecursive(root);
})();

(function() {
  constraintList = [];

  const root = Yoga.nodeNew();
  Yoga.nodeStyleSetFlexDirection(root, Yoga.FlexDirectionRow);
  Yoga.nodeStyleSetWidth(root, 100);
  Yoga.nodeStyleSetHeight(root, 100);

  const root_child0 = Yoga.nodeNew();
  Yoga.nodeSetMeasureFunc(root_child0, _measure);
  Yoga.nodeInsertChild(root, root_child0, 0);

  Yoga.nodeCalculateLayout(root, Yoga.Undefined, Yoga.Undefined, Yoga.DirectionLTR);

  ASSERT_EQ(1, constraintList.length);

  ASSERT_FLOAT_EQ(100, constraintList[0].height);
  ASSERT_EQ(Yoga.MeasureModeExactly, constraintList[0].heightMode);

  Yoga.nodeFreeRecursive(root);
})();

(function() {
  constraintList = [];

  const root = Yoga.nodeNew();
  Yoga.nodeStyleSetWidth(root, 100);
  Yoga.nodeStyleSetHeight(root, 100);

  const root_child0 = Yoga.nodeNew();
  Yoga.nodeSetMeasureFunc(root_child0, _measure);
  Yoga.nodeInsertChild(root, root_child0, 0);

  Yoga.nodeCalculateLayout(root, Yoga.Undefined, Yoga.Undefined, Yoga.DirectionLTR);

  ASSERT_EQ(1, constraintList.length);

  ASSERT_FLOAT_EQ(100, constraintList[0].height);
  ASSERT_EQ(Yoga.MeasureModeAtMost, constraintList[0].heightMode);

  Yoga.nodeFreeRecursive(root);
})();

(function() {
  constraintList = [];

  const root = Yoga.nodeNew();
  Yoga.nodeStyleSetAlignItems(root, Yoga.AlignFlexStart);
  Yoga.nodeStyleSetWidth(root, 100);
  Yoga.nodeStyleSetHeight(root, 100);

  const root_child0 = Yoga.nodeNew();
  Yoga.nodeSetMeasureFunc(root_child0, _measure);
  Yoga.nodeInsertChild(root, root_child0, 0);

  Yoga.nodeCalculateLayout(root, Yoga.Undefined, Yoga.Undefined, Yoga.DirectionLTR);

  ASSERT_EQ(1, constraintList.length);

  ASSERT_FLOAT_EQ(100, constraintList[0].width);
  ASSERT_EQ(Yoga.MeasureModeAtMost, constraintList[0].widthMode);

  Yoga.nodeFreeRecursive(root);
})();

(function() {
  constraintList = [];

  const root = Yoga.nodeNew();
  Yoga.nodeStyleSetFlexDirection(root, Yoga.FlexDirectionRow);
  Yoga.nodeStyleSetWidth(root, 100);
  Yoga.nodeStyleSetHeight(root, 100);

  const root_child0 = Yoga.nodeNew();
  Yoga.nodeSetMeasureFunc(root_child0, _measure);
  Yoga.nodeInsertChild(root, root_child0, 0);

  Yoga.nodeCalculateLayout(root, Yoga.Undefined, Yoga.Undefined, Yoga.DirectionLTR);

  ASSERT_EQ(1, constraintList.length);

  ASSERT_FLOAT_EQ(100, constraintList[0].width);
  ASSERT_EQ(Yoga.MeasureModeAtMost, constraintList[0].widthMode);

  Yoga.nodeFreeRecursive(root);
})();

(function() {
  constraintList = [];

  const root = Yoga.nodeNew();
  Yoga.nodeStyleSetFlexDirection(root, Yoga.FlexDirectionRow);
  Yoga.nodeStyleSetAlignItems(root, Yoga.AlignFlexStart);
  Yoga.nodeStyleSetWidth(root, 100);
  Yoga.nodeStyleSetHeight(root, 100);

  const root_child0 = Yoga.nodeNew();
  Yoga.nodeSetMeasureFunc(root_child0, _measure);
  Yoga.nodeInsertChild(root, root_child0, 0);

  Yoga.nodeCalculateLayout(root, Yoga.Undefined, Yoga.Undefined, Yoga.DirectionLTR);

  ASSERT_EQ(1, constraintList.length);

  ASSERT_FLOAT_EQ(100, constraintList[0].height);
  ASSERT_EQ(Yoga.MeasureModeAtMost, constraintList[0].heightMode);

  Yoga.nodeFreeRecursive(root);
})();

(function() {
  constraintList = [];

  const root = Yoga.nodeNew();
  Yoga.nodeStyleSetHeight(root, 100);

  const root_child0 = Yoga.nodeNew();
  Yoga.nodeStyleSetFlexGrow(root_child0, 1);
  Yoga.nodeSetMeasureFunc(root_child0, _measure);
  Yoga.nodeInsertChild(root, root_child0, 0);

  Yoga.nodeCalculateLayout(root, Yoga.Undefined, Yoga.Undefined, Yoga.DirectionLTR);

  ASSERT_EQ(2, constraintList.length);

  ASSERT_FLOAT_EQ(100, constraintList[0].height);
  ASSERT_EQ(Yoga.MeasureModeAtMost, constraintList[0].heightMode);

  ASSERT_FLOAT_EQ(100, constraintList[1].height);
  ASSERT_EQ(Yoga.MeasureModeExactly, constraintList[1].heightMode);

  Yoga.nodeFreeRecursive(root);
})();

(function() {
  constraintList = [];

  const root = Yoga.nodeNew();
  Yoga.nodeStyleSetHeight(root, 100);

  const root_child0 = Yoga.nodeNew();
  Yoga.nodeStyleSetFlexGrow(root_child0, 1);
  Yoga.nodeStyleSetFlexBasis(root_child0, 0);
  Yoga.nodeSetMeasureFunc(root_child0, _measure);
  Yoga.nodeInsertChild(root, root_child0, 0);

  Yoga.nodeCalculateLayout(root, Yoga.Undefined, Yoga.Undefined, Yoga.DirectionLTR);

  ASSERT_EQ(1, constraintList.length);

  ASSERT_FLOAT_EQ(100, constraintList[0].height);
  ASSERT_EQ(Yoga.MeasureModeExactly, constraintList[0].heightMode);

  Yoga.nodeFreeRecursive(root);
})();

(function() {
  constraintList = [];

  const root = Yoga.nodeNew();
  Yoga.nodeStyleSetAlignItems(root, Yoga.AlignFlexStart);
  Yoga.nodeStyleSetOverflow(root, Yoga.OverflowScroll);
  Yoga.nodeStyleSetHeight(root, 100);
  Yoga.nodeStyleSetWidth(root, 100);

  const root_child0 = Yoga.nodeNew();
  Yoga.nodeSetMeasureFunc(root_child0, _measure);
  Yoga.nodeInsertChild(root, root_child0, 0);

  Yoga.nodeCalculateLayout(root, Yoga.Undefined, Yoga.Undefined, Yoga.DirectionLTR);

  ASSERT_EQ(1, constraintList.length);

  ASSERT_FLOAT_EQ(100, constraintList[0].width);
  ASSERT_EQ(Yoga.MeasureModeAtMost, constraintList[0].widthMode);

  ASSERT_TRUE(Yoga.valueIsUndefined(constraintList[0].height));
  ASSERT_EQ(Yoga.MeasureModeUndefined, constraintList[0].heightMode);

  Yoga.nodeFreeRecursive(root);
})();

(function() {
  constraintList = [];

  const root = Yoga.nodeNew();
  Yoga.nodeStyleSetAlignItems(root, Yoga.AlignFlexStart);
  Yoga.nodeStyleSetFlexDirection(root, Yoga.FlexDirectionRow);
  Yoga.nodeStyleSetOverflow(root, Yoga.OverflowScroll);
  Yoga.nodeStyleSetHeight(root, 100);
  Yoga.nodeStyleSetWidth(root, 100);

  const root_child0 = Yoga.nodeNew();
  Yoga.nodeSetMeasureFunc(root_child0, _measure);
  Yoga.nodeInsertChild(root, root_child0, 0);

  Yoga.nodeCalculateLayout(root, Yoga.Undefined, Yoga.Undefined, Yoga.DirectionLTR);

  ASSERT_EQ(1, constraintList.length);

  ASSERT_TRUE(Yoga.valueIsUndefined(constraintList[0].width));
  ASSERT_EQ(Yoga.MeasureModeUndefined, constraintList[0].widthMode);

  ASSERT_FLOAT_EQ(100, constraintList[0].height);
  ASSERT_EQ(Yoga.MeasureModeAtMost, constraintList[0].heightMode);

  Yoga.nodeFreeRecursive(root);
})();
