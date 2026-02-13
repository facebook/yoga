/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <yoga/enums/Unit.h>
#include <yoga/numeric/FloatOptional.h>
#include <yoga/style/StyleCalcLength.h>

namespace facebook::yoga {

/**
 * This class represents a CSS Value for sizes (e.g. width, height, min-width,
 * etc.). It may be one of:
 * 1. Undefined
 * 2. A keyword (e.g. auto, max-content, stretch, etc.)
 * 3. A CSS <length-percentage> value:
 *    a. <length> value (e.g. 10px)
 *    b. <percentage> value of a reference <length>
 *
 * References:
 * 1. https://www.w3.org/TR/css-values-4/#lengths
 * 2. https://www.w3.org/TR/css-values-4/#percentage-value
 * 3. https://www.w3.org/TR/css-values-4/#mixed-percentages
 */
class StyleSizeLength {
 public:
  constexpr StyleSizeLength() = default;

  constexpr static StyleSizeLength points(float value) {
    return yoga::isUndefined(value) || yoga::isinf(value)
        ? undefined()
        : StyleSizeLength{FloatOptional{value}, Unit::Point};
  }

  constexpr static StyleSizeLength percent(float value) {
    return yoga::isUndefined(value) || yoga::isinf(value)
        ? undefined()
        : StyleSizeLength{FloatOptional{value}, Unit::Percent};
  }

  constexpr static StyleSizeLength ofAuto() {
    return StyleSizeLength{FloatOptional{}, Unit::Auto};
  }

  constexpr static StyleSizeLength ofMaxContent() {
    return StyleSizeLength{FloatOptional{}, Unit::MaxContent};
  }

  constexpr static StyleSizeLength ofFitContent() {
    return StyleSizeLength{FloatOptional{}, Unit::FitContent};
  }

  constexpr static StyleSizeLength ofStretch() {
    return StyleSizeLength{FloatOptional{}, Unit::Stretch};
  }

  constexpr static StyleSizeLength undefined() {
    return StyleSizeLength{FloatOptional{}, Unit::Undefined};
  }

  constexpr static StyleSizeLength calc(StyleCalcLength value) {
    return StyleSizeLength{value, Unit::Calc};
  }

  constexpr bool isAuto() const {
    return unit_ == Unit::Auto;
  }

  constexpr bool isMaxContent() const {
    return unit_ == Unit::MaxContent;
  }

  constexpr bool isFitContent() const {
    return unit_ == Unit::FitContent;
  }

  constexpr bool isStretch() const {
    return unit_ == Unit::Stretch;
  }

  constexpr bool isUndefined() const {
    return unit_ == Unit::Undefined;
  }

  constexpr bool isDefined() const {
    return !isUndefined();
  }

  constexpr bool isPoints() const {
    return unit_ == Unit::Point;
  }

  constexpr bool isPercent() const {
    return unit_ == Unit::Percent;
  }

  constexpr bool isCalc() const {
    return unit_ == Unit::Calc;
  }

  constexpr FloatOptional value() const {
    if (unit_ == Unit::Calc) {
      return FloatOptional{};
    }
    return value_.scalar;
  }

  constexpr StyleCalcLength calcValue() const {
    if (unit_ == Unit::Calc) {
      return value_.calc;
    }
    return StyleCalcLength{};
  }

  FloatOptional resolve(
      float referenceLength,
      float viewportWidth,
      float viewportHeight) const {
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wswitch-enum"
#endif
    switch (unit_) {
#ifdef __clang__
#pragma clang diagnostic pop
#endif
      case Unit::Point:
        return value_.scalar;
      case Unit::Percent:
        return FloatOptional{value_.scalar.unwrap() * referenceLength * 0.01f};
      case Unit::Calc:
        return value_.calc.resolve(
            referenceLength, viewportWidth, viewportHeight);
      default:
        return FloatOptional{};
    }
  }

  explicit constexpr operator YGValue() const {
    if (unit_ == Unit::Calc) {
      return static_cast<YGValue>(value_.calc);
    }
    return YGValue{value_.scalar.unwrap(), unscopedEnum(unit_)};
  }

  constexpr bool operator==(const StyleSizeLength& rhs) const {
    if (unit_ != rhs.unit_) {
      return false;
    }
    if (unit_ == Unit::Calc) {
      return value_.calc == rhs.value_.calc;
    } else {
      return value_.scalar == rhs.value_.scalar;
    }
  }

  constexpr bool inexactEquals(const StyleSizeLength& other) const {
    if (unit_ != other.unit_) {
      return false;
    }
    if (unit_ == Unit::Calc) {
      return facebook::yoga::inexactEquals(value_.calc, other.value_.calc);
    } else {
      return facebook::yoga::inexactEquals(value_.scalar, other.value_.scalar);
    }
  }

 private:
  union Value {
    FloatOptional scalar;
    StyleCalcLength calc;

    constexpr Value() : scalar{} {}
    constexpr Value(FloatOptional s) : scalar(s) {}
    constexpr Value(StyleCalcLength c) : calc(c) {}
  };

  // We intentionally do not allow direct construction using value and unit, to
  // avoid invalid, or redundant combinations.
  constexpr StyleSizeLength(FloatOptional value, Unit unit)
      : value_{value}, unit_(unit) {}

  constexpr StyleSizeLength(StyleCalcLength value, Unit unit)
      : value_{value}, unit_(unit) {}

  Value value_{};
  Unit unit_{Unit::Undefined};
};

inline bool inexactEquals(const StyleSizeLength& a, const StyleSizeLength& b) {
  return a.inexactEquals(b);
}

} // namespace facebook::yoga
