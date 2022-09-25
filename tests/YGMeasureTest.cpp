/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>
#include <yoga/YGNode.h>
#include <yoga/Yoga.h>

static YGSize _measure(
    YGNodeRef node,
    float width,
    YGMeasureMode widthMode,
    float height,
    YGMeasureMode heightMode) {
  int* measureCount = (int*) node->getContext();
  if (measureCount) {
    (*measureCount)++;
  }

  return YGSize{
      .width = 10,
      .height = 10,
  };
}

static YGSize _simulate_wrapping_text(
    YGNodeRef node,
    float width,
    YGMeasureMode widthMode,
    float height,
    YGMeasureMode heightMode) {
  if (widthMode == YGMeasureModeUndefined || width >= 68) {
    return YGSize{.width = 68, .height = 16};
  }

  return YGSize{
      .width = 50,
      .height = 32,
  };
}

static YGSize _measure_assert_negative(
    YGNodeRef node,
    float width,
    YGMeasureMode widthMode,
    float height,
    YGMeasureMode heightMode) {
  EXPECT_GE(width, 0);
  EXPECT_GE(height, 0);

  return YGSize{
      .width = 0,
      .height = 0,
  };
}

TEST(YogaTest, dont_measure_single_grow_shrink_child) {
  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetWidth(root, 100);
  YGNodeStyleSetHeight(root, 100);

  int measureCount = 0;

  const YGNodeRef root_child0 = YGNodeNew();
  root_child0->setContext(&measureCount);
  root_child0->setMeasureFunc(_measure);
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
  root_child0_child0->setContext(&measureCount);
  root_child0_child0->setMeasureFunc(_measure);
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
  root_child0->setContext(&measureCount);
  root_child0->setMeasureFunc(_measure);
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
  root_child0->setContext(&measureCount);
  root_child0->setMeasureFunc(_measure);
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

TEST(YogaTest, measure_nodes_with_margin_auto_and_stretch) {
  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetWidth(root, 500);
  YGNodeStyleSetHeight(root, 500);

  const YGNodeRef root_child0 = YGNodeNew();
  root_child0->setMeasureFunc(_measure);
  YGNodeStyleSetMarginAuto(root_child0, YGEdgeLeft);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  EXPECT_EQ(490, YGNodeLayoutGetLeft(root_child0));
  EXPECT_EQ(0, YGNodeLayoutGetTop(root_child0));
  EXPECT_EQ(10, YGNodeLayoutGetWidth(root_child0));
  EXPECT_EQ(10, YGNodeLayoutGetHeight(root_child0));

  YGNodeFreeRecursive(root);
}

TEST(YogaTest, dont_measure_when_min_equals_max_mixed_width_percent) {
  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetAlignItems(root, YGAlignFlexStart);
  YGNodeStyleSetWidth(root, 100);
  YGNodeStyleSetHeight(root, 100);

  int measureCount = 0;

  const YGNodeRef root_child0 = YGNodeNew();
  root_child0->setContext(&measureCount);
  root_child0->setMeasureFunc(_measure);
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

TEST(YogaTest, dont_measure_when_min_equals_max_mixed_height_percent) {
  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetAlignItems(root, YGAlignFlexStart);
  YGNodeStyleSetWidth(root, 100);
  YGNodeStyleSetHeight(root, 100);

  int measureCount = 0;

  const YGNodeRef root_child0 = YGNodeNew();
  root_child0->setContext(&measureCount);
  root_child0->setMeasureFunc(_measure);
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

TEST(YogaTest, measure_enough_size_should_be_in_single_line) {
  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetWidth(root, 100);

  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeStyleSetAlignSelf(root_child0, YGAlignFlexStart);
  root_child0->setMeasureFunc(_simulate_wrapping_text);

  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(68, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(16, YGNodeLayoutGetHeight(root_child0));

  YGNodeFreeRecursive(root);
}

TEST(YogaTest, measure_not_enough_size_should_wrap) {
  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetWidth(root, 55);

  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeStyleSetAlignSelf(root_child0, YGAlignFlexStart);
  //  YGNodeSetMeasureFunc(root_child0, _simulate_wrapping_text);
  root_child0->setMeasureFunc(_simulate_wrapping_text);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(32, YGNodeLayoutGetHeight(root_child0));

  YGNodeFreeRecursive(root);
}

TEST(YogaTest, measure_zero_space_should_grow) {
  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetHeight(root, 200);
  YGNodeStyleSetFlexDirection(root, YGFlexDirectionColumn);
  YGNodeStyleSetFlexGrow(root, 0);

  int measureCount = 0;

  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeStyleSetFlexDirection(root_child0, YGFlexDirectionColumn);
  YGNodeStyleSetPadding(root_child0, YGEdgeAll, 100);
  root_child0->setContext(&measureCount);
  root_child0->setMeasureFunc(_measure);

  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, 282, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(282, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));

  YGNodeFreeRecursive(root);
}

TEST(YogaTest, measure_flex_direction_row_and_padding) {
  const YGConfigRef config = YGConfigNew();

  const YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexDirection(root, YGFlexDirectionRow);
  YGNodeStyleSetPadding(root, YGEdgeLeft, 25);
  YGNodeStyleSetPadding(root, YGEdgeTop, 25);
  YGNodeStyleSetPadding(root, YGEdgeRight, 25);
  YGNodeStyleSetPadding(root, YGEdgeBottom, 25);
  YGNodeStyleSetWidth(root, 50);
  YGNodeStyleSetHeight(root, 50);

  const YGNodeRef root_child0 = YGNodeNewWithConfig(config);
  root_child0->setMeasureFunc(_simulate_wrapping_text);
  //  YGNodeSetMeasureFunc(root_child0, _simulate_wrapping_text);
  YGNodeInsertChild(root, root_child0, 0);

  const YGNodeRef root_child1 = YGNodeNewWithConfig(config);
  YGNodeStyleSetWidth(root_child1, 5);
  YGNodeStyleSetHeight(root_child1, 5);
  YGNodeInsertChild(root, root_child1, 1);
  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(25, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(25, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(75, YGNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(25, YGNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(5, YGNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(5, YGNodeLayoutGetHeight(root_child1));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}

TEST(YogaTest, measure_flex_direction_column_and_padding) {
  const YGConfigRef config = YGConfigNew();

  const YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetMargin(root, YGEdgeTop, 20);
  YGNodeStyleSetPadding(root, YGEdgeAll, 25);
  YGNodeStyleSetWidth(root, 50);
  YGNodeStyleSetHeight(root, 50);

  const YGNodeRef root_child0 = YGNodeNewWithConfig(config);
  root_child0->setMeasureFunc(_simulate_wrapping_text);
  //  YGNodeSetMeasureFunc(root_child0, _simulate_wrapping_text);
  YGNodeInsertChild(root, root_child0, 0);

  const YGNodeRef root_child1 = YGNodeNewWithConfig(config);
  YGNodeStyleSetWidth(root_child1, 5);
  YGNodeStyleSetHeight(root_child1, 5);
  YGNodeInsertChild(root, root_child1, 1);
  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(20, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(25, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(25, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(32, YGNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(25, YGNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(57, YGNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(5, YGNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(5, YGNodeLayoutGetHeight(root_child1));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}

TEST(YogaTest, measure_flex_direction_row_no_padding) {
  const YGConfigRef config = YGConfigNew();

  const YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexDirection(root, YGFlexDirectionRow);
  YGNodeStyleSetMargin(root, YGEdgeTop, 20);
  YGNodeStyleSetWidth(root, 50);
  YGNodeStyleSetHeight(root, 50);

  const YGNodeRef root_child0 = YGNodeNewWithConfig(config);
  //  YGNodeSetMeasureFunc(root_child0, _simulate_wrapping_text);
  root_child0->setMeasureFunc(_simulate_wrapping_text);
  YGNodeInsertChild(root, root_child0, 0);

  const YGNodeRef root_child1 = YGNodeNewWithConfig(config);
  YGNodeStyleSetWidth(root_child1, 5);
  YGNodeStyleSetHeight(root_child1, 5);
  YGNodeInsertChild(root, root_child1, 1);
  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(20, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(5, YGNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(5, YGNodeLayoutGetHeight(root_child1));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}

TEST(YogaTest, measure_flex_direction_row_no_padding_align_items_flexstart) {
  const YGConfigRef config = YGConfigNew();

  const YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexDirection(root, YGFlexDirectionRow);
  YGNodeStyleSetMargin(root, YGEdgeTop, 20);
  YGNodeStyleSetWidth(root, 50);
  YGNodeStyleSetHeight(root, 50);
  YGNodeStyleSetAlignItems(root, YGAlignFlexStart);

  const YGNodeRef root_child0 = YGNodeNewWithConfig(config);
  root_child0->setMeasureFunc(_simulate_wrapping_text);
  YGNodeInsertChild(root, root_child0, 0);

  const YGNodeRef root_child1 = YGNodeNewWithConfig(config);
  YGNodeStyleSetWidth(root_child1, 5);
  YGNodeStyleSetHeight(root_child1, 5);
  YGNodeInsertChild(root, root_child1, 1);
  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(20, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(32, YGNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(5, YGNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(5, YGNodeLayoutGetHeight(root_child1));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}

TEST(YogaTest, measure_with_fixed_size) {
  const YGConfigRef config = YGConfigNew();

  const YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetMargin(root, YGEdgeTop, 20);
  YGNodeStyleSetPadding(root, YGEdgeAll, 25);
  YGNodeStyleSetWidth(root, 50);
  YGNodeStyleSetHeight(root, 50);

  const YGNodeRef root_child0 = YGNodeNewWithConfig(config);
  root_child0->setMeasureFunc(_simulate_wrapping_text);
  YGNodeStyleSetWidth(root_child0, 10);
  YGNodeStyleSetHeight(root_child0, 10);
  YGNodeInsertChild(root, root_child0, 0);

  const YGNodeRef root_child1 = YGNodeNewWithConfig(config);
  YGNodeStyleSetWidth(root_child1, 5);
  YGNodeStyleSetHeight(root_child1, 5);
  YGNodeInsertChild(root, root_child1, 1);
  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(20, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(25, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(25, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(10, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(10, YGNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(25, YGNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(35, YGNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(5, YGNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(5, YGNodeLayoutGetHeight(root_child1));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}

TEST(YogaTest, measure_with_flex_shrink) {
  const YGConfigRef config = YGConfigNew();

  const YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetMargin(root, YGEdgeTop, 20);
  YGNodeStyleSetPadding(root, YGEdgeAll, 25);
  YGNodeStyleSetWidth(root, 50);
  YGNodeStyleSetHeight(root, 50);

  const YGNodeRef root_child0 = YGNodeNewWithConfig(config);
  root_child0->setMeasureFunc(_simulate_wrapping_text);
  YGNodeStyleSetFlexShrink(root_child0, 1);
  YGNodeInsertChild(root, root_child0, 0);

  const YGNodeRef root_child1 = YGNodeNewWithConfig(config);
  YGNodeStyleSetWidth(root_child1, 5);
  YGNodeStyleSetHeight(root_child1, 5);
  YGNodeInsertChild(root, root_child1, 1);
  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(20, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(25, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(25, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(25, YGNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(25, YGNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(5, YGNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(5, YGNodeLayoutGetHeight(root_child1));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}

TEST(YogaTest, measure_no_padding) {
  const YGConfigRef config = YGConfigNew();

  const YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetMargin(root, YGEdgeTop, 20);
  YGNodeStyleSetWidth(root, 50);
  YGNodeStyleSetHeight(root, 50);

  const YGNodeRef root_child0 = YGNodeNewWithConfig(config);
  root_child0->setMeasureFunc(_simulate_wrapping_text);
  YGNodeStyleSetFlexShrink(root_child0, 1);
  YGNodeInsertChild(root, root_child0, 0);

  const YGNodeRef root_child1 = YGNodeNewWithConfig(config);
  YGNodeStyleSetWidth(root_child1, 5);
  YGNodeStyleSetHeight(root_child1, 5);
  YGNodeInsertChild(root, root_child1, 1);
  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(20, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(32, YGNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(32, YGNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(5, YGNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(5, YGNodeLayoutGetHeight(root_child1));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}

#if GTEST_HAS_DEATH_TEST
TEST(YogaDeathTest, cannot_add_child_to_node_with_measure_func) {
  const YGNodeRef root = YGNodeNew();
  root->setMeasureFunc(_measure);

  const YGNodeRef root_child0 = YGNodeNew();
  ASSERT_THROW(YGNodeInsertChild(root, root_child0, 0), std::logic_error);
  YGNodeFree(root_child0);
  YGNodeFreeRecursive(root);
}

TEST(YogaDeathTest, cannot_add_nonnull_measure_func_to_non_leaf_node) {
  const YGNodeRef root = YGNodeNew();
  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeInsertChild(root, root_child0, 0);
  ASSERT_THROW(root->setMeasureFunc(_measure), std::logic_error);
  YGNodeFreeRecursive(root);
}

#endif

TEST(YogaTest, can_nullify_measure_func_on_any_node) {
  const YGNodeRef root = YGNodeNew();
  YGNodeInsertChild(root, YGNodeNew(), 0);
  root->setMeasureFunc(nullptr);
  ASSERT_TRUE(!root->hasMeasureFunc());
  YGNodeFreeRecursive(root);
}

TEST(YogaTest, cant_call_negative_measure) {
  const YGConfigRef config = YGConfigNew();

  const YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexDirection(root, YGFlexDirectionColumn);
  YGNodeStyleSetWidth(root, 50);
  YGNodeStyleSetHeight(root, 10);

  const YGNodeRef root_child0 = YGNodeNewWithConfig(config);
  root_child0->setMeasureFunc(_measure_assert_negative);
  YGNodeStyleSetMargin(root_child0, YGEdgeTop, 20);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  YGNodeFreeRecursive(root);
  YGConfigFree(config);
}

TEST(YogaTest, cant_call_negative_measure_horizontal) {
  const YGConfigRef config = YGConfigNew();

  const YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexDirection(root, YGFlexDirectionRow);
  YGNodeStyleSetWidth(root, 10);
  YGNodeStyleSetHeight(root, 20);

  const YGNodeRef root_child0 = YGNodeNewWithConfig(config);
  root_child0->setMeasureFunc(_measure_assert_negative);
  YGNodeStyleSetMargin(root_child0, YGEdgeStart, 20);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  YGNodeFreeRecursive(root);
  YGConfigFree(config);
}

static YGSize _measure_90_10(
    YGNodeRef node,
    float width,
    YGMeasureMode widthMode,
    float height,
    YGMeasureMode heightMode) {

  return YGSize{
      .width = 90,
      .height = 10,
  };
}

static YGSize _measure_100_100(
    YGNodeRef node,
    float width,
    YGMeasureMode widthMode,
    float height,
    YGMeasureMode heightMode) {

  return YGSize{
      .width = 100,
      .height = 100,
  };
}

TEST(YogaTest, percent_with_text_node) {
  const YGConfigRef config = YGConfigNew();

  const YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexDirection(root, YGFlexDirectionRow);
  YGNodeStyleSetJustifyContent(root, YGJustifySpaceBetween);
  YGNodeStyleSetAlignItems(root, YGAlignCenter);
  YGNodeStyleSetWidth(root, 100);
  YGNodeStyleSetHeight(root, 80);

  const YGNodeRef root_child0 = YGNodeNewWithConfig(config);
  YGNodeInsertChild(root, root_child0, 0);

  const YGNodeRef root_child1 = YGNodeNewWithConfig(config);
  root_child1->setMeasureFunc(_measure_90_10);
  YGNodeStyleSetMaxWidthPercent(root_child1, 50);
  YGNodeStyleSetPaddingPercent(root_child1, YGEdgeTop, 50);
  YGNodeInsertChild(root, root_child1, 1);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(80, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(40, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(10, YGNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(60, YGNodeLayoutGetHeight(root_child1));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}

TEST(YogaTest, percent_margin_with_measure_func) {
  const YGConfigRef config = YGConfigNew();

  const YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexDirection(root, YGFlexDirectionRow);
  YGNodeStyleSetWidth(root, 500);
  YGNodeStyleSetHeight(root, 500);

  const YGNodeRef root_child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetWidth(root_child0, 100);
  YGNodeStyleSetHeight(root_child0, 100);
  YGNodeStyleSetMargin(root_child0, YGEdgeTop, 0);
  root_child0->setMeasureFunc(_measure_100_100);
  YGNodeInsertChild(root, root_child0, 0);

  const YGNodeRef root_child1 = YGNodeNewWithConfig(config);
  YGNodeStyleSetWidth(root_child1, 100);
  YGNodeStyleSetHeight(root_child1, 100);
  YGNodeStyleSetMargin(root_child1, YGEdgeTop, 100);
  root_child1->setMeasureFunc(_measure_100_100);
  YGNodeInsertChild(root, root_child1, 1);

  const YGNodeRef root_child2 = YGNodeNewWithConfig(config);
  YGNodeStyleSetWidth(root_child2, 100);
  YGNodeStyleSetHeight(root_child2, 100);
  YGNodeStyleSetMarginPercent(root_child2, YGEdgeTop, 10);
  root_child2->setMeasureFunc(_measure_100_100);
  YGNodeInsertChild(root, root_child2, 2);

  const YGNodeRef root_child3 = YGNodeNewWithConfig(config);
  YGNodeStyleSetWidth(root_child3, 100);
  YGNodeStyleSetHeight(root_child3, 100);
  YGNodeStyleSetMarginPercent(root_child3, YGEdgeTop, 20);
  root_child3->setMeasureFunc(_measure_100_100);
  YGNodeInsertChild(root, root_child3, 3);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(500, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(500, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(200, YGNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetHeight(root_child2));

  ASSERT_FLOAT_EQ(300, YGNodeLayoutGetLeft(root_child3));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetTop(root_child3));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetWidth(root_child3));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetHeight(root_child3));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}

TEST(YogaTest, percent_padding_with_measure_func) {
  const YGConfigRef config = YGConfigNew();

  const YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexDirection(root, YGFlexDirectionRow);
  YGNodeStyleSetAlignItems(root, YGAlignFlexStart);
  YGNodeStyleSetAlignContent(root, YGAlignFlexStart);
  YGNodeStyleSetWidth(root, 500);
  YGNodeStyleSetHeight(root, 500);

  const YGNodeRef root_child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetWidth(root_child0, 100);
  YGNodeStyleSetHeight(root_child0, 100);
  YGNodeStyleSetPadding(root_child0, YGEdgeTop, 0);
  root_child0->setMeasureFunc(_measure_100_100);
  YGNodeInsertChild(root, root_child0, 0);

  const YGNodeRef root_child1 = YGNodeNewWithConfig(config);
  YGNodeStyleSetWidth(root_child1, 100);
  YGNodeStyleSetHeight(root_child1, 100);
  YGNodeStyleSetPadding(root_child1, YGEdgeTop, 100);
  root_child1->setMeasureFunc(_measure_100_100);
  YGNodeInsertChild(root, root_child1, 1);

  const YGNodeRef root_child2 = YGNodeNewWithConfig(config);
  YGNodeStyleSetPaddingPercent(root_child2, YGEdgeTop, 10);
  root_child2->setMeasureFunc(_measure_100_100);
  YGNodeInsertChild(root, root_child2, 2);

  const YGNodeRef root_child3 = YGNodeNewWithConfig(config);
  YGNodeStyleSetPaddingPercent(root_child3, YGEdgeTop, 20);
  root_child3->setMeasureFunc(_measure_100_100);
  YGNodeInsertChild(root, root_child3, 3);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(500, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(500, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(200, YGNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(150, YGNodeLayoutGetHeight(root_child2));

  ASSERT_FLOAT_EQ(300, YGNodeLayoutGetLeft(root_child3));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child3));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetWidth(root_child3));
  ASSERT_FLOAT_EQ(200, YGNodeLayoutGetHeight(root_child3));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}

TEST(YogaTest, percent_padding_and_percent_margin_with_measure_func) {
  const YGConfigRef config = YGConfigNew();

  const YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexDirection(root, YGFlexDirectionRow);
  YGNodeStyleSetAlignItems(root, YGAlignFlexStart);
  YGNodeStyleSetAlignContent(root, YGAlignFlexStart);
  YGNodeStyleSetWidth(root, 500);
  YGNodeStyleSetHeight(root, 500);

  const YGNodeRef root_child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetWidth(root_child0, 100);
  YGNodeStyleSetHeight(root_child0, 100);
  YGNodeStyleSetPadding(root_child0, YGEdgeTop, 0);
  root_child0->setMeasureFunc(_measure_100_100);
  YGNodeInsertChild(root, root_child0, 0);

  const YGNodeRef root_child1 = YGNodeNewWithConfig(config);
  YGNodeStyleSetWidth(root_child1, 100);
  YGNodeStyleSetHeight(root_child1, 100);
  YGNodeStyleSetPadding(root_child1, YGEdgeTop, 100);
  root_child1->setMeasureFunc(_measure_100_100);
  YGNodeInsertChild(root, root_child1, 1);

  const YGNodeRef root_child2 = YGNodeNewWithConfig(config);
  YGNodeStyleSetPaddingPercent(root_child2, YGEdgeTop, 10);
  YGNodeStyleSetMarginPercent(root_child2, YGEdgeTop, 10);
  root_child2->setMeasureFunc(_measure_100_100);
  YGNodeInsertChild(root, root_child2, 2);

  const YGNodeRef root_child3 = YGNodeNewWithConfig(config);
  YGNodeStyleSetPaddingPercent(root_child3, YGEdgeTop, 20);
  YGNodeStyleSetMarginPercent(root_child3, YGEdgeTop, 20);
  root_child3->setMeasureFunc(_measure_100_100);
  YGNodeInsertChild(root, root_child3, 3);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(500, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(500, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(200, YGNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(150, YGNodeLayoutGetHeight(root_child2));

  ASSERT_FLOAT_EQ(300, YGNodeLayoutGetLeft(root_child3));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetTop(root_child3));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetWidth(root_child3));
  ASSERT_FLOAT_EQ(200, YGNodeLayoutGetHeight(root_child3));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}

static YGSize _measureCk_test_label_shrink_based_on_height(
    YGNodeRef node,
    float width,
    YGMeasureMode widthMode,
    float height,
    YGMeasureMode heightMode) {

  if (heightMode == YGMeasureModeAtMost) {
    return YGSize{
        .width = 290,
        .height = 103,
    };
  } else {
    return YGSize{
        .width = 290,
        .height = height,
    };
  }
}

TEST(YogaTest, margin_percent_with_measure_func) {
  const YGConfigRef config = YGConfigNew();

  const YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetWidth(root, 320);

  const YGNodeRef root_child0 = YGNodeNewWithConfig(config);
  YGNodeInsertChild(root, root_child0, 0);

  const YGNodeRef root_child0_child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetHeight(root_child0_child0, 450);
  YGNodeInsertChild(root_child0, root_child0_child0, 0);

  const YGNodeRef root_child0_child0_child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexDirection(root_child0_child0_child0, YGFlexDirectionRow);
  YGNodeStyleSetMarginPercent(root_child0_child0_child0, YGEdgeTop, 5);
  YGNodeInsertChild(root_child0_child0, root_child0_child0_child0, 0);

  const YGNodeRef root_child0_child0_child0_child0 =
      YGNodeNewWithConfig(config);
  YGNodeSetMeasureFunc(
      root_child0_child0_child0_child0,
      _measureCk_test_label_shrink_based_on_height);
  YGNodeInsertChild(
      root_child0_child0_child0, root_child0_child0_child0_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(320, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(450, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(320, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(450, YGNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0_child0));
  ASSERT_FLOAT_EQ(320, YGNodeLayoutGetWidth(root_child0_child0));
  ASSERT_FLOAT_EQ(450, YGNodeLayoutGetHeight(root_child0_child0));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0_child0_child0));
  ASSERT_FLOAT_EQ(16, YGNodeLayoutGetTop(root_child0_child0_child0));
  ASSERT_FLOAT_EQ(320, YGNodeLayoutGetWidth(root_child0_child0_child0));
  ASSERT_FLOAT_EQ(103, YGNodeLayoutGetHeight(root_child0_child0_child0));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0_child0_child0_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0_child0_child0_child0));
  ASSERT_FLOAT_EQ(290, YGNodeLayoutGetWidth(root_child0_child0_child0_child0));
  ASSERT_FLOAT_EQ(103, YGNodeLayoutGetHeight(root_child0_child0_child0_child0));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}
