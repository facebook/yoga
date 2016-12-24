/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

(function() {
  const node0 = Yoga.nodeNew();
  const node1 = Yoga.nodeNew();
  ASSERT_FALSE(Yoga.nodeIsDirty(node0));

  Yoga.nodeCopyStyle(node0, node1);
  ASSERT_FALSE(Yoga.nodeIsDirty(node0));

  Yoga.nodeFree(node0);
  Yoga.nodeFree(node1);
})();

(function() {
  const node0 = Yoga.nodeNew();
  ASSERT_FALSE(Yoga.nodeIsDirty(node0));
  ASSERT_EQ(Yoga.FlexDirectionColumn, Yoga.nodeStyleGetFlexDirection(node0));
  ASSERT_TRUE(Yoga.valueIsUndefined(Yoga.nodeStyleGetMaxHeight(node0)));

  const node1 = Yoga.nodeNew();
  Yoga.nodeStyleSetFlexDirection(node1, Yoga.FlexDirectionRow);
  Yoga.nodeStyleSetMaxHeight(node1, 10);

  Yoga.nodeCopyStyle(node0, node1);
  ASSERT_TRUE(Yoga.nodeIsDirty(node0));
  ASSERT_EQ(Yoga.FlexDirectionRow, Yoga.nodeStyleGetFlexDirection(node0));
  ASSERT_FLOAT_EQ(10, Yoga.nodeStyleGetMaxHeight(node0));

  Yoga.nodeFree(node0);
  Yoga.nodeFree(node1);
})();

(function() {
  const node0 = Yoga.nodeNew();
  Yoga.nodeStyleSetFlexDirection(node0, Yoga.FlexDirectionRow);
  Yoga.nodeStyleSetMaxHeight(node0, 10);
  Yoga.nodeCalculateLayout(node0, Yoga.Undefined, Yoga.Undefined, Yoga.DirectionLTR);
  ASSERT_FALSE(Yoga.nodeIsDirty(node0));

  const node1 = Yoga.nodeNew();
  Yoga.nodeStyleSetFlexDirection(node1, Yoga.FlexDirectionRow);
  Yoga.nodeStyleSetMaxHeight(node1, 10);

  Yoga.nodeCopyStyle(node0, node1);
  ASSERT_FALSE(Yoga.nodeIsDirty(node0));

  Yoga.nodeFree(node0);
  Yoga.nodeFree(node1);
})();
