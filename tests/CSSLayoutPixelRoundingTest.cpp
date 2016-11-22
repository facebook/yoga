/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

/*
*
<div id="pixel_rounding_flex_basis_flex_grow_row_width_of_100" style="width: 100px; height: 100px; flex-direction: row;">
 <div style="flex-grow: 1;"></div>
 <div style="flex-grow: 1;"></div>
 <div style="flex-grow: 1;"></div>
</div>

<div id="pixel_rounding_flex_basis_flex_grow_row_prime_number_width" style="width: 113px; height: 100px; flex-direction: row;">
 <div style="flex-grow: 1;"></div>
 <div style="flex-grow: 1;"></div>
 <div style="flex-grow: 1;"></div>
 <div style="flex-grow: 1;"></div>
 <div style="flex-grow: 1;"></div>
</div>

<div id="pixel_rounding_flex_basis_flex_shrink_row" style="width: 101px; height: 100px; flex-direction: row;">
 <div style="flex-basis: 100px; flex-shrink: 1;"></div>
 <div style="flex-basis: 25px;"></div>
 <div style="flex-basis: 25px;"></div>
</div>

<div id="pixel_rounding_flex_basis_overrides_main_size" style="height: 113px; width: 100px;">
 <div style="height: 20px; flex-grow:1; flex-basis:50px;"></div>
 <div style="height: 10px; flex-grow:1;"></div>
 <div style="height: 10px; flex-grow:1;"></div>
</div>

<div id="rounding_feature_total_fractial" style="height: 113.4px; width: 87.4px;">
 <div style="height: 20.3px; flex-grow:0.7; flex-basis:50.3px;"></div>
 <div style="height: 10px; flex-grow:1.6;"></div>
 <div style="height: 10.7px; flex-grow:1.1;"></div>
</div>

<div id="rounding_feature_total_fractial_nested" style="height: 113.4px; width: 87.4px;">
 <div style="height: 20.3px; flex-grow:0.7; flex-basis:50.3px;">
   <div style="bottom: 13.3px; height: 9.9px; flex-grow:1.2; flex-basis:0.3px;"></div>
   <div style="top: 13.3px; height: 1.1px; flex-grow:4.2; flex-basis:0.3px;"></div>
 </div>
 <div style="height: 10px; flex-grow:1.6;"></div>
 <div style="height: 10.7px; flex-grow:1.1;"></div>
</div>
 *
 */

#include <CSSLayout/CSSLayout.h>
#include <gtest/gtest.h>

class CSSLayoutFeatureRoundingTest : public ::testing::Test {

protected:
  virtual void SetUp() {
    CSSLayoutSetExperimentalFeatureEnabled(CSSExperimentalFeatureRounding, true);
  }

  virtual void TearDown() {
    CSSLayoutSetExperimentalFeatureEnabled(CSSExperimentalFeatureRounding, false);
  }
};

TEST_F(CSSLayoutFeatureRoundingTest, pixel_rounding_flex_basis_flex_grow_row_width_of_100) {
  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetFlexDirection(root, CSSFlexDirectionRow);
  CSSNodeStyleSetWidth(root, 100);
  CSSNodeStyleSetHeight(root, 100);

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeStyleSetFlexGrow(root_child0, 1);
  CSSNodeInsertChild(root, root_child0, 0);

  const CSSNodeRef root_child1 = CSSNodeNew();
  CSSNodeStyleSetFlexGrow(root_child1, 1);
  CSSNodeInsertChild(root, root_child1, 1);

  const CSSNodeRef root_child2 = CSSNodeNew();
  CSSNodeStyleSetFlexGrow(root_child2, 1);
  CSSNodeInsertChild(root, root_child2, 2);
  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionLTR);

  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(100, CSSNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(100, CSSNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(33, CSSNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(100, CSSNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(33, CSSNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(34, CSSNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(100, CSSNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(67, CSSNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(33, CSSNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(100, CSSNodeLayoutGetHeight(root_child2));

  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionRTL);

  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(100, CSSNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(100, CSSNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(67, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(33, CSSNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(100, CSSNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(33, CSSNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(34, CSSNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(100, CSSNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(33, CSSNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(100, CSSNodeLayoutGetHeight(root_child2));

  CSSNodeFreeRecursive(root);
}

TEST_F(CSSLayoutFeatureRoundingTest, pixel_rounding_flex_basis_flex_grow_row_prime_number_width) {
  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetFlexDirection(root, CSSFlexDirectionRow);
  CSSNodeStyleSetWidth(root, 113);
  CSSNodeStyleSetHeight(root, 100);

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeStyleSetFlexGrow(root_child0, 1);
  CSSNodeInsertChild(root, root_child0, 0);

  const CSSNodeRef root_child1 = CSSNodeNew();
  CSSNodeStyleSetFlexGrow(root_child1, 1);
  CSSNodeInsertChild(root, root_child1, 1);

  const CSSNodeRef root_child2 = CSSNodeNew();
  CSSNodeStyleSetFlexGrow(root_child2, 1);
  CSSNodeInsertChild(root, root_child2, 2);

  const CSSNodeRef root_child3 = CSSNodeNew();
  CSSNodeStyleSetFlexGrow(root_child3, 1);
  CSSNodeInsertChild(root, root_child3, 3);

  const CSSNodeRef root_child4 = CSSNodeNew();
  CSSNodeStyleSetFlexGrow(root_child4, 1);
  CSSNodeInsertChild(root, root_child4, 4);
  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionLTR);

  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(113, CSSNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(100, CSSNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(23, CSSNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(100, CSSNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(23, CSSNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(22, CSSNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(100, CSSNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(45, CSSNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(23, CSSNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(100, CSSNodeLayoutGetHeight(root_child2));

  ASSERT_FLOAT_EQ(68, CSSNodeLayoutGetLeft(root_child3));
  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetTop(root_child3));
  ASSERT_FLOAT_EQ(22, CSSNodeLayoutGetWidth(root_child3));
  ASSERT_FLOAT_EQ(100, CSSNodeLayoutGetHeight(root_child3));

  ASSERT_FLOAT_EQ(90, CSSNodeLayoutGetLeft(root_child4));
  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetTop(root_child4));
  ASSERT_FLOAT_EQ(23, CSSNodeLayoutGetWidth(root_child4));
  ASSERT_FLOAT_EQ(100, CSSNodeLayoutGetHeight(root_child4));

  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionRTL);

  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(113, CSSNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(100, CSSNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(90, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(23, CSSNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(100, CSSNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(68, CSSNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(22, CSSNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(100, CSSNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(45, CSSNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(23, CSSNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(100, CSSNodeLayoutGetHeight(root_child2));

  ASSERT_FLOAT_EQ(23, CSSNodeLayoutGetLeft(root_child3));
  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetTop(root_child3));
  ASSERT_FLOAT_EQ(22, CSSNodeLayoutGetWidth(root_child3));
  ASSERT_FLOAT_EQ(100, CSSNodeLayoutGetHeight(root_child3));

  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetLeft(root_child4));
  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetTop(root_child4));
  ASSERT_FLOAT_EQ(23, CSSNodeLayoutGetWidth(root_child4));
  ASSERT_FLOAT_EQ(100, CSSNodeLayoutGetHeight(root_child4));

  CSSNodeFreeRecursive(root);
}

TEST_F(CSSLayoutFeatureRoundingTest, pixel_rounding_flex_basis_flex_shrink_row) {
  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetFlexDirection(root, CSSFlexDirectionRow);
  CSSNodeStyleSetWidth(root, 101);
  CSSNodeStyleSetHeight(root, 100);

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeStyleSetFlexShrink(root_child0, 1);
  CSSNodeStyleSetFlexBasis(root_child0, 100);
  CSSNodeInsertChild(root, root_child0, 0);

  const CSSNodeRef root_child1 = CSSNodeNew();
  CSSNodeStyleSetFlexBasis(root_child1, 25);
  CSSNodeInsertChild(root, root_child1, 1);

  const CSSNodeRef root_child2 = CSSNodeNew();
  CSSNodeStyleSetFlexBasis(root_child2, 25);
  CSSNodeInsertChild(root, root_child2, 2);
  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionLTR);

  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(101, CSSNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(100, CSSNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(51, CSSNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(100, CSSNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(51, CSSNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(25, CSSNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(100, CSSNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(76, CSSNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(25, CSSNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(100, CSSNodeLayoutGetHeight(root_child2));

  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionRTL);

  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(101, CSSNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(100, CSSNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(50, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(51, CSSNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(100, CSSNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(25, CSSNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(25, CSSNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(100, CSSNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(25, CSSNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(100, CSSNodeLayoutGetHeight(root_child2));

  CSSNodeFreeRecursive(root);
}


TEST_F(CSSLayoutFeatureRoundingTest, pixel_roundingflex_basis_overrides_main_size) {
  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetWidth(root, 100);
  CSSNodeStyleSetHeight(root, 113);

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeStyleSetFlexGrow(root_child0, 1);
  CSSNodeStyleSetFlexBasis(root_child0, 50);
  CSSNodeStyleSetHeight(root_child0, 20);
  CSSNodeInsertChild(root, root_child0, 0);

  const CSSNodeRef root_child1 = CSSNodeNew();
  CSSNodeStyleSetFlexGrow(root_child1, 1);
  CSSNodeStyleSetHeight(root_child1, 10);
  CSSNodeInsertChild(root, root_child1, 1);

  const CSSNodeRef root_child2 = CSSNodeNew();
  CSSNodeStyleSetFlexGrow(root_child2, 1);
  CSSNodeStyleSetHeight(root_child2, 10);
  CSSNodeInsertChild(root, root_child2, 2);
  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionLTR);

  ASSERT_EQ(0, CSSNodeLayoutGetLeft(root));
  ASSERT_EQ(0, CSSNodeLayoutGetTop(root));
  ASSERT_EQ(100, CSSNodeLayoutGetWidth(root));
  ASSERT_EQ(113, CSSNodeLayoutGetHeight(root));

  ASSERT_EQ(0, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, CSSNodeLayoutGetTop(root_child0));
  ASSERT_EQ(100, CSSNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(64, CSSNodeLayoutGetHeight(root_child0));

  ASSERT_EQ(0, CSSNodeLayoutGetLeft(root_child1));
  ASSERT_EQ(64, CSSNodeLayoutGetTop(root_child1));
  ASSERT_EQ(100, CSSNodeLayoutGetWidth(root_child1));
  ASSERT_EQ(25, CSSNodeLayoutGetHeight(root_child1));

  ASSERT_EQ(0, CSSNodeLayoutGetLeft(root_child2));
  ASSERT_EQ(89, CSSNodeLayoutGetTop(root_child2));
  ASSERT_EQ(100, CSSNodeLayoutGetWidth(root_child2));
  ASSERT_EQ(24, CSSNodeLayoutGetHeight(root_child2));

  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionRTL);

  ASSERT_EQ(0, CSSNodeLayoutGetLeft(root));
  ASSERT_EQ(0, CSSNodeLayoutGetTop(root));
  ASSERT_EQ(100, CSSNodeLayoutGetWidth(root));
  ASSERT_EQ(113, CSSNodeLayoutGetHeight(root));

  ASSERT_EQ(0, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_EQ(0, CSSNodeLayoutGetTop(root_child0));
  ASSERT_EQ(100, CSSNodeLayoutGetWidth(root_child0));
  ASSERT_EQ(64, CSSNodeLayoutGetHeight(root_child0));

  ASSERT_EQ(0, CSSNodeLayoutGetLeft(root_child1));
  ASSERT_EQ(64, CSSNodeLayoutGetTop(root_child1));
  ASSERT_EQ(100, CSSNodeLayoutGetWidth(root_child1));
  ASSERT_EQ(25, CSSNodeLayoutGetHeight(root_child1));

  ASSERT_EQ(0, CSSNodeLayoutGetLeft(root_child2));
  ASSERT_EQ(89, CSSNodeLayoutGetTop(root_child2));
  ASSERT_EQ(100, CSSNodeLayoutGetWidth(root_child2));
  ASSERT_EQ(24, CSSNodeLayoutGetHeight(root_child2));

  CSSNodeFreeRecursive(root);
}

TEST_F(CSSLayoutFeatureRoundingTest, flex_basis_overrides_main_size_1) {
  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetWidth(root, 100);
  CSSNodeStyleSetHeight(root, 113.4f);

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeStyleSetFlexGrow(root_child0, 1);
  CSSNodeStyleSetFlexBasis(root_child0, 50);
  CSSNodeStyleSetHeight(root_child0, 20);
  CSSNodeInsertChild(root, root_child0, 0);

  const CSSNodeRef root_child1 = CSSNodeNew();
  CSSNodeStyleSetFlexGrow(root_child1, 1);
  CSSNodeStyleSetHeight(root_child1, 10);
  CSSNodeInsertChild(root, root_child1, 1);

  const CSSNodeRef root_child2 = CSSNodeNew();
  CSSNodeStyleSetFlexGrow(root_child2, 1);
  CSSNodeStyleSetHeight(root_child2, 10);
  CSSNodeInsertChild(root, root_child2, 2);
  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionLTR);

  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(100, CSSNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(113, CSSNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(100, CSSNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(64, CSSNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(64, CSSNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(100, CSSNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(25, CSSNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(89, CSSNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(100, CSSNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(24, CSSNodeLayoutGetHeight(root_child2));

  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionRTL);

  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(100, CSSNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(113, CSSNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(100, CSSNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(64, CSSNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(64, CSSNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(100, CSSNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(25, CSSNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(89, CSSNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(100, CSSNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(24, CSSNodeLayoutGetHeight(root_child2));

  CSSNodeFreeRecursive(root);
}

TEST_F(CSSLayoutFeatureRoundingTest, flex_basis_overrides_main_size_2) {
  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetWidth(root, 100);
  CSSNodeStyleSetHeight(root, 113.6f);

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeStyleSetFlexGrow(root_child0, 1);
  CSSNodeStyleSetFlexBasis(root_child0, 50);
  CSSNodeStyleSetHeight(root_child0, 20);
  CSSNodeInsertChild(root, root_child0, 0);

  const CSSNodeRef root_child1 = CSSNodeNew();
  CSSNodeStyleSetFlexGrow(root_child1, 1);
  CSSNodeStyleSetHeight(root_child1, 10);
  CSSNodeInsertChild(root, root_child1, 1);

  const CSSNodeRef root_child2 = CSSNodeNew();
  CSSNodeStyleSetFlexGrow(root_child2, 1);
  CSSNodeStyleSetHeight(root_child2, 10);
  CSSNodeInsertChild(root, root_child2, 2);
  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionLTR);

  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(100, CSSNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(114, CSSNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(100, CSSNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(65, CSSNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(65, CSSNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(100, CSSNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(24, CSSNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(89, CSSNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(100, CSSNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(25, CSSNodeLayoutGetHeight(root_child2));

  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionRTL);

  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(100, CSSNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(114, CSSNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(100, CSSNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(65, CSSNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(65, CSSNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(100, CSSNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(24, CSSNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(89, CSSNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(100, CSSNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(25, CSSNodeLayoutGetHeight(root_child2));

  CSSNodeFreeRecursive(root);
}

TEST_F(CSSLayoutFeatureRoundingTest, flex_basis_overrides_main_size_3) {
  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetPosition(root, CSSEdgeTop, 0.3f);
  CSSNodeStyleSetWidth(root, 100);
  CSSNodeStyleSetHeight(root, 113.4f);

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeStyleSetFlexGrow(root_child0, 1);
  CSSNodeStyleSetFlexBasis(root_child0, 50);
  CSSNodeStyleSetHeight(root_child0, 20);
  CSSNodeInsertChild(root, root_child0, 0);

  const CSSNodeRef root_child1 = CSSNodeNew();
  CSSNodeStyleSetFlexGrow(root_child1, 1);
  CSSNodeStyleSetHeight(root_child1, 10);
  CSSNodeInsertChild(root, root_child1, 1);

  const CSSNodeRef root_child2 = CSSNodeNew();
  CSSNodeStyleSetFlexGrow(root_child2, 1);
  CSSNodeStyleSetHeight(root_child2, 10);
  CSSNodeInsertChild(root, root_child2, 2);
  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionLTR);

  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(100, CSSNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(114, CSSNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(100, CSSNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(64, CSSNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(64, CSSNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(100, CSSNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(25, CSSNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(89, CSSNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(100, CSSNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(24, CSSNodeLayoutGetHeight(root_child2));

  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionRTL);

  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(100, CSSNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(114, CSSNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(100, CSSNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(64, CSSNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(64, CSSNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(100, CSSNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(25, CSSNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(89, CSSNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(100, CSSNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(24, CSSNodeLayoutGetHeight(root_child2));

  CSSNodeFreeRecursive(root);
}

TEST_F(CSSLayoutFeatureRoundingTest, flex_basis_overrides_main_size_4) {
  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetPosition(root, CSSEdgeTop, 0.7f);
  CSSNodeStyleSetWidth(root, 100);
  CSSNodeStyleSetHeight(root, 113.4f);

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeStyleSetFlexGrow(root_child0, 1);
  CSSNodeStyleSetFlexBasis(root_child0, 50);
  CSSNodeStyleSetHeight(root_child0, 20);
  CSSNodeInsertChild(root, root_child0, 0);

  const CSSNodeRef root_child1 = CSSNodeNew();
  CSSNodeStyleSetFlexGrow(root_child1, 1);
  CSSNodeStyleSetHeight(root_child1, 10);
  CSSNodeInsertChild(root, root_child1, 1);

  const CSSNodeRef root_child2 = CSSNodeNew();
  CSSNodeStyleSetFlexGrow(root_child2, 1);
  CSSNodeStyleSetHeight(root_child2, 10);
  CSSNodeInsertChild(root, root_child2, 2);
  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionLTR);

  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(1, CSSNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(100, CSSNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(113, CSSNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(100, CSSNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(64, CSSNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(64, CSSNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(100, CSSNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(25, CSSNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(89, CSSNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(100, CSSNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(24, CSSNodeLayoutGetHeight(root_child2));

  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionRTL);

  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(1, CSSNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(100, CSSNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(113, CSSNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(100, CSSNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(64, CSSNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(64, CSSNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(100, CSSNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(25, CSSNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(89, CSSNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(100, CSSNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(24, CSSNodeLayoutGetHeight(root_child2));

  CSSNodeFreeRecursive(root);
}

TEST_F(CSSLayoutFeatureRoundingTest, rounding_feature_total_fractial) {
  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetWidth(root, 87.4f);
  CSSNodeStyleSetHeight(root, 113.4f);

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeStyleSetFlexGrow(root_child0, 0.7f);
  CSSNodeStyleSetFlexBasis(root_child0, 50.3f);
  CSSNodeStyleSetHeight(root_child0, 20.3f);
  CSSNodeInsertChild(root, root_child0, 0);

  const CSSNodeRef root_child1 = CSSNodeNew();
  CSSNodeStyleSetFlexGrow(root_child1, 1.6f);
  CSSNodeStyleSetHeight(root_child1, 10);
  CSSNodeInsertChild(root, root_child1, 1);

  const CSSNodeRef root_child2 = CSSNodeNew();
  CSSNodeStyleSetFlexGrow(root_child2, 1.1f);
  CSSNodeStyleSetHeight(root_child2, 10.7f);
  CSSNodeInsertChild(root, root_child2, 2);
  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionLTR);

  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(87, CSSNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(113, CSSNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(87, CSSNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(59, CSSNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(59, CSSNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(87, CSSNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(30, CSSNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(89, CSSNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(87, CSSNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(24, CSSNodeLayoutGetHeight(root_child2));

  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionRTL);

  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(87, CSSNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(113, CSSNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(87, CSSNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(59, CSSNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(59, CSSNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(87, CSSNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(30, CSSNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(89, CSSNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(87, CSSNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(24, CSSNodeLayoutGetHeight(root_child2));

  CSSNodeFreeRecursive(root);
}


TEST_F(CSSLayoutFeatureRoundingTest, rounding_feature_total_fractial_nested) {
  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetWidth(root, 87.4f);
  CSSNodeStyleSetHeight(root, 113.4f);

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeStyleSetFlexGrow(root_child0, 0.7f);
  CSSNodeStyleSetFlexBasis(root_child0, 50.3f);
  CSSNodeStyleSetHeight(root_child0, 20.3f);
  CSSNodeInsertChild(root, root_child0, 0);

  const CSSNodeRef root_child0_child0 = CSSNodeNew();
  CSSNodeStyleSetFlexGrow(root_child0_child0, 1.2f);
  CSSNodeStyleSetFlexBasis(root_child0_child0, 0.3f);
  CSSNodeStyleSetPosition(root_child0_child0, CSSEdgeBottom, 13.3f);
  CSSNodeStyleSetHeight(root_child0_child0, 9.9f);
  CSSNodeInsertChild(root_child0, root_child0_child0, 0);

  const CSSNodeRef root_child0_child1 = CSSNodeNew();
  CSSNodeStyleSetFlexGrow(root_child0_child1, 4.2f);
  CSSNodeStyleSetFlexBasis(root_child0_child1, 0.3f);
  CSSNodeStyleSetPosition(root_child0_child1, CSSEdgeTop, 13.3f);
  CSSNodeStyleSetHeight(root_child0_child1, 1.1f);
  CSSNodeInsertChild(root_child0, root_child0_child1, 1);

  const CSSNodeRef root_child1 = CSSNodeNew();
  CSSNodeStyleSetFlexGrow(root_child1, 1.6f);
  CSSNodeStyleSetHeight(root_child1, 10);
  CSSNodeInsertChild(root, root_child1, 1);

  const CSSNodeRef root_child2 = CSSNodeNew();
  CSSNodeStyleSetFlexGrow(root_child2, 1.1f);
  CSSNodeStyleSetHeight(root_child2, 10.7f);
  CSSNodeInsertChild(root, root_child2, 2);
  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionLTR);

  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(87, CSSNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(113, CSSNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(87, CSSNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(59, CSSNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetLeft(root_child0_child0));
  ASSERT_FLOAT_EQ(-13, CSSNodeLayoutGetTop(root_child0_child0));
  ASSERT_FLOAT_EQ(87, CSSNodeLayoutGetWidth(root_child0_child0));
  ASSERT_FLOAT_EQ(13, CSSNodeLayoutGetHeight(root_child0_child0));

  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetLeft(root_child0_child1));
  ASSERT_FLOAT_EQ(27, CSSNodeLayoutGetTop(root_child0_child1));
  ASSERT_FLOAT_EQ(87, CSSNodeLayoutGetWidth(root_child0_child1));
  ASSERT_FLOAT_EQ(45, CSSNodeLayoutGetHeight(root_child0_child1));

  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(59, CSSNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(87, CSSNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(30, CSSNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(89, CSSNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(87, CSSNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(24, CSSNodeLayoutGetHeight(root_child2));

  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionRTL);

  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(87, CSSNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(113, CSSNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(87, CSSNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(59, CSSNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetLeft(root_child0_child0));
  ASSERT_FLOAT_EQ(-13, CSSNodeLayoutGetTop(root_child0_child0));
  ASSERT_FLOAT_EQ(87, CSSNodeLayoutGetWidth(root_child0_child0));
  ASSERT_FLOAT_EQ(13, CSSNodeLayoutGetHeight(root_child0_child0));

  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetLeft(root_child0_child1));
  ASSERT_FLOAT_EQ(27, CSSNodeLayoutGetTop(root_child0_child1));
  ASSERT_FLOAT_EQ(87, CSSNodeLayoutGetWidth(root_child0_child1));
  ASSERT_FLOAT_EQ(45, CSSNodeLayoutGetHeight(root_child0_child1));

  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(59, CSSNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(87, CSSNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(30, CSSNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(0, CSSNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(89, CSSNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(87, CSSNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(24, CSSNodeLayoutGetHeight(root_child2));

  CSSNodeFreeRecursive(root);
}


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


TEST_F(CSSLayoutFeatureRoundingTest, rounding_feature_with_custom_measure_func_floor) {
  const CSSNodeRef root = CSSNodeNew();

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeSetMeasureFunc(root_child0, _measureFloor);
  CSSNodeInsertChild(root, root_child0, 0);

  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionLTR);

  ASSERT_FLOAT_EQ(10, CSSNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(10, CSSNodeLayoutGetHeight(root_child0));

  CSSNodeFreeRecursive(root);
}

TEST_F(CSSLayoutFeatureRoundingTest, rounding_feature_with_custom_measure_func_ceil) {
  const CSSNodeRef root = CSSNodeNew();

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeSetMeasureFunc(root_child0, _measureCeil);
  CSSNodeInsertChild(root, root_child0, 0);

  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionLTR);

  ASSERT_FLOAT_EQ(11, CSSNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(11, CSSNodeLayoutGetHeight(root_child0));

  CSSNodeFreeRecursive(root);
}
