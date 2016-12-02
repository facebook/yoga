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

  ASSERT_EQ(YGDirectionInherit, CSSNodeStyleGetDirection(root));
  ASSERT_EQ(YGFlexDirectionColumn, CSSNodeStyleGetFlexDirection(root));
  ASSERT_EQ(YGJustifyFlexStart, CSSNodeStyleGetJustifyContent(root));
  ASSERT_EQ(YGAlignFlexStart, CSSNodeStyleGetAlignContent(root));
  ASSERT_EQ(YGAlignStretch, CSSNodeStyleGetAlignItems(root));
  ASSERT_EQ(YGAlignAuto, CSSNodeStyleGetAlignSelf(root));
  ASSERT_EQ(YGPositionTypeRelative, CSSNodeStyleGetPositionType(root));
  ASSERT_EQ(YGWrapNoWrap, CSSNodeStyleGetFlexWrap(root));
  ASSERT_EQ(YGOverflowVisible, CSSNodeStyleGetOverflow(root));
  ASSERT_FLOAT_EQ(0, CSSNodeStyleGetFlexGrow(root));
  ASSERT_FLOAT_EQ(0, CSSNodeStyleGetFlexShrink(root));
  ASSERT_TRUE(CSSValueIsUndefined(CSSNodeStyleGetFlexBasis(root)));

  ASSERT_TRUE(CSSValueIsUndefined(CSSNodeStyleGetPosition(root, YGEdgeLeft)));
  ASSERT_TRUE(CSSValueIsUndefined(CSSNodeStyleGetPosition(root, YGEdgeTop)));
  ASSERT_TRUE(CSSValueIsUndefined(CSSNodeStyleGetPosition(root, YGEdgeRight)));
  ASSERT_TRUE(CSSValueIsUndefined(CSSNodeStyleGetPosition(root, YGEdgeBottom)));
  ASSERT_TRUE(CSSValueIsUndefined(CSSNodeStyleGetPosition(root, YGEdgeStart)));
  ASSERT_TRUE(CSSValueIsUndefined(CSSNodeStyleGetPosition(root, YGEdgeEnd)));

  ASSERT_FLOAT_EQ(0, CSSNodeStyleGetMargin(root, YGEdgeLeft));
  ASSERT_FLOAT_EQ(0, CSSNodeStyleGetMargin(root, YGEdgeTop));
  ASSERT_FLOAT_EQ(0, CSSNodeStyleGetMargin(root, YGEdgeRight));
  ASSERT_FLOAT_EQ(0, CSSNodeStyleGetMargin(root, YGEdgeBottom));
  ASSERT_TRUE(CSSValueIsUndefined(CSSNodeStyleGetMargin(root, YGEdgeStart)));
  ASSERT_TRUE(CSSValueIsUndefined(CSSNodeStyleGetMargin(root, YGEdgeEnd)));

  ASSERT_FLOAT_EQ(0, CSSNodeStyleGetPadding(root, YGEdgeLeft));
  ASSERT_FLOAT_EQ(0, CSSNodeStyleGetPadding(root, YGEdgeTop));
  ASSERT_FLOAT_EQ(0, CSSNodeStyleGetPadding(root, YGEdgeRight));
  ASSERT_FLOAT_EQ(0, CSSNodeStyleGetPadding(root, YGEdgeBottom));
  ASSERT_TRUE(CSSValueIsUndefined(CSSNodeStyleGetPadding(root, YGEdgeStart)));
  ASSERT_TRUE(CSSValueIsUndefined(CSSNodeStyleGetPadding(root, YGEdgeEnd)));

  ASSERT_FLOAT_EQ(0, CSSNodeStyleGetBorder(root, YGEdgeLeft));
  ASSERT_FLOAT_EQ(0, CSSNodeStyleGetBorder(root, YGEdgeTop));
  ASSERT_FLOAT_EQ(0, CSSNodeStyleGetBorder(root, YGEdgeRight));
  ASSERT_FLOAT_EQ(0, CSSNodeStyleGetBorder(root, YGEdgeBottom));
  ASSERT_TRUE(CSSValueIsUndefined(CSSNodeStyleGetBorder(root, YGEdgeStart)));
  ASSERT_TRUE(CSSValueIsUndefined(CSSNodeStyleGetBorder(root, YGEdgeEnd)));

  ASSERT_TRUE(CSSValueIsUndefined(CSSNodeStyleGetWidth(root)));
  ASSERT_TRUE(CSSValueIsUndefined(CSSNodeStyleGetHeight(root)));
  ASSERT_TRUE(CSSValueIsUndefined(CSSNodeStyleGetMinWidth(root)));
  ASSERT_TRUE(CSSValueIsUndefined(CSSNodeStyleGetMinHeight(root)));
  ASSERT_TRUE(CSSValueIsUndefined(CSSNodeStyleGetMaxWidth(root)));
  ASSERT_TRUE(CSSValueIsUndefined(CSSNodeStyleGetMaxHeight(root)));

  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetRight(root));
  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetBottom(root));
  ASSERT_TRUE(CSSValueIsUndefined(CSSNodeLayoutGetWidth(root)));
  ASSERT_TRUE(CSSValueIsUndefined(CSSNodeLayoutGetHeight(root)));
  ASSERT_EQ(YGDirectionInherit, CSSNodeLayoutGetDirection(root));

  CSSNodeFreeRecursive(root);
}
