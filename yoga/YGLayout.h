/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#ifdef __cplusplus

#include "BitUtils.h"
#include "YGFloatOptional.h"
#include "Yoga-internal.h"

struct YGLayout {
  std::array<float, 4> position = {};
  std::array<float, 2> dimensions = {{YGUndefined, YGUndefined}};
  std::array<float, 4> margin = {};
  std::array<float, 4> border = {};
  std::array<float, 4> padding = {};

private:
  static constexpr size_t directionOffset = 0;
  static constexpr size_t hadOverflowOffset =
      directionOffset + facebook::yoga::detail::bitWidthFn<YGDirection>();
  uint8_t flags = 0;

public:
  uint32_t computedFlexBasisGeneration = 0;
  YGFloatOptional computedFlexBasis = {};

  // Instead of recomputing the entire layout every single time, we cache some
  // information to break early when nothing changed
  uint32_t generationCount = 0;
  YGDirection lastOwnerDirection = YGDirectionInherit;

  uint32_t nextCachedMeasurementsIndex = 0;
  std::array<YGCachedMeasurement, YG_MAX_CACHED_RESULT_COUNT>
      cachedMeasurements = {};
  std::array<float, 2> measuredDimensions = {{YGUndefined, YGUndefined}};

  YGCachedMeasurement cachedLayout = YGCachedMeasurement();

  YGDirection direction() const {
    return facebook::yoga::detail::getEnumData<YGDirection>(
        flags, directionOffset);
  }

  void setDirection(YGDirection direction) {
    facebook::yoga::detail::setEnumData<YGDirection>(
        flags, directionOffset, direction);
  }

  bool hadOverflow() const {
    return facebook::yoga::detail::getBooleanData(flags, hadOverflowOffset);
  }
  void setHadOverflow(bool hadOverflow) {
    facebook::yoga::detail::setBooleanData(
        flags, hadOverflowOffset, hadOverflow);
  }

  bool operator==(YGLayout layout) const;
  bool operator!=(YGLayout layout) const { return !(*this == layout); }
};

#endif
