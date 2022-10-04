/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>
#include <yoga/testutil/testutil.h>
#include <yoga/YGNode.h>
#include <yoga/Yoga.h>

using facebook::yoga::test::TestUtil;

TEST(YogaTest, assert_layout_trees_are_same) {
  TestUtil::startCountingNodes();

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

  const int32_t cal1_configInstanceCount = YGConfigGetInstanceCount();
  const int32_t cal1_nodeInstanceCount = TestUtil::nodeCount();

  YGNodeCalculateLayout(root1, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(YGConfigGetInstanceCount(), cal1_configInstanceCount);
  ASSERT_EQ(TestUtil::nodeCount(), cal1_nodeInstanceCount);

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

  const int32_t cal2_configInstanceCount = YGConfigGetInstanceCount();
  const int32_t cal2_nodeInstanceCount = TestUtil::nodeCount();

  YGNodeCalculateLayout(root2, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(YGConfigGetInstanceCount(), cal2_configInstanceCount);
  ASSERT_EQ(TestUtil::nodeCount(), cal2_nodeInstanceCount);

  ASSERT_TRUE(YGNodeLayoutGetDidUseLegacyFlag(root1));
  ASSERT_TRUE(YGNodeLayoutGetDidUseLegacyFlag(root2));
  ASSERT_TRUE(root1->isLayoutTreeEqualToNode(*root2));

  YGNodeStyleSetAlignItems(root2, YGAlignFlexEnd);

  const int32_t cal3_configInstanceCount = YGConfigGetInstanceCount();
  const int32_t cal3_nodeInstanceCount = TestUtil::nodeCount();

  YGNodeCalculateLayout(root2, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(YGConfigGetInstanceCount(), cal3_configInstanceCount);
  ASSERT_EQ(TestUtil::stopCountingNodes(), cal3_nodeInstanceCount);

  ASSERT_FALSE(root1->isLayoutTreeEqualToNode(*root2));

  YGNodeFreeRecursive(root1);
  YGNodeFreeRecursive(root2);

  YGConfigFree(config);
}
