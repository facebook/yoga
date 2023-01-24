/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <cstdint>
#include <type_traits>
#include <gtest/gtest.h>
#include <yoga/YGEnums.h>
#include <yoga/YGStyle.h>
#include <yoga/YGValue.h>

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

#define INDEX_ACCESSOR_TESTS_1(NAME, IDX, X)                           \
  {                                                                    \
    auto style = YGStyle{};                                            \
    style.NAME()[IDX] = X;                                             \
    ASSERT_EQ(style.NAME()[IDX], X);                                   \
    auto asArray = decltype(std::declval<const YGStyle&>().NAME()){X}; \
    style.NAME() = asArray;                                            \
    ASSERT_EQ(static_cast<decltype(asArray)>(style.NAME()), asArray);  \
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
  TEST(YGStyle, style_##NAME##_access) {           \
    auto style = YGStyle{};                        \
    ASSERT_EQ(style.NAME(), DEFAULT_VAL);          \
    ACCESSOR_TESTS(__VA_ARGS__)(NAME, __VA_ARGS__) \
  }

#define INDEX_ACCESSOR_TEST(NAME, DEFAULT_VAL, IDX, ...)      \
  TEST(YGStyle, style_##NAME##_access) {                      \
    ASSERT_EQ(YGStyle{}.NAME()[IDX], DEFAULT_VAL);            \
    INDEX_ACCESSOR_TESTS(__VA_ARGS__)(NAME, IDX, __VA_ARGS__) \
  }

namespace facebook {
namespace yoga {

using CompactValue = detail::CompactValue;

// TODO: MSVC doesn't like the macros
#ifndef _MSC_VER

ACCESSOR_TEST(
    direction,
    YGDirectionInherit,
    YGDirectionLTR,
    YGDirectionRTL,
    YGDirectionInherit);

ACCESSOR_TEST(
    flexDirection,
    YGFlexDirectionColumn,
    YGFlexDirectionColumnReverse,
    YGFlexDirectionRowReverse,
    YGFlexDirectionRow)

ACCESSOR_TEST(
    justifyContent,
    YGJustifyFlexStart,
    YGJustifyFlexEnd,
    YGJustifySpaceAround,
    YGJustifyFlexStart,
    YGJustifySpaceEvenly)

ACCESSOR_TEST(
    alignContent,
    YGAlignFlexStart,
    YGAlignAuto,
    YGAlignFlexStart,
    YGAlignCenter,
    YGAlignFlexEnd,
    YGAlignStretch)

ACCESSOR_TEST(
    alignItems,
    YGAlignStretch,
    YGAlignFlexStart,
    YGAlignFlexEnd,
    YGAlignBaseline,
    YGAlignSpaceBetween,
    YGAlignSpaceAround)

ACCESSOR_TEST(
    alignSelf,
    YGAlignAuto,
    YGAlignFlexStart,
    YGAlignCenter,
    YGAlignAuto,
    YGAlignFlexEnd,
    YGAlignStretch)

ACCESSOR_TEST(
    positionType,
    YGPositionTypeStatic,
    YGPositionTypeAbsolute,
    YGPositionTypeRelative,
    YGPositionTypeStatic)

ACCESSOR_TEST(
    flexWrap,
    YGWrapNoWrap,
    YGWrapWrap,
    YGWrapWrapReverse,
    YGWrapNoWrap)

ACCESSOR_TEST(
    overflow,
    YGOverflowVisible,
    YGOverflowHidden,
    YGOverflowScroll,
    YGOverflowVisible)

ACCESSOR_TEST(display, YGDisplayFlex, YGDisplayNone, YGDisplayFlex)

ACCESSOR_TEST(
    flex,
    YGFloatOptional{},
    YGFloatOptional{123.45f},
    YGFloatOptional{-9.87f},
    YGFloatOptional{})

ACCESSOR_TEST(
    flexGrow,
    YGFloatOptional{},
    YGFloatOptional{123.45f},
    YGFloatOptional{-9.87f},
    YGFloatOptional{})

ACCESSOR_TEST(
    flexShrink,
    YGFloatOptional{},
    YGFloatOptional{123.45f},
    YGFloatOptional{-9.87f},
    YGFloatOptional{})

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

INDEX_ACCESSOR_TEST(
    dimensions,
    CompactValue::ofAuto(),
    YGDimensionWidth,
    CompactValue::ofUndefined(),
    CompactValue::ofAuto(),
    CompactValue::of<YGUnitPoint>(7777.77f),
    CompactValue::of<YGUnitPercent>(-100.0f))

INDEX_ACCESSOR_TEST(
    minDimensions,
    CompactValue::ofUndefined(),
    YGDimensionHeight,
    CompactValue::ofAuto(),
    CompactValue::ofUndefined(),
    CompactValue::of<YGUnitPoint>(7777.77f),
    CompactValue::of<YGUnitPercent>(-100.0f))

INDEX_ACCESSOR_TEST(
    maxDimensions,
    CompactValue::ofUndefined(),
    YGDimensionHeight,
    CompactValue::ofAuto(),
    CompactValue::ofUndefined(),
    CompactValue::of<YGUnitPoint>(7777.77f),
    CompactValue::of<YGUnitPercent>(-100.0f))

ACCESSOR_TEST(
    aspectRatio,
    YGFloatOptional{},
    YGFloatOptional{-123.45f},
    YGFloatOptional{9876.5f},
    YGFloatOptional{0.0f},
    YGFloatOptional{});

#endif

} // namespace yoga
} // namespace facebook
