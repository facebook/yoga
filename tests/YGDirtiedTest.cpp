/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>
#include <yoga/Yoga.h>
#include <yoga/node/Node.h>

using namespace facebook;

static void _dirtied(YGNodeConstRef node) {
  int* dirtiedCount = (int*)YGNodeGetContext(node);
  (*dirtiedCount)++;
}

TEST(YogaTest, dirtied) {
  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetAlignItems(root, YGAlignFlexStart);
  YGNodeStyleSetWidth(root, 100);
  YGNodeStyleSetHeight(root, 100);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  int dirtiedCount = 0;
  YGNodeSetContext(root, &dirtiedCount);
  YGNodeSetDirtiedFunc(root, _dirtied);

  ASSERT_EQ(0, dirtiedCount);

  // `_dirtied` MUST be called in case of explicit dirtying.
  static_cast<yoga::Node*>(root)->setDirty(true);
  ASSERT_EQ(1, dirtiedCount);

  // `_dirtied` MUST be called ONCE.
  static_cast<yoga::Node*>(root)->setDirty(true);
  ASSERT_EQ(1, dirtiedCount);
}

TEST(YogaTest, dirtied_propagation) {
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

  int dirtiedCount = 0;
  YGNodeSetContext(root, &dirtiedCount);
  YGNodeSetDirtiedFunc(root, _dirtied);

  ASSERT_EQ(0, dirtiedCount);

  // `_dirtied` MUST be called for the first time.
  static_cast<yoga::Node*>(root_child0)->markDirtyAndPropagate();
  ASSERT_EQ(1, dirtiedCount);

  // `_dirtied` must NOT be called for the second time.
  static_cast<yoga::Node*>(root_child0)->markDirtyAndPropagate();
  ASSERT_EQ(1, dirtiedCount);
}

TEST(YogaTest, dirtied_hierarchy) {
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

  int dirtiedCount = 0;
  YGNodeSetContext(root_child0, &dirtiedCount);
  YGNodeSetDirtiedFunc(root_child0, _dirtied);

  ASSERT_EQ(0, dirtiedCount);

  // `_dirtied` must NOT be called for descendants.
  static_cast<yoga::Node*>(root)->markDirtyAndPropagate();
  ASSERT_EQ(0, dirtiedCount);

  // `_dirtied` must NOT be called for the sibling node.
  static_cast<yoga::Node*>(root_child1)->markDirtyAndPropagate();
  ASSERT_EQ(0, dirtiedCount);

  // `_dirtied` MUST be called in case of explicit dirtying.
  static_cast<yoga::Node*>(root_child0)->markDirtyAndPropagate();
  ASSERT_EQ(1, dirtiedCount);
}
