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
  ASSERT_EQ(YGNodeStyleGetFlexBasis(root).unit, YGUnitAuto);

  ASSERT_EQ(YGNodeStyleGetPosition(root, YGEdgeLeft).unit, YGUnitUndefined);
  ASSERT_EQ(YGNodeStyleGetPosition(root, YGEdgeTop).unit, YGUnitUndefined);
  ASSERT_EQ(YGNodeStyleGetPosition(root, YGEdgeRight).unit, YGUnitUndefined);
  ASSERT_EQ(YGNodeStyleGetPosition(root, YGEdgeBottom).unit, YGUnitUndefined);
  ASSERT_EQ(YGNodeStyleGetPosition(root, YGEdgeStart).unit, YGUnitUndefined);
  ASSERT_EQ(YGNodeStyleGetPosition(root, YGEdgeEnd).unit, YGUnitUndefined);

  ASSERT_EQ(YGNodeStyleGetMargin(root, YGEdgeLeft).unit, YGUnitUndefined);
  ASSERT_EQ(YGNodeStyleGetMargin(root, YGEdgeTop).unit, YGUnitUndefined);
  ASSERT_EQ(YGNodeStyleGetMargin(root, YGEdgeRight).unit, YGUnitUndefined);
  ASSERT_EQ(YGNodeStyleGetMargin(root, YGEdgeBottom).unit, YGUnitUndefined);
  ASSERT_EQ(YGNodeStyleGetMargin(root, YGEdgeStart).unit, YGUnitUndefined);
  ASSERT_EQ(YGNodeStyleGetMargin(root, YGEdgeEnd).unit, YGUnitUndefined);

  ASSERT_EQ(YGNodeStyleGetPadding(root, YGEdgeLeft).unit, YGUnitUndefined);
  ASSERT_EQ(YGNodeStyleGetPadding(root, YGEdgeTop).unit, YGUnitUndefined);
  ASSERT_EQ(YGNodeStyleGetPadding(root, YGEdgeRight).unit, YGUnitUndefined);
  ASSERT_EQ(YGNodeStyleGetPadding(root, YGEdgeBottom).unit, YGUnitUndefined);
  ASSERT_EQ(YGNodeStyleGetPadding(root, YGEdgeStart).unit, YGUnitUndefined);
  ASSERT_EQ(YGNodeStyleGetPadding(root, YGEdgeEnd).unit, YGUnitUndefined);

  ASSERT_TRUE(YGFloatIsUndefined(YGNodeStyleGetBorder(root, YGEdgeLeft)));
  ASSERT_TRUE(YGFloatIsUndefined(YGNodeStyleGetBorder(root, YGEdgeTop)));
  ASSERT_TRUE(YGFloatIsUndefined(YGNodeStyleGetBorder(root, YGEdgeRight)));
  ASSERT_TRUE(YGFloatIsUndefined(YGNodeStyleGetBorder(root, YGEdgeBottom)));
  ASSERT_TRUE(YGFloatIsUndefined(YGNodeStyleGetBorder(root, YGEdgeStart)));
  ASSERT_TRUE(YGFloatIsUndefined(YGNodeStyleGetBorder(root, YGEdgeEnd)));

  ASSERT_EQ(YGNodeStyleGetWidth(root).unit, YGUnitAuto);
  ASSERT_EQ(YGNodeStyleGetHeight(root).unit, YGUnitAuto);
  ASSERT_EQ(YGNodeStyleGetMinWidth(root).unit, YGUnitUndefined);
  ASSERT_EQ(YGNodeStyleGetMinHeight(root).unit, YGUnitUndefined);
  ASSERT_EQ(YGNodeStyleGetMaxWidth(root).unit, YGUnitUndefined);
  ASSERT_EQ(YGNodeStyleGetMaxHeight(root).unit, YGUnitUndefined);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetRight(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetBottom(root));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetMargin(root, YGEdgeLeft));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetMargin(root, YGEdgeTop));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetMargin(root, YGEdgeRight));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetMargin(root, YGEdgeBottom));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetPadding(root, YGEdgeLeft));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetPadding(root, YGEdgeTop));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetPadding(root, YGEdgeRight));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetPadding(root, YGEdgeBottom));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetBorder(root, YGEdgeLeft));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetBorder(root, YGEdgeTop));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetBorder(root, YGEdgeRight));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetBorder(root, YGEdgeBottom));

  ASSERT_TRUE(YGFloatIsUndefined(YGNodeLayoutGetWidth(root)));
  ASSERT_TRUE(YGFloatIsUndefined(YGNodeLayoutGetHeight(root)));
  ASSERT_EQ(YGDirectionInherit, YGNodeLayoutGetDirection(root));

  YGNodeFreeRecursive(root);
}
