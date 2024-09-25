/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * clang-format off
 * @generated SignedSource<<6a7f059e2eb63c8cd443dcddf18e4ed6>>
 * generated by gentest/gentest-driver.ts from gentest/fixtures/YGBoxSizingTest.html
 */

#include <gtest/gtest.h>
#include <yoga/Yoga.h>
#include "../util/TestUtil.h"

TEST(YogaTest, box_sizing_content_box) {
  GTEST_SKIP();

  YGConfigRef config = YGConfigNew();

  YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetPositionType(root, YGPositionTypeAbsolute);
  YGNodeStyleSetPadding(root, YGEdgeLeft, 5);
  YGNodeStyleSetPadding(root, YGEdgeTop, 5);
  YGNodeStyleSetPadding(root, YGEdgeRight, 5);
  YGNodeStyleSetPadding(root, YGEdgeBottom, 5);
  YGNodeStyleSetBorder(root, YGEdgeLeft, 10);
  YGNodeStyleSetBorder(root, YGEdgeTop, 10);
  YGNodeStyleSetBorder(root, YGEdgeRight, 10);
  YGNodeStyleSetBorder(root, YGEdgeBottom, 10);
  YGNodeStyleSetWidth(root, 100);
  YGNodeStyleSetHeight(root, 100);
  YGNodeStyleSetBoxSizing(root, YGBoxSizingContentBox);
  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(130, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(130, YGNodeLayoutGetHeight(root));

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionRTL);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(130, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(130, YGNodeLayoutGetHeight(root));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}
