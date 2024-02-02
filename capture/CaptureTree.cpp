/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <fstream>

#include <capture/CaptureTree.h>
#include <capture/NodeToString.h>

namespace facebook::yoga {

void captureTree(YGNodeRef node, const std::filesystem::path& path) {
  std::string str;
  nodeToString(str, node, YGPrintOptionsStyle | YGPrintOptionsChildren);
  std::ofstream file(path);
  file << str;
}

} // namespace facebook::yoga
