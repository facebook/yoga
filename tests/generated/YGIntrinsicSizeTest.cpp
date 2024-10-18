/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * clang-format off
 * @generated SignedSource<<112035ed7718c93e29fefe32eb90f7d5>>
 * generated by gentest/gentest-driver.ts from gentest/fixtures/YGIntrinsicSizeTest.html
 */

#include <gtest/gtest.h>
#include <yoga/Yoga.h>
#include "../util/TestUtil.h"

TEST(YogaTest, contains_inner_text_long_word) {
  YGConfigRef config = YGConfigNew();

  YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetAlignItems(root, YGAlignFlexStart);
  YGNodeStyleSetPositionType(root, YGPositionTypeAbsolute);
  YGNodeStyleSetWidth(root, 2000);
  YGNodeStyleSetHeight(root, 2000);

  YGNodeRef root_child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexDirection(root_child0, YGFlexDirectionRow);
  YGNodeInsertChild(root, root_child0, 0);
  YGNodeSetContext(root_child0, (void*)"LoremipsumdolorsitametconsecteturadipiscingelitSedeleifasdfettortoracauctorFuscerhoncusipsumtemporerosaliquamconsequatPraesentsoda");
  YGNodeSetMeasureFunc(root_child0, &facebook::yoga::test::IntrinsicSizeMeasure);
  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(2000, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(2000, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(1300, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(10, YGNodeLayoutGetHeight(root_child0));

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionRTL);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(2000, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(2000, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(700, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(1300, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(10, YGNodeLayoutGetHeight(root_child0));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}

TEST(YogaTest, contains_inner_text_no_width_no_height) {
  YGConfigRef config = YGConfigNew();

  YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetAlignItems(root, YGAlignFlexStart);
  YGNodeStyleSetPositionType(root, YGPositionTypeAbsolute);
  YGNodeStyleSetWidth(root, 2000);
  YGNodeStyleSetHeight(root, 2000);

  YGNodeRef root_child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexDirection(root_child0, YGFlexDirectionRow);
  YGNodeInsertChild(root, root_child0, 0);
  YGNodeSetContext(root_child0, (void*)"Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed eleifasd et tortor ac auctor. Integer at volutpat libero, sed elementum dui interdum id. Aliquam consectetur massa vel neque aliquet, quis consequat risus fringilla. Fusce rhoncus ipsum tempor eros aliquam, vel tempus metus ullamcorper. Nam at nulla sed tellus vestibulum fringilla vel sit amet ligula. Proin velit lectus, euismod sit amet quam vel ultricies dolor, vitae finibus lorem ipsum. Pellentesque molestie at mi sit amet dictum. Donec vehicula lacinia felis sit amet consectetur. Praesent sodales enim sapien, sed varius ipsum pellentesque vel. Aenean eu mi eu justo tincidunt finibus vel sit amet ipsum. Sed bibasdum purus vel ipsum sagittis, quis fermentum dolor lobortis. Etiam vulputate eleifasd lectus vel varius. Phasellus imperdiet lectus sit amet ipsum egestas, ut bibasdum ipsum malesuada. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Sed mollis eros sit amet elit porttitor, vel venenatis turpis venenatis. Nulla tempus tortor at eros efficitur, sit amet dapibus ipsum malesuada. Ut at mauris sed nunc malesuada convallis. Duis id sem vel magna varius eleifasd vel at est. Donec eget orci a ipsum tempor lobortis. Sed at consectetur ipsum.");
  YGNodeSetMeasureFunc(root_child0, &facebook::yoga::test::IntrinsicSizeMeasure);
  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(2000, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(2000, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(2000, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(70, YGNodeLayoutGetHeight(root_child0));

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionRTL);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(2000, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(2000, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(2000, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(70, YGNodeLayoutGetHeight(root_child0));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}

TEST(YogaTest, contains_inner_text_no_width_no_height_long_word_in_paragraph) {
  YGConfigRef config = YGConfigNew();

  YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetAlignItems(root, YGAlignFlexStart);
  YGNodeStyleSetPositionType(root, YGPositionTypeAbsolute);
  YGNodeStyleSetWidth(root, 2000);
  YGNodeStyleSetHeight(root, 2000);

  YGNodeRef root_child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexDirection(root_child0, YGFlexDirectionRow);
  YGNodeInsertChild(root, root_child0, 0);
  YGNodeSetContext(root_child0, (void*)"Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed eleifasd et tortor ac auctor. Integer at volutpat libero, sed elementum dui interdum id. Aliquam consectetur massa vel neque aliquet, quis consequat risus fringilla. Fusce rhoncus ipsum tempor eros aliquam, vel tempus metus ullamcorper. Nam at nulla sed tellus vestibulum fringilla vel sit amet ligula. Proin velit lectus, euismod sit amet quam vel ultricies dolor, vitae finibus loremipsumloremipsumloremipsumloremipsumloremipsumloremipsumloremipsumloremipsumloremipsumloremipsumloremipsumloremipsumloremipsumlorem Pellentesque molestie at mi sit amet dictum. Donec vehicula lacinia felis sit amet consectetur. Praesent sodales enim sapien, sed varius ipsum pellentesque vel. Aenean eu mi eu justo tincidunt finibus vel sit amet ipsum. Sed bibasdum purus vel ipsum sagittis, quis fermentum dolor lobortis. Etiam vulputate eleifasd lectus vel varius. Phasellus imperdiet lectus sit amet ipsum egestas, ut bibasdum ipsum malesuada. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Sed mollis eros sit amet elit porttitor, vel venenatis turpis venenatis. Nulla tempus tortor at eros efficitur, sit amet dapibus ipsum malesuada. Ut at mauris sed nunc malesuada convallis. Duis id sem vel magna varius eleifasd vel at est. Donec eget orci a ipsum tempor lobortis. Sed at consectetur ipsum.");
  YGNodeSetMeasureFunc(root_child0, &facebook::yoga::test::IntrinsicSizeMeasure);
  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(2000, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(2000, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(2000, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(70, YGNodeLayoutGetHeight(root_child0));

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionRTL);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(2000, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(2000, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(2000, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(70, YGNodeLayoutGetHeight(root_child0));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}

TEST(YogaTest, contains_inner_text_fixed_width) {
  YGConfigRef config = YGConfigNew();

  YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetAlignItems(root, YGAlignFlexStart);
  YGNodeStyleSetPositionType(root, YGPositionTypeAbsolute);
  YGNodeStyleSetWidth(root, 2000);
  YGNodeStyleSetHeight(root, 2000);

  YGNodeRef root_child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexDirection(root_child0, YGFlexDirectionRow);
  YGNodeStyleSetWidth(root_child0, 100);
  YGNodeInsertChild(root, root_child0, 0);
  YGNodeSetContext(root_child0, (void*)"Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed eleifasd et tortor ac auctor. Integer at volutpat libero, sed elementum dui interdum id. Aliquam consectetur massa vel neque aliquet, quis consequat risus fringilla. Fusce rhoncus ipsum tempor eros aliquam, vel tempus metus ullamcorper. Nam at nulla sed tellus vestibulum fringilla vel sit amet ligula. Proin velit lectus, euismod sit amet quam vel ultricies dolor, vitae finibus lorem ipsum. Pellentesque molestie at mi sit amet dictum. Donec vehicula lacinia felis sit amet consectetur. Praesent sodales enim sapien, sed varius ipsum pellentesque vel. Aenean eu mi eu justo tincidunt finibus vel sit amet ipsum. Sed bibasdum purus vel ipsum sagittis, quis fermentum dolor lobortis. Etiam vulputate eleifasd lectus vel varius. Phasellus imperdiet lectus sit amet ipsum egestas, ut bibasdum ipsum malesuada. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Sed mollis eros sit amet elit porttitor, vel venenatis turpis venenatis. Nulla tempus tortor at eros efficitur, sit amet dapibus ipsum malesuada. Ut at mauris sed nunc malesuada convallis. Duis id sem vel magna varius eleifasd vel at est. Donec eget orci a ipsum tempor lobortis. Sed at consectetur ipsum.");
  YGNodeSetMeasureFunc(root_child0, &facebook::yoga::test::IntrinsicSizeMeasure);
  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(2000, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(2000, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(1290, YGNodeLayoutGetHeight(root_child0));

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionRTL);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(2000, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(2000, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(1900, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(1290, YGNodeLayoutGetHeight(root_child0));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}

TEST(YogaTest, contains_inner_text_no_width_fixed_height) {
  YGConfigRef config = YGConfigNew();

  YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetAlignItems(root, YGAlignFlexStart);
  YGNodeStyleSetPositionType(root, YGPositionTypeAbsolute);
  YGNodeStyleSetWidth(root, 2000);
  YGNodeStyleSetHeight(root, 2000);

  YGNodeRef root_child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexDirection(root_child0, YGFlexDirectionRow);
  YGNodeStyleSetHeight(root_child0, 20);
  YGNodeInsertChild(root, root_child0, 0);
  YGNodeSetContext(root_child0, (void*)"Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed eleifasd et tortor ac auctor. Integer at volutpat libero, sed elementum dui interdum id. Aliquam consectetur massa vel neque aliquet, quis consequat risus fringilla. Fusce rhoncus ipsum tempor eros aliquam, vel tempus metus ullamcorper. Nam at nulla sed tellus vestibulum fringilla vel sit amet ligula. Proin velit lectus, euismod sit amet quam vel ultricies dolor, vitae finibus lorem ipsum. Pellentesque molestie at mi sit amet dictum. Donec vehicula lacinia felis sit amet consectetur. Praesent sodales enim sapien, sed varius ipsum pellentesque vel. Aenean eu mi eu justo tincidunt finibus vel sit amet ipsum. Sed bibasdum purus vel ipsum sagittis, quis fermentum dolor lobortis. Etiam vulputate eleifasd lectus vel varius. Phasellus imperdiet lectus sit amet ipsum egestas, ut bibasdum ipsum malesuada. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Sed mollis eros sit amet elit porttitor, vel venenatis turpis venenatis. Nulla tempus tortor at eros efficitur, sit amet dapibus ipsum malesuada. Ut at mauris sed nunc malesuada convallis. Duis id sem vel magna varius eleifasd vel at est. Donec eget orci a ipsum tempor lobortis. Sed at consectetur ipsum.");
  YGNodeSetMeasureFunc(root_child0, &facebook::yoga::test::IntrinsicSizeMeasure);
  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(2000, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(2000, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(2000, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(20, YGNodeLayoutGetHeight(root_child0));

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionRTL);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(2000, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(2000, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(2000, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(20, YGNodeLayoutGetHeight(root_child0));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}

TEST(YogaTest, contains_inner_text_fixed_width_fixed_height) {
  YGConfigRef config = YGConfigNew();

  YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetAlignItems(root, YGAlignFlexStart);
  YGNodeStyleSetPositionType(root, YGPositionTypeAbsolute);
  YGNodeStyleSetWidth(root, 2000);
  YGNodeStyleSetHeight(root, 2000);

  YGNodeRef root_child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexDirection(root_child0, YGFlexDirectionRow);
  YGNodeStyleSetWidth(root_child0, 50);
  YGNodeStyleSetHeight(root_child0, 20);
  YGNodeInsertChild(root, root_child0, 0);
  YGNodeSetContext(root_child0, (void*)"Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed eleifasd et tortor ac auctor. Integer at volutpat libero, sed elementum dui interdum id. Aliquam consectetur massa vel neque aliquet, quis consequat risus fringilla. Fusce rhoncus ipsum tempor eros aliquam, vel tempus metus ullamcorper. Nam at nulla sed tellus vestibulum fringilla vel sit amet ligula. Proin velit lectus, euismod sit amet quam vel ultricies dolor, vitae finibus lorem ipsum. Pellentesque molestie at mi sit amet dictum. Donec vehicula lacinia felis sit amet consectetur. Praesent sodales enim sapien, sed varius ipsum pellentesque vel. Aenean eu mi eu justo tincidunt finibus vel sit amet ipsum. Sed bibasdum purus vel ipsum sagittis, quis fermentum dolor lobortis. Etiam vulputate eleifasd lectus vel varius. Phasellus imperdiet lectus sit amet ipsum egestas, ut bibasdum ipsum malesuada. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Sed mollis eros sit amet elit porttitor, vel venenatis turpis venenatis. Nulla tempus tortor at eros efficitur, sit amet dapibus ipsum malesuada. Ut at mauris sed nunc malesuada convallis. Duis id sem vel magna varius eleifasd vel at est. Donec eget orci a ipsum tempor lobortis. Sed at consectetur ipsum.");
  YGNodeSetMeasureFunc(root_child0, &facebook::yoga::test::IntrinsicSizeMeasure);
  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(2000, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(2000, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(20, YGNodeLayoutGetHeight(root_child0));

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionRTL);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(2000, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(2000, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(1950, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(20, YGNodeLayoutGetHeight(root_child0));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}

TEST(YogaTest, contains_inner_text_max_width_max_height) {
  YGConfigRef config = YGConfigNew();

  YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetAlignItems(root, YGAlignFlexStart);
  YGNodeStyleSetPositionType(root, YGPositionTypeAbsolute);
  YGNodeStyleSetWidth(root, 2000);
  YGNodeStyleSetHeight(root, 2000);

  YGNodeRef root_child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexDirection(root_child0, YGFlexDirectionRow);
  YGNodeStyleSetMaxWidth(root_child0, 50);
  YGNodeStyleSetMaxHeight(root_child0, 20);
  YGNodeInsertChild(root, root_child0, 0);
  YGNodeSetContext(root_child0, (void*)"Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed eleifasd et tortor ac auctor. Integer at volutpat libero, sed elementum dui interdum id. Aliquam consectetur massa vel neque aliquet, quis consequat risus fringilla. Fusce rhoncus ipsum tempor eros aliquam, vel tempus metus ullamcorper. Nam at nulla sed tellus vestibulum fringilla vel sit amet ligula. Proin velit lectus, euismod sit amet quam vel ultricies dolor, vitae finibus lorem ipsum. Pellentesque molestie at mi sit amet dictum. Donec vehicula lacinia felis sit amet consectetur. Praesent sodales enim sapien, sed varius ipsum pellentesque vel. Aenean eu mi eu justo tincidunt finibus vel sit amet ipsum. Sed bibasdum purus vel ipsum sagittis, quis fermentum dolor lobortis. Etiam vulputate eleifasd lectus vel varius. Phasellus imperdiet lectus sit amet ipsum egestas, ut bibasdum ipsum malesuada. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Sed mollis eros sit amet elit porttitor, vel venenatis turpis venenatis. Nulla tempus tortor at eros efficitur, sit amet dapibus ipsum malesuada. Ut at mauris sed nunc malesuada convallis. Duis id sem vel magna varius eleifasd vel at est. Donec eget orci a ipsum tempor lobortis. Sed at consectetur ipsum.");
  YGNodeSetMeasureFunc(root_child0, &facebook::yoga::test::IntrinsicSizeMeasure);
  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(2000, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(2000, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(20, YGNodeLayoutGetHeight(root_child0));

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionRTL);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(2000, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(2000, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(1950, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(20, YGNodeLayoutGetHeight(root_child0));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}

TEST(YogaTest, contains_inner_text_max_width) {
  YGConfigRef config = YGConfigNew();

  YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetAlignItems(root, YGAlignFlexStart);
  YGNodeStyleSetPositionType(root, YGPositionTypeAbsolute);
  YGNodeStyleSetWidth(root, 2000);
  YGNodeStyleSetHeight(root, 2000);

  YGNodeRef root_child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexDirection(root_child0, YGFlexDirectionRow);
  YGNodeStyleSetMaxWidth(root_child0, 100);
  YGNodeInsertChild(root, root_child0, 0);
  YGNodeSetContext(root_child0, (void*)"Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed eleifasd et tortor ac auctor. Integer at volutpat libero, sed elementum dui interdum id. Aliquam consectetur massa vel neque aliquet, quis consequat risus fringilla. Fusce rhoncus ipsum tempor eros aliquam, vel tempus metus ullamcorper. Nam at nulla sed tellus vestibulum fringilla vel sit amet ligula. Proin velit lectus, euismod sit amet quam vel ultricies dolor, vitae finibus lorem ipsum. Pellentesque molestie at mi sit amet dictum. Donec vehicula lacinia felis sit amet consectetur. Praesent sodales enim sapien, sed varius ipsum pellentesque vel. Aenean eu mi eu justo tincidunt finibus vel sit amet ipsum. Sed bibasdum purus vel ipsum sagittis, quis fermentum dolor lobortis. Etiam vulputate eleifasd lectus vel varius. Phasellus imperdiet lectus sit amet ipsum egestas, ut bibasdum ipsum malesuada. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Sed mollis eros sit amet elit porttitor, vel venenatis turpis venenatis. Nulla tempus tortor at eros efficitur, sit amet dapibus ipsum malesuada. Ut at mauris sed nunc malesuada convallis. Duis id sem vel magna varius eleifasd vel at est. Donec eget orci a ipsum tempor lobortis. Sed at consectetur ipsum.");
  YGNodeSetMeasureFunc(root_child0, &facebook::yoga::test::IntrinsicSizeMeasure);
  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(2000, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(2000, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(1290, YGNodeLayoutGetHeight(root_child0));

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionRTL);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(2000, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(2000, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(1900, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(1290, YGNodeLayoutGetHeight(root_child0));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}

TEST(YogaTest, contains_inner_text_fixed_width_shorter_text) {
  YGConfigRef config = YGConfigNew();

  YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetAlignItems(root, YGAlignFlexStart);
  YGNodeStyleSetPositionType(root, YGPositionTypeAbsolute);
  YGNodeStyleSetWidth(root, 2000);
  YGNodeStyleSetHeight(root, 2000);

  YGNodeRef root_child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexDirection(root_child0, YGFlexDirectionRow);
  YGNodeStyleSetWidth(root_child0, 100);
  YGNodeInsertChild(root, root_child0, 0);
  YGNodeSetContext(root_child0, (void*)"Lorem ipsum");
  YGNodeSetMeasureFunc(root_child0, &facebook::yoga::test::IntrinsicSizeMeasure);
  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(2000, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(2000, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(20, YGNodeLayoutGetHeight(root_child0));

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionRTL);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(2000, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(2000, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(1900, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(20, YGNodeLayoutGetHeight(root_child0));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}

TEST(YogaTest, contains_inner_text_fixed_height_shorter_text) {
  YGConfigRef config = YGConfigNew();

  YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetAlignItems(root, YGAlignFlexStart);
  YGNodeStyleSetPositionType(root, YGPositionTypeAbsolute);
  YGNodeStyleSetWidth(root, 2000);
  YGNodeStyleSetHeight(root, 2000);

  YGNodeRef root_child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexDirection(root_child0, YGFlexDirectionRow);
  YGNodeStyleSetHeight(root_child0, 100);
  YGNodeInsertChild(root, root_child0, 0);
  YGNodeSetContext(root_child0, (void*)"Lorem ipsum");
  YGNodeSetMeasureFunc(root_child0, &facebook::yoga::test::IntrinsicSizeMeasure);
  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(2000, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(2000, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(110, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetHeight(root_child0));

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionRTL);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(2000, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(2000, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(1890, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(110, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetHeight(root_child0));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}

TEST(YogaTest, contains_inner_text_max_height) {
  YGConfigRef config = YGConfigNew();

  YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetAlignItems(root, YGAlignFlexStart);
  YGNodeStyleSetPositionType(root, YGPositionTypeAbsolute);
  YGNodeStyleSetWidth(root, 2000);
  YGNodeStyleSetHeight(root, 2000);

  YGNodeRef root_child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexDirection(root_child0, YGFlexDirectionRow);
  YGNodeStyleSetMaxHeight(root_child0, 20);
  YGNodeInsertChild(root, root_child0, 0);
  YGNodeSetContext(root_child0, (void*)"Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed eleifasd et tortor ac auctor. Integer at volutpat libero, sed elementum dui interdum id. Aliquam consectetur massa vel neque aliquet, quis consequat risus fringilla. Fusce rhoncus ipsum tempor eros aliquam, vel tempus metus ullamcorper. Nam at nulla sed tellus vestibulum fringilla vel sit amet ligula. Proin velit lectus, euismod sit amet quam vel ultricies dolor, vitae finibus lorem ipsum. Pellentesque molestie at mi sit amet dictum. Donec vehicula lacinia felis sit amet consectetur. Praesent sodales enim sapien, sed varius ipsum pellentesque vel. Aenean eu mi eu justo tincidunt finibus vel sit amet ipsum. Sed bibasdum purus vel ipsum sagittis, quis fermentum dolor lobortis. Etiam vulputate eleifasd lectus vel varius. Phasellus imperdiet lectus sit amet ipsum egestas, ut bibasdum ipsum malesuada. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Sed mollis eros sit amet elit porttitor, vel venenatis turpis venenatis. Nulla tempus tortor at eros efficitur, sit amet dapibus ipsum malesuada. Ut at mauris sed nunc malesuada convallis. Duis id sem vel magna varius eleifasd vel at est. Donec eget orci a ipsum tempor lobortis. Sed at consectetur ipsum.");
  YGNodeSetMeasureFunc(root_child0, &facebook::yoga::test::IntrinsicSizeMeasure);
  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(2000, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(2000, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(2000, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(20, YGNodeLayoutGetHeight(root_child0));

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionRTL);

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root));
  ASSERT_FLOAT_EQ(2000, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(2000, YGNodeLayoutGetHeight(root));

  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetLeft(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetTop(root_child0));
  ASSERT_FLOAT_EQ(2000, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(20, YGNodeLayoutGetHeight(root_child0));

  YGNodeFreeRecursive(root);

  YGConfigFree(config);
}