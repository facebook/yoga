/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>

#include <cstdint>
#include <yoga/Bitfield.h>

namespace facebook {
namespace yoga {

TEST(Bitfield, one_boolean_defaults_to_false) {
  constexpr auto bf = Bitfield<uint8_t, bool>{};

  ASSERT_EQ(bf.at<0>(), false);
  static_assert(
      bf.at<0>() == false, "first boolean member must default to false");
}

TEST(Bitfield, one_boolean_can_be_initialized_to_true) {
  constexpr auto bf = Bitfield<uint8_t, bool>{true};

  ASSERT_EQ(bf.at<0>(), true);
  static_assert(
      bf.at<0>() == true, "first boolean member must be initialized to true");
}

TEST(Bitfield, one_boolean_can_be_set_to_true) {
  auto bf = Bitfield<uint8_t, bool>{};

  bf.at<0>() = true;
  ASSERT_EQ(bf.at<0>(), true);
}

TEST(Bitfield, second_boolean_defaults_to_false) {
  constexpr auto bf = Bitfield<uint8_t, bool, bool>{};

  ASSERT_EQ(bf.at<1>(), false);
  static_assert(
      bf.at<1>() == false, "second boolean member must default to false");
}

TEST(Bitfield, second_boolean_can_be_initialized_to_true) {
  constexpr auto bf = Bitfield<uint8_t, bool, bool>{false, true};

  ASSERT_EQ(bf.at<0>(), false);
  ASSERT_EQ(bf.at<1>(), true);
  static_assert(
      bf.at<0>() == false, "first boolean member must default to false");
  static_assert(
      bf.at<1>() == true, "second boolean member must be initialized to true");
}

TEST(Bitfield, second_boolean_can_be_set_to_true) {
  auto bf = Bitfield<uint8_t, bool, bool>{};

  bf.at<1>() = true;
  ASSERT_EQ(bf.at<0>(), false);
  ASSERT_EQ(bf.at<1>(), true);
}

TEST(Bitfield, third_boolean_defaults_to_false) {
  constexpr auto bf = Bitfield<uint8_t, bool, bool, bool>{};

  ASSERT_EQ(bf.at<2>(), false);
  static_assert(
      bf.at<2>() == false, "second boolean member must default to false");
}

TEST(Bitfield, third_boolean_can_be_initialized_to_true) {
  constexpr auto bf = Bitfield<uint8_t, bool, bool, bool>{false, false, true};

  ASSERT_EQ(bf.at<0>(), false);
  ASSERT_EQ(bf.at<1>(), false);
  ASSERT_EQ(bf.at<2>(), true);
  static_assert(
      bf.at<0>() == false, "first boolean member must default to false");
  static_assert(
      bf.at<1>() == false, "second boolean member must default to false");
  static_assert(
      bf.at<2>() == true, "second boolean member must be initialized to true");
}

TEST(Bitfield, third_boolean_can_be_set_to_true) {
  auto bf = Bitfield<uint8_t, bool, bool, bool>{};

  bf.at<2>() = true;
  ASSERT_EQ(bf.at<0>(), false);
  ASSERT_EQ(bf.at<1>(), false);
  ASSERT_EQ(bf.at<2>(), true);
}

TEST(Bitfield, initializing_boolean_values_does_not_spill_over) {
  constexpr auto bf =
      Bitfield<uint8_t, bool, bool, bool>{false, (bool) 7, false};

  ASSERT_EQ(bf.at<0>(), false);
  ASSERT_EQ(bf.at<1>(), true);
  ASSERT_EQ(bf.at<2>(), false);
  static_assert(
      bf.at<0>() == false, "first boolean member must be initialized to false");
  static_assert(
      bf.at<1>() == true, "second boolean member must be initialized to true");
  static_assert(
      bf.at<2>() == false, "third boolean member must be initialized to false");
}

TEST(Bitfield, setting_boolean_values_does_not_spill_over) {
  auto bf = Bitfield<uint8_t, bool, bool, bool>{};

  bf.at<1>() = (bool) 7;

  ASSERT_EQ(bf.at<0>(), false);
  ASSERT_EQ(bf.at<1>(), true);
  ASSERT_EQ(bf.at<2>(), false);
}

TEST(Bitfield, first_enum_defaults_to_0) {
  constexpr auto bf = Bitfield<uint8_t, YGAlign>{};

  ASSERT_EQ(bf.at<0>(), YGAlignAuto);
  static_assert(
      bf.at<0>() == YGAlignAuto, "first enum member must default to 0");
}

TEST(Bitfield, first_enum_can_be_initialized) {
  constexpr auto bf = Bitfield<uint8_t, YGAlign>{YGAlignFlexEnd};

  ASSERT_EQ(bf.at<0>(), YGAlignFlexEnd);
  static_assert(
      bf.at<0>() == YGAlignFlexEnd,
      "first enum member must be initialized to YGAlignFlexEnd");
}

TEST(Bitfield, first_enum_can_be_set) {
  auto bf = Bitfield<uint8_t, YGAlign>{};

  bf.at<0>() = YGAlignSpaceBetween;

  ASSERT_EQ(bf.at<0>(), YGAlignSpaceBetween);
}

TEST(Bitfield, second_enum_defaults_to_0) {
  constexpr auto bf = Bitfield<uint8_t, YGAlign, YGEdge>{};

  ASSERT_EQ(bf.at<0>(), YGAlignAuto);
  ASSERT_EQ(bf.at<1>(), YGEdgeLeft);
  static_assert(
      bf.at<0>() == YGAlignAuto, "first enum member must default to 0");
  static_assert(
      bf.at<1>() == YGEdgeLeft, "second enum member must default to 0");
}

TEST(Bitfield, second_enum_can_be_initialized) {
  constexpr auto bf =
      Bitfield<uint8_t, YGAlign, YGEdge>{YGAlignAuto, YGEdgeAll};

  ASSERT_EQ(bf.at<0>(), YGAlignAuto);
  ASSERT_EQ(bf.at<1>(), YGEdgeAll);
  static_assert(
      bf.at<0>() == YGAlignAuto, "first enum member must default to 0");
  static_assert(
      bf.at<1>() == YGEdgeAll,
      "second enum member must be initialized to YGEdgeAll");
}

TEST(Bitfield, second_enum_can_be_set) {
  auto bf = Bitfield<uint8_t, YGAlign, YGEdge>{};

  bf.at<1>() = YGEdgeAll;

  ASSERT_EQ(bf.at<0>(), YGAlignAuto);
  ASSERT_EQ(bf.at<1>(), YGEdgeAll);
}

TEST(Bitfield, third_enum_defaults_to_0) {
  constexpr auto bf = Bitfield<uint8_t, YGAlign, bool, YGEdge>{};

  ASSERT_EQ(bf.at<0>(), YGAlignAuto);
  ASSERT_EQ(bf.at<1>(), false);
  ASSERT_EQ(bf.at<2>(), YGEdgeLeft);
  static_assert(
      bf.at<0>() == YGAlignAuto, "first enum member must default to 0");
  static_assert(
      bf.at<1>() == false, "middle boolean member must default to false");
  static_assert(bf.at<2>() == YGEdgeLeft, "last enum member must default to 0");
}

TEST(Bitfield, third_enum_can_be_initialized) {
  constexpr auto bf = Bitfield<uint8_t, YGAlign, bool, YGEdge>{
      YGAlignAuto, false, YGEdgeVertical};

  ASSERT_EQ(bf.at<0>(), YGAlignAuto);
  ASSERT_EQ(bf.at<1>(), false);
  ASSERT_EQ(bf.at<2>(), YGEdgeVertical);
  static_assert(
      bf.at<0>() == YGAlignAuto, "first enum member must default to 0");
  static_assert(
      bf.at<1>() == false, "middle boolean member must default to false");
  static_assert(
      bf.at<2>() == YGEdgeVertical,
      "second enum member must be initialized to YGEdgeVertical");
}

TEST(Bitfield, third_enum_can_be_set) {
  auto bf = Bitfield<uint8_t, YGAlign, bool, YGEdge>{};

  bf.at<2>() = YGEdgeVertical;

  ASSERT_EQ(bf.at<0>(), YGAlignAuto);
  ASSERT_EQ(bf.at<1>(), false);
  ASSERT_EQ(bf.at<2>(), YGEdgeVertical);
}

TEST(Bitfield, initializing_values_does_not_spill_over) {
  constexpr auto bf = Bitfield<uint8_t, YGAlign, YGEdge, bool>{
      (YGAlign) 0, (YGEdge) 0xffffff, false};

  ASSERT_EQ(bf.at<0>(), (YGAlign) 0);
  ASSERT_EQ(bf.at<1>(), 0xf);
  ASSERT_EQ(bf.at<2>(), false);
  static_assert(bf.at<0>() == 0, "first enum member must be initialized to 0");
  static_assert(
      bf.at<1>() == 0xf, "second member must be initialized to YGEdgeVertical");
  static_assert(
      bf.at<2>() == false, "boolean member must be initialized to false");
}

TEST(Bitfield, setting_values_does_not_spill_over) {
  auto bf = Bitfield<uint8_t, YGAlign, YGEdge, bool>{};

  bf.at<1>() = (YGEdge) 0xffffff;

  ASSERT_EQ(bf.at<0>(), 0);
  ASSERT_EQ(bf.at<1>(), 0xf);
  ASSERT_EQ(bf.at<2>(), false);
}

} // namespace yoga
} // namespace facebook
