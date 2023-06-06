/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
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
