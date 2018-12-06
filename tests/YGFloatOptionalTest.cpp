/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the LICENSE
 * file in the root directory of this source tree.
 */
#include <yoga/YGFloatOptional.h>
#include <gtest/gtest.h>
#include <yoga/YGFloatOptional.h>
#include <yoga/Yoga.h>

constexpr auto empty = YGFloatOptional{};
constexpr auto zero = YGFloatOptional{0.0f};
constexpr auto one = YGFloatOptional{1.0f};
constexpr auto positive = YGFloatOptional{1234.5f};
constexpr auto negative = YGFloatOptional{-9876.5f};

TEST(YGFloatOptional, value) {
  ASSERT_EQ(zero.unwrap(), 0.0f);
  ASSERT_EQ(positive.unwrap(), 1234.5f);
  ASSERT_EQ(negative.unwrap(), -9876.5f);
  ASSERT_TRUE(YGFloatIsUndefined(empty.unwrap()));

  ASSERT_TRUE(empty.isUndefined());
  ASSERT_FALSE(zero.isUndefined());
  ASSERT_FALSE(negative.isUndefined());
}

TEST(YGFloatOptional, equality) {
  ASSERT_TRUE(empty == empty);
  ASSERT_TRUE(empty == YGUndefined);
  ASSERT_FALSE(empty == zero);
  ASSERT_FALSE(empty == negative);
  ASSERT_FALSE(empty == 12.3f);

  ASSERT_TRUE(zero == zero);
  ASSERT_TRUE(zero == 0.0f);
  ASSERT_FALSE(zero == positive);
  ASSERT_FALSE(zero == -5555.5f);

  ASSERT_TRUE(one == one);
  ASSERT_TRUE(one == 1.0f);
  ASSERT_FALSE(one == positive);

  ASSERT_TRUE(negative == negative);
  ASSERT_TRUE(negative == negative.unwrap());
  ASSERT_FALSE(negative == zero);
}

TEST(YGFloatOptional, inequality) {
  ASSERT_FALSE(empty != empty);
  ASSERT_FALSE(empty != YGUndefined);
  ASSERT_TRUE(empty != zero);
  ASSERT_TRUE(empty != negative);
  ASSERT_TRUE(empty != 12.3f);

  ASSERT_FALSE(zero != zero);
  ASSERT_FALSE(zero != 0.0f);
  ASSERT_TRUE(zero != positive);
  ASSERT_TRUE(zero != -5555.5f);

  ASSERT_FALSE(one != one);
  ASSERT_FALSE(one != 1.0f);
  ASSERT_TRUE(one != positive);

  ASSERT_FALSE(negative != negative);
  ASSERT_FALSE(negative != negative.unwrap());
  ASSERT_TRUE(negative != zero);
}

TEST(YGFloatOptional, greater) {
  ASSERT_FALSE(empty > empty);
  ASSERT_FALSE(empty > zero);
  ASSERT_FALSE(empty > one);
  ASSERT_FALSE(empty > positive);
  ASSERT_FALSE(empty > negative);
  ASSERT_FALSE(zero > empty);
  ASSERT_FALSE(one > empty);
  ASSERT_FALSE(positive > empty);
  ASSERT_FALSE(negative > empty);

  ASSERT_TRUE(zero > negative);
  ASSERT_FALSE(zero > zero);
  ASSERT_FALSE(zero > positive);
  ASSERT_FALSE(zero > one);

  ASSERT_TRUE(one > negative);
  ASSERT_TRUE(one > zero);
  ASSERT_FALSE(one > empty);
  ASSERT_FALSE(one > positive);

  ASSERT_TRUE(negative > YGFloatOptional{-INFINITY});
  ASSERT_FALSE(negative > empty);
}

TEST(YGFloatOptional, lower) {
  ASSERT_FALSE(empty < empty);
  ASSERT_FALSE(empty < zero);
  ASSERT_FALSE(empty < one);
  ASSERT_FALSE(empty < positive);
  ASSERT_FALSE(empty < negative);
  ASSERT_FALSE(zero < empty);
  ASSERT_FALSE(one < empty);
  ASSERT_FALSE(positive < empty);
  ASSERT_FALSE(negative < empty);

  ASSERT_TRUE(negative < zero);
  ASSERT_FALSE(zero < zero);
  ASSERT_FALSE(positive < zero);
  ASSERT_FALSE(one < zero);

  ASSERT_TRUE(negative < one);
  ASSERT_TRUE(zero < one);
  ASSERT_FALSE(empty < one);
  ASSERT_FALSE(positive < one);

  ASSERT_TRUE(YGFloatOptional{-INFINITY} < negative);
  ASSERT_FALSE(empty < negative);
}

TEST(YGFloatOptional, greater_equals) {
  ASSERT_TRUE(empty >= empty);
  ASSERT_FALSE(empty >= zero);
  ASSERT_FALSE(empty >= one);
  ASSERT_FALSE(empty >= positive);
  ASSERT_FALSE(empty >= negative);

  ASSERT_TRUE(zero >= negative);
  ASSERT_TRUE(zero >= zero);
  ASSERT_FALSE(zero >= positive);
  ASSERT_FALSE(zero >= one);

  ASSERT_TRUE(one >= negative);
  ASSERT_TRUE(one >= zero);
  ASSERT_FALSE(one >= empty);
  ASSERT_FALSE(one >= positive);

  ASSERT_TRUE(negative >= YGFloatOptional{-INFINITY});
  ASSERT_TRUE(negative >= negative);
  ASSERT_FALSE(negative >= empty);
}

TEST(YGFloatOptional, lower_equals) {
  ASSERT_TRUE(empty <= empty);
  ASSERT_FALSE(zero <= empty);
  ASSERT_FALSE(one <= empty);
  ASSERT_FALSE(positive <= empty);
  ASSERT_FALSE(negative <= empty);

  ASSERT_TRUE(negative <= zero);
  ASSERT_TRUE(zero <= zero);
  ASSERT_FALSE(positive <= zero);
  ASSERT_FALSE(one <= zero);

  ASSERT_TRUE(negative <= one);
  ASSERT_TRUE(zero <= one);
  ASSERT_FALSE(empty <= one);
  ASSERT_FALSE(positive <= one);

  ASSERT_TRUE(YGFloatOptional{-INFINITY} <= negative);
  ASSERT_TRUE(negative <= negative);
  ASSERT_FALSE(empty <= negative);
}

TEST(YGFloatOptional, addition) {
  ASSERT_EQ(zero + one, one);
  ASSERT_EQ(
      negative + positive,
      YGFloatOptional{negative.unwrap() + positive.unwrap()});
  ASSERT_EQ(empty + zero, empty);
  ASSERT_EQ(empty + empty, empty);
  ASSERT_EQ(negative + empty, empty);
}

TEST(YGFloatOptional, subtraction) {
  ASSERT_EQ(zero - one, YGFloatOptional{-1.0f});
  ASSERT_EQ(
      negative - positive,
      YGFloatOptional{negative.unwrap() - positive.unwrap()});
  ASSERT_EQ(empty - zero, empty);
  ASSERT_EQ(empty - empty, empty);
  ASSERT_EQ(negative - empty, empty);
}

TEST(YGFloatOptional, unary_minus) {
  ASSERT_EQ(-zero, zero);
  ASSERT_EQ(-negative, YGFloatOptional{-negative.unwrap()});
  ASSERT_EQ(-positive, YGFloatOptional{-positive.unwrap()});
  ASSERT_EQ(-empty, empty);
}

TEST(YGFloatOptional, orElse) {
  ASSERT_EQ(empty.orElse(1.23f), 1.23f);
  ASSERT_TRUE(YGFloatIsUndefined(empty.orElse(YGUndefined)));
  ASSERT_EQ(one.orElse(1.23f), 1.0f);
}

TEST(YGFloatOptional, orElseGet) {
  auto x = empty.orElseGet([] { return 1.23f; });
  ASSERT_EQ(x, 1.23f);
  ASSERT_TRUE(YGFloatIsUndefined(empty.orElseGet([] { return YGUndefined; })));

  auto y = one.orElseGet([] { return 1.23f; });
  ASSERT_EQ(y, 1.0f);
}
