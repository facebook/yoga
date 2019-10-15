/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <gtest/gtest.h>
#include <yoga/Yoga.h>
#include <yoga/event/event.h>
#include <yoga/YGNode.h>
#include <yoga/testutil/testutil.h>

#include <algorithm>
#include <functional>
#include <memory>
#include <vector>
#include <yoga/YGEnums.h>

namespace facebook {
namespace yoga {
namespace test {

template <Event::Type E>
struct TypedEventTestData {};

template <>
struct TypedEventTestData<Event::LayoutPassEnd> {
  void* layoutContext;
  LayoutData layoutData;
};

struct EventArgs {
  const YGNode* node;
  Event::Type type;
  std::unique_ptr<void, std::function<void(void*)>> dataPtr;
  std::unique_ptr<void, std::function<void(void*)>> eventTestDataPtr;

  template <Event::Type E>
  const Event::TypedData<E>& data() {
    return *static_cast<Event::TypedData<E>*>(dataPtr.get());
  }

  template <Event::Type E>
  const TypedEventTestData<E>& eventTestData() {
    return *static_cast<TypedEventTestData<E>*>(eventTestDataPtr.get());
  }
};

class EventTest : public ::testing::Test {
  ScopedEventSubscription subscription = {&EventTest::listen};
  static void listen(const YGNode&, Event::Type, Event::Data);

public:
  static std::vector<EventArgs> events;
  static EventArgs& lastEvent() { return events.back(); }
  void TearDown() override;
};

TEST_F(EventTest, new_node_has_event) {
  auto c = YGConfigGetDefault();
  auto n = YGNodeNew();

  ASSERT_EQ(lastEvent().node, n);
  ASSERT_EQ(lastEvent().type, Event::NodeAllocation);
  ASSERT_EQ(lastEvent().data<Event::NodeAllocation>().config, c);

  YGNodeFree(n);
}

TEST_F(EventTest, new_node_with_config_event) {
  auto c = YGConfigNew();
  auto n = YGNodeNewWithConfig(c);

  ASSERT_EQ(lastEvent().node, n);
  ASSERT_EQ(lastEvent().type, Event::NodeAllocation);
  ASSERT_EQ(lastEvent().data<Event::NodeAllocation>().config, c);

  YGNodeFree(n);
  YGConfigFree(c);
}

TEST_F(EventTest, clone_node_event) {
  auto c = YGConfigNew();
  auto n = YGNodeNewWithConfig(c);
  auto clone = YGNodeClone(n);

  ASSERT_EQ(lastEvent().node, clone);
  ASSERT_EQ(lastEvent().type, Event::NodeAllocation);
  ASSERT_EQ(lastEvent().data<Event::NodeAllocation>().config, c);

  YGNodeFree(n);
  YGNodeFree(clone);
  YGConfigFree(c);
}

TEST_F(EventTest, free_node_event) {
  auto c = YGConfigNew();
  auto n = YGNodeNewWithConfig(c);
  YGNodeFree(n);

  ASSERT_EQ(lastEvent().node, n);
  ASSERT_EQ(lastEvent().type, Event::NodeDeallocation);
  ASSERT_EQ(lastEvent().data<Event::NodeDeallocation>().config, c);

  YGConfigFree(c);
}

TEST_F(EventTest, layout_events) {
  auto root = YGNodeNew();
  auto child = YGNodeNew();
  YGNodeInsertChild(root, child, 0);

  YGNodeCalculateLayout(root, 123, 456, YGDirectionLTR);

  ASSERT_EQ(events[2].node, root);
  ASSERT_EQ(events[2].type, Event::LayoutPassStart);

  ASSERT_EQ(events[3].node, child);
  ASSERT_EQ(events[3].type, Event::NodeLayout);

  ASSERT_EQ(events[4].node, child);
  ASSERT_EQ(events[4].type, Event::NodeLayout);

  ASSERT_EQ(events[5].node, child);
  ASSERT_EQ(events[5].type, Event::NodeLayout);

  ASSERT_EQ(events[6].node, root);
  ASSERT_EQ(events[6].type, Event::NodeLayout);

  ASSERT_EQ(events[7].node, root);
  ASSERT_EQ(events[7].type, Event::LayoutPassEnd);

  YGNodeFreeRecursive(root);
}

TEST_F(EventTest, layout_events_single_node) {
  auto root = YGNodeNew();
  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(events[1].node, root);
  ASSERT_EQ(events[1].type, Event::LayoutPassStart);

  ASSERT_EQ(events[2].node, root);
  ASSERT_EQ(events[2].type, Event::NodeLayout);

  ASSERT_EQ(events[3].node, root);
  ASSERT_EQ(events[3].type, Event::LayoutPassEnd);

  LayoutData layoutData =
      events[3].eventTestData<Event::LayoutPassEnd>().layoutData;

  ASSERT_EQ(layoutData.layouts, 1);
  ASSERT_EQ(layoutData.measures, 0);
  ASSERT_EQ(layoutData.maxMeasureCache, 1);
}

TEST_F(EventTest, layout_events_counts_multi_node_layout) {
  auto root = YGNodeNew();
  auto childA = YGNodeNew();
  YGNodeInsertChild(root, childA, 0);
  auto childB = YGNodeNew();
  YGNodeInsertChild(root, childB, 1);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(events[3].node, root);
  ASSERT_EQ(events[3].type, Event::LayoutPassStart);

  ASSERT_EQ(events[11].node, root);
  ASSERT_EQ(events[11].type, Event::LayoutPassEnd);

  LayoutData layoutData =
      events[11].eventTestData<Event::LayoutPassEnd>().layoutData;

  ASSERT_EQ(layoutData.layouts, 3);
  ASSERT_EQ(layoutData.measures, 4);
  ASSERT_EQ(layoutData.maxMeasureCache, 3);
}

TEST_F(EventTest, layout_events_counts_cache_hits_single_node_layout) {
  auto root = YGNodeNew();

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(events[4].node, root);
  ASSERT_EQ(events[4].type, Event::LayoutPassStart);

  ASSERT_EQ(events[6].node, root);
  ASSERT_EQ(events[6].type, Event::LayoutPassEnd);

  LayoutData layoutData =
      events[6].eventTestData<Event::LayoutPassEnd>().layoutData;

  ASSERT_EQ(layoutData.layouts, 0);
  ASSERT_EQ(layoutData.measures, 0);
  ASSERT_EQ(layoutData.cachedLayouts, 1);
  ASSERT_EQ(layoutData.cachedMeasures, 0);
}

TEST_F(EventTest, layout_events_counts_cache_hits_multi_node_layout) {
  auto root = YGNodeNew();
  auto childA = YGNodeNew();
  YGNodeInsertChild(root, childA, 0);
  auto childB = YGNodeNew();
  YGNodeInsertChild(root, childB, 1);

  YGNodeCalculateLayout(root, 987, 654, YGDirectionLTR);
  YGNodeCalculateLayout(root, 123, 456, YGDirectionLTR);

  YGNodeCalculateLayout(root, 987, 654, YGDirectionLTR);

  ASSERT_EQ(lastEvent().node, root);
  ASSERT_EQ(lastEvent().type, Event::LayoutPassEnd);

  LayoutData layoutData =
      lastEvent().eventTestData<Event::LayoutPassEnd>().layoutData;

  ASSERT_EQ(layoutData.layouts, 3);
  ASSERT_EQ(layoutData.measures, 0);
  ASSERT_EQ(layoutData.maxMeasureCache, 5);
  ASSERT_EQ(layoutData.cachedLayouts, 0);
  ASSERT_EQ(layoutData.cachedMeasures, 4);
}

TEST_F(EventTest, layout_events_has_max_measure_cache) {
  auto root = YGNodeNew();
  auto a = YGNodeNew();
  YGNodeInsertChild(root, a, 0);
  auto b = YGNodeNew();
  YGNodeInsertChild(root, b, 1);
  YGNodeStyleSetFlexBasis(a, 10.0f);

  for (auto s : {20, 30, 40}) {
    YGNodeCalculateLayout(root, s, s, YGDirectionLTR);
  }

  ASSERT_EQ(lastEvent().node, root);
  ASSERT_EQ(lastEvent().type, Event::LayoutPassEnd);

  LayoutData layoutData =
      lastEvent().eventTestData<Event::LayoutPassEnd>().layoutData;

  ASSERT_EQ(layoutData.layouts, 3);
  ASSERT_EQ(layoutData.measures, 3);
  ASSERT_EQ(layoutData.maxMeasureCache, 7);
}

TEST_F(EventTest, measure_functions_get_wrapped) {
  auto root = YGNodeNew();
  YGNodeSetMeasureFunc(
      root, [](YGNodeRef, float, YGMeasureMode, float, YGMeasureMode) {
        return YGSize{};
      });

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(events[2].node, root);
  ASSERT_EQ(events[2].type, Event::MeasureCallbackStart);

  ASSERT_EQ(events[events.size() - 1].node, root);
  ASSERT_EQ(events[events.size() - 1].type, Event::LayoutPassEnd);
}

TEST_F(EventTest, baseline_functions_get_wrapped) {
  auto root = YGNodeNew();
  auto child = YGNodeNew();
  YGNodeInsertChild(root, child, 0);

  YGNodeSetBaselineFunc(child, [](YGNodeRef, float, float) { return 0.0f; });
  YGNodeStyleSetFlexDirection(root, YGFlexDirectionRow);
  YGNodeStyleSetAlignItems(root, YGAlignBaseline);

  YGNodeCalculateLayout(root, YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(events[5].node, child);
  ASSERT_EQ(events[5].type, Event::NodeBaselineStart);

  ASSERT_EQ(events[events.size() - 1].node, root);
  ASSERT_EQ(events[events.size() - 1].type, Event::LayoutPassEnd);
}

namespace {

template <Event::Type E>
EventArgs createArgs(const YGNode& node, const Event::Data data) {
  using Data = Event::TypedData<E>;
  auto deleteData = [](void* x) { delete static_cast<Data*>(x); };

  return {&node, E, {new Data{(data.get<E>())}, deleteData}};
}

template <Event::Type E>
EventArgs createArgs(
    const YGNode& node,
    const Event::Data data,
    TypedEventTestData<E> eventTestData) {
  using EventTestData = TypedEventTestData<E>;
  auto deleteEventTestData = [](void* x) {
    delete static_cast<EventTestData*>(x);
  };

  EventArgs args = createArgs<E>(node, data);
  args.eventTestDataPtr = {new EventTestData{eventTestData},
                           deleteEventTestData};
  return args;
}

} // namespace

void EventTest::listen(const YGNode& node, Event::Type type, Event::Data data) {
  switch (type) {
    case Event::NodeAllocation:
      events.push_back(createArgs<Event::NodeAllocation>(node, data));
      break;
    case Event::NodeDeallocation:
      events.push_back(createArgs<Event::NodeDeallocation>(node, data));
      break;
    case Event::NodeLayout:
      events.push_back(createArgs<Event::NodeLayout>(node, data));
      break;
    case Event::LayoutPassStart:
      events.push_back(createArgs<Event::LayoutPassStart>(node, data));
      break;
    case Event::LayoutPassEnd: {
      auto& eventData = data.get<Event::LayoutPassEnd>();
      events.push_back(createArgs<Event::LayoutPassEnd>(
          node, data, {eventData.layoutContext, *eventData.layoutData}));
      break;
    }

    case Event::MeasureCallbackStart:
      events.push_back(createArgs<Event::MeasureCallbackStart>(node, data));
      break;
    case Event::MeasureCallbackEnd:
      events.push_back(createArgs<Event::MeasureCallbackEnd>(node, data));
      break;
    case Event::NodeBaselineStart:
      events.push_back(createArgs<Event::NodeBaselineStart>(node, data));
      break;
    case Event::NodeBaselineEnd:
      events.push_back(createArgs<Event::NodeBaselineEnd>(node, data));
      break;
  }
}

void EventTest::TearDown() {
  events.clear();
}

std::vector<EventArgs> EventTest::events{};

} // namespace test
} // namespace yoga
} // namespace facebook
