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
                        CSSMeasureMode widthMode,
                        float height,
                        CSSMeasureMode heightMode) {

  int *measureCount = (int *)CSSNodeGetContext(node);
  *measureCount = *measureCount + 1;
  return CSSSize {
      .width = widthMode == CSSMeasureModeUndefined ? 10 : width,
      .height = heightMode == CSSMeasureModeUndefined ? 10 : height,
  };
}

static CSSSize _measureMin(CSSNodeRef node,
                        float width,
                        CSSMeasureMode widthMode,
                        float height,
                        CSSMeasureMode heightMode) {

  int *measureCount = (int *)CSSNodeGetContext(node);
  *measureCount = *measureCount + 1;
  return CSSSize {
      .width = widthMode == CSSMeasureModeUndefined || (widthMode == CSSMeasureModeAtMost && width > 10) ? 10 : width,
      .height = heightMode == CSSMeasureModeUndefined || (heightMode == CSSMeasureModeAtMost && height > 10) ? 10 : height,
  };
}

TEST(CSSLayoutTest, measure_once_single_flexible_child) {
  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetFlexDirection(root, CSSFlexDirectionRow);
  CSSNodeStyleSetAlignItems(root, CSSAlignFlexStart);
  CSSNodeStyleSetWidth(root, 100);
  CSSNodeStyleSetHeight(root, 100);

  const CSSNodeRef root_child0 = CSSNodeNew();
  int measureCount = 0;
  CSSNodeSetContext(root_child0, &measureCount);
  CSSNodeSetMeasureFunc(root_child0, _measureMax);
  CSSNodeStyleSetFlexGrow(root_child0, 1);
  CSSNodeInsertChild(root, root_child0, 0);

  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionLTR);

  ASSERT_EQ(1, measureCount);

  CSSNodeFreeRecursive(root);
}

TEST(CSSLayoutTest, remeasure_text_node_height_change) {
  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetAlignItems(root, CSSAlignFlexStart);

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeSetIsTextnode(root_child0, true);
  CSSNodeStyleSetFlexGrow(root_child0, 1);
  int measureCount = 0;
  CSSNodeSetContext(root_child0, &measureCount);
  CSSNodeSetMeasureFunc(root_child0, _measureMax);
  CSSNodeInsertChild(root, root_child0, 0);

  CSSNodeCalculateLayout(root, 100, 10, CSSDirectionLTR);
  CSSNodeCalculateLayout(root, 100, 20, CSSDirectionLTR);

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

  CSSNodeCalculateLayout(root, 100, 100, CSSDirectionLTR);
  CSSNodeCalculateLayout(root, 100, 50, CSSDirectionLTR);

  ASSERT_EQ(1, measureCount);

  CSSNodeFreeRecursive(root);
}

TEST(CSSLayoutTest, remeasure_with_same_atmost_width_larger_than_needed_height) {
  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetAlignItems(root, CSSAlignFlexStart);

  const CSSNodeRef root_child0 = CSSNodeNew();
  int measureCount = 0;
  CSSNodeSetContext(root_child0, &measureCount);
  CSSNodeSetMeasureFunc(root_child0, _measureMin);
  CSSNodeInsertChild(root, root_child0, 0);

  CSSNodeCalculateLayout(root, 100, 100, CSSDirectionLTR);
  CSSNodeCalculateLayout(root, 100, 50, CSSDirectionLTR);

  ASSERT_EQ(1, measureCount);

  CSSNodeFreeRecursive(root);
}

TEST(CSSLayoutTest, remeasure_with_computed_width_larger_than_needed_height) {
  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetAlignItems(root, CSSAlignFlexStart);

  const CSSNodeRef root_child0 = CSSNodeNew();
  int measureCount = 0;
  CSSNodeSetContext(root_child0, &measureCount);
  CSSNodeSetMeasureFunc(root_child0, _measureMin);
  CSSNodeInsertChild(root, root_child0, 0);

  CSSNodeCalculateLayout(root, 100, 100, CSSDirectionLTR);
  CSSNodeStyleSetAlignItems(root, CSSAlignStretch);
  CSSNodeCalculateLayout(root, 10, 50, CSSDirectionLTR);

  ASSERT_EQ(1, measureCount);

  CSSNodeFreeRecursive(root);
}

TEST(CSSLayoutTest, remeasure_with_atmost_computed_width_undefined_height) {
  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetAlignItems(root, CSSAlignFlexStart);

  const CSSNodeRef root_child0 = CSSNodeNew();
  int measureCount = 0;
  CSSNodeSetContext(root_child0, &measureCount);
  CSSNodeSetMeasureFunc(root_child0, _measureMin);
  CSSNodeInsertChild(root, root_child0, 0);

  CSSNodeCalculateLayout(root, 100, CSSUndefined, CSSDirectionLTR);
  CSSNodeCalculateLayout(root, 10, CSSUndefined, CSSDirectionLTR);

  ASSERT_EQ(1, measureCount);

  CSSNodeFreeRecursive(root);
}
