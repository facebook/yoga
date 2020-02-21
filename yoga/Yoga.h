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
  float width;
  float height;
} YGSize;

typedef struct YGConfig* YGConfigRef;

typedef struct YGNode* YGNodeRef;
typedef const struct YGNode* YGNodeConstRef;

typedef YGSize (__cdecl *YGMeasureFunc)(
    YGNodeRef node,
    float width,
    YGMeasureMode widthMode,
    float height,
    YGMeasureMode heightMode);
typedef float (__cdecl *YGBaselineFunc)(YGNodeRef node, float width, float height);
typedef void (__cdecl *YGDirtiedFunc)(YGNodeRef node);
typedef void (__cdecl *YGPrintFunc)(YGNodeRef node);
typedef void (__cdecl *YGNodeCleanupFunc)(YGNodeRef node);
typedef int (__cdecl *YGLogger)(
    YGConfigRef config,
    YGNodeRef node,
    YGLogLevel level,
    const char* format,
    va_list args);
typedef YGNodeRef (
    *YGCloneNodeFunc)(YGNodeRef oldNode, YGNodeRef owner, int childIndex);

// YGNode
WIN_EXPORT YGNodeRef __cdecl YGNodeNew(void);
WIN_EXPORT YGNodeRef __cdecl YGNodeNewWithConfig(YGConfigRef config);
WIN_EXPORT YGNodeRef __cdecl YGNodeClone(YGNodeRef node);
WIN_EXPORT void __cdecl YGNodeFree(YGNodeRef node);
WIN_EXPORT void __cdecl YGNodeFreeRecursiveWithCleanupFunc(
    YGNodeRef node,
    YGNodeCleanupFunc cleanup);
WIN_EXPORT void __cdecl YGNodeFreeRecursive(YGNodeRef node);
WIN_EXPORT void __cdecl YGNodeReset(YGNodeRef node);

WIN_EXPORT void __cdecl YGNodeInsertChild(
    YGNodeRef node,
    YGNodeRef child,
    uint32_t index);

WIN_EXPORT void __cdecl YGNodeSwapChild(
    YGNodeRef node,
    YGNodeRef child,
    uint32_t index);

WIN_EXPORT void __cdecl YGNodeRemoveChild(YGNodeRef node, YGNodeRef child);
WIN_EXPORT void __cdecl YGNodeRemoveAllChildren(YGNodeRef node);
WIN_EXPORT YGNodeRef __cdecl YGNodeGetChild(YGNodeRef node, uint32_t index);
WIN_EXPORT YGNodeRef __cdecl YGNodeGetOwner(YGNodeRef node);
WIN_EXPORT YGNodeRef __cdecl YGNodeGetParent(YGNodeRef node);
WIN_EXPORT uint32_t __cdecl YGNodeGetChildCount(YGNodeRef node);
WIN_EXPORT void __cdecl YGNodeSetChildren(
    YGNodeRef owner,
    const YGNodeRef children[],
    uint32_t count);

WIN_EXPORT void __cdecl YGNodeSetIsReferenceBaseline(
    YGNodeRef node,
    bool isReferenceBaseline);

WIN_EXPORT bool __cdecl YGNodeIsReferenceBaseline(YGNodeRef node);

WIN_EXPORT void __cdecl YGNodeCalculateLayout(
    YGNodeRef node,
    float availableWidth,
    float availableHeight,
    YGDirection ownerDirection);

// Mark a node as dirty. Only valid for nodes with a custom measure function
// set.
//
// Yoga knows when to mark all other nodes as dirty but because nodes with
// measure functions depend on information not known to Yoga they must perform
// this dirty marking manually.
WIN_EXPORT void __cdecl YGNodeMarkDirty(YGNodeRef node);

// Marks the current node and all its descendants as dirty.
//
// Intended to be used for Uoga benchmarks. Don't use in production, as calling
// `YGCalculateLayout` will cause the recalculation of each and every node.
WIN_EXPORT void __cdecl YGNodeMarkDirtyAndPropogateToDescendants(YGNodeRef node);

WIN_EXPORT void __cdecl YGNodePrint(YGNodeRef node, YGPrintOptions options);

WIN_EXPORT bool __cdecl YGFloatIsUndefined(float value);

WIN_EXPORT bool __cdecl YGNodeCanUseCachedMeasurement(
    YGMeasureMode widthMode,
    float width,
    YGMeasureMode heightMode,
    float height,
    YGMeasureMode lastWidthMode,
    float lastWidth,
    YGMeasureMode lastHeightMode,
    float lastHeight,
    float lastComputedWidth,
    float lastComputedHeight,
    float marginRow,
    float marginColumn,
    YGConfigRef config);

WIN_EXPORT void __cdecl YGNodeCopyStyle(YGNodeRef dstNode, YGNodeRef srcNode);

WIN_EXPORT void* __cdecl YGNodeGetContext(YGNodeRef node);
WIN_EXPORT void __cdecl YGNodeSetContext(YGNodeRef node, void* context);
void __cdecl YGConfigSetPrintTreeFlag(YGConfigRef config, bool enabled);
bool __cdecl YGNodeHasMeasureFunc(YGNodeRef node);
WIN_EXPORT void __cdecl YGNodeSetMeasureFunc(YGNodeRef node, YGMeasureFunc measureFunc);
bool __cdecl YGNodeHasBaselineFunc(YGNodeRef node);
void __cdecl YGNodeSetBaselineFunc(YGNodeRef node, YGBaselineFunc baselineFunc);
YGDirtiedFunc __cdecl YGNodeGetDirtiedFunc(YGNodeRef node);
void __cdecl YGNodeSetDirtiedFunc(YGNodeRef node, YGDirtiedFunc dirtiedFunc);
void __cdecl YGNodeSetPrintFunc(YGNodeRef node, YGPrintFunc printFunc);
WIN_EXPORT bool __cdecl YGNodeGetHasNewLayout(YGNodeRef node);
WIN_EXPORT void __cdecl YGNodeSetHasNewLayout(YGNodeRef node, bool hasNewLayout);
YGNodeType __cdecl YGNodeGetNodeType(YGNodeRef node);
void __cdecl YGNodeSetNodeType(YGNodeRef node, YGNodeType nodeType);
WIN_EXPORT bool __cdecl YGNodeIsDirty(YGNodeRef node);
bool __cdecl YGNodeLayoutGetDidUseLegacyFlag(YGNodeRef node);

WIN_EXPORT void __cdecl YGNodeStyleSetDirection(YGNodeRef node, YGDirection direction);
WIN_EXPORT YGDirection __cdecl YGNodeStyleGetDirection(YGNodeConstRef node);

WIN_EXPORT void __cdecl YGNodeStyleSetFlexDirection(
    YGNodeRef node,
    YGFlexDirection flexDirection);
WIN_EXPORT YGFlexDirection __cdecl YGNodeStyleGetFlexDirection(YGNodeConstRef node);

WIN_EXPORT void __cdecl YGNodeStyleSetJustifyContent(
    YGNodeRef node,
    YGJustify justifyContent);
WIN_EXPORT YGJustify __cdecl YGNodeStyleGetJustifyContent(YGNodeConstRef node);

WIN_EXPORT void __cdecl YGNodeStyleSetAlignContent(
    YGNodeRef node,
    YGAlign alignContent);
WIN_EXPORT YGAlign __cdecl YGNodeStyleGetAlignContent(YGNodeConstRef node);

WIN_EXPORT void __cdecl YGNodeStyleSetAlignItems(YGNodeRef node, YGAlign alignItems);
WIN_EXPORT YGAlign __cdecl YGNodeStyleGetAlignItems(YGNodeConstRef node);

WIN_EXPORT void __cdecl YGNodeStyleSetAlignSelf(YGNodeRef node, YGAlign alignSelf);
WIN_EXPORT YGAlign __cdecl YGNodeStyleGetAlignSelf(YGNodeConstRef node);

WIN_EXPORT void __cdecl YGNodeStyleSetPositionType(
    YGNodeRef node,
    YGPositionType positionType);
WIN_EXPORT YGPositionType __cdecl YGNodeStyleGetPositionType(YGNodeConstRef node);

WIN_EXPORT void __cdecl YGNodeStyleSetFlexWrap(YGNodeRef node, YGWrap flexWrap);
WIN_EXPORT YGWrap __cdecl YGNodeStyleGetFlexWrap(YGNodeConstRef node);

WIN_EXPORT void __cdecl YGNodeStyleSetOverflow(YGNodeRef node, YGOverflow overflow);
WIN_EXPORT YGOverflow __cdecl YGNodeStyleGetOverflow(YGNodeConstRef node);

WIN_EXPORT void __cdecl YGNodeStyleSetDisplay(YGNodeRef node, YGDisplay display);
WIN_EXPORT YGDisplay __cdecl YGNodeStyleGetDisplay(YGNodeConstRef node);

WIN_EXPORT void __cdecl YGNodeStyleSetFlex(YGNodeRef node, float flex);
WIN_EXPORT float __cdecl YGNodeStyleGetFlex(YGNodeConstRef node);

WIN_EXPORT void __cdecl YGNodeStyleSetFlexGrow(YGNodeRef node, float flexGrow);
WIN_EXPORT float __cdecl YGNodeStyleGetFlexGrow(YGNodeConstRef node);

WIN_EXPORT void __cdecl YGNodeStyleSetFlexShrink(YGNodeRef node, float flexShrink);
WIN_EXPORT float __cdecl YGNodeStyleGetFlexShrink(YGNodeConstRef node);

WIN_EXPORT void __cdecl YGNodeStyleSetFlexBasis(YGNodeRef node, float flexBasis);
WIN_EXPORT void __cdecl YGNodeStyleSetFlexBasisPercent(YGNodeRef node, float flexBasis);
WIN_EXPORT void __cdecl YGNodeStyleSetFlexBasisAuto(YGNodeRef node);
WIN_EXPORT YGValue __cdecl YGNodeStyleGetFlexBasis(YGNodeConstRef node);

WIN_EXPORT void __cdecl YGNodeStyleSetPosition(
    YGNodeRef node,
    YGEdge edge,
    float position);
WIN_EXPORT void __cdecl YGNodeStyleSetPositionPercent(
    YGNodeRef node,
    YGEdge edge,
    float position);
WIN_EXPORT YGValue __cdecl YGNodeStyleGetPosition(YGNodeConstRef node, YGEdge edge);

WIN_EXPORT void __cdecl YGNodeStyleSetMargin(YGNodeRef node, YGEdge edge, float margin);
WIN_EXPORT void __cdecl YGNodeStyleSetMarginPercent(
    YGNodeRef node,
    YGEdge edge,
    float margin);
WIN_EXPORT void __cdecl YGNodeStyleSetMarginAuto(YGNodeRef node, YGEdge edge);
WIN_EXPORT YGValue __cdecl YGNodeStyleGetMargin(YGNodeConstRef node, YGEdge edge);

WIN_EXPORT void __cdecl YGNodeStyleSetPadding(
    YGNodeRef node,
    YGEdge edge,
    float padding);
WIN_EXPORT void __cdecl YGNodeStyleSetPaddingPercent(
    YGNodeRef node,
    YGEdge edge,
    float padding);
WIN_EXPORT YGValue __cdecl YGNodeStyleGetPadding(YGNodeConstRef node, YGEdge edge);

WIN_EXPORT void __cdecl YGNodeStyleSetBorder(YGNodeRef node, YGEdge edge, float border);
WIN_EXPORT float __cdecl YGNodeStyleGetBorder(YGNodeConstRef node, YGEdge edge);

WIN_EXPORT void __cdecl YGNodeStyleSetWidth(YGNodeRef node, float width);
WIN_EXPORT void __cdecl YGNodeStyleSetWidthPercent(YGNodeRef node, float width);
WIN_EXPORT void __cdecl YGNodeStyleSetWidthAuto(YGNodeRef node);
WIN_EXPORT YGValue __cdecl YGNodeStyleGetWidth(YGNodeConstRef node);

WIN_EXPORT void __cdecl YGNodeStyleSetHeight(YGNodeRef node, float height);
WIN_EXPORT void __cdecl YGNodeStyleSetHeightPercent(YGNodeRef node, float height);
WIN_EXPORT void __cdecl YGNodeStyleSetHeightAuto(YGNodeRef node);
WIN_EXPORT YGValue __cdecl YGNodeStyleGetHeight(YGNodeConstRef node);

WIN_EXPORT void __cdecl YGNodeStyleSetMinWidth(YGNodeRef node, float minWidth);
WIN_EXPORT void __cdecl YGNodeStyleSetMinWidthPercent(YGNodeRef node, float minWidth);
WIN_EXPORT YGValue __cdecl YGNodeStyleGetMinWidth(YGNodeConstRef node);

WIN_EXPORT void __cdecl YGNodeStyleSetMinHeight(YGNodeRef node, float minHeight);
WIN_EXPORT void __cdecl YGNodeStyleSetMinHeightPercent(YGNodeRef node, float minHeight);
WIN_EXPORT YGValue __cdecl YGNodeStyleGetMinHeight(YGNodeConstRef node);

WIN_EXPORT void __cdecl YGNodeStyleSetMaxWidth(YGNodeRef node, float maxWidth);
WIN_EXPORT void __cdecl YGNodeStyleSetMaxWidthPercent(YGNodeRef node, float maxWidth);
WIN_EXPORT YGValue __cdecl YGNodeStyleGetMaxWidth(YGNodeConstRef node);

WIN_EXPORT void __cdecl YGNodeStyleSetMaxHeight(YGNodeRef node, float maxHeight);
WIN_EXPORT void __cdecl YGNodeStyleSetMaxHeightPercent(YGNodeRef node, float maxHeight);
WIN_EXPORT YGValue __cdecl YGNodeStyleGetMaxHeight(YGNodeConstRef node);

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
WIN_EXPORT void __cdecl YGNodeStyleSetAspectRatio(YGNodeRef node, float aspectRatio);
WIN_EXPORT float __cdecl YGNodeStyleGetAspectRatio(YGNodeConstRef node);

WIN_EXPORT float __cdecl YGNodeLayoutGetLeft(YGNodeRef node);
WIN_EXPORT float __cdecl YGNodeLayoutGetTop(YGNodeRef node);
WIN_EXPORT float __cdecl YGNodeLayoutGetRight(YGNodeRef node);
WIN_EXPORT float __cdecl YGNodeLayoutGetBottom(YGNodeRef node);
WIN_EXPORT float __cdecl YGNodeLayoutGetWidth(YGNodeRef node);
WIN_EXPORT float __cdecl YGNodeLayoutGetHeight(YGNodeRef node);
WIN_EXPORT YGDirection __cdecl YGNodeLayoutGetDirection(YGNodeRef node);
WIN_EXPORT bool __cdecl YGNodeLayoutGetHadOverflow(YGNodeRef node);
bool __cdecl YGNodeLayoutGetDidLegacyStretchFlagAffectLayout(YGNodeRef node);

// Get the computed values for these nodes after performing layout. If they were
// set using point values then the returned value will be the same as
// YGNodeStyleGetXXX. However if they were set using a percentage value then the
// returned value is the computed value used during layout.
WIN_EXPORT float __cdecl YGNodeLayoutGetMargin(YGNodeRef node, YGEdge edge);
WIN_EXPORT float __cdecl YGNodeLayoutGetBorder(YGNodeRef node, YGEdge edge);
WIN_EXPORT float __cdecl YGNodeLayoutGetPadding(YGNodeRef node, YGEdge edge);

WIN_EXPORT void __cdecl YGConfigSetLogger(YGConfigRef config, YGLogger logger);
WIN_EXPORT void __cdecl YGAssert(bool condition, const char* message);
WIN_EXPORT void __cdecl YGAssertWithNode(
    YGNodeRef node,
    bool condition,
    const char* message);
WIN_EXPORT void YGAssertWithConfig(
    YGConfigRef config,
    bool condition,
    const char* message);
// Set this to number of pixels in 1 point to round calculation results If you
// want to avoid rounding - set PointScaleFactor to 0
WIN_EXPORT void __cdecl YGConfigSetPointScaleFactor(
    YGConfigRef config,
    float pixelsInPoint);
void __cdecl YGConfigSetShouldDiffLayoutWithoutLegacyStretchBehaviour(
    YGConfigRef config,
    bool shouldDiffLayout);

// Yoga previously had an error where containers would take the maximum space
// possible instead of the minimum like they are supposed to. In practice this
// resulted in implicit behaviour similar to align-self: stretch; Because this
// was such a long-standing bug we must allow legacy users to switch back to
// this behaviour.
WIN_EXPORT void __cdecl YGConfigSetUseLegacyStretchBehaviour(
    YGConfigRef config,
    bool useLegacyStretchBehaviour);

// YGConfig
WIN_EXPORT YGConfigRef __cdecl YGConfigNew(void);
WIN_EXPORT void __cdecl YGConfigFree(YGConfigRef config);
WIN_EXPORT void __cdecl YGConfigCopy(YGConfigRef dest, YGConfigRef src);
WIN_EXPORT int32_t __cdecl YGConfigGetInstanceCount(void);

WIN_EXPORT void __cdecl YGConfigSetExperimentalFeatureEnabled(
    YGConfigRef config,
    YGExperimentalFeature feature,
    bool enabled);
WIN_EXPORT bool __cdecl YGConfigIsExperimentalFeatureEnabled(
    YGConfigRef config,
    YGExperimentalFeature feature);

// Using the web defaults is the preferred configuration for new projects. Usage
// of non web defaults should be considered as legacy.
WIN_EXPORT void __cdecl YGConfigSetUseWebDefaults(YGConfigRef config, bool enabled);
WIN_EXPORT bool __cdecl YGConfigGetUseWebDefaults(YGConfigRef config);

WIN_EXPORT void __cdecl YGConfigSetCloneNodeFunc(
    YGConfigRef config,
    YGCloneNodeFunc callback);

// Export only for C#
WIN_EXPORT YGConfigRef __cdecl YGConfigGetDefault(void);

WIN_EXPORT void __cdecl YGConfigSetContext(YGConfigRef config, void* context);
WIN_EXPORT void* __cdecl YGConfigGetContext(YGConfigRef config);

WIN_EXPORT float __cdecl YGRoundValueToPixelGrid(
    float value,
    float pointScaleFactor,
    bool forceCeil,
    bool forceFloor);

YG_EXTERN_C_END

#ifdef __cplusplus

#include <functional>
#include <vector>

// Calls f on each node in the tree including the given node argument.
void __cdecl YGTraversePreOrder(
    YGNodeRef node,
    std::function<void(YGNodeRef node)>&& f);

void __cdecl YGNodeSetChildren(YGNodeRef owner, const std::vector<YGNodeRef>& children);

#endif
