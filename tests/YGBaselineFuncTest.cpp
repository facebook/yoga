/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>
#include <yoga/Yoga.h>

static float
_baseline(YGNodeConstRef node, const float /*width*/, const float /*height*/) {
  float* baseline = (float*)YGNodeGetContext(node);
  return *baseline;
}

TEST(YogaTest, align_baseline_customer_func) {
  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetFlexDirection(root, YGFlexDirectionRow);
  YGNodeStyleSetAlignItems(root, YGAlignBaseline);
  YGNodeStyleSetWidth(root, 100);
  YGNodeStyleSetHeight(root, 100);

  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeStyleSetWidth(root_child0, 50);
  YGNodeStyleSetHeight(root_child0, 50);
  YGNodeInsertChild(root, root_child0, 0);

  const YGNodeRef root_child1 = YGNodeNew();
  YGNodeStyleSetWidth(root_child1, 50);
  YGNodeStyleSetHeight(root_child1, 20);
  YGNodeInsertChild(root, root_child1, 1);

  float baselineValue = 10;
  const YGNodeRef root_child1_child0 = YGNodeNew();
  YGNodeSetContext(root_child1_child0, &baselineValue);
  YGNodeStyleSetWidth(root_child1_child0, 50);
  YGNodeSetBaselineFunc(root_child1_child0, _baseline);
  YGNodeStyleSetHeight(root_child1_child0, 20);
  YGNodeInsertChild(root_child1, root_child1_child0, 0);
  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(40, YGNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(20, YGNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child1_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child1_child0));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetWidth(root_child1_child0));
  ASSERT_FLOAT_EQ(20, YGNodeLayoutGetHeight(root_child1_child0));
}
