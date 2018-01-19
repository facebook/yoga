/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 *
 * @format
 */

var target = typeof global !== 'undefined' ? global : window;

target.getMeasureCounter = function(Yoga, cb, staticWidth, staticHeight) {
  var counter = 0;

  return {
    inc: function(width, widthMode, height, heightMode) {
      counter += 1;

      return cb
        ? cb(width, widthMode, height, heightMode)
        : {width: staticWidth, height: staticHeight};
    },

    get: function() {
      return counter;
    },
  };
};

target.getMeasureCounterMax = function(Yoga) {
  return getMeasureCounter(Yoga, function(
    width,
    widthMode,
    height,
    heightMode,
  ) {
    var measuredWidth = widthMode === Yoga.MEASURE_MODE_UNDEFINED ? 10 : width;
    var measuredHeight =
      heightMode === Yoga.MEASURE_MODE_UNDEFINED ? 10 : height;

    return {width: measuredWidth, height: measuredHeight};
  });
};

target.getMeasureCounterMin = function(Yoga) {
  return getMeasureCounter(Yoga, function(
    width,
    widthMode,
    height,
    heightMode,
  ) {
    var measuredWidth =
      widthMode === Yoga.MEASURE_MODE_UNDEFINED ||
      (widthMode == Yoga.MEASURE_MODE_AT_MOST && width > 10)
        ? 10
        : width;
    var measuredHeight =
      heightMode === Yoga.MEASURE_MODE_UNDEFINED ||
      (heightMode == Yoga.MEASURE_MODE_AT_MOST && height > 10)
        ? 10
        : height;

    return {width: measuredWidth, height: measuredHeight};
  });
};
