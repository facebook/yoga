/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

var store = [0, 0];

var _measureMax = Runtime.addFunction(
function (retAddr, node, width, widthMode, height, heightMode) {
  var measureCount = _YGNodeGetContext(node);
  store[measureCount]++;
  setValue(retAddr + 0, widthMode == _YGMeasureModeUndefined ? 10 : width, 'float');
  setValue(retAddr + 4, heightMode == _YGMeasureModeUndefined ? 10 : height, 'float');
});

var _measureMin= Runtime.addFunction(
function (retAddr, node, width, widthMode, height, heightMode) {
  var measureCount = _YGNodeGetContext(node);
  store[measureCount]++;
  setValue(retAddr + 0, widthMode == _YGMeasureModeUndefined || (widthMode == _YGMeasureModeAtMost && width > 10) ? 10 : width, 'float');
  setValue(retAddr + 4, heightMode == _YGMeasureModeUndefined || (heightMode == _YGMeasureModeAtMost && height > 10) ? 10 : height, 'float');
});

(function() {
  const root = _YGNodeNew();
  _YGNodeStyleSetFlexDirection(root, _YGFlexDirectionRow);
  _YGNodeStyleSetAlignItems(root, _YGAlignFlexStart);
  _YGNodeStyleSetWidth(root, 100);
  _YGNodeStyleSetHeight(root, 100);

  const root_child0 = _YGNodeNew();
  var measureCount = 2;
  store[measureCount] = 0;
  _YGNodeSetContext(root_child0, measureCount);
  _YGNodeSetMeasureFunc(root_child0, _measureMax);
  _YGNodeStyleSetFlexGrow(root_child0, 1);
  _YGNodeInsertChild(root, root_child0, 0);

  _YGNodeCalculateLayout(root, _YGUndefined, _YGUndefined, _YGDirectionLTR);

  ASSERT_EQ(1, store[measureCount]);

  _YGNodeFreeRecursive(root);
})();

(function() {
  const root = _YGNodeNew();

  const root_child0 = _YGNodeNew();
  var measureCount = 1;
  store[measureCount] = 0;
  _YGNodeSetContext(root_child0, measureCount);
  _YGNodeSetMeasureFunc(root_child0, _measureMin);
  _YGNodeInsertChild(root, root_child0, 0);

  _YGNodeCalculateLayout(root, 100, 100, _YGDirectionLTR);
  _YGNodeCalculateLayout(root, 100, 50, _YGDirectionLTR);

  ASSERT_EQ(1, store[measureCount]);

  _YGNodeFreeRecursive(root);
})();

(function() {
  const root = _YGNodeNew();
  _YGNodeStyleSetAlignItems(root, _YGAlignFlexStart);

  const root_child0 = _YGNodeNew();
  var measureCount = 1;
  store[measureCount] = 0;
  _YGNodeSetContext(root_child0, measureCount);
  _YGNodeSetMeasureFunc(root_child0, _measureMin);
  _YGNodeInsertChild(root, root_child0, 0);

  _YGNodeCalculateLayout(root, 100, 100, _YGDirectionLTR);
  _YGNodeCalculateLayout(root, 100, 50, _YGDirectionLTR);

  ASSERT_EQ(1, store[measureCount]);

  _YGNodeFreeRecursive(root);
})();

(function() {
  const root = _YGNodeNew();
  _YGNodeStyleSetAlignItems(root, _YGAlignFlexStart);

  const root_child0 = _YGNodeNew();
  var measureCount = 1;
  store[measureCount] = 0;
  _YGNodeSetContext(root_child0, measureCount);
  _YGNodeSetMeasureFunc(root_child0, _measureMin);
  _YGNodeInsertChild(root, root_child0, 0);

  _YGNodeCalculateLayout(root, 100, 100, _YGDirectionLTR);
  _YGNodeStyleSetAlignItems(root, _YGAlignStretch);
  _YGNodeCalculateLayout(root, 10, 50, _YGDirectionLTR);

  ASSERT_EQ(1, store[measureCount]);

  _YGNodeFreeRecursive(root);
})();

(function() {
  const root = _YGNodeNew();
  _YGNodeStyleSetAlignItems(root, _YGAlignFlexStart);

  const root_child0 = _YGNodeNew();
  var measureCount = 1;
  store[measureCount] = 0;
  _YGNodeSetContext(root_child0, measureCount);
  _YGNodeSetMeasureFunc(root_child0, _measureMin);
  _YGNodeInsertChild(root, root_child0, 0);

  _YGNodeCalculateLayout(root, 100, _YGUndefined, _YGDirectionLTR);
  _YGNodeCalculateLayout(root, 10, _YGUndefined, _YGDirectionLTR);

  ASSERT_EQ(1, store[measureCount]);

  _YGNodeFreeRecursive(root);
})();
