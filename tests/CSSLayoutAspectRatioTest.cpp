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

static CSSSize _measure(CSSNodeRef node,
                        float width,
                        YGMeasureMode widthMode,
                        float height,
                        YGMeasureMode heightMode) {
  return CSSSize {
      .width = widthMode == YGMeasureModeExactly ? width : 50,
      .height = heightMode == YGMeasureModeExactly ? height : 50,
  };
}

TEST(CSSLayoutTest, aspect_ratio_cross_defined) {
  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetAlignItems(root, YGAlignFlexStart);
  CSSNodeStyleSetWidth(root, 100);
  CSSNodeStyleSetHeight(root, 100);

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeStyleSetWidth(root_child0, 50);
  CSSNodeStyleSetAspectRatio(root_child0, 1);
  CSSNodeInsertChild(root, root_child0, 0);

  CSSNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(0, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, CSSNodeLayoutGetTop(root_child0));
  ASSERT_EQ(50, CSSNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, CSSNodeLayoutGetHeight(root_child0));

  CSSNodeFreeRecursive(root);
}

TEST(CSSLayoutTest, aspect_ratio_main_defined) {
  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetAlignItems(root, YGAlignFlexStart);
  CSSNodeStyleSetWidth(root, 100);
  CSSNodeStyleSetHeight(root, 100);

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeStyleSetHeight(root_child0, 50);
  CSSNodeStyleSetAspectRatio(root_child0, 1);
  CSSNodeInsertChild(root, root_child0, 0);

  CSSNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(0, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, CSSNodeLayoutGetTop(root_child0));
  ASSERT_EQ(50, CSSNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, CSSNodeLayoutGetHeight(root_child0));

  CSSNodeFreeRecursive(root);
}

TEST(CSSLayoutTest, aspect_ratio_both_dimensions_defined) {
  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetWidth(root, 100);
  CSSNodeStyleSetHeight(root, 100);

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeStyleSetHeight(root_child0, 50);
  CSSNodeStyleSetAspectRatio(root_child0, 1);
  CSSNodeInsertChild(root, root_child0, 0);

  CSSNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(0, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, CSSNodeLayoutGetTop(root_child0));
  ASSERT_EQ(100, CSSNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, CSSNodeLayoutGetHeight(root_child0));

  CSSNodeFreeRecursive(root);
}

TEST(CSSLayoutTest, aspect_ratio_align_stretch) {
  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetWidth(root, 100);
  CSSNodeStyleSetHeight(root, 100);

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeStyleSetAspectRatio(root_child0, 1);
  CSSNodeInsertChild(root, root_child0, 0);

  CSSNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(0, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, CSSNodeLayoutGetTop(root_child0));
  ASSERT_EQ(100, CSSNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(100, CSSNodeLayoutGetHeight(root_child0));

  CSSNodeFreeRecursive(root);
}

TEST(CSSLayoutTest, aspect_ratio_flex_grow) {
  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetAlignItems(root, YGAlignFlexStart);
  CSSNodeStyleSetWidth(root, 100);
  CSSNodeStyleSetHeight(root, 100);

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeStyleSetHeight(root_child0, 50);
  CSSNodeStyleSetFlexGrow(root_child0, 1);
  CSSNodeStyleSetAspectRatio(root_child0, 1);
  CSSNodeInsertChild(root, root_child0, 0);

  CSSNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(0, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, CSSNodeLayoutGetTop(root_child0));
  ASSERT_EQ(100, CSSNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(100, CSSNodeLayoutGetHeight(root_child0));

  CSSNodeFreeRecursive(root);
}

TEST(CSSLayoutTest, aspect_ratio_flex_shrink) {
  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetAlignItems(root, YGAlignFlexStart);
  CSSNodeStyleSetWidth(root, 100);
  CSSNodeStyleSetHeight(root, 100);

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeStyleSetHeight(root_child0, 150);
  CSSNodeStyleSetFlexShrink(root_child0, 1);
  CSSNodeStyleSetAspectRatio(root_child0, 1);
  CSSNodeInsertChild(root, root_child0, 0);

  CSSNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(0, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, CSSNodeLayoutGetTop(root_child0));
  ASSERT_EQ(100, CSSNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(100, CSSNodeLayoutGetHeight(root_child0));

  CSSNodeFreeRecursive(root);
}

TEST(CSSLayoutTest, aspect_ratio_basis) {
  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetAlignItems(root, YGAlignFlexStart);
  CSSNodeStyleSetWidth(root, 100);
  CSSNodeStyleSetHeight(root, 100);

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeStyleSetFlexBasis(root_child0, 50);
  CSSNodeStyleSetAspectRatio(root_child0, 1);
  CSSNodeInsertChild(root, root_child0, 0);

  CSSNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(0, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, CSSNodeLayoutGetTop(root_child0));
  ASSERT_EQ(50, CSSNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, CSSNodeLayoutGetHeight(root_child0));

  CSSNodeFreeRecursive(root);
}

TEST(CSSLayoutTest, aspect_ratio_absolute_layout_width_defined) {
  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetWidth(root, 100);
  CSSNodeStyleSetHeight(root, 100);

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeStyleSetPositionType(root_child0, YGPositionTypeAbsolute);
  CSSNodeStyleSetPosition(root_child0, YGEdgeLeft, 0);
  CSSNodeStyleSetPosition(root_child0, YGEdgeTop, 0);
  CSSNodeStyleSetWidth(root_child0, 50);
  CSSNodeStyleSetAspectRatio(root_child0, 1);
  CSSNodeInsertChild(root, root_child0, 0);

  CSSNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(0, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, CSSNodeLayoutGetTop(root_child0));
  ASSERT_EQ(50, CSSNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, CSSNodeLayoutGetHeight(root_child0));

  CSSNodeFreeRecursive(root);
}

TEST(CSSLayoutTest, aspect_ratio_absolute_layout_height_defined) {
  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetWidth(root, 100);
  CSSNodeStyleSetHeight(root, 100);

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeStyleSetPositionType(root_child0, YGPositionTypeAbsolute);
  CSSNodeStyleSetPosition(root_child0, YGEdgeLeft, 0);
  CSSNodeStyleSetPosition(root_child0, YGEdgeTop, 0);
  CSSNodeStyleSetHeight(root_child0, 50);
  CSSNodeStyleSetAspectRatio(root_child0, 1);
  CSSNodeInsertChild(root, root_child0, 0);

  CSSNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(0, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, CSSNodeLayoutGetTop(root_child0));
  ASSERT_EQ(50, CSSNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, CSSNodeLayoutGetHeight(root_child0));

  CSSNodeFreeRecursive(root);
}

TEST(CSSLayoutTest, aspect_ratio_with_max_cross_defined) {
  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetAlignItems(root, YGAlignFlexStart);
  CSSNodeStyleSetWidth(root, 100);
  CSSNodeStyleSetHeight(root, 100);

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeStyleSetHeight(root_child0, 50);
  CSSNodeStyleSetMaxWidth(root_child0, 40);
  CSSNodeStyleSetAspectRatio(root_child0, 1);
  CSSNodeInsertChild(root, root_child0, 0);

  CSSNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(0, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, CSSNodeLayoutGetTop(root_child0));
  ASSERT_EQ(40, CSSNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, CSSNodeLayoutGetHeight(root_child0));

  CSSNodeFreeRecursive(root);
}

TEST(CSSLayoutTest, aspect_ratio_with_max_main_defined) {
  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetAlignItems(root, YGAlignFlexStart);
  CSSNodeStyleSetWidth(root, 100);
  CSSNodeStyleSetHeight(root, 100);

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeStyleSetWidth(root_child0, 50);
  CSSNodeStyleSetMaxHeight(root_child0, 40);
  CSSNodeStyleSetAspectRatio(root_child0, 1);
  CSSNodeInsertChild(root, root_child0, 0);

  CSSNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(0, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, CSSNodeLayoutGetTop(root_child0));
  ASSERT_EQ(50, CSSNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(40, CSSNodeLayoutGetHeight(root_child0));

  CSSNodeFreeRecursive(root);
}

TEST(CSSLayoutTest, aspect_ratio_with_min_cross_defined) {
  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetAlignItems(root, YGAlignFlexStart);
  CSSNodeStyleSetWidth(root, 100);
  CSSNodeStyleSetHeight(root, 100);

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeStyleSetHeight(root_child0, 30);
  CSSNodeStyleSetMinWidth(root_child0, 40);
  CSSNodeStyleSetAspectRatio(root_child0, 1);
  CSSNodeInsertChild(root, root_child0, 0);

  CSSNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(0, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, CSSNodeLayoutGetTop(root_child0));
  ASSERT_EQ(40, CSSNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(30, CSSNodeLayoutGetHeight(root_child0));

  CSSNodeFreeRecursive(root);
}

TEST(CSSLayoutTest, aspect_ratio_with_min_main_defined) {
  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetAlignItems(root, YGAlignFlexStart);
  CSSNodeStyleSetWidth(root, 100);
  CSSNodeStyleSetHeight(root, 100);

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeStyleSetWidth(root_child0, 30);
  CSSNodeStyleSetMinHeight(root_child0, 40);
  CSSNodeStyleSetAspectRatio(root_child0, 1);
  CSSNodeInsertChild(root, root_child0, 0);

  CSSNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(0, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, CSSNodeLayoutGetTop(root_child0));
  ASSERT_EQ(30, CSSNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(40, CSSNodeLayoutGetHeight(root_child0));

  CSSNodeFreeRecursive(root);
}

TEST(CSSLayoutTest, aspect_ratio_double_cross) {
  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetAlignItems(root, YGAlignFlexStart);
  CSSNodeStyleSetWidth(root, 100);
  CSSNodeStyleSetHeight(root, 100);

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeStyleSetHeight(root_child0, 50);
  CSSNodeStyleSetAspectRatio(root_child0, 2);
  CSSNodeInsertChild(root, root_child0, 0);

  CSSNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(0, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, CSSNodeLayoutGetTop(root_child0));
  ASSERT_EQ(100, CSSNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, CSSNodeLayoutGetHeight(root_child0));

  CSSNodeFreeRecursive(root);
}

TEST(CSSLayoutTest, aspect_ratio_half_cross) {
  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetAlignItems(root, YGAlignFlexStart);
  CSSNodeStyleSetWidth(root, 100);
  CSSNodeStyleSetHeight(root, 100);

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeStyleSetHeight(root_child0, 100);
  CSSNodeStyleSetAspectRatio(root_child0, 0.5);
  CSSNodeInsertChild(root, root_child0, 0);

  CSSNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(0, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, CSSNodeLayoutGetTop(root_child0));
  ASSERT_EQ(50, CSSNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(100, CSSNodeLayoutGetHeight(root_child0));

  CSSNodeFreeRecursive(root);
}

TEST(CSSLayoutTest, aspect_ratio_double_main) {
  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetAlignItems(root, YGAlignFlexStart);
  CSSNodeStyleSetWidth(root, 100);
  CSSNodeStyleSetHeight(root, 100);

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeStyleSetWidth(root_child0, 50);
  CSSNodeStyleSetAspectRatio(root_child0, 2);
  CSSNodeInsertChild(root, root_child0, 0);

  CSSNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(0, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, CSSNodeLayoutGetTop(root_child0));
  ASSERT_EQ(50, CSSNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(100, CSSNodeLayoutGetHeight(root_child0));

  CSSNodeFreeRecursive(root);
}

TEST(CSSLayoutTest, aspect_ratio_half_main) {
  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetAlignItems(root, YGAlignFlexStart);
  CSSNodeStyleSetWidth(root, 100);
  CSSNodeStyleSetHeight(root, 100);

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeStyleSetWidth(root_child0, 100);
  CSSNodeStyleSetAspectRatio(root_child0, 0.5);
  CSSNodeInsertChild(root, root_child0, 0);

  CSSNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(0, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, CSSNodeLayoutGetTop(root_child0));
  ASSERT_EQ(100, CSSNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, CSSNodeLayoutGetHeight(root_child0));

  CSSNodeFreeRecursive(root);
}

TEST(CSSLayoutTest, aspect_ratio_with_measure_func) {
  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetAlignItems(root, YGAlignFlexStart);
  CSSNodeStyleSetWidth(root, 100);
  CSSNodeStyleSetHeight(root, 100);

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeSetMeasureFunc(root_child0, _measure);
  CSSNodeStyleSetAspectRatio(root_child0, 1);
  CSSNodeInsertChild(root, root_child0, 0);

  CSSNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(0, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, CSSNodeLayoutGetTop(root_child0));
  ASSERT_EQ(50, CSSNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(50, CSSNodeLayoutGetHeight(root_child0));

  CSSNodeFreeRecursive(root);
}
