/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#ifdef DEBUG

#include <filesystem>
#include <fstream>

#include <yoga/benchmark/Benchmark.h>
#include <yoga/debug/NodeToString.h>
#include <yoga/enums/PrintOptions.h>

namespace facebook::yoga {

void captureTree(const Node* node, std::string captureName) {
  std::string str;
  nodeToString(str, node, PrintOptions::Style | PrintOptions::Children);
  std::filesystem::path currentPath = __FILE__;
  std::ofstream file;
  file.open(
      currentPath.parent_path().string() + "/captures/" + captureName +
      ".json");
  file << str;
  file.close();
}

} // namespace facebook::yoga
#endif
