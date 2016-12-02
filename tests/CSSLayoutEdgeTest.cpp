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
  CSSNodeStyleSetFlexDirection(root, YGFlexDirectionRow);
  CSSNodeStyleSetWidth(root, 100);
  CSSNodeStyleSetHeight(root, 100);

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeStyleSetFlexGrow(root_child0, 1);
  CSSNodeStyleSetMargin(root_child0, YGEdgeStart, 10);
  CSSNodeStyleSetMargin(root_child0, YGEdgeLeft, 20);
  CSSNodeStyleSetMargin(root_child0, YGEdgeRight, 20);
  CSSNodeInsertChild(root, root_child0, 0);

  CSSNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);
  ASSERT_FLOAT_EQ(10, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(20, CSSNodeLayoutGetRight(root_child0));

  CSSNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionRTL);
  ASSERT_FLOAT_EQ(20, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(10, CSSNodeLayoutGetRight(root_child0));

  CSSNodeFreeRecursive(root);
}

TEST(CSSLayoutTest, end_overrides) {
  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetFlexDirection(root, YGFlexDirectionRow);
  CSSNodeStyleSetWidth(root, 100);
  CSSNodeStyleSetHeight(root, 100);

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeStyleSetFlexGrow(root_child0, 1);
  CSSNodeStyleSetMargin(root_child0, YGEdgeEnd, 10);
  CSSNodeStyleSetMargin(root_child0, YGEdgeLeft, 20);
  CSSNodeStyleSetMargin(root_child0, YGEdgeRight, 20);
  CSSNodeInsertChild(root, root_child0, 0);

  CSSNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);
  ASSERT_FLOAT_EQ(20, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(10, CSSNodeLayoutGetRight(root_child0));

  CSSNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionRTL);
  ASSERT_FLOAT_EQ(10, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(20, CSSNodeLayoutGetRight(root_child0));

  CSSNodeFreeRecursive(root);
}

TEST(CSSLayoutTest, horizontal_overridden) {
  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetFlexDirection(root, YGFlexDirectionRow);
  CSSNodeStyleSetWidth(root, 100);
  CSSNodeStyleSetHeight(root, 100);

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeStyleSetFlexGrow(root_child0, 1);
  CSSNodeStyleSetMargin(root_child0, YGEdgeHorizontal, 10);
  CSSNodeStyleSetMargin(root_child0, YGEdgeLeft, 20);
  CSSNodeInsertChild(root, root_child0, 0);

  CSSNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);
  ASSERT_FLOAT_EQ(20, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(10, CSSNodeLayoutGetRight(root_child0));

  CSSNodeFreeRecursive(root);
}

TEST(CSSLayoutTest, vertical_overridden) {
  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetFlexDirection(root, YGFlexDirectionColumn);
  CSSNodeStyleSetWidth(root, 100);
  CSSNodeStyleSetHeight(root, 100);

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeStyleSetFlexGrow(root_child0, 1);
  CSSNodeStyleSetMargin(root_child0, YGEdgeVertical, 10);
  CSSNodeStyleSetMargin(root_child0, YGEdgeTop, 20);
  CSSNodeInsertChild(root, root_child0, 0);

  CSSNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);
  ASSERT_FLOAT_EQ(20, CSSNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(10, CSSNodeLayoutGetBottom(root_child0));

  CSSNodeFreeRecursive(root);
}

TEST(CSSLayoutTest, horizontal_overrides_all) {
  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetFlexDirection(root, YGFlexDirectionColumn);
  CSSNodeStyleSetWidth(root, 100);
  CSSNodeStyleSetHeight(root, 100);

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeStyleSetFlexGrow(root_child0, 1);
  CSSNodeStyleSetMargin(root_child0, YGEdgeHorizontal, 10);
  CSSNodeStyleSetMargin(root_child0, YGEdgeAll, 20);
  CSSNodeInsertChild(root, root_child0, 0);

  CSSNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);
  ASSERT_FLOAT_EQ(10, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(20, CSSNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(10, CSSNodeLayoutGetRight(root_child0));
  ASSERT_FLOAT_EQ(20, CSSNodeLayoutGetBottom(root_child0));

  CSSNodeFreeRecursive(root);
}

TEST(CSSLayoutTest, vertical_overrides_all) {
  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetFlexDirection(root, YGFlexDirectionColumn);
  CSSNodeStyleSetWidth(root, 100);
  CSSNodeStyleSetHeight(root, 100);

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeStyleSetFlexGrow(root_child0, 1);
  CSSNodeStyleSetMargin(root_child0, YGEdgeVertical, 10);
  CSSNodeStyleSetMargin(root_child0, YGEdgeAll, 20);
  CSSNodeInsertChild(root, root_child0, 0);

  CSSNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);
  ASSERT_FLOAT_EQ(20, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(10, CSSNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(20, CSSNodeLayoutGetRight(root_child0));
  ASSERT_FLOAT_EQ(10, CSSNodeLayoutGetBottom(root_child0));

  CSSNodeFreeRecursive(root);
}

TEST(CSSLayoutTest, all_overridden) {
  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetFlexDirection(root, YGFlexDirectionColumn);
  CSSNodeStyleSetWidth(root, 100);
  CSSNodeStyleSetHeight(root, 100);

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeStyleSetFlexGrow(root_child0, 1);
  CSSNodeStyleSetMargin(root_child0, YGEdgeLeft, 10);
  CSSNodeStyleSetMargin(root_child0, YGEdgeTop, 10);
  CSSNodeStyleSetMargin(root_child0, YGEdgeRight, 10);
  CSSNodeStyleSetMargin(root_child0, YGEdgeBottom, 10);
  CSSNodeStyleSetMargin(root_child0, YGEdgeAll, 20);
  CSSNodeInsertChild(root, root_child0, 0);

  CSSNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);
  ASSERT_FLOAT_EQ(10, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(10, CSSNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(10, CSSNodeLayoutGetRight(root_child0));
  ASSERT_FLOAT_EQ(10, CSSNodeLayoutGetBottom(root_child0));

  CSSNodeFreeRecursive(root);
}
