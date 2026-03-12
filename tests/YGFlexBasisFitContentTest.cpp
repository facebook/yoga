/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>
#include <yoga/Yoga.h>
#include <algorithm>

static YGSize measureTextLike(
    YGNodeConstRef /*node*/,
    float width,
    YGMeasureMode widthMode,
    float /*height*/,
    YGMeasureMode /*heightMode*/) {
  float measuredWidth = 200.0f;
  if (widthMode == YGMeasureModeAtMost) {
    measuredWidth = std::min(measuredWidth, width);
  }
  return YGSize{.width = measuredWidth, .height = 20.0f};
}

class YGFlexBasisFitContentTest : public testing::TestWithParam<bool> {
 protected:
  void SetUp() override {
    config_ = YGConfigNew();
    YGConfigSetExperimentalFeatureEnabled(
        config_, YGExperimentalFeatureFixFlexBasisFitContent, GetParam());
  }

  void TearDown() override {
    if (root_ != nullptr) {
      YGNodeFreeRecursive(root_);
    }
    YGConfigFree(config_);
  }

  YGConfigRef config_ = nullptr;
  YGNodeRef root_ = nullptr;
};

// Auto-height container with a percentage-height child produces the same
// layout regardless of feature state, because Check 3 preserves percentage
// resolution when availableInnerHeight is NaN.
TEST_P(YGFlexBasisFitContentTest, percentage_height_converges) {
  root_ = YGNodeNewWithConfig(config_);
  YGNodeStyleSetHeight(root_, 300);
  YGNodeStyleSetWidth(root_, 100);

  YGNodeRef container = YGNodeNewWithConfig(config_);
  YGNodeInsertChild(root_, container, 0);

  YGNodeRef child = YGNodeNewWithConfig(config_);
  YGNodeStyleSetHeightPercent(child, 50);
  YGNodeInsertChild(container, child, 0);

  YGNodeCalculateLayout(root_, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(75, YGNodeLayoutGetHeight(child));
  ASSERT_FLOAT_EQ(150, YGNodeLayoutGetHeight(container));
}

// Two auto-height containers with percentage children and flexGrow:1 produce
// the same layout regardless of feature state.
TEST_P(YGFlexBasisFitContentTest, percentage_with_flex_grow_converges) {
  root_ = YGNodeNewWithConfig(config_);
  YGNodeStyleSetHeight(root_, 400);
  YGNodeStyleSetWidth(root_, 100);

  YGNodeRef containerA = YGNodeNewWithConfig(config_);
  YGNodeStyleSetFlexGrow(containerA, 1);
  YGNodeInsertChild(root_, containerA, 0);

  YGNodeRef childA = YGNodeNewWithConfig(config_);
  YGNodeStyleSetHeightPercent(childA, 25);
  YGNodeInsertChild(containerA, childA, 0);

  YGNodeRef containerB = YGNodeNewWithConfig(config_);
  YGNodeStyleSetFlexGrow(containerB, 1);
  YGNodeInsertChild(root_, containerB, 1);

  YGNodeRef childB = YGNodeNewWithConfig(config_);
  YGNodeStyleSetHeightPercent(childB, 50);
  YGNodeInsertChild(containerB, childB, 0);

  YGNodeCalculateLayout(root_, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(150, YGNodeLayoutGetHeight(containerA));
  ASSERT_FLOAT_EQ(250, YGNodeLayoutGetHeight(containerB));
}

// Auto-height container with flexShrink and a percentage child causing
// overflow produces the same layout regardless of feature state.
TEST_P(YGFlexBasisFitContentTest, flex_shrink_overflow_converges) {
  root_ = YGNodeNewWithConfig(config_);
  YGNodeStyleSetHeight(root_, 200);
  YGNodeStyleSetWidth(root_, 100);

  YGNodeRef container = YGNodeNewWithConfig(config_);
  YGNodeStyleSetFlexShrink(container, 1);
  YGNodeInsertChild(root_, container, 0);

  YGNodeRef child = YGNodeNewWithConfig(config_);
  YGNodeStyleSetHeightPercent(child, 100);
  YGNodeInsertChild(container, child, 0);

  YGNodeRef fixed = YGNodeNewWithConfig(config_);
  YGNodeStyleSetHeight(fixed, 150);
  YGNodeInsertChild(root_, fixed, 1);

  YGNodeCalculateLayout(root_, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetHeight(container));
  ASSERT_FLOAT_EQ(150, YGNodeLayoutGetHeight(fixed));
}

// In a scroll container (column), changing a sibling's height does not cause
// re-measurement of unaffected subtrees when the feature is enabled.
TEST_P(YGFlexBasisFitContentTest, scroll_avoids_remeasure) {
  static uint32_t measureCount = 0;
  auto measureFunc = [](YGNodeConstRef /*node*/,
                        float /*width*/,
                        YGMeasureMode /*widthMode*/,
                        float /*height*/,
                        YGMeasureMode /*heightMode*/) {
    measureCount++;
    return YGSize{.width = 50.0f, .height = 50.0f};
  };

  measureCount = 0;

  root_ = YGNodeNewWithConfig(config_);
  YGNodeStyleSetOverflow(root_, YGOverflowScroll);
  YGNodeStyleSetWidth(root_, 100);
  YGNodeStyleSetHeight(root_, 500);

  YGNodeRef sibling = YGNodeNewWithConfig(config_);
  YGNodeStyleSetHeight(sibling, 100);
  YGNodeInsertChild(root_, sibling, 0);

  YGNodeRef wrapper = YGNodeNewWithConfig(config_);
  YGNodeInsertChild(root_, wrapper, 1);

  YGNodeRef inner = YGNodeNewWithConfig(config_);
  YGNodeInsertChild(wrapper, inner, 0);

  YGNodeRef leaf = YGNodeNewWithConfig(config_);
  YGNodeSetMeasureFunc(leaf, measureFunc);
  YGNodeInsertChild(inner, leaf, 0);

  YGNodeCalculateLayout(root_, YGUndefined, YGUndefined, YGDirectionLTR);
  uint32_t firstPassCount = measureCount;

  YGNodeStyleSetHeight(sibling, 200);
  YGNodeCalculateLayout(root_, YGUndefined, YGUndefined, YGDirectionLTR);
  uint32_t secondPassCount = measureCount - firstPassCount;

  ASSERT_FLOAT_EQ(50, YGNodeLayoutGetHeight(leaf));

  EXPECT_EQ(0, secondPassCount);
}

// Row direction is unaffected by the optimization. Width FitContent is always
// preserved to support text wrapping through container nodes.
TEST_P(YGFlexBasisFitContentTest, row_direction_unchanged) {
  root_ = YGNodeNewWithConfig(config_);
  YGNodeStyleSetWidth(root_, 100);
  YGNodeStyleSetHeight(root_, 100);

  YGNodeRef container = YGNodeNewWithConfig(config_);
  YGNodeInsertChild(root_, container, 0);

  YGNodeRef text = YGNodeNewWithConfig(config_);
  YGNodeSetMeasureFunc(text, measureTextLike);
  YGNodeInsertChild(container, text, 0);

  YGNodeCalculateLayout(root_, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(100, YGNodeLayoutGetWidth(text));
}

// Scroll container in row direction: width FitContent is skipped for the
// main axis (row) in scroll containers, matching legacy behavior.
TEST_P(YGFlexBasisFitContentTest, row_scroll_skips_width) {
  root_ = YGNodeNewWithConfig(config_);
  YGNodeStyleSetFlexDirection(root_, YGFlexDirectionRow);
  YGNodeStyleSetOverflow(root_, YGOverflowScroll);
  YGNodeStyleSetWidth(root_, 100);
  YGNodeStyleSetHeight(root_, 100);

  YGNodeRef text = YGNodeNewWithConfig(config_);
  YGNodeSetMeasureFunc(text, measureTextLike);
  YGNodeInsertChild(root_, text, 0);

  YGNodeCalculateLayout(root_, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(200, YGNodeLayoutGetWidth(text));
}

INSTANTIATE_TEST_SUITE_P(
    YogaTest,
    YGFlexBasisFitContentTest,
    testing::Values(false, true));

// Feature toggle invalidates layout cache.
TEST(YogaTest, flex_basis_fit_content_feature_change_invalidates_cache) {
  YGConfigRef config = YGConfigNew();
  YGConfigSetExperimentalFeatureEnabled(
      config, YGExperimentalFeatureFixFlexBasisFitContent, false);

  YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetHeight(root, 300);
  YGNodeStyleSetWidth(root, 100);

  YGNodeRef container = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexGrow(container, 1);
  YGNodeInsertChild(root, container, 0);

  YGNodeRef child = YGNodeNewWithConfig(config);
  YGNodeStyleSetHeightPercent(child, 50);
  YGNodeInsertChild(container, child, 0);

  YGNodeRef fixed = YGNodeNewWithConfig(config);
  YGNodeStyleSetHeight(fixed, 100);
  YGNodeInsertChild(root, fixed, 1);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);
  float heightBefore = YGNodeLayoutGetHeight(container);

  YGConfigSetExperimentalFeatureEnabled(
      config, YGExperimentalFeatureFixFlexBasisFitContent, true);
  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);
  float heightAfter = YGNodeLayoutGetHeight(container);

  ASSERT_FLOAT_EQ(heightBefore, heightAfter);

  YGNodeFreeRecursive(root);
  YGConfigFree(config);
}
