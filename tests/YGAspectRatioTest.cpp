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

static YGSize _measure(YGNodeRef node,
                        float width,
                        YGMeasureMode widthMode,
                        float height,
                        YGMeasureMode heightMode) {
  return YGSize {
      .width = widthMode == YGMeasureModeExactly ? width : 50,
      .height = heightMode == YGMeasureModeExactly ? height : 50,
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

TEST(YogaTest, aspect_ratio_both_dimensions_defined) {
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
  ASSERT_EQ(100, YGNodeLayoutGetWidth(root_child0));
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
  ASSERT_EQ(50, YGNodeLayoutGetWidth(root_child0));
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
  ASSERT_EQ(30, YGNodeLayoutGetWidth(root_child0));
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
  YGNodeStyleSetAspectRatio(root_child0, 2);
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
  YGNodeStyleSetAspectRatio(root_child0, 0.5);
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
