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

TEST(CSSLayoutTest, copy_style_same) {
  const CSSNodeRef node0 = CSSNodeNew();
  const CSSNodeRef node1 = CSSNodeNew();
  ASSERT_FALSE(CSSNodeIsDirty(node0));

  CSSNodeCopyStyle(node0, node1);
  ASSERT_FALSE(CSSNodeIsDirty(node0));

  CSSNodeFree(node0);
  CSSNodeFree(node1);
}

TEST(CSSLayoutTest, copy_style_modified) {
  const CSSNodeRef node0 = CSSNodeNew();
  ASSERT_FALSE(CSSNodeIsDirty(node0));
  ASSERT_EQ(CSSFlexDirectionColumn, CSSNodeStyleGetFlexDirection(node0));
  ASSERT_TRUE(CSSValueIsUndefined(CSSNodeStyleGetMaxHeight(node0)));

  const CSSNodeRef node1 = CSSNodeNew();
  CSSNodeStyleSetFlexDirection(node1, CSSFlexDirectionRow);
  CSSNodeStyleSetMaxHeight(node1, 10);

  CSSNodeCopyStyle(node0, node1);
  ASSERT_TRUE(CSSNodeIsDirty(node0));
  ASSERT_EQ(CSSFlexDirectionRow, CSSNodeStyleGetFlexDirection(node0));
  ASSERT_FLOAT_EQ(10, CSSNodeStyleGetMaxHeight(node0));

  CSSNodeFree(node0);
  CSSNodeFree(node1);
}

TEST(CSSLayoutTest, copy_style_modified_same) {
  const CSSNodeRef node0 = CSSNodeNew();
  CSSNodeStyleSetFlexDirection(node0, CSSFlexDirectionRow);
  CSSNodeStyleSetMaxHeight(node0, 10);
  CSSNodeCalculateLayout(node0, CSSUndefined, CSSUndefined, CSSDirectionLTR);
  ASSERT_FALSE(CSSNodeIsDirty(node0));

  const CSSNodeRef node1 = CSSNodeNew();
  CSSNodeStyleSetFlexDirection(node1, CSSFlexDirectionRow);
  CSSNodeStyleSetMaxHeight(node1, 10);

  CSSNodeCopyStyle(node0, node1);
  ASSERT_FALSE(CSSNodeIsDirty(node0));

  CSSNodeFree(node0);
  CSSNodeFree(node1);
}
