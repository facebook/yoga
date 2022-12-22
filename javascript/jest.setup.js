/**
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 *
 * @format
 */

module.exports = async () => {
  global.Yoga = process.env['WASM']
    ? await require("./dist/index.wasm").initialize()
    : await require("./dist/index.asm").initialize();

  global.getMeasureCounter = function(Yoga, cb, staticWidth, staticHeight) {
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

  global.getMeasureCounterMax = function(Yoga) {
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

   global.getMeasureCounterMin = function(Yoga) {
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
}
