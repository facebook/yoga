/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

(function() {
  Yoga.setExperimentalFeatureEnabled(Yoga.ExperimentalFeatureWebFlexBasis, true);

  const root = Yoga.nodeNew();

  const root_child0 = Yoga.nodeNew();
  Yoga.nodeStyleSetHeight(root_child0, 10);
  Yoga.nodeStyleSetFlexBasis(root_child0, 20);
  Yoga.nodeInsertChild(root, root_child0, 0);

  Yoga.nodeCalculateLayout(root, 100, Yoga.Undefined, Yoga.DirectionLTR);
  Yoga.nodeCalculateLayout(root, 100, 100, Yoga.DirectionLTR);

  ASSERT_FLOAT_EQ(20, Yoga.nodeLayoutGetHeight(root_child0));

  Yoga.nodeFreeRecursive(root);

  Yoga.setExperimentalFeatureEnabled(Yoga.ExperimentalFeatureWebFlexBasis, false);
})();
