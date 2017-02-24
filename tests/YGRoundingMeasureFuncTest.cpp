/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#include <gtest/gtest.h>
#include <yoga/Yoga.h>

static YGSize _measureFloor(YGNodeRef node,
                            float width,
                            YGMeasureMode widthMode,
                            float height,
                            YGMeasureMode heightMode) {
  return YGSize{
      width = 10.2f, height = 10.2f,
  };
}

static YGSize _measureCeil(YGNodeRef node,
                           float width,
                           YGMeasureMode widthMode,
                           float height,
                           YGMeasureMode heightMode) {
  return YGSize{
      width = 10.5, height = 10.5,
  };
}

TEST(YogaTest, rounding_feature_with_custom_measure_func_floor) {
  YGSetExperimentalFeatureEnabled(YGExperimentalFeatureRounding, true);

  const YGNodeRef root = YGNodeNew();

  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeSetMeasureFunc(root_child0, _measureFloor);
  YGNodeInsertChild(root, root_child0, 0);

  YGSetPointScaleFactor(0.0);
  
  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionRTL);
  
  ASSERT_FLOAT_EQ(10.2, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(10.2, YGNodeLayoutGetHeight(root_child0));

  YGSetPointScaleFactor(1.0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(10, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(10, YGNodeLayoutGetHeight(root_child0));
  
  YGSetPointScaleFactor(2.0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionRTL);

  ASSERT_FLOAT_EQ(10, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(10, YGNodeLayoutGetHeight(root_child0));
  
  YGSetPointScaleFactor(4.0);
  
  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);
  
  ASSERT_FLOAT_EQ(10.25, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(10.25, YGNodeLayoutGetHeight(root_child0));

  YGSetPointScaleFactor(1.0 / 3.0);
  
  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionRTL);
  
  ASSERT_FLOAT_EQ(9.0, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(9.0, YGNodeLayoutGetHeight(root_child0));

  YGNodeFreeRecursive(root);

  YGSetPointScaleFactor(1.0);
  YGSetExperimentalFeatureEnabled(YGExperimentalFeatureRounding, false);
}

TEST(YogaTest, rounding_feature_with_custom_measure_func_ceil) {
  YGSetExperimentalFeatureEnabled(YGExperimentalFeatureRounding, true);

  const YGNodeRef root = YGNodeNew();

  const YGNodeRef root_child0 = YGNodeNew();
  YGNodeSetMeasureFunc(root_child0, _measureCeil);
  YGNodeInsertChild(root, root_child0, 0);

  YGSetPointScaleFactor(1.0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(11, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(11, YGNodeLayoutGetHeight(root_child0));

  YGNodeFreeRecursive(root);

  YGSetPointScaleFactor(1.0);
  YGSetExperimentalFeatureEnabled(YGExperimentalFeatureRounding, false);
}
