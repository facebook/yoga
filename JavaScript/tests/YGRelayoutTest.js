/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

(function() {
  _YGSetExperimentalFeatureEnabled(_YGExperimentalFeatureWebFlexBasis, true);

  const root = _YGNodeNew();

  const root_child0 = _YGNodeNew();
  _YGNodeStyleSetHeight(root_child0, 10);
  _YGNodeStyleSetFlexBasis(root_child0, 20);
  _YGNodeInsertChild(root, root_child0, 0);

  _YGNodeCalculateLayout(root, 100, _YGUndefined, _YGDirectionLTR);
  _YGNodeCalculateLayout(root, 100, 100, _YGDirectionLTR);

  ASSERT_FLOAT_EQ(20, _YGNodeLayoutGetHeight(root_child0));

  _YGNodeFreeRecursive(root);

  _YGSetExperimentalFeatureEnabled(_YGExperimentalFeatureWebFlexBasis, false);
})();
