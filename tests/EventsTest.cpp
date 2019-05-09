/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the LICENSE
 * file in the root directory of this source tree.
 */
#include <gtest/gtest.h>
#include <yoga/Yoga.h>
#include <yoga/events.h>
#include <yoga/YGNode.h>
#include <yoga/testutil/testutil.h>

#include <functional>
#include <memory>

namespace facebook {
namespace yoga {
namespace test {

struct EventArgs {
  const YGNode* node;
  Event::Type type;
  std::unique_ptr<void, std::function<void(void*)>> dataPtr;

  template <Event::Type E>
  const Event::TypedData<E>& data() {
    return *static_cast<Event::TypedData<E>*>(dataPtr.get());
  }
};

class EventTest : public ::testing::Test {
  ScopedEventSubscription subscription = {&EventTest::listen};
  static void listen(const YGNode&, Event::Type, Event::Data);

public:
  static EventArgs lastEvent;
};

TEST_F(EventTest, new_node_has_event) {
  auto c = YGConfigGetDefault();
  auto n = YGNodeNew();

  ASSERT_EQ(lastEvent.node, n);
  ASSERT_EQ(lastEvent.type, Event::NodeAllocation);
  ASSERT_EQ(lastEvent.data<Event::NodeAllocation>().config, c);

  YGNodeFree(n);
}

TEST_F(EventTest, new_node_with_config_event) {
  auto c = YGConfigNew();
  auto n = YGNodeNewWithConfig(c);

  ASSERT_EQ(lastEvent.node, n);
  ASSERT_EQ(lastEvent.type, Event::NodeAllocation);
  ASSERT_EQ(lastEvent.data<Event::NodeAllocation>().config, c);

  YGNodeFree(n);
  YGConfigFree(c);
}

TEST_F(EventTest, clone_node_event) {
  auto c = YGConfigNew();
  auto n = YGNodeNewWithConfig(c);
  auto clone = YGNodeClone(n);

  ASSERT_EQ(lastEvent.node, clone);
  ASSERT_EQ(lastEvent.type, Event::NodeAllocation);
  ASSERT_EQ(lastEvent.data<Event::NodeAllocation>().config, c);

  YGNodeFree(n);
  YGNodeFree(clone);
  YGConfigFree(c);
}

TEST_F(EventTest, free_node_event) {
  auto c = YGConfigNew();
  auto n = YGNodeNewWithConfig(c);
  YGNodeFree(n);

  ASSERT_EQ(lastEvent.node, n);
  ASSERT_EQ(lastEvent.type, Event::NodeDeallocation);
  ASSERT_EQ(lastEvent.data<Event::NodeDeallocation>().config, c);

  YGConfigFree(c);
}

namespace {

template <Event::Type E>
EventArgs createArgs(const YGNode& node, const Event::Data& data) {
  using Data = Event::TypedData<E>;
  auto deleteData = [](void* x) { delete static_cast<Data*>(x); };
  return {&node, E, {new Data{data.get<E>()}, deleteData}};
}

} // namespace

void EventTest::listen(const YGNode& node, Event::Type type, Event::Data data) {
  switch (type) {
    case Event::NodeAllocation:
      lastEvent = createArgs<Event::NodeAllocation>(node, data);
      break;
    case Event::NodeDeallocation:
      lastEvent = createArgs<Event::NodeDeallocation>(node, data);
      break;
  }
}

EventArgs EventTest::lastEvent{};

} // namespace test
} // namespace yoga
} // namespace facebook
