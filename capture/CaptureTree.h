/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <filesystem>

#include <yoga/Yoga.h>

namespace facebook::yoga {

struct SerializedMeasureFunc {
  float inputWidth;
  YGMeasureMode widthMode;
  float inputHeight;
  YGMeasureMode heightMode;
  float outputWidth;
  float outputHeight;
  std::chrono::steady_clock::duration::rep durationNs;
};

void YGNodeCalculateLayoutWithCapture(
    YGNodeRef node,
    float availableWidth,
    float availableHeight,
    YGDirection ownerDirection,
    const std::filesystem::path& path);

void captureMeasureFunc(
    float width,
    YGMeasureMode widthMode,
    float height,
    YGMeasureMode heightMode,
    YGSize output,
    std::chrono::steady_clock::duration durationNs);

} // namespace facebook::yoga
