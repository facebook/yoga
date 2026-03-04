/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>
#include <yoga/Yoga.h>

// Tests for the FlexBasisFitContentInMainAxis errata.
//
// For non-scroll container nodes, FitContent and MaxContent produce the same
// final dimensions (both use content-based sizing). The errata primarily
// affects re-measurement/caching behavior (performance), not layout values.
//
// The one visible layout difference is Check 1: when mainAxisSize is NaN
// (e.g. inside a scroll content container), the errata causes flex-basis
// to be ignored, while the corrected behavior accepts positive flex-basis
// regardless of mainAxisSize.

// Verify that container children produce the same layout regardless of errata
// when the child's content overflows a definite-height column parent.
// FitContent and MaxContent both resolve to content size for containers.
TEST(YogaTest, flex_basis_fit_content_errata_column_same_layout) {
  // With errata
  {
    YGConfigRef config = YGConfigNew();
    YGConfigSetErrata(config, YGErrataFlexBasisFitContentInMainAxis);

    YGNodeRef root = YGNodeNewWithConfig(config);
    YGNodeStyleSetWidth(root, 200);
    YGNodeStyleSetHeight(root, 300);

    YGNodeRef root_child0 = YGNodeNewWithConfig(config);
    YGNodeInsertChild(root, root_child0, 0);

    YGNodeRef root_child0_child0 = YGNodeNewWithConfig(config);
    YGNodeStyleSetWidth(root_child0_child0, 50);
    YGNodeStyleSetHeight(root_child0_child0, 500);
    YGNodeInsertChild(root_child0, root_child0_child0, 0);

    YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

    ASSERT_FLOAT_EQ(200, YGNodeLayoutGetWidth(root));
    ASSERT_FLOAT_EQ(300, YGNodeLayoutGetHeight(root));

    // Container child gets content height (500) even with FitContent errata,
    // because FitContent and MaxContent produce the same result for containers.
    ASSERT_FLOAT_EQ(200, YGNodeLayoutGetWidth(root_child0));
    ASSERT_FLOAT_EQ(500, YGNodeLayoutGetHeight(root_child0));

    ASSERT_FLOAT_EQ(50, YGNodeLayoutGetWidth(root_child0_child0));
    ASSERT_FLOAT_EQ(500, YGNodeLayoutGetHeight(root_child0_child0));

    YGNodeFreeRecursive(root);
    YGConfigFree(config);
  }

  // Without errata (same result)
  {
    YGConfigRef config = YGConfigNew();

    YGNodeRef root = YGNodeNewWithConfig(config);
    YGNodeStyleSetWidth(root, 200);
    YGNodeStyleSetHeight(root, 300);

    YGNodeRef root_child0 = YGNodeNewWithConfig(config);
    YGNodeInsertChild(root, root_child0, 0);

    YGNodeRef root_child0_child0 = YGNodeNewWithConfig(config);
    YGNodeStyleSetWidth(root_child0_child0, 50);
    YGNodeStyleSetHeight(root_child0_child0, 500);
    YGNodeInsertChild(root_child0, root_child0_child0, 0);

    YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

    ASSERT_FLOAT_EQ(200, YGNodeLayoutGetWidth(root));
    ASSERT_FLOAT_EQ(300, YGNodeLayoutGetHeight(root));

    ASSERT_FLOAT_EQ(200, YGNodeLayoutGetWidth(root_child0));
    ASSERT_FLOAT_EQ(500, YGNodeLayoutGetHeight(root_child0));

    ASSERT_FLOAT_EQ(50, YGNodeLayoutGetWidth(root_child0_child0));
    ASSERT_FLOAT_EQ(500, YGNodeLayoutGetHeight(root_child0_child0));

    YGNodeFreeRecursive(root);
    YGConfigFree(config);
  }
}

// Same test but for row direction.
TEST(YogaTest, flex_basis_fit_content_errata_row_same_layout) {
  // With errata
  {
    YGConfigRef config = YGConfigNew();
    YGConfigSetErrata(config, YGErrataFlexBasisFitContentInMainAxis);

    YGNodeRef root = YGNodeNewWithConfig(config);
    YGNodeStyleSetFlexDirection(root, YGFlexDirectionRow);
    YGNodeStyleSetWidth(root, 300);
    YGNodeStyleSetHeight(root, 200);

    YGNodeRef root_child0 = YGNodeNewWithConfig(config);
    YGNodeInsertChild(root, root_child0, 0);

    YGNodeRef root_child0_child0 = YGNodeNewWithConfig(config);
    YGNodeStyleSetWidth(root_child0_child0, 500);
    YGNodeStyleSetHeight(root_child0_child0, 50);
    YGNodeInsertChild(root_child0, root_child0_child0, 0);

    YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

    ASSERT_FLOAT_EQ(300, YGNodeLayoutGetWidth(root));
    ASSERT_FLOAT_EQ(200, YGNodeLayoutGetHeight(root));

    ASSERT_FLOAT_EQ(500, YGNodeLayoutGetWidth(root_child0));
    ASSERT_FLOAT_EQ(200, YGNodeLayoutGetHeight(root_child0));

    ASSERT_FLOAT_EQ(500, YGNodeLayoutGetWidth(root_child0_child0));
    ASSERT_FLOAT_EQ(50, YGNodeLayoutGetHeight(root_child0_child0));

    YGNodeFreeRecursive(root);
    YGConfigFree(config);
  }

  // Without errata (same result)
  {
    YGConfigRef config = YGConfigNew();

    YGNodeRef root = YGNodeNewWithConfig(config);
    YGNodeStyleSetFlexDirection(root, YGFlexDirectionRow);
    YGNodeStyleSetWidth(root, 300);
    YGNodeStyleSetHeight(root, 200);

    YGNodeRef root_child0 = YGNodeNewWithConfig(config);
    YGNodeInsertChild(root, root_child0, 0);

    YGNodeRef root_child0_child0 = YGNodeNewWithConfig(config);
    YGNodeStyleSetWidth(root_child0_child0, 500);
    YGNodeStyleSetHeight(root_child0_child0, 50);
    YGNodeInsertChild(root_child0, root_child0_child0, 0);

    YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

    ASSERT_FLOAT_EQ(300, YGNodeLayoutGetWidth(root));
    ASSERT_FLOAT_EQ(200, YGNodeLayoutGetHeight(root));

    ASSERT_FLOAT_EQ(500, YGNodeLayoutGetWidth(root_child0));
    ASSERT_FLOAT_EQ(200, YGNodeLayoutGetHeight(root_child0));

    ASSERT_FLOAT_EQ(500, YGNodeLayoutGetWidth(root_child0_child0));
    ASSERT_FLOAT_EQ(50, YGNodeLayoutGetHeight(root_child0_child0));

    YGNodeFreeRecursive(root);
    YGConfigFree(config);
  }
}

// Scroll containers use MaxContent in main axis regardless of errata.
TEST(YogaTest, flex_basis_fit_content_errata_scroll_same_layout) {
  // With errata
  {
    YGConfigRef config = YGConfigNew();
    YGConfigSetErrata(config, YGErrataFlexBasisFitContentInMainAxis);

    YGNodeRef root = YGNodeNewWithConfig(config);
    YGNodeStyleSetWidth(root, 200);
    YGNodeStyleSetHeight(root, 300);
    YGNodeStyleSetOverflow(root, YGOverflowScroll);

    YGNodeRef root_child0 = YGNodeNewWithConfig(config);
    YGNodeInsertChild(root, root_child0, 0);

    YGNodeRef root_child0_child0 = YGNodeNewWithConfig(config);
    YGNodeStyleSetHeight(root_child0_child0, 500);
    YGNodeInsertChild(root_child0, root_child0_child0, 0);

    YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

    ASSERT_FLOAT_EQ(200, YGNodeLayoutGetWidth(root));
    ASSERT_FLOAT_EQ(300, YGNodeLayoutGetHeight(root));

    ASSERT_FLOAT_EQ(200, YGNodeLayoutGetWidth(root_child0));
    ASSERT_FLOAT_EQ(500, YGNodeLayoutGetHeight(root_child0));

    ASSERT_FLOAT_EQ(200, YGNodeLayoutGetWidth(root_child0_child0));
    ASSERT_FLOAT_EQ(500, YGNodeLayoutGetHeight(root_child0_child0));

    YGNodeFreeRecursive(root);
    YGConfigFree(config);
  }

  // Without errata (same result)
  {
    YGConfigRef config = YGConfigNew();

    YGNodeRef root = YGNodeNewWithConfig(config);
    YGNodeStyleSetWidth(root, 200);
    YGNodeStyleSetHeight(root, 300);
    YGNodeStyleSetOverflow(root, YGOverflowScroll);

    YGNodeRef root_child0 = YGNodeNewWithConfig(config);
    YGNodeInsertChild(root, root_child0, 0);

    YGNodeRef root_child0_child0 = YGNodeNewWithConfig(config);
    YGNodeStyleSetHeight(root_child0_child0, 500);
    YGNodeInsertChild(root_child0, root_child0_child0, 0);

    YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

    ASSERT_FLOAT_EQ(200, YGNodeLayoutGetWidth(root));
    ASSERT_FLOAT_EQ(300, YGNodeLayoutGetHeight(root));

    ASSERT_FLOAT_EQ(200, YGNodeLayoutGetWidth(root_child0));
    ASSERT_FLOAT_EQ(500, YGNodeLayoutGetHeight(root_child0));

    ASSERT_FLOAT_EQ(200, YGNodeLayoutGetWidth(root_child0_child0));
    ASSERT_FLOAT_EQ(500, YGNodeLayoutGetHeight(root_child0_child0));

    YGNodeFreeRecursive(root);
    YGConfigFree(config);
  }
}

// With errata: flex-basis is ignored when mainAxisSize is NaN, because the
// old condition requires isDefined(mainAxisSize). Items inside a scroll
// container's auto-height content container get height 0.
TEST(YogaTest, flex_basis_in_scroll_content_with_errata) {
  YGConfigRef config = YGConfigNew();
  YGConfigSetErrata(config, YGErrataFlexBasisFitContentInMainAxis);

  YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetWidth(root, 200);
  YGNodeStyleSetHeight(root, 300);
  YGNodeStyleSetOverflow(root, YGOverflowScroll);

  // Content container: auto height, measured with MaxContent by scroll parent
  YGNodeRef root_child0 = YGNodeNewWithConfig(config);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeRef root_child0_child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexBasis(root_child0_child0, 200);
  YGNodeInsertChild(root_child0, root_child0_child0, 0);

  YGNodeRef root_child0_child1 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexBasis(root_child0_child1, 300);
  YGNodeInsertChild(root_child0, root_child0_child1, 1);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(200, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(300, YGNodeLayoutGetHeight(root));

  // Content container has 0 height because items' flex-basis is ignored
  ASSERT_FLOAT_EQ(200, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(200, YGNodeLayoutGetWidth(root_child0_child0));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetHeight(root_child0_child0));

  ASSERT_FLOAT_EQ(200, YGNodeLayoutGetWidth(root_child0_child1));
  ASSERT_FLOAT_EQ(0, YGNodeLayoutGetHeight(root_child0_child1));

  YGNodeFreeRecursive(root);
  YGConfigFree(config);
}

// Without errata: flex-basis is respected even when mainAxisSize is NaN.
// The corrected condition accepts positive resolvedFlexBasis regardless
// of mainAxisSize, so items get their specified flex-basis heights.
TEST(YogaTest, flex_basis_in_scroll_content_without_errata) {
  YGConfigRef config = YGConfigNew();
  // No errata (default: Errata::None)

  YGNodeRef root = YGNodeNewWithConfig(config);
  YGNodeStyleSetWidth(root, 200);
  YGNodeStyleSetHeight(root, 300);
  YGNodeStyleSetOverflow(root, YGOverflowScroll);

  YGNodeRef root_child0 = YGNodeNewWithConfig(config);
  YGNodeInsertChild(root, root_child0, 0);

  YGNodeRef root_child0_child0 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexBasis(root_child0_child0, 200);
  YGNodeInsertChild(root_child0, root_child0_child0, 0);

  YGNodeRef root_child0_child1 = YGNodeNewWithConfig(config);
  YGNodeStyleSetFlexBasis(root_child0_child1, 300);
  YGNodeInsertChild(root_child0, root_child0_child1, 1);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_FLOAT_EQ(200, YGNodeLayoutGetWidth(root));
  ASSERT_FLOAT_EQ(300, YGNodeLayoutGetHeight(root));

  // Content container has height 500 (200 + 300 from items' flex-basis)
  ASSERT_FLOAT_EQ(200, YGNodeLayoutGetWidth(root_child0));
  ASSERT_FLOAT_EQ(500, YGNodeLayoutGetHeight(root_child0));

  ASSERT_FLOAT_EQ(200, YGNodeLayoutGetWidth(root_child0_child0));
  ASSERT_FLOAT_EQ(200, YGNodeLayoutGetHeight(root_child0_child0));

  ASSERT_FLOAT_EQ(200, YGNodeLayoutGetTop(root_child0_child1));
  ASSERT_FLOAT_EQ(200, YGNodeLayoutGetWidth(root_child0_child1));
  ASSERT_FLOAT_EQ(300, YGNodeLayoutGetHeight(root_child0_child1));

  YGNodeFreeRecursive(root);
  YGConfigFree(config);
}
