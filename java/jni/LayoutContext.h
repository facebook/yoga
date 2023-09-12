/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <stack>
#include "YGJTypesVanilla.h"

namespace facebook::yoga::vanillajni {

class LayoutContext {
public:
  struct Holder {
    explicit Holder(PtrJNodeMapVanilla* data) {
      LayoutContext::contexts_.push(data);
    }
    ~Holder() { LayoutContext::contexts_.pop(); }
  };

  static PtrJNodeMapVanilla* getCurrent() {
    return contexts_.empty() ? nullptr : contexts_.top();
  }

private:
  static thread_local std::stack<PtrJNodeMapVanilla*> contexts_;
};

} // namespace facebook::yoga::vanillajni
