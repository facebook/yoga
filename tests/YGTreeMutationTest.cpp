/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>
#include <yoga/Yoga.h>

static std::vector<YGNodeRef> getChildren(YGNodeRef const node) {
  const uint32_t count = YGNodeGetChildCount(node);
  std::vector<YGNodeRef> children;
  children.reserve(count);
  for (uint32_t i = 0; i < count; i++) {
    children.push_back(YGNodeGetChild(node, i));
  }
  return children;
}

TEST(YogaTest, set_children_adds_children_to_parent) {
  YGNodeRef const root = YGNodeNew();
  YGNodeRef const root_child0 = YGNodeNew();
  YGNodeRef const root_child1 = YGNodeNew();

  YGNodeSetChildren(root, {root_child0, root_child1});

  const std::vector<YGNodeRef> children = getChildren(root);
  const std::vector<YGNodeRef> expectedChildren = {root_child0, root_child1};
  ASSERT_EQ(children, expectedChildren);

  const std::vector<YGNodeRef> owners = {YGNodeGetOwner(root_child0),
                                         YGNodeGetOwner(root_child1)};
  const std::vector<YGNodeRef> expectedOwners = {root, root};
  ASSERT_EQ(owners, expectedOwners);

  YGNodeFreeRecursive(root);
}

TEST(YogaTest, set_children_to_empty_removes_old_children) {
  YGNodeRef const root = YGNodeNew();
  YGNodeRef const root_child0 = YGNodeNew();
  YGNodeRef const root_child1 = YGNodeNew();

  YGNodeSetChildren(root, {root_child0, root_child1});
  YGNodeSetChildren(root, {});

  const std::vector<YGNodeRef> children = getChildren(root);
  const std::vector<YGNodeRef> expectedChildren = {};
  ASSERT_EQ(children, expectedChildren);

  const std::vector<YGNodeRef> owners = {YGNodeGetOwner(root_child0),
                                         YGNodeGetOwner(root_child1)};
  const std::vector<YGNodeRef> expectedOwners = {nullptr, nullptr};
  ASSERT_EQ(owners, expectedOwners);

  YGNodeFreeRecursive(root);
}

TEST(YogaTest, set_children_replaces_non_common_children) {
  YGNodeRef const root = YGNodeNew();
  YGNodeRef const root_child0 = YGNodeNew();
  YGNodeRef const root_child1 = YGNodeNew();

  YGNodeSetChildren(root, {root_child0, root_child1});

  YGNodeRef const root_child2 = YGNodeNew();
  YGNodeRef const root_child3 = YGNodeNew();

  YGNodeSetChildren(root, {root_child2, root_child3});

  const std::vector<YGNodeRef> children = getChildren(root);
  const std::vector<YGNodeRef> expectedChildren = {root_child2, root_child3};
  ASSERT_EQ(children, expectedChildren);

  const std::vector<YGNodeRef> owners = {YGNodeGetOwner(root_child0),
                                         YGNodeGetOwner(root_child1)};
  const std::vector<YGNodeRef> expectedOwners = {nullptr, nullptr};
  ASSERT_EQ(owners, expectedOwners);

  YGNodeFreeRecursive(root);
  YGNodeFree(root_child0);
  YGNodeFree(root_child1);
}

TEST(YogaTest, set_children_keeps_and_reorders_common_children) {
  YGNodeRef const root = YGNodeNew();
  YGNodeRef const root_child0 = YGNodeNew();
  YGNodeRef const root_child1 = YGNodeNew();
  YGNodeRef const root_child2 = YGNodeNew();

  YGNodeSetChildren(root, {root_child0, root_child1, root_child2});

  YGNodeRef const root_child3 = YGNodeNew();

  YGNodeSetChildren(root, {root_child2, root_child1, root_child3});

  const std::vector<YGNodeRef> children = getChildren(root);
  const std::vector<YGNodeRef> expectedChildren = {
      root_child2, root_child1, root_child3};
  ASSERT_EQ(children, expectedChildren);

  const std::vector<YGNodeRef> owners = {YGNodeGetOwner(root_child0),
                                         YGNodeGetOwner(root_child1),
                                         YGNodeGetOwner(root_child2),
                                         YGNodeGetOwner(root_child3)};
  const std::vector<YGNodeRef> expectedOwners = {nullptr, root, root, root};
  ASSERT_EQ(owners, expectedOwners);

  YGNodeFreeRecursive(root);
  YGNodeFree(root_child0);
}
