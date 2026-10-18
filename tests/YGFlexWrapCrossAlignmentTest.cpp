/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>
#include <yoga/Yoga.h>

#include <initializer_list>

namespace {

struct Box {
  float left;
  float top;
  float width;
  float height;
};

struct Expected {
  YGAlign align;
  Box ltr;
  Box rtl;
};

// Lays out a wrapping container with two flex lines and returns the box of
// the item on the second line. That item has a margin of 5 on every edge and a
// relative inset of 10 on its left and top edges. Its sibling makes the second
// line 60 thick in the cross axis, and the first line is 30 thick. With
// align-items: stretch the item has no cross size of its own.
Box layoutItemOnSecondLine(
    YGFlexDirection flexDirection,
    YGWrap wrap,
    YGAlign alignItems,
    YGDirection direction) {
  const bool isRow = flexDirection == YGFlexDirectionRow;
  const bool stretch = alignItems == YGAlignStretch;

  YGConfigRef config = YGConfigNew();

  YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexDirection(root, flexDirection);
  YGNodeStyleSetFlexWrap(root, wrap);
  YGNodeStyleSetAlignContent(root, YGAlignFlexStart);
  YGNodeStyleSetAlignItems(root, alignItems);
  YGNodeStyleSetPadding(root, YGEdgeAll, 10);
  YGNodeStyleSetWidth(root, isRow ? 150 : 200);
  YGNodeStyleSetHeight(root, isRow ? 200 : 150);

  YGNodeRef first = YGNodeNewWithConfig(config);
  YGNodeStyleSetWidth(first, isRow ? 100 : 30);
  YGNodeStyleSetHeight(first, isRow ? 30 : 100);
  YGNodeInsertChild(root, first, 0);

  YGNodeRef item = YGNodeNewWithConfig(config);
  YGNodeStyleSetMargin(item, YGEdgeAll, 5);
  YGNodeStyleSetPosition(item, YGEdgeLeft, 10);
  YGNodeStyleSetPosition(item, YGEdgeTop, 10);
  if (isRow) {
    YGNodeStyleSetWidth(item, 50);
    if (!stretch) {
      YGNodeStyleSetHeight(item, 20);
    }
  } else {
    YGNodeStyleSetHeight(item, 50);
    if (!stretch) {
      YGNodeStyleSetWidth(item, 20);
    }
  }
  YGNodeInsertChild(root, item, 1);

  YGNodeRef sibling = YGNodeNewWithConfig(config);
  YGNodeStyleSetWidth(sibling, isRow ? 40 : 60);
  YGNodeStyleSetHeight(sibling, isRow ? 60 : 40);
  YGNodeInsertChild(root, sibling, 2);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, direction);

  const Box box{
      YGNodeLayoutGetLeft(item),
      YGNodeLayoutGetTop(item),
      YGNodeLayoutGetWidth(item),
      YGNodeLayoutGetHeight(item)};

  YGNodeFreeRecursive(root);
  YGConfigFree(config);

  return box;
}

void expectBox(const Box& actual, const Box& expected) {
  EXPECT_FLOAT_EQ(expected.left, actual.left);
  EXPECT_FLOAT_EQ(expected.top, actual.top);
  EXPECT_FLOAT_EQ(expected.width, actual.width);
  EXPECT_FLOAT_EQ(expected.height, actual.height);
}

void checkAllAlignments(
    YGFlexDirection flexDirection,
    YGWrap wrap,
    const std::initializer_list<Expected>& cases) {
  for (const auto& expected : cases) {
    SCOPED_TRACE(YGAlignToString(expected.align));
    {
      SCOPED_TRACE("LTR");
      expectBox(
          layoutItemOnSecondLine(
              flexDirection, wrap, expected.align, YGDirectionLTR),
          expected.ltr);
    }
    {
      SCOPED_TRACE("RTL");
      expectBox(
          layoutItemOnSecondLine(
              flexDirection, wrap, expected.align, YGDirectionRTL),
          expected.rtl);
    }
  }
}

// Lays out a wrap-reverse container with one line, 40 thick in the cross
// axis and packed against the cross start, which is the bottom of a row and
// the right of an LTR column. The item comes after a sibling and has a margin
// of 10 on one edge only.
Box layoutWrapReverseItemWithOneSidedMargin(
    YGFlexDirection flexDirection,
    YGEdge marginEdge,
    YGAlign alignItems,
    YGDirection direction) {
  const bool isRow = flexDirection == YGFlexDirectionRow;
  const bool stretch = alignItems == YGAlignStretch;

  YGConfigRef config = YGConfigNew();

  YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexDirection(root, flexDirection);
  YGNodeStyleSetFlexWrap(root, YGWrapWrapReverse);
  YGNodeStyleSetAlignContent(root, YGAlignFlexStart);
  YGNodeStyleSetAlignItems(root, alignItems);
  YGNodeStyleSetWidth(root, isRow ? 200 : 100);
  YGNodeStyleSetHeight(root, isRow ? 100 : 200);

  YGNodeRef sibling = YGNodeNewWithConfig(config);
  YGNodeStyleSetWidth(sibling, isRow ? 50 : 40);
  YGNodeStyleSetHeight(sibling, isRow ? 40 : 50);
  YGNodeInsertChild(root, sibling, 0);

  YGNodeRef item = YGNodeNewWithConfig(config);
  YGNodeStyleSetMargin(item, marginEdge, 10);
  if (isRow) {
    YGNodeStyleSetWidth(item, 50);
    if (!stretch) {
      YGNodeStyleSetHeight(item, 20);
    }
  } else {
    YGNodeStyleSetHeight(item, 50);
    if (!stretch) {
      YGNodeStyleSetWidth(item, 20);
    }
  }
  YGNodeInsertChild(root, item, 1);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, direction);

  const Box box{
      YGNodeLayoutGetLeft(item),
      YGNodeLayoutGetTop(item),
      YGNodeLayoutGetWidth(item),
      YGNodeLayoutGetHeight(item)};

  YGNodeFreeRecursive(root);
  YGConfigFree(config);

  return box;
}

struct AlignedBox {
  YGAlign align;
  Box box;
};

void checkOneSidedMargin(
    YGFlexDirection flexDirection,
    YGEdge marginEdge,
    YGDirection direction,
    const std::initializer_list<AlignedBox>& cases) {
  for (const auto& expected : cases) {
    SCOPED_TRACE(YGAlignToString(expected.align));
    expectBox(
        layoutWrapReverseItemWithOneSidedMargin(
            flexDirection, marginEdge, expected.align, direction),
        expected.box);
  }
}

} // namespace

// The second line spans top 40 to 100. The item keeps its margin and moves
// 10 down for its top inset under every alignment.
TEST(YogaTest, wrap_row_keeps_cross_axis_margin_and_inset) {
  checkAllAlignments(
      YGFlexDirectionRow,
      YGWrapWrap,
      {
          {YGAlignFlexStart, {25, 55, 50, 20}, {95, 55, 50, 20}},
          {YGAlignCenter, {25, 70, 50, 20}, {95, 70, 50, 20}},
          {YGAlignFlexEnd, {25, 85, 50, 20}, {95, 85, 50, 20}},
          {YGAlignStretch, {25, 55, 50, 50}, {95, 55, 50, 50}},
      });
}

// The second line spans top 100 to 160 and its cross start is the bottom. The
// top inset still moves the item down.
TEST(YogaTest, wrap_reverse_row_keeps_cross_axis_margin_and_inset) {
  checkAllAlignments(
      YGFlexDirectionRow,
      YGWrapWrapReverse,
      {
          {YGAlignFlexStart, {25, 145, 50, 20}, {95, 145, 50, 20}},
          {YGAlignCenter, {25, 130, 50, 20}, {95, 130, 50, 20}},
          {YGAlignFlexEnd, {25, 115, 50, 20}, {95, 115, 50, 20}},
          {YGAlignStretch, {25, 115, 50, 50}, {95, 115, 50, 50}},
      });
}

// The second line spans left 40 to 100 in LTR and left 100 to 160 in RTL. The
// left inset moves the item right in both directions.
TEST(YogaTest, wrap_column_keeps_cross_axis_margin_and_inset) {
  checkAllAlignments(
      YGFlexDirectionColumn,
      YGWrapWrap,
      {
          {YGAlignFlexStart, {55, 25, 20, 50}, {145, 25, 20, 50}},
          {YGAlignCenter, {70, 25, 20, 50}, {130, 25, 20, 50}},
          {YGAlignFlexEnd, {85, 25, 20, 50}, {115, 25, 20, 50}},
          {YGAlignStretch, {55, 25, 50, 50}, {115, 25, 50, 50}},
      });
}

// Reversing the lines swaps the two directions of the column case above.
TEST(YogaTest, wrap_reverse_column_keeps_cross_axis_margin_and_inset) {
  checkAllAlignments(
      YGFlexDirectionColumn,
      YGWrapWrapReverse,
      {
          {YGAlignFlexStart, {145, 25, 20, 50}, {55, 25, 20, 50}},
          {YGAlignCenter, {130, 25, 20, 50}, {70, 25, 20, 50}},
          {YGAlignFlexEnd, {115, 25, 20, 50}, {85, 25, 20, 50}},
          {YGAlignStretch, {115, 25, 50, 50}, {55, 25, 50, 50}},
      });
}

// The line spans top 60 to 100 in the row, left 60 to 100 in the LTR column
// and left 0 to 40 in the RTL column, where the cross start is the left. The
// margin stays on the edge it was set on.
TEST(YogaTest, wrap_reverse_keeps_one_sided_cross_axis_margin) {
  checkOneSidedMargin(
      YGFlexDirectionRow,
      YGEdgeTop,
      YGDirectionLTR,
      {
          {YGAlignFlexStart, {50, 80, 50, 20}},
          {YGAlignCenter, {50, 75, 50, 20}},
          {YGAlignFlexEnd, {50, 70, 50, 20}},
          {YGAlignStretch, {50, 70, 50, 30}},
      });
  checkOneSidedMargin(
      YGFlexDirectionRow,
      YGEdgeBottom,
      YGDirectionLTR,
      {
          {YGAlignFlexStart, {50, 70, 50, 20}},
          {YGAlignCenter, {50, 65, 50, 20}},
          {YGAlignFlexEnd, {50, 60, 50, 20}},
          {YGAlignStretch, {50, 60, 50, 30}},
      });
  checkOneSidedMargin(
      YGFlexDirectionColumn,
      YGEdgeLeft,
      YGDirectionLTR,
      {
          {YGAlignFlexStart, {80, 50, 20, 50}},
          {YGAlignCenter, {75, 50, 20, 50}},
          {YGAlignFlexEnd, {70, 50, 20, 50}},
      });
  checkOneSidedMargin(
      YGFlexDirectionColumn,
      YGEdgeLeft,
      YGDirectionRTL,
      {
          {YGAlignFlexStart, {10, 50, 20, 50}},
          {YGAlignCenter, {15, 50, 20, 50}},
          {YGAlignFlexEnd, {20, 50, 20, 50}},
      });
}

// https://github.com/react/yoga/issues/1856
TEST(YogaTest, wrap_column_relative_inset_moves_item_in_cross_axis) {
  YGConfigRef config = YGConfigNew();

  YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexWrap(root, YGWrapWrap);
  YGNodeStyleSetPadding(root, YGEdgeAll, 10);
  YGNodeStyleSetWidth(root, 200);
  YGNodeStyleSetHeight(root, 250);

  for (size_t i = 0; i < 4; i++) {
    YGNodeRef child = YGNodeNewWithConfig(config);
    YGNodeStyleSetMargin(child, YGEdgeAll, 5);
    YGNodeStyleSetWidth(child, 50);
    YGNodeStyleSetHeight(child, 50);
    YGNodeInsertChild(root, child, i);
  }
  YGNodeRef root_child0 = YGNodeGetChild(root, 0);
  YGNodeStyleSetPosition(root_child0, YGEdgeLeft, 10);
  YGNodeStyleSetPosition(root_child0, YGEdgeTop, 10);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(25, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(25, YGNodeLayoutGetTop(root_child0));

  ASSERT_FLOAT_EQ(15, YGNodeLayoutGetLeft(YGNodeGetChild(root, 1)));
  ASSERT_FLOAT_EQ(75, YGNodeLayoutGetTop(YGNodeGetChild(root, 1)));

  ASSERT_FLOAT_EQ(15, YGNodeLayoutGetLeft(YGNodeGetChild(root, 2)));
  ASSERT_FLOAT_EQ(135, YGNodeLayoutGetTop(YGNodeGetChild(root, 2)));

  ASSERT_FLOAT_EQ(75, YGNodeLayoutGetLeft(YGNodeGetChild(root, 3)));
  ASSERT_FLOAT_EQ(15, YGNodeLayoutGetTop(YGNodeGetChild(root, 3)));

  YGNodeFreeRecursive(root);
  YGConfigFree(config);
}

// https://github.com/react/yoga/issues/1067
TEST(YogaTest, wrap_row_align_items_center_with_one_sided_cross_margin) {
  YGConfigRef config = YGConfigNew();

  YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexDirection(root, YGFlexDirectionRow);
  YGNodeStyleSetFlexWrap(root, YGWrapWrap);
  YGNodeStyleSetAlignItems(root, YGAlignCenter);
  YGNodeStyleSetWidth(root, 300);

  YGNodeRef root_child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetMargin(root_child0, YGEdgeLeft, 100);
  YGNodeStyleSetMargin(root_child0, YGEdgeTop, 100);
  YGNodeStyleSetWidth(root_child0, 100);
  YGNodeStyleSetHeight(root_child0, 100);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(200, YGNodeLayoutGetHeight(root));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetTop(root_child0));

  YGNodeFreeRecursive(root);
  YGConfigFree(config);
}

// Baseline layouts go through the same multi-line pass even without wrap, so
// items there need their margin and inset too. A bottom inset moves an item up.
TEST(YogaTest, baseline_layout_keeps_cross_axis_margin_and_inset) {
  YGConfigRef config = YGConfigNew();

  YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexDirection(root, YGFlexDirectionRow);
  YGNodeStyleSetAlignItems(root, YGAlignBaseline);
  YGNodeStyleSetPadding(root, YGEdgeAll, 10);
  YGNodeStyleSetWidth(root, 300);
  YGNodeStyleSetHeight(root, 100);

  YGNodeRef root_child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetWidth(root_child0, 50);
  YGNodeStyleSetHeight(root_child0, 60);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeRef root_child1 = YGNodeNewWithConfig(config);
  YGNodeStyleSetAlignSelf(root_child1, YGAlignFlexStart);
  YGNodeStyleSetMargin(root_child1, YGEdgeTop, 5);
  YGNodeStyleSetPosition(root_child1, YGEdgeTop, 10);
  YGNodeStyleSetWidth(root_child1, 50);
  YGNodeStyleSetHeight(root_child1, 20);
  YGNodeInsertChild(root, root_child1, 1);

  YGNodeRef root_child2 = YGNodeNewWithConfig(config);
  YGNodeStyleSetPosition(root_child2, YGEdgeBottom, 10);
  YGNodeStyleSetWidth(root_child2, 50);
  YGNodeStyleSetHeight(root_child2, 20);
  YGNodeInsertChild(root, root_child2, 2);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(10, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(25, YGNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(40, YGNodeLayoutGetTop(root_child2));

  YGNodeFreeRecursive(root);
  YGConfigFree(config);
}

// Insets do not apply to statically positioned items, with or without wrap.
TEST(YogaTest, wrap_static_item_ignores_cross_axis_inset) {
  YGConfigRef config = YGConfigNew();

  YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexDirection(root, YGFlexDirectionRow);
  YGNodeStyleSetFlexWrap(root, YGWrapWrap);
  YGNodeStyleSetAlignItems(root, YGAlignFlexStart);
  YGNodeStyleSetWidth(root, 100);
  YGNodeStyleSetHeight(root, 100);

  YGNodeRef root_child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetPositionType(root_child0, YGPositionTypeStatic);
  YGNodeStyleSetPosition(root_child0, YGEdgeTop, 10);
  YGNodeStyleSetMargin(root_child0, YGEdgeTop, 5);
  YGNodeStyleSetWidth(root_child0, 50);
  YGNodeStyleSetHeight(root_child0, 20);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(5, YGNodeLayoutGetTop(root_child0));

  YGNodeFreeRecursive(root);
  YGConfigFree(config);
}
