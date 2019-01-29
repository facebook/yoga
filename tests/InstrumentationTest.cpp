/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the LICENSE
 * file in the root directory of this source tree.
 */
#include <gtest/gtest.h>
#include <yoga/Yoga.h>
#include <yoga/YGMarker.h>
#include <yoga/instrumentation.h>

#include <cstring>
#include <functional>
#include <memory>
#include <tuple>

namespace facebook {
namespace yoga {
namespace marker {
namespace test {

template <typename T>
using uniquePtr = std::unique_ptr<T, std::function<void(T*)>>;

struct MarkerTest : public ::testing::Test {
  struct Data {
    YGMarker marker;
    YGNodeRef node;
    YGMarkerData markerData;
  };

  struct EndData {
    Data data;
    void* cookie;
  };

  static struct {
    Data start;
    EndData end;
  } markerCookie;

  static void* startMarker(YGMarker, YGNodeRef, YGMarkerData);
  static void endMarker(YGMarker, YGNodeRef, YGMarkerData, void*);
  static uniquePtr<YGConfig> makeConfig();
  static uniquePtr<YGNode> makeNode(uniquePtr<YGConfig>&);

  void SetUp() override;
};

TEST_F(MarkerTest, marker_start_works) {
  auto config = makeConfig();
  auto root = makeNode(config);

  decltype(MarkerSection<YGMarkerLayout>::data)* dataAddress;
  {
    MarkerSection<YGMarkerLayout> marker{root.get()};
    dataAddress = &marker.data;
  }

  ASSERT_EQ(markerCookie.start.marker, YGMarkerLayout)
      << "wrong marker type passed to `startMarker`";
  ASSERT_EQ(markerCookie.start.node, root.get())
      << "wrong node pointer passed to `startMarker`";
  ASSERT_EQ(markerCookie.start.markerData.layout, dataAddress)
      << "wrong pointer to marker data passed to `startMarker`";
}

TEST_F(MarkerTest, marker_end_works) {
  auto config = makeConfig();
  auto root = makeNode(config);

  { MarkerSection<YGMarkerLayout> marker{root.get()}; }

  ASSERT_EQ(markerCookie.end.data.marker, markerCookie.start.marker)
      << "marker type passed to `endMarker` differs from type passed to "
         "`startMarker`";
  ASSERT_EQ(markerCookie.end.data.node, markerCookie.start.node)
      << "node passed to `endMarker` differs from node passed to `startMarker`";
  ASSERT_EQ(
      markerCookie.end.data.markerData.layout,
      markerCookie.start.markerData.layout)
      << "marker data pointer passed to `endMarker` differs from pointer "
         "passed to `startMarker`";
  ASSERT_EQ(markerCookie.end.cookie, &markerCookie)
      << "pointer returned by `startMarker` was not passed to `endMarker`";
}

TEST_F(MarkerTest, layout_marker) {
  auto config = makeConfig();
  auto root = makeNode(config);

  YGNodeCalculateLayout(root.get(), YGUndefined, YGUndefined, YGDirectionLTR);

  ASSERT_EQ(markerCookie.start.marker, YGMarkerLayout);
  ASSERT_EQ(markerCookie.start.node, root.get());
}

void* MarkerTest::startMarker(
    YGMarker marker,
    YGNodeRef node,
    YGMarkerData data) {
  markerCookie.start = {marker, node, data};
  return &markerCookie;
}

void MarkerTest::endMarker(
    YGMarker marker,
    YGNodeRef node,
    YGMarkerData data,
    void* id) {
  markerCookie.end = {{marker, node, data}, id};
}

uniquePtr<YGConfig> MarkerTest::makeConfig() {
  auto c = uniquePtr<YGConfig>{YGConfigNew(), &YGConfigFree};
  YGConfigSetMarkerCallbacks(c.get(), {startMarker, endMarker});
  return c;
}

uniquePtr<YGNode> MarkerTest::makeNode(uniquePtr<YGConfig>& config) {
  auto n = uniquePtr<YGNode>{YGNodeNewWithConfig(config.get()), &YGNodeFree};
  return n;
}

void MarkerTest::SetUp() {
  markerCookie = {};
}

decltype(MarkerTest::markerCookie) MarkerTest::markerCookie = {};

} // namespace test
} // namespace marker
} // namespace yoga
} // namespace facebook
