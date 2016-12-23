/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

(function() {
  const root = _YGNodeNew();
  _YGNodeStyleSetFlexDirection(root, _YGFlexDirectionRow);
  _YGNodeStyleSetWidth(root, 100);
  _YGNodeStyleSetHeight(root, 100);

  const root_child0 = _YGNodeNew();
  _YGNodeStyleSetFlexGrow(root_child0, 1);
  _YGNodeStyleSetMargin(root_child0, _YGEdgeStart, 10);
  _YGNodeStyleSetMargin(root_child0, _YGEdgeLeft, 20);
  _YGNodeStyleSetMargin(root_child0, _YGEdgeRight, 20);
  _YGNodeInsertChild(root, root_child0, 0);

  _YGNodeCalculateLayout(root, _YGUndefined, _YGUndefined, _YGDirectionLTR);
  ASSERT_FLOAT_EQ(10, _YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(20, _YGNodeLayoutGetRight(root_child0));

  _YGNodeCalculateLayout(root, _YGUndefined, _YGUndefined, _YGDirectionRTL);
  ASSERT_FLOAT_EQ(20, _YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(10, _YGNodeLayoutGetRight(root_child0));

  _YGNodeFreeRecursive(root);
})();

(function() {
  const root = _YGNodeNew();
  _YGNodeStyleSetFlexDirection(root, _YGFlexDirectionRow);
  _YGNodeStyleSetWidth(root, 100);
  _YGNodeStyleSetHeight(root, 100);

  const root_child0 = _YGNodeNew();
  _YGNodeStyleSetFlexGrow(root_child0, 1);
  _YGNodeStyleSetMargin(root_child0, _YGEdgeEnd, 10);
  _YGNodeStyleSetMargin(root_child0, _YGEdgeLeft, 20);
  _YGNodeStyleSetMargin(root_child0, _YGEdgeRight, 20);
  _YGNodeInsertChild(root, root_child0, 0);

  _YGNodeCalculateLayout(root, _YGUndefined, _YGUndefined, _YGDirectionLTR);
  ASSERT_FLOAT_EQ(20, _YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(10, _YGNodeLayoutGetRight(root_child0));

  _YGNodeCalculateLayout(root, _YGUndefined, _YGUndefined, _YGDirectionRTL);
  ASSERT_FLOAT_EQ(10, _YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(20, _YGNodeLayoutGetRight(root_child0));

  _YGNodeFreeRecursive(root);
})();

(function() {
  const root = _YGNodeNew();
  _YGNodeStyleSetFlexDirection(root, _YGFlexDirectionRow);
  _YGNodeStyleSetWidth(root, 100);
  _YGNodeStyleSetHeight(root, 100);

  const root_child0 = _YGNodeNew();
  _YGNodeStyleSetFlexGrow(root_child0, 1);
  _YGNodeStyleSetMargin(root_child0, _YGEdgeHorizontal, 10);
  _YGNodeStyleSetMargin(root_child0, _YGEdgeLeft, 20);
  _YGNodeInsertChild(root, root_child0, 0);

  _YGNodeCalculateLayout(root, _YGUndefined, _YGUndefined, _YGDirectionLTR);
  ASSERT_FLOAT_EQ(20, _YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(10, _YGNodeLayoutGetRight(root_child0));

  _YGNodeFreeRecursive(root);
})();

(function() {
  const root = _YGNodeNew();
  _YGNodeStyleSetFlexDirection(root, _YGFlexDirectionColumn);
  _YGNodeStyleSetWidth(root, 100);
  _YGNodeStyleSetHeight(root, 100);

  const root_child0 = _YGNodeNew();
  _YGNodeStyleSetFlexGrow(root_child0, 1);
  _YGNodeStyleSetMargin(root_child0, _YGEdgeVertical, 10);
  _YGNodeStyleSetMargin(root_child0, _YGEdgeTop, 20);
  _YGNodeInsertChild(root, root_child0, 0);

  _YGNodeCalculateLayout(root, _YGUndefined, _YGUndefined, _YGDirectionLTR);
  ASSERT_FLOAT_EQ(20, _YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(10, _YGNodeLayoutGetBottom(root_child0));

  _YGNodeFreeRecursive(root);
})();

(function() {
  const root = _YGNodeNew();
  _YGNodeStyleSetFlexDirection(root, _YGFlexDirectionColumn);
  _YGNodeStyleSetWidth(root, 100);
  _YGNodeStyleSetHeight(root, 100);

  const root_child0 = _YGNodeNew();
  _YGNodeStyleSetFlexGrow(root_child0, 1);
  _YGNodeStyleSetMargin(root_child0, _YGEdgeHorizontal, 10);
  _YGNodeStyleSetMargin(root_child0, _YGEdgeAll, 20);
  _YGNodeInsertChild(root, root_child0, 0);

  _YGNodeCalculateLayout(root, _YGUndefined, _YGUndefined, _YGDirectionLTR);
  ASSERT_FLOAT_EQ(10, _YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(20, _YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(10, _YGNodeLayoutGetRight(root_child0));
  ASSERT_FLOAT_EQ(20, _YGNodeLayoutGetBottom(root_child0));

  _YGNodeFreeRecursive(root);
})();

(function() {
  const root = _YGNodeNew();
  _YGNodeStyleSetFlexDirection(root, _YGFlexDirectionColumn);
  _YGNodeStyleSetWidth(root, 100);
  _YGNodeStyleSetHeight(root, 100);

  const root_child0 = _YGNodeNew();
  _YGNodeStyleSetFlexGrow(root_child0, 1);
  _YGNodeStyleSetMargin(root_child0, _YGEdgeVertical, 10);
  _YGNodeStyleSetMargin(root_child0, _YGEdgeAll, 20);
  _YGNodeInsertChild(root, root_child0, 0);

  _YGNodeCalculateLayout(root, _YGUndefined, _YGUndefined, _YGDirectionLTR);
  ASSERT_FLOAT_EQ(20, _YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(10, _YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(20, _YGNodeLayoutGetRight(root_child0));
  ASSERT_FLOAT_EQ(10, _YGNodeLayoutGetBottom(root_child0));

  _YGNodeFreeRecursive(root);
})();

(function() {
  const root = _YGNodeNew();
  _YGNodeStyleSetFlexDirection(root, _YGFlexDirectionColumn);
  _YGNodeStyleSetWidth(root, 100);
  _YGNodeStyleSetHeight(root, 100);

  const root_child0 = _YGNodeNew();
  _YGNodeStyleSetFlexGrow(root_child0, 1);
  _YGNodeStyleSetMargin(root_child0, _YGEdgeLeft, 10);
  _YGNodeStyleSetMargin(root_child0, _YGEdgeTop, 10);
  _YGNodeStyleSetMargin(root_child0, _YGEdgeRight, 10);
  _YGNodeStyleSetMargin(root_child0, _YGEdgeBottom, 10);
  _YGNodeStyleSetMargin(root_child0, _YGEdgeAll, 20);
  _YGNodeInsertChild(root, root_child0, 0);

  _YGNodeCalculateLayout(root, _YGUndefined, _YGUndefined, _YGDirectionLTR);
  ASSERT_FLOAT_EQ(10, _YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(10, _YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(10, _YGNodeLayoutGetRight(root_child0));
  ASSERT_FLOAT_EQ(10, _YGNodeLayoutGetBottom(root_child0));

  _YGNodeFreeRecursive(root);
})();
