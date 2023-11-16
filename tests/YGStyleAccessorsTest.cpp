/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>
#include <yoga/Yoga.h>
#include <yoga/style/Style.h>
#include <cstdint>
#include <type_traits>

#define ACCESSOR_TESTS_1(NAME, X) \
  style.NAME() = X;               \
  ASSERT_EQ(style.NAME(), X);
#define ACCESSOR_TESTS_2(NAME, X, ...) \
  ACCESSOR_TESTS_1(NAME, X);           \
  ACCESSOR_TESTS_1(NAME, __VA_ARGS__);
#define ACCESSOR_TESTS_3(NAME, X, ...) \
  ACCESSOR_TESTS_1(NAME, X);           \
  ACCESSOR_TESTS_2(NAME, __VA_ARGS__);
#define ACCESSOR_TESTS_4(NAME, X, ...) \
  ACCESSOR_TESTS_1(NAME, X);           \
  ACCESSOR_TESTS_3(NAME, __VA_ARGS__);
#define ACCESSOR_TESTS_5(NAME, X, ...) \
  ACCESSOR_TESTS_1(NAME, X);           \
  ACCESSOR_TESTS_4(NAME, __VA_ARGS__)

#define ACCESSOR_TESTS_N(a, b, c, d, e, COUNT, ...) ACCESSOR_TESTS_##COUNT
#define ACCESSOR_TESTS(...) ACCESSOR_TESTS_N(__VA_ARGS__, 5, 4, 3, 2, 1)

#define INDEX_ACCESSOR_TESTS_1(NAME, IDX, X)                          \
  {                                                                   \
    auto style = Style{};                                             \
    style.NAME()[IDX] = X;                                            \
    ASSERT_EQ(style.NAME()[IDX], X);                                  \
    auto asArray = decltype(std::declval<const Style&>().NAME()){X};  \
    style.NAME() = asArray;                                           \
    ASSERT_EQ(static_cast<decltype(asArray)>(style.NAME()), asArray); \
  }

#define INDEX_ACCESSOR_TESTS_2(NAME, IDX, X, Y) \
  INDEX_ACCESSOR_TESTS_1(NAME, IDX, X)          \
  INDEX_ACCESSOR_TESTS_1(NAME, IDX, Y)

#define INDEX_ACCESSOR_TESTS_3(NAME, IDX, X, ...) \
  INDEX_ACCESSOR_TESTS_1(NAME, IDX, X)            \
  INDEX_ACCESSOR_TESTS_2(NAME, IDX, __VA_ARGS__)

#define INDEX_ACCESSOR_TESTS_4(NAME, IDX, X, ...) \
  INDEX_ACCESSOR_TESTS_1(NAME, IDX, X)            \
  INDEX_ACCESSOR_TESTS_3(NAME, IDX, __VA_ARGS__)

#define INDEX_ACCESSOR_TESTS_5(NAME, IDX, X, ...) \
  INDEX_ACCESSOR_TESTS_1(NAME, IDX, X)            \
  INDEX_ACCESSOR_TESTS_4(NAME, IDX, __VA_ARGS__)

#define INDEX_ACCESSOR_TESTS_N(a, b, c, d, e, COUNT, ...) \
  INDEX_ACCESSOR_TESTS_##COUNT
#define INDEX_ACCESSOR_TESTS(...) \
  INDEX_ACCESSOR_TESTS_N(__VA_ARGS__, 5, 4, 3, 2, 1)

// test macro for up to 5 values. If more are needed, extend the macros above.
#define ACCESSOR_TEST(NAME, DEFAULT_VAL, ...)      \
  TEST(Style, style_##NAME##_access) {             \
    auto style = Style{};                          \
    ASSERT_EQ(style.NAME(), DEFAULT_VAL);          \
    ACCESSOR_TESTS(__VA_ARGS__)(NAME, __VA_ARGS__) \
  }

#define INDEX_ACCESSOR_TEST(NAME, DEFAULT_VAL, IDX, ...)      \
  TEST(Style, style_##NAME##_access) {                        \
    ASSERT_EQ(Style{}.NAME()[IDX], DEFAULT_VAL);              \
    INDEX_ACCESSOR_TESTS(__VA_ARGS__)(NAME, IDX, __VA_ARGS__) \
  }

namespace facebook::yoga {

// TODO: MSVC doesn't like the macros
#ifndef _MSC_VER

ACCESSOR_TEST(
    direction,
    Direction::Inherit,
    Direction::LTR,
    Direction::RTL,
    Direction::Inherit);

ACCESSOR_TEST(
    flexDirection,
    FlexDirection::Column,
    FlexDirection::ColumnReverse,
    FlexDirection::RowReverse,
    FlexDirection::Row)

ACCESSOR_TEST(
    justifyContent,
    Justify::FlexStart,
    Justify::FlexEnd,
    Justify::SpaceAround,
    Justify::FlexStart,
    Justify::SpaceEvenly)

ACCESSOR_TEST(
    alignContent,
    Align::FlexStart,
    Align::Auto,
    Align::FlexStart,
    Align::Center,
    Align::FlexEnd,
    Align::Stretch)

ACCESSOR_TEST(
    alignItems,
    Align::Stretch,
    Align::FlexStart,
    Align::FlexEnd,
    Align::Baseline,
    Align::SpaceBetween,
    Align::SpaceAround)

ACCESSOR_TEST(
    alignSelf,
    Align::Auto,
    Align::FlexStart,
    Align::Center,
    Align::Auto,
    Align::FlexEnd,
    Align::Stretch)

ACCESSOR_TEST(
    positionType,
    PositionType::Static,
    PositionType::Absolute,
    PositionType::Relative)

ACCESSOR_TEST(flexWrap, Wrap::NoWrap, Wrap::Wrap, Wrap::WrapReverse)

ACCESSOR_TEST(overflow, Overflow::Visible, Overflow::Hidden, Overflow::Scroll)

ACCESSOR_TEST(display, Display::Flex, Display::None, Display::Flex)

ACCESSOR_TEST(
    flex,
    FloatOptional{},
    FloatOptional{123.45f},
    FloatOptional{-9.87f},
    FloatOptional{})

ACCESSOR_TEST(
    flexGrow,
    FloatOptional{},
    FloatOptional{123.45f},
    FloatOptional{-9.87f},
    FloatOptional{})

ACCESSOR_TEST(
    flexShrink,
    FloatOptional{},
    FloatOptional{123.45f},
    FloatOptional{-9.87f},
    FloatOptional{})

ACCESSOR_TEST(
    flexBasis,
    CompactValue::ofAuto(),
    CompactValue::ofUndefined(),
    CompactValue::ofAuto(),
    CompactValue::of<YGUnitPoint>(7777.77f),
    CompactValue::of<YGUnitPercent>(-100.0f))

INDEX_ACCESSOR_TEST(
    position,
    CompactValue::ofUndefined(),
    YGEdgeBottom,
    CompactValue::ofAuto(),
    CompactValue::ofUndefined(),
    CompactValue::of<YGUnitPoint>(7777.77f),
    CompactValue::of<YGUnitPercent>(-100.0f))

INDEX_ACCESSOR_TEST(
    margin,
    CompactValue::ofUndefined(),
    YGEdgeTop,
    CompactValue::ofAuto(),
    CompactValue::ofUndefined(),
    CompactValue::of<YGUnitPoint>(7777.77f),
    CompactValue::of<YGUnitPercent>(-100.0f))

INDEX_ACCESSOR_TEST(
    padding,
    CompactValue::ofUndefined(),
    YGEdgeAll,
    CompactValue::of<YGUnitPoint>(7777.77f),
    CompactValue::ofUndefined(),
    CompactValue::of<YGUnitPercent>(-100.0f))

INDEX_ACCESSOR_TEST(
    border,
    CompactValue::ofUndefined(),
    YGEdgeHorizontal,
    CompactValue::of<YGUnitPoint>(-7777.77f),
    CompactValue::ofUndefined())

ACCESSOR_TEST(
    aspectRatio,
    FloatOptional{},
    FloatOptional{-123.45f},
    FloatOptional{9876.5f},
    FloatOptional{0.0f},
    FloatOptional{});

#endif

} // namespace facebook::yoga
