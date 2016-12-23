/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

(function() {
  const root = _YGNodeNew();

  ASSERT_EQ(0, _YGNodeGetChildCount(root));
  ASSERT_EQ(0, _YGNodeGetChild(root, 1));

  ASSERT_EQ(_YGDirectionInherit, _YGNodeStyleGetDirection(root));
  ASSERT_EQ(_YGFlexDirectionColumn, _YGNodeStyleGetFlexDirection(root));
  ASSERT_EQ(_YGJustifyFlexStart, _YGNodeStyleGetJustifyContent(root));
  ASSERT_EQ(_YGAlignFlexStart, _YGNodeStyleGetAlignContent(root));
  ASSERT_EQ(_YGAlignStretch, _YGNodeStyleGetAlignItems(root));
  ASSERT_EQ(_YGAlignAuto, _YGNodeStyleGetAlignSelf(root));
  ASSERT_EQ(_YGPositionTypeRelative, _YGNodeStyleGetPositionType(root));
  ASSERT_EQ(_YGWrapNoWrap, _YGNodeStyleGetFlexWrap(root));
  ASSERT_EQ(_YGOverflowVisible, _YGNodeStyleGetOverflow(root));
  ASSERT_FLOAT_EQ(0, _YGNodeStyleGetFlexGrow(root));
  ASSERT_FLOAT_EQ(0, _YGNodeStyleGetFlexShrink(root));
  ASSERT_TRUE(_YGValueIsUndefined(_YGNodeStyleGetFlexBasis(root)));

  ASSERT_TRUE(_YGValueIsUndefined(_YGNodeStyleGetPosition(root, _YGEdgeLeft)));
  ASSERT_TRUE(_YGValueIsUndefined(_YGNodeStyleGetPosition(root, _YGEdgeTop)));
  ASSERT_TRUE(_YGValueIsUndefined(_YGNodeStyleGetPosition(root, _YGEdgeRight)));
  ASSERT_TRUE(_YGValueIsUndefined(_YGNodeStyleGetPosition(root, _YGEdgeBottom)));
  ASSERT_TRUE(_YGValueIsUndefined(_YGNodeStyleGetPosition(root, _YGEdgeStart)));
  ASSERT_TRUE(_YGValueIsUndefined(_YGNodeStyleGetPosition(root, _YGEdgeEnd)));

  ASSERT_FLOAT_EQ(0, _YGNodeStyleGetMargin(root, _YGEdgeLeft));
  ASSERT_FLOAT_EQ(0, _YGNodeStyleGetMargin(root, _YGEdgeTop));
  ASSERT_FLOAT_EQ(0, _YGNodeStyleGetMargin(root, _YGEdgeRight));
  ASSERT_FLOAT_EQ(0, _YGNodeStyleGetMargin(root, _YGEdgeBottom));
  ASSERT_TRUE(_YGValueIsUndefined(_YGNodeStyleGetMargin(root, _YGEdgeStart)));
  ASSERT_TRUE(_YGValueIsUndefined(_YGNodeStyleGetMargin(root, _YGEdgeEnd)));

  ASSERT_FLOAT_EQ(0, _YGNodeStyleGetPadding(root, _YGEdgeLeft));
  ASSERT_FLOAT_EQ(0, _YGNodeStyleGetPadding(root, _YGEdgeTop));
  ASSERT_FLOAT_EQ(0, _YGNodeStyleGetPadding(root, _YGEdgeRight));
  ASSERT_FLOAT_EQ(0, _YGNodeStyleGetPadding(root, _YGEdgeBottom));
  ASSERT_TRUE(_YGValueIsUndefined(_YGNodeStyleGetPadding(root, _YGEdgeStart)));
  ASSERT_TRUE(_YGValueIsUndefined(_YGNodeStyleGetPadding(root, _YGEdgeEnd)));

  ASSERT_FLOAT_EQ(0, _YGNodeStyleGetBorder(root, _YGEdgeLeft));
  ASSERT_FLOAT_EQ(0, _YGNodeStyleGetBorder(root, _YGEdgeTop));
  ASSERT_FLOAT_EQ(0, _YGNodeStyleGetBorder(root, _YGEdgeRight));
  ASSERT_FLOAT_EQ(0, _YGNodeStyleGetBorder(root, _YGEdgeBottom));
  ASSERT_TRUE(_YGValueIsUndefined(_YGNodeStyleGetBorder(root, _YGEdgeStart)));
  ASSERT_TRUE(_YGValueIsUndefined(_YGNodeStyleGetBorder(root, _YGEdgeEnd)));

  ASSERT_TRUE(_YGValueIsUndefined(_YGNodeStyleGetWidth(root)));
  ASSERT_TRUE(_YGValueIsUndefined(_YGNodeStyleGetHeight(root)));
  ASSERT_TRUE(_YGValueIsUndefined(_YGNodeStyleGetMinWidth(root)));
  ASSERT_TRUE(_YGValueIsUndefined(_YGNodeStyleGetMinHeight(root)));
  ASSERT_TRUE(_YGValueIsUndefined(_YGNodeStyleGetMaxWidth(root)));
  ASSERT_TRUE(_YGValueIsUndefined(_YGNodeStyleGetMaxHeight(root)));

  ASSERT_FLOAT_EQ(0, _YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, _YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(0, _YGNodeLayoutGetRight(root));
  ASSERT_FLOAT_EQ(0, _YGNodeLayoutGetBottom(root));
  ASSERT_TRUE(_YGValueIsUndefined(_YGNodeLayoutGetWidth(root)));
  ASSERT_TRUE(_YGValueIsUndefined(_YGNodeLayoutGetHeight(root)));
  ASSERT_EQ(_YGDirectionInherit, _YGNodeLayoutGetDirection(root));

  _YGNodeFreeRecursive(root);
})();
