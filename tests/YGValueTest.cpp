/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>

#include <yoga/YGValue.h>

TEST(YGValue, supports_equality) {
  ASSERT_EQ((YGValue{12.5, YGUnitPercent}), (YGValue{12.5, YGUnitPercent}));
  ASSERT_NE((YGValue{12.5, YGUnitPercent}), (YGValue{56.7, YGUnitPercent}));
  ASSERT_NE((YGValue{12.5, YGUnitPercent}), (YGValue{12.5, YGUnitPoint}));
  ASSERT_NE((YGValue{12.5, YGUnitPercent}), (YGValue{12.5, YGUnitAuto}));
  ASSERT_NE((YGValue{12.5, YGUnitPercent}), (YGValue{12.5, YGUnitUndefined}));

  ASSERT_EQ(
      (YGValue{12.5, YGUnitUndefined}),
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
