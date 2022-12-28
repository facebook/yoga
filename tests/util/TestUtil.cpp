/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "TestUtil.h"

#include <yoga/YGNode.h>
#include <yoga/event/event.h>

namespace facebook {
namespace yoga {
namespace test {

int nodeInstanceCount = 0;

namespace {

void yogaEventSubscriber(
    const YGNode& node,
    Event::Type eventType,
    const Event::Data& eventData) {

  switch (eventType) {
    case Event::NodeAllocation:
      nodeInstanceCount++;
      break;
    case Event::NodeDeallocation:
      nodeInstanceCount--;
      break;
    default:
      break;
  }
}
} // namespace

void TestUtil::startCountingNodes() {
  nodeInstanceCount = 0;
  Event::subscribe(yogaEventSubscriber);
}

int TestUtil::nodeCount() {
  return nodeInstanceCount;
}

int TestUtil::stopCountingNodes() {
  Event::reset();
  auto prev = nodeInstanceCount;
  nodeInstanceCount = 0;
  return prev;
}

ScopedEventSubscription::ScopedEventSubscription(
    std::function<Event::Subscriber>&& s) {
  Event::subscribe(std::move(s));
}

ScopedEventSubscription::~ScopedEventSubscription() {
  Event::reset();
}

} // namespace test
} // namespace yoga
} // namespace facebook
