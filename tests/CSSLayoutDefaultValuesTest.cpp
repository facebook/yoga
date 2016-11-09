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

TEST(CSSLayoutTest, assert_default_values) {
  const CSSNodeRef root = CSSNodeNew();

  ASSERT_EQ(0, CSSNodeChildCount(root));
  ASSERT_EQ(NULL, CSSNodeGetChild(root, 1));

  ASSERT_EQ(CSSDirectionInherit, CSSNodeStyleGetDirection(root));
  ASSERT_EQ(CSSFlexDirectionColumn, CSSNodeStyleGetFlexDirection(root));
  ASSERT_EQ(CSSJustifyFlexStart, CSSNodeStyleGetJustifyContent(root));
  ASSERT_EQ(CSSAlignFlexStart, CSSNodeStyleGetAlignContent(root));
  ASSERT_EQ(CSSAlignStretch, CSSNodeStyleGetAlignItems(root));
  ASSERT_EQ(CSSAlignAuto, CSSNodeStyleGetAlignSelf(root));
  ASSERT_EQ(CSSPositionTypeRelative, CSSNodeStyleGetPositionType(root));
  ASSERT_EQ(CSSWrapTypeNoWrap, CSSNodeStyleGetFlexWrap(root));
  ASSERT_EQ(CSSOverflowVisible, CSSNodeStyleGetOverflow(root));
  ASSERT_EQ(0, CSSNodeStyleGetFlexGrow(root));
  ASSERT_EQ(0, CSSNodeStyleGetFlexShrink(root));
  ASSERT_TRUE(CSSValueIsUndefined(CSSNodeStyleGetFlexBasis(root)));

  ASSERT_TRUE(CSSValueIsUndefined(CSSNodeStyleGetPosition(root, CSSEdgeLeft)));
  ASSERT_TRUE(CSSValueIsUndefined(CSSNodeStyleGetPosition(root, CSSEdgeTop)));
  ASSERT_TRUE(CSSValueIsUndefined(CSSNodeStyleGetPosition(root, CSSEdgeRight)));
  ASSERT_TRUE(CSSValueIsUndefined(CSSNodeStyleGetPosition(root, CSSEdgeBottom)));
  ASSERT_TRUE(CSSValueIsUndefined(CSSNodeStyleGetPosition(root, CSSEdgeStart)));
  ASSERT_TRUE(CSSValueIsUndefined(CSSNodeStyleGetPosition(root, CSSEdgeEnd)));

  ASSERT_EQ(0, CSSNodeStyleGetMargin(root, CSSEdgeLeft));
  ASSERT_EQ(0, CSSNodeStyleGetMargin(root, CSSEdgeTop));
  ASSERT_EQ(0, CSSNodeStyleGetMargin(root, CSSEdgeRight));
  ASSERT_EQ(0, CSSNodeStyleGetMargin(root, CSSEdgeBottom));
  ASSERT_TRUE(CSSValueIsUndefined(CSSNodeStyleGetMargin(root, CSSEdgeStart)));
  ASSERT_TRUE(CSSValueIsUndefined(CSSNodeStyleGetMargin(root, CSSEdgeEnd)));

  ASSERT_EQ(0, CSSNodeStyleGetPadding(root, CSSEdgeLeft));
  ASSERT_EQ(0, CSSNodeStyleGetPadding(root, CSSEdgeTop));
  ASSERT_EQ(0, CSSNodeStyleGetPadding(root, CSSEdgeRight));
  ASSERT_EQ(0, CSSNodeStyleGetPadding(root, CSSEdgeBottom));
  ASSERT_TRUE(CSSValueIsUndefined(CSSNodeStyleGetPadding(root, CSSEdgeStart)));
  ASSERT_TRUE(CSSValueIsUndefined(CSSNodeStyleGetPadding(root, CSSEdgeEnd)));

  ASSERT_EQ(0, CSSNodeStyleGetBorder(root, CSSEdgeLeft));
  ASSERT_EQ(0, CSSNodeStyleGetBorder(root, CSSEdgeTop));
  ASSERT_EQ(0, CSSNodeStyleGetBorder(root, CSSEdgeRight));
  ASSERT_EQ(0, CSSNodeStyleGetBorder(root, CSSEdgeBottom));
  ASSERT_TRUE(CSSValueIsUndefined(CSSNodeStyleGetBorder(root, CSSEdgeStart)));
  ASSERT_TRUE(CSSValueIsUndefined(CSSNodeStyleGetBorder(root, CSSEdgeEnd)));

  ASSERT_TRUE(CSSValueIsUndefined(CSSNodeStyleGetWidth(root)));
  ASSERT_TRUE(CSSValueIsUndefined(CSSNodeStyleGetHeight(root)));
  ASSERT_TRUE(CSSValueIsUndefined(CSSNodeStyleGetMinWidth(root)));
  ASSERT_TRUE(CSSValueIsUndefined(CSSNodeStyleGetMinHeight(root)));
  ASSERT_TRUE(CSSValueIsUndefined(CSSNodeStyleGetMaxWidth(root)));
  ASSERT_TRUE(CSSValueIsUndefined(CSSNodeStyleGetMaxHeight(root)));

  ASSERT_EQ(0, CSSNodeLayoutGetLeft(root));
  ASSERT_EQ(0, CSSNodeLayoutGetTop(root));
  ASSERT_EQ(0, CSSNodeLayoutGetRight(root));
  ASSERT_EQ(0, CSSNodeLayoutGetBottom(root));
  ASSERT_TRUE(CSSValueIsUndefined(CSSNodeLayoutGetWidth(root)));
  ASSERT_TRUE(CSSValueIsUndefined(CSSNodeLayoutGetHeight(root)));
  ASSERT_EQ(CSSDirectionInherit, CSSNodeLayoutGetDirection(root));

  CSSNodeFreeRecursive(root);
}
