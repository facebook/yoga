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

struct _MeasureConstraint {
  float width;
  CSSMeasureMode widthMode;
  float height;
  CSSMeasureMode heightMode;
};

struct _MeasureConstraintList {
  uint32_t length;
  struct _MeasureConstraint *constraints;
};

static CSSSize _measure(CSSNodeRef node,
                        float width,
                        CSSMeasureMode widthMode,
                        float height,
                        CSSMeasureMode heightMode) {
  struct _MeasureConstraintList *constraintList = (struct _MeasureConstraintList *)CSSNodeGetContext(node);
  struct _MeasureConstraint *constraints = constraintList->constraints;
  uint32_t currentIndex = constraintList->length;
  (&constraints[currentIndex])->width = width;
  (&constraints[currentIndex])->widthMode = widthMode;
  (&constraints[currentIndex])->height = height;
  (&constraints[currentIndex])->heightMode = heightMode;
  constraintList->length = currentIndex + 1;

  return CSSSize {
      .width = widthMode == CSSMeasureModeUndefined ? 10 : width,
      .height = heightMode == CSSMeasureModeUndefined ? 10 : width,
  };
}

TEST(CSSLayoutTest, exactly_measure_stretched_child_column) {
  struct _MeasureConstraintList constraintList = _MeasureConstraintList {
    .length = 0,
    .constraints = (struct _MeasureConstraint *) malloc(10 * sizeof(struct _MeasureConstraint)),
  };

  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetWidth(root, 100);
  CSSNodeStyleSetHeight(root, 100);

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeSetContext(root_child0, &constraintList);
  CSSNodeSetMeasureFunc(root_child0, _measure);
  CSSNodeInsertChild(root, root_child0, 0);

  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionLTR);

  ASSERT_EQ(1, constraintList.length);

  ASSERT_EQ(100, constraintList.constraints[0].width);
  ASSERT_EQ(CSSMeasureModeExactly, constraintList.constraints[0].widthMode);

  free(constraintList.constraints);
  CSSNodeFreeRecursive(root);
}

TEST(CSSLayoutTest, exactly_measure_stretched_child_row) {
  struct _MeasureConstraintList constraintList = _MeasureConstraintList {
    .length = 0,
    .constraints = (struct _MeasureConstraint *) malloc(10 * sizeof(struct _MeasureConstraint)),
  };

  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetFlexDirection(root, CSSFlexDirectionRow);
  CSSNodeStyleSetWidth(root, 100);
  CSSNodeStyleSetHeight(root, 100);

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeSetContext(root_child0, &constraintList);
  CSSNodeSetMeasureFunc(root_child0, _measure);
  CSSNodeInsertChild(root, root_child0, 0);

  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionLTR);

  ASSERT_EQ(1, constraintList.length);

  ASSERT_EQ(100, constraintList.constraints[0].height);
  ASSERT_EQ(CSSMeasureModeExactly, constraintList.constraints[0].heightMode);

  free(constraintList.constraints);
  CSSNodeFreeRecursive(root);
}

TEST(CSSLayoutTest, at_most_main_axis_column) {
  struct _MeasureConstraintList constraintList = _MeasureConstraintList {
    .length = 0,
    .constraints = (struct _MeasureConstraint *) malloc(10 * sizeof(struct _MeasureConstraint)),
  };

  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetWidth(root, 100);
  CSSNodeStyleSetHeight(root, 100);

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeSetContext(root_child0, &constraintList);
  CSSNodeSetMeasureFunc(root_child0, _measure);
  CSSNodeInsertChild(root, root_child0, 0);

  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionLTR);

  ASSERT_EQ(1, constraintList.length);

  ASSERT_EQ(100, constraintList.constraints[0].height);
  ASSERT_EQ(CSSMeasureModeAtMost, constraintList.constraints[0].heightMode);

  free(constraintList.constraints);
  CSSNodeFreeRecursive(root);
}

TEST(CSSLayoutTest, at_most_cross_axis_column) {
  struct _MeasureConstraintList constraintList = _MeasureConstraintList {
    .length = 0,
    .constraints = (struct _MeasureConstraint *) malloc(10 * sizeof(struct _MeasureConstraint)),
  };

  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetAlignItems(root, CSSAlignFlexStart);
  CSSNodeStyleSetWidth(root, 100);
  CSSNodeStyleSetHeight(root, 100);

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeSetContext(root_child0, &constraintList);
  CSSNodeSetMeasureFunc(root_child0, _measure);
  CSSNodeInsertChild(root, root_child0, 0);

  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionLTR);

  ASSERT_EQ(1, constraintList.length);

  ASSERT_EQ(100, constraintList.constraints[0].width);
  ASSERT_EQ(CSSMeasureModeAtMost, constraintList.constraints[0].widthMode);

  free(constraintList.constraints);
  CSSNodeFreeRecursive(root);
}

TEST(CSSLayoutTest, at_most_main_axis_row) {
  struct _MeasureConstraintList constraintList = _MeasureConstraintList {
    .length = 0,
    .constraints = (struct _MeasureConstraint *) malloc(10 * sizeof(struct _MeasureConstraint)),
  };

  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetFlexDirection(root, CSSFlexDirectionRow);
  CSSNodeStyleSetWidth(root, 100);
  CSSNodeStyleSetHeight(root, 100);

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeSetContext(root_child0, &constraintList);
  CSSNodeSetMeasureFunc(root_child0, _measure);
  CSSNodeInsertChild(root, root_child0, 0);

  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionLTR);

  ASSERT_EQ(1, constraintList.length);

  ASSERT_EQ(100, constraintList.constraints[0].width);
  ASSERT_EQ(CSSMeasureModeAtMost, constraintList.constraints[0].widthMode);

  free(constraintList.constraints);
  CSSNodeFreeRecursive(root);
}

TEST(CSSLayoutTest, at_most_cross_axis_row) {
  struct _MeasureConstraintList constraintList = _MeasureConstraintList {
    .length = 0,
    .constraints = (struct _MeasureConstraint *) malloc(10 * sizeof(struct _MeasureConstraint)),
  };

  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetFlexDirection(root, CSSFlexDirectionRow);
  CSSNodeStyleSetAlignItems(root, CSSAlignFlexStart);
  CSSNodeStyleSetWidth(root, 100);
  CSSNodeStyleSetHeight(root, 100);

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeSetContext(root_child0, &constraintList);
  CSSNodeSetMeasureFunc(root_child0, _measure);
  CSSNodeInsertChild(root, root_child0, 0);

  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionLTR);

  ASSERT_EQ(1, constraintList.length);

  ASSERT_EQ(100, constraintList.constraints[0].height);
  ASSERT_EQ(CSSMeasureModeAtMost, constraintList.constraints[0].heightMode);

  free(constraintList.constraints);
  CSSNodeFreeRecursive(root);
}

TEST(CSSLayoutTest, flex_child) {
  struct _MeasureConstraintList constraintList = _MeasureConstraintList {
    .length = 0,
    .constraints = (struct _MeasureConstraint *) malloc(10 * sizeof(struct _MeasureConstraint)),
  };

  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetHeight(root, 100);

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeStyleSetFlexGrow(root_child0, 1);
  CSSNodeSetContext(root_child0, &constraintList);
  CSSNodeSetMeasureFunc(root_child0, _measure);
  CSSNodeInsertChild(root, root_child0, 0);

  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionLTR);

  ASSERT_EQ(2, constraintList.length);

  ASSERT_EQ(100, constraintList.constraints[0].height);
  ASSERT_EQ(CSSMeasureModeAtMost, constraintList.constraints[0].heightMode);

  ASSERT_EQ(100, constraintList.constraints[1].height);
  ASSERT_EQ(CSSMeasureModeExactly, constraintList.constraints[1].heightMode);

  free(constraintList.constraints);
  CSSNodeFreeRecursive(root);
}

TEST(CSSLayoutTest, flex_child_with_flex_basis) {
  struct _MeasureConstraintList constraintList = _MeasureConstraintList {
    .length = 0,
    .constraints = (struct _MeasureConstraint *) malloc(10 * sizeof(struct _MeasureConstraint)),
  };

  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetHeight(root, 100);

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeStyleSetFlexGrow(root_child0, 1);
  CSSNodeStyleSetFlexBasis(root_child0, 0);
  CSSNodeSetContext(root_child0, &constraintList);
  CSSNodeSetMeasureFunc(root_child0, _measure);
  CSSNodeInsertChild(root, root_child0, 0);

  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionLTR);

  ASSERT_EQ(1, constraintList.length);

  ASSERT_EQ(100, constraintList.constraints[0].height);
  ASSERT_EQ(CSSMeasureModeExactly, constraintList.constraints[0].heightMode);

  free(constraintList.constraints);
  CSSNodeFreeRecursive(root);
}

TEST(CSSLayoutTest, overflow_scroll_column) {
  struct _MeasureConstraintList constraintList = _MeasureConstraintList {
    .length = 0,
    .constraints = (struct _MeasureConstraint *) malloc(10 * sizeof(struct _MeasureConstraint)),
  };

  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetAlignItems(root, CSSAlignFlexStart);
  CSSNodeStyleSetOverflow(root, CSSOverflowScroll);
  CSSNodeStyleSetHeight(root, 100);
  CSSNodeStyleSetWidth(root, 100);

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeSetContext(root_child0, &constraintList);
  CSSNodeSetMeasureFunc(root_child0, _measure);
  CSSNodeInsertChild(root, root_child0, 0);

  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionLTR);

  ASSERT_EQ(1, constraintList.length);

  ASSERT_EQ(100, constraintList.constraints[0].width);
  ASSERT_EQ(CSSMeasureModeAtMost, constraintList.constraints[0].widthMode);

  ASSERT_TRUE(CSSValueIsUndefined(constraintList.constraints[0].height));
  ASSERT_EQ(CSSMeasureModeUndefined, constraintList.constraints[0].heightMode);

  free(constraintList.constraints);
  CSSNodeFreeRecursive(root);
}

TEST(CSSLayoutTest, overflow_scroll_row) {
  struct _MeasureConstraintList constraintList = _MeasureConstraintList {
    .length = 0,
    .constraints = (struct _MeasureConstraint *) malloc(10 * sizeof(struct _MeasureConstraint)),
  };

  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetAlignItems(root, CSSAlignFlexStart);
  CSSNodeStyleSetFlexDirection(root, CSSFlexDirectionRow);
  CSSNodeStyleSetOverflow(root, CSSOverflowScroll);
  CSSNodeStyleSetHeight(root, 100);
  CSSNodeStyleSetWidth(root, 100);

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeSetContext(root_child0, &constraintList);
  CSSNodeSetMeasureFunc(root_child0, _measure);
  CSSNodeInsertChild(root, root_child0, 0);

  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionLTR);

  ASSERT_EQ(1, constraintList.length);

  ASSERT_TRUE(CSSValueIsUndefined(constraintList.constraints[0].width));
  ASSERT_EQ(CSSMeasureModeUndefined, constraintList.constraints[0].widthMode);

  ASSERT_EQ(100, constraintList.constraints[0].height);
  ASSERT_EQ(CSSMeasureModeAtMost, constraintList.constraints[0].heightMode);

  free(constraintList.constraints);
  CSSNodeFreeRecursive(root);
}
