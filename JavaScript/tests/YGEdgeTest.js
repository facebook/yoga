/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

(function() {
  const root = Yoga.nodeNew();
  Yoga.nodeStyleSetFlexDirection(root, Yoga.FlexDirectionRow);
  Yoga.nodeStyleSetWidth(root, 100);
  Yoga.nodeStyleSetHeight(root, 100);

  const root_child0 = Yoga.nodeNew();
  Yoga.nodeStyleSetFlexGrow(root_child0, 1);
  Yoga.nodeStyleSetMargin(root_child0, Yoga.EdgeStart, 10);
  Yoga.nodeStyleSetMargin(root_child0, Yoga.EdgeLeft, 20);
  Yoga.nodeStyleSetMargin(root_child0, Yoga.EdgeRight, 20);
  Yoga.nodeInsertChild(root, root_child0, 0);

  Yoga.nodeCalculateLayout(root, Yoga.Undefined, Yoga.Undefined, Yoga.DirectionLTR);
  ASSERT_FLOAT_EQ(10, Yoga.nodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(20, Yoga.nodeLayoutGetRight(root_child0));

  Yoga.nodeCalculateLayout(root, Yoga.Undefined, Yoga.Undefined, Yoga.DirectionRTL);
  ASSERT_FLOAT_EQ(20, Yoga.nodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(10, Yoga.nodeLayoutGetRight(root_child0));

  Yoga.nodeFreeRecursive(root);
})();

(function() {
  const root = Yoga.nodeNew();
  Yoga.nodeStyleSetFlexDirection(root, Yoga.FlexDirectionRow);
  Yoga.nodeStyleSetWidth(root, 100);
  Yoga.nodeStyleSetHeight(root, 100);

  const root_child0 = Yoga.nodeNew();
  Yoga.nodeStyleSetFlexGrow(root_child0, 1);
  Yoga.nodeStyleSetMargin(root_child0, Yoga.EdgeEnd, 10);
  Yoga.nodeStyleSetMargin(root_child0, Yoga.EdgeLeft, 20);
  Yoga.nodeStyleSetMargin(root_child0, Yoga.EdgeRight, 20);
  Yoga.nodeInsertChild(root, root_child0, 0);

  Yoga.nodeCalculateLayout(root, Yoga.Undefined, Yoga.Undefined, Yoga.DirectionLTR);
  ASSERT_FLOAT_EQ(20, Yoga.nodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(10, Yoga.nodeLayoutGetRight(root_child0));

  Yoga.nodeCalculateLayout(root, Yoga.Undefined, Yoga.Undefined, Yoga.DirectionRTL);
  ASSERT_FLOAT_EQ(10, Yoga.nodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(20, Yoga.nodeLayoutGetRight(root_child0));

  Yoga.nodeFreeRecursive(root);
})();

(function() {
  const root = Yoga.nodeNew();
  Yoga.nodeStyleSetFlexDirection(root, Yoga.FlexDirectionRow);
  Yoga.nodeStyleSetWidth(root, 100);
  Yoga.nodeStyleSetHeight(root, 100);

  const root_child0 = Yoga.nodeNew();
  Yoga.nodeStyleSetFlexGrow(root_child0, 1);
  Yoga.nodeStyleSetMargin(root_child0, Yoga.EdgeHorizontal, 10);
  Yoga.nodeStyleSetMargin(root_child0, Yoga.EdgeLeft, 20);
  Yoga.nodeInsertChild(root, root_child0, 0);

  Yoga.nodeCalculateLayout(root, Yoga.Undefined, Yoga.Undefined, Yoga.DirectionLTR);
  ASSERT_FLOAT_EQ(20, Yoga.nodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(10, Yoga.nodeLayoutGetRight(root_child0));

  Yoga.nodeFreeRecursive(root);
})();

(function() {
  const root = Yoga.nodeNew();
  Yoga.nodeStyleSetFlexDirection(root, Yoga.FlexDirectionColumn);
  Yoga.nodeStyleSetWidth(root, 100);
  Yoga.nodeStyleSetHeight(root, 100);

  const root_child0 = Yoga.nodeNew();
  Yoga.nodeStyleSetFlexGrow(root_child0, 1);
  Yoga.nodeStyleSetMargin(root_child0, Yoga.EdgeVertical, 10);
  Yoga.nodeStyleSetMargin(root_child0, Yoga.EdgeTop, 20);
  Yoga.nodeInsertChild(root, root_child0, 0);

  Yoga.nodeCalculateLayout(root, Yoga.Undefined, Yoga.Undefined, Yoga.DirectionLTR);
  ASSERT_FLOAT_EQ(20, Yoga.nodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(10, Yoga.nodeLayoutGetBottom(root_child0));

  Yoga.nodeFreeRecursive(root);
})();

(function() {
  const root = Yoga.nodeNew();
  Yoga.nodeStyleSetFlexDirection(root, Yoga.FlexDirectionColumn);
  Yoga.nodeStyleSetWidth(root, 100);
  Yoga.nodeStyleSetHeight(root, 100);

  const root_child0 = Yoga.nodeNew();
  Yoga.nodeStyleSetFlexGrow(root_child0, 1);
  Yoga.nodeStyleSetMargin(root_child0, Yoga.EdgeHorizontal, 10);
  Yoga.nodeStyleSetMargin(root_child0, Yoga.EdgeAll, 20);
  Yoga.nodeInsertChild(root, root_child0, 0);

  Yoga.nodeCalculateLayout(root, Yoga.Undefined, Yoga.Undefined, Yoga.DirectionLTR);
  ASSERT_FLOAT_EQ(10, Yoga.nodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(20, Yoga.nodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(10, Yoga.nodeLayoutGetRight(root_child0));
  ASSERT_FLOAT_EQ(20, Yoga.nodeLayoutGetBottom(root_child0));

  Yoga.nodeFreeRecursive(root);
})();

(function() {
  const root = Yoga.nodeNew();
  Yoga.nodeStyleSetFlexDirection(root, Yoga.FlexDirectionColumn);
  Yoga.nodeStyleSetWidth(root, 100);
  Yoga.nodeStyleSetHeight(root, 100);

  const root_child0 = Yoga.nodeNew();
  Yoga.nodeStyleSetFlexGrow(root_child0, 1);
  Yoga.nodeStyleSetMargin(root_child0, Yoga.EdgeVertical, 10);
  Yoga.nodeStyleSetMargin(root_child0, Yoga.EdgeAll, 20);
  Yoga.nodeInsertChild(root, root_child0, 0);

  Yoga.nodeCalculateLayout(root, Yoga.Undefined, Yoga.Undefined, Yoga.DirectionLTR);
  ASSERT_FLOAT_EQ(20, Yoga.nodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(10, Yoga.nodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(20, Yoga.nodeLayoutGetRight(root_child0));
  ASSERT_FLOAT_EQ(10, Yoga.nodeLayoutGetBottom(root_child0));

  Yoga.nodeFreeRecursive(root);
})();

(function() {
  const root = Yoga.nodeNew();
  Yoga.nodeStyleSetFlexDirection(root, Yoga.FlexDirectionColumn);
  Yoga.nodeStyleSetWidth(root, 100);
  Yoga.nodeStyleSetHeight(root, 100);

  const root_child0 = Yoga.nodeNew();
  Yoga.nodeStyleSetFlexGrow(root_child0, 1);
  Yoga.nodeStyleSetMargin(root_child0, Yoga.EdgeLeft, 10);
  Yoga.nodeStyleSetMargin(root_child0, Yoga.EdgeTop, 10);
  Yoga.nodeStyleSetMargin(root_child0, Yoga.EdgeRight, 10);
  Yoga.nodeStyleSetMargin(root_child0, Yoga.EdgeBottom, 10);
  Yoga.nodeStyleSetMargin(root_child0, Yoga.EdgeAll, 20);
  Yoga.nodeInsertChild(root, root_child0, 0);

  Yoga.nodeCalculateLayout(root, Yoga.Undefined, Yoga.Undefined, Yoga.DirectionLTR);
  ASSERT_FLOAT_EQ(10, Yoga.nodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(10, Yoga.nodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(10, Yoga.nodeLayoutGetRight(root_child0));
  ASSERT_FLOAT_EQ(10, Yoga.nodeLayoutGetBottom(root_child0));

  Yoga.nodeFreeRecursive(root);
})();
