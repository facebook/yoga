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
  const YGConfigRef config = YGConfigNew();
  const YGNodeRef root = YGNodeNewWithConfig(config);

  const YGNodeRef root_child0 = YGNodeNewWithConfig(config);
  YGNodeSetMeasureFunc(root_child0, _measureFloor);
  YGNodeInsertChild(root, root_child0, 0);

  YGConfigSetPointScaleFactor(config, 0.0f);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionRTL);

  ASSERT_FLOAT_EQ(10.2, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(10.2, YGNodeLayoutGetHeight(root_child0));

  YGConfigSetPointScaleFactor(config, 1.0f);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(10, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(10, YGNodeLayoutGetHeight(root_child0));

  YGConfigSetPointScaleFactor(config, 2.0f);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionRTL);

  ASSERT_FLOAT_EQ(10, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(10, YGNodeLayoutGetHeight(root_child0));

  YGConfigSetPointScaleFactor(config, 4.0f);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(10.25f, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(10.25, YGNodeLayoutGetHeight(root_child0));

  YGConfigSetPointScaleFactor(config, 1.0f / 3.0f);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionRTL);

  ASSERT_FLOAT_EQ(9.0, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(9.0, YGNodeLayoutGetHeight(root_child0));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}

TEST(YogaTest, rounding_feature_with_custom_measure_func_ceil) {
  const YGConfigRef config = YGConfigNew();
  const YGNodeRef root = YGNodeNewWithConfig(config);

  const YGNodeRef root_child0 = YGNodeNewWithConfig(config);
  YGNodeSetMeasureFunc(root_child0, _measureCeil);
  YGNodeInsertChild(root, root_child0, 0);

  YGConfigSetPointScaleFactor(config, 1.0f);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(11, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(11, YGNodeLayoutGetHeight(root_child0));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}
