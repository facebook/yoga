/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#pragma once

#include "YGMacros.h"

YG_EXTERN_C_BEGIN

#define YGFlexDirectionCount 4
#ifndef NS_ENUM
typedef enum YGFlexDirection {
  YGFlexDirectionColumn,
  YGFlexDirectionColumnReverse,
  YGFlexDirectionRow,
  YGFlexDirectionRowReverse,
} YGFlexDirection;
#else
typedef NS_ENUM(NSInteger, YGFlexDirection) {
  YGFlexDirectionColumn,
  YGFlexDirectionColumnReverse,
  YGFlexDirectionRow,
  YGFlexDirectionRowReverse,
};
#endif

#define YGMeasureModeCount 3
#ifndef NS_ENUM
typedef enum YGMeasureMode {
  YGMeasureModeUndefined,
  YGMeasureModeExactly,
  YGMeasureModeAtMost,
} YGMeasureMode;
#else
typedef NS_ENUM(NSInteger, YGMeasureMode) {
  YGMeasureModeUndefined,
  YGMeasureModeExactly,
  YGMeasureModeAtMost,
};
#endif

#define YGPrintOptionsCount 3
#ifndef NS_ENUM
typedef enum YGPrintOptions {
  YGPrintOptionsLayout = 1,
  YGPrintOptionsStyle = 2,
  YGPrintOptionsChildren = 4,
} YGPrintOptions;
#else
typedef NS_ENUM(NSInteger, YGPrintOptions) {
  YGPrintOptionsLayout = 1,
  YGPrintOptionsStyle = 2,
  YGPrintOptionsChildren = 4,
};
#endif

#define YGEdgeCount 9
#ifndef NS_ENUM
typedef enum YGEdge {
  YGEdgeLeft,
  YGEdgeTop,
  YGEdgeRight,
  YGEdgeBottom,
  YGEdgeStart,
  YGEdgeEnd,
  YGEdgeHorizontal,
  YGEdgeVertical,
  YGEdgeAll,
} YGEdge;
#else
typedef NS_ENUM(NSInteger, YGEdge) {
  YGEdgeLeft,
  YGEdgeTop,
  YGEdgeRight,
  YGEdgeBottom,
  YGEdgeStart,
  YGEdgeEnd,
  YGEdgeHorizontal,
  YGEdgeVertical,
  YGEdgeAll,
};
#endif

#define YGPositionTypeCount 2
#ifndef NS_ENUM
typedef enum YGPositionType {
  YGPositionTypeRelative,
  YGPositionTypeAbsolute,
} YGPositionType;
#else
typedef NS_ENUM(NSInteger, YGPositionType) {
  YGPositionTypeRelative,
  YGPositionTypeAbsolute,
};
#endif

#define YGDimensionCount 2
#ifndef NS_ENUM
typedef enum YGDimension {
  YGDimensionWidth,
  YGDimensionHeight,
} YGDimension;
#else
typedef NS_ENUM(NSInteger, YGDimension) {
  YGDimensionWidth,
  YGDimensionHeight,
};
#endif

#define YGJustifyCount 5
#ifndef NS_ENUM
typedef enum YGJustify {
  YGJustifyFlexStart,
  YGJustifyCenter,
  YGJustifyFlexEnd,
  YGJustifySpaceBetween,
  YGJustifySpaceAround,
} YGJustify;
#else
typedef NS_ENUM(NSInteger, YGJustify) {
  YGJustifyFlexStart,
  YGJustifyCenter,
  YGJustifyFlexEnd,
  YGJustifySpaceBetween,
  YGJustifySpaceAround,
};
#endif

#define YGDirectionCount 3
#ifndef NS_ENUM
typedef enum YGDirection {
  YGDirectionInherit,
  YGDirectionLTR,
  YGDirectionRTL,
} YGDirection;
#else
typedef NS_ENUM(NSInteger, YGDirection) {
  YGDirectionInherit,
  YGDirectionLTR,
  YGDirectionRTL,
};
#endif

#define YGLogLevelCount 5
#ifndef NS_ENUM
typedef enum YGLogLevel {
  YGLogLevelError,
  YGLogLevelWarn,
  YGLogLevelInfo,
  YGLogLevelDebug,
  YGLogLevelVerbose,
} YGLogLevel;
#else
typedef NS_ENUM(NSInteger, YGLogLevel) {
  YGLogLevelError,
  YGLogLevelWarn,
  YGLogLevelInfo,
  YGLogLevelDebug,
  YGLogLevelVerbose,
};
#endif

#define YGWrapCount 2
#ifndef NS_ENUM
typedef enum YGWrap {
  YGWrapNoWrap,
  YGWrapWrap,
} YGWrap;
#else
typedef NS_ENUM(NSInteger, YGWrap) {
  YGWrapNoWrap,
  YGWrapWrap,
};
#endif

#define YGOverflowCount 3
#ifndef NS_ENUM
typedef enum YGOverflow {
  YGOverflowVisible,
  YGOverflowHidden,
  YGOverflowScroll,
} YGOverflow;
#else
typedef NS_ENUM(NSInteger, YGOverflow) {
  YGOverflowVisible,
  YGOverflowHidden,
  YGOverflowScroll,
};
#endif

#define YGExperimentalFeatureCount 2
#ifndef NS_ENUM
typedef enum YGExperimentalFeature {
  YGExperimentalFeatureRounding,
  YGExperimentalFeatureWebFlexBasis,
} YGExperimentalFeature;
#else
typedef NS_ENUM(NSInteger, YGExperimentalFeature) {
  YGExperimentalFeatureRounding,
  YGExperimentalFeatureWebFlexBasis,
};
#endif

#define YGAlignCount 5
#ifndef NS_ENUM
typedef enum YGAlign {
  YGAlignAuto,
  YGAlignFlexStart,
  YGAlignCenter,
  YGAlignFlexEnd,
  YGAlignStretch,
} YGAlign;
#else
typedef NS_ENUM(NSInteger, YGAlign) {
  YGAlignAuto,
  YGAlignFlexStart,
  YGAlignCenter,
  YGAlignFlexEnd,
  YGAlignStretch,
};
#endif

#define YGUnitCount 3
#ifndef NS_ENUM
typedef enum YGUnit {
  YGUnitUndefined,
  YGUnitPixel,
  YGUnitPercent,
} YGUnit;
#else
typedef NS_ENUM(NSInteger, YGUnit) {
  YGUnitUndefined,
  YGUnitPixel,
  YGUnitPercent,
};
#endif

YG_EXTERN_C_END
