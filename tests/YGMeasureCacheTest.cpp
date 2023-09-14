/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>
#include <yoga/Yoga.h>

static YGSize _measureMax(
    YGNodeConstRef node,
    float width,
    YGMeasureMode widthMode,
    float height,
    YGMeasureMode heightMode) {
  int* measureCount = (int*)YGNodeGetContext(node);
  (*measureCount)++;

  return YGSize{
      widthMode == YGMeasureModeUndefined ? 10 : width,
      heightMode == YGMeasureModeUndefined ? 10 : height,
  };
}

static YGSize _measureMin(
    YGNodeConstRef node,
    float width,
    YGMeasureMode widthMode,
    float height,
    YGMeasureMode heightMode) {
  int* measureCount = (int*)YGNodeGetContext(node);
  *measureCount = *measureCount + 1;
  return YGSize{
      widthMode == YGMeasureModeUndefined ||
              (widthMode == YGMeasureModeAtMost && width > 10)
          ? 10
          : width,
      heightMode == YGMeasureModeUndefined ||
              (heightMode == YGMeasureModeAtMost && height > 10)
          ? 10
          : height,
  };
}

static YGSize _measure_84_49(
    YGNodeConstRef node,
    float /*width*/,
    YGMeasureMode /*widthMode*/,
    float /*height*/,
    YGMeasureMode /*heightMode*/) {
  int* measureCount = (int*)YGNodeGetContext(node);
  if (measureCount) {
    (*measureCount)++;
  }

  return YGSize{84.f, 49.f};
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

TEST(
    YogaTest,
    remeasure_with_already_measured_value_smaller_but_still_float_equal) {
  int measureCount = 0;

  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetWidth(root, 288.f);
  YGNodeStyleSetHeight(root, 288.f);
  YGNodeStyleSetFlexDirection(root, YGFlexDirectionRow);

  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeStyleSetPadding(root_child0, YGEdgeAll, 2.88f);
  YGNodeStyleSetFlexDirection(root_child0, YGFlexDirectionRow);
  YGNodeInsertChild(root, root_child0, 0);

  const YGNodeRef root_child0_child0 = YGNodeNew();
  YGNodeSetContext(root_child0_child0, &measureCount);
  YGNodeSetMeasureFunc(root_child0_child0, _measure_84_49);
  YGNodeInsertChild(root_child0, root_child0_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  YGNodeFreeRecursive(root);

  ASSERT_EQ(1, measureCount);
}
