/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>
#include <yoga/Yoga.h>

TEST(YogaTest, zero_out_layout) {
  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetFlexDirection(root, YGFlexDirectionRow);
  YGNodeStyleSetWidth(root, 200);
  YGNodeStyleSetHeight(root, 200);

  const YGNodeRef child = YGNodeNew();
  YGNodeInsertChild(root, child, 0);
  YGNodeStyleSetWidth(child, 100);
  YGNodeStyleSetHeight(child, 100);
  YGNodeStyleSetMargin(child, YGEdgeTop, 10);
  YGNodeStyleSetPadding(child, YGEdgeTop, 10);

  YGNodeCalculateLayout(root, 100, 100, YGDirectionLTR);

  ASSERT_FLOAT_EQ(10, YGNodeLayoutGetMargin(child, YGEdgeTop));
  ASSERT_FLOAT_EQ(10, YGNodeLayoutGetPadding(child, YGEdgeTop));

  YGNodeStyleSetDisplay(child, YGDisplayNone);

  YGNodeCalculateLayout(root, 100, 100, YGDirectionLTR);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetMargin(child, YGEdgeTop));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetPadding(child, YGEdgeTop));

  YGNodeFreeRecursive(root);
}
