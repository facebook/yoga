/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#include <gtest/gtest.h>
#include <yoga/YGNode.h>
#include <yoga/Yoga.h>

TEST(YogaTest, assert_layout_trees_are_same) {
  YGConfig* config = YGConfigNew();
  YGConfigSetUseLegacyStretchBehaviour(config, true);
  const YGNodeRef root1 = YGNodeNewWithConfig(config);
  YGNodeStyleSetWidth(root1, 500);
  YGNodeStyleSetHeight(root1, 500);

  const YGNodeRef root1_child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetAlignItems(root1_child0, YGAlignFlexStart);
  YGNodeInsertChild(root1, root1_child0, 0);

  const YGNodeRef root1_child0_child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexGrow(root1_child0_child0, 1);
  YGNodeStyleSetFlexShrink(root1_child0_child0, 1);
  YGNodeInsertChild(root1_child0, root1_child0_child0, 0);

  const YGNodeRef root1_child0_child0_child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexGrow(root1_child0_child0_child0, 1);
  YGNodeStyleSetFlexShrink(root1_child0_child0_child0, 1);
  YGNodeInsertChild(root1_child0_child0, root1_child0_child0_child0, 0);

  YGNodeCalculateLayout(root1, YGUndefined, YGUndefined, YGDirectionLTR);

  const YGNodeRef root2 = YGNodeNewWithConfig(config);
  YGNodeStyleSetWidth(root2, 500);
  YGNodeStyleSetHeight(root2, 500);

  const YGNodeRef root2_child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetAlignItems(root2_child0, YGAlignFlexStart);
  YGNodeInsertChild(root2, root2_child0, 0);

  const YGNodeRef root2_child0_child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexGrow(root2_child0_child0, 1);
  YGNodeStyleSetFlexShrink(root2_child0_child0, 1);
  YGNodeInsertChild(root2_child0, root2_child0_child0, 0);

  const YGNodeRef root2_child0_child0_child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexGrow(root2_child0_child0_child0, 1);
  YGNodeStyleSetFlexShrink(root2_child0_child0_child0, 1);
  YGNodeInsertChild(root2_child0_child0, root2_child0_child0_child0, 0);

  YGNodeCalculateLayout(root2, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_TRUE(YGNodeLayoutGetDidUseLegacyFlag(root1));
  ASSERT_TRUE(YGNodeLayoutGetDidUseLegacyFlag(root2));
  ASSERT_TRUE(root1->isLayoutTreeEqualToNode(*root2));

  YGNodeStyleSetAlignItems(root2, YGAlignFlexEnd);

  YGNodeCalculateLayout(root2, YGUndefined, YGUndefined, YGDirectionLTR);
  ASSERT_FALSE(root1->isLayoutTreeEqualToNode(*root2));

  YGNodeFreeRecursive(root1);
  YGNodeFreeRecursive(root2);

  YGConfigFree(config);
}
