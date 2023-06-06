/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>
#include <yoga/YGNode.h>
#include <yoga/Yoga.h>

static float _baselineFunc(
    YGNodeRef /*node*/,
    const float /*width*/,
    const float height) {
  return height / 2;
}

static YGSize _measure1(
    YGNodeRef /*node*/,
    float /*width*/,
    YGMeasureMode /*widthMode*/,
    float /*height*/,
    YGMeasureMode /*heightMode*/) {
  return YGSize{42, 50};
}

static YGSize _measure2(
    YGNodeRef /*node*/,
    float /*width*/,
    YGMeasureMode /*widthMode*/,
    float /*height*/,
    YGMeasureMode /*heightMode*/) {
  return YGSize{279, 126};
}

static YGNodeRef createYGNode(
    YGConfigRef config,
    YGFlexDirection direction,
    int width,
    int height,
    bool alignBaseline) {
  const YGNodeRef node = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexDirection(node, direction);
  if (alignBaseline) {
    YGNodeStyleSetAlignItems(node, YGAlignBaseline);
  }
  YGNodeStyleSetWidth(node, (float) width);
  YGNodeStyleSetHeight(node, (float) height);
  return node;
}

// Test case for bug in T32999822
TEST(YogaTest, align_baseline_parent_ht_not_specified) {
  YGConfigRef config = YGConfigNew();

  const YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexDirection(root, YGFlexDirectionRow);
  YGNodeStyleSetAlignContent(root, YGAlignStretch);
  YGNodeStyleSetAlignItems(root, YGAlignBaseline);
  YGNodeStyleSetWidth(root, 340);
  YGNodeStyleSetMaxHeight(root, 170);
  YGNodeStyleSetMinHeight(root, 0);

  const YGNodeRef root_child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexGrow(root_child0, 0);
  YGNodeStyleSetFlexShrink(root_child0, 1);
  YGNodeSetMeasureFunc(root_child0, _measure1);
  YGNodeInsertChild(root, root_child0, 0);

  const YGNodeRef root_child1 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexGrow(root_child1, 0);
  YGNodeStyleSetFlexShrink(root_child1, 1);
  YGNodeSetMeasureFunc(root_child1, _measure2);
  YGNodeInsertChild(root, root_child1, 1);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(340, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(126, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(42, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetHeight(root_child0));
  ASSERT_FLOAT_EQ(76, YGNodeLayoutGetTop(root_child0));

  ASSERT_FLOAT_EQ(42, YGNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(279, YGNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(126, YGNodeLayoutGetHeight(root_child1));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}

TEST(YogaTest, align_baseline_with_no_parent_ht) {
  YGConfigRef config = YGConfigNew();

  const YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexDirection(root, YGFlexDirectionRow);
  YGNodeStyleSetAlignItems(root, YGAlignBaseline);
  YGNodeStyleSetWidth(root, 150);

  const YGNodeRef root_child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetWidth(root_child0, 50);
  YGNodeStyleSetHeight(root_child0, 50);
  YGNodeInsertChild(root, root_child0, 0);

  const YGNodeRef root_child1 = YGNodeNewWithConfig(config);
  YGNodeStyleSetWidth(root_child1, 50);
  YGNodeStyleSetHeight(root_child1, 40);
  YGNodeSetBaselineFunc(root_child1, _baselineFunc);
  YGNodeInsertChild(root, root_child1, 1);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(150, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(70, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(30, YGNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(40, YGNodeLayoutGetHeight(root_child1));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}

TEST(YogaTest, align_baseline_with_no_baseline_func_and_no_parent_ht) {
  YGConfigRef config = YGConfigNew();

  const YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexDirection(root, YGFlexDirectionRow);
  YGNodeStyleSetAlignItems(root, YGAlignBaseline);
  YGNodeStyleSetWidth(root, 150);

  const YGNodeRef root_child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetWidth(root_child0, 50);
  YGNodeStyleSetHeight(root_child0, 80);
  YGNodeInsertChild(root, root_child0, 0);

  const YGNodeRef root_child1 = YGNodeNewWithConfig(config);
  YGNodeStyleSetWidth(root_child1, 50);
  YGNodeStyleSetHeight(root_child1, 50);
  YGNodeInsertChild(root, root_child1, 1);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(150, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(80, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(80, YGNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(30, YGNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetHeight(root_child1));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}

TEST(YogaTest, align_baseline_parent_using_child_in_column_as_reference) {
  YGConfigRef config = YGConfigNew();

  const YGNodeRef root =
      createYGNode(config, YGFlexDirectionRow, 1000, 1000, true);

  const YGNodeRef root_child0 =
      createYGNode(config, YGFlexDirectionColumn, 500, 600, false);
  YGNodeInsertChild(root, root_child0, 0);

  const YGNodeRef root_child1 =
      createYGNode(config, YGFlexDirectionColumn, 500, 800, false);
  YGNodeInsertChild(root, root_child1, 1);

  const YGNodeRef root_child1_child0 =
      createYGNode(config, YGFlexDirectionColumn, 500, 300, false);
  YGNodeInsertChild(root_child1, root_child1_child0, 0);

  const YGNodeRef root_child1_child1 =
      createYGNode(config, YGFlexDirectionColumn, 500, 400, false);
  root_child1_child1->setBaselineFunc(_baselineFunc);
  YGNodeSetIsReferenceBaseline(root_child1_child1, true);
  YGNodeInsertChild(root_child1, root_child1_child1, 1);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));

  ASSERT_FLOAT_EQ(500, YGNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetTop(root_child1));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child1_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child1_child0));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child1_child1));
  ASSERT_FLOAT_EQ(300, YGNodeLayoutGetTop(root_child1_child1));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}

TEST(
    YogaTest,
    align_baseline_parent_using_child_with_padding_in_column_as_reference) {
  YGConfigRef config = YGConfigNew();

  const YGNodeRef root =
      createYGNode(config, YGFlexDirectionRow, 1000, 1000, true);

  const YGNodeRef root_child0 =
      createYGNode(config, YGFlexDirectionColumn, 500, 600, false);
  YGNodeInsertChild(root, root_child0, 0);

  const YGNodeRef root_child1 =
      createYGNode(config, YGFlexDirectionColumn, 500, 800, false);
  YGNodeInsertChild(root, root_child1, 1);

  const YGNodeRef root_child1_child0 =
      createYGNode(config, YGFlexDirectionColumn, 500, 300, false);
  YGNodeInsertChild(root_child1, root_child1_child0, 0);

  const YGNodeRef root_child1_child1 =
      createYGNode(config, YGFlexDirectionColumn, 500, 400, false);
  root_child1_child1->setBaselineFunc(_baselineFunc);
  YGNodeSetIsReferenceBaseline(root_child1_child1, true);
  YGNodeStyleSetPadding(root_child1_child1, YGEdgeLeft, 100);
  YGNodeStyleSetPadding(root_child1_child1, YGEdgeRight, 100);
  YGNodeStyleSetPadding(root_child1_child1, YGEdgeTop, 100);
  YGNodeStyleSetPadding(root_child1_child1, YGEdgeBottom, 100);
  YGNodeInsertChild(root_child1, root_child1_child1, 1);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));

  ASSERT_FLOAT_EQ(500, YGNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetTop(root_child1));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child1_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child1_child0));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child1_child1));
  ASSERT_FLOAT_EQ(300, YGNodeLayoutGetTop(root_child1_child1));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}

TEST(
    YogaTest,
    align_baseline_parent_with_padding_using_child_in_column_as_reference) {
  YGConfigRef config = YGConfigNew();

  const YGNodeRef root =
      createYGNode(config, YGFlexDirectionRow, 1000, 1000, true);

  const YGNodeRef root_child0 =
      createYGNode(config, YGFlexDirectionColumn, 500, 600, false);
  YGNodeInsertChild(root, root_child0, 0);

  const YGNodeRef root_child1 =
      createYGNode(config, YGFlexDirectionColumn, 500, 800, false);
  YGNodeStyleSetPadding(root_child1, YGEdgeLeft, 100);
  YGNodeStyleSetPadding(root_child1, YGEdgeRight, 100);
  YGNodeStyleSetPadding(root_child1, YGEdgeTop, 100);
  YGNodeStyleSetPadding(root_child1, YGEdgeBottom, 100);
  YGNodeInsertChild(root, root_child1, 1);

  const YGNodeRef root_child1_child0 =
      createYGNode(config, YGFlexDirectionColumn, 500, 300, false);
  YGNodeInsertChild(root_child1, root_child1_child0, 0);

  const YGNodeRef root_child1_child1 =
      createYGNode(config, YGFlexDirectionColumn, 500, 400, false);
  root_child1_child1->setBaselineFunc(_baselineFunc);
  YGNodeSetIsReferenceBaseline(root_child1_child1, true);
  YGNodeInsertChild(root_child1, root_child1_child1, 1);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));

  ASSERT_FLOAT_EQ(500, YGNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child1));

  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetLeft(root_child1_child0));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetTop(root_child1_child0));

  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetLeft(root_child1_child1));
  ASSERT_FLOAT_EQ(400, YGNodeLayoutGetTop(root_child1_child1));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}

TEST(
    YogaTest,
    align_baseline_parent_with_margin_using_child_in_column_as_reference) {
  YGConfigRef config = YGConfigNew();

  const YGNodeRef root =
      createYGNode(config, YGFlexDirectionRow, 1000, 1000, true);

  const YGNodeRef root_child0 =
      createYGNode(config, YGFlexDirectionColumn, 500, 600, false);
  YGNodeInsertChild(root, root_child0, 0);

  const YGNodeRef root_child1 =
      createYGNode(config, YGFlexDirectionColumn, 500, 800, false);
  YGNodeStyleSetMargin(root_child1, YGEdgeLeft, 100);
  YGNodeStyleSetMargin(root_child1, YGEdgeRight, 100);
  YGNodeStyleSetMargin(root_child1, YGEdgeTop, 100);
  YGNodeStyleSetMargin(root_child1, YGEdgeBottom, 100);
  YGNodeInsertChild(root, root_child1, 1);

  const YGNodeRef root_child1_child0 =
      createYGNode(config, YGFlexDirectionColumn, 500, 300, false);
  YGNodeInsertChild(root_child1, root_child1_child0, 0);

  const YGNodeRef root_child1_child1 =
      createYGNode(config, YGFlexDirectionColumn, 500, 400, false);
  root_child1_child1->setBaselineFunc(_baselineFunc);
  YGNodeSetIsReferenceBaseline(root_child1_child1, true);
  YGNodeInsertChild(root_child1, root_child1_child1, 1);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));

  ASSERT_FLOAT_EQ(600, YGNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetTop(root_child1));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child1_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child1_child0));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child1_child1));
  ASSERT_FLOAT_EQ(300, YGNodeLayoutGetTop(root_child1_child1));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}

TEST(
    YogaTest,
    align_baseline_parent_using_child_with_margin_in_column_as_reference) {
  YGConfigRef config = YGConfigNew();

  const YGNodeRef root =
      createYGNode(config, YGFlexDirectionRow, 1000, 1000, true);

  const YGNodeRef root_child0 =
      createYGNode(config, YGFlexDirectionColumn, 500, 600, false);
  YGNodeInsertChild(root, root_child0, 0);

  const YGNodeRef root_child1 =
      createYGNode(config, YGFlexDirectionColumn, 500, 800, false);
  YGNodeInsertChild(root, root_child1, 1);

  const YGNodeRef root_child1_child0 =
      createYGNode(config, YGFlexDirectionColumn, 500, 300, false);
  YGNodeInsertChild(root_child1, root_child1_child0, 0);

  const YGNodeRef root_child1_child1 =
      createYGNode(config, YGFlexDirectionColumn, 500, 400, false);
  root_child1_child1->setBaselineFunc(_baselineFunc);
  YGNodeSetIsReferenceBaseline(root_child1_child1, true);
  YGNodeStyleSetMargin(root_child1_child1, YGEdgeLeft, 100);
  YGNodeStyleSetMargin(root_child1_child1, YGEdgeRight, 100);
  YGNodeStyleSetMargin(root_child1_child1, YGEdgeTop, 100);
  YGNodeStyleSetMargin(root_child1_child1, YGEdgeBottom, 100);
  YGNodeInsertChild(root_child1, root_child1_child1, 1);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));

  ASSERT_FLOAT_EQ(500, YGNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child1));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child1_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child1_child0));

  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetLeft(root_child1_child1));
  ASSERT_FLOAT_EQ(400, YGNodeLayoutGetTop(root_child1_child1));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}

TEST(YogaTest, align_baseline_parent_using_child_in_row_as_reference) {
  YGConfigRef config = YGConfigNew();

  const YGNodeRef root =
      createYGNode(config, YGFlexDirectionRow, 1000, 1000, true);

  const YGNodeRef root_child0 =
      createYGNode(config, YGFlexDirectionColumn, 500, 600, false);
  YGNodeInsertChild(root, root_child0, 0);

  const YGNodeRef root_child1 =
      createYGNode(config, YGFlexDirectionRow, 500, 800, true);
  YGNodeInsertChild(root, root_child1, 1);

  const YGNodeRef root_child1_child0 =
      createYGNode(config, YGFlexDirectionColumn, 500, 500, false);
  YGNodeInsertChild(root_child1, root_child1_child0, 0);

  const YGNodeRef root_child1_child1 =
      createYGNode(config, YGFlexDirectionColumn, 500, 400, false);
  root_child1_child1->setBaselineFunc(_baselineFunc);
  YGNodeSetIsReferenceBaseline(root_child1_child1, true);
  YGNodeInsertChild(root_child1, root_child1_child1, 1);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));

  ASSERT_FLOAT_EQ(500, YGNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetTop(root_child1));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child1_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child1_child0));

  ASSERT_FLOAT_EQ(500, YGNodeLayoutGetLeft(root_child1_child1));
  ASSERT_FLOAT_EQ(300, YGNodeLayoutGetTop(root_child1_child1));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}

TEST(
    YogaTest,
    align_baseline_parent_using_child_with_padding_in_row_as_reference) {
  YGConfigRef config = YGConfigNew();

  const YGNodeRef root =
      createYGNode(config, YGFlexDirectionRow, 1000, 1000, true);

  const YGNodeRef root_child0 =
      createYGNode(config, YGFlexDirectionColumn, 500, 600, false);
  YGNodeInsertChild(root, root_child0, 0);

  const YGNodeRef root_child1 =
      createYGNode(config, YGFlexDirectionRow, 500, 800, true);
  YGNodeInsertChild(root, root_child1, 1);

  const YGNodeRef root_child1_child0 =
      createYGNode(config, YGFlexDirectionColumn, 500, 500, false);
  YGNodeInsertChild(root_child1, root_child1_child0, 0);

  const YGNodeRef root_child1_child1 =
      createYGNode(config, YGFlexDirectionColumn, 500, 400, false);
  root_child1_child1->setBaselineFunc(_baselineFunc);
  YGNodeSetIsReferenceBaseline(root_child1_child1, true);
  YGNodeStyleSetPadding(root_child1_child1, YGEdgeLeft, 100);
  YGNodeStyleSetPadding(root_child1_child1, YGEdgeRight, 100);
  YGNodeStyleSetPadding(root_child1_child1, YGEdgeTop, 100);
  YGNodeStyleSetPadding(root_child1_child1, YGEdgeBottom, 100);
  YGNodeInsertChild(root_child1, root_child1_child1, 1);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));

  ASSERT_FLOAT_EQ(500, YGNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetTop(root_child1));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child1_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child1_child0));

  ASSERT_FLOAT_EQ(500, YGNodeLayoutGetLeft(root_child1_child1));
  ASSERT_FLOAT_EQ(300, YGNodeLayoutGetTop(root_child1_child1));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}

TEST(
    YogaTest,
    align_baseline_parent_using_child_with_margin_in_row_as_reference) {
  YGConfigRef config = YGConfigNew();

  const YGNodeRef root =
      createYGNode(config, YGFlexDirectionRow, 1000, 1000, true);

  const YGNodeRef root_child0 =
      createYGNode(config, YGFlexDirectionColumn, 500, 600, false);
  YGNodeInsertChild(root, root_child0, 0);

  const YGNodeRef root_child1 =
      createYGNode(config, YGFlexDirectionRow, 500, 800, true);
  YGNodeInsertChild(root, root_child1, 1);

  const YGNodeRef root_child1_child0 =
      createYGNode(config, YGFlexDirectionColumn, 500, 500, false);
  YGNodeInsertChild(root_child1, root_child1_child0, 0);

  const YGNodeRef root_child1_child1 =
      createYGNode(config, YGFlexDirectionColumn, 500, 400, false);
  root_child1_child1->setBaselineFunc(_baselineFunc);
  YGNodeSetIsReferenceBaseline(root_child1_child1, true);
  YGNodeStyleSetMargin(root_child1_child1, YGEdgeLeft, 100);
  YGNodeStyleSetMargin(root_child1_child1, YGEdgeRight, 100);
  YGNodeStyleSetMargin(root_child1_child1, YGEdgeTop, 100);
  YGNodeStyleSetMargin(root_child1_child1, YGEdgeBottom, 100);
  YGNodeInsertChild(root_child1, root_child1_child1, 1);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));

  ASSERT_FLOAT_EQ(500, YGNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetTop(root_child1));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child1_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child1_child0));

  ASSERT_FLOAT_EQ(600, YGNodeLayoutGetLeft(root_child1_child1));
  ASSERT_FLOAT_EQ(300, YGNodeLayoutGetTop(root_child1_child1));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}

TEST(
    YogaTest,
    align_baseline_parent_using_child_in_column_as_reference_with_no_baseline_func) {
  YGConfigRef config = YGConfigNew();

  const YGNodeRef root =
      createYGNode(config, YGFlexDirectionRow, 1000, 1000, true);

  const YGNodeRef root_child0 =
      createYGNode(config, YGFlexDirectionColumn, 500, 600, false);
  YGNodeInsertChild(root, root_child0, 0);

  const YGNodeRef root_child1 =
      createYGNode(config, YGFlexDirectionColumn, 500, 800, false);
  YGNodeInsertChild(root, root_child1, 1);

  const YGNodeRef root_child1_child0 =
      createYGNode(config, YGFlexDirectionColumn, 500, 300, false);
  YGNodeInsertChild(root_child1, root_child1_child0, 0);

  const YGNodeRef root_child1_child1 =
      createYGNode(config, YGFlexDirectionColumn, 500, 400, false);
  YGNodeSetIsReferenceBaseline(root_child1_child1, true);
  YGNodeInsertChild(root_child1, root_child1_child1, 1);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetTop(root_child0));

  ASSERT_FLOAT_EQ(500, YGNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child1));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child1_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child1_child0));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child1_child1));
  ASSERT_FLOAT_EQ(300, YGNodeLayoutGetTop(root_child1_child1));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}

TEST(
    YogaTest,
    align_baseline_parent_using_child_in_row_as_reference_with_no_baseline_func) {
  YGConfigRef config = YGConfigNew();

  const YGNodeRef root =
      createYGNode(config, YGFlexDirectionRow, 1000, 1000, true);

  const YGNodeRef root_child0 =
      createYGNode(config, YGFlexDirectionColumn, 500, 600, false);
  YGNodeInsertChild(root, root_child0, 0);

  const YGNodeRef root_child1 =
      createYGNode(config, YGFlexDirectionRow, 500, 800, true);
  YGNodeInsertChild(root, root_child1, 1);

  const YGNodeRef root_child1_child0 =
      createYGNode(config, YGFlexDirectionColumn, 500, 500, false);
  YGNodeInsertChild(root_child1, root_child1_child0, 0);

  const YGNodeRef root_child1_child1 =
      createYGNode(config, YGFlexDirectionColumn, 500, 400, false);
  YGNodeSetIsReferenceBaseline(root_child1_child1, true);
  YGNodeInsertChild(root_child1, root_child1_child1, 1);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));

  ASSERT_FLOAT_EQ(500, YGNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetTop(root_child1));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child1_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child1_child0));

  ASSERT_FLOAT_EQ(500, YGNodeLayoutGetLeft(root_child1_child1));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetTop(root_child1_child1));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}

TEST(
    YogaTest,
    align_baseline_parent_using_child_in_column_as_reference_with_height_not_specified) {
  YGConfigRef config = YGConfigNew();

  const YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexDirection(root, YGFlexDirectionRow);
  YGNodeStyleSetAlignItems(root, YGAlignBaseline);
  YGNodeStyleSetWidth(root, 1000);

  const YGNodeRef root_child0 =
      createYGNode(config, YGFlexDirectionColumn, 500, 600, false);
  YGNodeInsertChild(root, root_child0, 0);

  const YGNodeRef root_child1 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexDirection(root_child1, YGFlexDirectionColumn);
  YGNodeStyleSetWidth(root_child1, 500);
  YGNodeInsertChild(root, root_child1, 1);

  const YGNodeRef root_child1_child0 =
      createYGNode(config, YGFlexDirectionColumn, 500, 300, false);
  YGNodeInsertChild(root_child1, root_child1_child0, 0);

  const YGNodeRef root_child1_child1 =
      createYGNode(config, YGFlexDirectionColumn, 500, 400, false);
  root_child1_child1->setBaselineFunc(_baselineFunc);
  YGNodeSetIsReferenceBaseline(root_child1_child1, true);
  YGNodeInsertChild(root_child1, root_child1_child1, 1);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(800, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));

  ASSERT_FLOAT_EQ(500, YGNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(700, YGNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child1_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child1_child0));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child1_child1));
  ASSERT_FLOAT_EQ(300, YGNodeLayoutGetTop(root_child1_child1));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}

TEST(
    YogaTest,
    align_baseline_parent_using_child_in_row_as_reference_with_height_not_specified) {
  YGConfigRef config = YGConfigNew();

  const YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexDirection(root, YGFlexDirectionRow);
  YGNodeStyleSetAlignItems(root, YGAlignBaseline);
  YGNodeStyleSetWidth(root, 1000);

  const YGNodeRef root_child0 =
      createYGNode(config, YGFlexDirectionColumn, 500, 600, false);
  YGNodeInsertChild(root, root_child0, 0);

  const YGNodeRef root_child1 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexDirection(root_child1, YGFlexDirectionRow);
  YGNodeStyleSetWidth(root_child1, 500);
  YGNodeInsertChild(root, root_child1, 1);

  const YGNodeRef root_child1_child0 =
      createYGNode(config, YGFlexDirectionColumn, 500, 500, false);
  YGNodeInsertChild(root_child1, root_child1_child0, 0);

  const YGNodeRef root_child1_child1 =
      createYGNode(config, YGFlexDirectionColumn, 500, 400, false);
  root_child1_child1->setBaselineFunc(_baselineFunc);
  YGNodeSetIsReferenceBaseline(root_child1_child1, true);
  YGNodeInsertChild(root_child1, root_child1_child1, 1);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(900, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));

  ASSERT_FLOAT_EQ(500, YGNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(400, YGNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(500, YGNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child1_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child1_child0));

  ASSERT_FLOAT_EQ(500, YGNodeLayoutGetLeft(root_child1_child1));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child1_child1));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}

TEST(
    YogaTest,
    align_baseline_parent_using_child_in_column_as_reference_with_no_baseline_func_and_height_not_specified) {
  YGConfigRef config = YGConfigNew();

  const YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexDirection(root, YGFlexDirectionRow);
  YGNodeStyleSetAlignItems(root, YGAlignBaseline);
  YGNodeStyleSetWidth(root, 1000);

  const YGNodeRef root_child0 =
      createYGNode(config, YGFlexDirectionColumn, 500, 600, false);
  YGNodeInsertChild(root, root_child0, 0);

  const YGNodeRef root_child1 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexDirection(root_child1, YGFlexDirectionColumn);
  YGNodeStyleSetWidth(root_child1, 500);
  YGNodeInsertChild(root, root_child1, 1);

  const YGNodeRef root_child1_child0 =
      createYGNode(config, YGFlexDirectionColumn, 500, 300, false);
  YGNodeInsertChild(root_child1, root_child1_child0, 0);

  const YGNodeRef root_child1_child1 =
      createYGNode(config, YGFlexDirectionColumn, 500, 400, false);
  YGNodeSetIsReferenceBaseline(root_child1_child1, true);
  YGNodeInsertChild(root_child1, root_child1_child1, 1);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(700, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetTop(root_child0));

  ASSERT_FLOAT_EQ(500, YGNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(700, YGNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child1_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child1_child0));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child1_child1));
  ASSERT_FLOAT_EQ(300, YGNodeLayoutGetTop(root_child1_child1));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}

TEST(
    YogaTest,
    align_baseline_parent_using_child_in_row_as_reference_with_no_baseline_func_and_height_not_specified) {
  YGConfigRef config = YGConfigNew();

  const YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexDirection(root, YGFlexDirectionRow);
  YGNodeStyleSetAlignItems(root, YGAlignBaseline);
  YGNodeStyleSetWidth(root, 1000);

  const YGNodeRef root_child0 =
      createYGNode(config, YGFlexDirectionColumn, 500, 600, false);
  YGNodeInsertChild(root, root_child0, 0);

  const YGNodeRef root_child1 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexDirection(root_child1, YGFlexDirectionRow);
  YGNodeStyleSetWidth(root_child1, 500);
  YGNodeInsertChild(root, root_child1, 1);

  const YGNodeRef root_child1_child0 =
      createYGNode(config, YGFlexDirectionColumn, 500, 500, false);
  YGNodeInsertChild(root_child1, root_child1_child0, 0);

  const YGNodeRef root_child1_child1 =
      createYGNode(config, YGFlexDirectionColumn, 500, 400, false);
  YGNodeSetIsReferenceBaseline(root_child1_child1, true);
  YGNodeInsertChild(root_child1, root_child1_child1, 1);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(700, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));

  ASSERT_FLOAT_EQ(500, YGNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(200, YGNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(500, YGNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child1_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child1_child0));

  ASSERT_FLOAT_EQ(500, YGNodeLayoutGetLeft(root_child1_child1));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child1_child1));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}
