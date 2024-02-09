/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <fstream>
#include <vector>

#include <capture/CaptureTree.h>
#include <capture/NodeToString.h>
#include <nlohmann/json.hpp>

namespace facebook::yoga {

using namespace nlohmann;

static void captureTree(
    std::string_view serializedTree,
    const std::filesystem::path& path) {
  std::ofstream file(path);
  file << serializedTree;
}

static std::vector<SerializedMeasureFunc>& serializedMeasureFuncVec() {
  static thread_local std::vector<SerializedMeasureFunc>
      serializedMeasureFuncVec;
  return serializedMeasureFuncVec;
}

void YGNodeCalculateLayoutWithCapture(
    YGNodeRef node,
    float availableWidth,
    float availableHeight,
    YGDirection ownerDirection,
    const std::filesystem::path& path) {
  json j;
  serializeLayoutInputs(j, availableWidth, availableHeight, ownerDirection);
  serializeTree(
      j,
      node,
      PrintOptions::Style | PrintOptions::Children | PrintOptions::Config |
          PrintOptions::Node);

  YGNodeCalculateLayout(node, availableWidth, availableHeight, ownerDirection);

  serializeMeasureFuncs(j, serializedMeasureFuncVec());
  serializedMeasureFuncVec().clear();
  captureTree(j.dump(2), path);
}

void captureMeasureFunc(
    float width,
    YGMeasureMode widthMode,
    float height,
    YGMeasureMode heightMode,
    YGSize output,
    std::chrono::steady_clock::duration durationNs) {
  serializedMeasureFuncVec().push_back(SerializedMeasureFunc{
      width,
      widthMode,
      height,
      heightMode,
      output.width,
      output.height,
      durationNs.count()});
}

} // namespace facebook::yoga
