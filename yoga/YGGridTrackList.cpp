/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <yoga/YGGridTrackList.h>
#include <yoga/node/Node.h>
#include <yoga/style/GridTrack.h>
#include <yoga/style/StyleSizeLength.h>
#include <memory>
#include <vector>

using namespace facebook::yoga;

struct YGGridTrackValue {
  enum class Type { Points, Percent, Fr, Auto, MinMax };

  Type type;
  float value;
  std::unique_ptr<YGGridTrackValue> minValue;
  std::unique_ptr<YGGridTrackValue> maxValue;

  YGGridTrackValue(Type t, float v = 0.0f) : type(t), value(v) {}

  YGGridTrackValue(
      std::unique_ptr<YGGridTrackValue> min,
      std::unique_ptr<YGGridTrackValue> max)
      : type(Type::MinMax),
        value(0.0f),
        minValue(std::move(min)),
        maxValue(std::move(max)) {}

  StyleSizeLength toStyleSizeLength() const {
    switch (type) {
      case Type::Points:
        return StyleSizeLength::points(value);
      case Type::Percent:
        return StyleSizeLength::percent(value);
      case Type::Fr:
        return StyleSizeLength::stretch(value);
      case Type::Auto:
        return StyleSizeLength::ofAuto();
      case Type::MinMax:
        // MinMax should not call this, it needs special handling
        return StyleSizeLength::ofAuto();
    }
    return StyleSizeLength::ofAuto();
  }
};

struct YGGridTrackList {
  std::vector<std::unique_ptr<YGGridTrackValue>> tracks;

  YGGridTrackList() = default;
  YGGridTrackList(const YGGridTrackList&) = delete;
  YGGridTrackList& operator=(const YGGridTrackList&) = delete;
  YGGridTrackList(YGGridTrackList&&) = delete;
  YGGridTrackList& operator=(YGGridTrackList&&) = delete;

  GridTrackList toGridTrackList() const {
    GridTrackList result;
    result.reserve(tracks.size());

    for (const auto& track : tracks) {
      if (track->type == YGGridTrackValue::Type::MinMax) {
        auto min = track->minValue->toStyleSizeLength();
        auto max = track->maxValue->toStyleSizeLength();
        result.push_back(GridTrackSize::minmax(min, max));
      } else {
        switch (track->type) {
          case YGGridTrackValue::Type::Points:
            result.push_back(GridTrackSize::length(track->value));
            break;
          case YGGridTrackValue::Type::Percent:
            result.push_back(GridTrackSize::percent(track->value));
            break;
          case YGGridTrackValue::Type::Fr:
            result.push_back(GridTrackSize::fr(track->value));
            break;
          case YGGridTrackValue::Type::Auto:
            result.push_back(GridTrackSize::auto_());
            break;
          case YGGridTrackValue::Type::MinMax:
            // Already handled above
            break;
        }
      }
    }

    return result;
  }
};

YGGridTrackListRef YGGridTrackListCreate() {
  return new YGGridTrackList();
}

void YGGridTrackListFree(YGGridTrackListRef list) {
  delete list;
}

void YGGridTrackListAddTrack(
    YGGridTrackListRef list,
    YGGridTrackValueRef trackValue) {
  if (list && trackValue) {
    list->tracks.push_back(std::unique_ptr<YGGridTrackValue>(trackValue));
  }
}

YGGridTrackValueRef YGGridTrackPoints(float points) {
  return new YGGridTrackValue(YGGridTrackValue::Type::Points, points);
}

YGGridTrackValueRef YGGridTrackPercent(float percent) {
  return new YGGridTrackValue(YGGridTrackValue::Type::Percent, percent);
}

YGGridTrackValueRef YGGridTrackFr(float fr) {
  return new YGGridTrackValue(YGGridTrackValue::Type::Fr, fr);
}

YGGridTrackValueRef YGGridTrackAuto() {
  return new YGGridTrackValue(YGGridTrackValue::Type::Auto);
}

YGGridTrackValueRef
YGGridTrackMinMax(YGGridTrackValueRef min, YGGridTrackValueRef max) {
  return new YGGridTrackValue(
      std::unique_ptr<YGGridTrackValue>(min),
      std::unique_ptr<YGGridTrackValue>(max));
}

void YGNodeStyleSetGridTemplateRows(
    YGNodeRef node,
    YGGridTrackListRef trackList) {
  if (node && trackList) {
    auto* n = resolveRef(node);
    n->style().setGridTemplateRows(trackList->toGridTrackList());
    n->markDirtyAndPropagate();
  }
}

void YGNodeStyleSetGridTemplateColumns(
    YGNodeRef node,
    YGGridTrackListRef trackList) {
  if (node && trackList) {
    auto* n = resolveRef(node);
    n->style().setGridTemplateColumns(trackList->toGridTrackList());
    n->markDirtyAndPropagate();
  }
}

void YGNodeStyleSetGridAutoRows(YGNodeRef node, YGGridTrackListRef trackList) {
  if (node && trackList) {
    auto* n = resolveRef(node);
    n->style().setGridAutoRows(trackList->toGridTrackList());
    n->markDirtyAndPropagate();
  }
}

void YGNodeStyleSetGridAutoColumns(
    YGNodeRef node,
    YGGridTrackListRef trackList) {
  if (node && trackList) {
    auto* n = resolveRef(node);
    n->style().setGridAutoColumns(trackList->toGridTrackList());
    n->markDirtyAndPropagate();
  }
}
