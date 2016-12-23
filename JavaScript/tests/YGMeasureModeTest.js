/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

var constraintList = [];

var _measure = Runtime.addFunction(
function (retAddr, node, width, widthMode, height, heightMode) {
  var currentIndex = constraintList.length;
  constraintList[currentIndex] = {
    width : width,
    widthMode : widthMode,
    height : height,
    heightMode : heightMode };
  setValue(retAddr + 0, widthMode == _YGMeasureModeUndefined ? 10 : width, 'float');
  setValue(retAddr + 4, heightMode == _YGMeasureModeUndefined ? 10 : width, 'float');
});

(function() {
  constraintList = [];

  const root = _YGNodeNew();
  _YGNodeStyleSetWidth(root, 100);
  _YGNodeStyleSetHeight(root, 100);

  const root_child0 = _YGNodeNew();
  _YGNodeSetMeasureFunc(root_child0, _measure);
  _YGNodeInsertChild(root, root_child0, 0);

  _YGNodeCalculateLayout(root, _YGUndefined, _YGUndefined, _YGDirectionLTR);

  ASSERT_EQ(1, constraintList.length);

  ASSERT_FLOAT_EQ(100, constraintList[0].width);
  ASSERT_EQ(_YGMeasureModeExactly, constraintList[0].widthMode);

  _YGNodeFreeRecursive(root);
})();

(function() {
  constraintList = [];

  const root = _YGNodeNew();
  _YGNodeStyleSetFlexDirection(root, _YGFlexDirectionRow);
  _YGNodeStyleSetWidth(root, 100);
  _YGNodeStyleSetHeight(root, 100);

  const root_child0 = _YGNodeNew();
  _YGNodeSetMeasureFunc(root_child0, _measure);
  _YGNodeInsertChild(root, root_child0, 0);

  _YGNodeCalculateLayout(root, _YGUndefined, _YGUndefined, _YGDirectionLTR);

  ASSERT_EQ(1, constraintList.length);

  ASSERT_FLOAT_EQ(100, constraintList[0].height);
  ASSERT_EQ(_YGMeasureModeExactly, constraintList[0].heightMode);

  _YGNodeFreeRecursive(root);
})();

(function() {
  constraintList = [];

  const root = _YGNodeNew();
  _YGNodeStyleSetWidth(root, 100);
  _YGNodeStyleSetHeight(root, 100);

  const root_child0 = _YGNodeNew();
  _YGNodeSetMeasureFunc(root_child0, _measure);
  _YGNodeInsertChild(root, root_child0, 0);

  _YGNodeCalculateLayout(root, _YGUndefined, _YGUndefined, _YGDirectionLTR);

  ASSERT_EQ(1, constraintList.length);

  ASSERT_FLOAT_EQ(100, constraintList[0].height);
  ASSERT_EQ(_YGMeasureModeAtMost, constraintList[0].heightMode);

  _YGNodeFreeRecursive(root);
})();

(function() {
  constraintList = [];

  const root = _YGNodeNew();
  _YGNodeStyleSetAlignItems(root, _YGAlignFlexStart);
  _YGNodeStyleSetWidth(root, 100);
  _YGNodeStyleSetHeight(root, 100);

  const root_child0 = _YGNodeNew();
  _YGNodeSetMeasureFunc(root_child0, _measure);
  _YGNodeInsertChild(root, root_child0, 0);

  _YGNodeCalculateLayout(root, _YGUndefined, _YGUndefined, _YGDirectionLTR);

  ASSERT_EQ(1, constraintList.length);

  ASSERT_FLOAT_EQ(100, constraintList[0].width);
  ASSERT_EQ(_YGMeasureModeAtMost, constraintList[0].widthMode);

  _YGNodeFreeRecursive(root);
})();

(function() {
  constraintList = [];

  const root = _YGNodeNew();
  _YGNodeStyleSetFlexDirection(root, _YGFlexDirectionRow);
  _YGNodeStyleSetWidth(root, 100);
  _YGNodeStyleSetHeight(root, 100);

  const root_child0 = _YGNodeNew();
  _YGNodeSetMeasureFunc(root_child0, _measure);
  _YGNodeInsertChild(root, root_child0, 0);

  _YGNodeCalculateLayout(root, _YGUndefined, _YGUndefined, _YGDirectionLTR);

  ASSERT_EQ(1, constraintList.length);

  ASSERT_FLOAT_EQ(100, constraintList[0].width);
  ASSERT_EQ(_YGMeasureModeAtMost, constraintList[0].widthMode);

  _YGNodeFreeRecursive(root);
})();

(function() {
  constraintList = [];

  const root = _YGNodeNew();
  _YGNodeStyleSetFlexDirection(root, _YGFlexDirectionRow);
  _YGNodeStyleSetAlignItems(root, _YGAlignFlexStart);
  _YGNodeStyleSetWidth(root, 100);
  _YGNodeStyleSetHeight(root, 100);

  const root_child0 = _YGNodeNew();
  _YGNodeSetMeasureFunc(root_child0, _measure);
  _YGNodeInsertChild(root, root_child0, 0);

  _YGNodeCalculateLayout(root, _YGUndefined, _YGUndefined, _YGDirectionLTR);

  ASSERT_EQ(1, constraintList.length);

  ASSERT_FLOAT_EQ(100, constraintList[0].height);
  ASSERT_EQ(_YGMeasureModeAtMost, constraintList[0].heightMode);

  _YGNodeFreeRecursive(root);
})();

(function() {
  constraintList = [];

  const root = _YGNodeNew();
  _YGNodeStyleSetHeight(root, 100);

  const root_child0 = _YGNodeNew();
  _YGNodeStyleSetFlexGrow(root_child0, 1);
  _YGNodeSetMeasureFunc(root_child0, _measure);
  _YGNodeInsertChild(root, root_child0, 0);

  _YGNodeCalculateLayout(root, _YGUndefined, _YGUndefined, _YGDirectionLTR);

  ASSERT_EQ(2, constraintList.length);

  ASSERT_FLOAT_EQ(100, constraintList[0].height);
  ASSERT_EQ(_YGMeasureModeAtMost, constraintList[0].heightMode);

  ASSERT_FLOAT_EQ(100, constraintList[1].height);
  ASSERT_EQ(_YGMeasureModeExactly, constraintList[1].heightMode);

  _YGNodeFreeRecursive(root);
})();

(function() {
  constraintList = [];

  const root = _YGNodeNew();
  _YGNodeStyleSetHeight(root, 100);

  const root_child0 = _YGNodeNew();
  _YGNodeStyleSetFlexGrow(root_child0, 1);
  _YGNodeStyleSetFlexBasis(root_child0, 0);
  _YGNodeSetMeasureFunc(root_child0, _measure);
  _YGNodeInsertChild(root, root_child0, 0);

  _YGNodeCalculateLayout(root, _YGUndefined, _YGUndefined, _YGDirectionLTR);

  ASSERT_EQ(1, constraintList.length);

  ASSERT_FLOAT_EQ(100, constraintList[0].height);
  ASSERT_EQ(_YGMeasureModeExactly, constraintList[0].heightMode);

  _YGNodeFreeRecursive(root);
})();

(function() {
  constraintList = [];

  const root = _YGNodeNew();
  _YGNodeStyleSetAlignItems(root, _YGAlignFlexStart);
  _YGNodeStyleSetOverflow(root, _YGOverflowScroll);
  _YGNodeStyleSetHeight(root, 100);
  _YGNodeStyleSetWidth(root, 100);

  const root_child0 = _YGNodeNew();
  _YGNodeSetMeasureFunc(root_child0, _measure);
  _YGNodeInsertChild(root, root_child0, 0);

  _YGNodeCalculateLayout(root, _YGUndefined, _YGUndefined, _YGDirectionLTR);

  ASSERT_EQ(1, constraintList.length);

  ASSERT_FLOAT_EQ(100, constraintList[0].width);
  ASSERT_EQ(_YGMeasureModeAtMost, constraintList[0].widthMode);

  ASSERT_TRUE(_YGValueIsUndefined(constraintList[0].height));
  ASSERT_EQ(_YGMeasureModeUndefined, constraintList[0].heightMode);

  _YGNodeFreeRecursive(root);
})();

(function() {
  constraintList = [];

  const root = _YGNodeNew();
  _YGNodeStyleSetAlignItems(root, _YGAlignFlexStart);
  _YGNodeStyleSetFlexDirection(root, _YGFlexDirectionRow);
  _YGNodeStyleSetOverflow(root, _YGOverflowScroll);
  _YGNodeStyleSetHeight(root, 100);
  _YGNodeStyleSetWidth(root, 100);

  const root_child0 = _YGNodeNew();
  _YGNodeSetMeasureFunc(root_child0, _measure);
  _YGNodeInsertChild(root, root_child0, 0);

  _YGNodeCalculateLayout(root, _YGUndefined, _YGUndefined, _YGDirectionLTR);

  ASSERT_EQ(1, constraintList.length);

  ASSERT_TRUE(_YGValueIsUndefined(constraintList[0].width));
  ASSERT_EQ(_YGMeasureModeUndefined, constraintList[0].widthMode);

  ASSERT_FLOAT_EQ(100, constraintList[0].height);
  ASSERT_EQ(_YGMeasureModeAtMost, constraintList[0].heightMode);

  _YGNodeFreeRecursive(root);
})();
