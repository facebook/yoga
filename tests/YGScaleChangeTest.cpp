/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>
#include <yoga/Yoga.h>

TEST(YogaTest, scale_change_invalidates_layout) {
  YGConfigRef config = YGConfigNew();

  YGNodeRef root = YGNodeNewWithConfig(config);
  YGConfigSetPointScaleFactor(config, 1.0f);

  YGNodeStyleSetFlexDirection(root, YGFlexDirectionRow);
  YGNodeStyleSetWidth(root, 50);
  YGNodeStyleSetHeight(root, 50);

  YGNodeRef root_child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexGrow(root_child0, 1);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeRef root_child1 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexGrow(root_child1, 1);
  YGNodeInsertChild(root, root_child1, 1);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(25, YGNodeLayoutGetLeft(root_child1));

  YGConfigSetPointScaleFactor(config, 1.5f);
  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  // Left should change due to pixel alignment of new scale factor
  ASSERT_FLOAT_EQ(25.333334f, YGNodeLayoutGetLeft(root_child1));

  YGNodeFreeRecursive(root);
  YGConfigFree(config);
}

TEST(YogaTest, errata_config_change_relayout) {
  YGConfig* config = YGConfigNew();
  YGConfigSetErrata(config, YGErrataStretchFlexBasis);
  YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetWidth(root, 500);
  YGNodeStyleSetHeight(root, 500);

  YGNodeRef root_child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetAlignItems(root_child0, YGAlignFlexStart);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeRef root_child0_child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexGrow(root_child0_child0, 1);
  YGNodeStyleSetFlexShrink(root_child0_child0, 1);
  YGNodeInsertChild(root_child0, root_child0_child0, 0);

  YGNodeRef root_child0_child0_child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexGrow(root_child0_child0_child0, 1);
  YGNodeStyleSetFlexShrink(root_child0_child0_child0, 1);
  YGNodeInsertChild(root_child0_child0, root_child0_child0_child0, 0);
  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(500, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(500, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(500, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(500, YGNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetWidth(root_child0_child0));
  ASSERT_FLOAT_EQ(500, YGNodeLayoutGetHeight(root_child0_child0));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0_child0_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0_child0_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetWidth(root_child0_child0_child0));
  ASSERT_FLOAT_EQ(500, YGNodeLayoutGetHeight(root_child0_child0_child0));

  YGConfigSetErrata(config, YGErrataNone);
  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(500, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(500, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(500, YGNodeLayoutGetWidth(root_child0));
  // This should be modified by the lack of the errata
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetWidth(root_child0_child0));
  // This should be modified by the lack of the errata
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetHeight(root_child0_child0));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0_child0_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0_child0_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetWidth(root_child0_child0_child0));
  // This should be modified by the lack of the errata
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetHeight(root_child0_child0_child0));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}

TEST(YogaTest, setting_compatible_config_maintains_layout_cache) {
  static uint32_t measureCallCount = 0;
  auto measureCustom = [](YGNodeConstRef /*node*/,
                          float /*width*/,
                          YGMeasureMode /*widthMode*/,
                          float /*height*/,
                          YGMeasureMode /*heightMode*/) {
    measureCallCount++;
    return YGSize{
        .width = 25.0f,
        .height = 25.0f,
    };
  };

  YGConfigRef config = YGConfigNew();

  YGNodeRef root = YGNodeNewWithConfig(config);
  YGConfigSetPointScaleFactor(config, 1.0f);

  YGNodeStyleSetFlexDirection(root, YGFlexDirectionRow);
  YGNodeStyleSetWidth(root, 50);
  YGNodeStyleSetHeight(root, 50);

  YGNodeRef root_child0 = YGNodeNewWithConfig(config);
  EXPECT_EQ(0, measureCallCount);

  YGNodeSetMeasureFunc(root_child0, measureCustom);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeRef root_child1 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexGrow(root_child1, 1);
  YGNodeInsertChild(root, root_child1, 1);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);
  EXPECT_EQ(1, measureCallCount);
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(25, YGNodeLayoutGetLeft(root_child1));

  YGConfigRef config2 = YGConfigNew();
  // Calling YGConfigSetPointScaleFactor multiple times, ensures that config2
  // gets a different config version that config1
  YGConfigSetPointScaleFactor(config2, 1.0f);
  YGConfigSetPointScaleFactor(config2, 1.5f);
  YGConfigSetPointScaleFactor(config2, 1.0f);

  YGNodeSetConfig(root, config2);
  YGNodeSetConfig(root_child0, config2);
  YGNodeSetConfig(root_child1, config2);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  // Measure should not be called again, as layout should have been cached since
  // config is functionally the same as before
  EXPECT_EQ(1, measureCallCount);
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(25, YGNodeLayoutGetLeft(root_child1));

  YGNodeFreeRecursive(root);
  YGConfigFree(config);
  YGConfigFree(config2);
}
