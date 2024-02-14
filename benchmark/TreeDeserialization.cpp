/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <memory>
#include <vector>

#include <benchmark/TreeDeserialization.h>
#include <capture/CaptureTree.h>
#include <nlohmann/json.hpp>
#include <yoga/Yoga.h>

namespace facebook::yoga {

using namespace nlohmann;

static inline bool isAuto(json& j) {
  return j.is_string() && j == "auto";
}

static inline std::string invalidArgumentMessage(
    std::string arg,
    std::string enumName) {
  return arg + " does not represent any " + enumName + " values";
}

static inline float floatFromJson(json& j) {
  float result = YGUndefined;
  if (!j.is_null()) {
    result = j;
  }

  return result;
}

YGFlexDirection flexDirectionFromString(std::string str) {
  if (str == "row") {
    return YGFlexDirectionRow;
  } else if (str == "row-reverse") {
    return YGFlexDirectionRowReverse;
  } else if (str == "column") {
    return YGFlexDirectionColumn;
  } else if (str == "column-reverse") {
    return YGFlexDirectionColumnReverse;
  } else {
    throw std::invalid_argument(invalidArgumentMessage(str, "YGFlexDirection"));
  }
}

YGJustify justifyContentFromString(std::string str) {
  if (str == "flex-start") {
    return YGJustifyFlexStart;
  } else if (str == "center") {
    return YGJustifyCenter;
  } else if (str == "flex-end") {
    return YGJustifyFlexEnd;
  } else if (str == "space-between") {
    return YGJustifySpaceBetween;
  } else if (str == "space-around") {
    return YGJustifySpaceAround;
  } else if (str == "space-evenly") {
    return YGJustifySpaceEvenly;
  } else {
    throw std::invalid_argument(invalidArgumentMessage(str, "YGJustify"));
  }
}

YGAlign alignFromString(std::string str) {
  if (str == "auto") {
    return YGAlignAuto;
  } else if (str == "flex-start") {
    return YGAlignFlexStart;
  } else if (str == "center") {
    return YGAlignCenter;
  } else if (str == "flex-end") {
    return YGAlignFlexEnd;
  } else if (str == "stretch") {
    return YGAlignStretch;
  } else if (str == "baseline") {
    return YGAlignBaseline;
  } else if (str == "space-between") {
    return YGAlignSpaceBetween;
  } else if (str == "space-around") {
    return YGAlignSpaceAround;
  } else if (str == "space-evenly") {
    return YGAlignSpaceEvenly;
  } else {
    throw std::invalid_argument(invalidArgumentMessage(str, "YGAlign"));
  }
}

YGWrap wrapFromString(std::string str) {
  if (str == "no-wrap") {
    return YGWrapNoWrap;
  } else if (str == "wrap") {
    return YGWrapWrap;
  } else if (str == "wrap-reverse") {
    return YGWrapWrapReverse;
  } else {
    throw std::invalid_argument(invalidArgumentMessage(str, "YGAlign"));
  }
}

YGOverflow overflowFromString(std::string str) {
  if (str == "visible") {
    return YGOverflowVisible;
  } else if (str == "hidden") {
    return YGOverflowHidden;
  } else if (str == "scroll") {
    return YGOverflowScroll;
  } else {
    throw std::invalid_argument(invalidArgumentMessage(str, "YGAlign"));
  }
}

YGDisplay displayFromString(std::string str) {
  if (str == "flex") {
    return YGDisplayFlex;
  } else if (str == "none") {
    return YGDisplayNone;
  } else {
    throw std::invalid_argument(invalidArgumentMessage(str, "YGAlign"));
  }
}

YGPositionType positionTypeFromString(std::string str) {
  if (str == "static") {
    return YGPositionTypeStatic;
  } else if (str == "relative") {
    return YGPositionTypeRelative;
  } else if (str == "absolute") {
    return YGPositionTypeAbsolute;
  } else {
    throw std::invalid_argument(invalidArgumentMessage(str, "YGAlign"));
  }
}

YGUnit unitFromJson(json& j) {
  if (isAuto(j)) {
    return YGUnitAuto;
  }

  std::string unit = j["unit"];
  if (unit == "px") {
    return YGUnitPoint;
  } else if (unit == "pct") {
    return YGUnitPercent;
  } else {
    throw std::invalid_argument(invalidArgumentMessage(unit, "YGUnit"));
  }
}

YGEdge edgeFromString(std::string str) {
  if (str == "left") {
    return YGEdgeLeft;
  } else if (str == "top") {
    return YGEdgeTop;
  } else if (str == "right") {
    return YGEdgeRight;
  } else if (str == "bottom") {
    return YGEdgeBottom;
  } else if (str == "start") {
    return YGEdgeStart;
  } else if (str == "end") {
    return YGEdgeEnd;
  } else if (str == "horizontal") {
    return YGEdgeHorizontal;
  } else if (str == "vertical") {
    return YGEdgeVertical;
  } else if (str == "all") {
    return YGEdgeAll;
  } else {
    throw std::invalid_argument(invalidArgumentMessage(str, "YGEdge"));
  }
}

YGErrata errataFromString(std::string str) {
  if (str == "none") {
    return YGErrataNone;
  } else if (str == "all") {
    return YGErrataAll;
  } else if (str == "classic") {
    return YGErrataClassic;
  } else {
    throw std::invalid_argument(invalidArgumentMessage(str, "YGErrata"));
  }
}

YGExperimentalFeature experimentalFeatureFromString(std::string str) {
  if (str == "web-flex-basis") {
    return YGExperimentalFeatureWebFlexBasis;
  } else {
    throw std::invalid_argument(
        invalidArgumentMessage(str, "YGExperimentalFeature"));
  }
}

std::string edgeStringFromPropertyName(
    json::iterator it,
    std::string propertyName) {
  return it.key().substr(propertyName.length() + 1);
}

YGDirection directionFromString(std::string str) {
  if (str == "ltr") {
    return YGDirectionLTR;
  } else if (str == "rtl") {
    return YGDirectionRTL;
  } else if (str == "inherit") {
    return YGDirectionInherit;
  } else {
    throw std::invalid_argument(invalidArgumentMessage(str, "YGDirection"));
  }
}

YGMeasureMode measureModeFromString(std::string str) {
  if (str == "at-most") {
    return YGMeasureModeAtMost;
  } else if (str == "exactly") {
    return YGMeasureModeExactly;
  } else if (str == "undefined") {
    return YGMeasureModeUndefined;
  } else {
    throw std::invalid_argument(invalidArgumentMessage(str, "YGMeasureMode"));
  }
}

void populateMeasureFuncVec(
    json& j,
    std::shared_ptr<MeasureFuncVecWithIndex> fns) {
  for (auto measureFuncJson : j) {
    fns->vec.push_back(SerializedMeasureFunc{
        floatFromJson(measureFuncJson["width"]),
        measureModeFromString(measureFuncJson["width-mode"]),
        floatFromJson(measureFuncJson["height"]),
        measureModeFromString(measureFuncJson["height-mode"]),
        floatFromJson(measureFuncJson["output-width"]),
        floatFromJson(measureFuncJson["output-height"]),
        measureFuncJson["duration-ns"]});
  }
}
} // namespace facebook::yoga
