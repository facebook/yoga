/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>

#include <yoga/YGValue.h>

TEST(YGValue, supports_equality) {
  ASSERT_EQ((YGValue{12.5f, YGUnitPercent}), (YGValue{12.5f, YGUnitPercent}));
  ASSERT_NE((YGValue{12.5f, YGUnitPercent}), (YGValue{56.7f, YGUnitPercent}));
  ASSERT_NE((YGValue{12.5f, YGUnitPercent}), (YGValue{12.5f, YGUnitPoint}));
  ASSERT_NE((YGValue{12.5f, YGUnitPercent}), (YGValue{12.5f, YGUnitAuto}));
  ASSERT_NE((YGValue{12.5f, YGUnitPercent}), (YGValue{12.5f, YGUnitUndefined}));

  ASSERT_EQ(
      (YGValue{12.5f, YGUnitUndefined}),
      (YGValue{YGUndefined, YGUnitUndefined}));
  ASSERT_EQ((YGValue{0, YGUnitAuto}), (YGValue{-1, YGUnitAuto}));
}

using namespace facebook::yoga::literals;

TEST(YGValue, supports_double_point_literals) {
  ASSERT_EQ(12.5_pt, (YGValue{12.5, YGUnitPoint}));
}

TEST(YGValue, supports_double_percent_literals) {
  ASSERT_EQ(12.5_percent, (YGValue{12.5, YGUnitPercent}));
}

TEST(YGValue, supports_integral_point_literals) {
  ASSERT_EQ(34_pt, (YGValue{34, YGUnitPoint}));
}

TEST(YGValue, supports_integral_percent_literals) {
  ASSERT_EQ(125_percent, (YGValue{125, YGUnitPercent}));
}

TEST(YGValue, supports_negative_point_literals) {
  ASSERT_EQ(-34.5_pt, (YGValue{-34.5, YGUnitPoint}));
}

TEST(YGValue, supports_negative_percent_literals) {
  ASSERT_EQ(-34.5_percent, (YGValue{-34.5, YGUnitPercent}));
}
