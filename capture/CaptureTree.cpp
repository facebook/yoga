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

static std::vector<SerializedMeasureFunc>& currentSerializedMeasureFuncVec() {
  static thread_local std::vector<SerializedMeasureFunc>
      currentSerializedMeasureFuncVec;
  return currentSerializedMeasureFuncVec;
}

/*
 * Capturing a tree often means that we capturing multiple serial layouts over
 * the course of the capture. Because of this, we need to make sure that we do
 * a full layout pass with no caching. If we do not do this there is a chance
 * we do not capture measure functions that were called and cached in previous
 * layouts. Missing these captures would lead to inaccurate benchmarking where
 * we do not have cached state.
 *
 * TODO: Dirty entire tree not just measure function nodes
 */
static void dirtyTree(YGNodeRef node) {
  if (YGNodeHasMeasureFunc(node)) {
    YGNodeMarkDirty(node);
  }

  const size_t childCount = YGNodeGetChildCount(node);
  for (size_t i = 0; i < childCount; i++) {
    dirtyTree(YGNodeGetChild(node, i));
  }
}

void YGNodeCalculateLayoutWithCapture(
    YGNodeRef node,
    float availableWidth,
    float availableHeight,
    YGDirection ownerDirection,
    const std::filesystem::path& path) {
  dirtyTree(node);
  json j;
  serializeLayoutInputs(j, availableWidth, availableHeight, ownerDirection);
  serializeTree(
      j,
      node,
      PrintOptions::Style | PrintOptions::Children | PrintOptions::Config |
          PrintOptions::Node);

  YGNodeCalculateLayout(node, availableWidth, availableHeight, ownerDirection);

  serializeMeasureFuncResults(j, currentSerializedMeasureFuncVec());
  // TODO: It is possible to have a measure function call layout again if, e.g.,
  // views are nested in text. Need to be able to resolve this special case.
  currentSerializedMeasureFuncVec().clear();
  captureTree(j.dump(2), path);
}

void captureMeasureFunc(
    float width,
    YGMeasureMode widthMode,
    float height,
    YGMeasureMode heightMode,
    YGSize output,
    std::chrono::steady_clock::duration durationNs) {
  currentSerializedMeasureFuncVec().push_back(SerializedMeasureFunc{
      width,
      widthMode,
      height,
      heightMode,
      output.width,
      output.height,
      durationNs.count()});
}

} // namespace facebook::yoga
