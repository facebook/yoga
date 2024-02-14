/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <memory>
#include <vector>

#include <capture/CaptureTree.h>
#include <nlohmann/json.hpp>
#include <yoga/Yoga.h>

namespace facebook::yoga {

using namespace nlohmann;

struct MeasureFuncVecWithIndex {
  std::vector<SerializedMeasureFunc> vec;
  size_t index;
};

YGFlexDirection flexDirectionFromString(std::string str);

YGJustify justifyContentFromString(std::string str);

YGAlign alignFromString(std::string str);

YGWrap wrapFromString(std::string str);

YGOverflow overflowFromString(std::string str);

YGDisplay displayFromString(std::string str);

YGPositionType positionTypeFromString(std::string str);

YGUnit unitFromJson(json& j);

YGEdge edgeFromString(std::string str);

YGErrata errataFromString(std::string str);

YGExperimentalFeature experimentalFeatureFromString(std::string str);

std::string edgeStringFromPropertyName(
    json::iterator it,
    std::string propertyName);

YGDirection directionFromString(std::string str);

YGMeasureMode measureModeFromString(std::string str);

void populateMeasureFuncVec(
    json& j,
    std::shared_ptr<MeasureFuncVecWithIndex> fns);
} // namespace facebook::yoga
