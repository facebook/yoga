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

#if GTEST_HAS_DEATH_TEST
static CSSSize _measure(CSSNodeRef node,
                        float width,
                        CSSMeasureMode widthMode,
                        float height,
                        CSSMeasureMode heightMode) {
  return CSSSize {
      .width = 0,
      .height = 0,
  };
}

TEST(CSSLayoutTest, cannot_add_child_to_node_with_measure_func) {
  const CSSNodeRef root = CSSNodeNew();
  CSSNodeSetMeasureFunc(root, _measure);

  const CSSNodeRef root_child0 = CSSNodeNew();
  ASSERT_DEATH(CSSNodeInsertChild(root, root_child0, 0), "Cannot add child.*");
  CSSNodeFreeRecursive(root);
}

TEST(CSSLayoutTest, cannot_add_nonnull_measure_func_to_non_leaf_node) {
  const CSSNodeRef root = CSSNodeNew();
  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeInsertChild(root, root_child0, 0);

  ASSERT_DEATH(CSSNodeSetMeasureFunc(root, _measure), "Cannot set measure function.*");
  CSSNodeFreeRecursive(root);
}

TEST(CSSLayoutTest, can_nullify_measure_func_on_any_node) {
  const CSSNodeRef root = CSSNodeNew();
  CSSNodeInsertChild(root, CSSNodeNew(), 0);

  CSSNodeSetMeasureFunc(root, NULL);
  ASSERT_TRUE(CSSNodeGetMeasureFunc(root) == NULL);
  CSSNodeFreeRecursive(root);
}

#endif
