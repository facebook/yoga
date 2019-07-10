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
    case YGMarkerMeasure:
      return "YGMarkerMeasure";
    case YGMarkerBaselineFn:
      return "YGMarkerBaselineFn";
  }
  return "";
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
