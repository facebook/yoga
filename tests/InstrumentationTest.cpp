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

bool operator==(const YGMarkerLayoutData&, const YGMarkerLayoutData&);
void PrintTo(const YGMarkerLayoutData, std::ostream*);

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
    union {
      YGMarkerLayoutData layout;
    } markerData;
  };

  static struct {
    Data start;
    EndData end;
  } markerCookie;

  static void* startMarker(YGMarker, YGNodeRef, YGMarkerData);
  static void endMarker(YGMarker, YGNodeRef, YGMarkerData, void*);
  uniquePtr<YGNode> makeNode();
  uniquePtr<YGNode> addChild(uniquePtr<YGNode>& owner);
  static void calculateLayout(
      uniquePtr<YGNode>& node,
      float width = YGUndefined,
      float height = YGUndefined);

  void SetUp() override;
  uniquePtr<YGConfig> config;
};

TEST_F(MarkerTest, marker_start_works) {
  auto root = makeNode();

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
  auto root = makeNode();

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
  auto root = makeNode();

  calculateLayout(root);

  ASSERT_EQ(markerCookie.start.marker, YGMarkerLayout);
  ASSERT_EQ(markerCookie.start.node, root.get());
}

TEST_F(MarkerTest, layout_marker_counts_single_node_layout) {
  auto root = makeNode();

  calculateLayout(root);

  ASSERT_EQ(
      markerCookie.end.markerData.layout,
      (YGMarkerLayoutData{.layouts = 1, .measures = 0, .maxMeasureCache = 1}));
}

TEST_F(MarkerTest, layout_marker_counts_multi_node_layout) {
  auto root = makeNode();
  auto childA = addChild(root);
  auto childB = addChild(root);

  calculateLayout(root);

  ASSERT_EQ(
      markerCookie.end.markerData.layout,
      (YGMarkerLayoutData{.layouts = 3, .measures = 4, .maxMeasureCache = 3}));
}

TEST_F(MarkerTest, layout_marker_counts_cache_hits_single_node_layout) {
  auto root = makeNode();
  calculateLayout(root);

  calculateLayout(root);

  ASSERT_EQ(
      markerCookie.end.markerData.layout,
      (YGMarkerLayoutData{.layouts = 0,
                          .measures = 0,
                          .cachedLayouts = 1,
                          .cachedMeasures = 0}));
}

TEST_F(MarkerTest, layout_marker_counts_cache_hits_multi_node_layout) {
  auto root = makeNode();
  auto childA = addChild(root);
  auto childB = addChild(root);
  calculateLayout(root, 987, 654);
  calculateLayout(root, 123, 456);

  calculateLayout(root, 987, 654);

  ASSERT_EQ(
      markerCookie.end.markerData.layout,
      (YGMarkerLayoutData{.layouts = 3,
                          .measures = 0,
                          .maxMeasureCache = 5,
                          .cachedLayouts = 0,
                          .cachedMeasures = 4}));
}

TEST_F(MarkerTest, layout_marker_has_max_measure_cache) {
  auto root = makeNode();
  auto a = addChild(root);
  auto b = addChild(root);
  YGNodeStyleSetFlexBasis(a.get(), 10.0f);

  for (auto s : {20, 30, 40}) {
    calculateLayout(root, s, s);
  }

  ASSERT_EQ(
      markerCookie.end.markerData.layout,
      (YGMarkerLayoutData{.layouts = 3, .measures = 3, .maxMeasureCache = 7}));
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
  markerCookie.end = {{marker, node, data}, id, {}};
  switch (marker) {
    case YGMarkerLayout:
      markerCookie.end.markerData.layout = *marker::data<YGMarkerLayout>(data);
      break;
  };
}

uniquePtr<YGNode> MarkerTest::makeNode() {
  auto n = uniquePtr<YGNode>{YGNodeNewWithConfig(config.get()), &YGNodeFree};
  return n;
}

uniquePtr<YGNode> MarkerTest::addChild(uniquePtr<YGNode>& owner) {
  auto n = makeNode();
  YGNodeInsertChild(owner.get(), n.get(), YGNodeGetChildCount(owner.get()));
  return n;
}

void MarkerTest::calculateLayout(
    uniquePtr<YGNode>& node,
    float width,
    float height) {
  YGNodeCalculateLayout(node.get(), width, height, YGDirectionLTR);
}

void MarkerTest::SetUp() {
  markerCookie = {};

  config = uniquePtr<YGConfig>{YGConfigNew(), &YGConfigFree};
  YGConfigSetMarkerCallbacks(config.get(), {startMarker, endMarker});
}

decltype(MarkerTest::markerCookie) MarkerTest::markerCookie = {};

} // namespace test
} // namespace marker
} // namespace yoga
} // namespace facebook

bool operator==(const YGMarkerLayoutData& lhs, const YGMarkerLayoutData& rhs) {
  return lhs.layouts == rhs.layouts && lhs.measures == rhs.measures &&
      lhs.maxMeasureCache == rhs.maxMeasureCache &&
      lhs.cachedLayouts == rhs.cachedLayouts &&
      lhs.cachedMeasures == rhs.cachedMeasures;
}

void PrintTo(const YGMarkerLayoutData data, std::ostream* os) {
  *os << "YGMarkerLayoutData{ layouts = " << data.layouts
      << ", measures = " << data.measures
      << ", maxMeasureCache = " << data.maxMeasureCache
      << ", cachedLayouts = " << data.cachedLayouts
      << ", cachedMeasures = " << data.cachedMeasures << " }";
}
