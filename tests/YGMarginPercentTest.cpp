/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the LICENSE
 * file in the root directory of this source tree.
 */

#include <gtest/gtest.h>
#include <yoga/Yoga.h>

static YGSize _measureCk_test_label_shrink_based_on_height(
        YGNodeRef node,
        float width,
        YGMeasureMode widthMode,
        float height,
        YGMeasureMode heightMode) {

    if (heightMode == YGMeasureModeAtMost) {
        return YGSize{
                .width = 290,
                .height = 103,
        };
    } else {
        return YGSize{
                .width = 290,
                .height = height,
        };
    }
}

TEST(YogaTest, margin_percent_with_measure_func) {
  const YGConfigRef config = YGConfigNew();

  const YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetWidth(root, 320);

  const YGNodeRef root_child0 = YGNodeNewWithConfig(config);
  YGNodeInsertChild(root, root_child0, 0);

  const YGNodeRef root_child0_child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetHeight(root_child0_child0, 450);
  YGNodeInsertChild(root_child0, root_child0_child0, 0);

  const YGNodeRef root_child0_child0_child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexDirection(root_child0_child0_child0, YGFlexDirectionRow);
  YGNodeStyleSetMarginPercent(root_child0_child0_child0, YGEdgeTop, 5);
  YGNodeInsertChild(root_child0_child0, root_child0_child0_child0, 0);

  const YGNodeRef root_child0_child0_child0_child0 =
          YGNodeNewWithConfig(config);
  YGNodeSetMeasureFunc(
          root_child0_child0_child0_child0,
          _measureCk_test_label_shrink_based_on_height);
  YGNodeInsertChild(
          root_child0_child0_child0, root_child0_child0_child0_child0, 0);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(320, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(450, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(320, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(450, YGNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0_child0));
  ASSERT_FLOAT_EQ(320, YGNodeLayoutGetWidth(root_child0_child0));
  ASSERT_FLOAT_EQ(450, YGNodeLayoutGetHeight(root_child0_child0));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0_child0_child0));
  ASSERT_FLOAT_EQ(16, YGNodeLayoutGetTop(root_child0_child0_child0));
  ASSERT_FLOAT_EQ(320, YGNodeLayoutGetWidth(root_child0_child0_child0));
  ASSERT_FLOAT_EQ(103, YGNodeLayoutGetHeight(root_child0_child0_child0));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0_child0_child0_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0_child0_child0_child0));
  ASSERT_FLOAT_EQ(290, YGNodeLayoutGetWidth(root_child0_child0_child0_child0));
  ASSERT_FLOAT_EQ(103, YGNodeLayoutGetHeight(root_child0_child0_child0_child0));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}
