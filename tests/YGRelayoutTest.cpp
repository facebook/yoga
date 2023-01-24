/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>
#include <yoga/Yoga.h>

TEST(YogaTest, dont_cache_computed_flex_basis_between_layouts) {
  const YGConfigRef config = YGConfigNew();
  YGConfigSetExperimentalFeatureEnabled(
      config, YGExperimentalFeatureWebFlexBasis, true);

  const YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetHeightPercent(root, 100);
  YGNodeStyleSetWidthPercent(root, 100);

  const YGNodeRef root_child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexBasisPercent(root_child0, 100);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, 100, YGUndefined, YGDirectionLTR);
  YGNodeCalculateLayout(root, 100, 100, YGDirectionLTR);

  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetHeight(root_child0));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}

TEST(YogaTest, recalculate_resolvedDimonsion_onchange) {
  const YGNodeRef root = YGNodeNew();

  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeStyleSetMinHeight(root_child0, 10);
  YGNodeStyleSetMaxHeight(root_child0, 10);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);
  ASSERT_FLOAT_EQ(10, YGNodeLayoutGetHeight(root_child0));

  YGNodeStyleSetMinHeight(root_child0, YGUndefined);
  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetHeight(root_child0));

  YGNodeFreeRecursive(root);
}
