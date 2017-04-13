/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

// @Generated by gentest/gentest.rb from gentest/fixtures/YGRoundingTest.html

#include <gtest/gtest.h>
#include <yoga/Yoga.h>

TEST(YogaTest, rounding_flex_basis_flex_grow_row_width_of_100) {
  const YGConfigRef config = YGConfigNew();
  YGConfigSetExperimentalFeatureEnabled(config, YGExperimentalFeatureRounding, true);

  const YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexDirection(root, YGFlexDirectionRow);
  YGNodeStyleSetWidth(root, 100);
  YGNodeStyleSetHeight(root, 100);

  const YGNodeRef root_child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexGrow(root_child0, 1);
  YGNodeInsertChild(root, root_child0, 0);

  const YGNodeRef root_child1 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexGrow(root_child1, 1);
  YGNodeInsertChild(root, root_child1, 1);

  const YGNodeRef root_child2 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexGrow(root_child2, 1);
  YGNodeInsertChild(root, root_child2, 2);
  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(33, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(33, YGNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(34, YGNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(67, YGNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(33, YGNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetHeight(root_child2));

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionRTL);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(67, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(33, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(33, YGNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(34, YGNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(33, YGNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetHeight(root_child2));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}

TEST(YogaTest, rounding_flex_basis_flex_grow_row_prime_number_width) {
  const YGConfigRef config = YGConfigNew();
  YGConfigSetExperimentalFeatureEnabled(config, YGExperimentalFeatureRounding, true);

  const YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexDirection(root, YGFlexDirectionRow);
  YGNodeStyleSetWidth(root, 113);
  YGNodeStyleSetHeight(root, 100);

  const YGNodeRef root_child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexGrow(root_child0, 1);
  YGNodeInsertChild(root, root_child0, 0);

  const YGNodeRef root_child1 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexGrow(root_child1, 1);
  YGNodeInsertChild(root, root_child1, 1);

  const YGNodeRef root_child2 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexGrow(root_child2, 1);
  YGNodeInsertChild(root, root_child2, 2);

  const YGNodeRef root_child3 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexGrow(root_child3, 1);
  YGNodeInsertChild(root, root_child3, 3);

  const YGNodeRef root_child4 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexGrow(root_child4, 1);
  YGNodeInsertChild(root, root_child4, 4);
  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(113, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(23, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(23, YGNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(22, YGNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(45, YGNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(23, YGNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetHeight(root_child2));

  ASSERT_FLOAT_EQ(68, YGNodeLayoutGetLeft(root_child3));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child3));
  ASSERT_FLOAT_EQ(22, YGNodeLayoutGetWidth(root_child3));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetHeight(root_child3));

  ASSERT_FLOAT_EQ(90, YGNodeLayoutGetLeft(root_child4));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child4));
  ASSERT_FLOAT_EQ(23, YGNodeLayoutGetWidth(root_child4));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetHeight(root_child4));

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionRTL);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(113, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(90, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(23, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(68, YGNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(22, YGNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(45, YGNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(23, YGNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetHeight(root_child2));

  ASSERT_FLOAT_EQ(23, YGNodeLayoutGetLeft(root_child3));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child3));
  ASSERT_FLOAT_EQ(22, YGNodeLayoutGetWidth(root_child3));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetHeight(root_child3));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child4));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child4));
  ASSERT_FLOAT_EQ(23, YGNodeLayoutGetWidth(root_child4));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetHeight(root_child4));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}

TEST(YogaTest, rounding_flex_basis_flex_shrink_row) {
  const YGConfigRef config = YGConfigNew();
  YGConfigSetExperimentalFeatureEnabled(config, YGExperimentalFeatureRounding, true);

  const YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexDirection(root, YGFlexDirectionRow);
  YGNodeStyleSetWidth(root, 101);
  YGNodeStyleSetHeight(root, 100);

  const YGNodeRef root_child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexShrink(root_child0, 1);
  YGNodeStyleSetFlexBasis(root_child0, 100);
  YGNodeInsertChild(root, root_child0, 0);

  const YGNodeRef root_child1 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexBasis(root_child1, 25);
  YGNodeInsertChild(root, root_child1, 1);

  const YGNodeRef root_child2 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexBasis(root_child2, 25);
  YGNodeInsertChild(root, root_child2, 2);
  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(101, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(51, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(51, YGNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(25, YGNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(76, YGNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(25, YGNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetHeight(root_child2));

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionRTL);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(101, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(51, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(25, YGNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(25, YGNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(25, YGNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetHeight(root_child2));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}

TEST(YogaTest, rounding_flex_basis_overrides_main_size) {
  const YGConfigRef config = YGConfigNew();
  YGConfigSetExperimentalFeatureEnabled(config, YGExperimentalFeatureRounding, true);

  const YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetWidth(root, 100);
  YGNodeStyleSetHeight(root, 113);

  const YGNodeRef root_child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexGrow(root_child0, 1);
  YGNodeStyleSetFlexBasis(root_child0, 50);
  YGNodeStyleSetHeight(root_child0, 20);
  YGNodeInsertChild(root, root_child0, 0);

  const YGNodeRef root_child1 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexGrow(root_child1, 1);
  YGNodeStyleSetHeight(root_child1, 10);
  YGNodeInsertChild(root, root_child1, 1);

  const YGNodeRef root_child2 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexGrow(root_child2, 1);
  YGNodeStyleSetHeight(root_child2, 10);
  YGNodeInsertChild(root, root_child2, 2);
  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(113, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(64, YGNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(64, YGNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(25, YGNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(89, YGNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(24, YGNodeLayoutGetHeight(root_child2));

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionRTL);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(113, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(64, YGNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(64, YGNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(25, YGNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(89, YGNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(24, YGNodeLayoutGetHeight(root_child2));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}

TEST(YogaTest, rounding_total_fractial) {
  const YGConfigRef config = YGConfigNew();
  YGConfigSetExperimentalFeatureEnabled(config, YGExperimentalFeatureRounding, true);

  const YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetWidth(root, 87.4f);
  YGNodeStyleSetHeight(root, 113.4f);

  const YGNodeRef root_child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexGrow(root_child0, 0.7f);
  YGNodeStyleSetFlexBasis(root_child0, 50.3f);
  YGNodeStyleSetHeight(root_child0, 20.3f);
  YGNodeInsertChild(root, root_child0, 0);

  const YGNodeRef root_child1 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexGrow(root_child1, 1.6f);
  YGNodeStyleSetHeight(root_child1, 10);
  YGNodeInsertChild(root, root_child1, 1);

  const YGNodeRef root_child2 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexGrow(root_child2, 1.1f);
  YGNodeStyleSetHeight(root_child2, 10.7f);
  YGNodeInsertChild(root, root_child2, 2);
  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(87, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(113, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(87, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(59, YGNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(59, YGNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(87, YGNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(30, YGNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(89, YGNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(87, YGNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(24, YGNodeLayoutGetHeight(root_child2));

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionRTL);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(87, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(113, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(87, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(59, YGNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(59, YGNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(87, YGNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(30, YGNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(89, YGNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(87, YGNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(24, YGNodeLayoutGetHeight(root_child2));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}

TEST(YogaTest, rounding_total_fractial_nested) {
  const YGConfigRef config = YGConfigNew();
  YGConfigSetExperimentalFeatureEnabled(config, YGExperimentalFeatureRounding, true);

  const YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetWidth(root, 87.4f);
  YGNodeStyleSetHeight(root, 113.4f);

  const YGNodeRef root_child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexGrow(root_child0, 0.7f);
  YGNodeStyleSetFlexBasis(root_child0, 50.3f);
  YGNodeStyleSetHeight(root_child0, 20.3f);
  YGNodeInsertChild(root, root_child0, 0);

  const YGNodeRef root_child0_child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexGrow(root_child0_child0, 1);
  YGNodeStyleSetFlexBasis(root_child0_child0, 0.3f);
  YGNodeStyleSetPosition(root_child0_child0, YGEdgeBottom, 13.3f);
  YGNodeStyleSetHeight(root_child0_child0, 9.9f);
  YGNodeInsertChild(root_child0, root_child0_child0, 0);

  const YGNodeRef root_child0_child1 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexGrow(root_child0_child1, 4);
  YGNodeStyleSetFlexBasis(root_child0_child1, 0.3f);
  YGNodeStyleSetPosition(root_child0_child1, YGEdgeTop, 13.3f);
  YGNodeStyleSetHeight(root_child0_child1, 1.1f);
  YGNodeInsertChild(root_child0, root_child0_child1, 1);

  const YGNodeRef root_child1 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexGrow(root_child1, 1.6f);
  YGNodeStyleSetHeight(root_child1, 10);
  YGNodeInsertChild(root, root_child1, 1);

  const YGNodeRef root_child2 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexGrow(root_child2, 1.1f);
  YGNodeStyleSetHeight(root_child2, 10.7f);
  YGNodeInsertChild(root, root_child2, 2);
  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(87, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(113, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(87, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(59, YGNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0_child0));
  ASSERT_FLOAT_EQ(-13, YGNodeLayoutGetTop(root_child0_child0));
  ASSERT_FLOAT_EQ(87, YGNodeLayoutGetWidth(root_child0_child0));
  ASSERT_FLOAT_EQ(12, YGNodeLayoutGetHeight(root_child0_child0));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0_child1));
  ASSERT_FLOAT_EQ(25, YGNodeLayoutGetTop(root_child0_child1));
  ASSERT_FLOAT_EQ(87, YGNodeLayoutGetWidth(root_child0_child1));
  ASSERT_FLOAT_EQ(47, YGNodeLayoutGetHeight(root_child0_child1));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(59, YGNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(87, YGNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(30, YGNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(89, YGNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(87, YGNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(24, YGNodeLayoutGetHeight(root_child2));

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionRTL);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(87, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(113, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(87, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(59, YGNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0_child0));
  ASSERT_FLOAT_EQ(-13, YGNodeLayoutGetTop(root_child0_child0));
  ASSERT_FLOAT_EQ(87, YGNodeLayoutGetWidth(root_child0_child0));
  ASSERT_FLOAT_EQ(12, YGNodeLayoutGetHeight(root_child0_child0));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0_child1));
  ASSERT_FLOAT_EQ(25, YGNodeLayoutGetTop(root_child0_child1));
  ASSERT_FLOAT_EQ(87, YGNodeLayoutGetWidth(root_child0_child1));
  ASSERT_FLOAT_EQ(47, YGNodeLayoutGetHeight(root_child0_child1));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(59, YGNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(87, YGNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(30, YGNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(89, YGNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(87, YGNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(24, YGNodeLayoutGetHeight(root_child2));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}

TEST(YogaTest, rounding_fractial_input_1) {
  const YGConfigRef config = YGConfigNew();
  YGConfigSetExperimentalFeatureEnabled(config, YGExperimentalFeatureRounding, true);

  const YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetWidth(root, 100);
  YGNodeStyleSetHeight(root, 113.4f);

  const YGNodeRef root_child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexGrow(root_child0, 1);
  YGNodeStyleSetFlexBasis(root_child0, 50);
  YGNodeStyleSetHeight(root_child0, 20);
  YGNodeInsertChild(root, root_child0, 0);

  const YGNodeRef root_child1 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexGrow(root_child1, 1);
  YGNodeStyleSetHeight(root_child1, 10);
  YGNodeInsertChild(root, root_child1, 1);

  const YGNodeRef root_child2 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexGrow(root_child2, 1);
  YGNodeStyleSetHeight(root_child2, 10);
  YGNodeInsertChild(root, root_child2, 2);
  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(113, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(64, YGNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(64, YGNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(25, YGNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(89, YGNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(24, YGNodeLayoutGetHeight(root_child2));

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionRTL);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(113, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(64, YGNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(64, YGNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(25, YGNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(89, YGNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(24, YGNodeLayoutGetHeight(root_child2));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}

TEST(YogaTest, rounding_fractial_input_2) {
  const YGConfigRef config = YGConfigNew();
  YGConfigSetExperimentalFeatureEnabled(config, YGExperimentalFeatureRounding, true);

  const YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetWidth(root, 100);
  YGNodeStyleSetHeight(root, 113.6f);

  const YGNodeRef root_child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexGrow(root_child0, 1);
  YGNodeStyleSetFlexBasis(root_child0, 50);
  YGNodeStyleSetHeight(root_child0, 20);
  YGNodeInsertChild(root, root_child0, 0);

  const YGNodeRef root_child1 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexGrow(root_child1, 1);
  YGNodeStyleSetHeight(root_child1, 10);
  YGNodeInsertChild(root, root_child1, 1);

  const YGNodeRef root_child2 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexGrow(root_child2, 1);
  YGNodeStyleSetHeight(root_child2, 10);
  YGNodeInsertChild(root, root_child2, 2);
  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(114, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(65, YGNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(65, YGNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(24, YGNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(89, YGNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(25, YGNodeLayoutGetHeight(root_child2));

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionRTL);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(114, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(65, YGNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(65, YGNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(24, YGNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(89, YGNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(25, YGNodeLayoutGetHeight(root_child2));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}

TEST(YogaTest, rounding_fractial_input_3) {
  const YGConfigRef config = YGConfigNew();
  YGConfigSetExperimentalFeatureEnabled(config, YGExperimentalFeatureRounding, true);

  const YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetPosition(root, YGEdgeTop, 0.1f);
  YGNodeStyleSetWidth(root, 100);
  YGNodeStyleSetHeight(root, 113.1f);

  const YGNodeRef root_child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexGrow(root_child0, 1);
  YGNodeStyleSetFlexBasis(root_child0, 50);
  YGNodeStyleSetHeight(root_child0, 20);
  YGNodeInsertChild(root, root_child0, 0);

  const YGNodeRef root_child1 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexGrow(root_child1, 1);
  YGNodeStyleSetHeight(root_child1, 10);
  YGNodeInsertChild(root, root_child1, 1);

  const YGNodeRef root_child2 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexGrow(root_child2, 1);
  YGNodeStyleSetHeight(root_child2, 10);
  YGNodeInsertChild(root, root_child2, 2);
  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(113, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(64, YGNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(64, YGNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(25, YGNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(89, YGNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(24, YGNodeLayoutGetHeight(root_child2));

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionRTL);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(113, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(64, YGNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(64, YGNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(25, YGNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(89, YGNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(24, YGNodeLayoutGetHeight(root_child2));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}

TEST(YogaTest, rounding_fractial_input_4) {
  const YGConfigRef config = YGConfigNew();
  YGConfigSetExperimentalFeatureEnabled(config, YGExperimentalFeatureRounding, true);

  const YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetPosition(root, YGEdgeTop, 0.7f);
  YGNodeStyleSetWidth(root, 100);
  YGNodeStyleSetHeight(root, 113.4f);

  const YGNodeRef root_child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexGrow(root_child0, 1);
  YGNodeStyleSetFlexBasis(root_child0, 50);
  YGNodeStyleSetHeight(root_child0, 20);
  YGNodeInsertChild(root, root_child0, 0);

  const YGNodeRef root_child1 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexGrow(root_child1, 1);
  YGNodeStyleSetHeight(root_child1, 10);
  YGNodeInsertChild(root, root_child1, 1);

  const YGNodeRef root_child2 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexGrow(root_child2, 1);
  YGNodeStyleSetHeight(root_child2, 10);
  YGNodeInsertChild(root, root_child2, 2);
  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(1, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(113, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(64, YGNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(64, YGNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(25, YGNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(89, YGNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(24, YGNodeLayoutGetHeight(root_child2));

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionRTL);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(1, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(113, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(64, YGNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(64, YGNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(25, YGNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(89, YGNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(24, YGNodeLayoutGetHeight(root_child2));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}

TEST(YogaTest, rounding_fractial_input_5_x) {
  const YGConfigRef config = YGConfigNew();
  YGConfigSetExperimentalFeatureEnabled(config, YGExperimentalFeatureRounding, true);

  const YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexDirection(root, YGFlexDirectionRow);
  YGNodeStyleSetPosition(root, YGEdgeTop, 0.4f);
  YGNodeStyleSetWidth(root, 100);
  YGNodeStyleSetHeight(root, 100.4f);

  const YGNodeRef root_child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetWidth(root_child0, 10);
  YGNodeStyleSetHeightPercent(root_child0, 100);
  YGNodeInsertChild(root, root_child0, 0);

  const YGNodeRef root_child1 = YGNodeNewWithConfig(config);
  YGNodeStyleSetWidth(root_child1, 10);
  YGNodeStyleSetHeightPercent(root_child1, 100);
  YGNodeInsertChild(root, root_child1, 1);

  const YGNodeRef root_child2 = YGNodeNewWithConfig(config);
  YGNodeStyleSetWidth(root_child2, 10);
  YGNodeStyleSetHeightPercent(root_child2, 100);
  YGNodeInsertChild(root, root_child2, 2);
  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(101, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(10, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(101, YGNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(10, YGNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(10, YGNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(101, YGNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(20, YGNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(10, YGNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(101, YGNodeLayoutGetHeight(root_child2));

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionRTL);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(101, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(90, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(10, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(101, YGNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(80, YGNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(10, YGNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(101, YGNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(70, YGNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(10, YGNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(101, YGNodeLayoutGetHeight(root_child2));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}

TEST(YogaTest, rounding_fractial_input_5_y) {
  const YGConfigRef config = YGConfigNew();
  YGConfigSetExperimentalFeatureEnabled(config, YGExperimentalFeatureRounding, true);

  const YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetMargin(root, YGEdgeLeft, 0.4f);
  YGNodeStyleSetWidth(root, 100.4f);
  YGNodeStyleSetHeight(root, 100);

  const YGNodeRef root_child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetWidthPercent(root_child0, 100);
  YGNodeStyleSetHeight(root_child0, 10);
  YGNodeInsertChild(root, root_child0, 0);

  const YGNodeRef root_child1 = YGNodeNewWithConfig(config);
  YGNodeStyleSetWidthPercent(root_child1, 100);
  YGNodeStyleSetHeight(root_child1, 10);
  YGNodeInsertChild(root, root_child1, 1);

  const YGNodeRef root_child2 = YGNodeNewWithConfig(config);
  YGNodeStyleSetWidthPercent(root_child2, 100);
  YGNodeStyleSetHeight(root_child2, 10);
  YGNodeInsertChild(root, root_child2, 2);
  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(101, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(101, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(10, YGNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(10, YGNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(101, YGNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(10, YGNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(20, YGNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(101, YGNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(10, YGNodeLayoutGetHeight(root_child2));

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionRTL);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(101, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(101, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(10, YGNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(10, YGNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(101, YGNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(10, YGNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(20, YGNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(101, YGNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(10, YGNodeLayoutGetHeight(root_child2));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}
