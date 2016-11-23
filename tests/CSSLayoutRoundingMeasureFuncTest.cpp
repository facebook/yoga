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

static CSSSize _measureFloor(CSSNodeRef node,
  float width,
  CSSMeasureMode widthMode,
  float height,
  CSSMeasureMode heightMode) {

  return CSSSize{
    width = 10.2,
    height = 10.2,
  };
}

static CSSSize _measureCeil(CSSNodeRef node,
  float width,
  CSSMeasureMode widthMode,
  float height,
  CSSMeasureMode heightMode) {

  return CSSSize{
    width = 10.5,
    height = 10.5,
  };
}

TEST(CSSLayoutTest, rounding_feature_with_custom_measure_func_floor) {
  CSSLayoutSetExperimentalFeatureEnabled(CSSExperimentalFeatureRounding, true);

  const CSSNodeRef root = CSSNodeNew();

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeSetMeasureFunc(root_child0, _measureFloor);
  CSSNodeInsertChild(root, root_child0, 0);

  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionLTR);

  ASSERT_FLOAT_EQ(10, CSSNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(10, CSSNodeLayoutGetHeight(root_child0));

  CSSNodeFreeRecursive(root);

  CSSLayoutSetExperimentalFeatureEnabled(CSSExperimentalFeatureRounding, false);
}

TEST(CSSLayoutTest, rounding_feature_with_custom_measure_func_ceil) {
  CSSLayoutSetExperimentalFeatureEnabled(CSSExperimentalFeatureRounding, true);

  const CSSNodeRef root = CSSNodeNew();

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeSetMeasureFunc(root_child0, _measureCeil);
  CSSNodeInsertChild(root, root_child0, 0);

  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionLTR);

  ASSERT_FLOAT_EQ(11, CSSNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(11, CSSNodeLayoutGetHeight(root_child0));

  CSSNodeFreeRecursive(root);

  CSSLayoutSetExperimentalFeatureEnabled(CSSExperimentalFeatureRounding, false);
}
