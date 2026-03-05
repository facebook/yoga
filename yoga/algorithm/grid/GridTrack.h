/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <yoga/style/GridTrack.h>

namespace facebook::yoga {

struct GridTrack : GridTrackSize {
  float baseSize = 0.0f;
  float growthLimit = 0.0f;
  bool infinitelyGrowable = false;

  explicit GridTrack(const GridTrackSize& trackSize)
      : GridTrackSize(trackSize) {}
};

} // namespace facebook::yoga
