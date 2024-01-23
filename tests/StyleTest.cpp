/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>
#include <yoga/style/Style.h>

namespace facebook::yoga {

TEST(Style, computed_padding_is_floored) {
  yoga::Style style;
  style.setPadding(Edge::All, value::points(-1.0f));
  auto paddingStart = style.computeInlineStartPadding(
      FlexDirection::Row, Direction::LTR, 0.0f /*widthSize*/);
  ASSERT_EQ(paddingStart, 0.0f);
}

TEST(Style, computed_border_is_floored) {
  yoga::Style style;
  style.setBorder(Edge::All, value::points(-1.0f));
  auto borderStart =
      style.computeInlineStartBorder(FlexDirection::Row, Direction::LTR);
  ASSERT_EQ(borderStart, 0.0f);
}

TEST(Style, computed_gap_is_floored) {
  yoga::Style style;
  style.setGap(Gutter::Column, value::points(-1.0f));
  auto gapBetweenColumns = style.computeGapForAxis(FlexDirection::Row);
  ASSERT_EQ(gapBetweenColumns, 0.0f);
}

TEST(Style, computed_margin_is_not_floored) {
  yoga::Style style;
  style.setMargin(Edge::All, value::points(-1.0f));
  auto marginStart = style.computeInlineStartMargin(
      FlexDirection::Row, Direction::LTR, 0.0f /*widthSize*/);
  ASSERT_EQ(marginStart, -1.0f);
}

} // namespace facebook::yoga
