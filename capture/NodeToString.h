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

void nodeToString(std::string& str, YGNodeRef node, YGPrintOptions options);

} // namespace facebook::yoga
