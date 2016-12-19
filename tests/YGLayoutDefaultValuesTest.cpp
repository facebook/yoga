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

TEST(YogaTest, assert_default_values) {
  const YGNodeRef root = YGNodeNew();

  ASSERT_EQ(0, YGNodeChildCount(root));
  ASSERT_EQ(NULL, YGNodeGetChild(root, 1));

  ASSERT_EQ(YGDirectionInherit, YGNodeStyleGetDirection(root));
  ASSERT_EQ(YGFlexDirectionColumn, YGNodeStyleGetFlexDirection(root));
  ASSERT_EQ(YGJustifyFlexStart, YGNodeStyleGetJustifyContent(root));
  ASSERT_EQ(YGAlignFlexStart, YGNodeStyleGetAlignContent(root));
  ASSERT_EQ(YGAlignStretch, YGNodeStyleGetAlignItems(root));
  ASSERT_EQ(YGAlignAuto, YGNodeStyleGetAlignSelf(root));
  ASSERT_EQ(YGPositionTypeRelative, YGNodeStyleGetPositionType(root));
  ASSERT_EQ(YGWrapNoWrap, YGNodeStyleGetFlexWrap(root));
  ASSERT_EQ(YGOverflowVisible, YGNodeStyleGetOverflow(root));
  ASSERT_FLOAT_EQ(0, YGNodeStyleGetFlexGrow(root));
  ASSERT_FLOAT_EQ(0, YGNodeStyleGetFlexShrink(root));
  ASSERT_FALSE(YGNodeStyleGetFlexBasis(root).defined);

  ASSERT_FALSE(YGNodeStyleGetPosition(root, YGEdgeLeft).defined);
  ASSERT_FALSE(YGNodeStyleGetPosition(root, YGEdgeTop).defined);
  ASSERT_FALSE(YGNodeStyleGetPosition(root, YGEdgeRight).defined);
  ASSERT_FALSE(YGNodeStyleGetPosition(root, YGEdgeBottom).defined);
  ASSERT_FALSE(YGNodeStyleGetPosition(root, YGEdgeStart).defined);
  ASSERT_FALSE(YGNodeStyleGetPosition(root, YGEdgeEnd).defined);

  ASSERT_FLOAT_EQ(0, YGNodeStyleGetMargin(root, YGEdgeLeft).value);
  ASSERT_FLOAT_EQ(0, YGNodeStyleGetMargin(root, YGEdgeTop).value);
  ASSERT_FLOAT_EQ(0, YGNodeStyleGetMargin(root, YGEdgeRight).value);
  ASSERT_FLOAT_EQ(0, YGNodeStyleGetMargin(root, YGEdgeBottom).value);
  ASSERT_FALSE(YGNodeStyleGetMargin(root, YGEdgeStart).defined);
  ASSERT_FALSE(YGNodeStyleGetMargin(root, YGEdgeEnd).defined);

  ASSERT_FLOAT_EQ(0, YGNodeStyleGetPadding(root, YGEdgeLeft).value);
  ASSERT_FLOAT_EQ(0, YGNodeStyleGetPadding(root, YGEdgeTop).value);
  ASSERT_FLOAT_EQ(0, YGNodeStyleGetPadding(root, YGEdgeRight).value);
  ASSERT_FLOAT_EQ(0, YGNodeStyleGetPadding(root, YGEdgeBottom).value);
  ASSERT_FALSE(YGNodeStyleGetPadding(root, YGEdgeStart).defined);
  ASSERT_FALSE(YGNodeStyleGetPadding(root, YGEdgeEnd).defined);

  ASSERT_FLOAT_EQ(0, YGNodeStyleGetBorder(root, YGEdgeLeft));
  ASSERT_FLOAT_EQ(0, YGNodeStyleGetBorder(root, YGEdgeTop));
  ASSERT_FLOAT_EQ(0, YGNodeStyleGetBorder(root, YGEdgeRight));
  ASSERT_FLOAT_EQ(0, YGNodeStyleGetBorder(root, YGEdgeBottom));
  ASSERT_TRUE(YGFloatIsUndefined(YGNodeStyleGetBorder(root, YGEdgeStart)));
  ASSERT_TRUE(YGFloatIsUndefined(YGNodeStyleGetBorder(root, YGEdgeEnd)));

  ASSERT_FALSE(YGNodeStyleGetWidth(root).defined);
  ASSERT_FALSE(YGNodeStyleGetHeight(root).defined);
  ASSERT_FALSE(YGNodeStyleGetMinWidth(root).defined);
  ASSERT_FALSE(YGNodeStyleGetMinHeight(root).defined);
  ASSERT_FALSE(YGNodeStyleGetMaxWidth(root).defined);
  ASSERT_FALSE(YGNodeStyleGetMaxHeight(root).defined);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetRight(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetBottom(root));
  ASSERT_TRUE(YGFloatIsUndefined(YGNodeLayoutGetWidth(root)));
  ASSERT_TRUE(YGFloatIsUndefined(YGNodeLayoutGetHeight(root)));
  ASSERT_EQ(YGDirectionInherit, YGNodeLayoutGetDirection(root));

  YGNodeFreeRecursive(root);
}
