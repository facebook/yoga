/*
 * Copyright (c) Facebook, Inc. and its affiliates.
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


YGSize _measureRecalc(YGNodeRef node, float width, YGMeasureMode widthMode, float height, YGMeasureMode heightMode) {
    return YGSize { 0, 0};
}

TEST(YogaTest, recalculate_on_layout_values_change) {
  const YGConfigRef config = YGConfigNew();
  YGConfigSetExperimentalFeatureEnabled(config, YGExperimentalFeatureWebFlexBasis, true);
  YGConfigSetPointScaleFactor(config, 3.f);
  const YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexDirection(root, YGFlexDirectionRow);
  YGNodeStyleSetAlignItems(root, YGAlignFlexStart);
  YGNodeStyleSetAlignContent(root, YGAlignFlexStart);
  const YGNodeRef child = YGNodeNewWithConfig(config);
  YGNodeStyleSetMinHeightPercent(child, 40.f);
  YGNodeStyleSetMaxHeightPercent(child, 60.f);
  YGNodeStyleSetHeight(child, 10.f);
  YGNodeStyleSetWidth(child, 50.0f);
  YGNodeSetMeasureFunc(child, _measureRecalc);
  YGNodeInsertChild(root, child, 0);

  YGNodeCalculateLayout(root, 50.0f, YGUndefined, YGDirectionLTR);
  ASSERT_FLOAT_EQ(10, YGNodeLayoutGetHeight(child));

  YGNodeCalculateLayout(root, 50.0f, 30.0f, YGDirectionLTR);
  ASSERT_FLOAT_EQ(12, YGNodeLayoutGetHeight(child));

  YGNodeFreeRecursive(root);
}
