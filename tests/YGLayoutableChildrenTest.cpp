/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>
#include <yoga/Yoga.h>
#include <yoga/node/Node.h>
#include <cstdio>

TEST(YogaTest, layoutable_children_single_contents_node) {
  YGNodeRef root = YGNodeNew();

  YGNodeRef root_child0 = YGNodeNew();
  YGNodeRef root_child1 = YGNodeNew();
  YGNodeRef root_child2 = YGNodeNew();

  YGNodeRef root_grandchild0 = YGNodeNew();
  YGNodeRef root_grandchild1 = YGNodeNew();

  YGNodeInsertChild(root, root_child0, 0);
  YGNodeInsertChild(root, root_child1, 1);
  YGNodeInsertChild(root, root_child2, 2);

  YGNodeInsertChild(root_child1, root_grandchild0, 0);
  YGNodeInsertChild(root_child1, root_grandchild1, 1);

  YGNodeStyleSetDisplay(root_child1, YGDisplayContents);

  std::vector<facebook::yoga::Node*> order = {
      facebook::yoga::resolveRef(root_child0),
      facebook::yoga::resolveRef(root_grandchild0),
      facebook::yoga::resolveRef(root_grandchild1),
      facebook::yoga::resolveRef(root_child2),
  };
  auto correctOrderIt = order.begin();

  for (auto node : facebook::yoga::resolveRef(root)->getLayoutChildren()) {
    ASSERT_EQ(node, *correctOrderIt);
    correctOrderIt++;
  }

  YGNodeFreeRecursive(root);
}

TEST(YogaTest, layoutable_children_multiple_contents_nodes) {
  YGNodeRef root = YGNodeNew();

  YGNodeRef root_child0 = YGNodeNew();
  YGNodeRef root_child1 = YGNodeNew();
  YGNodeRef root_child2 = YGNodeNew();

  YGNodeRef root_grandchild0 = YGNodeNew();
  YGNodeRef root_grandchild1 = YGNodeNew();
  YGNodeRef root_grandchild2 = YGNodeNew();
  YGNodeRef root_grandchild3 = YGNodeNew();
  YGNodeRef root_grandchild4 = YGNodeNew();
  YGNodeRef root_grandchild5 = YGNodeNew();

  YGNodeInsertChild(root, root_child0, 0);
  YGNodeInsertChild(root, root_child1, 1);
  YGNodeInsertChild(root, root_child2, 2);

  YGNodeInsertChild(root_child0, root_grandchild0, 0);
  YGNodeInsertChild(root_child0, root_grandchild1, 1);
  YGNodeInsertChild(root_child1, root_grandchild2, 0);
  YGNodeInsertChild(root_child1, root_grandchild3, 1);
  YGNodeInsertChild(root_child2, root_grandchild4, 0);
  YGNodeInsertChild(root_child2, root_grandchild5, 1);

  YGNodeStyleSetDisplay(root_child0, YGDisplayContents);
  YGNodeStyleSetDisplay(root_child1, YGDisplayContents);
  YGNodeStyleSetDisplay(root_child2, YGDisplayContents);

  std::vector<facebook::yoga::Node*> order = {
      facebook::yoga::resolveRef(root_grandchild0),
      facebook::yoga::resolveRef(root_grandchild1),
      facebook::yoga::resolveRef(root_grandchild2),
      facebook::yoga::resolveRef(root_grandchild3),
      facebook::yoga::resolveRef(root_grandchild4),
      facebook::yoga::resolveRef(root_grandchild5),
  };
  auto correctOrderIt = order.begin();

  for (auto node : facebook::yoga::resolveRef(root)->getLayoutChildren()) {
    ASSERT_EQ(node, *correctOrderIt);
    correctOrderIt++;
  }

  YGNodeFreeRecursive(root);
}

TEST(YogaTest, layoutable_children_nested_contents_nodes) {
  YGNodeRef root = YGNodeNew();

  YGNodeRef root_child0 = YGNodeNew();
  YGNodeRef root_child1 = YGNodeNew();
  YGNodeRef root_child2 = YGNodeNew();

  YGNodeRef root_grandchild0 = YGNodeNew();
  YGNodeRef root_grandchild1 = YGNodeNew();

  YGNodeRef root_great_grandchild0 = YGNodeNew();
  YGNodeRef root_great_grandchild1 = YGNodeNew();

  YGNodeInsertChild(root, root_child0, 0);
  YGNodeInsertChild(root, root_child1, 1);
  YGNodeInsertChild(root, root_child2, 2);

  YGNodeInsertChild(root_child1, root_grandchild0, 0);
  YGNodeInsertChild(root_child1, root_grandchild1, 1);

  YGNodeInsertChild(root_grandchild1, root_great_grandchild0, 0);
  YGNodeInsertChild(root_grandchild1, root_great_grandchild1, 1);

  YGNodeStyleSetDisplay(root_child1, YGDisplayContents);
  YGNodeStyleSetDisplay(root_grandchild1, YGDisplayContents);

  std::vector<facebook::yoga::Node*> order = {
      facebook::yoga::resolveRef(root_child0),
      facebook::yoga::resolveRef(root_grandchild0),
      facebook::yoga::resolveRef(root_great_grandchild0),
      facebook::yoga::resolveRef(root_great_grandchild1),
      facebook::yoga::resolveRef(root_child2),
  };
  auto correctOrderIt = order.begin();

  for (auto node : facebook::yoga::resolveRef(root)->getLayoutChildren()) {
    ASSERT_EQ(node, *correctOrderIt);
    correctOrderIt++;
  }

  YGNodeFreeRecursive(root);
}

TEST(YogaTest, layoutable_children_contents_leaf_node) {
  YGNodeRef root = YGNodeNew();

  YGNodeRef root_child0 = YGNodeNew();
  YGNodeRef root_child1 = YGNodeNew();
  YGNodeRef root_child2 = YGNodeNew();

  YGNodeInsertChild(root, root_child0, 0);
  YGNodeInsertChild(root, root_child1, 1);
  YGNodeInsertChild(root, root_child2, 2);

  YGNodeStyleSetDisplay(root_child1, YGDisplayContents);

  std::vector<facebook::yoga::Node*> order = {
      facebook::yoga::resolveRef(root_child0),
      facebook::yoga::resolveRef(root_child2),
  };
  auto correctOrderIt = order.begin();

  for (auto node : facebook::yoga::resolveRef(root)->getLayoutChildren()) {
    ASSERT_EQ(node, *correctOrderIt);
    correctOrderIt++;
  }

  YGNodeFreeRecursive(root);
}

TEST(YogaTest, layoutable_children_contents_root_node) {
  YGNodeRef root = YGNodeNew();

  YGNodeRef root_child0 = YGNodeNew();
  YGNodeRef root_child1 = YGNodeNew();
  YGNodeRef root_child2 = YGNodeNew();

  YGNodeInsertChild(root, root_child0, 0);
  YGNodeInsertChild(root, root_child1, 1);
  YGNodeInsertChild(root, root_child2, 2);

  YGNodeStyleSetDisplay(root, YGDisplayContents);

  std::vector<facebook::yoga::Node*> order = {
      facebook::yoga::resolveRef(root_child0),
      facebook::yoga::resolveRef(root_child1),
      facebook::yoga::resolveRef(root_child2),
  };
  auto correctOrderIt = order.begin();

  for (auto node : facebook::yoga::resolveRef(root)->getLayoutChildren()) {
    ASSERT_EQ(node, *correctOrderIt);
    correctOrderIt++;
  }

  YGNodeFreeRecursive(root);
}
