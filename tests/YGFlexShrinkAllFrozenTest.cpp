/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

// Regression tests for flex shrink after the first pass freezes items:
// https://github.com/react/yoga/issues/2038, #1651 and #931.

#include <gtest/gtest.h>
#include <yoga/Yoga.h>

namespace {

const bool kWithoutErrata[] = {false, true};

YGConfigRef newConfig(bool withoutErrata) {
  YGConfigRef config = YGConfigNew();
  if (withoutErrata) {
    YGConfigSetErrata(config, YGErrataNone);
  }
  return config;
}

// root (350 x 350) > row > [box, sibling (600 x 23)]. The box is the only
// shrinkable item, and its basis comes from its aspectRatio and the stretched
// height: 23 * 22/24 = 21.083334.
YGNodeRef newAspectRatioRow(
    YGConfigRef config,
    float shrink,
    YGNodeRef* box,
    YGNodeRef* sibling) {
  YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetWidth(root, 350.0f);
  YGNodeStyleSetHeight(root, 350.0f);

  YGNodeRef row = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexDirection(row, YGFlexDirectionRow);
  YGNodeInsertChild(root, row, 0);

  *box = YGNodeNewWithConfig(config);
  YGNodeStyleSetAspectRatio(*box, 22.0f / 24.0f);
  YGNodeStyleSetFlexShrink(*box, shrink);
  YGNodeInsertChild(row, *box, 0);

  *sibling = YGNodeNewWithConfig(config);
  YGNodeStyleSetWidth(*sibling, 600.0f);
  YGNodeStyleSetHeight(*sibling, 23.0f);
  YGNodeInsertChild(row, *sibling, 1);

  return root;
}

} // namespace

// https://github.com/react/yoga/issues/2038
// All items freeze at their minWidth. Removing them from the float total left a
// residual instead of 0.
TEST(YGFlexShrinkAllFrozen, all_items_frozen_at_min_width) {
  for (bool withoutErrata : kWithoutErrata) {
    YGConfigRef config = newConfig(withoutErrata);
    YGNodeRef root = YGNodeNewWithConfig(config);
    YGNodeStyleSetFlexDirection(root, YGFlexDirectionRow);
    YGNodeStyleSetWidth(root, 350.0f);
    YGNodeStyleSetHeight(root, 50.0f);

    const float widths[] = {100.1f, 200.3f, 300.7f};
    const float minWidths[] = {90.0f, 190.0f, 290.0f};
    for (size_t i = 0; i < 3; i++) {
      YGNodeRef child = YGNodeNewWithConfig(config);
      YGNodeStyleSetWidth(child, widths[i]);
      YGNodeStyleSetMinWidth(child, minWidths[i]);
      YGNodeStyleSetFlexShrink(child, 1.0f);
      YGNodeInsertChild(root, child, i);
    }

    YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

    for (size_t i = 0; i < 3; i++) {
      EXPECT_EQ(minWidths[i], YGNodeLayoutGetWidth(YGNodeGetChild(root, i)))
          << "withoutErrata " << withoutErrata << ", child[" << i << "]";
    }

    YGNodeFreeRecursive(root);
    YGConfigFree(config);
  }
}

// https://github.com/react/yoga/issues/931
// An item with flexShrink 0.25 freezes at minHeight 25, but basis * (1 -
// flexShrink) left it at 113.
TEST(YGFlexShrinkAllFrozen, issue_931_shrink_below_one_freezes_at_min_height) {
  for (bool withoutErrata : kWithoutErrata) {
    YGConfigRef config = newConfig(withoutErrata);
    YGNodeRef root = YGNodeNewWithConfig(config);
    YGNodeStyleSetWidth(root, 500.0f);
    YGNodeStyleSetHeight(root, 400.0f);

    YGNodeRef shrinking = YGNodeNewWithConfig(config);
    YGNodeStyleSetWidth(shrinking, 100.0f);
    YGNodeStyleSetHeight(shrinking, 100.0f);
    YGNodeStyleSetMinHeight(shrinking, 25.0f);
    YGNodeStyleSetMaxHeight(shrinking, 300.0f);
    YGNodeStyleSetFlexBasis(shrinking, 150.0f);
    YGNodeStyleSetFlexGrow(shrinking, 0.33f);
    YGNodeStyleSetFlexShrink(shrinking, 0.25f);
    YGNodeInsertChild(root, shrinking, 0);

    YGNodeRef fixed = YGNodeNewWithConfig(config);
    YGNodeStyleSetWidth(fixed, 100.0f);
    YGNodeStyleSetHeight(fixed, 200.0f);
    YGNodeStyleSetMaxHeight(fixed, 200.0f);
    YGNodeStyleSetFlexGrow(fixed, 1.0f);
    YGNodeStyleSetFlexShrink(fixed, 0.0f);
    YGNodeInsertChild(root, fixed, 1);

    YGNodeRef basis = YGNodeNewWithConfig(config);
    YGNodeStyleSetWidth(basis, 100.0f);
    YGNodeStyleSetMinHeight(basis, 200.0f);
    YGNodeStyleSetFlexBasis(basis, 200.0f);
    YGNodeStyleSetFlexShrink(basis, 0.0f);
    YGNodeInsertChild(root, basis, 2);

    YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

    EXPECT_EQ(25.0f, YGNodeLayoutGetHeight(shrinking))
        << "withoutErrata " << withoutErrata;

    YGNodeFreeRecursive(root);
    YGConfigFree(config);
  }
}

// https://github.com/react/yoga/issues/2038
// The box freezes at 0, and freezing it left a 2^-19 residual. Shrink factors
// from #2039.
TEST(YGFlexShrinkAllFrozen, aspect_ratio_sole_shrinkable_item) {
  const float shrinkFactors[] = {
      1.0f, 2.0f, 3.0f, 6.0f, 9.0f, 11.0f, 12.0f, 19.0f, 22.0f, 999.0f};

  for (bool withoutErrata : kWithoutErrata) {
    for (float shrink : shrinkFactors) {
      YGConfigRef config = newConfig(withoutErrata);
      YGNodeRef box = nullptr;
      YGNodeRef sibling = nullptr;
      YGNodeRef root = newAspectRatioRow(config, shrink, &box, &sibling);

      YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

      EXPECT_EQ(0.0f, YGNodeLayoutGetWidth(box))
          << "withoutErrata " << withoutErrata << ", flexShrink " << shrink;
      EXPECT_EQ(0.0f, YGNodeLayoutGetHeight(box))
          << "withoutErrata " << withoutErrata << ", flexShrink " << shrink;
      EXPECT_EQ(0.0f, YGNodeLayoutGetLeft(sibling))
          << "withoutErrata " << withoutErrata << ", flexShrink " << shrink;

      YGNodeFreeRecursive(root);
      YGConfigFree(config);
    }
  }
}

// https://github.com/react/yoga/issues/2038
// With flexShrink 0 the box keeps its aspectRatio basis (21.08 x 23, rounded to
// 21 x 23). From #2039.
TEST(YGFlexShrinkAllFrozen, unshrinkable_item_keeps_aspect_ratio_basis) {
  for (bool withoutErrata : kWithoutErrata) {
    YGConfigRef config = newConfig(withoutErrata);
    YGNodeRef box = nullptr;
    YGNodeRef sibling = nullptr;
    YGNodeRef root = newAspectRatioRow(config, 0.0f, &box, &sibling);

    YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

    EXPECT_EQ(21.0f, YGNodeLayoutGetWidth(box))
        << "withoutErrata " << withoutErrata;
    EXPECT_EQ(23.0f, YGNodeLayoutGetHeight(box))
        << "withoutErrata " << withoutErrata;
    EXPECT_EQ(21.0f, YGNodeLayoutGetLeft(sibling))
        << "withoutErrata " << withoutErrata;

    YGNodeFreeRecursive(root);
    YGConfigFree(config);
  }
}
