/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>
#include <yoga/Yoga.h>

TEST(YogaTest, start_overrides) {
  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetFlexDirection(root, YGFlexDirectionRow);
  YGNodeStyleSetWidth(root, 100);
  YGNodeStyleSetHeight(root, 100);

  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeStyleSetFlexGrow(root_child0, 1);
  YGNodeStyleSetMargin(root_child0, YGEdgeStart, 10);
  YGNodeStyleSetMargin(root_child0, YGEdgeLeft, 20);
  YGNodeStyleSetMargin(root_child0, YGEdgeRight, 20);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);
  ASSERT_FLOAT_EQ(10, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(20, YGNodeLayoutGetRight(root_child0));

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionRTL);
  ASSERT_FLOAT_EQ(20, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(10, YGNodeLayoutGetRight(root_child0));

  YGNodeFreeRecursive(root);
}

TEST(YogaTest, end_overrides) {
  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetFlexDirection(root, YGFlexDirectionRow);
  YGNodeStyleSetWidth(root, 100);
  YGNodeStyleSetHeight(root, 100);

  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeStyleSetFlexGrow(root_child0, 1);
  YGNodeStyleSetMargin(root_child0, YGEdgeEnd, 10);
  YGNodeStyleSetMargin(root_child0, YGEdgeLeft, 20);
  YGNodeStyleSetMargin(root_child0, YGEdgeRight, 20);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);
  ASSERT_FLOAT_EQ(20, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(10, YGNodeLayoutGetRight(root_child0));

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionRTL);
  ASSERT_FLOAT_EQ(10, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(20, YGNodeLayoutGetRight(root_child0));

  YGNodeFreeRecursive(root);
}

TEST(YogaTest, horizontal_overridden) {
  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetFlexDirection(root, YGFlexDirectionRow);
  YGNodeStyleSetWidth(root, 100);
  YGNodeStyleSetHeight(root, 100);

  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeStyleSetFlexGrow(root_child0, 1);
  YGNodeStyleSetMargin(root_child0, YGEdgeHorizontal, 10);
  YGNodeStyleSetMargin(root_child0, YGEdgeLeft, 20);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);
  ASSERT_FLOAT_EQ(20, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(10, YGNodeLayoutGetRight(root_child0));

  YGNodeFreeRecursive(root);
}

TEST(YogaTest, vertical_overridden) {
  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetFlexDirection(root, YGFlexDirectionColumn);
  YGNodeStyleSetWidth(root, 100);
  YGNodeStyleSetHeight(root, 100);

  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeStyleSetFlexGrow(root_child0, 1);
  YGNodeStyleSetMargin(root_child0, YGEdgeVertical, 10);
  YGNodeStyleSetMargin(root_child0, YGEdgeTop, 20);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);
  ASSERT_FLOAT_EQ(20, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(10, YGNodeLayoutGetBottom(root_child0));

  YGNodeFreeRecursive(root);
}

TEST(YogaTest, horizontal_overrides_all) {
  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetFlexDirection(root, YGFlexDirectionColumn);
  YGNodeStyleSetWidth(root, 100);
  YGNodeStyleSetHeight(root, 100);

  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeStyleSetFlexGrow(root_child0, 1);
  YGNodeStyleSetMargin(root_child0, YGEdgeHorizontal, 10);
  YGNodeStyleSetMargin(root_child0, YGEdgeAll, 20);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);
  ASSERT_FLOAT_EQ(10, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(20, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(10, YGNodeLayoutGetRight(root_child0));
  ASSERT_FLOAT_EQ(20, YGNodeLayoutGetBottom(root_child0));

  YGNodeFreeRecursive(root);
}

TEST(YogaTest, vertical_overrides_all) {
  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetFlexDirection(root, YGFlexDirectionColumn);
  YGNodeStyleSetWidth(root, 100);
  YGNodeStyleSetHeight(root, 100);

  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeStyleSetFlexGrow(root_child0, 1);
  YGNodeStyleSetMargin(root_child0, YGEdgeVertical, 10);
  YGNodeStyleSetMargin(root_child0, YGEdgeAll, 20);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);
  ASSERT_FLOAT_EQ(20, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(10, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(20, YGNodeLayoutGetRight(root_child0));
  ASSERT_FLOAT_EQ(10, YGNodeLayoutGetBottom(root_child0));

  YGNodeFreeRecursive(root);
}

TEST(YogaTest, all_overridden) {
  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetFlexDirection(root, YGFlexDirectionColumn);
  YGNodeStyleSetWidth(root, 100);
  YGNodeStyleSetHeight(root, 100);

  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeStyleSetFlexGrow(root_child0, 1);
  YGNodeStyleSetMargin(root_child0, YGEdgeLeft, 10);
  YGNodeStyleSetMargin(root_child0, YGEdgeTop, 10);
  YGNodeStyleSetMargin(root_child0, YGEdgeRight, 10);
  YGNodeStyleSetMargin(root_child0, YGEdgeBottom, 10);
  YGNodeStyleSetMargin(root_child0, YGEdgeAll, 20);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);
  ASSERT_FLOAT_EQ(10, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(10, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(10, YGNodeLayoutGetRight(root_child0));
  ASSERT_FLOAT_EQ(10, YGNodeLayoutGetBottom(root_child0));

  YGNodeFreeRecursive(root);
}
