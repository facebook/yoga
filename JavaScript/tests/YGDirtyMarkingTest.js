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
  Yoga.nodeStyleSetAlignItems(root, Yoga.AlignFlexStart);
  Yoga.nodeStyleSetWidth(root, 100);
  Yoga.nodeStyleSetHeight(root, 100);

  const root_child0 = Yoga.nodeNew();
  Yoga.nodeStyleSetWidth(root_child0, 50);
  Yoga.nodeStyleSetHeight(root_child0, 20);
  Yoga.nodeInsertChild(root, root_child0, 0);

  const root_child1 = Yoga.nodeNew();
  Yoga.nodeStyleSetWidth(root_child1, 50);
  Yoga.nodeStyleSetHeight(root_child1, 20);
  Yoga.nodeInsertChild(root, root_child1, 1);

  Yoga.nodeCalculateLayout(root, Yoga.Undefined, Yoga.Undefined, Yoga.DirectionLTR);

  Yoga.nodeStyleSetWidth(root_child0, 20);

  EXPECT_TRUE(Yoga.nodeIsDirty(root_child0));
  EXPECT_FALSE(Yoga.nodeIsDirty(root_child1));
  EXPECT_TRUE(Yoga.nodeIsDirty(root));

  Yoga.nodeCalculateLayout(root, Yoga.Undefined, Yoga.Undefined, Yoga.DirectionLTR);

  EXPECT_FALSE(Yoga.nodeIsDirty(root_child0));
  EXPECT_FALSE(Yoga.nodeIsDirty(root_child1));
  EXPECT_FALSE(Yoga.nodeIsDirty(root));

  Yoga.nodeFreeRecursive(root);
})();

(function() {
  const root = Yoga.nodeNew();
  Yoga.nodeStyleSetAlignItems(root, Yoga.AlignFlexStart);
  Yoga.nodeStyleSetWidth(root, 100);
  Yoga.nodeStyleSetHeight(root, 100);

  const root_child0 = Yoga.nodeNew();
  Yoga.nodeStyleSetWidth(root_child0, 50);
  Yoga.nodeStyleSetHeight(root_child0, 20);
  Yoga.nodeInsertChild(root, root_child0, 0);

  const root_child1 = Yoga.nodeNew();
  Yoga.nodeStyleSetWidth(root_child1, 50);
  Yoga.nodeStyleSetHeight(root_child1, 20);
  Yoga.nodeInsertChild(root, root_child1, 1);

  Yoga.nodeCalculateLayout(root, Yoga.Undefined, Yoga.Undefined, Yoga.DirectionLTR);

  Yoga.nodeStyleSetWidth(root_child0, 50);

  EXPECT_FALSE(Yoga.nodeIsDirty(root_child0));
  EXPECT_FALSE(Yoga.nodeIsDirty(root_child1));
  EXPECT_FALSE(Yoga.nodeIsDirty(root));

  Yoga.nodeFreeRecursive(root);
})();

(function() {
  const root = Yoga.nodeNew();
  Yoga.nodeStyleSetAlignItems(root, Yoga.AlignFlexStart);
  Yoga.nodeStyleSetWidth(root, 50);
  Yoga.nodeStyleSetHeight(root, 50);

  const child0 = Yoga.nodeNew();
  Yoga.nodeStyleSetWidth(child0, 50);
  Yoga.nodeStyleSetHeight(child0, 25);
  Yoga.nodeInsertChild(root, child0, 0);

  Yoga.nodeCalculateLayout(root, Yoga.Undefined, Yoga.Undefined, Yoga.DirectionLTR);

  const child1 = Yoga.nodeNew();
  Yoga.nodeRemoveChild(root, child1);
  EXPECT_FALSE(Yoga.nodeIsDirty(root));
  Yoga.nodeFree(child1);

  Yoga.nodeRemoveChild(root, child0);
  EXPECT_TRUE(Yoga.nodeIsDirty(root));
  Yoga.nodeFree(child0);

  Yoga.nodeFreeRecursive(root);
})();
