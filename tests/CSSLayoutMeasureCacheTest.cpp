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

static CSSSize _measure(void *context,
                        float width,
                        CSSMeasureMode widthMode,
                        float height,
                        CSSMeasureMode heightMode) {
  int *measureCount = (int *)context;
  *measureCount = *measureCount + 1;
  return CSSSize {
      .width = widthMode == CSSMeasureModeUndefined ? 10 : width,
      .height = heightMode == CSSMeasureModeUndefined ? 10 : width,
  };
}

TEST(CSSLayoutTest, measure_once_single_flexible_child) {
  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetFlexDirection(root, CSSFlexDirectionRow);
  CSSNodeStyleSetAlignItems(root, CSSAlignFlexStart);
  CSSNodeStyleSetWidth(root, 100);
  CSSNodeStyleSetHeight(root, 100);

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeStyleSetWidth(root_child0, 50);
  CSSNodeInsertChild(root, root_child0, 0);

  const CSSNodeRef root_child1 = CSSNodeNew();
  int measureCount = 0;
  CSSNodeSetContext(root_child1, &measureCount);
  CSSNodeSetMeasureFunc(root_child1, _measure);
  CSSNodeStyleSetFlexGrow(root_child1, 1);
  CSSNodeInsertChild(root, root_child1, 1);

  const CSSNodeRef root_child2 = CSSNodeNew();
  CSSNodeStyleSetWidth(root_child2, 50);
  CSSNodeInsertChild(root, root_child2, 2);

  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionLTR);

  ASSERT_EQ(1, measureCount);
}

TEST(CSSLayoutTest, dont_remeasure_text_node_height_change) {
  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetAlignItems(root, CSSAlignFlexStart);
  CSSNodeStyleSetWidth(root, 100);
  CSSNodeStyleSetHeight(root, 100);

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeStyleSetWidth(root_child0, 50);
  CSSNodeStyleSetHeight(root_child0, 20);
  CSSNodeInsertChild(root, root_child0, 0);

  const CSSNodeRef root_child1 = CSSNodeNew();
  int measureCount = 0;
  CSSNodeSetContext(root_child1, &measureCount);
  CSSNodeSetMeasureFunc(root_child1, _measure);
  CSSNodeSetIsTextnode(root_child1, true);
  CSSNodeStyleSetFlexGrow(root_child1, 1);
  CSSNodeInsertChild(root, root_child1, 1);

  const CSSNodeRef root_child2 = CSSNodeNew();
  CSSNodeStyleSetWidth(root_child2, 50);
  CSSNodeStyleSetHeight(root_child2, 20);
  CSSNodeInsertChild(root, root_child2, 2);

  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionLTR);

  ASSERT_EQ(1, measureCount);
}
