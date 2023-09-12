/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <yoga/event/event.h>

#include <functional>

namespace facebook::yoga::test {

struct TestUtil {
  static void startCountingNodes();
  static int nodeCount();
  static int stopCountingNodes();
};

struct ScopedEventSubscription {
  ScopedEventSubscription(std::function<Event::Subscriber>&&);
  ~ScopedEventSubscription();
};

} // namespace facebook::yoga::test
