/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

var measureCount = 0;

var _measure = Yoga.addFunction(
function (retAddr, node, width, widthMode, height, heightMode) {
  measureCount++;
  Yoga.setValue(retAddr + 0, 10, 'float');
  Yoga.setValue(retAddr + 4, 10, 'float');
});

(function() {
  const root = Yoga.nodeNew();
  Yoga.nodeStyleSetWidth(root, 100);
  Yoga.nodeStyleSetHeight(root, 100);

  measureCount = 0;

  const root_child0 = Yoga.nodeNew();
  Yoga.nodeSetMeasureFunc(root_child0, _measure);
  Yoga.nodeStyleSetFlexGrow(root_child0, 1);
  Yoga.nodeStyleSetFlexShrink(root_child0, 1);
  Yoga.nodeInsertChild(root, root_child0, 0);

  Yoga.nodeCalculateLayout(root, Yoga.Undefined, Yoga.Undefined, Yoga.DirectionLTR);

  ASSERT_EQ(0, measureCount);

  Yoga.nodeFreeRecursive(root);
})();

(function() {
  const root = Yoga.nodeNew();
  Yoga.nodeSetMeasureFunc(root, _measure);

  const root_child0 = Yoga.nodeNew();
  try {
    ASSERT_DEATH(Yoga.nodeInsertChild(root, root_child0, 0), "Cannot add child.*");
  } catch (e) {
  }
  Yoga.nodeFree(root_child0);
  Yoga.nodeFreeRecursive(root);
})();

(function() {
  const root = Yoga.nodeNew();
  const root_child0 = Yoga.nodeNew();
  Yoga.nodeInsertChild(root, root_child0, 0);

  try {
    ASSERT_DEATH(Yoga.nodeSetMeasureFunc(root, _measure), "Cannot set measure function.*");
  } catch (e) {

  }
  Yoga.nodeFreeRecursive(root);
})();

(function() {
  const root = Yoga.nodeNew();
  Yoga.nodeInsertChild(root, Yoga.nodeNew(), 0);

  Yoga.nodeSetMeasureFunc(root, 0);
  ASSERT_TRUE(Yoga.nodeGetMeasureFunc(root) === 0);
  Yoga.nodeFreeRecursive(root);
})();

