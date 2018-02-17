/**
 * Copyright (c) 2014-present, Facebook, Inc.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>
#include <yoga/Yoga.h>

TEST(YogaTest, computed_layout_padding) {
  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetWidth(root, 100);
  YGNodeStyleSetHeight(root, 100);
  YGNodeStyleSetPaddingPercent(root, YGEdgeStart, 10);

  YGNodeCalculateLayout(root, 100, 100, YGDirectionLTR);

  ASSERT_FLOAT_EQ(10, YGNodeLayoutGetPadding(root, YGEdgeLeft));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetPadding(root, YGEdgeRight));

  YGNodeCalculateLayout(root, 100, 100, YGDirectionRTL);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetPadding(root, YGEdgeLeft));
  ASSERT_FLOAT_EQ(10, YGNodeLayoutGetPadding(root, YGEdgeRight));

  YGNodeFreeRecursive(root);
}
