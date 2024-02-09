/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <string>

#include <yoga/Yoga.h>

namespace facebook::yoga {

enum class PrintOptions : uint8_t {
  Layout = 1 << 0,
  Children = 1 << 1,
  Style = 1 << 2,
  Config = 1 << 3,
};
YG_DEFINE_ENUM_FLAG_OPERATORS(PrintOptions);

void nodeToString(std::string& str, YGNodeRef node, PrintOptions options);

} // namespace facebook::yoga
