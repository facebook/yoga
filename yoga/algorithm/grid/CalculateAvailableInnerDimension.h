/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
*/

#pragma once

#include <yoga/node/Node.h>
#include <yoga/enums/Dimension.h>
#include <yoga/enums/Direction.h>
#include <cfloat>

namespace facebook::yoga {

float calculateAvailableInnerDimension(
    const yoga::Node* const node,
    const Direction direction,
    const Dimension dimension,
    const float availableDim,
    const float paddingAndBorder,
    const float ownerDim,
    const float ownerWidth) {
  float availableInnerDim = availableDim - paddingAndBorder;
  // Max dimension overrides predefined dimension value; Min dimension in turn
  // overrides both of the above
  if (yoga::isDefined(availableInnerDim)) {
    // We want to make sure our available height does not violate min and max
    // constraints
    const FloatOptional minDimensionOptional =
        node->style().resolvedMinDimension(
            direction, dimension, ownerDim, ownerWidth);
    const float minInnerDim = minDimensionOptional.isUndefined()
        ? 0.0f
        : minDimensionOptional.unwrap() - paddingAndBorder;

    const FloatOptional maxDimensionOptional =
        node->style().resolvedMaxDimension(
            direction, dimension, ownerDim, ownerWidth);

    const float maxInnerDim = maxDimensionOptional.isUndefined()
        ? FLT_MAX
        : maxDimensionOptional.unwrap() - paddingAndBorder;
    availableInnerDim = yoga::maxOrDefined(
        yoga::minOrDefined(availableInnerDim, maxInnerDim), minInnerDim);
  }

  return availableInnerDim;
}

} // namespace facebook::yoga