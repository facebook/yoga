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

static YGSize _measure(YGNodeRef node,
                       float width,
                       YGMeasureMode widthMode,
                       float height,
                       YGMeasureMode heightMode) {
  int *measureCount = (int *) YGNodeGetContext(node);
  if (measureCount) {
    (*measureCount)++;
  }

  return YGSize{
      .width = 10, .height = 10,
  };
}

TEST(YogaTest, dont_measure_single_grow_shrink_child) {
  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetWidth(root, 100);
  YGNodeStyleSetHeight(root, 100);

  int measureCount = 0;

  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeSetContext(root_child0, &measureCount);
  YGNodeSetMeasureFunc(root_child0, _measure);
  YGNodeStyleSetFlexGrow(root_child0, 1);
  YGNodeStyleSetFlexShrink(root_child0, 1);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(0, measureCount);

  YGNodeFreeRecursive(root);
}

TEST(YogaTest, measure_absolute_child_with_no_constraints) {
  const YGNodeRef root = YGNodeNew();

  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeInsertChild(root, root_child0, 0);

  int measureCount = 0;

  const YGNodeRef root_child0_child0 = YGNodeNew();
  YGNodeStyleSetPositionType(root_child0_child0, YGPositionTypeAbsolute);
  YGNodeSetContext(root_child0_child0, &measureCount);
  YGNodeSetMeasureFunc(root_child0_child0, _measure);
  YGNodeInsertChild(root_child0, root_child0_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(1, measureCount);

  YGNodeFreeRecursive(root);
}

TEST(YogaTest, dont_measure_when_min_equals_max) {
  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetAlignItems(root, YGAlignFlexStart);
  YGNodeStyleSetWidth(root, 100);
  YGNodeStyleSetHeight(root, 100);

  int measureCount = 0;

  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeSetContext(root_child0, &measureCount);
  YGNodeSetMeasureFunc(root_child0, _measure);
  YGNodeStyleSetMinWidth(root_child0, 10);
  YGNodeStyleSetMaxWidth(root_child0, 10);
  YGNodeStyleSetMinHeight(root_child0, 10);
  YGNodeStyleSetMaxHeight(root_child0, 10);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(0, measureCount);
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(10, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(10, YGNodeLayoutGetHeight(root_child0));

  YGNodeFreeRecursive(root);
}

TEST(YogaTest, dont_measure_when_min_equals_max_percentages) {
  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetAlignItems(root, YGAlignFlexStart);
  YGNodeStyleSetWidth(root, 100);
  YGNodeStyleSetHeight(root, 100);

  int measureCount = 0;

  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeSetContext(root_child0, &measureCount);
  YGNodeSetMeasureFunc(root_child0, _measure);
  YGNodeStyleSetMinWidthPercent(root_child0, 10);
  YGNodeStyleSetMaxWidthPercent(root_child0, 10);
  YGNodeStyleSetMinHeightPercent(root_child0, 10);
  YGNodeStyleSetMaxHeightPercent(root_child0, 10);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(0, measureCount);
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(10, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(10, YGNodeLayoutGetHeight(root_child0));

  YGNodeFreeRecursive(root);
}

TEST(YogaTest, dont_measure_when_min_equals_max_mixed) {
  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetAlignItems(root, YGAlignFlexStart);
  YGNodeStyleSetWidth(root, 100);
  YGNodeStyleSetHeight(root, 100);

  int measureCount = 0;

  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeSetContext(root_child0, &measureCount);
  YGNodeSetMeasureFunc(root_child0, _measure);
  YGNodeStyleSetMinWidthPercent(root_child0, 10);
  YGNodeStyleSetMaxWidthPercent(root_child0, 10);
  YGNodeStyleSetMinHeight(root_child0, 10);
  YGNodeStyleSetMaxHeight(root_child0, 10);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(0, measureCount);
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(10, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(10, YGNodeLayoutGetHeight(root_child0));

  YGNodeFreeRecursive(root);
}

TEST(YogaTest, dont_measure_when_min_equals_max_mixed_2) {
  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetAlignItems(root, YGAlignFlexStart);
  YGNodeStyleSetWidth(root, 100);
  YGNodeStyleSetHeight(root, 100);

  int measureCount = 0;

  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeSetContext(root_child0, &measureCount);
  YGNodeSetMeasureFunc(root_child0, _measure);
  YGNodeStyleSetMinWidth(root_child0, 10);
  YGNodeStyleSetMaxWidth(root_child0, 10);
  YGNodeStyleSetMinHeightPercent(root_child0, 10);
  YGNodeStyleSetMaxHeightPercent(root_child0, 10);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(0, measureCount);
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(10, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(10, YGNodeLayoutGetHeight(root_child0));

  YGNodeFreeRecursive(root);
}

#if GTEST_HAS_DEATH_TEST
TEST(YogaTest, cannot_add_child_to_node_with_measure_func) {
  const YGNodeRef root = YGNodeNew();
  YGNodeSetMeasureFunc(root, _measure);

  const YGNodeRef root_child0 = YGNodeNew();
  ASSERT_DEATH(YGNodeInsertChild(root, root_child0, 0), "Cannot add child.*");
  YGNodeFree(root_child0);
  YGNodeFreeRecursive(root);
}

TEST(YogaTest, cannot_add_nonnull_measure_func_to_non_leaf_node) {
  const YGNodeRef root = YGNodeNew();
  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeInsertChild(root, root_child0, 0);

  ASSERT_DEATH(YGNodeSetMeasureFunc(root, _measure), "Cannot set measure function.*");
  YGNodeFreeRecursive(root);
}

TEST(YogaTest, can_nullify_measure_func_on_any_node) {
  const YGNodeRef root = YGNodeNew();
  YGNodeInsertChild(root, YGNodeNew(), 0);

  YGNodeSetMeasureFunc(root, NULL);
  ASSERT_TRUE(YGNodeGetMeasureFunc(root) == NULL);
  YGNodeFreeRecursive(root);
}

#endif
