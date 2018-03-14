/**
 * Copyright (c) 2014-present, Facebook, Inc.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>
#include <yoga/Yoga.h>
#include <yoga/Yoga-internal.h>

TEST(YogaTest, rounding_value) {
  // Test that whole numbers are rounded to whole despite ceil/floor flags
  ASSERT_FLOAT_EQ(6.0, YGRoundValueToPixelGrid(6.000001, 2.0, false, false));
  ASSERT_FLOAT_EQ(6.0, YGRoundValueToPixelGrid(6.000001, 2.0, true, false));
  ASSERT_FLOAT_EQ(6.0, YGRoundValueToPixelGrid(6.000001, 2.0, false, true));
  ASSERT_FLOAT_EQ(6.0, YGRoundValueToPixelGrid(5.999999, 2.0, false, false));
  ASSERT_FLOAT_EQ(6.0, YGRoundValueToPixelGrid(5.999999, 2.0, true, false));
  ASSERT_FLOAT_EQ(6.0, YGRoundValueToPixelGrid(5.999999, 2.0, false, true));

  // Test with negative numbers
  ASSERT_FLOAT_EQ(-6.0, YGRoundValueToPixelGrid(-6.000001, 2.0, false, false));
  ASSERT_FLOAT_EQ(-6.0, YGRoundValueToPixelGrid(-6.000001, 2.0, true, false));
  ASSERT_FLOAT_EQ(-6.0, YGRoundValueToPixelGrid(-6.000001, 2.0, false, true));
  ASSERT_FLOAT_EQ(-6.0, YGRoundValueToPixelGrid(-5.999999, 2.0, false, false));
  ASSERT_FLOAT_EQ(-6.0, YGRoundValueToPixelGrid(-5.999999, 2.0, true, false));
  ASSERT_FLOAT_EQ(-6.0, YGRoundValueToPixelGrid(-5.999999, 2.0, false, true));

  // Test that numbers with fraction are rounded correctly accounting for ceil/floor flags
  ASSERT_FLOAT_EQ(6.0, YGRoundValueToPixelGrid(6.01, 2.0, false, false));
  ASSERT_FLOAT_EQ(6.5, YGRoundValueToPixelGrid(6.01, 2.0, true, false));
  ASSERT_FLOAT_EQ(6.0, YGRoundValueToPixelGrid(6.01, 2.0, false, true));
  ASSERT_FLOAT_EQ(6.0, YGRoundValueToPixelGrid(5.99, 2.0, false, false));
  ASSERT_FLOAT_EQ(6.0, YGRoundValueToPixelGrid(5.99, 2.0, true, false));
  ASSERT_FLOAT_EQ(5.5, YGRoundValueToPixelGrid(5.99, 2.0, false, true));
  ASSERT_FLOAT_EQ(6.0, YGRoundValueToPixelGrid(6.49, 1.0, false, false));
  ASSERT_FLOAT_EQ(7.0, YGRoundValueToPixelGrid(6.50, 1.0, false, false));
  ASSERT_FLOAT_EQ(7.0, YGRoundValueToPixelGrid(6.51, 1.0, false, false));
  ASSERT_FLOAT_EQ(7.0, YGRoundValueToPixelGrid(6.50, 1.0, true, false));
  ASSERT_FLOAT_EQ(6.0, YGRoundValueToPixelGrid(6.50, 1.0, false, true));

  // Test with negative numbers
  ASSERT_FLOAT_EQ(-6.0, YGRoundValueToPixelGrid(-6.01, 2.0, false, false));
  ASSERT_FLOAT_EQ(-6.0, YGRoundValueToPixelGrid(-6.01, 2.0, true, false));
  ASSERT_FLOAT_EQ(-6.5, YGRoundValueToPixelGrid(-6.01, 2.0, false, true));
  ASSERT_FLOAT_EQ(-6.0, YGRoundValueToPixelGrid(-5.99, 2.0, false, false));
  ASSERT_FLOAT_EQ(-5.5, YGRoundValueToPixelGrid(-5.99, 2.0, true, false));
  ASSERT_FLOAT_EQ(-6.0, YGRoundValueToPixelGrid(-5.99, 2.0, false, true));
  ASSERT_FLOAT_EQ(-6.0, YGRoundValueToPixelGrid(-6.49, 1.0, false, false));
  ASSERT_FLOAT_EQ(-6.0, YGRoundValueToPixelGrid(-6.50, 1.0, false, false));
  ASSERT_FLOAT_EQ(-7.0, YGRoundValueToPixelGrid(-6.51, 1.0, false, false));
  ASSERT_FLOAT_EQ(-6.0, YGRoundValueToPixelGrid(-6.50, 1.0, true, false));
  ASSERT_FLOAT_EQ(-7.0, YGRoundValueToPixelGrid(-6.50, 1.0, false, true));

  // Do a simple translation test to ensure that a distance between 2 values
  // stays consistent during an animation, even after rounding them.
  const int LAPS = 3;
  const int LAP_CLOSEST = 0;
  const int LAP_CEIL = 1;
  const int LAP_FLOOR = 2;
  for (int currentLap = LAP_CLOSEST; currentLap < LAPS; ++currentLap)
  {
    float left = -2.0f;
    float right = 2.0f;
    const float distance = right-left;
    float totalDistance = 1.1f;
    const float step = 0.01f;
    while (totalDistance >= 0.0f) {
      left += step;
      right += step;
      const float snappedLeft = YGRoundValueToPixelGrid(left, 1.0, currentLap==LAP_CEIL, currentLap==LAP_FLOOR);
      const float snappedRight = YGRoundValueToPixelGrid(right, 1.0, currentLap==LAP_CEIL, currentLap==LAP_FLOOR);
      ASSERT_FLOAT_EQ(distance, (snappedRight-snappedLeft));
      totalDistance -= step;
    }
  }
}
