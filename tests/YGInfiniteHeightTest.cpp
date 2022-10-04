/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>
#include <yoga/Yoga.h>

// This test isn't correct from the Flexbox standard standpoint,
// because percentages are calculated with parent constraints.
// However, we need to make sure we fail gracefully in this case, not returning
// NaN
TEST(YogaTest, percent_absolute_position_infinite_height) {
  const YGConfigRef config = YGConfigNew();

  const YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexDirection(root, YGFlexDirectionRow);
  YGNodeStyleSetWidth(root, 300);

  const YGNodeRef root_child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetWidth(root_child0, 300);
  YGNodeStyleSetHeight(root_child0, 300);
  YGNodeInsertChild(root, root_child0, 0);

  const YGNodeRef root_child1 = YGNodeNewWithConfig(config);
  YGNodeStyleSetPositionType(root_child1, YGPositionTypeAbsolute);
  YGNodeStyleSetPositionPercent(root_child1, YGEdgeLeft, 20);
  YGNodeStyleSetPositionPercent(root_child1, YGEdgeTop, 20);
  YGNodeStyleSetWidthPercent(root_child1, 20);
  YGNodeStyleSetHeightPercent(root_child1, 20);
  YGNodeInsertChild(root, root_child1, 1);
  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(300, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(300, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(300, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(300, YGNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(60, YGNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(60, YGNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetHeight(root_child1));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}
