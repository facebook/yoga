/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the LICENSE
 * file in the root directory of this source tree.
 */

#include <gtest/gtest.h>
#include <yoga/Yoga.h>

TEST(YogaTest, flex_shrink_min_width) {
  const YGConfigRef config = YGConfigNew();
  YGConfigSetUseWebDefaults(config, true);

  const YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexDirection(root, YGFlexDirectionRow);
  YGNodeStyleSetWidth(root, 500);
  YGNodeStyleSetHeight(root, 500);

  const YGNodeRef root_child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexDirection(root_child0, YGFlexDirectionRow);
  YGNodeStyleSetWidth(root_child0, 100);
  YGNodeStyleSetMinWidth(root_child0, 301);
  YGNodeStyleSetHeight(root_child0, 100);
  YGNodeInsertChild(root, root_child0, 0);

  const YGNodeRef root_child1 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexDirection(root_child1, YGFlexDirectionRow);
  YGNodeStyleSetWidth(root_child1, 100);
  YGNodeStyleSetMinWidth(root_child1, 25);
  YGNodeStyleSetHeight(root_child1, 100);
  YGNodeInsertChild(root, root_child1, 1);

  const YGNodeRef root_child2 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexDirection(root_child2, YGFlexDirectionRow);
  YGNodeStyleSetWidth(root_child2, 100);
  YGNodeStyleSetHeight(root_child2, 100);
  YGNodeInsertChild(root, root_child2, 2);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);
  
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(500, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(500, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(301, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(301, YGNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(401, YGNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(99, YGNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetHeight(root_child2));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}

TEST(YogaTest, flex_shrink_flex_grow_min_width) {
  const YGConfigRef config = YGConfigNew();
  YGConfigSetUseWebDefaults(config, true);

  const YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexDirection(root, YGFlexDirectionRow);
  YGNodeStyleSetWidth(root, 500);
  YGNodeStyleSetHeight(root, 500);

  const YGNodeRef root_child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexDirection(root_child0, YGFlexDirectionRow);
  YGNodeStyleSetFlexGrow(root_child0, 0);
  YGNodeStyleSetFlexShrink(root_child0, 1);
  YGNodeStyleSetWidth(root_child0, 100);
  YGNodeStyleSetMinWidth(root_child0, 301);
  YGNodeStyleSetHeight(root_child0, 100);
  YGNodeInsertChild(root, root_child0, 0);

  const YGNodeRef root_child1 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexDirection(root_child1, YGFlexDirectionRow);
  YGNodeStyleSetFlexGrow(root_child1, 1);
  YGNodeStyleSetFlexShrink(root_child1, 1);
  YGNodeStyleSetWidth(root_child1, 100);
  YGNodeStyleSetMinWidth(root_child1, 25);
  YGNodeStyleSetHeight(root_child1, 100);
  YGNodeInsertChild(root, root_child1, 1);

  const YGNodeRef root_child2 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexDirection(root_child2, YGFlexDirectionRow);
  YGNodeStyleSetWidth(root_child2, 100);
  YGNodeStyleSetHeight(root_child2, 100);
  YGNodeStyleSetFlexShrink(root_child2, 1);
  YGNodeStyleSetFlexGrow(root_child2, 1);
  YGNodeInsertChild(root, root_child2, 2);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(500, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(500, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(301, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(301, YGNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(401, YGNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(99, YGNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetHeight(root_child2));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}
