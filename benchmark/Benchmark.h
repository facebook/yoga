/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <chrono>
#include <string>

namespace facebook::yoga {

struct BenchmarkResult {
  std::chrono::steady_clock::duration treeCreationDuration;
  std::chrono::steady_clock::duration layoutDuration;
};

} // namespace facebook::yoga
