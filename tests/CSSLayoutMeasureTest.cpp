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

static CSSSize _measure(CSSNodeRef node,
                        float width,
                        CSSMeasureMode widthMode,
                        float height,
                        CSSMeasureMode heightMode) {
  int *measureCount = (int *)CSSNodeGetContext(node);
  *measureCount = *measureCount + 1;
  return CSSSize {
      .width = widthMode == CSSMeasureModeUndefined ? 10 : width,
      .height = heightMode == CSSMeasureModeUndefined ? 10 : width,
  };
}

TEST(CSSLayoutTest, ignore_measure_on_non_leaf_node) {
  const CSSNodeRef root = CSSNodeNew();
  int measureCount = 0;
  CSSNodeSetContext(root, &measureCount);
  CSSNodeSetMeasureFunc(root, _measure);

  const CSSNodeRef root_child0 = CSSNodeNew();
  int childMeasureCount = 0;
  CSSNodeSetContext(root_child0, &childMeasureCount);
  CSSNodeSetMeasureFunc(root_child0, _measure);
  CSSNodeInsertChild(root, root_child0, 0);

  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionLTR);

  ASSERT_EQ(0, measureCount);
  ASSERT_EQ(1, childMeasureCount);

  CSSNodeFreeRecursive(root);
}
