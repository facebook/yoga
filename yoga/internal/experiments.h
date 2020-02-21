/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <cstddef>

namespace facebook {
namespace yoga {
namespace internal {

enum struct Experiment : size_t {
  kDoubleMeasureCallbacks,
};

void __cdecl enable(Experiment);
void __cdecl disable(Experiment);
bool __cdecl toggle(Experiment);

} // namespace internal
} // namespace yoga
} // namespace facebook
