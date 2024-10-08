/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * clang-format off
 * @generated SignedSource<<00e4ee58a2a66a3fcd064d3c517d8330>>
 * generated by gentest/gentest-driver.ts from gentest/fixtures/YGAutoTest.html
 */

#include <gtest/gtest.h>
#include <yoga/Yoga.h>
#include "../util/TestUtil.h"

TEST(YogaTest, auto_width) {
  YGConfigRef config = YGConfigNew();

  YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexDirection(root, YGFlexDirectionRow);
  YGNodeStyleSetPositionType(root, YGPositionTypeAbsolute);
  YGNodeStyleSetWidthAuto(root);
  YGNodeStyleSetHeight(root, 50);

  YGNodeRef root_child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetWidth(root_child0, 50);
  YGNodeStyleSetHeight(root_child0, 50);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeRef root_child1 = YGNodeNewWithConfig(config);
  YGNodeStyleSetWidth(root_child1, 50);
  YGNodeStyleSetHeight(root_child1, 50);
  YGNodeInsertChild(root, root_child1, 1);

  YGNodeRef root_child2 = YGNodeNewWithConfig(config);
  YGNodeStyleSetWidth(root_child2, 50);
  YGNodeStyleSetHeight(root_child2, 50);
  YGNodeInsertChild(root, root_child2, 2);
  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(150, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetHeight(root_child2));

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionRTL);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(150, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetHeight(root_child2));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}

TEST(YogaTest, auto_height) {
  YGConfigRef config = YGConfigNew();

  YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetPositionType(root, YGPositionTypeAbsolute);
  YGNodeStyleSetWidth(root, 50);
  YGNodeStyleSetHeightAuto(root);

  YGNodeRef root_child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetWidth(root_child0, 50);
  YGNodeStyleSetHeight(root_child0, 50);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeRef root_child1 = YGNodeNewWithConfig(config);
  YGNodeStyleSetWidth(root_child1, 50);
  YGNodeStyleSetHeight(root_child1, 50);
  YGNodeInsertChild(root, root_child1, 1);

  YGNodeRef root_child2 = YGNodeNewWithConfig(config);
  YGNodeStyleSetWidth(root_child2, 50);
  YGNodeStyleSetHeight(root_child2, 50);
  YGNodeInsertChild(root, root_child2, 2);
  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(150, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetHeight(root_child2));

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionRTL);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(150, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetHeight(root_child2));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}

TEST(YogaTest, auto_flex_basis) {
  YGConfigRef config = YGConfigNew();

  YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetPositionType(root, YGPositionTypeAbsolute);
  YGNodeStyleSetWidth(root, 50);

  YGNodeRef root_child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetWidth(root_child0, 50);
  YGNodeStyleSetHeight(root_child0, 50);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeRef root_child1 = YGNodeNewWithConfig(config);
  YGNodeStyleSetWidth(root_child1, 50);
  YGNodeStyleSetHeight(root_child1, 50);
  YGNodeInsertChild(root, root_child1, 1);

  YGNodeRef root_child2 = YGNodeNewWithConfig(config);
  YGNodeStyleSetWidth(root_child2, 50);
  YGNodeStyleSetHeight(root_child2, 50);
  YGNodeInsertChild(root, root_child2, 2);
  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(150, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetHeight(root_child2));

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionRTL);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(150, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetHeight(root_child2));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}

TEST(YogaTest, auto_position) {
  YGConfigRef config = YGConfigNew();

  YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetPositionType(root, YGPositionTypeAbsolute);
  YGNodeStyleSetWidth(root, 50);
  YGNodeStyleSetHeight(root, 50);

  YGNodeRef root_child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetPositionAuto(root_child0, YGEdgeRight);
  YGNodeStyleSetWidth(root_child0, 25);
  YGNodeStyleSetHeight(root_child0, 25);
  YGNodeInsertChild(root, root_child0, 0);
  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(25, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(25, YGNodeLayoutGetHeight(root_child0));

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionRTL);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(25, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(25, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(25, YGNodeLayoutGetHeight(root_child0));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}

TEST(YogaTest, auto_margin) {
  YGConfigRef config = YGConfigNew();

  YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetPositionType(root, YGPositionTypeAbsolute);
  YGNodeStyleSetWidth(root, 50);
  YGNodeStyleSetHeight(root, 50);

  YGNodeRef root_child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetMarginAuto(root_child0, YGEdgeLeft);
  YGNodeStyleSetWidth(root_child0, 25);
  YGNodeStyleSetHeight(root_child0, 25);
  YGNodeInsertChild(root, root_child0, 0);
  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(25, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(25, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(25, YGNodeLayoutGetHeight(root_child0));

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionRTL);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(25, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(25, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(25, YGNodeLayoutGetHeight(root_child0));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}
