/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <array>
#include <cmath>
#include <concepts>

#include <yoga/Yoga.h>
#include <yoga/numeric/FloatOptional.h>

namespace facebook::yoga {

constexpr bool isUndefined(std::floating_point auto value) {
  // Can be replaced by constexpr std::isnan in C++ 23
  return value != value;
}

inline float maxOrDefined(const float a, const float b) {
  if (!yoga::isUndefined(a) && !yoga::isUndefined(b)) {
    return fmaxf(a, b);
  }
  return yoga::isUndefined(a) ? b : a;
}

inline float minOrDefined(const float a, const float b) {
  if (!yoga::isUndefined(a) && !yoga::isUndefined(b)) {
    return fminf(a, b);
  }

  return yoga::isUndefined(a) ? b : a;
}

// Custom equality functions using a hardcoded epsilon of 0.0001f, or returning
// true if both floats are NaN.
inline bool inexactEquals(const float a, const float b) {
  if (!yoga::isUndefined(a) && !yoga::isUndefined(b)) {
    return fabs(a - b) < 0.0001f;
  }
  return yoga::isUndefined(a) && yoga::isUndefined(b);
}

inline bool inexactEquals(const double a, const double b) {
  if (!yoga::isUndefined(a) && !yoga::isUndefined(b)) {
    return fabs(a - b) < 0.0001;
  }
  return yoga::isUndefined(a) && yoga::isUndefined(b);
}

inline bool inexactEquals(const YGValue& a, const YGValue& b) {
  if (a.unit != b.unit) {
    return false;
  }

  if (a.unit == YGUnitUndefined ||
      (yoga::isUndefined(a.value) && yoga::isUndefined(b.value))) {
    return true;
  }

  return fabs(a.value - b.value) < 0.0001f;
}

template <std::size_t Size, typename ElementT>
bool inexactEquals(
    const std::array<ElementT, Size>& val1,
    const std::array<ElementT, Size>& val2) {
  bool areEqual = true;
  for (std::size_t i = 0; i < Size && areEqual; ++i) {
    areEqual = inexactEquals(val1[i], val2[i]);
  }
  return areEqual;
}

} // namespace facebook::yoga
