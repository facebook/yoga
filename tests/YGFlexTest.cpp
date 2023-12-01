
#include <gtest/gtest.h>
#include <yoga/Yoga.h>

TEST(YogaTest, flex_min_height_children_wrap) {
  const YGConfigRef config = YGConfigNew();
  const YGNodeRef root = YGNodeNewWithConfig(config);

  YGNodeStyleSetFlexDirection(root, YGFlexDirectionRow);
  YGNodeStyleSetFlexWrap(root, YGWrapWrap);

  YGNodeStyleSetWidth(root, 200);
  YGNodeStyleSetHeightAuto(root);
  YGNodeStyleSetMinHeight(root, 200);
  YGNodeStyleSetFlexBasisAuto(root);

  YGNodeStyleSetJustifyContent(root, YGJustifyFlexStart);
  YGNodeStyleSetAlignItems(root, YGAlignFlexStart);
  YGNodeStyleSetAlignContent(root, YGAlignFlexStart);

  for (size_t i = 0; i < 2; i++) {
    YGNodeRef node = YGNodeNewWithConfig(config);
    YGNodeStyleSetWidth(node, 120);
    YGNodeStyleSetHeight(node, 120);

    YGNodeInsertChild(root, node, i); // index start from 0
  }

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);
  ASSERT_FLOAT_EQ(200, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(240, YGNodeLayoutGetHeight(root));
}

TEST(YogaTest, flex_min_width_children_wrap) {
  const YGConfigRef config = YGConfigNew();
  const YGNodeRef root = YGNodeNewWithConfig(config);

  YGNodeStyleSetFlexDirection(root, YGFlexDirectionColumn);
  YGNodeStyleSetFlexWrap(root, YGWrapWrap);

  YGNodeStyleSetMinWidth(root, 200);
  YGNodeStyleSetHeightAuto(root);
  YGNodeStyleSetHeight(root, 200);
  YGNodeStyleSetFlexBasisAuto(root);

  YGNodeStyleSetJustifyContent(root, YGJustifyFlexStart);
  YGNodeStyleSetAlignItems(root, YGAlignFlexStart);
  YGNodeStyleSetAlignContent(root, YGAlignFlexStart);

  for (size_t i = 0; i < 2; i++) {
    YGNodeRef node = YGNodeNewWithConfig(config);
    YGNodeStyleSetWidth(node, 120);
    YGNodeStyleSetHeight(node, 120);

    YGNodeInsertChild(root, node, i); // index start from 0
  }

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);
  ASSERT_FLOAT_EQ(200, YGNodeLayoutGetHeight(root));
  ASSERT_FLOAT_EQ(240, YGNodeLayoutGetWidth(root));
}