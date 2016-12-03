/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#include <CSSLayout/Yoga.h>
#include <gtest/gtest.h>

TEST(YogaTest, copy_style_same) {
  const YGNodeRef node0 = YGNodeNew();
  const YGNodeRef node1 = YGNodeNew();
  ASSERT_FALSE(YGNodeIsDirty(node0));

  YGNodeCopyStyle(node0, node1);
  ASSERT_FALSE(YGNodeIsDirty(node0));

  YGNodeFree(node0);
  YGNodeFree(node1);
}

TEST(YogaTest, copy_style_modified) {
  const YGNodeRef node0 = YGNodeNew();
  ASSERT_FALSE(YGNodeIsDirty(node0));
  ASSERT_EQ(YGFlexDirectionColumn, YGNodeStyleGetFlexDirection(node0));
  ASSERT_TRUE(YGValueIsUndefined(YGNodeStyleGetMaxHeight(node0)));

  const YGNodeRef node1 = YGNodeNew();
  YGNodeStyleSetFlexDirection(node1, YGFlexDirectionRow);
  YGNodeStyleSetMaxHeight(node1, 10);

  YGNodeCopyStyle(node0, node1);
  ASSERT_TRUE(YGNodeIsDirty(node0));
  ASSERT_EQ(YGFlexDirectionRow, YGNodeStyleGetFlexDirection(node0));
  ASSERT_FLOAT_EQ(10, YGNodeStyleGetMaxHeight(node0));

  YGNodeFree(node0);
  YGNodeFree(node1);
}

TEST(YogaTest, copy_style_modified_same) {
  const YGNodeRef node0 = YGNodeNew();
  YGNodeStyleSetFlexDirection(node0, YGFlexDirectionRow);
  YGNodeStyleSetMaxHeight(node0, 10);
  YGNodeCalculateLayout(node0, YGUndefined, YGUndefined, YGDirectionLTR);
  ASSERT_FALSE(YGNodeIsDirty(node0));

  const YGNodeRef node1 = YGNodeNew();
  YGNodeStyleSetFlexDirection(node1, YGFlexDirectionRow);
  YGNodeStyleSetMaxHeight(node1, 10);

  YGNodeCopyStyle(node0, node1);
  ASSERT_FALSE(YGNodeIsDirty(node0));

  YGNodeFree(node0);
  YGNodeFree(node1);
}
