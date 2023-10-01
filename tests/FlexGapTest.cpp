/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>
#include <yoga/Yoga.h>

// TODO: move this to a fixture based test once it supports parsing negative
// values
TEST(FlexGap, gap_negative_value) {
  const YGConfigRef config = YGConfigNew();

  const YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexDirection(root, YGFlexDirectionRow);
  YGNodeStyleSetGap(root, YGGutterAll, -20);
  YGNodeStyleSetHeight(root, 200);

  const YGNodeRef root_child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetWidth(root_child0, 20);
  YGNodeInsertChild(root, root_child0, 0);

  const YGNodeRef root_child1 = YGNodeNewWithConfig(config);
  YGNodeStyleSetWidth(root_child1, 20);
  YGNodeInsertChild(root, root_child1, 1);

  const YGNodeRef root_child2 = YGNodeNewWithConfig(config);
  YGNodeStyleSetWidth(root_child2, 20);
  YGNodeInsertChild(root, root_child2, 2);

  const YGNodeRef root_child3 = YGNodeNewWithConfig(config);
  YGNodeStyleSetWidth(root_child3, 20);
  YGNodeInsertChild(root, root_child3, 3);
  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(80, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(200, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(20, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(200, YGNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(20, YGNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(20, YGNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(200, YGNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(40, YGNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(20, YGNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(200, YGNodeLayoutGetHeight(root_child2));

  ASSERT_FLOAT_EQ(60, YGNodeLayoutGetLeft(root_child3));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child3));
  ASSERT_FLOAT_EQ(20, YGNodeLayoutGetWidth(root_child3));
  ASSERT_FLOAT_EQ(200, YGNodeLayoutGetHeight(root_child3));

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionRTL);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(80, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(200, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(60, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(20, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(200, YGNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(40, YGNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(20, YGNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(200, YGNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(20, YGNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(20, YGNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(200, YGNodeLayoutGetHeight(root_child2));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child3));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child3));
  ASSERT_FLOAT_EQ(20, YGNodeLayoutGetWidth(root_child3));
  ASSERT_FLOAT_EQ(200, YGNodeLayoutGetHeight(root_child3));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}
