/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <chrono>
#include <string>

#include <capture/CaptureTree.h>
#include <nlohmann/json.hpp>
#include <yoga/Yoga.h>

namespace facebook::yoga {

enum class PrintOptions : uint8_t {
  Layout = 1 << 0,
  Children = 1 << 1,
  Style = 1 << 2,
  Config = 1 << 3,
  Node = 1 << 4,
};
YG_DEFINE_ENUM_FLAG_OPERATORS(PrintOptions);

void serializeTree(nlohmann::json& j, YGNodeRef root, PrintOptions options);

void serializeLayoutInputs(
    nlohmann::json& j,
    float availableWidth,
    float availableHeight,
    YGDirection ownerDirection);

void serializeMeasureFuncResults(
    nlohmann::json& j,
    std::vector<SerializedMeasureFunc>& measureFuncs);

} // namespace facebook::yoga
