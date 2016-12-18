/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

typedef NS_ENUM(NSInteger, YKFlexDirection) {
  YKFlexDirectionColumn,
  YKFlexDirectionColumnReverse,
  YKFlexDirectionRow,
  YKFlexDirectionRowReverse,
};

typedef NS_ENUM(NSInteger, YKMeasureMode) {
  YKMeasureModeUndefined,
  YKMeasureModeExactly,
  YKMeasureModeAtMost,
};

typedef NS_ENUM(NSInteger, YKPrintOptions) {
  YKPrintOptionsLayout = 1,
  YKPrintOptionsStyle = 2,
  YKPrintOptionsChildren = 4,
};

typedef NS_ENUM(NSInteger, YKEdge) {
  YKEdgeLeft,
  YKEdgeTop,
  YKEdgeRight,
  YKEdgeBottom,
  YKEdgeStart,
  YKEdgeEnd,
  YKEdgeHorizontal,
  YKEdgeVertical,
  YKEdgeAll,
};

typedef NS_ENUM(NSInteger, YKPositionType) {
  YKPositionTypeRelative,
  YKPositionTypeAbsolute,
};

typedef NS_ENUM(NSInteger, YKDimension) {
  YKDimensionWidth,
  YKDimensionHeight,
};

typedef NS_ENUM(NSInteger, YKJustify) {
  YKJustifyFlexStart,
  YKJustifyCenter,
  YKJustifyFlexEnd,
  YKJustifySpaceBetween,
  YKJustifySpaceAround,
};

typedef NS_ENUM(NSInteger, YKDirection) {
  YKDirectionInherit,
  YKDirectionLeftToRight,
  YKDirectionRightToLeft,
};

typedef NS_ENUM(NSInteger, YKLogLevel) {
  YKLogLevelError,
  YKLogLevelWarn,
  YKLogLevelInfo,
  YKLogLevelDebug,
  YKLogLevelVerbose,
};

typedef NS_ENUM(NSInteger, YKWrap) {
  YKWrapNoWrap,
  YKWrapWrap,
};

typedef NS_ENUM(NSInteger, YKOverflow) {
  YKOverflowVisible,
  YKOverflowHidden,
  YKOverflowScroll,
};

typedef NS_ENUM(NSInteger, YKExperimentalFeature) {
  YKExperimentalFeatureRounding,
  YKExperimentalFeatureWebFlexBasis,
};

typedef NS_ENUM(NSInteger, YKAlign) {
  YKAlignAuto,
  YKAlignFlexStart,
  YKAlignCenter,
  YKAlignFlexEnd,
  YKAlignStretch,
};

