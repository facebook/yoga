/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <yoga/YGMacros.h>
#include <yoga/YGNode.h>

YG_EXTERN_C_BEGIN

/**
 * Opaque handle to a grid track list for building grid-template-rows/columns.
 */
typedef struct YGGridTrackList* YGGridTrackListRef;

/**
 * Opaque handle to a grid track value.
 */
typedef struct YGGridTrackValue* YGGridTrackValueRef;

/**
 * Create a new grid track list.
 */
YG_EXPORT YGGridTrackListRef YGGridTrackListCreate(void);

/**
 * Free a grid track list.
 */
YG_EXPORT void YGGridTrackListFree(YGGridTrackListRef list);

/**
 * Add a track to the grid track list.
 */
YG_EXPORT void YGGridTrackListAddTrack(
    YGGridTrackListRef list,
    YGGridTrackValueRef trackValue);

/**
 * Create a grid track value with a points (px) length.
 */
YG_EXPORT YGGridTrackValueRef YGGridTrackPoints(float points);

/**
 * Create a grid track value with a percentage length.
 */
YG_EXPORT YGGridTrackValueRef YGGridTrackPercent(float percent);

/**
 * Create a grid track value with a flexible (fr) length.
 */
YG_EXPORT YGGridTrackValueRef YGGridTrackFr(float fr);

/**
 * Create a grid track value with auto sizing.
 */
YG_EXPORT YGGridTrackValueRef YGGridTrackAuto(void);

/**
 * Create a grid track value with minmax(min, max) sizing.
 */
YG_EXPORT YGGridTrackValueRef 
YGGridTrackMinMax(YGGridTrackValueRef min, YGGridTrackValueRef max);

YG_EXTERN_C_END
