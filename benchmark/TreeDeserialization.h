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

YGFlexDirection flexDirectionFromString(const std::string& str);

YGJustify justifyContentFromString(const std::string& str);

YGAlign alignFromString(const std::string& str);

YGWrap wrapFromString(const std::string& str);

YGOverflow overflowFromString(const std::string& str);

YGDisplay displayFromString(const std::string& str);

YGPositionType positionTypeFromString(const std::string& str);

YGUnit unitFromJson(json& j);

YGEdge edgeFromString(const std::string& str);

YGErrata errataFromString(const std::string& str);

YGExperimentalFeature experimentalFeatureFromString(const std::string& str);

std::string edgeStringFromPropertyName(
    const json::iterator& it,
    const std::string& propertyName);

YGDirection directionFromString(const std::string& str);

YGMeasureMode measureModeFromString(const std::string& str);

SerializedMeasureFunc serializedMeasureFuncFromJson(json& j);
} // namespace facebook::yoga
