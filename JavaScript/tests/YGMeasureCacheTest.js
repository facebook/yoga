/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

var store = [0, 0];

var _measureMax = Yoga.addFunction(
function (retAddr, node, width, widthMode, height, heightMode) {
  var measureCount = Yoga.nodeGetContext(node);
  store[measureCount]++;
  Yoga.setValue(retAddr + 0, widthMode == Yoga.MeasureModeUndefined ? 10 : width, 'float');
  Yoga.setValue(retAddr + 4, heightMode == Yoga.MeasureModeUndefined ? 10 : height, 'float');
});

var _measureMin= Yoga.addFunction(
function (retAddr, node, width, widthMode, height, heightMode) {
  var measureCount = Yoga.nodeGetContext(node);
  store[measureCount]++;
  Yoga.setValue(retAddr + 0, widthMode == Yoga.MeasureModeUndefined || (widthMode == Yoga.MeasureModeAtMost && width > 10) ? 10 : width, 'float');
  Yoga.setValue(retAddr + 4, heightMode == Yoga.MeasureModeUndefined || (heightMode == Yoga.MeasureModeAtMost && height > 10) ? 10 : height, 'float');
});

(function() {
  const root = Yoga.nodeNew();
  Yoga.nodeStyleSetFlexDirection(root, Yoga.FlexDirectionRow);
  Yoga.nodeStyleSetAlignItems(root, Yoga.AlignFlexStart);
  Yoga.nodeStyleSetWidth(root, 100);
  Yoga.nodeStyleSetHeight(root, 100);

  const root_child0 = Yoga.nodeNew();
  var measureCount = 2;
  store[measureCount] = 0;
  Yoga.nodeSetContext(root_child0, measureCount);
  Yoga.nodeSetMeasureFunc(root_child0, _measureMax);
  Yoga.nodeStyleSetFlexGrow(root_child0, 1);
  Yoga.nodeInsertChild(root, root_child0, 0);

  Yoga.nodeCalculateLayout(root, Yoga.Undefined, Yoga.Undefined, Yoga.DirectionLTR);

  ASSERT_EQ(1, store[measureCount]);

  Yoga.nodeFreeRecursive(root);
})();

(function() {
  const root = Yoga.nodeNew();

  const root_child0 = Yoga.nodeNew();
  var measureCount = 1;
  store[measureCount] = 0;
  Yoga.nodeSetContext(root_child0, measureCount);
  Yoga.nodeSetMeasureFunc(root_child0, _measureMin);
  Yoga.nodeInsertChild(root, root_child0, 0);

  Yoga.nodeCalculateLayout(root, 100, 100, Yoga.DirectionLTR);
  Yoga.nodeCalculateLayout(root, 100, 50, Yoga.DirectionLTR);

  ASSERT_EQ(1, store[measureCount]);

  Yoga.nodeFreeRecursive(root);
})();

(function() {
  const root = Yoga.nodeNew();
  Yoga.nodeStyleSetAlignItems(root, Yoga.AlignFlexStart);

  const root_child0 = Yoga.nodeNew();
  var measureCount = 1;
  store[measureCount] = 0;
  Yoga.nodeSetContext(root_child0, measureCount);
  Yoga.nodeSetMeasureFunc(root_child0, _measureMin);
  Yoga.nodeInsertChild(root, root_child0, 0);

  Yoga.nodeCalculateLayout(root, 100, 100, Yoga.DirectionLTR);
  Yoga.nodeCalculateLayout(root, 100, 50, Yoga.DirectionLTR);

  ASSERT_EQ(1, store[measureCount]);

  Yoga.nodeFreeRecursive(root);
})();

(function() {
  const root = Yoga.nodeNew();
  Yoga.nodeStyleSetAlignItems(root, Yoga.AlignFlexStart);

  const root_child0 = Yoga.nodeNew();
  var measureCount = 1;
  store[measureCount] = 0;
  Yoga.nodeSetContext(root_child0, measureCount);
  Yoga.nodeSetMeasureFunc(root_child0, _measureMin);
  Yoga.nodeInsertChild(root, root_child0, 0);

  Yoga.nodeCalculateLayout(root, 100, 100, Yoga.DirectionLTR);
  Yoga.nodeStyleSetAlignItems(root, Yoga.AlignStretch);
  Yoga.nodeCalculateLayout(root, 10, 50, Yoga.DirectionLTR);

  ASSERT_EQ(1, store[measureCount]);

  Yoga.nodeFreeRecursive(root);
})();

(function() {
  const root = Yoga.nodeNew();
  Yoga.nodeStyleSetAlignItems(root, Yoga.AlignFlexStart);

  const root_child0 = Yoga.nodeNew();
  var measureCount = 1;
  store[measureCount] = 0;
  Yoga.nodeSetContext(root_child0, measureCount);
  Yoga.nodeSetMeasureFunc(root_child0, _measureMin);
  Yoga.nodeInsertChild(root, root_child0, 0);

  Yoga.nodeCalculateLayout(root, 100, Yoga.Undefined, Yoga.DirectionLTR);
  Yoga.nodeCalculateLayout(root, 10, Yoga.Undefined, Yoga.DirectionLTR);

  ASSERT_EQ(1, store[measureCount]);

  Yoga.nodeFreeRecursive(root);
})();
