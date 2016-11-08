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
  int *measureCount = (int*) CSSNodeGetContext(node);
  if (measureCount) {
    (*measureCount)++;
  }

  return CSSSize {
      .width = 10,
      .height = 10,
  };
}

TEST(CSSLayoutTest, dont_measure_single_grow_shrink_child) {
  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetWidth(root, 100);
  CSSNodeStyleSetHeight(root, 100);

  int measureCount = 0;

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeSetContext(root_child0, &measureCount);
  CSSNodeSetMeasureFunc(root_child0, _measure);
  CSSNodeStyleSetFlexGrow(root_child0, 1);
  CSSNodeStyleSetFlexShrink(root_child0, 1);
  CSSNodeInsertChild(root, root_child0, 0);

  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionLTR);

  ASSERT_EQ(0, measureCount);
}

#if GTEST_HAS_DEATH_TEST
TEST(CSSLayoutTest, cannot_add_child_to_node_with_measure_func) {
  const CSSNodeRef root = CSSNodeNew();
  CSSNodeSetMeasureFunc(root, _measure);

  const CSSNodeRef root_child0 = CSSNodeNew();
  ASSERT_DEATH(CSSNodeInsertChild(root, root_child0, 0), "Cannot add child.*");
}

TEST(CSSLayoutTest, cannot_add_measure_func_to_non_leaf_node) {
  const CSSNodeRef root = CSSNodeNew();
  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeInsertChild(root, root_child0, 0);

  ASSERT_DEATH(CSSNodeSetMeasureFunc(root, _measure), "Cannot set measure function.*");
}
#endif
