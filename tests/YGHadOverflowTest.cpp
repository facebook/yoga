/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>
#include <yoga/Yoga.h>

using namespace ::testing;

class YogaTest_HadOverflowTests : public Test {
 protected:
  YogaTest_HadOverflowTests() {
    config = YGConfigNew();
    root = YGNodeNewWithConfig(config);
    YGNodeStyleSetWidth(root, 200);
    YGNodeStyleSetHeight(root, 100);
    YGNodeStyleSetFlexDirection(root, YGFlexDirectionColumn);
    YGNodeStyleSetFlexWrap(root, YGWrapNoWrap);
  }

  ~YogaTest_HadOverflowTests() {
    YGNodeFreeRecursive(root);
    YGConfigFree(config);
  }

  YGNodeRef root;
  YGConfigRef config;
};

TEST_F(
    YogaTest_HadOverflowTests,
    children_overflow_no_wrap_and_no_flex_children) {
  const YGNodeRef child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetWidth(child0, 80);
  YGNodeStyleSetHeight(child0, 40);
  YGNodeStyleSetMargin(child0, YGEdgeTop, 10);
  YGNodeStyleSetMargin(child0, YGEdgeBottom, 15);
  YGNodeInsertChild(root, child0, 0);
  const YGNodeRef child1 = YGNodeNewWithConfig(config);
  YGNodeStyleSetWidth(child1, 80);
  YGNodeStyleSetHeight(child1, 40);
  YGNodeStyleSetMargin(child1, YGEdgeBottom, 5);
  YGNodeInsertChild(root, child1, 1);

  YGNodeCalculateLayout(root, 200, 100, YGDirectionLTR);

  ASSERT_TRUE(YGNodeLayoutGetHadOverflow(root));
}

TEST_F(
    YogaTest_HadOverflowTests,
    spacing_overflow_no_wrap_and_no_flex_children) {
  const YGNodeRef child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetWidth(child0, 80);
  YGNodeStyleSetHeight(child0, 40);
  YGNodeStyleSetMargin(child0, YGEdgeTop, 10);
  YGNodeStyleSetMargin(child0, YGEdgeBottom, 10);
  YGNodeInsertChild(root, child0, 0);
  const YGNodeRef child1 = YGNodeNewWithConfig(config);
  YGNodeStyleSetWidth(child1, 80);
  YGNodeStyleSetHeight(child1, 40);
  YGNodeStyleSetMargin(child1, YGEdgeBottom, 5);
  YGNodeInsertChild(root, child1, 1);

  YGNodeCalculateLayout(root, 200, 100, YGDirectionLTR);

  ASSERT_TRUE(YGNodeLayoutGetHadOverflow(root));
}

TEST_F(YogaTest_HadOverflowTests, no_overflow_no_wrap_and_flex_children) {
  const YGNodeRef child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetWidth(child0, 80);
  YGNodeStyleSetHeight(child0, 40);
  YGNodeStyleSetMargin(child0, YGEdgeTop, 10);
  YGNodeStyleSetMargin(child0, YGEdgeBottom, 10);
  YGNodeInsertChild(root, child0, 0);
  const YGNodeRef child1 = YGNodeNewWithConfig(config);
  YGNodeStyleSetWidth(child1, 80);
  YGNodeStyleSetHeight(child1, 40);
  YGNodeStyleSetMargin(child1, YGEdgeBottom, 5);
  YGNodeStyleSetFlexShrink(child1, 1);
  YGNodeInsertChild(root, child1, 1);

  YGNodeCalculateLayout(root, 200, 100, YGDirectionLTR);

  ASSERT_FALSE(YGNodeLayoutGetHadOverflow(root));
}

TEST_F(YogaTest_HadOverflowTests, hadOverflow_gets_reset_if_not_logger_valid) {
  const YGNodeRef child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetWidth(child0, 80);
  YGNodeStyleSetHeight(child0, 40);
  YGNodeStyleSetMargin(child0, YGEdgeTop, 10);
  YGNodeStyleSetMargin(child0, YGEdgeBottom, 10);
  YGNodeInsertChild(root, child0, 0);
  const YGNodeRef child1 = YGNodeNewWithConfig(config);
  YGNodeStyleSetWidth(child1, 80);
  YGNodeStyleSetHeight(child1, 40);
  YGNodeStyleSetMargin(child1, YGEdgeBottom, 5);
  YGNodeInsertChild(root, child1, 1);

  YGNodeCalculateLayout(root, 200, 100, YGDirectionLTR);

  ASSERT_TRUE(YGNodeLayoutGetHadOverflow(root));

  YGNodeStyleSetFlexShrink(child1, 1);

  YGNodeCalculateLayout(root, 200, 100, YGDirectionLTR);

  ASSERT_FALSE(YGNodeLayoutGetHadOverflow(root));
}

TEST_F(YogaTest_HadOverflowTests, spacing_overflow_in_nested_nodes) {
  const YGNodeRef child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetWidth(child0, 80);
  YGNodeStyleSetHeight(child0, 40);
  YGNodeStyleSetMargin(child0, YGEdgeTop, 10);
  YGNodeStyleSetMargin(child0, YGEdgeBottom, 10);
  YGNodeInsertChild(root, child0, 0);
  const YGNodeRef child1 = YGNodeNewWithConfig(config);
  YGNodeStyleSetWidth(child1, 80);
  YGNodeStyleSetHeight(child1, 40);
  YGNodeInsertChild(root, child1, 1);
  const YGNodeRef child1_1 = YGNodeNewWithConfig(config);
  YGNodeStyleSetWidth(child1_1, 80);
  YGNodeStyleSetHeight(child1_1, 40);
  YGNodeStyleSetMargin(child1_1, YGEdgeBottom, 5);
  YGNodeInsertChild(child1, child1_1, 0);

  YGNodeCalculateLayout(root, 200, 100, YGDirectionLTR);

  ASSERT_TRUE(YGNodeLayoutGetHadOverflow(root));
}
