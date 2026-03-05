/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <emscripten/emscripten.h>
#include <yoga/Yoga.h>

// Static buffer for returning YGValue structs to JS.
// JS reads buf[0] as float (value) and buf[1] as int (unit) via HEAPF32/HEAP32.
// Safe because WASM is single-threaded.
static float ygvalue_buf[2];

static void writeYGValue(YGValue v) {
  ygvalue_buf[0] = v.value;
  // Store unit as integer bits in a float slot; JS reads via HEAP32.
  ((int*)ygvalue_buf)[1] = (int)v.unit;
}

EMSCRIPTEN_KEEPALIVE float* jswrap_YGValueBuffer(void) {
  return ygvalue_buf;
}

// --- YGValue getter wrappers ---

EMSCRIPTEN_KEEPALIVE void jswrap_YGNodeStyleGetWidth(YGNodeConstRef node) {
  writeYGValue(YGNodeStyleGetWidth(node));
}

EMSCRIPTEN_KEEPALIVE void jswrap_YGNodeStyleGetHeight(YGNodeConstRef node) {
  writeYGValue(YGNodeStyleGetHeight(node));
}

EMSCRIPTEN_KEEPALIVE void jswrap_YGNodeStyleGetPosition(
    YGNodeConstRef node,
    YGEdge edge) {
  writeYGValue(YGNodeStyleGetPosition(node, edge));
}

EMSCRIPTEN_KEEPALIVE void jswrap_YGNodeStyleGetMargin(
    YGNodeConstRef node,
    YGEdge edge) {
  writeYGValue(YGNodeStyleGetMargin(node, edge));
}

EMSCRIPTEN_KEEPALIVE void jswrap_YGNodeStyleGetPadding(
    YGNodeConstRef node,
    YGEdge edge) {
  writeYGValue(YGNodeStyleGetPadding(node, edge));
}

EMSCRIPTEN_KEEPALIVE void jswrap_YGNodeStyleGetFlexBasis(YGNodeConstRef node) {
  writeYGValue(YGNodeStyleGetFlexBasis(node));
}

EMSCRIPTEN_KEEPALIVE void jswrap_YGNodeStyleGetMinWidth(YGNodeConstRef node) {
  writeYGValue(YGNodeStyleGetMinWidth(node));
}

EMSCRIPTEN_KEEPALIVE void jswrap_YGNodeStyleGetMinHeight(YGNodeConstRef node) {
  writeYGValue(YGNodeStyleGetMinHeight(node));
}

EMSCRIPTEN_KEEPALIVE void jswrap_YGNodeStyleGetMaxWidth(YGNodeConstRef node) {
  writeYGValue(YGNodeStyleGetMaxWidth(node));
}

EMSCRIPTEN_KEEPALIVE void jswrap_YGNodeStyleGetMaxHeight(YGNodeConstRef node) {
  writeYGValue(YGNodeStyleGetMaxHeight(node));
}

EMSCRIPTEN_KEEPALIVE void jswrap_YGNodeStyleGetGap(
    YGNodeConstRef node,
    YGGutter gutter) {
  writeYGValue(YGNodeStyleGetGap(node, gutter));
}

// --- Measure callback bridge ---
// Uses EM_JS to call into a JS-side Map<nodePtr, callback> stored on Module.

EM_JS(
    float,
    callMeasureFunc,
    (YGNodeConstRef nodePtr,
     float width,
     int widthMode,
     float height,
     int heightMode,
     int returnWidthOrHeight),
    {
      // clang-format off
      var fn = Module["_yogaMeasureFuncs"].get(nodePtr);
      if (!fn)
        return 0;
      if (!fn._cachedResult || fn._cachedWidth !== width || fn._cachedWidthMode !== widthMode || fn._cachedHeight !== height || fn._cachedHeightMode !== heightMode) {
        fn._cachedResult = fn(width, widthMode, height, heightMode);
        fn._cachedWidth = width;
        fn._cachedWidthMode = widthMode;
        fn._cachedHeight = height;
        fn._cachedHeightMode = heightMode;
      }
      var result = fn._cachedResult;
      if (returnWidthOrHeight === 0) {
        var w = result.width;
        return (w === undefined || w === null) ? NaN : +w;
      } else {
        var h = result.height;
        return (h === undefined || h === null) ? NaN : +h;
      }
      // clang-format on
    });

static YGSize globalMeasureFunc(
    YGNodeConstRef nodeRef,
    float width,
    YGMeasureMode widthMode,
    float height,
    YGMeasureMode heightMode) {
  YGSize size;
  size.width = callMeasureFunc(
      nodeRef, width, (int)widthMode, height, (int)heightMode, 0);
  size.height = callMeasureFunc(
      nodeRef, width, (int)widthMode, height, (int)heightMode, 1);
  return size;
}

EMSCRIPTEN_KEEPALIVE void jswrap_YGNodeSetMeasureFunc(YGNodeRef node) {
  YGNodeSetMeasureFunc(node, &globalMeasureFunc);
}

EMSCRIPTEN_KEEPALIVE void jswrap_YGNodeUnsetMeasureFunc(YGNodeRef node) {
  YGNodeSetMeasureFunc(node, NULL);
}

// --- Dirtied callback bridge ---

EM_JS(void, callDirtiedFunc, (YGNodeConstRef nodePtr), {
  var fn = Module["_yogaDirtiedFuncs"].get(nodePtr);
  if (fn)
    fn();
});

static void globalDirtiedFunc(YGNodeConstRef nodeRef) {
  callDirtiedFunc(nodeRef);
}

EMSCRIPTEN_KEEPALIVE void jswrap_YGNodeSetDirtiedFunc(YGNodeRef node) {
  YGNodeSetDirtiedFunc(node, &globalDirtiedFunc);
}

EMSCRIPTEN_KEEPALIVE void jswrap_YGNodeUnsetDirtiedFunc(YGNodeRef node) {
  YGNodeSetDirtiedFunc(node, NULL);
}
