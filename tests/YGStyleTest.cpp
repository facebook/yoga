/**
 * Copyright (c) 2014-present, Facebook, Inc.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>
#include <yoga/YGNode.h>
#include <iostream>

TEST(YogaTest, copy_style_same) {
  const YGNodeRef node0 = YGNodeNew();
  const YGNodeRef node1 = YGNodeNew();
  ASSERT_FALSE(node0->isDirty());

  YGNodeCopyStyle(node0, node1);
  ASSERT_FALSE(node0->isDirty());

  YGNodeFree(node0);
  YGNodeFree(node1);
}

TEST(YogaTest, copy_style_modified) {
  const YGNodeRef node0 = YGNodeNew();
  ASSERT_FALSE(node0->isDirty());
  ASSERT_EQ(YGFlexDirectionColumn, YGNodeStyleGetFlexDirection(node0));
  ASSERT_FALSE(YGNodeStyleGetMaxHeight(node0).unit != YGUnitUndefined);

  const YGNodeRef node1 = YGNodeNew();
  YGNodeStyleSetFlexDirection(node1, YGFlexDirectionRow);
  YGNodeStyleSetMaxHeight(node1, 10);

  YGNodeCopyStyle(node0, node1);
  ASSERT_TRUE(node0->isDirty());
  ASSERT_EQ(YGFlexDirectionRow, YGNodeStyleGetFlexDirection(node0));
  ASSERT_FLOAT_EQ(10, YGNodeStyleGetMaxHeight(node0).value);

  YGNodeFree(node0);
  YGNodeFree(node1);
}

TEST(YogaTest, copy_style_modified_same) {
  const YGNodeRef node0 = YGNodeNew();
  YGNodeStyleSetFlexDirection(node0, YGFlexDirectionRow);
  YGNodeStyleSetMaxHeight(node0, 10);
  YGNodeCalculateLayout(node0, YGUndefined, YGUndefined, YGDirectionLTR);
  ASSERT_FALSE(node0->isDirty());

  const YGNodeRef node1 = YGNodeNew();
  YGNodeStyleSetFlexDirection(node1, YGFlexDirectionRow);
  YGNodeStyleSetMaxHeight(node1, 10);

  YGNodeCopyStyle(node0, node1);
  ASSERT_FALSE(node0->isDirty());

  YGNodeFree(node0);
  YGNodeFree(node1);
}
