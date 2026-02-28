/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <cstdint>
#include <optional>
#include <string>

namespace facebook::yoga {

// https://www.w3.org/TR/css-grid-1/#typedef-grid-row-start-grid-line
enum class GridLineType : uint8_t {
  Auto,
  Integer,
  Span,
};

struct GridLine {
  GridLineType type;
  // Line position (1, 2, -1, -2, etc)
  int32_t integer;

  constexpr static GridLine auto_() {
    return GridLine{GridLineType::Auto, 0};
  }

  constexpr static GridLine fromInteger(int32_t value) {
    return GridLine{GridLineType::Integer, value};
  }

  constexpr static GridLine span(int32_t value) {
    return GridLine{GridLineType::Span, value};
  }

  constexpr bool isAuto() const {
    return type == GridLineType::Auto;
  }

  constexpr bool isInteger() const {
    return type == GridLineType::Integer;
  }

  constexpr bool isSpan() const {
    return type == GridLineType::Span;
  }

  bool operator==(const GridLine& other) const  = default;
};

} // namespace facebook::yoga
