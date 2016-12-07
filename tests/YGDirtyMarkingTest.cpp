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

TEST(YogaTest, dirty_propagation) {
  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetAlignItems(root, YGAlignFlexStart);
  YGNodeStyleSetWidth(root, 100);
  YGNodeStyleSetHeight(root, 100);

  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeStyleSetWidth(root_child0, 50);
  YGNodeStyleSetHeight(root_child0, 20);
  YGNodeInsertChild(root, root_child0, 0);

  const YGNodeRef root_child1 = YGNodeNew();
  YGNodeStyleSetWidth(root_child1, 50);
  YGNodeStyleSetHeight(root_child1, 20);
  YGNodeInsertChild(root, root_child1, 1);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  YGNodeStyleSetWidth(root_child0, 20);

  EXPECT_TRUE(YGNodeIsDirty(root_child0));
  EXPECT_FALSE(YGNodeIsDirty(root_child1));
  EXPECT_TRUE(YGNodeIsDirty(root));

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  EXPECT_FALSE(YGNodeIsDirty(root_child0));
  EXPECT_FALSE(YGNodeIsDirty(root_child1));
  EXPECT_FALSE(YGNodeIsDirty(root));

  YGNodeFreeRecursive(root);
}

TEST(YogaTest, dirty_propagation_only_if_prop_changed) {
  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetAlignItems(root, YGAlignFlexStart);
  YGNodeStyleSetWidth(root, 100);
  YGNodeStyleSetHeight(root, 100);

  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeStyleSetWidth(root_child0, 50);
  YGNodeStyleSetHeight(root_child0, 20);
  YGNodeInsertChild(root, root_child0, 0);

  const YGNodeRef root_child1 = YGNodeNew();
  YGNodeStyleSetWidth(root_child1, 50);
  YGNodeStyleSetHeight(root_child1, 20);
  YGNodeInsertChild(root, root_child1, 1);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  YGNodeStyleSetWidth(root_child0, 50);

  EXPECT_FALSE(YGNodeIsDirty(root_child0));
  EXPECT_FALSE(YGNodeIsDirty(root_child1));
  EXPECT_FALSE(YGNodeIsDirty(root));

  YGNodeFreeRecursive(root);
}

TEST(YogaTest, dirty_node_only_if_children_are_actually_removed) {
  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetAlignItems(root, YGAlignFlexStart);
  YGNodeStyleSetWidth(root, 50);
  YGNodeStyleSetHeight(root, 50);

  const YGNodeRef child0 = YGNodeNew();
  YGNodeStyleSetWidth(child0, 50);
  YGNodeStyleSetHeight(child0, 25);
  YGNodeInsertChild(root, child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  const YGNodeRef child1 = YGNodeNew();
  YGNodeRemoveChild(root, child1);
  EXPECT_FALSE(YGNodeIsDirty(root));
  YGNodeFree(child1);

  YGNodeRemoveChild(root, child0);
  EXPECT_TRUE(YGNodeIsDirty(root));
  YGNodeFree(child0);

  YGNodeFreeRecursive(root);
}
