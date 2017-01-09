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

TEST(YogaTest, get_style_horizontal) {
  const YGNodeRef node = YGNodeNew();

  YGNodeStyleSetMargin(node, YGEdgeLeft, 10);
  YGNodeStyleSetMargin(node, YGEdgeRight, 10);
  YGNodeStyleSetMargin(node, YGEdgeStart, 10);
  YGNodeStyleSetMargin(node, YGEdgeEnd, 10);
  ASSERT_FLOAT_EQ(0, YGNodeStyleGetMargin(node, YGEdgeHorizontal).value);

  YGNodeStyleSetMargin(node, YGEdgeAll, 15);
  ASSERT_FLOAT_EQ(15, YGNodeStyleGetMargin(node, YGEdgeHorizontal).value);

  YGNodeStyleSetMargin(node, YGEdgeHorizontal, 20);
  ASSERT_FLOAT_EQ(20, YGNodeStyleGetMargin(node, YGEdgeHorizontal).value);

  YGNodeFreeRecursive(node);
}

TEST(YogaTest, get_style_vertical) {
  const YGNodeRef node = YGNodeNew();

  YGNodeStyleSetMargin(node, YGEdgeTop, 10);
  YGNodeStyleSetMargin(node, YGEdgeBottom, 10);
  ASSERT_FLOAT_EQ(0, YGNodeStyleGetMargin(node, YGEdgeVertical).value);

  YGNodeStyleSetMargin(node, YGEdgeAll, 15);
  ASSERT_FLOAT_EQ(15, YGNodeStyleGetMargin(node, YGEdgeVertical).value);

  YGNodeStyleSetMargin(node, YGEdgeVertical, 20);
  ASSERT_FLOAT_EQ(20, YGNodeStyleGetMargin(node, YGEdgeVertical).value);

  YGNodeFreeRecursive(node);
}

TEST(YogaTest, get_style_all) {
  const YGNodeRef node = YGNodeNew();

  YGNodeStyleSetMargin(node, YGEdgeLeft, 10);
  YGNodeStyleSetMargin(node, YGEdgeRight, 10);
  YGNodeStyleSetMargin(node, YGEdgeStart, 10);
  YGNodeStyleSetMargin(node, YGEdgeEnd, 10);
  YGNodeStyleSetMargin(node, YGEdgeTop, 10);
  YGNodeStyleSetMargin(node, YGEdgeBottom, 10);
  ASSERT_FLOAT_EQ(0, YGNodeStyleGetMargin(node, YGEdgeAll).value);

  YGNodeStyleSetMargin(node, YGEdgeAll, 15);
  ASSERT_FLOAT_EQ(15, YGNodeStyleGetMargin(node, YGEdgeAll).value);

  YGNodeFreeRecursive(node);
}