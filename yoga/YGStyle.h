/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the LICENSE
 * file in the root directory of this source tree.
 */
#pragma once
#include <algorithm>
#include <array>
#include <initializer_list>
#include "CompactValue.h"
#include "YGFloatOptional.h"
#include "Yoga-internal.h"
#include "Yoga.h"

constexpr YGValue kYGValueUndefined = {0, YGUnitUndefined};

constexpr YGValue kYGValueAuto = {0, YGUnitAuto};

struct YGStyle {
 private:
  using CompactValue = facebook::yoga::detail::CompactValue;

 public:
  using Dimensions = facebook::yoga::detail::Values<2>;
  using Edges = facebook::yoga::detail::Values<YGEdgeCount>;

  YGDirection direction : 3;
  YGFlexDirection flexDirection : 3;
  YGJustify justifyContent : 4;
  YGAlign alignContent : 4;
  YGAlign alignItems : 4;
  YGAlign alignSelf : 4;
  YGPositionType positionType : 2;
  YGWrap flexWrap : 3;
  YGOverflow overflow : 3;
  YGDisplay display : 2;
  YGFloatOptional flex = {};
  YGFloatOptional flexGrow = {};
  YGFloatOptional flexShrink = {};
  CompactValue flexBasis = CompactValue::ofAuto();
  Edges margin = {};
  Edges position = {};
  Edges padding = {};
  Edges border = {};
  Dimensions dimensions{CompactValue::ofAuto()};
  Dimensions minDimensions = {};
  Dimensions maxDimensions = {};
  // Yoga specific properties, not compatible with flexbox specification
  YGFloatOptional aspectRatio = {};

  YGStyle()
      : direction(YGDirectionInherit),
        flexDirection(YGFlexDirectionColumn),
        justifyContent(YGJustifyFlexStart),
        alignContent(YGAlignFlexStart),
        alignItems(YGAlignStretch),
        alignSelf(YGAlignAuto),
        positionType(YGPositionTypeRelative),
        flexWrap(YGWrapNoWrap),
        overflow(YGOverflowVisible),
        display(YGDisplayFlex) {}
  bool operator==(const YGStyle& style);

  bool operator!=(YGStyle style) {
    return !(*this == style);
  }
  ~YGStyle() = default;
};
