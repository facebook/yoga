/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>

#include <yoga/bits/NumericBitfield.h>
#include <cstdint>

namespace facebook::yoga {

TEST(NumericBitfield, one_boolean_defaults_to_false) {
  constexpr uint32_t flags = 0;

  ASSERT_EQ(getBooleanData(flags, 0), false);
  static_assert(
      getBooleanData(flags, 0) == false,
      "first boolean member must default to false");
}

TEST(NumericBitfield, one_boolean_can_be_initialized_to_true) {
  constexpr uint32_t flags = 1;

  ASSERT_EQ(getBooleanData(flags, 0), true);
  static_assert(
      getBooleanData(flags, 0) == true,
      "first boolean member must be initialized to true");
}

TEST(NumericBitfield, one_boolean_can_be_set_to_true) {
  uint32_t flags = 0;

  setBooleanData(flags, 0, true);
  ASSERT_EQ(getBooleanData(flags, 0), true);
}

TEST(NumericBitfield, second_boolean_defaults_to_false) {
  constexpr uint32_t flags = 0;

  ASSERT_EQ(getBooleanData(flags, 1), false);
  static_assert(
      getBooleanData(flags, 1) == false,
      "second boolean member must default to false");
}

TEST(NumericBitfield, second_boolean_can_be_initialized_to_true) {
  constexpr uint32_t flags = 2;

  ASSERT_EQ(getBooleanData(flags, 0), false);
  ASSERT_EQ(getBooleanData(flags, 1), true);
  static_assert(
      getBooleanData(flags, 0) == false,
      "first boolean member must default to false");
  static_assert(
      getBooleanData(flags, 1) == true,
      "second boolean member must be initialized to true");
}

TEST(NumericBitfield, second_boolean_can_be_set_to_true) {
  uint32_t flags = 0;

  setBooleanData(flags, 1, true);
  ASSERT_EQ(getBooleanData(flags, 0), false);
  ASSERT_EQ(getBooleanData(flags, 1), true);
}

TEST(NumericBitfield, third_boolean_defaults_to_false) {
  constexpr uint32_t flags = 0;

  ASSERT_EQ(getBooleanData(flags, 2), false);
  static_assert(
      getBooleanData(flags, 2) == false,
      "second boolean member must default to false");
}

TEST(NumericBitfield, third_boolean_can_be_initialized_to_true) {
  constexpr uint32_t flags = 4;

  ASSERT_EQ(getBooleanData(flags, 0), false);
  ASSERT_EQ(getBooleanData(flags, 1), false);
  ASSERT_EQ(getBooleanData(flags, 2), true);
  static_assert(
      getBooleanData(flags, 0) == false,
      "first boolean member must default to false");
  static_assert(
      getBooleanData(flags, 1) == false,
      "second boolean member must default to false");
  static_assert(
      getBooleanData(flags, 2) == true,
      "second boolean member must be initialized to true");
}

TEST(NumericBitfield, third_boolean_can_be_set_to_true) {
  uint32_t flags = 0;

  setBooleanData(flags, 2, true);
  ASSERT_EQ(getBooleanData(flags, 0), false);
  ASSERT_EQ(getBooleanData(flags, 1), false);
  ASSERT_EQ(getBooleanData(flags, 2), true);
}

TEST(NumericBitfield, setting_boolean_values_does_not_spill_over) {
  uint32_t flags = 0;

  setBooleanData(flags, 1, (bool)7);

  ASSERT_EQ(getBooleanData(flags, 0), false);
  ASSERT_EQ(getBooleanData(flags, 1), true);
  ASSERT_EQ(getBooleanData(flags, 2), false);
}

TEST(NumericBitfield, first_enum_defaults_to_0) {
  constexpr uint32_t flags = 0;

  ASSERT_EQ(getEnumData<YGAlign>(flags, 0), YGAlignAuto);
  static_assert(
      getEnumData<YGAlign>(flags, 0) == YGAlignAuto,
      "first enum member must default to 0");
}

TEST(NumericBitfield, first_enum_can_be_set) {
  uint32_t flags = 0;

  setEnumData<YGAlign>(flags, 0, YGAlignSpaceBetween);

  ASSERT_EQ(getEnumData<YGAlign>(flags, 0), YGAlignSpaceBetween);
}

TEST(NumericBitfield, second_enum_defaults_to_0) {
  constexpr uint32_t flags = 0;
  static constexpr size_t alignOffset = 0;
  static constexpr size_t edgeOffset = 3;

  ASSERT_EQ(getEnumData<YGAlign>(flags, alignOffset), YGAlignAuto);
  ASSERT_EQ(getEnumData<YGEdge>(flags, edgeOffset), YGEdgeLeft);
  static_assert(
      getEnumData<YGAlign>(flags, alignOffset) == YGAlignAuto,
      "first enum member must default to 0");
  static_assert(
      getEnumData<YGEdge>(flags, edgeOffset) == YGEdgeLeft,
      "second enum member must default to 0");
}

TEST(NumericBitfield, second_enum_can_be_set) {
  uint32_t flags = 0;
  static constexpr size_t alignOffset = 0;
  static constexpr size_t edgeOffset = 3;

  setEnumData<YGEdge>(flags, edgeOffset, YGEdgeAll);

  ASSERT_EQ(getEnumData<YGAlign>(flags, alignOffset), YGAlignAuto);
  ASSERT_EQ(getEnumData<YGEdge>(flags, edgeOffset), YGEdgeAll);
}

TEST(NumericBitfield, third_enum_defaults_to_0) {
  constexpr uint32_t flags = 0;
  static constexpr size_t alignOffset = 0;
  static constexpr size_t boolOffset = 3;
  static constexpr size_t edgesOffset = 4;

  ASSERT_EQ(getEnumData<YGAlign>(flags, alignOffset), YGAlignAuto);
  ASSERT_EQ(getBooleanData(flags, boolOffset), false);
  ASSERT_EQ(getEnumData<YGEdge>(flags, edgesOffset), YGEdgeLeft);
  static_assert(
      getEnumData<YGAlign>(flags, alignOffset) == YGAlignAuto,
      "first enum member must default to 0");
  static_assert(
      getBooleanData(flags, boolOffset) == false,
      "middle boolean member must default to false");
  static_assert(
      getEnumData<YGEdge>(flags, edgesOffset) == YGEdgeLeft,
      "last enum member must default to 0");
}

TEST(NumericBitfield, third_enum_can_be_set) {
  uint32_t flags = 0;
  static constexpr size_t alignOffset = 0;
  static constexpr size_t boolOffset = 3;
  static constexpr size_t edgesOffset = 4;

  setEnumData<YGEdge>(flags, edgesOffset, YGEdgeVertical);

  ASSERT_EQ(getEnumData<YGAlign>(flags, alignOffset), YGAlignAuto);
  ASSERT_EQ(getBooleanData(flags, boolOffset), false);
  ASSERT_EQ(getEnumData<YGEdge>(flags, edgesOffset), YGEdgeVertical);
}

TEST(NumericBitfield, setting_values_does_not_spill_over) {
  uint32_t flags = 0;
  static constexpr size_t alignOffset = 0;
  static constexpr size_t edgesOffset = 4;
  static constexpr size_t boolOffset = 8;

  uint32_t edge = 0xffffff;
  setEnumData<YGEdge>(flags, edgesOffset, (YGEdge)edge);

  ASSERT_EQ(getEnumData<YGAlign>(flags, alignOffset), 0);
  ASSERT_EQ(getBooleanData(flags, boolOffset), false);
  ASSERT_EQ(getEnumData<YGEdge>(flags, edgesOffset), 0xf);
}

} // namespace facebook::yoga
