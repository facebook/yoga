/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <chrono>
#include <memory>
#include <string>
#include <vector>

#include <yoga/Yoga.h>

namespace facebook::yoga {

struct YogaNodeAndConfig {
  std::shared_ptr<YGNode> node_;
  std::shared_ptr<const YGConfig> config_;
  std::vector<YogaNodeAndConfig> children_;
};

struct BenchmarkResult {
  std::chrono::steady_clock::duration treeCreationDuration;
  std::chrono::steady_clock::duration layoutDuration;
};

} // namespace facebook::yoga
