/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#define YOGA_COMPACT_VALUE_TEST

#include <gtest/gtest.h>
#include <yoga/style/CompactValue.h>
#include <cmath>

using namespace facebook::yoga;

const auto tooSmall = nextafterf(CompactValue::LOWER_BOUND, -INFINITY);
const auto tooLargePoints =
    nextafterf(CompactValue::UPPER_BOUND_POINT, INFINITY);
const auto tooLargePercent =
    nextafterf(CompactValue::UPPER_BOUND_PERCENT, INFINITY);

TEST(YogaTest, compact_value_can_represent_undefined) {
  auto c = CompactValue{value::undefined()};
  auto v = (StyleLength)c;
  ASSERT_EQ(v, value::undefined());
  ASSERT_NE(v, value::ofAuto());
  ASSERT_NE(v, value::points(-1.25));
  ASSERT_NE(v, value::percent(25));
  ASSERT_TRUE(c.isUndefined());
  ASSERT_FALSE(c.isAuto());
}

TEST(YogaTest, compact_value_manages_infinity_as_undefined) {
  auto c = CompactValue{value::points(std::numeric_limits<float>::infinity())};
  auto v = (StyleLength)c;
  ASSERT_EQ(v, value::undefined());
  ASSERT_NE(v, value::ofAuto());
  ASSERT_NE(v, value::points(-1.25));
  ASSERT_NE(v, value::percent(25));
  ASSERT_TRUE(c.isUndefined());
  ASSERT_FALSE(c.isAuto());
}

TEST(YogaTest, compact_value_can_represent_auto) {
  auto c = CompactValue{value::ofAuto()};
  auto v = (StyleLength)c;
  ASSERT_NE(v, value::undefined());
  ASSERT_EQ(v, value::ofAuto());
  ASSERT_NE(v, value::points(-1.25));
  ASSERT_NE(v, value::percent(25));
  ASSERT_FALSE(c.isUndefined());
  ASSERT_TRUE(c.isAuto());
}

TEST(YogaTest, compact_value_can_represent_zero_points) {
  auto c = CompactValue{value::points(0)};
  auto v = (StyleLength)c;
  ASSERT_NE(v, value::undefined());
  ASSERT_NE(v, value::ofAuto());
  ASSERT_EQ(v, value::points(0));
  ASSERT_NE(v, value::percent(0));
  ASSERT_FALSE(c.isUndefined());
  ASSERT_FALSE(c.isAuto());
}

TEST(YogaTest, compact_value_can_represent_lower_bound_points) {
  auto c = CompactValue({value::points(CompactValue::LOWER_BOUND)});
  auto v = (StyleLength)c;
  ASSERT_NE(v, value::undefined());
  ASSERT_NE(v, value::ofAuto());
  ASSERT_EQ(v, value::points(CompactValue::LOWER_BOUND));
  ASSERT_NE(v, value::percent(CompactValue::LOWER_BOUND));
  ASSERT_FALSE(c.isUndefined());
  ASSERT_FALSE(c.isAuto());
}

TEST(YogaTest, compact_value_can_represent_negative_lower_bound_points) {
  auto c = CompactValue({value::points(-CompactValue::LOWER_BOUND)});
  auto v = (StyleLength)c;
  ASSERT_NE(v, value::undefined());
  ASSERT_NE(v, value::ofAuto());
  ASSERT_EQ(v, value::points(-CompactValue::LOWER_BOUND));
  ASSERT_NE(v, value::percent(-CompactValue::LOWER_BOUND));
  ASSERT_FALSE(c.isUndefined());
  ASSERT_FALSE(c.isAuto());
}

TEST(YogaTest, compact_value_clamps_smaller_than_lower_bound_points_to_zero) {
  auto c = CompactValue({value::points(tooSmall)});
  auto v = (StyleLength)c;
  ASSERT_NE(v, value::undefined());
  ASSERT_NE(v, value::ofAuto());
  ASSERT_EQ(v, value::points(0));
  ASSERT_NE(v, value::percent(0));
}

TEST(
    YogaTest,
    compact_value_clamps_greater_than_negative_lower_bound_points_to_zero) {
  auto c = CompactValue({value::points(-tooSmall)});
  auto v = (StyleLength)c;
  ASSERT_NE(v, value::undefined());
  ASSERT_NE(v, value::ofAuto());
  ASSERT_EQ(v, value::points(0));
  ASSERT_NE(v, value::percent(0));
}

TEST(YogaTest, compact_value_can_represent_upper_bound_points) {
  auto c = CompactValue({value::points(CompactValue::UPPER_BOUND_POINT)});
  auto v = (StyleLength)c;
  ASSERT_NE(v, value::undefined());
  ASSERT_NE(v, value::ofAuto());
  ASSERT_EQ(v, value::points(CompactValue::UPPER_BOUND_POINT));
  ASSERT_NE(v, value::percent(CompactValue::UPPER_BOUND_POINT));
  ASSERT_FALSE(c.isUndefined());
  ASSERT_FALSE(c.isAuto());
}

TEST(YogaTest, compact_value_can_represent_negative_upper_bound_points) {
  auto c = CompactValue({value::points(-CompactValue::UPPER_BOUND_POINT)});
  auto v = (StyleLength)c;
  ASSERT_NE(v, value::undefined());
  ASSERT_NE(v, value::ofAuto());
  ASSERT_EQ(v, value::points(-CompactValue::UPPER_BOUND_POINT));
  ASSERT_NE(v, value::percent(-CompactValue::UPPER_BOUND_POINT));
  ASSERT_FALSE(c.isUndefined());
  ASSERT_FALSE(c.isAuto());
}

TEST(
    YogaTest,
    compact_value_clamps_greater_than__upper_bound_points_to_upper_bound) {
  auto c = CompactValue({value::points(tooLargePoints)});
  auto v = (StyleLength)c;
  ASSERT_NE(v, value::undefined());
  ASSERT_NE(v, value::ofAuto());
  ASSERT_EQ(v, value::points(CompactValue::UPPER_BOUND_POINT));
  ASSERT_NE(v, value::percent(CompactValue::UPPER_BOUND_POINT));
}

TEST(
    YogaTest,
    compact_value_clamps_smaller_than_negative_upper_bound_points_to_upper_bound) {
  auto c = CompactValue({value::points(-tooLargePoints)});
  auto v = (StyleLength)c;
  ASSERT_NE(v, value::undefined());
  ASSERT_NE(v, value::ofAuto());
  ASSERT_EQ(v, value::points(-CompactValue::UPPER_BOUND_POINT));
  ASSERT_NE(v, value::percent(-CompactValue::UPPER_BOUND_POINT));
}

TEST(YogaTest, compact_value_can_represent_one_point) {
  auto c = CompactValue({value::points(1)});
  auto v = (StyleLength)c;
  ASSERT_NE(v, value::undefined());
  ASSERT_NE(v, value::ofAuto());
  ASSERT_EQ(v, value::points(1));
  ASSERT_NE(v, value::percent(1));
  ASSERT_FALSE(c.isUndefined());
  ASSERT_FALSE(c.isAuto());
}

TEST(YogaTest, compact_value_can_represent_negative_one_point) {
  auto c = CompactValue({value::points(-1)});
  auto v = (StyleLength)c;
  ASSERT_NE(v, value::undefined());
  ASSERT_NE(v, value::ofAuto());
  ASSERT_EQ(v, value::points(-1));
  ASSERT_NE(v, value::percent(-1));
  ASSERT_FALSE(c.isUndefined());
  ASSERT_FALSE(c.isAuto());
}

TEST(YogaTest, compact_value_can_represent_zero_percent) {
  auto c = CompactValue{value::percent(0)};
  auto v = (StyleLength)c;
  ASSERT_NE(v, value::undefined());
  ASSERT_NE(v, value::ofAuto());
  ASSERT_NE(v, value::points(0));
  ASSERT_EQ(v, value::percent(0));
  ASSERT_FALSE(c.isUndefined());
  ASSERT_FALSE(c.isAuto());
}

TEST(YogaTest, compact_value_can_represent_lower_bound_percent) {
  auto c = CompactValue({value::percent(CompactValue::LOWER_BOUND)});
  auto v = (StyleLength)c;
  ASSERT_NE(v, value::undefined());
  ASSERT_NE(v, value::ofAuto());
  ASSERT_NE(v, value::points(CompactValue::LOWER_BOUND));
  ASSERT_EQ(v, value::percent(CompactValue::LOWER_BOUND));
  ASSERT_FALSE(c.isUndefined());
  ASSERT_FALSE(c.isAuto());
}

TEST(YogaTest, compact_value_can_represent_negative_lower_bound_percent) {
  auto c = CompactValue({value::percent(-CompactValue::LOWER_BOUND)});
  auto v = (StyleLength)c;
  ASSERT_NE(v, value::undefined());
  ASSERT_NE(v, value::ofAuto());
  ASSERT_NE(v, value::points(-CompactValue::LOWER_BOUND));
  ASSERT_EQ(v, value::percent(-CompactValue::LOWER_BOUND));
  ASSERT_FALSE(c.isUndefined());
  ASSERT_FALSE(c.isAuto());
}

TEST(YogaTest, compact_value_clamps_smaller_than_lower_bound_percent_to_zero) {
  auto c = CompactValue({value::percent(tooSmall)});
  auto v = (StyleLength)c;
  ASSERT_NE(v, value::undefined());
  ASSERT_NE(v, value::ofAuto());
  ASSERT_NE(v, value::points(0));
  ASSERT_EQ(v, value::percent(0));
}

TEST(
    YogaTest,
    compact_value_clamps_greater_than_negative_lower_bound_percent_to_zero) {
  auto c = CompactValue({value::percent(-tooSmall)});
  auto v = (StyleLength)c;
  ASSERT_NE(v, value::undefined());
  ASSERT_NE(v, value::ofAuto());
  ASSERT_NE(v, value::points(0));
  ASSERT_EQ(v, value::percent(0));
}

TEST(YogaTest, compact_value_can_represent_upper_bound_percent) {
  auto c = CompactValue({value::percent(CompactValue::UPPER_BOUND_PERCENT)});
  auto v = (StyleLength)c;
  ASSERT_NE(v, value::undefined());
  ASSERT_NE(v, value::ofAuto());
  ASSERT_NE(v, value::points(CompactValue::UPPER_BOUND_PERCENT));
  ASSERT_EQ(v, value::percent(CompactValue::UPPER_BOUND_PERCENT));
  ASSERT_FALSE(c.isUndefined());
  ASSERT_FALSE(c.isAuto());
}

TEST(YogaTest, compact_value_can_represent_negative_upper_bound_percent) {
  auto c = CompactValue({value::percent(-CompactValue::UPPER_BOUND_PERCENT)});
  auto v = (StyleLength)c;
  ASSERT_NE(v, value::undefined());
  ASSERT_NE(v, value::ofAuto());
  ASSERT_NE(v, value::points(-CompactValue::UPPER_BOUND_PERCENT));
  ASSERT_EQ(v, value::percent(-CompactValue::UPPER_BOUND_PERCENT));
  ASSERT_FALSE(c.isUndefined());
  ASSERT_FALSE(c.isAuto());
}

TEST(
    YogaTest,
    compact_value_clamps_greater_than_upper_bound_percent_to_upper_bound) {
  auto c = CompactValue({value::percent(tooLargePercent)});
  auto v = (StyleLength)c;
  ASSERT_NE(v, value::undefined());
  ASSERT_NE(v, value::ofAuto());
  ASSERT_NE(v, value::points(CompactValue::UPPER_BOUND_PERCENT));
  ASSERT_EQ(v, value::percent(CompactValue::UPPER_BOUND_PERCENT));
}

TEST(
    YogaTest,
    compact_value_clamps_smaller_than_negative_upper_bound_percent_to_upper_bound) {
  auto c = CompactValue({value::percent(-tooLargePercent)});
  auto v = (StyleLength)c;
  ASSERT_NE(v, value::undefined());
  ASSERT_NE(v, value::ofAuto());
  ASSERT_NE(v, value::points(-CompactValue::UPPER_BOUND_PERCENT));
  ASSERT_EQ(v, value::percent(-CompactValue::UPPER_BOUND_PERCENT));
}

TEST(YogaTest, compact_value_can_represent_one_percent) {
  auto c = CompactValue({value::percent(1)});
  auto v = (StyleLength)c;
  ASSERT_NE(v, value::undefined());
  ASSERT_NE(v, value::ofAuto());
  ASSERT_NE(v, value::points(1));
  ASSERT_EQ(v, value::percent(1));
  ASSERT_FALSE(c.isUndefined());
  ASSERT_FALSE(c.isAuto());
}

TEST(YogaTest, compact_value_can_represent_negative_one_percent) {
  auto c = CompactValue({value::percent(-1)});
  auto v = (StyleLength)c;
  ASSERT_NE(v, value::undefined());
  ASSERT_NE(v, value::ofAuto());
  ASSERT_NE(v, value::points(-1));
  ASSERT_EQ(v, value::percent(-1));
  ASSERT_FALSE(c.isUndefined());
  ASSERT_FALSE(c.isAuto());
}
