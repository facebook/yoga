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

static CSSSize _measureMax(CSSNodeRef node,
                        float width,
                        YGMeasureMode widthMode,
                        float height,
                        YGMeasureMode heightMode) {

  int *measureCount = (int *)CSSNodeGetContext(node);
  (*measureCount)++;

  return CSSSize {
      .width = widthMode == YGMeasureModeUndefined ? 10 : width,
      .height = heightMode == YGMeasureModeUndefined ? 10 : height,
  };
}

static CSSSize _measureMin(CSSNodeRef node,
                        float width,
                        YGMeasureMode widthMode,
                        float height,
                        YGMeasureMode heightMode) {

  int *measureCount = (int *)CSSNodeGetContext(node);
  *measureCount = *measureCount + 1;
  return CSSSize {
      .width = widthMode == YGMeasureModeUndefined || (widthMode == YGMeasureModeAtMost && width > 10) ? 10 : width,
      .height = heightMode == YGMeasureModeUndefined || (heightMode == YGMeasureModeAtMost && height > 10) ? 10 : height,
  };
}

TEST(CSSLayoutTest, measure_once_single_flexible_child) {
  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetFlexDirection(root, YGFlexDirectionRow);
  CSSNodeStyleSetAlignItems(root, YGAlignFlexStart);
  CSSNodeStyleSetWidth(root, 100);
  CSSNodeStyleSetHeight(root, 100);

  const CSSNodeRef root_child0 = CSSNodeNew();
  int measureCount = 0;
  CSSNodeSetContext(root_child0, &measureCount);
  CSSNodeSetMeasureFunc(root_child0, _measureMax);
  CSSNodeStyleSetFlexGrow(root_child0, 1);
  CSSNodeInsertChild(root, root_child0, 0);

  CSSNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(1, measureCount);

  CSSNodeFreeRecursive(root);
}

TEST(CSSLayoutTest, remeasure_with_same_exact_width_larger_than_needed_height) {
  const CSSNodeRef root = CSSNodeNew();

  const CSSNodeRef root_child0 = CSSNodeNew();
  int measureCount = 0;
  CSSNodeSetContext(root_child0, &measureCount);
  CSSNodeSetMeasureFunc(root_child0, _measureMin);
  CSSNodeInsertChild(root, root_child0, 0);

  CSSNodeCalculateLayout(root, 100, 100, YGDirectionLTR);
  CSSNodeCalculateLayout(root, 100, 50, YGDirectionLTR);

  ASSERT_EQ(1, measureCount);

  CSSNodeFreeRecursive(root);
}

TEST(CSSLayoutTest, remeasure_with_same_atmost_width_larger_than_needed_height) {
  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetAlignItems(root, YGAlignFlexStart);

  const CSSNodeRef root_child0 = CSSNodeNew();
  int measureCount = 0;
  CSSNodeSetContext(root_child0, &measureCount);
  CSSNodeSetMeasureFunc(root_child0, _measureMin);
  CSSNodeInsertChild(root, root_child0, 0);

  CSSNodeCalculateLayout(root, 100, 100, YGDirectionLTR);
  CSSNodeCalculateLayout(root, 100, 50, YGDirectionLTR);

  ASSERT_EQ(1, measureCount);

  CSSNodeFreeRecursive(root);
}

TEST(CSSLayoutTest, remeasure_with_computed_width_larger_than_needed_height) {
  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetAlignItems(root, YGAlignFlexStart);

  const CSSNodeRef root_child0 = CSSNodeNew();
  int measureCount = 0;
  CSSNodeSetContext(root_child0, &measureCount);
  CSSNodeSetMeasureFunc(root_child0, _measureMin);
  CSSNodeInsertChild(root, root_child0, 0);

  CSSNodeCalculateLayout(root, 100, 100, YGDirectionLTR);
  CSSNodeStyleSetAlignItems(root, YGAlignStretch);
  CSSNodeCalculateLayout(root, 10, 50, YGDirectionLTR);

  ASSERT_EQ(1, measureCount);

  CSSNodeFreeRecursive(root);
}

TEST(CSSLayoutTest, remeasure_with_atmost_computed_width_undefined_height) {
  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetAlignItems(root, YGAlignFlexStart);

  const CSSNodeRef root_child0 = CSSNodeNew();
  int measureCount = 0;
  CSSNodeSetContext(root_child0, &measureCount);
  CSSNodeSetMeasureFunc(root_child0, _measureMin);
  CSSNodeInsertChild(root, root_child0, 0);

  CSSNodeCalculateLayout(root, 100, YGUndefined, YGDirectionLTR);
  CSSNodeCalculateLayout(root, 10, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(1, measureCount);

  CSSNodeFreeRecursive(root);
}
