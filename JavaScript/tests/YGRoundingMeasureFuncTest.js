/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

var _measureFloor = Yoga.addFunction(
function (retAddr, node, width, widthMode, height, heightMode) {
  measureCount++;
  Yoga.setValue(retAddr + 0, 10.2, 'float');
  Yoga.setValue(retAddr + 4, 10.2, 'float');
});

var _measureCeil = Yoga.addFunction(
function (retAddr, node, width, widthMode, height, heightMode) {
  measureCount++;
  Yoga.setValue(retAddr + 0, 10.5, 'float');
  Yoga.setValue(retAddr + 4, 10.5, 'float');
});

(function() {
  Yoga.setExperimentalFeatureEnabled(Yoga.ExperimentalFeatureRounding, true);

  const root = Yoga.nodeNew();

  const root_child0 = Yoga.nodeNew();
  Yoga.nodeSetMeasureFunc(root_child0, _measureFloor);
  Yoga.nodeInsertChild(root, root_child0, 0);

  Yoga.nodeCalculateLayout(root, Yoga.Undefined, Yoga.Undefined, Yoga.DirectionLTR);

  ASSERT_FLOAT_EQ(10, Yoga.nodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(10, Yoga.nodeLayoutGetHeight(root_child0));

  Yoga.nodeFreeRecursive(root);

  Yoga.setExperimentalFeatureEnabled(Yoga.ExperimentalFeatureRounding, false);
})();

(function() {
  Yoga.setExperimentalFeatureEnabled(Yoga.ExperimentalFeatureRounding, true);

  const root = Yoga.nodeNew();

  const root_child0 = Yoga.nodeNew();
  Yoga.nodeSetMeasureFunc(root_child0, _measureCeil);
  Yoga.nodeInsertChild(root, root_child0, 0);

  Yoga.nodeCalculateLayout(root, Yoga.Undefined, Yoga.Undefined, Yoga.DirectionLTR);

  ASSERT_FLOAT_EQ(11, Yoga.nodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(11, Yoga.nodeLayoutGetHeight(root_child0));

  Yoga.nodeFreeRecursive(root);

  Yoga.setExperimentalFeatureEnabled(Yoga.ExperimentalFeatureRounding, false);
})();
