/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#include <gtest/gtest.h>
#include <yoga/Yoga.h>

TEST(YogaTest, assert_default_values) {
  const YGNodeRef root = YGNodeNew();

  ASSERT_EQ(0, YGNodeGetChildCount(root));
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
  ASSERT_FALSE(YGNodeStyleGetFlexBasis(root).unit != YGUnitUndefined);

  ASSERT_FALSE(YGNodeStyleGetPosition(root, YGEdgeLeft).unit != YGUnitUndefined);
  ASSERT_FALSE(YGNodeStyleGetPosition(root, YGEdgeTop).unit != YGUnitUndefined);
  ASSERT_FALSE(YGNodeStyleGetPosition(root, YGEdgeRight).unit != YGUnitUndefined);
  ASSERT_FALSE(YGNodeStyleGetPosition(root, YGEdgeBottom).unit != YGUnitUndefined);
  ASSERT_FALSE(YGNodeStyleGetPosition(root, YGEdgeStart).unit != YGUnitUndefined);
  ASSERT_FALSE(YGNodeStyleGetPosition(root, YGEdgeEnd).unit != YGUnitUndefined);

  ASSERT_FLOAT_EQ(0, YGNodeStyleGetMargin(root, YGEdgeLeft).value);
  ASSERT_FLOAT_EQ(0, YGNodeStyleGetMargin(root, YGEdgeTop).value);
  ASSERT_FLOAT_EQ(0, YGNodeStyleGetMargin(root, YGEdgeRight).value);
  ASSERT_FLOAT_EQ(0, YGNodeStyleGetMargin(root, YGEdgeBottom).value);
  ASSERT_FALSE(YGNodeStyleGetMargin(root, YGEdgeStart).unit != YGUnitUndefined);
  ASSERT_FALSE(YGNodeStyleGetMargin(root, YGEdgeEnd).unit != YGUnitUndefined);

  ASSERT_FLOAT_EQ(0, YGNodeStyleGetPadding(root, YGEdgeLeft).value);
  ASSERT_FLOAT_EQ(0, YGNodeStyleGetPadding(root, YGEdgeTop).value);
  ASSERT_FLOAT_EQ(0, YGNodeStyleGetPadding(root, YGEdgeRight).value);
  ASSERT_FLOAT_EQ(0, YGNodeStyleGetPadding(root, YGEdgeBottom).value);
  ASSERT_FALSE(YGNodeStyleGetPadding(root, YGEdgeStart).unit != YGUnitUndefined);
  ASSERT_FALSE(YGNodeStyleGetPadding(root, YGEdgeEnd).unit != YGUnitUndefined);

  ASSERT_FLOAT_EQ(0, YGNodeStyleGetBorder(root, YGEdgeLeft));
  ASSERT_FLOAT_EQ(0, YGNodeStyleGetBorder(root, YGEdgeTop));
  ASSERT_FLOAT_EQ(0, YGNodeStyleGetBorder(root, YGEdgeRight));
  ASSERT_FLOAT_EQ(0, YGNodeStyleGetBorder(root, YGEdgeBottom));
  ASSERT_TRUE(YGFloatIsUndefined(YGNodeStyleGetBorder(root, YGEdgeStart)));
  ASSERT_TRUE(YGFloatIsUndefined(YGNodeStyleGetBorder(root, YGEdgeEnd)));

  ASSERT_FALSE(YGNodeStyleGetWidth(root).unit != YGUnitUndefined);
  ASSERT_FALSE(YGNodeStyleGetHeight(root).unit != YGUnitUndefined);
  ASSERT_FALSE(YGNodeStyleGetMinWidth(root).unit != YGUnitUndefined);
  ASSERT_FALSE(YGNodeStyleGetMinHeight(root).unit != YGUnitUndefined);
  ASSERT_FALSE(YGNodeStyleGetMaxWidth(root).unit != YGUnitUndefined);
  ASSERT_FALSE(YGNodeStyleGetMaxHeight(root).unit != YGUnitUndefined);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetRight(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetBottom(root));
  ASSERT_TRUE(YGFloatIsUndefined(YGNodeLayoutGetWidth(root)));
  ASSERT_TRUE(YGFloatIsUndefined(YGNodeLayoutGetHeight(root)));
  ASSERT_EQ(YGDirectionInherit, YGNodeLayoutGetDirection(root));

  YGNodeFreeRecursive(root);
}
