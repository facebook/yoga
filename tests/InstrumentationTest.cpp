/*
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
#include <deque>
#include <exception>
#include <functional>
#include <memory>
#include <string>

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

  struct MarkerCookie {
    Data start;
    EndData end;
  };

  // std::deque will keep pointers stable on reallocation, whereas std::vector
  // does not
  static std::deque<MarkerCookie> markerCookies;

  static void* startMarker(YGMarker, YGNodeRef, YGMarkerData);
  static void endMarker(YGMarker, YGNodeRef, YGMarkerData, void*);
  uniquePtr<YGNode> makeNode();
  uniquePtr<YGNode> addChild(uniquePtr<YGNode>& owner);
  static void calculateLayout(
      uniquePtr<YGNode>& node,
      float width = YGUndefined,
      float height = YGUndefined);
  static MarkerCookie& findMarker(YGMarker);
  static MarkerCookie& findLastMarker(YGMarker);

  void SetUp() override;
  void TearDown() override;
  uniquePtr<YGConfig> config;
};

TEST_F(MarkerTest, marker_start_works) {
  auto root = makeNode();

  decltype(MarkerSection<YGMarkerLayout>::data)* dataAddress;
  {
    MarkerSection<YGMarkerLayout> marker{root.get()};
    dataAddress = &marker.data;
  }

  auto& markerCookie = findLastMarker(YGMarkerLayout);

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

  auto& markerCookie = findLastMarker(YGMarkerLayout);

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

  auto& markerCookie = findLastMarker(YGMarkerLayout);

  ASSERT_EQ(markerCookie.start.marker, YGMarkerLayout);
  ASSERT_EQ(markerCookie.start.node, root.get());
}

TEST_F(MarkerTest, layout_marker_counts_single_node_layout) {
  auto root = makeNode();

  calculateLayout(root);

  auto& markerCookie = findLastMarker(YGMarkerLayout);

  ASSERT_EQ(
      markerCookie.end.markerData.layout,
      (YGMarkerLayoutData{.layouts = 1, .measures = 0, .maxMeasureCache = 1}));
}

TEST_F(MarkerTest, layout_marker_counts_multi_node_layout) {
  auto root = makeNode();
  auto childA = addChild(root);
  auto childB = addChild(root);

  calculateLayout(root);

  auto& markerCookie = findLastMarker(YGMarkerLayout);

  ASSERT_EQ(
      markerCookie.end.markerData.layout,
      (YGMarkerLayoutData{.layouts = 3, .measures = 4, .maxMeasureCache = 3}));
}

TEST_F(MarkerTest, layout_marker_counts_cache_hits_single_node_layout) {
  auto root = makeNode();
  calculateLayout(root);

  calculateLayout(root);

  auto& markerCookie = findLastMarker(YGMarkerLayout);

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

  auto& markerCookie = findLastMarker(YGMarkerLayout);

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

  auto& markerCookie = findLastMarker(YGMarkerLayout);

  ASSERT_EQ(
      markerCookie.end.markerData.layout,
      (YGMarkerLayoutData{.layouts = 3, .measures = 3, .maxMeasureCache = 7}));
}

TEST_F(MarkerTest, measure_functions_get_wrapped) {
  auto root = makeNode();
  YGNodeSetMeasureFunc(
      root.get(), [](YGNodeRef, float, YGMeasureMode, float, YGMeasureMode) {
        return YGSize{};
      });

  calculateLayout(root);
  auto& markerCookie = findLastMarker(YGMarkerMeasure);

  ASSERT_EQ(markerCookie.start.marker, YGMarkerMeasure)
      << "have " << markerCookies.size() << " recorded markers";
}

TEST_F(MarkerTest, baseline_functions_get_wrapped) {
  auto root = makeNode();
  auto child = addChild(root);
  YGNodeSetBaselineFunc(
      child.get(), [](YGNodeRef, float, float) { return 0.0f; });
  YGNodeStyleSetFlexDirection(root.get(), YGFlexDirectionRow);
  YGNodeStyleSetAlignItems(root.get(), YGAlignBaseline);

  calculateLayout(root);
  auto& markerCookie = findLastMarker(YGMarkerBaselineFn);

  ASSERT_EQ(markerCookie.start.marker, YGMarkerBaselineFn)
      << "have " << markerCookies.size() << " recorded markers";
}

void* MarkerTest::startMarker(
    YGMarker marker,
    YGNodeRef node,
    YGMarkerData data) {
  markerCookies.emplace_back();
  MarkerCookie* cookie = &markerCookies.back();
  cookie->start = {marker, node, data};
  return cookie;
}

void MarkerTest::endMarker(
    YGMarker marker,
    YGNodeRef node,
    YGMarkerData data,
    void* id) {
  auto cookie = static_cast<MarkerCookie*>(id);
  cookie->end = {{marker, node, data}, id, {}};
  switch (marker) {
    case YGMarkerLayout:
      cookie->end.markerData.layout = *marker::data<YGMarkerLayout>(data);
      break;
    case YGMarkerMeasure:
    case YGMarkerBaselineFn:
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

namespace {

const char* markerTypeName(YGMarker type) {
  switch (type) {
    case YGMarkerLayout:
      return "YGMarkerLayout";
    case YGMarkerMeasure:
      return "YGMarkerMeasure";
    case YGMarkerBaselineFn:
      return "YGMarkerBaselineFn";
  }
}

template <typename It>
MarkerTest::MarkerCookie& find(It begin, It end, YGMarker type) {
  auto result = std::find_if(begin, end, [type](MarkerTest::MarkerCookie& c) {
    return c.start.marker == type;
  });
  if (result == end) {
    throw std::runtime_error{std::string{"No marker recorded for type: "} +
                             markerTypeName(type)};
  }
  return *result;
}

} // namespace

MarkerTest::MarkerCookie& MarkerTest::findMarker(YGMarker markerType) {
  return find(markerCookies.begin(), markerCookies.end(), markerType);
}

MarkerTest::MarkerCookie& MarkerTest::findLastMarker(YGMarker markerType) {
  return find(markerCookies.rbegin(), markerCookies.rend(), markerType);
}

void MarkerTest::SetUp() {
  config = uniquePtr<YGConfig>{YGConfigNew(), &YGConfigFree};
  YGConfigSetMarkerCallbacks(config.get(), {startMarker, endMarker});
}

void MarkerTest::TearDown() {
  markerCookies.resize(0);
}

decltype(MarkerTest::markerCookies) MarkerTest::markerCookies = {};

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
