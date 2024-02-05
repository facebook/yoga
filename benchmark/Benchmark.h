/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <filesystem>
#include <string>

namespace facebook::yoga {

void generateBenchmark(const std::filesystem::path& capturePath);

} // namespace facebook::yoga
