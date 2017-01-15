/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#include <yoga/Yoga.h>
#include <gtest/gtest.h>

TEST(YogaTest, computed_layout_margin) {
  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetWidth(root, 100);
  YGNodeStyleSetHeight(root, 100);
  YGNodeStyleSetMarginPercent(root, YGEdgeStart, 10);

  YGNodeCalculateLayout(root, 100, 100, YGDirectionLTR);

  ASSERT_FLOAT_EQ(10, YGNodeLayoutGetMargin(root, YGEdgeLeft));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetMargin(root, YGEdgeRight));

  YGNodeCalculateLayout(root, 100, 100, YGDirectionRTL);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetMargin(root, YGEdgeLeft));
  ASSERT_FLOAT_EQ(10, YGNodeLayoutGetMargin(root, YGEdgeRight));

  YGNodeFreeRecursive(root);
}
