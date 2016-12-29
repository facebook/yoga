/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

Module.Undefined = NaN;

Module.FlexDirectionColumn = 0;
Module.FlexDirectionColumnReverse = 1;
Module.FlexDirectionRow = 2;
Module.FlexDirectionRowReverse = 3;

Module.MeasureModeUndefined = 0;
Module.MeasureModeExactly = 1;
Module.MeasureModeAtMost = 2;

Module.PrintOptionsLayout = 1;
Module.PrintOptionsStyle = 2;
Module.PrintOptionsChildren = 4;

Module.EdgeLeft = 0;
Module.EdgeTop = 1;
Module.EdgeRight = 2;
Module.EdgeBottom = 3;
Module.EdgeStart = 4;
Module.EdgeEnd = 5;
Module.EdgeHorizontal = 6;
Module.EdgeVertical = 7;
Module.EdgeAll = 8;

Module.PositionTypeRelative = 0;
Module.PositionTypeAbsolute = 1;

Module.DimensionWidth = 0;
Module.DimensionHeight = 1;

Module.JustifyFlexStart = 0;
Module.JustifyCenter = 1;
Module.JustifyFlexEnd = 2;
Module.JustifySpaceBetween = 3;
Module.JustifySpaceAround = 4;

Module.DirectionInherit = 0;
Module.DirectionLTR = 1;
Module.DirectionRTL = 2;

Module.LogLevelError = 0;
Module.LogLevelWarn = 1;
Module.LogLevelInfo = 2;
Module.LogLevelDebug = 3;
Module.LogLevelVerbose = 4;

Module.WrapNoWrap = 0;
Module.WrapWrap = 1;

Module.OverflowVisible = 0;
Module.OverflowHidden = 1;
Module.OverflowScroll = 2;

Module.ExperimentalFeatureRounding = 0;
Module.ExperimentalFeatureWebFlexBasis = 1;

Module.AlignAuto = 0;
Module.AlignFlexStart = 1;
Module.AlignCenter = 2;
Module.AlignFlexEnd = 3;
Module.AlignStretch = 4;

Module.nodeNew = _YGNodeNew;
Module.nodeFree = _YGNodeFree;
Module.nodeFreeRecursive = _YGNodeFreeRecursive;
Module.nodeReset = _YGNodeReset;
Module.nodeGetInstanceCount = _YGNodeGetInstanceCount;
Module.nodeInsertChild = _YGNodeInsertChild;
Module.nodeRemoveChild = _YGNodeRemoveChild;
Module.nodeGetChild = _YGNodeGetChild;
Module.nodeGetParent = _YGNodeGetParent;
Module.nodeGetChildCount = _YGNodeGetChildCount;
Module.nodeCalculateLayout = _YGNodeCalculateLayout;
Module.nodeMarkDirty = _YGNodeMarkDirty;
Module.nodeIsDirty = _YGNodeIsDirty;
Module.nodePrint = _YGNodePrint;
Module.valueIsUndefined = _YGValueIsUndefined;
Module.nodeCanUseCachedMeasurement = _YGNodeCanUseCachedMeasurement;
Module.nodeCopyStyle = _YGNodeCopyStyle;
Module.nodeSetContext = _YGNodeSetContext;
Module.nodeGetContext = _YGNodeGetContext;
Module.nodeSetMeasureFunc = _YGNodeSetMeasureFunc;
Module.nodeGetMeasureFunc = _YGNodeGetMeasureFunc;
Module.nodeSetPrintFunc = _YGNodeSetPrintFunc;
Module.nodeGetPrintFunc = _YGNodeGetPrintFunc;
Module.nodeSetHasNewLayout = _YGNodeSetHasNewLayout;
Module.nodeGetHasNewLayout = _YGNodeGetHasNewLayout;
Module.nodeStyleSetDirection = _YGNodeStyleSetDirection;
Module.nodeStyleGetDirection = _YGNodeStyleGetDirection;
Module.nodeStyleSetFlexDirection = _YGNodeStyleSetFlexDirection;
Module.nodeStyleGetFlexDirection = _YGNodeStyleGetFlexDirection;
Module.nodeStyleSetJustifyContent = _YGNodeStyleSetJustifyContent;
Module.nodeStyleGetJustifyContent = _YGNodeStyleGetJustifyContent;
Module.nodeStyleSetAlignContent = _YGNodeStyleSetAlignContent;
Module.nodeStyleGetAlignContent = _YGNodeStyleGetAlignContent;
Module.nodeStyleSetAlignItems = _YGNodeStyleSetAlignItems;
Module.nodeStyleGetAlignItems = _YGNodeStyleGetAlignItems;
Module.nodeStyleSetAlignSelf = _YGNodeStyleSetAlignSelf;
Module.nodeStyleGetAlignSelf = _YGNodeStyleGetAlignSelf;
Module.nodeStyleSetPositionType = _YGNodeStyleSetPositionType;
Module.nodeStyleGetPositionType = _YGNodeStyleGetPositionType;
Module.nodeStyleSetFlexWrap = _YGNodeStyleSetFlexWrap;
Module.nodeStyleGetFlexWrap = _YGNodeStyleGetFlexWrap;
Module.nodeStyleSetOverflow = _YGNodeStyleSetOverflow;
Module.nodeStyleGetOverflow = _YGNodeStyleGetOverflow;
Module.nodeStyleSetFlex = _YGNodeStyleSetFlex;
Module.nodeStyleSetFlexGrow = _YGNodeStyleSetFlexGrow;
Module.nodeStyleGetFlexGrow = _YGNodeStyleGetFlexGrow;
Module.nodeStyleSetFlexShrink = _YGNodeStyleSetFlexShrink;
Module.nodeStyleGetFlexShrink = _YGNodeStyleGetFlexShrink;
Module.nodeStyleSetFlexBasis = _YGNodeStyleSetFlexBasis;
Module.nodeStyleGetFlexBasis = _YGNodeStyleGetFlexBasis;
Module.nodeStyleSetPosition = _YGNodeStyleSetPosition;
Module.nodeStyleGetPosition = _YGNodeStyleGetPosition;
Module.nodeStyleSetMargin = _YGNodeStyleSetMargin;
Module.nodeStyleGetMargin = _YGNodeStyleGetMargin;
Module.nodeStyleSetPadding = _YGNodeStyleSetPadding;
Module.nodeStyleGetPadding = _YGNodeStyleGetPadding;
Module.nodeStyleSetBorder = _YGNodeStyleSetBorder;
Module.nodeStyleGetBorder = _YGNodeStyleGetBorder;
Module.nodeStyleSetWidth = _YGNodeStyleSetWidth;
Module.nodeStyleGetWidth = _YGNodeStyleGetWidth;
Module.nodeStyleSetHeight = _YGNodeStyleSetHeight;
Module.nodeStyleGetHeight = _YGNodeStyleGetHeight;
Module.nodeStyleSetMinWidth = _YGNodeStyleSetMinWidth;
Module.nodeStyleGetMinWidth = _YGNodeStyleGetMinWidth;
Module.nodeStyleSetMinHeight = _YGNodeStyleSetMinHeight;
Module.nodeStyleGetMinHeight = _YGNodeStyleGetMinHeight;
Module.nodeStyleSetMaxWidth = _YGNodeStyleSetMaxWidth;
Module.nodeStyleGetMaxWidth = _YGNodeStyleGetMaxWidth;
Module.nodeStyleSetMaxHeight = _YGNodeStyleSetMaxHeight;
Module.nodeStyleGetMaxHeight = _YGNodeStyleGetMaxHeight;
Module.nodeStyleSetAspectRatio = _YGNodeStyleSetAspectRatio;
Module.nodeStyleGetAspectRatio = _YGNodeStyleGetAspectRatio;
Module.nodeLayoutGetLeft = _YGNodeLayoutGetLeft;
Module.nodeLayoutGetTop = _YGNodeLayoutGetTop;
Module.nodeLayoutGetRight = _YGNodeLayoutGetRight;
Module.nodeLayoutGetBottom = _YGNodeLayoutGetBottom;
Module.nodeLayoutGetWidth = _YGNodeLayoutGetWidth;
Module.nodeLayoutGetHeight = _YGNodeLayoutGetHeight;
Module.nodeLayoutGetDirection = _YGNodeLayoutGetDirection;
Module.setLogger = _YGSetLogger;
Module.log = _YGLog;
Module.setExperimentalFeatureEnabled = _YGSetExperimentalFeatureEnabled;
Module.isExperimentalFeatureEnabled = _YGIsExperimentalFeatureEnabled;
Module.addFunction = Runtime.addFunction;Module.removeFunction = Runtime.removeFunction;
