/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>
#include <yoga/Yoga.h>

static YGSize _measure(
    YGNodeConstRef /*node*/,
    float width,
    YGMeasureMode widthMode,
    float height,
    YGMeasureMode heightMode) {
  return YGSize{
      widthMode == YGMeasureModeExactly ? width : 50,
      heightMode == YGMeasureModeExactly ? height : 50,
  };
}

TEST(YogaTest, aspect_ratio_cross_defined) {
  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetAlignItems(root, YGAlignFlexStart);
  YGNodeStyleSetWidth(root, 100);
  YGNodeStyleSetHeight(root, 100);

  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeStyleSetWidth(root_child0, 50);
  YGNodeStyleSetAspectRatio(root_child0, 1);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_EQ(50, YGNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, YGNodeLayoutGetHeight(root_child0));

  YGNodeFreeRecursive(root);
}

TEST(YogaTest, aspect_ratio_main_defined) {
  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetAlignItems(root, YGAlignFlexStart);
  YGNodeStyleSetWidth(root, 100);
  YGNodeStyleSetHeight(root, 100);

  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeStyleSetHeight(root_child0, 50);
  YGNodeStyleSetAspectRatio(root_child0, 1);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_EQ(50, YGNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, YGNodeLayoutGetHeight(root_child0));

  YGNodeFreeRecursive(root);
}

TEST(YogaTest, aspect_ratio_both_dimensions_defined_row) {
  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetFlexDirection(root, YGFlexDirectionRow);
  YGNodeStyleSetAlignItems(root, YGAlignFlexStart);
  YGNodeStyleSetWidth(root, 100);
  YGNodeStyleSetHeight(root, 100);

  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeStyleSetWidth(root_child0, 100);
  YGNodeStyleSetHeight(root_child0, 50);
  YGNodeStyleSetAspectRatio(root_child0, 1);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_EQ(100, YGNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(100, YGNodeLayoutGetHeight(root_child0));

  YGNodeFreeRecursive(root);
}

TEST(YogaTest, aspect_ratio_both_dimensions_defined_column) {
  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetAlignItems(root, YGAlignFlexStart);
  YGNodeStyleSetWidth(root, 100);
  YGNodeStyleSetHeight(root, 100);

  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeStyleSetWidth(root_child0, 100);
  YGNodeStyleSetHeight(root_child0, 50);
  YGNodeStyleSetAspectRatio(root_child0, 1);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_EQ(50, YGNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, YGNodeLayoutGetHeight(root_child0));

  YGNodeFreeRecursive(root);
}

TEST(YogaTest, aspect_ratio_align_stretch) {
  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetWidth(root, 100);
  YGNodeStyleSetHeight(root, 100);

  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeStyleSetAspectRatio(root_child0, 1);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_EQ(100, YGNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(100, YGNodeLayoutGetHeight(root_child0));

  YGNodeFreeRecursive(root);
}

TEST(YogaTest, aspect_ratio_flex_grow) {
  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetAlignItems(root, YGAlignFlexStart);
  YGNodeStyleSetWidth(root, 100);
  YGNodeStyleSetHeight(root, 100);

  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeStyleSetHeight(root_child0, 50);
  YGNodeStyleSetFlexGrow(root_child0, 1);
  YGNodeStyleSetAspectRatio(root_child0, 1);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_EQ(100, YGNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(100, YGNodeLayoutGetHeight(root_child0));

  YGNodeFreeRecursive(root);
}

TEST(YogaTest, aspect_ratio_flex_shrink) {
  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetAlignItems(root, YGAlignFlexStart);
  YGNodeStyleSetWidth(root, 100);
  YGNodeStyleSetHeight(root, 100);

  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeStyleSetHeight(root_child0, 150);
  YGNodeStyleSetFlexShrink(root_child0, 1);
  YGNodeStyleSetAspectRatio(root_child0, 1);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_EQ(100, YGNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(100, YGNodeLayoutGetHeight(root_child0));

  YGNodeFreeRecursive(root);
}

TEST(YogaTest, aspect_ratio_flex_shrink_2) {
  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetWidth(root, 100);
  YGNodeStyleSetHeight(root, 100);

  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeStyleSetHeightPercent(root_child0, 100);
  YGNodeStyleSetFlexShrink(root_child0, 1);
  YGNodeStyleSetAspectRatio(root_child0, 1);
  YGNodeInsertChild(root, root_child0, 0);

  const YGNodeRef root_child1 = YGNodeNew();
  YGNodeStyleSetHeightPercent(root_child1, 100);
  YGNodeStyleSetFlexShrink(root_child1, 1);
  YGNodeStyleSetAspectRatio(root_child1, 1);
  YGNodeInsertChild(root, root_child1, 1);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_EQ(50, YGNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, YGNodeLayoutGetHeight(root_child0));

  ASSERT_EQ(0, YGNodeLayoutGetLeft(root_child1));
  ASSERT_EQ(50, YGNodeLayoutGetTop(root_child1));
  ASSERT_EQ(50, YGNodeLayoutGetWidth(root_child1));
  ASSERT_EQ(50, YGNodeLayoutGetHeight(root_child1));

  YGNodeFreeRecursive(root);
}

TEST(YogaTest, aspect_ratio_basis) {
  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetAlignItems(root, YGAlignFlexStart);
  YGNodeStyleSetWidth(root, 100);
  YGNodeStyleSetHeight(root, 100);

  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeStyleSetFlexBasis(root_child0, 50);
  YGNodeStyleSetAspectRatio(root_child0, 1);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_EQ(50, YGNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, YGNodeLayoutGetHeight(root_child0));

  YGNodeFreeRecursive(root);
}

TEST(YogaTest, aspect_ratio_absolute_layout_width_defined) {
  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetWidth(root, 100);
  YGNodeStyleSetHeight(root, 100);

  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeStyleSetPositionType(root_child0, YGPositionTypeAbsolute);
  YGNodeStyleSetPosition(root_child0, YGEdgeLeft, 0);
  YGNodeStyleSetPosition(root_child0, YGEdgeTop, 0);
  YGNodeStyleSetWidth(root_child0, 50);
  YGNodeStyleSetAspectRatio(root_child0, 1);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_EQ(50, YGNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, YGNodeLayoutGetHeight(root_child0));

  YGNodeFreeRecursive(root);
}

TEST(YogaTest, aspect_ratio_absolute_layout_height_defined) {
  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetWidth(root, 100);
  YGNodeStyleSetHeight(root, 100);

  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeStyleSetPositionType(root_child0, YGPositionTypeAbsolute);
  YGNodeStyleSetPosition(root_child0, YGEdgeLeft, 0);
  YGNodeStyleSetPosition(root_child0, YGEdgeTop, 0);
  YGNodeStyleSetHeight(root_child0, 50);
  YGNodeStyleSetAspectRatio(root_child0, 1);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_EQ(50, YGNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, YGNodeLayoutGetHeight(root_child0));

  YGNodeFreeRecursive(root);
}

TEST(YogaTest, aspect_ratio_with_max_cross_defined) {
  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetAlignItems(root, YGAlignFlexStart);
  YGNodeStyleSetWidth(root, 100);
  YGNodeStyleSetHeight(root, 100);

  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeStyleSetHeight(root_child0, 50);
  YGNodeStyleSetMaxWidth(root_child0, 40);
  YGNodeStyleSetAspectRatio(root_child0, 1);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_EQ(40, YGNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, YGNodeLayoutGetHeight(root_child0));

  YGNodeFreeRecursive(root);
}

TEST(YogaTest, aspect_ratio_with_max_main_defined) {
  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetAlignItems(root, YGAlignFlexStart);
  YGNodeStyleSetWidth(root, 100);
  YGNodeStyleSetHeight(root, 100);

  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeStyleSetWidth(root_child0, 50);
  YGNodeStyleSetMaxHeight(root_child0, 40);
  YGNodeStyleSetAspectRatio(root_child0, 1);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_EQ(40, YGNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(40, YGNodeLayoutGetHeight(root_child0));

  YGNodeFreeRecursive(root);
}

TEST(YogaTest, aspect_ratio_with_min_cross_defined) {
  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetAlignItems(root, YGAlignFlexStart);
  YGNodeStyleSetWidth(root, 100);
  YGNodeStyleSetHeight(root, 100);

  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeStyleSetHeight(root_child0, 30);
  YGNodeStyleSetMinWidth(root_child0, 40);
  YGNodeStyleSetAspectRatio(root_child0, 1);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_EQ(40, YGNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(30, YGNodeLayoutGetHeight(root_child0));

  YGNodeFreeRecursive(root);
}

TEST(YogaTest, aspect_ratio_with_min_main_defined) {
  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetAlignItems(root, YGAlignFlexStart);
  YGNodeStyleSetWidth(root, 100);
  YGNodeStyleSetHeight(root, 100);

  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeStyleSetWidth(root_child0, 30);
  YGNodeStyleSetMinHeight(root_child0, 40);
  YGNodeStyleSetAspectRatio(root_child0, 1);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_EQ(40, YGNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(40, YGNodeLayoutGetHeight(root_child0));

  YGNodeFreeRecursive(root);
}

TEST(YogaTest, aspect_ratio_double_cross) {
  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetAlignItems(root, YGAlignFlexStart);
  YGNodeStyleSetWidth(root, 100);
  YGNodeStyleSetHeight(root, 100);

  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeStyleSetHeight(root_child0, 50);
  YGNodeStyleSetAspectRatio(root_child0, 2);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_EQ(100, YGNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, YGNodeLayoutGetHeight(root_child0));

  YGNodeFreeRecursive(root);
}

TEST(YogaTest, aspect_ratio_half_cross) {
  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetAlignItems(root, YGAlignFlexStart);
  YGNodeStyleSetWidth(root, 100);
  YGNodeStyleSetHeight(root, 100);

  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeStyleSetHeight(root_child0, 100);
  YGNodeStyleSetAspectRatio(root_child0, 0.5);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_EQ(50, YGNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(100, YGNodeLayoutGetHeight(root_child0));

  YGNodeFreeRecursive(root);
}

TEST(YogaTest, aspect_ratio_double_main) {
  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetAlignItems(root, YGAlignFlexStart);
  YGNodeStyleSetWidth(root, 100);
  YGNodeStyleSetHeight(root, 100);

  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeStyleSetWidth(root_child0, 50);
  YGNodeStyleSetAspectRatio(root_child0, 0.5);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_EQ(50, YGNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(100, YGNodeLayoutGetHeight(root_child0));

  YGNodeFreeRecursive(root);
}

TEST(YogaTest, aspect_ratio_half_main) {
  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetAlignItems(root, YGAlignFlexStart);
  YGNodeStyleSetWidth(root, 100);
  YGNodeStyleSetHeight(root, 100);

  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeStyleSetWidth(root_child0, 100);
  YGNodeStyleSetAspectRatio(root_child0, 2);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_EQ(100, YGNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, YGNodeLayoutGetHeight(root_child0));

  YGNodeFreeRecursive(root);
}

TEST(YogaTest, aspect_ratio_with_measure_func) {
  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetAlignItems(root, YGAlignFlexStart);
  YGNodeStyleSetWidth(root, 100);
  YGNodeStyleSetHeight(root, 100);

  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeSetMeasureFunc(root_child0, _measure);
  YGNodeStyleSetAspectRatio(root_child0, 1);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_EQ(50, YGNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, YGNodeLayoutGetHeight(root_child0));

  YGNodeFreeRecursive(root);
}

TEST(YogaTest, aspect_ratio_width_height_flex_grow_row) {
  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetFlexDirection(root, YGFlexDirectionRow);
  YGNodeStyleSetAlignItems(root, YGAlignFlexStart);
  YGNodeStyleSetWidth(root, 100);
  YGNodeStyleSetHeight(root, 200);

  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeStyleSetWidth(root_child0, 50);
  YGNodeStyleSetHeight(root_child0, 50);
  YGNodeStyleSetFlexGrow(root_child0, 1);
  YGNodeStyleSetAspectRatio(root_child0, 1);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_EQ(100, YGNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(100, YGNodeLayoutGetHeight(root_child0));

  YGNodeFreeRecursive(root);
}

TEST(YogaTest, aspect_ratio_width_height_flex_grow_column) {
  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetAlignItems(root, YGAlignFlexStart);
  YGNodeStyleSetWidth(root, 200);
  YGNodeStyleSetHeight(root, 100);

  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeStyleSetWidth(root_child0, 50);
  YGNodeStyleSetHeight(root_child0, 50);
  YGNodeStyleSetFlexGrow(root_child0, 1);
  YGNodeStyleSetAspectRatio(root_child0, 1);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_EQ(100, YGNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(100, YGNodeLayoutGetHeight(root_child0));

  YGNodeFreeRecursive(root);
}

TEST(YogaTest, aspect_ratio_height_as_flex_basis) {
  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetAlignItems(root, YGAlignFlexStart);
  YGNodeStyleSetFlexDirection(root, YGFlexDirectionRow);
  YGNodeStyleSetWidth(root, 200);
  YGNodeStyleSetHeight(root, 200);

  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeStyleSetHeight(root_child0, 50);
  YGNodeStyleSetFlexGrow(root_child0, 1);
  YGNodeStyleSetAspectRatio(root_child0, 1);
  YGNodeInsertChild(root, root_child0, 0);

  const YGNodeRef root_child1 = YGNodeNew();
  YGNodeStyleSetHeight(root_child1, 100);
  YGNodeStyleSetFlexGrow(root_child1, 1);
  YGNodeStyleSetAspectRatio(root_child1, 1);
  YGNodeInsertChild(root, root_child1, 1);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_EQ(75, YGNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(75, YGNodeLayoutGetHeight(root_child0));

  ASSERT_EQ(75, YGNodeLayoutGetLeft(root_child1));
  ASSERT_EQ(0, YGNodeLayoutGetTop(root_child1));
  ASSERT_EQ(125, YGNodeLayoutGetWidth(root_child1));
  ASSERT_EQ(125, YGNodeLayoutGetHeight(root_child1));

  YGNodeFreeRecursive(root);
}

TEST(YogaTest, aspect_ratio_width_as_flex_basis) {
  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetAlignItems(root, YGAlignFlexStart);
  YGNodeStyleSetWidth(root, 200);
  YGNodeStyleSetHeight(root, 200);

  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeStyleSetWidth(root_child0, 50);
  YGNodeStyleSetFlexGrow(root_child0, 1);
  YGNodeStyleSetAspectRatio(root_child0, 1);
  YGNodeInsertChild(root, root_child0, 0);

  const YGNodeRef root_child1 = YGNodeNew();
  YGNodeStyleSetWidth(root_child1, 100);
  YGNodeStyleSetFlexGrow(root_child1, 1);
  YGNodeStyleSetAspectRatio(root_child1, 1);
  YGNodeInsertChild(root, root_child1, 1);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_EQ(75, YGNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(75, YGNodeLayoutGetHeight(root_child0));

  ASSERT_EQ(0, YGNodeLayoutGetLeft(root_child1));
  ASSERT_EQ(75, YGNodeLayoutGetTop(root_child1));
  ASSERT_EQ(125, YGNodeLayoutGetWidth(root_child1));
  ASSERT_EQ(125, YGNodeLayoutGetHeight(root_child1));

  YGNodeFreeRecursive(root);
}

TEST(YogaTest, aspect_ratio_overrides_flex_grow_row) {
  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetAlignItems(root, YGAlignFlexStart);
  YGNodeStyleSetFlexDirection(root, YGFlexDirectionRow);
  YGNodeStyleSetWidth(root, 100);
  YGNodeStyleSetHeight(root, 100);

  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeStyleSetWidth(root_child0, 50);
  YGNodeStyleSetFlexGrow(root_child0, 1);
  YGNodeStyleSetAspectRatio(root_child0, 0.5);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_EQ(100, YGNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(200, YGNodeLayoutGetHeight(root_child0));

  YGNodeFreeRecursive(root);
}

TEST(YogaTest, aspect_ratio_overrides_flex_grow_column) {
  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetAlignItems(root, YGAlignFlexStart);
  YGNodeStyleSetWidth(root, 100);
  YGNodeStyleSetHeight(root, 100);

  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeStyleSetHeight(root_child0, 50);
  YGNodeStyleSetFlexGrow(root_child0, 1);
  YGNodeStyleSetAspectRatio(root_child0, 2);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_EQ(200, YGNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(100, YGNodeLayoutGetHeight(root_child0));

  YGNodeFreeRecursive(root);
}

TEST(YogaTest, aspect_ratio_left_right_absolute) {
  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetWidth(root, 100);
  YGNodeStyleSetHeight(root, 100);

  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeStyleSetPositionType(root_child0, YGPositionTypeAbsolute);
  YGNodeStyleSetPosition(root_child0, YGEdgeLeft, 10);
  YGNodeStyleSetPosition(root_child0, YGEdgeTop, 10);
  YGNodeStyleSetPosition(root_child0, YGEdgeRight, 10);
  YGNodeStyleSetAspectRatio(root_child0, 1);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(10, YGNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(10, YGNodeLayoutGetTop(root_child0));
  ASSERT_EQ(80, YGNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(80, YGNodeLayoutGetHeight(root_child0));

  YGNodeFreeRecursive(root);
}

TEST(YogaTest, aspect_ratio_top_bottom_absolute) {
  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetWidth(root, 100);
  YGNodeStyleSetHeight(root, 100);

  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeStyleSetPositionType(root_child0, YGPositionTypeAbsolute);
  YGNodeStyleSetPosition(root_child0, YGEdgeLeft, 10);
  YGNodeStyleSetPosition(root_child0, YGEdgeTop, 10);
  YGNodeStyleSetPosition(root_child0, YGEdgeBottom, 10);
  YGNodeStyleSetAspectRatio(root_child0, 1);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(10, YGNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(10, YGNodeLayoutGetTop(root_child0));
  ASSERT_EQ(80, YGNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(80, YGNodeLayoutGetHeight(root_child0));

  YGNodeFreeRecursive(root);
}

TEST(YogaTest, aspect_ratio_width_overrides_align_stretch_row) {
  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetFlexDirection(root, YGFlexDirectionRow);
  YGNodeStyleSetWidth(root, 100);
  YGNodeStyleSetHeight(root, 100);

  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeStyleSetWidth(root_child0, 50);
  YGNodeStyleSetAspectRatio(root_child0, 1);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_EQ(50, YGNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, YGNodeLayoutGetHeight(root_child0));

  YGNodeFreeRecursive(root);
}

TEST(YogaTest, aspect_ratio_height_overrides_align_stretch_column) {
  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetWidth(root, 100);
  YGNodeStyleSetHeight(root, 100);

  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeStyleSetHeight(root_child0, 50);
  YGNodeStyleSetAspectRatio(root_child0, 1);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_EQ(50, YGNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, YGNodeLayoutGetHeight(root_child0));

  YGNodeFreeRecursive(root);
}

TEST(YogaTest, aspect_ratio_allow_child_overflow_parent_size) {
  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetAlignItems(root, YGAlignFlexStart);
  YGNodeStyleSetWidth(root, 100);

  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeStyleSetHeight(root_child0, 50);
  YGNodeStyleSetAspectRatio(root_child0, 4);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(100, YGNodeLayoutGetWidth(root));
  ASSERT_EQ(50, YGNodeLayoutGetHeight(root));

  ASSERT_EQ(200, YGNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, YGNodeLayoutGetHeight(root_child0));

  YGNodeFreeRecursive(root);
}

TEST(YogaTest, aspect_ratio_defined_main_with_margin) {
  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetAlignItems(root, YGAlignCenter);
  YGNodeStyleSetJustifyContent(root, YGJustifyCenter);
  YGNodeStyleSetWidth(root, 100);
  YGNodeStyleSetHeight(root, 100);

  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeStyleSetHeight(root_child0, 50);
  YGNodeStyleSetAspectRatio(root_child0, 1);
  YGNodeStyleSetMargin(root_child0, YGEdgeLeft, 10);
  YGNodeStyleSetMargin(root_child0, YGEdgeRight, 10);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(100, YGNodeLayoutGetWidth(root));
  ASSERT_EQ(100, YGNodeLayoutGetHeight(root));

  ASSERT_EQ(50, YGNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, YGNodeLayoutGetHeight(root_child0));

  YGNodeFreeRecursive(root);
}

TEST(YogaTest, aspect_ratio_defined_cross_with_margin) {
  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetAlignItems(root, YGAlignCenter);
  YGNodeStyleSetJustifyContent(root, YGJustifyCenter);
  YGNodeStyleSetWidth(root, 100);
  YGNodeStyleSetHeight(root, 100);

  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeStyleSetWidth(root_child0, 50);
  YGNodeStyleSetAspectRatio(root_child0, 1);
  YGNodeStyleSetMargin(root_child0, YGEdgeLeft, 10);
  YGNodeStyleSetMargin(root_child0, YGEdgeRight, 10);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(100, YGNodeLayoutGetWidth(root));
  ASSERT_EQ(100, YGNodeLayoutGetHeight(root));

  ASSERT_EQ(50, YGNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, YGNodeLayoutGetHeight(root_child0));

  YGNodeFreeRecursive(root);
}

TEST(YogaTest, aspect_ratio_defined_cross_with_main_margin) {
  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetAlignItems(root, YGAlignCenter);
  YGNodeStyleSetJustifyContent(root, YGJustifyCenter);
  YGNodeStyleSetWidth(root, 100);
  YGNodeStyleSetHeight(root, 100);

  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeStyleSetWidth(root_child0, 50);
  YGNodeStyleSetAspectRatio(root_child0, 1);
  YGNodeStyleSetMargin(root_child0, YGEdgeTop, 10);
  YGNodeStyleSetMargin(root_child0, YGEdgeBottom, 10);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(100, YGNodeLayoutGetWidth(root));
  ASSERT_EQ(100, YGNodeLayoutGetHeight(root));

  ASSERT_EQ(50, YGNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, YGNodeLayoutGetHeight(root_child0));

  YGNodeFreeRecursive(root);
}

TEST(YogaTest, aspect_ratio_should_prefer_explicit_height) {
  const YGConfigRef config = YGConfigNew();
  YGConfigSetUseWebDefaults(config, true);

  const YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexDirection(root, YGFlexDirectionColumn);

  const YGNodeRef root_child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexDirection(root_child0, YGFlexDirectionColumn);
  YGNodeInsertChild(root, root_child0, 0);

  const YGNodeRef root_child0_child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexDirection(root_child0_child0, YGFlexDirectionColumn);
  YGNodeStyleSetHeight(root_child0_child0, 100);
  YGNodeStyleSetAspectRatio(root_child0_child0, 2);
  YGNodeInsertChild(root_child0, root_child0_child0, 0);

  YGNodeCalculateLayout(root, 100, 200, YGDirectionLTR);

  ASSERT_EQ(100, YGNodeLayoutGetWidth(root));
  ASSERT_EQ(200, YGNodeLayoutGetHeight(root));

  ASSERT_EQ(100, YGNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(100, YGNodeLayoutGetHeight(root_child0));

  ASSERT_EQ(200, YGNodeLayoutGetWidth(root_child0_child0));
  ASSERT_EQ(100, YGNodeLayoutGetHeight(root_child0_child0));

  YGNodeFreeRecursive(root);
}

TEST(YogaTest, aspect_ratio_should_prefer_explicit_width) {
  const YGConfigRef config = YGConfigNew();
  YGConfigSetUseWebDefaults(config, true);

  const YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexDirection(root, YGFlexDirectionRow);

  const YGNodeRef root_child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexDirection(root_child0, YGFlexDirectionRow);
  YGNodeInsertChild(root, root_child0, 0);

  const YGNodeRef root_child0_child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexDirection(root_child0_child0, YGFlexDirectionRow);
  YGNodeStyleSetWidth(root_child0_child0, 100);
  YGNodeStyleSetAspectRatio(root_child0_child0, 0.5);
  YGNodeInsertChild(root_child0, root_child0_child0, 0);

  YGNodeCalculateLayout(root, 200, 100, YGDirectionLTR);

  ASSERT_EQ(200, YGNodeLayoutGetWidth(root));
  ASSERT_EQ(100, YGNodeLayoutGetHeight(root));

  ASSERT_EQ(100, YGNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(100, YGNodeLayoutGetHeight(root_child0));

  ASSERT_EQ(100, YGNodeLayoutGetWidth(root_child0_child0));
  ASSERT_EQ(200, YGNodeLayoutGetHeight(root_child0_child0));

  YGNodeFreeRecursive(root);
}

TEST(YogaTest, aspect_ratio_should_prefer_flexed_dimension) {
  const YGConfigRef config = YGConfigNew();
  YGConfigSetUseWebDefaults(config, true);

  const YGNodeRef root = YGNodeNewWithConfig(config);

  const YGNodeRef root_child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexDirection(root_child0, YGFlexDirectionColumn);
  YGNodeStyleSetAspectRatio(root_child0, 2);
  YGNodeStyleSetFlexGrow(root_child0, 1);
  YGNodeInsertChild(root, root_child0, 0);

  const YGNodeRef root_child0_child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetAspectRatio(root_child0_child0, 4);
  YGNodeStyleSetFlexGrow(root_child0_child0, 1);
  YGNodeInsertChild(root_child0, root_child0_child0, 0);

  YGNodeCalculateLayout(root, 100, 100, YGDirectionLTR);

  ASSERT_EQ(100, YGNodeLayoutGetWidth(root));
  ASSERT_EQ(100, YGNodeLayoutGetHeight(root));

  ASSERT_EQ(100, YGNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, YGNodeLayoutGetHeight(root_child0));

  ASSERT_EQ(200, YGNodeLayoutGetWidth(root_child0_child0));
  ASSERT_EQ(50, YGNodeLayoutGetHeight(root_child0_child0));

  YGNodeFreeRecursive(root);
}
