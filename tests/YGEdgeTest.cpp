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
  YGNodeStyleSetWidth(root, YGPx(100));
  YGNodeStyleSetHeight(root, YGPx(100));

  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeStyleSetFlexGrow(root_child0, 1);
  YGNodeStyleSetMargin(root_child0, YGEdgeStart, YGPx(10));
  YGNodeStyleSetMargin(root_child0, YGEdgeLeft, YGPx(20));
  YGNodeStyleSetMargin(root_child0, YGEdgeRight, YGPx(20));
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
  YGNodeStyleSetWidth(root, YGPx(100));
  YGNodeStyleSetHeight(root, YGPx(100));

  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeStyleSetFlexGrow(root_child0, 1);
  YGNodeStyleSetMargin(root_child0, YGEdgeEnd, YGPx(10));
  YGNodeStyleSetMargin(root_child0, YGEdgeLeft, YGPx(20));
  YGNodeStyleSetMargin(root_child0, YGEdgeRight, YGPx(20));
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
  YGNodeStyleSetWidth(root, YGPx(100));
  YGNodeStyleSetHeight(root, YGPx(100));

  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeStyleSetFlexGrow(root_child0, 1);
  YGNodeStyleSetMargin(root_child0, YGEdgeHorizontal, YGPx(10));
  YGNodeStyleSetMargin(root_child0, YGEdgeLeft, YGPx(20));
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);
  ASSERT_FLOAT_EQ(20, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(10, YGNodeLayoutGetRight(root_child0));

  YGNodeFreeRecursive(root);
}

TEST(YogaTest, vertical_overridden) {
  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetFlexDirection(root, YGFlexDirectionColumn);
  YGNodeStyleSetWidth(root, YGPx(100));
  YGNodeStyleSetHeight(root, YGPx(100));

  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeStyleSetFlexGrow(root_child0, 1);
  YGNodeStyleSetMargin(root_child0, YGEdgeVertical, YGPx(10));
  YGNodeStyleSetMargin(root_child0, YGEdgeTop, YGPx(20));
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);
  ASSERT_FLOAT_EQ(20, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(10, YGNodeLayoutGetBottom(root_child0));

  YGNodeFreeRecursive(root);
}

TEST(YogaTest, horizontal_overrides_all) {
  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetFlexDirection(root, YGFlexDirectionColumn);
  YGNodeStyleSetWidth(root, YGPx(100));
  YGNodeStyleSetHeight(root, YGPx(100));

  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeStyleSetFlexGrow(root_child0, 1);
  YGNodeStyleSetMargin(root_child0, YGEdgeHorizontal, YGPx(10));
  YGNodeStyleSetMargin(root_child0, YGEdgeAll, YGPx(20));
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
  YGNodeStyleSetWidth(root, YGPx(100));
  YGNodeStyleSetHeight(root, YGPx(100));

  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeStyleSetFlexGrow(root_child0, 1);
  YGNodeStyleSetMargin(root_child0, YGEdgeVertical, YGPx(10));
  YGNodeStyleSetMargin(root_child0, YGEdgeAll, YGPx(20));
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
  YGNodeStyleSetWidth(root, YGPx(100));
  YGNodeStyleSetHeight(root, YGPx(100));

  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeStyleSetFlexGrow(root_child0, 1);
  YGNodeStyleSetMargin(root_child0, YGEdgeLeft, YGPx(10));
  YGNodeStyleSetMargin(root_child0, YGEdgeTop, YGPx(10));
  YGNodeStyleSetMargin(root_child0, YGEdgeRight, YGPx(10));
  YGNodeStyleSetMargin(root_child0, YGEdgeBottom, YGPx(10));
  YGNodeStyleSetMargin(root_child0, YGEdgeAll, YGPx(20));
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);
  ASSERT_FLOAT_EQ(10, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(10, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(10, YGNodeLayoutGetRight(root_child0));
  ASSERT_FLOAT_EQ(10, YGNodeLayoutGetBottom(root_child0));

  YGNodeFreeRecursive(root);
}
