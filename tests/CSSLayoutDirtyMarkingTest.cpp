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

TEST(CSSLayoutTest, dirty_propagation) {
  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetAlignItems(root, CSSAlignFlexStart);
  CSSNodeStyleSetWidth(root, 100);
  CSSNodeStyleSetHeight(root, 100);

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeStyleSetWidth(root_child0, 50);
  CSSNodeStyleSetHeight(root_child0, 20);
  CSSNodeInsertChild(root, root_child0, 0);

  const CSSNodeRef root_child1 = CSSNodeNew();
  CSSNodeStyleSetWidth(root_child1, 50);
  CSSNodeStyleSetHeight(root_child1, 20);
  CSSNodeInsertChild(root, root_child1, 1);

  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionLTR);

  CSSNodeStyleSetWidth(root_child0, 20);

  EXPECT_TRUE(CSSNodeIsDirty(root_child0));
  EXPECT_FALSE(CSSNodeIsDirty(root_child1));
  EXPECT_TRUE(CSSNodeIsDirty(root));

  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionLTR);

  EXPECT_FALSE(CSSNodeIsDirty(root_child0));
  EXPECT_FALSE(CSSNodeIsDirty(root_child1));
  EXPECT_FALSE(CSSNodeIsDirty(root));

  CSSNodeFreeRecursive(root);
}

TEST(CSSLayoutTest, dirty_propagation_only_if_prop_changed) {
  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetAlignItems(root, CSSAlignFlexStart);
  CSSNodeStyleSetWidth(root, 100);
  CSSNodeStyleSetHeight(root, 100);

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeStyleSetWidth(root_child0, 50);
  CSSNodeStyleSetHeight(root_child0, 20);
  CSSNodeInsertChild(root, root_child0, 0);

  const CSSNodeRef root_child1 = CSSNodeNew();
  CSSNodeStyleSetWidth(root_child1, 50);
  CSSNodeStyleSetHeight(root_child1, 20);
  CSSNodeInsertChild(root, root_child1, 1);

  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionLTR);

  CSSNodeStyleSetWidth(root_child0, 50);

  EXPECT_FALSE(CSSNodeIsDirty(root_child0));
  EXPECT_FALSE(CSSNodeIsDirty(root_child1));
  EXPECT_FALSE(CSSNodeIsDirty(root));

  CSSNodeFreeRecursive(root);
}
