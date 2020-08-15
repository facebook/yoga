/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#pragma once

#include <assert.h>
#include <math.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef __cplusplus
#include <stdbool.h>
#endif

#include "YGEnums.h"
#include "YGMacros.h"
#include "YGValue.h"

YG_EXTERN_C_BEGIN

typedef struct YGSize {
  YGFloat width;
  YGFloat height;
} YGSize;

typedef struct YGConfig* YGConfigRef;

typedef struct YGNode* YGNodeRef;
typedef const struct YGNode* YGNodeConstRef;

typedef YGSize (*YGMeasureFunc)(
    YGNodeRef node,
    YGFloat width,
    YGMeasureMode widthMode,
    YGFloat height,
    YGMeasureMode heightMode);
typedef YGFloat (*YGBaselineFunc)(YGNodeRef node, YGFloat width, YGFloat height);
typedef void (*YGDirtiedFunc)(YGNodeRef node);
typedef void (*YGPrintFunc)(YGNodeRef node);
typedef void (*YGNodeCleanupFunc)(YGNodeRef node);
typedef int (*YGLogger)(
    YGConfigRef config,
    YGNodeRef node,
    YGLogLevel level,
    const char* format,
    va_list args);
typedef YGNodeRef (
    *YGCloneNodeFunc)(YGNodeRef oldNode, YGNodeRef owner, int childIndex);

// YGNode
WIN_EXPORT YGNodeRef YGNodeNew(void);
WIN_EXPORT YGNodeRef YGNodeNewWithConfig(YGConfigRef config);
WIN_EXPORT YGNodeRef YGNodeClone(YGNodeRef node);
WIN_EXPORT void YGNodeFree(YGNodeRef node);
WIN_EXPORT void YGNodeFreeRecursiveWithCleanupFunc(
    YGNodeRef node,
    YGNodeCleanupFunc cleanup);
WIN_EXPORT void YGNodeFreeRecursive(YGNodeRef node);
WIN_EXPORT void YGNodeReset(YGNodeRef node);

WIN_EXPORT void YGNodeInsertChild(
    YGNodeRef node,
    YGNodeRef child,
    uint32_t index);

WIN_EXPORT void YGNodeSwapChild(
    YGNodeRef node,
    YGNodeRef child,
    uint32_t index);

WIN_EXPORT void YGNodeRemoveChild(YGNodeRef node, YGNodeRef child);
WIN_EXPORT void YGNodeRemoveAllChildren(YGNodeRef node);
WIN_EXPORT YGNodeRef YGNodeGetChild(YGNodeRef node, uint32_t index);
WIN_EXPORT YGNodeRef YGNodeGetOwner(YGNodeRef node);
WIN_EXPORT YGNodeRef YGNodeGetParent(YGNodeRef node);
WIN_EXPORT uint32_t YGNodeGetChildCount(YGNodeRef node);
WIN_EXPORT void YGNodeSetChildren(
    YGNodeRef owner,
    const YGNodeRef children[],
    uint32_t count);

WIN_EXPORT void YGNodeSetIsReferenceBaseline(
    YGNodeRef node,
    bool isReferenceBaseline);

WIN_EXPORT bool YGNodeIsReferenceBaseline(YGNodeRef node);

WIN_EXPORT void YGNodeCalculateLayout(
    YGNodeRef node,
    YGFloat availableWidth,
    YGFloat availableHeight,
    YGDirection ownerDirection);

// Mark a node as dirty. Only valid for nodes with a custom measure function
// set.
//
// Yoga knows when to mark all other nodes as dirty but because nodes with
// measure functions depend on information not known to Yoga they must perform
// this dirty marking manually.
WIN_EXPORT void YGNodeMarkDirty(YGNodeRef node);

// Marks the current node and all its descendants as dirty.
//
// Intended to be used for Uoga benchmarks. Don't use in production, as calling
// `YGCalculateLayout` will cause the recalculation of each and every node.
WIN_EXPORT void YGNodeMarkDirtyAndPropogateToDescendants(YGNodeRef node);

WIN_EXPORT void YGNodePrint(YGNodeRef node, YGPrintOptions options);

WIN_EXPORT bool YGFloatIsUndefined(YGFloat value);

WIN_EXPORT bool YGNodeCanUseCachedMeasurement(
    YGMeasureMode widthMode,
    YGFloat width,
    YGMeasureMode heightMode,
    YGFloat height,
    YGMeasureMode lastWidthMode,
    YGFloat lastWidth,
    YGMeasureMode lastHeightMode,
    YGFloat lastHeight,
    YGFloat lastComputedWidth,
    YGFloat lastComputedHeight,
    YGFloat marginRow,
    YGFloat marginColumn,
    YGConfigRef config);

WIN_EXPORT void YGNodeCopyStyle(YGNodeRef dstNode, YGNodeRef srcNode);

WIN_EXPORT void* YGNodeGetContext(YGNodeRef node);
WIN_EXPORT void YGNodeSetContext(YGNodeRef node, void* context);
void YGConfigSetPrintTreeFlag(YGConfigRef config, bool enabled);
bool YGNodeHasMeasureFunc(YGNodeRef node);
WIN_EXPORT void YGNodeSetMeasureFunc(YGNodeRef node, YGMeasureFunc measureFunc);
bool YGNodeHasBaselineFunc(YGNodeRef node);
void YGNodeSetBaselineFunc(YGNodeRef node, YGBaselineFunc baselineFunc);
YGDirtiedFunc YGNodeGetDirtiedFunc(YGNodeRef node);
void YGNodeSetDirtiedFunc(YGNodeRef node, YGDirtiedFunc dirtiedFunc);
void YGNodeSetPrintFunc(YGNodeRef node, YGPrintFunc printFunc);
WIN_EXPORT bool YGNodeGetHasNewLayout(YGNodeRef node);
WIN_EXPORT void YGNodeSetHasNewLayout(YGNodeRef node, bool hasNewLayout);
YGNodeType YGNodeGetNodeType(YGNodeRef node);
void YGNodeSetNodeType(YGNodeRef node, YGNodeType nodeType);
WIN_EXPORT bool YGNodeIsDirty(YGNodeRef node);
bool YGNodeLayoutGetDidUseLegacyFlag(YGNodeRef node);

WIN_EXPORT void YGNodeStyleSetDirection(YGNodeRef node, YGDirection direction);
WIN_EXPORT YGDirection YGNodeStyleGetDirection(YGNodeConstRef node);

WIN_EXPORT void YGNodeStyleSetFlexDirection(
    YGNodeRef node,
    YGFlexDirection flexDirection);
WIN_EXPORT YGFlexDirection YGNodeStyleGetFlexDirection(YGNodeConstRef node);

WIN_EXPORT void YGNodeStyleSetJustifyContent(
    YGNodeRef node,
    YGJustify justifyContent);
WIN_EXPORT YGJustify YGNodeStyleGetJustifyContent(YGNodeConstRef node);

WIN_EXPORT void YGNodeStyleSetAlignContent(
    YGNodeRef node,
    YGAlign alignContent);
WIN_EXPORT YGAlign YGNodeStyleGetAlignContent(YGNodeConstRef node);

WIN_EXPORT void YGNodeStyleSetAlignItems(YGNodeRef node, YGAlign alignItems);
WIN_EXPORT YGAlign YGNodeStyleGetAlignItems(YGNodeConstRef node);

WIN_EXPORT void YGNodeStyleSetAlignSelf(YGNodeRef node, YGAlign alignSelf);
WIN_EXPORT YGAlign YGNodeStyleGetAlignSelf(YGNodeConstRef node);

WIN_EXPORT void YGNodeStyleSetPositionType(
    YGNodeRef node,
    YGPositionType positionType);
WIN_EXPORT YGPositionType YGNodeStyleGetPositionType(YGNodeConstRef node);

WIN_EXPORT void YGNodeStyleSetFlexWrap(YGNodeRef node, YGWrap flexWrap);
WIN_EXPORT YGWrap YGNodeStyleGetFlexWrap(YGNodeConstRef node);

WIN_EXPORT void YGNodeStyleSetOverflow(YGNodeRef node, YGOverflow overflow);
WIN_EXPORT YGOverflow YGNodeStyleGetOverflow(YGNodeConstRef node);

WIN_EXPORT void YGNodeStyleSetDisplay(YGNodeRef node, YGDisplay display);
WIN_EXPORT YGDisplay YGNodeStyleGetDisplay(YGNodeConstRef node);

WIN_EXPORT void YGNodeStyleSetFlex(YGNodeRef node, YGFloat flex);
WIN_EXPORT YGFloat YGNodeStyleGetFlex(YGNodeConstRef node);

WIN_EXPORT void YGNodeStyleSetFlexGrow(YGNodeRef node, YGFloat flexGrow);
WIN_EXPORT YGFloat YGNodeStyleGetFlexGrow(YGNodeConstRef node);

WIN_EXPORT void YGNodeStyleSetFlexShrink(YGNodeRef node, YGFloat flexShrink);
WIN_EXPORT YGFloat YGNodeStyleGetFlexShrink(YGNodeConstRef node);

WIN_EXPORT void YGNodeStyleSetFlexBasis(YGNodeRef node, YGFloat flexBasis);
WIN_EXPORT void YGNodeStyleSetFlexBasisPercent(YGNodeRef node, YGFloat flexBasis);
WIN_EXPORT void YGNodeStyleSetFlexBasisAuto(YGNodeRef node);
WIN_EXPORT YGValue YGNodeStyleGetFlexBasis(YGNodeConstRef node);

WIN_EXPORT void YGNodeStyleSetPosition(
    YGNodeRef node,
    YGEdge edge,
    YGFloat position);
WIN_EXPORT void YGNodeStyleSetPositionPercent(
    YGNodeRef node,
    YGEdge edge,
    YGFloat position);
WIN_EXPORT YGValue YGNodeStyleGetPosition(YGNodeConstRef node, YGEdge edge);

WIN_EXPORT void YGNodeStyleSetMargin(YGNodeRef node, YGEdge edge, YGFloat margin);
WIN_EXPORT void YGNodeStyleSetMarginPercent(
    YGNodeRef node,
    YGEdge edge,
    YGFloat margin);
WIN_EXPORT void YGNodeStyleSetMarginAuto(YGNodeRef node, YGEdge edge);
WIN_EXPORT YGValue YGNodeStyleGetMargin(YGNodeConstRef node, YGEdge edge);

WIN_EXPORT void YGNodeStyleSetPadding(
    YGNodeRef node,
    YGEdge edge,
    YGFloat padding);
WIN_EXPORT void YGNodeStyleSetPaddingPercent(
    YGNodeRef node,
    YGEdge edge,
    YGFloat padding);
WIN_EXPORT YGValue YGNodeStyleGetPadding(YGNodeConstRef node, YGEdge edge);

WIN_EXPORT void YGNodeStyleSetBorder(YGNodeRef node, YGEdge edge, YGFloat border);
WIN_EXPORT YGFloat YGNodeStyleGetBorder(YGNodeConstRef node, YGEdge edge);

WIN_EXPORT void YGNodeStyleSetWidth(YGNodeRef node, YGFloat width);
WIN_EXPORT void YGNodeStyleSetWidthPercent(YGNodeRef node, YGFloat width);
WIN_EXPORT void YGNodeStyleSetWidthAuto(YGNodeRef node);
WIN_EXPORT YGValue YGNodeStyleGetWidth(YGNodeConstRef node);

WIN_EXPORT void YGNodeStyleSetHeight(YGNodeRef node, YGFloat height);
WIN_EXPORT void YGNodeStyleSetHeightPercent(YGNodeRef node, YGFloat height);
WIN_EXPORT void YGNodeStyleSetHeightAuto(YGNodeRef node);
WIN_EXPORT YGValue YGNodeStyleGetHeight(YGNodeConstRef node);

WIN_EXPORT void YGNodeStyleSetMinWidth(YGNodeRef node, YGFloat minWidth);
WIN_EXPORT void YGNodeStyleSetMinWidthPercent(YGNodeRef node, YGFloat minWidth);
WIN_EXPORT YGValue YGNodeStyleGetMinWidth(YGNodeConstRef node);

WIN_EXPORT void YGNodeStyleSetMinHeight(YGNodeRef node, YGFloat minHeight);
WIN_EXPORT void YGNodeStyleSetMinHeightPercent(YGNodeRef node, YGFloat minHeight);
WIN_EXPORT YGValue YGNodeStyleGetMinHeight(YGNodeConstRef node);

WIN_EXPORT void YGNodeStyleSetMaxWidth(YGNodeRef node, YGFloat maxWidth);
WIN_EXPORT void YGNodeStyleSetMaxWidthPercent(YGNodeRef node, YGFloat maxWidth);
WIN_EXPORT YGValue YGNodeStyleGetMaxWidth(YGNodeConstRef node);

WIN_EXPORT void YGNodeStyleSetMaxHeight(YGNodeRef node, YGFloat maxHeight);
WIN_EXPORT void YGNodeStyleSetMaxHeightPercent(YGNodeRef node, YGFloat maxHeight);
WIN_EXPORT YGValue YGNodeStyleGetMaxHeight(YGNodeConstRef node);

// Yoga specific properties, not compatible with flexbox specification Aspect
// ratio control the size of the undefined dimension of a node. Aspect ratio is
// encoded as a floating point value width/height. e.g. A value of 2 leads to a
// node with a width twice the size of its height while a value of 0.5 gives the
// opposite effect.
//
// - On a node with a set width/height aspect ratio control the size of the
//   unset dimension
// - On a node with a set flex basis aspect ratio controls the size of the node
//   in the cross axis if unset
// - On a node with a measure function aspect ratio works as though the measure
//   function measures the flex basis
// - On a node with flex grow/shrink aspect ratio controls the size of the node
//   in the cross axis if unset
// - Aspect ratio takes min/max dimensions into account
WIN_EXPORT void YGNodeStyleSetAspectRatio(YGNodeRef node, YGFloat aspectRatio);
WIN_EXPORT YGFloat YGNodeStyleGetAspectRatio(YGNodeConstRef node);

WIN_EXPORT YGFloat YGNodeLayoutGetLeft(YGNodeRef node);
WIN_EXPORT YGFloat YGNodeLayoutGetTop(YGNodeRef node);
WIN_EXPORT YGFloat YGNodeLayoutGetRight(YGNodeRef node);
WIN_EXPORT YGFloat YGNodeLayoutGetBottom(YGNodeRef node);
WIN_EXPORT YGFloat YGNodeLayoutGetWidth(YGNodeRef node);
WIN_EXPORT YGFloat YGNodeLayoutGetHeight(YGNodeRef node);
WIN_EXPORT YGDirection YGNodeLayoutGetDirection(YGNodeRef node);
WIN_EXPORT bool YGNodeLayoutGetHadOverflow(YGNodeRef node);
bool YGNodeLayoutGetDidLegacyStretchFlagAffectLayout(YGNodeRef node);

// Get the computed values for these nodes after performing layout. If they were
// set using point values then the returned value will be the same as
// YGNodeStyleGetXXX. However if they were set using a percentage value then the
// returned value is the computed value used during layout.
WIN_EXPORT YGFloat YGNodeLayoutGetMargin(YGNodeRef node, YGEdge edge);
WIN_EXPORT YGFloat YGNodeLayoutGetBorder(YGNodeRef node, YGEdge edge);
WIN_EXPORT YGFloat YGNodeLayoutGetPadding(YGNodeRef node, YGEdge edge);

WIN_EXPORT void YGConfigSetLogger(YGConfigRef config, YGLogger logger);
WIN_EXPORT void YGAssert(bool condition, const char* message);
WIN_EXPORT void YGAssertWithNode(
    YGNodeRef node,
    bool condition,
    const char* message);
WIN_EXPORT void YGAssertWithConfig(
    YGConfigRef config,
    bool condition,
    const char* message);
// Set this to number of pixels in 1 point to round calculation results If you
// want to avoid rounding - set PointScaleFactor to 0
WIN_EXPORT void YGConfigSetPointScaleFactor(
    YGConfigRef config,
    YGFloat pixelsInPoint);
void YGConfigSetShouldDiffLayoutWithoutLegacyStretchBehaviour(
    YGConfigRef config,
    bool shouldDiffLayout);

// Yoga previously had an error where containers would take the maximum space
// possible instead of the minimum like they are supposed to. In practice this
// resulted in implicit behaviour similar to align-self: stretch; Because this
// was such a long-standing bug we must allow legacy users to switch back to
// this behaviour.
WIN_EXPORT void YGConfigSetUseLegacyStretchBehaviour(
    YGConfigRef config,
    bool useLegacyStretchBehaviour);

// YGConfig
WIN_EXPORT YGConfigRef YGConfigNew(void);
WIN_EXPORT void YGConfigFree(YGConfigRef config);
WIN_EXPORT void YGConfigCopy(YGConfigRef dest, YGConfigRef src);
WIN_EXPORT int32_t YGConfigGetInstanceCount(void);

WIN_EXPORT void YGConfigSetExperimentalFeatureEnabled(
    YGConfigRef config,
    YGExperimentalFeature feature,
    bool enabled);
WIN_EXPORT bool YGConfigIsExperimentalFeatureEnabled(
    YGConfigRef config,
    YGExperimentalFeature feature);

// Using the web defaults is the preferred configuration for new projects. Usage
// of non web defaults should be considered as legacy.
WIN_EXPORT void YGConfigSetUseWebDefaults(YGConfigRef config, bool enabled);
WIN_EXPORT bool YGConfigGetUseWebDefaults(YGConfigRef config);

WIN_EXPORT void YGConfigSetCloneNodeFunc(
    YGConfigRef config,
    YGCloneNodeFunc callback);

// Export only for C#
WIN_EXPORT YGConfigRef YGConfigGetDefault(void);

WIN_EXPORT void YGConfigSetContext(YGConfigRef config, void* context);
WIN_EXPORT void* YGConfigGetContext(YGConfigRef config);

WIN_EXPORT YGFloat YGRoundValueToPixelGrid(
    double value,
    double pointScaleFactor,
    bool forceCeil,
    bool forceFloor);

YG_EXTERN_C_END

#ifdef __cplusplus
YG_EXTERN_CXX_BEGIN

#include <functional>
#include <vector>

// Calls f on each node in the tree including the given node argument.
void YGTraversePreOrder(
    YGNodeRef node,
    std::function<void(YGNodeRef node)>&& f);

void YGNodeSetChildren(YGNodeRef owner, const std::vector<YGNodeRef>& children);

YG_EXTERN_C_END
#endif
