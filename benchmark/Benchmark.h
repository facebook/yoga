/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#ifdef DEBUG

#pragma once

#include <yoga/node/Node.h>

namespace facebook::yoga {

void captureTree(const Node* node, std::string captureName);

} // namespace facebook::yoga
#endif
