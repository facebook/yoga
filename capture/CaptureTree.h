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

void captureTree(YGNodeRef node, const std::filesystem::path& path);

} // namespace facebook::yoga
