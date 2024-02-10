/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <fstream>

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
  captureTree(j.dump(2), path);
  YGNodeCalculateLayout(node, availableWidth, availableHeight, ownerDirection);
}

} // namespace facebook::yoga
