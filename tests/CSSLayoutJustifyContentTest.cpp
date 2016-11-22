/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

/**
 * @Generated by gentest/gentest.sh with the following input
 *
<div id="justify_content_row_flex_start" style="width: 102px; height: 102px; flex-direction: row; justify-content: flex-start;">
  <div style="width: 10px;"></div>
  <div style="width: 10px;"></div>
  <div style="width: 10px;"></div>
</div>

<div id="justify_content_row_flex_end" style="width: 102px; height: 102px; flex-direction: row; justify-content: flex-end;">
  <div style="width: 10px;"></div>
  <div style="width: 10px;"></div>
  <div style="width: 10px;"></div>
</div>

<div id="justify_content_row_center" style="width: 102px; height: 102px; flex-direction: row; justify-content: center;">
  <div style="width: 10px;"></div>
  <div style="width: 10px;"></div>
  <div style="width: 10px;"></div>
</div>

<div id="justify_content_row_space_between" style="width: 102px; height: 102px; flex-direction: row; justify-content: space-between;">
  <div style="width: 10px;"></div>
  <div style="width: 10px;"></div>
  <div style="width: 10px;"></div>
</div>

<div id="justify_content_row_space_around" style="width: 102px; height: 102px; flex-direction: row; justify-content: space-around;">
  <div style="width: 10px;"></div>
  <div style="width: 10px;"></div>
  <div style="width: 10px;"></div>
</div>

<div id="justify_content_column_flex_start" style="width: 102px; height: 102px; justify-content: flex-start;">
  <div style="height: 10px;"></div>
  <div style="heigth: 10px;"></div>
  <div style="height: 10px;"></div>
</div>

<div id="justify_content_column_flex_end" style="width: 102px; height: 102px; justify-content: flex-end;">
  <div style="height: 10px;"></div>
  <div style="height: 10px;"></div>
  <div style="height: 10px;"></div>
</div>

<div id="justify_content_column_center" style="width: 102px; height: 102px; justify-content: center;">
  <div style="height: 10px;"></div>
  <div style="height: 10px;"></div>
  <div style="height: 10px;"></div>
</div>

<div id="justify_content_column_space_between" style="width: 102px; height: 102px; justify-content: space-between;">
  <div style="height: 10px;"></div>
  <div style="height: 10px;"></div>
  <div style="height: 10px;"></div>
</div>

<div id="justify_content_column_space_around" style="width: 102px; height: 102px; justify-content: space-around;">
  <div style="height: 10px;"></div>
  <div style="height: 10px;"></div>
  <div style="height: 10px;"></div>
</div>
 *
 */

#include <CSSLayout/CSSLayout.h>
#include <gtest/gtest.h>

TEST(CSSLayoutTest, justify_content_row_flex_start) {
  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetFlexDirection(root, CSSFlexDirectionRow);
  CSSNodeStyleSetWidth(root, 102f);
  CSSNodeStyleSetHeight(root, 102f);

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeStyleSetWidth(root_child0, 10f);
  CSSNodeInsertChild(root, root_child0, 0);

  const CSSNodeRef root_child1 = CSSNodeNew();
  CSSNodeStyleSetWidth(root_child1, 10f);
  CSSNodeInsertChild(root, root_child1, 1);

  const CSSNodeRef root_child2 = CSSNodeNew();
  CSSNodeStyleSetWidth(root_child2, 10f);
  CSSNodeInsertChild(root, root_child2, 2);
  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionLTR);

  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(10f, CSSNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(10f, CSSNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(10f, CSSNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(20f, CSSNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(10f, CSSNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetHeight(root_child2));

  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionRTL);

  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(92f, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(10f, CSSNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(82f, CSSNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(10f, CSSNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(72f, CSSNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(10f, CSSNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetHeight(root_child2));

  CSSNodeFreeRecursive(root);
}

TEST(CSSLayoutTest, justify_content_row_flex_end) {
  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetFlexDirection(root, CSSFlexDirectionRow);
  CSSNodeStyleSetJustifyContent(root, CSSJustifyFlexEnd);
  CSSNodeStyleSetWidth(root, 102f);
  CSSNodeStyleSetHeight(root, 102f);

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeStyleSetWidth(root_child0, 10f);
  CSSNodeInsertChild(root, root_child0, 0);

  const CSSNodeRef root_child1 = CSSNodeNew();
  CSSNodeStyleSetWidth(root_child1, 10f);
  CSSNodeInsertChild(root, root_child1, 1);

  const CSSNodeRef root_child2 = CSSNodeNew();
  CSSNodeStyleSetWidth(root_child2, 10f);
  CSSNodeInsertChild(root, root_child2, 2);
  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionLTR);

  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(72f, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(10f, CSSNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(82f, CSSNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(10f, CSSNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(92f, CSSNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(10f, CSSNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetHeight(root_child2));

  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionRTL);

  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(20f, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(10f, CSSNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(10f, CSSNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(10f, CSSNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(10f, CSSNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetHeight(root_child2));

  CSSNodeFreeRecursive(root);
}

TEST(CSSLayoutTest, justify_content_row_center) {
  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetFlexDirection(root, CSSFlexDirectionRow);
  CSSNodeStyleSetJustifyContent(root, CSSJustifyCenter);
  CSSNodeStyleSetWidth(root, 102f);
  CSSNodeStyleSetHeight(root, 102f);

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeStyleSetWidth(root_child0, 10f);
  CSSNodeInsertChild(root, root_child0, 0);

  const CSSNodeRef root_child1 = CSSNodeNew();
  CSSNodeStyleSetWidth(root_child1, 10f);
  CSSNodeInsertChild(root, root_child1, 1);

  const CSSNodeRef root_child2 = CSSNodeNew();
  CSSNodeStyleSetWidth(root_child2, 10f);
  CSSNodeInsertChild(root, root_child2, 2);
  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionLTR);

  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(36f, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(10f, CSSNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(46f, CSSNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(10f, CSSNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(56f, CSSNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(10f, CSSNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetHeight(root_child2));

  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionRTL);

  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(56f, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(10f, CSSNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(46f, CSSNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(10f, CSSNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(36f, CSSNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(10f, CSSNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetHeight(root_child2));

  CSSNodeFreeRecursive(root);
}

TEST(CSSLayoutTest, justify_content_row_space_between) {
  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetFlexDirection(root, CSSFlexDirectionRow);
  CSSNodeStyleSetJustifyContent(root, CSSJustifySpaceBetween);
  CSSNodeStyleSetWidth(root, 102f);
  CSSNodeStyleSetHeight(root, 102f);

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeStyleSetWidth(root_child0, 10f);
  CSSNodeInsertChild(root, root_child0, 0);

  const CSSNodeRef root_child1 = CSSNodeNew();
  CSSNodeStyleSetWidth(root_child1, 10f);
  CSSNodeInsertChild(root, root_child1, 1);

  const CSSNodeRef root_child2 = CSSNodeNew();
  CSSNodeStyleSetWidth(root_child2, 10f);
  CSSNodeInsertChild(root, root_child2, 2);
  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionLTR);

  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(10f, CSSNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(46f, CSSNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(10f, CSSNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(92f, CSSNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(10f, CSSNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetHeight(root_child2));

  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionRTL);

  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(92f, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(10f, CSSNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(46f, CSSNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(10f, CSSNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(10f, CSSNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetHeight(root_child2));

  CSSNodeFreeRecursive(root);
}

TEST(CSSLayoutTest, justify_content_row_space_around) {
  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetFlexDirection(root, CSSFlexDirectionRow);
  CSSNodeStyleSetJustifyContent(root, CSSJustifySpaceAround);
  CSSNodeStyleSetWidth(root, 102f);
  CSSNodeStyleSetHeight(root, 102f);

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeStyleSetWidth(root_child0, 10f);
  CSSNodeInsertChild(root, root_child0, 0);

  const CSSNodeRef root_child1 = CSSNodeNew();
  CSSNodeStyleSetWidth(root_child1, 10f);
  CSSNodeInsertChild(root, root_child1, 1);

  const CSSNodeRef root_child2 = CSSNodeNew();
  CSSNodeStyleSetWidth(root_child2, 10f);
  CSSNodeInsertChild(root, root_child2, 2);
  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionLTR);

  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(12f, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(10f, CSSNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(46f, CSSNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(10f, CSSNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(80f, CSSNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(10f, CSSNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetHeight(root_child2));

  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionRTL);

  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(80f, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(10f, CSSNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(46f, CSSNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(10f, CSSNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(12f, CSSNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(10f, CSSNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetHeight(root_child2));

  CSSNodeFreeRecursive(root);
}

TEST(CSSLayoutTest, justify_content_column_flex_start) {
  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetWidth(root, 102f);
  CSSNodeStyleSetHeight(root, 102f);

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeStyleSetHeight(root_child0, 10f);
  CSSNodeInsertChild(root, root_child0, 0);

  const CSSNodeRef root_child1 = CSSNodeNew();
  CSSNodeInsertChild(root, root_child1, 1);

  const CSSNodeRef root_child2 = CSSNodeNew();
  CSSNodeStyleSetHeight(root_child2, 10f);
  CSSNodeInsertChild(root, root_child2, 2);
  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionLTR);

  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(10f, CSSNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(10f, CSSNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(10f, CSSNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(10f, CSSNodeLayoutGetHeight(root_child2));

  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionRTL);

  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(10f, CSSNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(10f, CSSNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(10f, CSSNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(10f, CSSNodeLayoutGetHeight(root_child2));

  CSSNodeFreeRecursive(root);
}

TEST(CSSLayoutTest, justify_content_column_flex_end) {
  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetJustifyContent(root, CSSJustifyFlexEnd);
  CSSNodeStyleSetWidth(root, 102f);
  CSSNodeStyleSetHeight(root, 102f);

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeStyleSetHeight(root_child0, 10f);
  CSSNodeInsertChild(root, root_child0, 0);

  const CSSNodeRef root_child1 = CSSNodeNew();
  CSSNodeStyleSetHeight(root_child1, 10f);
  CSSNodeInsertChild(root, root_child1, 1);

  const CSSNodeRef root_child2 = CSSNodeNew();
  CSSNodeStyleSetHeight(root_child2, 10f);
  CSSNodeInsertChild(root, root_child2, 2);
  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionLTR);

  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(72f, CSSNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(10f, CSSNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(82f, CSSNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(10f, CSSNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(92f, CSSNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(10f, CSSNodeLayoutGetHeight(root_child2));

  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionRTL);

  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(72f, CSSNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(10f, CSSNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(82f, CSSNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(10f, CSSNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(92f, CSSNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(10f, CSSNodeLayoutGetHeight(root_child2));

  CSSNodeFreeRecursive(root);
}

TEST(CSSLayoutTest, justify_content_column_center) {
  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetJustifyContent(root, CSSJustifyCenter);
  CSSNodeStyleSetWidth(root, 102f);
  CSSNodeStyleSetHeight(root, 102f);

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeStyleSetHeight(root_child0, 10f);
  CSSNodeInsertChild(root, root_child0, 0);

  const CSSNodeRef root_child1 = CSSNodeNew();
  CSSNodeStyleSetHeight(root_child1, 10f);
  CSSNodeInsertChild(root, root_child1, 1);

  const CSSNodeRef root_child2 = CSSNodeNew();
  CSSNodeStyleSetHeight(root_child2, 10f);
  CSSNodeInsertChild(root, root_child2, 2);
  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionLTR);

  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(36f, CSSNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(10f, CSSNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(46f, CSSNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(10f, CSSNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(56f, CSSNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(10f, CSSNodeLayoutGetHeight(root_child2));

  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionRTL);

  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(36f, CSSNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(10f, CSSNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(46f, CSSNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(10f, CSSNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(56f, CSSNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(10f, CSSNodeLayoutGetHeight(root_child2));

  CSSNodeFreeRecursive(root);
}

TEST(CSSLayoutTest, justify_content_column_space_between) {
  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetJustifyContent(root, CSSJustifySpaceBetween);
  CSSNodeStyleSetWidth(root, 102f);
  CSSNodeStyleSetHeight(root, 102f);

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeStyleSetHeight(root_child0, 10f);
  CSSNodeInsertChild(root, root_child0, 0);

  const CSSNodeRef root_child1 = CSSNodeNew();
  CSSNodeStyleSetHeight(root_child1, 10f);
  CSSNodeInsertChild(root, root_child1, 1);

  const CSSNodeRef root_child2 = CSSNodeNew();
  CSSNodeStyleSetHeight(root_child2, 10f);
  CSSNodeInsertChild(root, root_child2, 2);
  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionLTR);

  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(10f, CSSNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(46f, CSSNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(10f, CSSNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(92f, CSSNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(10f, CSSNodeLayoutGetHeight(root_child2));

  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionRTL);

  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(10f, CSSNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(46f, CSSNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(10f, CSSNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(92f, CSSNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(10f, CSSNodeLayoutGetHeight(root_child2));

  CSSNodeFreeRecursive(root);
}

TEST(CSSLayoutTest, justify_content_column_space_around) {
  const CSSNodeRef root = CSSNodeNew();
  CSSNodeStyleSetJustifyContent(root, CSSJustifySpaceAround);
  CSSNodeStyleSetWidth(root, 102f);
  CSSNodeStyleSetHeight(root, 102f);

  const CSSNodeRef root_child0 = CSSNodeNew();
  CSSNodeStyleSetHeight(root_child0, 10f);
  CSSNodeInsertChild(root, root_child0, 0);

  const CSSNodeRef root_child1 = CSSNodeNew();
  CSSNodeStyleSetHeight(root_child1, 10f);
  CSSNodeInsertChild(root, root_child1, 1);

  const CSSNodeRef root_child2 = CSSNodeNew();
  CSSNodeStyleSetHeight(root_child2, 10f);
  CSSNodeInsertChild(root, root_child2, 2);
  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionLTR);

  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(12f, CSSNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(10f, CSSNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(46f, CSSNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(10f, CSSNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(80f, CSSNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(10f, CSSNodeLayoutGetHeight(root_child2));

  CSSNodeCalculateLayout(root, CSSUndefined, CSSUndefined, CSSDirectionRTL);

  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(12f, CSSNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(10f, CSSNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetLeft(root_child1));
  ASSERT_FLOAT_EQ(46f, CSSNodeLayoutGetTop(root_child1));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetWidth(root_child1));
  ASSERT_FLOAT_EQ(10f, CSSNodeLayoutGetHeight(root_child1));

  ASSERT_FLOAT_EQ(0f, CSSNodeLayoutGetLeft(root_child2));
  ASSERT_FLOAT_EQ(80f, CSSNodeLayoutGetTop(root_child2));
  ASSERT_FLOAT_EQ(102f, CSSNodeLayoutGetWidth(root_child2));
  ASSERT_FLOAT_EQ(10f, CSSNodeLayoutGetHeight(root_child2));

  CSSNodeFreeRecursive(root);
}
