/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>
#include <yoga/Yoga.h>

TEST(YogaTest, rounding_value) {
  // Test that whole numbers are rounded to whole despite ceil/floor flags
  ASSERT_FLOAT_EQ(6.0, YGRoundValueToPixelGrid(6.000001, 2.0, false, false));
  ASSERT_FLOAT_EQ(6.0, YGRoundValueToPixelGrid(6.000001, 2.0, true, false));
  ASSERT_FLOAT_EQ(6.0, YGRoundValueToPixelGrid(6.000001, 2.0, false, true));
  ASSERT_FLOAT_EQ(6.0, YGRoundValueToPixelGrid(5.999999, 2.0, false, false));
  ASSERT_FLOAT_EQ(6.0, YGRoundValueToPixelGrid(5.999999, 2.0, true, false));
  ASSERT_FLOAT_EQ(6.0, YGRoundValueToPixelGrid(5.999999, 2.0, false, true));
  // Same tests for negative numbers
  ASSERT_FLOAT_EQ(-6.0, YGRoundValueToPixelGrid(-6.000001, 2.0, false, false));
  ASSERT_FLOAT_EQ(-6.0, YGRoundValueToPixelGrid(-6.000001, 2.0, true, false));
  ASSERT_FLOAT_EQ(-6.0, YGRoundValueToPixelGrid(-6.000001, 2.0, false, true));
  ASSERT_FLOAT_EQ(-6.0, YGRoundValueToPixelGrid(-5.999999, 2.0, false, false));
  ASSERT_FLOAT_EQ(-6.0, YGRoundValueToPixelGrid(-5.999999, 2.0, true, false));
  ASSERT_FLOAT_EQ(-6.0, YGRoundValueToPixelGrid(-5.999999, 2.0, false, true));

  // Test that numbers with fraction are rounded correctly accounting for
  // ceil/floor flags
  ASSERT_FLOAT_EQ(6.0, YGRoundValueToPixelGrid(6.01, 2.0, false, false));
  ASSERT_FLOAT_EQ(6.5, YGRoundValueToPixelGrid(6.01, 2.0, true, false));
  ASSERT_FLOAT_EQ(6.0, YGRoundValueToPixelGrid(6.01, 2.0, false, true));
  ASSERT_FLOAT_EQ(6.0, YGRoundValueToPixelGrid(5.99, 2.0, false, false));
  ASSERT_FLOAT_EQ(6.0, YGRoundValueToPixelGrid(5.99, 2.0, true, false));
  ASSERT_FLOAT_EQ(5.5, YGRoundValueToPixelGrid(5.99, 2.0, false, true));
  // Same tests for negative numbers
  ASSERT_FLOAT_EQ(-6.0, YGRoundValueToPixelGrid(-6.01, 2.0, false, false));
  ASSERT_FLOAT_EQ(-6.0, YGRoundValueToPixelGrid(-6.01, 2.0, true, false));
  ASSERT_FLOAT_EQ(-6.5, YGRoundValueToPixelGrid(-6.01, 2.0, false, true));
  ASSERT_FLOAT_EQ(-6.0, YGRoundValueToPixelGrid(-5.99, 2.0, false, false));
  ASSERT_FLOAT_EQ(-5.5, YGRoundValueToPixelGrid(-5.99, 2.0, true, false));
  ASSERT_FLOAT_EQ(-6.0, YGRoundValueToPixelGrid(-5.99, 2.0, false, true));
}

static YGSize measureText(
    YGNodeConstRef /*node*/,
    float /*width*/,
    YGMeasureMode /*widthMode*/,
    float /*height*/,
    YGMeasureMode /*heightMode*/) {
  return YGSize{10, 10};
}

// Regression test for https://github.com/facebook/yoga/issues/824
TEST(YogaTest, consistent_rounding_during_repeated_layouts) {
  const YGConfigRef config = YGConfigNew();
  YGConfigSetPointScaleFactor(config, 2);

  const YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetMargin(root, YGEdgeTop, -1.49f);
  YGNodeStyleSetWidth(root, 500);
  YGNodeStyleSetHeight(root, 500);

  const YGNodeRef node0 = YGNodeNewWithConfig(config);
  YGNodeInsertChild(root, node0, 0);

  const YGNodeRef node1 = YGNodeNewWithConfig(config);
  YGNodeSetMeasureFunc(node1, measureText);
  YGNodeInsertChild(node0, node1, 0);

  for (int i = 0; i < 5; i++) {
    // Dirty the tree so YGRoundToPixelGrid runs again
    YGNodeStyleSetMargin(root, YGEdgeLeft, (float)(i + 1));

    YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);
    ASSERT_FLOAT_EQ(10, YGNodeLayoutGetHeight(node1));
  }

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}

TEST(YogaTest, per_node_point_scale_factor) {
  const YGConfigRef config1 = YGConfigNew();
  YGConfigSetPointScaleFactor(config1, 2);

  const YGConfigRef config2 = YGConfigNew();
  YGConfigSetPointScaleFactor(config2, 1);

  const YGConfigRef config3 = YGConfigNew();
  YGConfigSetPointScaleFactor(config3, 0.5f);

  const YGNodeRef root = YGNodeNewWithConfig(config1);
  YGNodeStyleSetWidth(root, 11.5);
  YGNodeStyleSetHeight(root, 11.5);

  const YGNodeRef node0 = YGNodeNewWithConfig(config2);
  YGNodeStyleSetWidth(node0, 9.5);
  YGNodeStyleSetHeight(node0, 9.5);
  YGNodeInsertChild(root, node0, 0);

  const YGNodeRef node1 = YGNodeNewWithConfig(config3);
  YGNodeStyleSetWidth(node1, 7);
  YGNodeStyleSetHeight(node1, 7);
  YGNodeInsertChild(node0, node1, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(YGNodeLayoutGetWidth(root), 11.5);
  ASSERT_EQ(YGNodeLayoutGetHeight(root), 11.5);

  ASSERT_EQ(YGNodeLayoutGetWidth(node0), 10);
  ASSERT_EQ(YGNodeLayoutGetHeight(node0), 10);

  ASSERT_EQ(YGNodeLayoutGetWidth(node1), 8);
  ASSERT_EQ(YGNodeLayoutGetHeight(node1), 8);

  YGNodeFreeRecursive(root);

  YGConfigFree(config1);
  YGConfigFree(config2);
  YGConfigFree(config3);
}
