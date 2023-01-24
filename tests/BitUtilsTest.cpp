/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>

#include <cstdint>
#include <yoga/BitUtils.h>

namespace facebook {
namespace yoga {

TEST(BitUtils, one_boolean_defaults_to_false) {
  constexpr uint8_t flags = 0;

  ASSERT_EQ(detail::getBooleanData(flags, 0), false);
  static_assert(
      detail::getBooleanData(flags, 0) == false,
      "first boolean member must default to false");
}

TEST(BitUtils, one_boolean_can_be_initialized_to_true) {
  constexpr uint8_t flags = 1;

  ASSERT_EQ(detail::getBooleanData(flags, 0), true);
  static_assert(
      detail::getBooleanData(flags, 0) == true,
      "first boolean member must be initialized to true");
}

TEST(BitUtils, one_boolean_can_be_set_to_true) {
  uint8_t flags = 0;

  detail::setBooleanData(flags, 0, true);
  ASSERT_EQ(detail::getBooleanData(flags, 0), true);
}

TEST(BitUtils, second_boolean_defaults_to_false) {
  constexpr uint8_t flags = 0;

  ASSERT_EQ(detail::getBooleanData(flags, 1), false);
  static_assert(
      detail::getBooleanData(flags, 1) == false,
      "second boolean member must default to false");
}

TEST(BitUtils, second_boolean_can_be_initialized_to_true) {
  constexpr uint8_t flags = 2;

  ASSERT_EQ(detail::getBooleanData(flags, 0), false);
  ASSERT_EQ(detail::getBooleanData(flags, 1), true);
  static_assert(
      detail::getBooleanData(flags, 0) == false,
      "first boolean member must default to false");
  static_assert(
      detail::getBooleanData(flags, 1) == true,
      "second boolean member must be initialized to true");
}

TEST(BitUtils, second_boolean_can_be_set_to_true) {
  uint8_t flags = 0;

  detail::setBooleanData(flags, 1, true);
  ASSERT_EQ(detail::getBooleanData(flags, 0), false);
  ASSERT_EQ(detail::getBooleanData(flags, 1), true);
}

TEST(BitUtils, third_boolean_defaults_to_false) {
  constexpr uint8_t flags = 0;

  ASSERT_EQ(detail::getBooleanData(flags, 2), false);
  static_assert(
      detail::getBooleanData(flags, 2) == false,
      "second boolean member must default to false");
}

TEST(BitUtils, third_boolean_can_be_initialized_to_true) {
  constexpr uint8_t flags = 4;

  ASSERT_EQ(detail::getBooleanData(flags, 0), false);
  ASSERT_EQ(detail::getBooleanData(flags, 1), false);
  ASSERT_EQ(detail::getBooleanData(flags, 2), true);
  static_assert(
      detail::getBooleanData(flags, 0) == false,
      "first boolean member must default to false");
  static_assert(
      detail::getBooleanData(flags, 1) == false,
      "second boolean member must default to false");
  static_assert(
      detail::getBooleanData(flags, 2) == true,
      "second boolean member must be initialized to true");
}

TEST(BitUtils, third_boolean_can_be_set_to_true) {
  uint8_t flags = 0;

  detail::setBooleanData(flags, 2, true);
  ASSERT_EQ(detail::getBooleanData(flags, 0), false);
  ASSERT_EQ(detail::getBooleanData(flags, 1), false);
  ASSERT_EQ(detail::getBooleanData(flags, 2), true);
}

TEST(BitUtils, setting_boolean_values_does_not_spill_over) {
  uint8_t flags = 0;

  detail::setBooleanData(flags, 1, (bool) 7);

  ASSERT_EQ(detail::getBooleanData(flags, 0), false);
  ASSERT_EQ(detail::getBooleanData(flags, 1), true);
  ASSERT_EQ(detail::getBooleanData(flags, 2), false);
}

TEST(BitUtils, first_enum_defaults_to_0) {
  constexpr uint8_t flags = 0;

  ASSERT_EQ(detail::getEnumData<YGAlign>(flags, 0), YGAlignAuto);
  static_assert(
      detail::getEnumData<YGAlign>(flags, 0) == YGAlignAuto,
      "first enum member must default to 0");
}

TEST(BitUtils, first_enum_can_be_set) {
  uint8_t flags = 0;

  detail::setEnumData<YGAlign>(flags, 0, YGAlignSpaceBetween);

  ASSERT_EQ(detail::getEnumData<YGAlign>(flags, 0), YGAlignSpaceBetween);
}

TEST(BitUtils, second_enum_defaults_to_0) {
  constexpr uint8_t flags = 0;
  static constexpr size_t alignOffset = 0;
  static constexpr size_t edgeOffset = 3;

  ASSERT_EQ(detail::getEnumData<YGAlign>(flags, alignOffset), YGAlignAuto);
  ASSERT_EQ(detail::getEnumData<YGEdge>(flags, edgeOffset), YGEdgeLeft);
  static_assert(
      detail::getEnumData<YGAlign>(flags, alignOffset) == YGAlignAuto,
      "first enum member must default to 0");
  static_assert(
      detail::getEnumData<YGEdge>(flags, edgeOffset) == YGEdgeLeft,
      "second enum member must default to 0");
}

TEST(BitUtils, second_enum_can_be_set) {
  uint8_t flags = 0;
  static constexpr size_t alignOffset = 0;
  static constexpr size_t edgeOffset = 3;

  detail::setEnumData<YGEdge>(flags, edgeOffset, YGEdgeAll);

  ASSERT_EQ(detail::getEnumData<YGAlign>(flags, alignOffset), YGAlignAuto);
  ASSERT_EQ(detail::getEnumData<YGEdge>(flags, edgeOffset), YGEdgeAll);
}

TEST(BitUtils, third_enum_defaults_to_0) {
  constexpr uint8_t flags = 0;
  static constexpr size_t alignOffset = 0;
  static constexpr size_t boolOffset = 3;
  static constexpr size_t edgesOffset = 4;

  ASSERT_EQ(detail::getEnumData<YGAlign>(flags, alignOffset), YGAlignAuto);
  ASSERT_EQ(detail::getBooleanData(flags, boolOffset), false);
  ASSERT_EQ(detail::getEnumData<YGEdge>(flags, edgesOffset), YGEdgeLeft);
  static_assert(
      detail::getEnumData<YGAlign>(flags, alignOffset) == YGAlignAuto,
      "first enum member must default to 0");
  static_assert(
      detail::getBooleanData(flags, boolOffset) == false,
      "middle boolean member must default to false");
  static_assert(
      detail::getEnumData<YGEdge>(flags, edgesOffset) == YGEdgeLeft,
      "last enum member must default to 0");
}

TEST(BitUtils, third_enum_can_be_set) {
  uint8_t flags = 0;
  static constexpr size_t alignOffset = 0;
  static constexpr size_t boolOffset = 3;
  static constexpr size_t edgesOffset = 4;

  detail::setEnumData<YGEdge>(flags, edgesOffset, YGEdgeVertical);

  ASSERT_EQ(detail::getEnumData<YGAlign>(flags, alignOffset), YGAlignAuto);
  ASSERT_EQ(detail::getBooleanData(flags, boolOffset), false);
  ASSERT_EQ(detail::getEnumData<YGEdge>(flags, edgesOffset), YGEdgeVertical);
}

TEST(BitUtils, setting_values_does_not_spill_over) {
  uint8_t flags = 0;
  static constexpr size_t alignOffset = 0;
  static constexpr size_t edgesOffset = 3;
  static constexpr size_t boolOffset = 7;

  detail::setEnumData<YGEdge>(flags, edgesOffset, (YGEdge) 0xffffff);

  ASSERT_EQ(detail::getEnumData<YGAlign>(flags, alignOffset), 0);
  ASSERT_EQ(detail::getBooleanData(flags, boolOffset), false);
  ASSERT_EQ(detail::getEnumData<YGEdge>(flags, edgesOffset), 0xf);
}

} // namespace yoga
} // namespace facebook
