/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#include <gtest/gtest.h>
#include <yoga/Yoga.h>

TEST(YogaTest, dont_cache_computed_flex_basis_between_layouts) {
  YGSetExperimentalFeatureEnabled(YGExperimentalFeatureWebFlexBasis, true);

  const YGNodeRef root = YGNodeNew();

  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeStyleSetHeight(root_child0, 10);
  YGNodeStyleSetFlexBasis(root_child0, 20);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, 100, YGUndefined, YGDirectionLTR);
  YGNodeCalculateLayout(root, 100, 100, YGDirectionLTR);

  ASSERT_FLOAT_EQ(20, YGNodeLayoutGetHeight(root_child0));

  YGNodeFreeRecursive(root);

  YGSetExperimentalFeatureEnabled(YGExperimentalFeatureWebFlexBasis, false);
}
