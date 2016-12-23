/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

var measureCount = 0;

var _measure = Runtime.addFunction(
function (retAddr, node, width, widthMode, height, heightMode) {
  measureCount++;
  setValue(retAddr + 0, 10, 'float');
  setValue(retAddr + 4, 10, 'float');
});

(function() {
  const root = _YGNodeNew();
  _YGNodeStyleSetWidth(root, 100);
  _YGNodeStyleSetHeight(root, 100);

  measureCount = 0;

  const root_child0 = _YGNodeNew();
  _YGNodeSetMeasureFunc(root_child0, _measure);
  _YGNodeStyleSetFlexGrow(root_child0, 1);
  _YGNodeStyleSetFlexShrink(root_child0, 1);
  _YGNodeInsertChild(root, root_child0, 0);

  _YGNodeCalculateLayout(root, _YGUndefined, _YGUndefined, _YGDirectionLTR);

  ASSERT_EQ(0, measureCount);

  _YGNodeFreeRecursive(root);
})();

(function() {
  const root = _YGNodeNew();
  _YGNodeSetMeasureFunc(root, _measure);

  const root_child0 = _YGNodeNew();
  try {
    ASSERT_DEATH(_YGNodeInsertChild(root, root_child0, 0), "Cannot add child.*");
  } catch (e) {
  }
  _YGNodeFree(root_child0);
  _YGNodeFreeRecursive(root);
})();

(function() {
  const root = _YGNodeNew();
  const root_child0 = _YGNodeNew();
  _YGNodeInsertChild(root, root_child0, 0);

  try {
    ASSERT_DEATH(_YGNodeSetMeasureFunc(root, _measure), "Cannot set measure function.*");
  } catch (e) {

  }
  _YGNodeFreeRecursive(root);
})();

(function() {
  const root = _YGNodeNew();
  _YGNodeInsertChild(root, _YGNodeNew(), 0);

  _YGNodeSetMeasureFunc(root, 0);
  ASSERT_TRUE(_YGNodeGetMeasureFunc(root) === 0);
  _YGNodeFreeRecursive(root);
})();

