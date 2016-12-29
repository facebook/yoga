/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

(function() {
  const root = Yoga.nodeNew();

  ASSERT_EQ(0, Yoga.nodeGetChildCount(root));
  ASSERT_EQ(0, Yoga.nodeGetChild(root, 1));

  ASSERT_EQ(Yoga.DirectionInherit, Yoga.nodeStyleGetDirection(root));
  ASSERT_EQ(Yoga.FlexDirectionColumn, Yoga.nodeStyleGetFlexDirection(root));
  ASSERT_EQ(Yoga.JustifyFlexStart, Yoga.nodeStyleGetJustifyContent(root));
  ASSERT_EQ(Yoga.AlignFlexStart, Yoga.nodeStyleGetAlignContent(root));
  ASSERT_EQ(Yoga.AlignStretch, Yoga.nodeStyleGetAlignItems(root));
  ASSERT_EQ(Yoga.AlignAuto, Yoga.nodeStyleGetAlignSelf(root));
  ASSERT_EQ(Yoga.PositionTypeRelative, Yoga.nodeStyleGetPositionType(root));
  ASSERT_EQ(Yoga.WrapNoWrap, Yoga.nodeStyleGetFlexWrap(root));
  ASSERT_EQ(Yoga.OverflowVisible, Yoga.nodeStyleGetOverflow(root));
  ASSERT_FLOAT_EQ(0, Yoga.nodeStyleGetFlexGrow(root));
  ASSERT_FLOAT_EQ(0, Yoga.nodeStyleGetFlexShrink(root));
  ASSERT_TRUE(Yoga.valueIsUndefined(Yoga.nodeStyleGetFlexBasis(root)));

  ASSERT_TRUE(Yoga.valueIsUndefined(Yoga.nodeStyleGetPosition(root, Yoga.EdgeLeft)));
  ASSERT_TRUE(Yoga.valueIsUndefined(Yoga.nodeStyleGetPosition(root, Yoga.EdgeTop)));
  ASSERT_TRUE(Yoga.valueIsUndefined(Yoga.nodeStyleGetPosition(root, Yoga.EdgeRight)));
  ASSERT_TRUE(Yoga.valueIsUndefined(Yoga.nodeStyleGetPosition(root, Yoga.EdgeBottom)));
  ASSERT_TRUE(Yoga.valueIsUndefined(Yoga.nodeStyleGetPosition(root, Yoga.EdgeStart)));
  ASSERT_TRUE(Yoga.valueIsUndefined(Yoga.nodeStyleGetPosition(root, Yoga.EdgeEnd)));

  ASSERT_FLOAT_EQ(0, Yoga.nodeStyleGetMargin(root, Yoga.EdgeLeft));
  ASSERT_FLOAT_EQ(0, Yoga.nodeStyleGetMargin(root, Yoga.EdgeTop));
  ASSERT_FLOAT_EQ(0, Yoga.nodeStyleGetMargin(root, Yoga.EdgeRight));
  ASSERT_FLOAT_EQ(0, Yoga.nodeStyleGetMargin(root, Yoga.EdgeBottom));
  ASSERT_TRUE(Yoga.valueIsUndefined(Yoga.nodeStyleGetMargin(root, Yoga.EdgeStart)));
  ASSERT_TRUE(Yoga.valueIsUndefined(Yoga.nodeStyleGetMargin(root, Yoga.EdgeEnd)));

  ASSERT_FLOAT_EQ(0, Yoga.nodeStyleGetPadding(root, Yoga.EdgeLeft));
  ASSERT_FLOAT_EQ(0, Yoga.nodeStyleGetPadding(root, Yoga.EdgeTop));
  ASSERT_FLOAT_EQ(0, Yoga.nodeStyleGetPadding(root, Yoga.EdgeRight));
  ASSERT_FLOAT_EQ(0, Yoga.nodeStyleGetPadding(root, Yoga.EdgeBottom));
  ASSERT_TRUE(Yoga.valueIsUndefined(Yoga.nodeStyleGetPadding(root, Yoga.EdgeStart)));
  ASSERT_TRUE(Yoga.valueIsUndefined(Yoga.nodeStyleGetPadding(root, Yoga.EdgeEnd)));

  ASSERT_FLOAT_EQ(0, Yoga.nodeStyleGetBorder(root, Yoga.EdgeLeft));
  ASSERT_FLOAT_EQ(0, Yoga.nodeStyleGetBorder(root, Yoga.EdgeTop));
  ASSERT_FLOAT_EQ(0, Yoga.nodeStyleGetBorder(root, Yoga.EdgeRight));
  ASSERT_FLOAT_EQ(0, Yoga.nodeStyleGetBorder(root, Yoga.EdgeBottom));
  ASSERT_TRUE(Yoga.valueIsUndefined(Yoga.nodeStyleGetBorder(root, Yoga.EdgeStart)));
  ASSERT_TRUE(Yoga.valueIsUndefined(Yoga.nodeStyleGetBorder(root, Yoga.EdgeEnd)));

  ASSERT_TRUE(Yoga.valueIsUndefined(Yoga.nodeStyleGetWidth(root)));
  ASSERT_TRUE(Yoga.valueIsUndefined(Yoga.nodeStyleGetHeight(root)));
  ASSERT_TRUE(Yoga.valueIsUndefined(Yoga.nodeStyleGetMinWidth(root)));
  ASSERT_TRUE(Yoga.valueIsUndefined(Yoga.nodeStyleGetMinHeight(root)));
  ASSERT_TRUE(Yoga.valueIsUndefined(Yoga.nodeStyleGetMaxWidth(root)));
  ASSERT_TRUE(Yoga.valueIsUndefined(Yoga.nodeStyleGetMaxHeight(root)));

  ASSERT_FLOAT_EQ(0, Yoga.nodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, Yoga.nodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(0, Yoga.nodeLayoutGetRight(root));
  ASSERT_FLOAT_EQ(0, Yoga.nodeLayoutGetBottom(root));
  ASSERT_TRUE(Yoga.valueIsUndefined(Yoga.nodeLayoutGetWidth(root)));
  ASSERT_TRUE(Yoga.valueIsUndefined(Yoga.nodeLayoutGetHeight(root)));
  ASSERT_EQ(Yoga.DirectionInherit, Yoga.nodeLayoutGetDirection(root));

  Yoga.nodeFreeRecursive(root);
})();
