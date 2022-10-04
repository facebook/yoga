/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>
#include <yoga/YGNode.h>
#include <yoga/Yoga.h>

struct _MeasureConstraint {
  float width;
  YGMeasureMode widthMode;
  float height;
  YGMeasureMode heightMode;
};

struct _MeasureConstraintList {
  uint32_t length;
  struct _MeasureConstraint* constraints;
};

static YGSize _measure(
    YGNodeRef node,
    float width,
    YGMeasureMode widthMode,
    float height,
    YGMeasureMode heightMode) {
  struct _MeasureConstraintList* constraintList =
      (struct _MeasureConstraintList*) node->getContext();
  struct _MeasureConstraint* constraints = constraintList->constraints;
  uint32_t currentIndex = constraintList->length;
  (&constraints[currentIndex])->width = width;
  (&constraints[currentIndex])->widthMode = widthMode;
  (&constraints[currentIndex])->height = height;
  (&constraints[currentIndex])->heightMode = heightMode;
  constraintList->length = currentIndex + 1;

  return YGSize{
      .width = widthMode == YGMeasureModeUndefined ? 10 : width,
      .height = heightMode == YGMeasureModeUndefined ? 10 : width,
  };
}

TEST(YogaTest, exactly_measure_stretched_child_column) {
  struct _MeasureConstraintList constraintList = _MeasureConstraintList{
      .length = 0,
      .constraints = (struct _MeasureConstraint*) malloc(
          10 * sizeof(struct _MeasureConstraint)),
  };

  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetWidth(root, 100);
  YGNodeStyleSetHeight(root, 100);

  const YGNodeRef root_child0 = YGNodeNew();
  //  root_child0->setContext(&constraintList);
  root_child0->setContext(&constraintList);
  root_child0->setMeasureFunc(_measure);
  //  root_child0->setMeasureFunc(_measure);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(1u, constraintList.length);

  ASSERT_FLOAT_EQ(100, constraintList.constraints[0].width);
  ASSERT_EQ(YGMeasureModeExactly, constraintList.constraints[0].widthMode);

  free(constraintList.constraints);
  YGNodeFreeRecursive(root);
}

TEST(YogaTest, exactly_measure_stretched_child_row) {
  struct _MeasureConstraintList constraintList = _MeasureConstraintList{
      .length = 0,
      .constraints = (struct _MeasureConstraint*) malloc(
          10 * sizeof(struct _MeasureConstraint)),
  };

  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetFlexDirection(root, YGFlexDirectionRow);
  YGNodeStyleSetWidth(root, 100);
  YGNodeStyleSetHeight(root, 100);

  const YGNodeRef root_child0 = YGNodeNew();
  //  root_child0->setContext(&constraintList);
  root_child0->setContext(&constraintList);
  root_child0->setMeasureFunc(_measure);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(1u, constraintList.length);

  ASSERT_FLOAT_EQ(100, constraintList.constraints[0].height);
  ASSERT_EQ(YGMeasureModeExactly, constraintList.constraints[0].heightMode);

  free(constraintList.constraints);
  YGNodeFreeRecursive(root);
}

TEST(YogaTest, at_most_main_axis_column) {
  struct _MeasureConstraintList constraintList = _MeasureConstraintList{
      .length = 0,
      .constraints = (struct _MeasureConstraint*) malloc(
          10 * sizeof(struct _MeasureConstraint)),
  };

  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetWidth(root, 100);
  YGNodeStyleSetHeight(root, 100);

  const YGNodeRef root_child0 = YGNodeNew();
  root_child0->setContext(&constraintList);
  root_child0->setMeasureFunc(_measure);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(1u, constraintList.length);

  ASSERT_FLOAT_EQ(100, constraintList.constraints[0].height);
  ASSERT_EQ(YGMeasureModeAtMost, constraintList.constraints[0].heightMode);

  free(constraintList.constraints);
  YGNodeFreeRecursive(root);
}

TEST(YogaTest, at_most_cross_axis_column) {
  struct _MeasureConstraintList constraintList = _MeasureConstraintList{
      .length = 0,
      .constraints = (struct _MeasureConstraint*) malloc(
          10 * sizeof(struct _MeasureConstraint)),
  };

  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetAlignItems(root, YGAlignFlexStart);
  YGNodeStyleSetWidth(root, 100);
  YGNodeStyleSetHeight(root, 100);

  const YGNodeRef root_child0 = YGNodeNew();
  root_child0->setContext(&constraintList);
  root_child0->setMeasureFunc(_measure);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(1u, constraintList.length);

  ASSERT_FLOAT_EQ(100, constraintList.constraints[0].width);
  ASSERT_EQ(YGMeasureModeAtMost, constraintList.constraints[0].widthMode);

  free(constraintList.constraints);
  YGNodeFreeRecursive(root);
}

TEST(YogaTest, at_most_main_axis_row) {
  struct _MeasureConstraintList constraintList = _MeasureConstraintList{
      .length = 0,
      .constraints = (struct _MeasureConstraint*) malloc(
          10 * sizeof(struct _MeasureConstraint)),
  };

  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetFlexDirection(root, YGFlexDirectionRow);
  YGNodeStyleSetWidth(root, 100);
  YGNodeStyleSetHeight(root, 100);

  const YGNodeRef root_child0 = YGNodeNew();
  root_child0->setContext(&constraintList);
  root_child0->setMeasureFunc(_measure);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(1u, constraintList.length);

  ASSERT_FLOAT_EQ(100, constraintList.constraints[0].width);
  ASSERT_EQ(YGMeasureModeAtMost, constraintList.constraints[0].widthMode);

  free(constraintList.constraints);
  YGNodeFreeRecursive(root);
}

TEST(YogaTest, at_most_cross_axis_row) {
  struct _MeasureConstraintList constraintList = _MeasureConstraintList{
      .length = 0,
      .constraints = (struct _MeasureConstraint*) malloc(
          10 * sizeof(struct _MeasureConstraint)),
  };

  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetFlexDirection(root, YGFlexDirectionRow);
  YGNodeStyleSetAlignItems(root, YGAlignFlexStart);
  YGNodeStyleSetWidth(root, 100);
  YGNodeStyleSetHeight(root, 100);

  const YGNodeRef root_child0 = YGNodeNew();
  root_child0->setContext(&constraintList);
  root_child0->setMeasureFunc(_measure);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(1u, constraintList.length);

  ASSERT_FLOAT_EQ(100, constraintList.constraints[0].height);
  ASSERT_EQ(YGMeasureModeAtMost, constraintList.constraints[0].heightMode);

  free(constraintList.constraints);
  YGNodeFreeRecursive(root);
}

TEST(YogaTest, flex_child) {
  struct _MeasureConstraintList constraintList = _MeasureConstraintList{
      .length = 0,
      .constraints = (struct _MeasureConstraint*) malloc(
          10 * sizeof(struct _MeasureConstraint)),
  };

  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetHeight(root, 100);

  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeStyleSetFlexGrow(root_child0, 1);
  root_child0->setContext(&constraintList);
  root_child0->setMeasureFunc(_measure);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(2u, constraintList.length);

  ASSERT_FLOAT_EQ(100, constraintList.constraints[0].height);
  ASSERT_EQ(YGMeasureModeAtMost, constraintList.constraints[0].heightMode);

  ASSERT_FLOAT_EQ(100, constraintList.constraints[1].height);
  ASSERT_EQ(YGMeasureModeExactly, constraintList.constraints[1].heightMode);

  free(constraintList.constraints);
  YGNodeFreeRecursive(root);
}

TEST(YogaTest, flex_child_with_flex_basis) {
  struct _MeasureConstraintList constraintList = _MeasureConstraintList{
      .length = 0,
      .constraints = (struct _MeasureConstraint*) malloc(
          10 * sizeof(struct _MeasureConstraint)),
  };

  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetHeight(root, 100);

  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeStyleSetFlexGrow(root_child0, 1);
  YGNodeStyleSetFlexBasis(root_child0, 0);
  root_child0->setContext(&constraintList);
  root_child0->setMeasureFunc(_measure);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(1u, constraintList.length);

  ASSERT_FLOAT_EQ(100, constraintList.constraints[0].height);
  ASSERT_EQ(YGMeasureModeExactly, constraintList.constraints[0].heightMode);

  free(constraintList.constraints);
  YGNodeFreeRecursive(root);
}

TEST(YogaTest, overflow_scroll_column) {
  struct _MeasureConstraintList constraintList = _MeasureConstraintList{
      .length = 0,
      .constraints = (struct _MeasureConstraint*) malloc(
          10 * sizeof(struct _MeasureConstraint)),
  };

  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetAlignItems(root, YGAlignFlexStart);
  YGNodeStyleSetOverflow(root, YGOverflowScroll);
  YGNodeStyleSetHeight(root, 100);
  YGNodeStyleSetWidth(root, 100);

  const YGNodeRef root_child0 = YGNodeNew();
  root_child0->setContext(&constraintList);
  root_child0->setMeasureFunc(_measure);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(1u, constraintList.length);

  ASSERT_FLOAT_EQ(100, constraintList.constraints[0].width);
  ASSERT_EQ(YGMeasureModeAtMost, constraintList.constraints[0].widthMode);

  ASSERT_TRUE(YGFloatIsUndefined(constraintList.constraints[0].height));
  ASSERT_EQ(YGMeasureModeUndefined, constraintList.constraints[0].heightMode);

  free(constraintList.constraints);
  YGNodeFreeRecursive(root);
}

TEST(YogaTest, overflow_scroll_row) {
  struct _MeasureConstraintList constraintList = _MeasureConstraintList{
      .length = 0,
      .constraints = (struct _MeasureConstraint*) malloc(
          10 * sizeof(struct _MeasureConstraint)),
  };

  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetAlignItems(root, YGAlignFlexStart);
  YGNodeStyleSetFlexDirection(root, YGFlexDirectionRow);
  YGNodeStyleSetOverflow(root, YGOverflowScroll);
  YGNodeStyleSetHeight(root, 100);
  YGNodeStyleSetWidth(root, 100);

  const YGNodeRef root_child0 = YGNodeNew();
  root_child0->setContext(&constraintList);
  root_child0->setMeasureFunc(_measure);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(1u, constraintList.length);

  ASSERT_TRUE(YGFloatIsUndefined(constraintList.constraints[0].width));
  ASSERT_EQ(YGMeasureModeUndefined, constraintList.constraints[0].widthMode);

  ASSERT_FLOAT_EQ(100, constraintList.constraints[0].height);
  ASSERT_EQ(YGMeasureModeAtMost, constraintList.constraints[0].heightMode);

  free(constraintList.constraints);
  YGNodeFreeRecursive(root);
}
