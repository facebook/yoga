/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>
#include <yoga/style/SmallValueBuffer.h>

namespace facebook::yoga {

constexpr size_t kBufferSize = 4;

TEST(SmallValueBuffer, copy_assignment_with_overflow) {
  std::array<uint16_t, kBufferSize + 1> handles;

  SmallValueBuffer<kBufferSize> buffer1;
  for (size_t i = 0; i < kBufferSize + 1; ++i) {
    handles[i] = buffer1.push(static_cast<uint32_t>(i));
  }

  SmallValueBuffer<kBufferSize> buffer2 = buffer1;
  for (size_t i = 0; i < kBufferSize + 1; ++i) {
    EXPECT_EQ(buffer2.get32(handles[i]), i);
  }

  auto handle = buffer1.push(42u);
  EXPECT_EQ(buffer1.get32(handle), 42);

  EXPECT_THROW({ buffer2.get32(handle); }, std::logic_error);
}

TEST(SmallValueBuffer, push_32) {
  uint32_t magic = 88567114u;

  SmallValueBuffer<kBufferSize> buffer;
  auto handle = buffer.push(magic);
  EXPECT_EQ(buffer.get32(handle), magic);
}

TEST(SmallValueBuffer, push_overflow) {
  uint32_t magic1 = 88567114u;
  uint32_t magic2 = 351012214u;
  uint32_t magic3 = 146122128u;
  uint32_t magic4 = 2171092154u;
  uint32_t magic5 = 2269016953u;

  SmallValueBuffer<kBufferSize> buffer;
  EXPECT_EQ(buffer.get32(buffer.push(magic1)), magic1);
  EXPECT_EQ(buffer.get32(buffer.push(magic2)), magic2);
  EXPECT_EQ(buffer.get32(buffer.push(magic3)), magic3);
  EXPECT_EQ(buffer.get32(buffer.push(magic4)), magic4);
  EXPECT_EQ(buffer.get32(buffer.push(magic5)), magic5);
}

TEST(SmallValueBuffer, push_64) {
  uint64_t magic = 118138934255546108ull;

  SmallValueBuffer<kBufferSize> buffer;
  auto handle = buffer.push(magic);
  EXPECT_EQ(buffer.get64(handle), magic);
}

TEST(SmallValueBuffer, push_64_overflow) {
  uint64_t magic1 = 1401612388342512ull;
  uint64_t magic2 = 118712305386210ull;
  uint64_t magic3 = 752431801563359011ull;
  uint64_t magic4 = 118138934255546108ull;
  uint64_t magic5 = 237115443124116111ull;

  SmallValueBuffer<kBufferSize> buffer;
  EXPECT_EQ(buffer.get64(buffer.push(magic1)), magic1);
  EXPECT_EQ(buffer.get64(buffer.push(magic2)), magic2);
  EXPECT_EQ(buffer.get64(buffer.push(magic3)), magic3);
  EXPECT_EQ(buffer.get64(buffer.push(magic4)), magic4);
  EXPECT_EQ(buffer.get64(buffer.push(magic5)), magic5);
}

TEST(SmallValueBuffer, push_64_after_32) {
  uint32_t magic32 = 88567114u;
  uint64_t magic64 = 118712305386210ull;

  SmallValueBuffer<kBufferSize> buffer;
  auto handle32 = buffer.push(magic32);
  EXPECT_EQ(buffer.get32(handle32), magic32);

  auto handle64 = buffer.push(magic64);
  EXPECT_EQ(buffer.get64(handle64), magic64);
}

TEST(SmallValueBuffer, push_32_after_64) {
  uint32_t magic32 = 88567114u;
  uint64_t magic64 = 118712305386210ull;

  SmallValueBuffer<kBufferSize> buffer;
  auto handle64 = buffer.push(magic64);
  EXPECT_EQ(buffer.get64(handle64), magic64);

  auto handle32 = buffer.push(magic32);
  EXPECT_EQ(buffer.get32(handle32), magic32);
}

TEST(SmallValueBuffer, replace_32_with_32) {
  uint32_t magic1 = 88567114u;
  uint32_t magic2 = 351012214u;

  SmallValueBuffer<kBufferSize> buffer;
  auto handle = buffer.push(magic1);

  EXPECT_EQ(buffer.get32(buffer.replace(handle, magic2)), magic2);
}

TEST(SmallValueBuffer, replace_32_with_64) {
  uint32_t magic32 = 88567114u;
  uint64_t magic64 = 118712305386210ull;

  SmallValueBuffer<kBufferSize> buffer;
  auto handle = buffer.push(magic32);

  EXPECT_EQ(buffer.get64(buffer.replace(handle, magic64)), magic64);
}

TEST(SmallValueBuffer, replace_32_with_64_causes_overflow) {
  uint32_t magic1 = 88567114u;
  uint32_t magic2 = 351012214u;
  uint32_t magic3 = 146122128u;
  uint32_t magic4 = 2171092154u;

  uint64_t magic64 = 118712305386210ull;

  SmallValueBuffer<kBufferSize> buffer;
  auto handle1 = buffer.push(magic1);
  buffer.push(magic2);
  buffer.push(magic3);
  buffer.push(magic4);

  EXPECT_EQ(buffer.get64(buffer.replace(handle1, magic64)), magic64);
}

TEST(SmallValueBuffer, replace_64_with_32) {
  uint32_t magic32 = 88567114u;
  uint64_t magic64 = 118712305386210ull;

  SmallValueBuffer<kBufferSize> buffer;
  auto handle = buffer.push(magic64);

  EXPECT_EQ(buffer.get32(buffer.replace(handle, magic32)), magic32);
}

TEST(SmallValueBuffer, replace_64_with_64) {
  uint64_t magic1 = 1401612388342512ull;
  uint64_t magic2 = 118712305386210ull;

  SmallValueBuffer<kBufferSize> buffer;
  auto handle = buffer.push(magic1);

  EXPECT_EQ(buffer.get64(buffer.replace(handle, magic2)), magic2);
}

} // namespace facebook::yoga
