/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * @format
 */

import type {MeasureFunction} from 'yoga-layout';
import Yoga from 'yoga-layout';

export type MeasureCounter = {
  inc: MeasureFunction;
  get: () => number;
};

export function getMeasureCounter(
  cb?: MeasureFunction | null,
  staticWidth = 0,
  staticHeight = 0,
): MeasureCounter {
  let counter = 0;

  return {
    inc: function (width, widthMode, height, heightMode) {
      counter += 1;

      return cb
        ? cb(width, widthMode, height, heightMode)
        : {width: staticWidth, height: staticHeight};
    },

    get: function () {
      return counter;
    },
  };
}

export function getMeasureCounterMax(): MeasureCounter {
  return getMeasureCounter((width, widthMode, height, heightMode) => {
    const measuredWidth =
      widthMode === Yoga.MEASURE_MODE_UNDEFINED ? 10 : width;
    const measuredHeight =
      heightMode === Yoga.MEASURE_MODE_UNDEFINED ? 10 : height;

    return {width: measuredWidth, height: measuredHeight};
  });
}

export function getMeasureCounterMin(): MeasureCounter {
  return getMeasureCounter((width, widthMode, height, heightMode) => {
    const measuredWidth =
      widthMode === Yoga.MEASURE_MODE_UNDEFINED ||
      (widthMode == Yoga.MEASURE_MODE_AT_MOST && width > 10)
        ? 10
        : width;
    const measuredHeight =
      heightMode === Yoga.MEASURE_MODE_UNDEFINED ||
      (heightMode == Yoga.MEASURE_MODE_AT_MOST && height > 10)
        ? 10
        : height;

    return {width: measuredWidth, height: measuredHeight};
  });
}
