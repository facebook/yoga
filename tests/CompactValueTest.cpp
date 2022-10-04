/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#define YOGA_COMPACT_VALUE_TEST

#include <yoga/CompactValue.h>
#include <gtest/gtest.h>
#include <cmath>

using facebook::yoga::detail::CompactValue;

const auto tooSmall = nextafterf(CompactValue::LOWER_BOUND, -INFINITY);
const auto tooLargePoints =
    nextafterf(CompactValue::UPPER_BOUND_POINT, INFINITY);
const auto tooLargePercent =
    nextafterf(CompactValue::UPPER_BOUND_PERCENT, INFINITY);

TEST(YogaTest, compact_value_can_represent_undefined) {
  auto c = CompactValue{YGValue{12.5f, YGUnitUndefined}};
  YGValue v = c;
  ASSERT_EQ(v, YGValueUndefined);
  ASSERT_NE(v, YGValueAuto);
  ASSERT_NE(v, (YGValue{-1.25, YGUnitPoint}));
  ASSERT_NE(v, (YGValue{25, YGUnitPercent}));
  ASSERT_TRUE(c.isUndefined());
  ASSERT_FALSE(c.isAuto());
}

TEST(YogaTest, compact_value_manages_infinity_as_undefined) {
  auto c = CompactValue{
      YGValue{std::numeric_limits<float>::infinity(), YGUnitUndefined}};
  YGValue v = c;
  ASSERT_EQ(v, YGValueUndefined);
  ASSERT_NE(v, YGValueAuto);
  ASSERT_NE(v, (YGValue{-1.25, YGUnitPoint}));
  ASSERT_NE(v, (YGValue{25, YGUnitPercent}));
  ASSERT_TRUE(c.isUndefined());
  ASSERT_FALSE(c.isAuto());
}

TEST(YogaTest, compact_value_can_represent_auto) {
  auto c = CompactValue{YGValue{0, YGUnitAuto}};
  YGValue v = c;
  ASSERT_NE(v, YGValueUndefined);
  ASSERT_EQ(v, YGValueAuto);
  ASSERT_NE(v, (YGValue{-1.25, YGUnitPoint}));
  ASSERT_NE(v, (YGValue{25, YGUnitPercent}));
  ASSERT_FALSE(c.isUndefined());
  ASSERT_TRUE(c.isAuto());
}

TEST(YogaTest, compact_value_can_represent_zero_points) {
  auto c = CompactValue{YGValue{0, YGUnitPoint}};
  YGValue v = c;
  ASSERT_NE(v, YGValueUndefined);
  ASSERT_NE(v, YGValueAuto);
  ASSERT_EQ(v, (YGValue{0, YGUnitPoint}));
  ASSERT_NE(v, (YGValue{0, YGUnitPercent}));
  ASSERT_FALSE(c.isUndefined());
  ASSERT_FALSE(c.isAuto());
}

TEST(YogaTest, compact_value_can_represent_lower_bound_points) {
  auto c = CompactValue({YGValue{CompactValue::LOWER_BOUND, YGUnitPoint}});
  YGValue v = c;
  ASSERT_NE(v, YGValueUndefined);
  ASSERT_NE(v, YGValueAuto);
  ASSERT_EQ(v, (YGValue{CompactValue::LOWER_BOUND, YGUnitPoint}));
  ASSERT_NE(v, (YGValue{CompactValue::LOWER_BOUND, YGUnitPercent}));
  ASSERT_FALSE(c.isUndefined());
  ASSERT_FALSE(c.isAuto());
}

TEST(YogaTest, compact_value_can_represent_negative_lower_bound_points) {
  auto c = CompactValue({YGValue{-CompactValue::LOWER_BOUND, YGUnitPoint}});
  YGValue v = c;
  ASSERT_NE(v, YGValueUndefined);
  ASSERT_NE(v, YGValueAuto);
  ASSERT_EQ(v, (YGValue{-CompactValue::LOWER_BOUND, YGUnitPoint}));
  ASSERT_NE(v, (YGValue{-CompactValue::LOWER_BOUND, YGUnitPercent}));
  ASSERT_FALSE(c.isUndefined());
  ASSERT_FALSE(c.isAuto());
}

TEST(YogaTest, compact_value_clamps_smaller_than_lower_bound_points_to_zero) {
  auto c = CompactValue({YGValue{tooSmall, YGUnitPoint}});
  YGValue v = c;
  ASSERT_NE(v, YGValueUndefined);
  ASSERT_NE(v, YGValueAuto);
  ASSERT_EQ(v, (YGValue{0, YGUnitPoint}));
  ASSERT_NE(v, (YGValue{0, YGUnitPercent}));
}

TEST(
    YogaTest,
    compact_value_clamps_greater_than_negative_lower_bound_points_to_zero) {
  auto c = CompactValue({YGValue{-tooSmall, YGUnitPoint}});
  YGValue v = c;
  ASSERT_NE(v, YGValueUndefined);
  ASSERT_NE(v, YGValueAuto);
  ASSERT_EQ(v, (YGValue{0, YGUnitPoint}));
  ASSERT_NE(v, (YGValue{0, YGUnitPercent}));
}

TEST(YogaTest, compact_value_can_represent_upper_bound_points) {
  auto c =
      CompactValue({YGValue{CompactValue::UPPER_BOUND_POINT, YGUnitPoint}});
  YGValue v = c;
  ASSERT_NE(v, YGValueUndefined);
  ASSERT_NE(v, YGValueAuto);
  ASSERT_EQ(v, (YGValue{CompactValue::UPPER_BOUND_POINT, YGUnitPoint}));
  ASSERT_NE(v, (YGValue{CompactValue::UPPER_BOUND_POINT, YGUnitPercent}));
  ASSERT_FALSE(c.isUndefined());
  ASSERT_FALSE(c.isAuto());
}

TEST(YogaTest, compact_value_can_represent_negative_upper_bound_points) {
  auto c =
      CompactValue({YGValue{-CompactValue::UPPER_BOUND_POINT, YGUnitPoint}});
  YGValue v = c;
  ASSERT_NE(v, YGValueUndefined);
  ASSERT_NE(v, YGValueAuto);
  ASSERT_EQ(v, (YGValue{-CompactValue::UPPER_BOUND_POINT, YGUnitPoint}));
  ASSERT_NE(v, (YGValue{-CompactValue::UPPER_BOUND_POINT, YGUnitPercent}));
  ASSERT_FALSE(c.isUndefined());
  ASSERT_FALSE(c.isAuto());
}

TEST(
    YogaTest,
    compact_value_clamps_greater_than__upper_bound_points_to_upper_bound) {
  auto c = CompactValue({YGValue{tooLargePoints, YGUnitPoint}});
  YGValue v = c;
  ASSERT_NE(v, YGValueUndefined);
  ASSERT_NE(v, YGValueAuto);
  ASSERT_EQ(v, (YGValue{CompactValue::UPPER_BOUND_POINT, YGUnitPoint}));
  ASSERT_NE(v, (YGValue{CompactValue::UPPER_BOUND_POINT, YGUnitPercent}));
}

TEST(
    YogaTest,
    compact_value_clamps_smaller_than_negative_upper_bound_points_to_upper_bound) {
  auto c = CompactValue({YGValue{-tooLargePoints, YGUnitPoint}});
  YGValue v = c;
  ASSERT_NE(v, YGValueUndefined);
  ASSERT_NE(v, YGValueAuto);
  ASSERT_EQ(v, (YGValue{-CompactValue::UPPER_BOUND_POINT, YGUnitPoint}));
  ASSERT_NE(v, (YGValue{-CompactValue::UPPER_BOUND_POINT, YGUnitPercent}));
}

TEST(YogaTest, compact_value_can_represent_one_point) {
  auto c = CompactValue({YGValue{1, YGUnitPoint}});
  YGValue v = c;
  ASSERT_NE(v, YGValueUndefined);
  ASSERT_NE(v, YGValueAuto);
  ASSERT_EQ(v, (YGValue{1, YGUnitPoint}));
  ASSERT_NE(v, (YGValue{1, YGUnitPercent}));
  ASSERT_FALSE(c.isUndefined());
  ASSERT_FALSE(c.isAuto());
}

TEST(YogaTest, compact_value_can_represent_negative_one_point) {
  auto c = CompactValue({YGValue{-1, YGUnitPoint}});
  YGValue v = c;
  ASSERT_NE(v, YGValueUndefined);
  ASSERT_NE(v, YGValueAuto);
  ASSERT_EQ(v, (YGValue{-1, YGUnitPoint}));
  ASSERT_NE(v, (YGValue{-1, YGUnitPercent}));
  ASSERT_FALSE(c.isUndefined());
  ASSERT_FALSE(c.isAuto());
}

TEST(YogaTest, compact_value_can_represent_zero_percent) {
  auto c = CompactValue{YGValue{0, YGUnitPercent}};
  YGValue v = c;
  ASSERT_NE(v, YGValueUndefined);
  ASSERT_NE(v, YGValueAuto);
  ASSERT_NE(v, (YGValue{0, YGUnitPoint}));
  ASSERT_EQ(v, (YGValue{0, YGUnitPercent}));
  ASSERT_FALSE(c.isUndefined());
  ASSERT_FALSE(c.isAuto());
}

TEST(YogaTest, compact_value_can_represent_lower_bound_percent) {
  auto c = CompactValue({YGValue{CompactValue::LOWER_BOUND, YGUnitPercent}});
  YGValue v = c;
  ASSERT_NE(v, YGValueUndefined);
  ASSERT_NE(v, YGValueAuto);
  ASSERT_NE(v, (YGValue{CompactValue::LOWER_BOUND, YGUnitPoint}));
  ASSERT_EQ(v, (YGValue{CompactValue::LOWER_BOUND, YGUnitPercent}));
  ASSERT_FALSE(c.isUndefined());
  ASSERT_FALSE(c.isAuto());
}

TEST(YogaTest, compact_value_can_represent_negative_lower_bound_percent) {
  auto c = CompactValue({YGValue{-CompactValue::LOWER_BOUND, YGUnitPercent}});
  YGValue v = c;
  ASSERT_NE(v, YGValueUndefined);
  ASSERT_NE(v, YGValueAuto);
  ASSERT_NE(v, (YGValue{-CompactValue::LOWER_BOUND, YGUnitPoint}));
  ASSERT_EQ(v, (YGValue{-CompactValue::LOWER_BOUND, YGUnitPercent}));
  ASSERT_FALSE(c.isUndefined());
  ASSERT_FALSE(c.isAuto());
}

TEST(YogaTest, compact_value_clamps_smaller_than_lower_bound_percent_to_zero) {
  auto c = CompactValue({YGValue{tooSmall, YGUnitPercent}});
  YGValue v = c;
  ASSERT_NE(v, YGValueUndefined);
  ASSERT_NE(v, YGValueAuto);
  ASSERT_NE(v, (YGValue{0, YGUnitPoint}));
  ASSERT_EQ(v, (YGValue{0, YGUnitPercent}));
}

TEST(
    YogaTest,
    compact_value_clamps_greater_than_negative_lower_bound_percent_to_zero) {
  auto c = CompactValue({YGValue{-tooSmall, YGUnitPercent}});
  YGValue v = c;
  ASSERT_NE(v, YGValueUndefined);
  ASSERT_NE(v, YGValueAuto);
  ASSERT_NE(v, (YGValue{0, YGUnitPoint}));
  ASSERT_EQ(v, (YGValue{0, YGUnitPercent}));
}

TEST(YogaTest, compact_value_can_represent_upper_bound_percent) {
  auto c =
      CompactValue({YGValue{CompactValue::UPPER_BOUND_PERCENT, YGUnitPercent}});
  YGValue v = c;
  ASSERT_NE(v, YGValueUndefined);
  ASSERT_NE(v, YGValueAuto);
  ASSERT_NE(v, (YGValue{CompactValue::UPPER_BOUND_PERCENT, YGUnitPoint}));
  ASSERT_EQ(v, (YGValue{CompactValue::UPPER_BOUND_PERCENT, YGUnitPercent}));
  ASSERT_FALSE(c.isUndefined());
  ASSERT_FALSE(c.isAuto());
}

TEST(YogaTest, compact_value_can_represent_negative_upper_bound_percent) {
  auto c = CompactValue(
      {YGValue{-CompactValue::UPPER_BOUND_PERCENT, YGUnitPercent}});
  YGValue v = c;
  ASSERT_NE(v, YGValueUndefined);
  ASSERT_NE(v, YGValueAuto);
  ASSERT_NE(v, (YGValue{-CompactValue::UPPER_BOUND_PERCENT, YGUnitPoint}));
  ASSERT_EQ(v, (YGValue{-CompactValue::UPPER_BOUND_PERCENT, YGUnitPercent}));
  ASSERT_FALSE(c.isUndefined());
  ASSERT_FALSE(c.isAuto());
}

TEST(
    YogaTest,
    compact_value_clamps_greater_than_upper_bound_percent_to_upper_bound) {
  auto c = CompactValue({YGValue{tooLargePercent, YGUnitPercent}});
  YGValue v = c;
  ASSERT_NE(v, YGValueUndefined);
  ASSERT_NE(v, YGValueAuto);
  ASSERT_NE(v, (YGValue{CompactValue::UPPER_BOUND_PERCENT, YGUnitPoint}));
  ASSERT_EQ(v, (YGValue{CompactValue::UPPER_BOUND_PERCENT, YGUnitPercent}));
}

TEST(
    YogaTest,
    compact_value_clamps_smaller_than_negative_upper_bound_percent_to_upper_bound) {
  auto c = CompactValue({YGValue{-tooLargePercent, YGUnitPercent}});
  YGValue v = c;
  ASSERT_NE(v, YGValueUndefined);
  ASSERT_NE(v, YGValueAuto);
  ASSERT_NE(v, (YGValue{-CompactValue::UPPER_BOUND_PERCENT, YGUnitPoint}));
  ASSERT_EQ(v, (YGValue{-CompactValue::UPPER_BOUND_PERCENT, YGUnitPercent}));
}

TEST(YogaTest, compact_value_can_represent_one_percent) {
  auto c = CompactValue({YGValue{1, YGUnitPercent}});
  YGValue v = c;
  ASSERT_NE(v, YGValueUndefined);
  ASSERT_NE(v, YGValueAuto);
  ASSERT_NE(v, (YGValue{1, YGUnitPoint}));
  ASSERT_EQ(v, (YGValue{1, YGUnitPercent}));
  ASSERT_FALSE(c.isUndefined());
  ASSERT_FALSE(c.isAuto());
}

TEST(YogaTest, compact_value_can_represent_negative_one_percent) {
  auto c = CompactValue({YGValue{-1, YGUnitPercent}});
  YGValue v = c;
  ASSERT_NE(v, YGValueUndefined);
  ASSERT_NE(v, YGValueAuto);
  ASSERT_NE(v, (YGValue{-1, YGUnitPoint}));
  ASSERT_EQ(v, (YGValue{-1, YGUnitPercent}));
  ASSERT_FALSE(c.isUndefined());
  ASSERT_FALSE(c.isAuto());
}

TEST(YogaTest, dedicated_unit_factories) {
  ASSERT_EQ(CompactValue::ofUndefined(), CompactValue(YGValueUndefined));
  ASSERT_EQ(CompactValue::ofAuto(), CompactValue(YGValueAuto));
  ASSERT_EQ(
      CompactValue::of<YGUnitPoint>(-9876.5f),
      CompactValue(YGValue{-9876.5f, YGUnitPoint}));
  ASSERT_EQ(
      CompactValue::of<YGUnitPercent>(123.456f),
      CompactValue(YGValue{123.456f, YGUnitPercent}));
}

TEST(YogaTest, dedicated_unit_maybe_factories) {
  ASSERT_EQ(
      CompactValue::ofMaybe<YGUnitPoint>(-9876.5f),
      CompactValue(YGValue{-9876.5f, YGUnitPoint}));
  ASSERT_EQ(
      CompactValue::ofMaybe<YGUnitPoint>(YGUndefined),
      CompactValue(YGValueUndefined));
  ASSERT_EQ(
      CompactValue::ofMaybe<YGUnitPercent>(123.456f),
      CompactValue(YGValue{123.456f, YGUnitPercent}));
  ASSERT_EQ(
      CompactValue::ofMaybe<YGUnitPercent>(YGUndefined),
      CompactValue(YGValueUndefined));
}

TEST(YogaTest, can_be_assigned_from_YGValue) {
  CompactValue c{};

  YGValue v{2.0f, YGUnitPercent};
  c = v;
  ASSERT_EQ((YGValue) c, v);

  c = YGValue{123, YGUnitPoint};
  ASSERT_EQ((YGValue) c, (YGValue{123, YGUnitPoint}));
}

TEST(YogaTest, compact_value_bound_representations) {
  ASSERT_EQ(
      CompactValue::of<YGUnitPoint>(CompactValue::LOWER_BOUND).repr(),
      uint32_t{0});
  ASSERT_EQ(
      CompactValue::of<YGUnitPoint>(CompactValue::UPPER_BOUND_POINT).repr(),
      uint32_t{0x3fffffff});
  ASSERT_EQ(
      CompactValue::of<YGUnitPercent>(CompactValue::LOWER_BOUND).repr(),
      uint32_t{0x40000000});
  ASSERT_EQ(
      CompactValue::of<YGUnitPercent>(CompactValue::UPPER_BOUND_PERCENT).repr(),
      uint32_t{0x7f7fffff});

  ASSERT_EQ(
      CompactValue::of<YGUnitPoint>(-CompactValue::LOWER_BOUND).repr(),
      uint32_t{0x80000000});
  ASSERT_EQ(
      CompactValue::of<YGUnitPoint>(-CompactValue::UPPER_BOUND_POINT).repr(),
      uint32_t{0xbfffffff});
  ASSERT_EQ(
      CompactValue::of<YGUnitPercent>(-CompactValue::LOWER_BOUND).repr(),
      uint32_t{0xc0000000});
  ASSERT_EQ(
      CompactValue::of<YGUnitPercent>(-CompactValue::UPPER_BOUND_PERCENT)
          .repr(),
      uint32_t{0xff7fffff});
}
