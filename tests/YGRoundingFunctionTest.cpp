/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>
#include <yoga/Yoga.h>
#include <yoga/Yoga-internal.h>

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
    YGNodeRef /*node*/,
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
    YGNodeStyleSetMargin(root, YGEdgeLeft, (float) (i + 1));

    YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);
    ASSERT_FLOAT_EQ(10, YGNodeLayoutGetHeight(node1));
  }

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}
