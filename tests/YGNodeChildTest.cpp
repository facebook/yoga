/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>
#include <yoga/Yoga.h>

TEST(YogaTest, reset_layout_when_child_removed) {
  const YGNodeRef root = YGNodeNew();

  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeStyleSetWidth(root_child0, 100);
  YGNodeStyleSetHeight(root_child0, 100);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_EQ(100, YGNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(100, YGNodeLayoutGetHeight(root_child0));

  YGNodeRemoveChild(root, root_child0);

  ASSERT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_TRUE(YGFloatIsUndefined(YGNodeLayoutGetWidth(root_child0)));
  ASSERT_TRUE(YGFloatIsUndefined(YGNodeLayoutGetHeight(root_child0)));

  YGNodeFreeRecursive(root);
  YGNodeFreeRecursive(root_child0);
}
