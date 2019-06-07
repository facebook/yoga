/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the LICENSE
 * file in the root directory of this source tree.
 */
#include <cstdint>
#include <type_traits>
#include <gtest/gtest.h>
#include <yoga/YGEnums.h>
#include <yoga/YGStyle.h>
#include <yoga/YGValue.h>

#include <utility>

using AssignedProps =
    std::remove_reference<decltype(YGStyle{}.assignedProps())>::type;

namespace {
constexpr AssignedProps setBits(int from, int n) {
  return n > 0 ? (setBits(from, n - 1) | AssignedProps{1ull << (from + n - 1)})
               : 0;
}
} // namespace

#define ACCESSOR_TESTS_1(NAME, X) \
  style.NAME() = X;               \
  ASSERT_EQ(style.NAME(), X);     \
  ASSERT_EQ(style.assignedProps(), AssignedProps{1ull << YGStyle::NAME##Bit});
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
    ASSERT_EQ(                                                         \
        style.assignedProps(),                                         \
        AssignedProps{1ull << (YGStyle::NAME##Bit + IDX)});            \
    auto asArray = decltype(std::declval<const YGStyle&>().NAME()){X}; \
    style.NAME() = asArray;                                            \
    ASSERT_EQ(static_cast<decltype(asArray)>(style.NAME()), asArray);  \
    ASSERT_EQ(                                                         \
        style.assignedProps(),                                         \
        AssignedProps{setBits(                                         \
            YGStyle::NAME##Bit,                                        \
            facebook::yoga::enums::count<decltype(IDX)>())});          \
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
    ASSERT_EQ(YGStyle{}.assignedProps(), 0);                  \
    INDEX_ACCESSOR_TESTS(__VA_ARGS__)(NAME, IDX, __VA_ARGS__) \
  }

namespace facebook {
namespace yoga {

using CompactValue = detail::CompactValue;

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
    YGPositionTypeRelative,
    YGPositionTypeAbsolute,
    YGPositionTypeRelative)

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

TEST(YGStyle, set_properties_default_to_0) {
  ASSERT_EQ(YGStyle{}.assignedProps(), AssignedProps{0});
}

TEST(YGStyle, set_properties_reflects_all_set_properties) {
  auto style = YGStyle{};

  style.direction() = YGDirectionRTL;
  style.justifyContent() = YGJustifySpaceAround;
  style.flexWrap() = YGWrapWrap;
  style.padding()[YGEdgeVertical] = YGValue{1, YGUnitPoint};
  style.minDimensions()[YGDimensionHeight] = YGValue{1, YGUnitPercent};
  style.aspectRatio() = YGFloatOptional{1.23};

  ASSERT_EQ(
      style.assignedProps(),
      AssignedProps{1ull << YGStyle::directionBit |
                    1ull << YGStyle::justifyContentBit |
                    1ull << YGStyle::flexWrapBit |
                    1ull << (YGStyle::paddingBit + YGEdgeVertical) |
                    1ull << (YGStyle::minDimensionsBit + YGDimensionHeight) |
                    1ull << YGStyle::aspectRatioBit});
}

TEST(YGStyle, directionBit) {
  constexpr auto directionBit = YGStyle::directionBit;
  ASSERT_EQ(directionBit, 0);
}
TEST(YGStyle, flexDirectionBit) {
  constexpr auto flexDirectionBit = YGStyle::flexDirectionBit;
  ASSERT_EQ(flexDirectionBit, 1);
}
TEST(YGStyle, justifyContentBit) {
  constexpr auto justifyContentBit = YGStyle::justifyContentBit;
  ASSERT_EQ(justifyContentBit, 2);
}
TEST(YGStyle, alignContentBit) {
  constexpr auto alignContentBit = YGStyle::alignContentBit;
  ASSERT_EQ(alignContentBit, 3);
}
TEST(YGStyle, alignItemsBit) {
  constexpr auto alignItemsBit = YGStyle::alignItemsBit;
  ASSERT_EQ(alignItemsBit, 4);
}
TEST(YGStyle, alignSelfBit) {
  constexpr auto alignSelfBit = YGStyle::alignSelfBit;
  ASSERT_EQ(alignSelfBit, 5);
}
TEST(YGStyle, positionTypeBit) {
  constexpr auto positionTypeBit = YGStyle::positionTypeBit;
  ASSERT_EQ(positionTypeBit, 6);
}
TEST(YGStyle, flexWrapBit) {
  constexpr auto flexWrapBit = YGStyle::flexWrapBit;
  ASSERT_EQ(flexWrapBit, 7);
}
TEST(YGStyle, overflowBit) {
  constexpr auto overflowBit = YGStyle::overflowBit;
  ASSERT_EQ(overflowBit, 8);
}
TEST(YGStyle, displayBit) {
  constexpr auto displayBit = YGStyle::displayBit;
  ASSERT_EQ(displayBit, 9);
}
TEST(YGStyle, flexBit) {
  constexpr auto flexBit = YGStyle::flexBit;
  ASSERT_EQ(flexBit, 10);
}
TEST(YGStyle, flexGrowBit) {
  constexpr auto flexGrowBit = YGStyle::flexGrowBit;
  ASSERT_EQ(flexGrowBit, 11);
}
TEST(YGStyle, flexShrinkBit) {
  constexpr auto flexShrinkBit = YGStyle::flexShrinkBit;
  ASSERT_EQ(flexShrinkBit, 12);
}
TEST(YGStyle, flexBasisBit) {
  constexpr auto flexBasisBit = YGStyle::flexBasisBit;
  ASSERT_EQ(flexBasisBit, 13);
}
TEST(YGStyle, marginBit) {
  constexpr auto marginBit = YGStyle::marginBit;
  ASSERT_EQ(marginBit, 14);
}
TEST(YGStyle, positionBit) {
  constexpr auto positionBit = YGStyle::positionBit;
  ASSERT_EQ(positionBit, 23);
}
TEST(YGStyle, paddingBit) {
  constexpr auto paddingBit = YGStyle::paddingBit;
  ASSERT_EQ(paddingBit, 32);
}
TEST(YGStyle, borderBit) {
  constexpr auto borderBit = YGStyle::borderBit;
  ASSERT_EQ(borderBit, 41);
}
TEST(YGStyle, dimensionsBit) {
  constexpr auto dimensionsBit = YGStyle::dimensionsBit;
  ASSERT_EQ(dimensionsBit, 50);
}
TEST(YGStyle, maxDimensionsBit) {
  constexpr auto maxDimensionsBit = YGStyle::maxDimensionsBit;
  ASSERT_EQ(maxDimensionsBit, 52);
}
TEST(YGStyle, minDimensionsBit) {
  constexpr auto minDimensionsBit = YGStyle::minDimensionsBit;
  ASSERT_EQ(minDimensionsBit, 54);
}
TEST(YGStyle, aspectRatioBit) {
  constexpr auto aspectRatioBit = YGStyle::aspectRatioBit;
  ASSERT_EQ(aspectRatioBit, 56);
}
TEST(YGStyle, numStyles) {
  constexpr auto numStyles = YGStyle::numStyles;
  ASSERT_EQ(numStyles, 57);
}

} // namespace yoga
} // namespace facebook
