/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#include <CSSLayout/Yoga.h>
#include <gtest/gtest.h>

static YGSize _measureMax(YGNodeRef node,
                        float width,
                        YGMeasureMode widthMode,
                        float height,
                        YGMeasureMode heightMode) {

  int *measureCount = (int *)YGNodeGetContext(node);
  (*measureCount)++;

  return YGSize {
      .width = widthMode == YGMeasureModeUndefined ? 10 : width,
      .height = heightMode == YGMeasureModeUndefined ? 10 : height,
  };
}

static YGSize _measureMin(YGNodeRef node,
                        float width,
                        YGMeasureMode widthMode,
                        float height,
                        YGMeasureMode heightMode) {

  int *measureCount = (int *)YGNodeGetContext(node);
  *measureCount = *measureCount + 1;
  return YGSize {
      .width = widthMode == YGMeasureModeUndefined || (widthMode == YGMeasureModeAtMost && width > 10) ? 10 : width,
      .height = heightMode == YGMeasureModeUndefined || (heightMode == YGMeasureModeAtMost && height > 10) ? 10 : height,
  };
}

TEST(YogaTest, measure_once_single_flexible_child) {
  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetFlexDirection(root, YGFlexDirectionRow);
  YGNodeStyleSetAlignItems(root, YGAlignFlexStart);
  YGNodeStyleSetWidth(root, 100);
  YGNodeStyleSetHeight(root, 100);

  const YGNodeRef root_child0 = YGNodeNew();
  int measureCount = 0;
  YGNodeSetContext(root_child0, &measureCount);
  YGNodeSetMeasureFunc(root_child0, _measureMax);
  YGNodeStyleSetFlexGrow(root_child0, 1);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(1, measureCount);

  YGNodeFreeRecursive(root);
}

TEST(YogaTest, remeasure_with_same_exact_width_larger_than_needed_height) {
  const YGNodeRef root = YGNodeNew();

  const YGNodeRef root_child0 = YGNodeNew();
  int measureCount = 0;
  YGNodeSetContext(root_child0, &measureCount);
  YGNodeSetMeasureFunc(root_child0, _measureMin);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, 100, 100, YGDirectionLTR);
  YGNodeCalculateLayout(root, 100, 50, YGDirectionLTR);

  ASSERT_EQ(1, measureCount);

  YGNodeFreeRecursive(root);
}

TEST(YogaTest, remeasure_with_same_atmost_width_larger_than_needed_height) {
  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetAlignItems(root, YGAlignFlexStart);

  const YGNodeRef root_child0 = YGNodeNew();
  int measureCount = 0;
  YGNodeSetContext(root_child0, &measureCount);
  YGNodeSetMeasureFunc(root_child0, _measureMin);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, 100, 100, YGDirectionLTR);
  YGNodeCalculateLayout(root, 100, 50, YGDirectionLTR);

  ASSERT_EQ(1, measureCount);

  YGNodeFreeRecursive(root);
}

TEST(YogaTest, remeasure_with_computed_width_larger_than_needed_height) {
  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetAlignItems(root, YGAlignFlexStart);

  const YGNodeRef root_child0 = YGNodeNew();
  int measureCount = 0;
  YGNodeSetContext(root_child0, &measureCount);
  YGNodeSetMeasureFunc(root_child0, _measureMin);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, 100, 100, YGDirectionLTR);
  YGNodeStyleSetAlignItems(root, YGAlignStretch);
  YGNodeCalculateLayout(root, 10, 50, YGDirectionLTR);

  ASSERT_EQ(1, measureCount);

  YGNodeFreeRecursive(root);
}

TEST(YogaTest, remeasure_with_atmost_computed_width_undefined_height) {
  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetAlignItems(root, YGAlignFlexStart);

  const YGNodeRef root_child0 = YGNodeNew();
  int measureCount = 0;
  YGNodeSetContext(root_child0, &measureCount);
  YGNodeSetMeasureFunc(root_child0, _measureMin);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, 100, YGUndefined, YGDirectionLTR);
  YGNodeCalculateLayout(root, 10, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(1, measureCount);

  YGNodeFreeRecursive(root);
}
