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

typedef enum YGFlexDirection {
  YGFlexDirectionColumn,
  YGFlexDirectionColumnReverse,
  YGFlexDirectionRow,
  YGFlexDirectionRowReverse,
} YGFlexDirection;

typedef enum YGMeasureMode {
  YGMeasureModeUndefined,
  YGMeasureModeExactly,
  YGMeasureModeAtMost,
} YGMeasureMode;

typedef enum YGPrintOptions {
  YGPrintOptionsLayout = 1,
  YGPrintOptionsStyle = 2,
  YGPrintOptionsChildren = 4,
} YGPrintOptions;

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

typedef enum YGPositionType {
  YGPositionTypeRelative,
  YGPositionTypeAbsolute,
} YGPositionType;

typedef enum YGDimension {
  YGDimensionWidth,
  YGDimensionHeight,
} YGDimension;

typedef enum YGJustify {
  YGJustifyFlexStart,
  YGJustifyCenter,
  YGJustifyFlexEnd,
  YGJustifySpaceBetween,
  YGJustifySpaceAround,
} YGJustify;

typedef enum YGDirection {
  YGDirectionInherit,
  YGDirectionLTR,
  YGDirectionRTL,
} YGDirection;

typedef enum YGLogLevel {
  YGLogLevelError,
  YGLogLevelWarn,
  YGLogLevelInfo,
  YGLogLevelDebug,
  YGLogLevelVerbose,
} YGLogLevel;

typedef enum YGWrap {
  YGWrapNoWrap,
  YGWrapWrap,
} YGWrap;

typedef enum YGOverflow {
  YGOverflowVisible,
  YGOverflowHidden,
  YGOverflowScroll,
} YGOverflow;

typedef enum YGExperimentalFeature {
  YGExperimentalFeatureRounding,
  YGExperimentalFeatureWebFlexBasis,
} YGExperimentalFeature;

typedef enum YGAlign {
  YGAlignAuto,
  YGAlignFlexStart,
  YGAlignCenter,
  YGAlignFlexEnd,
  YGAlignStretch,
} YGAlign;

YG_EXTERN_C_END
