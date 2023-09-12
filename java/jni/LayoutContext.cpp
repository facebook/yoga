/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "LayoutContext.h"

namespace facebook::yoga::vanillajni {

thread_local std::stack<PtrJNodeMapVanilla*> LayoutContext::contexts_;

} // namespace facebook::yoga::vanillajni
