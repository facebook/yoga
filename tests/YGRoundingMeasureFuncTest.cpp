/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>
#include <yoga/YGNode.h>
#include <yoga/Yoga.h>

static YGSize _measureFloor(
    YGNodeRef /*node*/,
    float width,
    YGMeasureMode /*widthMode*/,
    float height,
    YGMeasureMode /*heightMode*/) {
  return YGSize{
      width = 10.2f,
      height = 10.2f,
  };
}

static YGSize _measureCeil(
    YGNodeRef /*node*/,
    float width,
    YGMeasureMode /*widthMode*/,
    float height,
    YGMeasureMode /*heightMode*/) {
  return YGSize{
      width = 10.5f,
      height = 10.5f,
  };
}

static YGSize _measureFractial(
    YGNodeRef /*node*/,
    float width,
    YGMeasureMode /*widthMode*/,
    float height,
    YGMeasureMode /*heightMode*/) {
  return YGSize{
      width = 0.5f,
      height = 0.5f,
  };
}

TEST(YogaTest, rounding_feature_with_custom_measure_func_floor) {
  const YGConfigRef config = YGConfigNew();
  const YGNodeRef root = YGNodeNewWithConfig(config);

  const YGNodeRef root_child0 = YGNodeNewWithConfig(config);
  root_child0->setMeasureFunc(_measureFloor);
  YGNodeInsertChild(root, root_child0, 0);

  YGConfigSetPointScaleFactor(config, 0.0f);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionRTL);

  ASSERT_FLOAT_EQ(10.2f, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(10.2f, YGNodeLayoutGetHeight(root_child0));

  YGConfigSetPointScaleFactor(config, 1.0f);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(11, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(11, YGNodeLayoutGetHeight(root_child0));

  YGConfigSetPointScaleFactor(config, 2.0f);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionRTL);

  ASSERT_FLOAT_EQ(10.5, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(10.5, YGNodeLayoutGetHeight(root_child0));

  YGConfigSetPointScaleFactor(config, 4.0f);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(10.25, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(10.25, YGNodeLayoutGetHeight(root_child0));

  YGConfigSetPointScaleFactor(config, 1.0f / 3.0f);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionRTL);

  ASSERT_FLOAT_EQ(12.0, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(12.0, YGNodeLayoutGetHeight(root_child0));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}

TEST(YogaTest, rounding_feature_with_custom_measure_func_ceil) {
  const YGConfigRef config = YGConfigNew();
  const YGNodeRef root = YGNodeNewWithConfig(config);

  const YGNodeRef root_child0 = YGNodeNewWithConfig(config);
  root_child0->setMeasureFunc(_measureCeil);
  YGNodeInsertChild(root, root_child0, 0);

  YGConfigSetPointScaleFactor(config, 1.0f);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(11, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(11, YGNodeLayoutGetHeight(root_child0));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}

TEST(
    YogaTest,
    rounding_feature_with_custom_measure_and_fractial_matching_scale) {
  const YGConfigRef config = YGConfigNew();
  const YGNodeRef root = YGNodeNewWithConfig(config);

  const YGNodeRef root_child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetPosition(root_child0, YGEdgeLeft, 73.625);
  root_child0->setMeasureFunc(_measureFractial);
  YGNodeInsertChild(root, root_child0, 0);

  YGConfigSetPointScaleFactor(config, 2.0f);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(0.5, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(0.5, YGNodeLayoutGetHeight(root_child0));
  ASSERT_FLOAT_EQ(73.5, YGNodeLayoutGetLeft(root_child0));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}
