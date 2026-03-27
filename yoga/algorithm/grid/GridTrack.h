/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <yoga/style/GridTrackSize.h>

namespace facebook::yoga {

// Represents a resolved grid track size during layout computation. 
// Includes variables used by the track sizing algorithm.
// https://www.w3.org/TR/css-grid-1/#algo-track-sizing
struct GridTrack {
  GridTrackSize trackSize;
  float baseSize = 0.0f;
  float growthLimit = 0.0f;
  bool infinitelyGrowable = false;

  explicit GridTrack(const GridTrackSize& ts) : trackSize(ts) {}
};

} // namespace facebook::yoga
