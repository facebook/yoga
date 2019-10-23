/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>
#include <yoga/Yoga.h>
#include <array>

TEST(YogaTest, computed_layout_padding) {
  const YGNodeRef root = YGNodeNew();
  YGNodeStyleSetWidth(root, 100);
  YGNodeStyleSetHeight(root, 100);
  YGNodeStyleSetPaddingPercent(root, YGEdgeStart, 10);

  YGNodeCalculateLayout(root, 100, 100, YGDirectionLTR);

  ASSERT_FLOAT_EQ(10, YGNodeLayoutGetPadding(root, YGEdgeLeft));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetPadding(root, YGEdgeRight));

  YGNodeCalculateLayout(root, 100, 100, YGDirectionRTL);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetPadding(root, YGEdgeLeft));
  ASSERT_FLOAT_EQ(10, YGNodeLayoutGetPadding(root, YGEdgeRight));

  YGNodeFreeRecursive(root);
}

TEST(YogaTest, padding_side_overrides_horizontal_and_vertical) {
  const std::array<YGEdge, 6> edges = {{YGEdgeTop,
                                        YGEdgeBottom,
                                        YGEdgeStart,
                                        YGEdgeEnd,
                                        YGEdgeLeft,
                                        YGEdgeRight}};

  for (float edgeValue = 0; edgeValue < 2; ++edgeValue) {
    for (const auto& edge : edges) {
      YGEdge horizontalOrVertical = edge == YGEdgeTop || edge == YGEdgeBottom
          ? YGEdgeVertical
          : YGEdgeHorizontal;

      const YGNodeRef root = YGNodeNew();
      YGNodeStyleSetWidth(root, 100);
      YGNodeStyleSetHeight(root, 100);
      YGNodeStyleSetPadding(root, horizontalOrVertical, 10);
      YGNodeStyleSetPadding(root, edge, edgeValue);

      YGNodeCalculateLayout(root, 100, 100, YGDirectionLTR);

      ASSERT_FLOAT_EQ(edgeValue, YGNodeLayoutGetPadding(root, edge));

      YGNodeFreeRecursive(root);
    }
  }
}

TEST(YogaTest, padding_side_overrides_all) {
  const std::array<YGEdge, 6> edges = {{YGEdgeTop,
                                        YGEdgeBottom,
                                        YGEdgeStart,
                                        YGEdgeEnd,
                                        YGEdgeLeft,
                                        YGEdgeRight}};

  for (float edgeValue = 0; edgeValue < 2; ++edgeValue) {
    for (const auto& edge : edges) {
      const YGNodeRef root = YGNodeNew();
      YGNodeStyleSetWidth(root, 100);
      YGNodeStyleSetHeight(root, 100);
      YGNodeStyleSetPadding(root, YGEdgeAll, 10);
      YGNodeStyleSetPadding(root, edge, edgeValue);

      YGNodeCalculateLayout(root, 100, 100, YGDirectionLTR);

      ASSERT_FLOAT_EQ(edgeValue, YGNodeLayoutGetPadding(root, edge));

      YGNodeFreeRecursive(root);
    }
  }
}

TEST(YogaTest, padding_horizontal_and_vertical_overrides_all) {
  const std::array<YGEdge, 2> directions = {{YGEdgeHorizontal, YGEdgeVertical}};

  for (float directionValue = 0; directionValue < 2; ++directionValue) {
    for (const auto& direction : directions) {
      const YGNodeRef root = YGNodeNew();
      YGNodeStyleSetWidth(root, 100);
      YGNodeStyleSetHeight(root, 100);
      YGNodeStyleSetPadding(root, YGEdgeAll, 10);
      YGNodeStyleSetPadding(root, direction, directionValue);

      YGNodeCalculateLayout(root, 100, 100, YGDirectionLTR);

      if (direction == YGEdgeVertical) {
        ASSERT_FLOAT_EQ(
            directionValue, YGNodeLayoutGetPadding(root, YGEdgeTop));
        ASSERT_FLOAT_EQ(
            directionValue, YGNodeLayoutGetPadding(root, YGEdgeBottom));
      } else {
        ASSERT_FLOAT_EQ(
            directionValue, YGNodeLayoutGetPadding(root, YGEdgeStart));
        ASSERT_FLOAT_EQ(
            directionValue, YGNodeLayoutGetPadding(root, YGEdgeEnd));
        ASSERT_FLOAT_EQ(
            directionValue, YGNodeLayoutGetPadding(root, YGEdgeLeft));
        ASSERT_FLOAT_EQ(
            directionValue, YGNodeLayoutGetPadding(root, YGEdgeRight));
      }

      YGNodeFreeRecursive(root);
    }
  }
}
