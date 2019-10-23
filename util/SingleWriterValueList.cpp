/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "SingleWriterValueList.h"

namespace facebook {
namespace yoga {
namespace detail {

void* FreeList::getRaw() {
  if (free_.size() == 0)
    return nullptr;

  auto ptr = free_.top();
  free_.pop();
  return ptr;
}

void FreeList::put(std::mutex& mutex, void* ptr) {
  std::lock_guard<std::mutex> lock{mutex};
  free_.push(ptr);
}

FreeList::FreeList() = default;
FreeList::~FreeList() = default;

} // namespace detail
} // namespace yoga
} // namespace facebook
