/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

var _measureFloor = Runtime.addFunction(
function (retAddr, node, width, widthMode, height, heightMode) {
  measureCount++;
  setValue(retAddr + 0, 10.2, 'float');
  setValue(retAddr + 4, 10.2, 'float');
});

var _measureCeil = Runtime.addFunction(
function (retAddr, node, width, widthMode, height, heightMode) {
  measureCount++;
  setValue(retAddr + 0, 10.5, 'float');
  setValue(retAddr + 4, 10.5, 'float');
});

(function() {
  _YGSetExperimentalFeatureEnabled(_YGExperimentalFeatureRounding, true);

  const root = _YGNodeNew();

  const root_child0 = _YGNodeNew();
  _YGNodeSetMeasureFunc(root_child0, _measureFloor);
  _YGNodeInsertChild(root, root_child0, 0);

  _YGNodeCalculateLayout(root, _YGUndefined, _YGUndefined, _YGDirectionLTR);

  ASSERT_FLOAT_EQ(10, _YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(10, _YGNodeLayoutGetHeight(root_child0));

  _YGNodeFreeRecursive(root);

  _YGSetExperimentalFeatureEnabled(_YGExperimentalFeatureRounding, false);
})();

(function() {
  _YGSetExperimentalFeatureEnabled(_YGExperimentalFeatureRounding, true);

  const root = _YGNodeNew();

  const root_child0 = _YGNodeNew();
  _YGNodeSetMeasureFunc(root_child0, _measureCeil);
  _YGNodeInsertChild(root, root_child0, 0);

  _YGNodeCalculateLayout(root, _YGUndefined, _YGUndefined, _YGDirectionLTR);

  ASSERT_FLOAT_EQ(11, _YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(11, _YGNodeLayoutGetHeight(root_child0));

  _YGNodeFreeRecursive(root);

  _YGSetExperimentalFeatureEnabled(_YGExperimentalFeatureRounding, false);
})();
