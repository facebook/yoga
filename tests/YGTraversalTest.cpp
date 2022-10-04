/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>
#include <yoga/Yoga.h>

TEST(YogaTest, pre_order_traversal) {
  YGNodeRef const root = YGNodeNew();
  YGNodeRef const root_child0 = YGNodeNew();
  YGNodeRef const root_child1 = YGNodeNew();
  YGNodeRef const root_child0_child0 = YGNodeNew();

  YGNodeSetChildren(root, {root_child0, root_child1});
  YGNodeInsertChild(root_child0, root_child0_child0, 0);

  std::vector<YGNodeRef> visited;
  YGTraversePreOrder(
      root, [&visited](YGNodeRef node) { visited.push_back(node); });

  const std::vector<YGNodeRef> expected = {
      root, root_child0, root_child0_child0, root_child1};
  ASSERT_EQ(visited, expected);

  YGNodeFreeRecursive(root);
}
