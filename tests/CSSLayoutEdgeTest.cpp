/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#include <CSSLayout/CSSLayout.h>
#include <gtest/gtest.h>

TEST(CSSLayoutTest, start_overrides) {
  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetFlexDirection(root, CSSFlexDirectionRow);
  CSSNodeStyleSetWidth(root, 100);
  CSSNodeStyleSetHeight(root, 100);

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeStyleSetFlexGrow(root_child0, 1);
  CSSNodeStyleSetMargin(root_child0, CSSEdgeStart, 10);
  CSSNodeStyleSetMargin(root_child0, CSSEdgeLeft, 20);
  CSSNodeStyleSetMargin(root_child0, CSSEdgeRight, 20);
  CSSNodeInsertChild(root, root_child0, 0);

  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionLTR);
  ASSERT_EQ(10, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(20, CSSNodeLayoutGetRight(root_child0));

  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionRTL);
  ASSERT_EQ(20, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(10, CSSNodeLayoutGetRight(root_child0));

  CSSNodeFreeRecursive(root);
}

TEST(CSSLayoutTest, end_overrides) {
  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetFlexDirection(root, CSSFlexDirectionRow);
  CSSNodeStyleSetWidth(root, 100);
  CSSNodeStyleSetHeight(root, 100);

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeStyleSetFlexGrow(root_child0, 1);
  CSSNodeStyleSetMargin(root_child0, CSSEdgeEnd, 10);
  CSSNodeStyleSetMargin(root_child0, CSSEdgeLeft, 20);
  CSSNodeStyleSetMargin(root_child0, CSSEdgeRight, 20);
  CSSNodeInsertChild(root, root_child0, 0);

  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionLTR);
  ASSERT_EQ(20, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(10, CSSNodeLayoutGetRight(root_child0));

  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionRTL);
  ASSERT_EQ(10, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(20, CSSNodeLayoutGetRight(root_child0));

  CSSNodeFreeRecursive(root);
}

TEST(CSSLayoutTest, horizontal_overridden) {
  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetFlexDirection(root, CSSFlexDirectionRow);
  CSSNodeStyleSetWidth(root, 100);
  CSSNodeStyleSetHeight(root, 100);

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeStyleSetFlexGrow(root_child0, 1);
  CSSNodeStyleSetMargin(root_child0, CSSEdgeHorizontal, 10);
  CSSNodeStyleSetMargin(root_child0, CSSEdgeLeft, 20);
  CSSNodeInsertChild(root, root_child0, 0);

  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionLTR);
  ASSERT_EQ(20, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(10, CSSNodeLayoutGetRight(root_child0));

  CSSNodeFreeRecursive(root);
}

TEST(CSSLayoutTest, vertical_overridden) {
  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetFlexDirection(root, CSSFlexDirectionColumn);
  CSSNodeStyleSetWidth(root, 100);
  CSSNodeStyleSetHeight(root, 100);

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeStyleSetFlexGrow(root_child0, 1);
  CSSNodeStyleSetMargin(root_child0, CSSEdgeVertical, 10);
  CSSNodeStyleSetMargin(root_child0, CSSEdgeTop, 20);
  CSSNodeInsertChild(root, root_child0, 0);

  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionLTR);
  ASSERT_EQ(20, CSSNodeLayoutGetTop(root_child0));
  ASSERT_EQ(10, CSSNodeLayoutGetBottom(root_child0));

  CSSNodeFreeRecursive(root);
}

TEST(CSSLayoutTest, horizontal_overrides_all) {
  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetFlexDirection(root, CSSFlexDirectionColumn);
  CSSNodeStyleSetWidth(root, 100);
  CSSNodeStyleSetHeight(root, 100);

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeStyleSetFlexGrow(root_child0, 1);
  CSSNodeStyleSetMargin(root_child0, CSSEdgeHorizontal, 10);
  CSSNodeStyleSetMargin(root_child0, CSSEdgeAll, 20);
  CSSNodeInsertChild(root, root_child0, 0);

  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionLTR);
  ASSERT_EQ(10, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(20, CSSNodeLayoutGetTop(root_child0));
  ASSERT_EQ(10, CSSNodeLayoutGetRight(root_child0));
  ASSERT_EQ(20, CSSNodeLayoutGetBottom(root_child0));

  CSSNodeFreeRecursive(root);
}

TEST(CSSLayoutTest, vertical_overrides_all) {
  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetFlexDirection(root, CSSFlexDirectionColumn);
  CSSNodeStyleSetWidth(root, 100);
  CSSNodeStyleSetHeight(root, 100);

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeStyleSetFlexGrow(root_child0, 1);
  CSSNodeStyleSetMargin(root_child0, CSSEdgeVertical, 10);
  CSSNodeStyleSetMargin(root_child0, CSSEdgeAll, 20);
  CSSNodeInsertChild(root, root_child0, 0);

  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionLTR);
  ASSERT_EQ(20, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(10, CSSNodeLayoutGetTop(root_child0));
  ASSERT_EQ(20, CSSNodeLayoutGetRight(root_child0));
  ASSERT_EQ(10, CSSNodeLayoutGetBottom(root_child0));

  CSSNodeFreeRecursive(root);
}

TEST(CSSLayoutTest, all_overridden) {
  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetFlexDirection(root, CSSFlexDirectionColumn);
  CSSNodeStyleSetWidth(root, 100);
  CSSNodeStyleSetHeight(root, 100);

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeStyleSetFlexGrow(root_child0, 1);
  CSSNodeStyleSetMargin(root_child0, CSSEdgeLeft, 10);
  CSSNodeStyleSetMargin(root_child0, CSSEdgeTop, 10);
  CSSNodeStyleSetMargin(root_child0, CSSEdgeRight, 10);
  CSSNodeStyleSetMargin(root_child0, CSSEdgeBottom, 10);
  CSSNodeStyleSetMargin(root_child0, CSSEdgeAll, 20);
  CSSNodeInsertChild(root, root_child0, 0);

  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionLTR);
  ASSERT_EQ(10, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(10, CSSNodeLayoutGetTop(root_child0));
  ASSERT_EQ(10, CSSNodeLayoutGetRight(root_child0));
  ASSERT_EQ(10, CSSNodeLayoutGetBottom(root_child0));

  CSSNodeFreeRecursive(root);
}
