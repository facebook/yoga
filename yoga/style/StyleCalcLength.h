/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <yoga/numeric/FloatOptional.h>

namespace facebook::yoga {

struct StyleCalcLength {
  constexpr StyleCalcLength() = default;
  constexpr StyleCalcLength(
      FloatOptional px,
      FloatOptional percent,
      FloatOptional vw,
      FloatOptional vh)
      : px_(px), percent_(percent), vw_(vw), vh_(vh) {}

  constexpr static StyleCalcLength points(float value) {
    return StyleCalcLength{
        FloatOptional{value},
        FloatOptional{},
        FloatOptional{},
        FloatOptional{}};
  }

  constexpr static StyleCalcLength percent(float value) {
    return StyleCalcLength{
        FloatOptional{},
        FloatOptional{value},
        FloatOptional{},
        FloatOptional{}};
  }

  constexpr static StyleCalcLength vw(float value) {
    return StyleCalcLength{
        FloatOptional{},
        FloatOptional{},
        FloatOptional{value},
        FloatOptional{}};
  }

  constexpr static StyleCalcLength vh(float value) {
    return StyleCalcLength{
        FloatOptional{},
        FloatOptional{},
        FloatOptional{},
        FloatOptional{value}};
  }

  constexpr bool isUndefined() const {
    return px_.isUndefined() && percent_.isUndefined() && vw_.isUndefined() &&
        vh_.isUndefined();
  }

  constexpr bool isPointsOnly() const {
    return px_.isDefined() && percent_.isUndefined() && vw_.isUndefined() &&
        vh_.isUndefined();
  }

  constexpr bool isPercentOnly() const {
    return px_.isUndefined() && percent_.isDefined() && vw_.isUndefined() &&
        vh_.isUndefined();
  }

  constexpr FloatOptional px() const {
    return px_;
  }
  constexpr FloatOptional percent() const {
    return percent_;
  }
  constexpr FloatOptional vw() const {
    return vw_;
  }
  constexpr FloatOptional vh() const {
    return vh_;
  }

  constexpr FloatOptional resolve(
      float referenceLength,
      float viewportWidth,
      float viewportHeight) const {
    if (isUndefined()) {
      return FloatOptional{};
    }
    return FloatOptional{
        px_.unwrapOrDefault(0.f) +
        (percent_.unwrapOrDefault(0.f) * referenceLength * 0.01f) +
        (vw_.unwrapOrDefault(0.f) * viewportWidth * 0.01f) +
        (vh_.unwrapOrDefault(0.f) * viewportHeight * 0.01f)};
  }

  explicit constexpr operator YGValue() const {
    if (isPointsOnly()) {
      return YGValue{px_.unwrap(), YGUnitPoint};
    }
    if (isPercentOnly()) {
      return YGValue{percent_.unwrap(), YGUnitPercent};
    }
    return YGValueUndefined;
  }

  constexpr bool operator==(const StyleCalcLength& rhs) const = default;

 private:
  FloatOptional px_{};
  FloatOptional percent_{};
  FloatOptional vw_{};
  FloatOptional vh_{};
};

constexpr bool inexactEquals(
    const StyleCalcLength& a,
    const StyleCalcLength& b) {
  return yoga::inexactEquals(a.px().unwrap(), b.px().unwrap()) &&
      yoga::inexactEquals(a.percent().unwrap(), b.percent().unwrap()) &&
      yoga::inexactEquals(a.vw().unwrap(), b.vw().unwrap()) &&
      yoga::inexactEquals(a.vh().unwrap(), b.vh().unwrap());
}

} // namespace facebook::yoga
