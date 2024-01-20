/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>
#include <yoga/style/StyleValuePool.h>

namespace facebook::yoga {

TEST(StyleValuePool, undefined_at_init) {
  StyleValuePool pool;
  StyleValueHandle handle;

  EXPECT_TRUE(handle.isUndefined());
  EXPECT_FALSE(handle.isDefined());
  EXPECT_EQ(pool.getLength(handle), value::undefined());
  EXPECT_EQ(pool.getNumber(handle), FloatOptional{});
}

TEST(StyleValuePool, auto_at_init) {
  StyleValuePool pool;
  auto handle = StyleValueHandle::ofAuto();

  EXPECT_TRUE(handle.isAuto());
  EXPECT_EQ(pool.getLength(handle), value::ofAuto());
}

TEST(StyleValuePool, store_small_int_points) {
  StyleValuePool pool;
  StyleValueHandle handle;

  pool.store(handle, value::points(10));

  EXPECT_EQ(pool.getLength(handle), value::points(10));
}

TEST(StyleValuePool, store_small_negative_int_points) {
  StyleValuePool pool;
  StyleValueHandle handle;

  pool.store(handle, value::points(-10));

  EXPECT_EQ(pool.getLength(handle), value::points(-10));
}

TEST(StyleValuePool, store_small_int_percent) {
  StyleValuePool pool;
  StyleValueHandle handle;

  pool.store(handle, value::percent(10));

  EXPECT_EQ(pool.getLength(handle), value::percent(10));
}

TEST(StyleValuePool, store_large_int_percent) {
  StyleValuePool pool;
  StyleValueHandle handle;

  pool.store(handle, value::percent(262144));

  EXPECT_EQ(pool.getLength(handle), value::percent(262144));
}

TEST(StyleValuePool, store_large_int_after_small_int) {
  StyleValuePool pool;
  StyleValueHandle handle;

  pool.store(handle, value::percent(10));
  pool.store(handle, value::percent(262144));

  EXPECT_EQ(pool.getLength(handle), value::percent(262144));
}

TEST(StyleValuePool, store_small_int_after_large_int) {
  StyleValuePool pool;
  StyleValueHandle handle;

  pool.store(handle, value::percent(262144));
  pool.store(handle, value::percent(10));

  EXPECT_EQ(pool.getLength(handle), value::percent(10));
}

TEST(StyleValuePool, store_small_int_number) {
  StyleValuePool pool;
  StyleValueHandle handle;

  pool.store(handle, FloatOptional{10.0f});

  EXPECT_EQ(pool.getNumber(handle), FloatOptional{10.0f});
}

TEST(StyleValuePool, store_undefined) {
  StyleValuePool pool;
  StyleValueHandle handle;

  pool.store(handle, value::undefined());

  EXPECT_TRUE(handle.isUndefined());
  EXPECT_FALSE(handle.isDefined());
  EXPECT_EQ(pool.getLength(handle), value::undefined());
}

TEST(StyleValuePool, store_undefined_after_small_int) {
  StyleValuePool pool;
  StyleValueHandle handle;

  pool.store(handle, value::points(10));
  pool.store(handle, value::undefined());

  EXPECT_TRUE(handle.isUndefined());
  EXPECT_FALSE(handle.isDefined());
  EXPECT_EQ(pool.getLength(handle), value::undefined());
}

TEST(StyleValuePool, store_undefined_after_large_int) {
  StyleValuePool pool;
  StyleValueHandle handle;

  pool.store(handle, value::points(262144));
  pool.store(handle, value::undefined());

  EXPECT_TRUE(handle.isUndefined());
  EXPECT_FALSE(handle.isDefined());
  EXPECT_EQ(pool.getLength(handle), value::undefined());
}

} // namespace facebook::yoga
