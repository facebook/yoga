/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

using System;
using System.Runtime.InteropServices;

namespace Facebook.Yoga
{
    internal static class Native
    {
#if UNITY_IOS && !UNITY_EDITOR
        private const string DllName = "__Internal";
#else
        private const string DllName = "yoga";
#endif

        [DllImport(DllName)]
        public static extern void YGInteropSetLogger(
            [MarshalAs(UnmanagedType.FunctionPtr)] YogaLogger.Func func);

        [DllImport(DllName)]
        public static extern IntPtr YGNodeNew();

        [DllImport(DllName)]
        public static extern void YGNodeInit(IntPtr cssNode);

        [DllImport(DllName)]
        public static extern void YGNodeFree(IntPtr cssNode);

        [DllImport(DllName)]
        public static extern void YGNodeReset(IntPtr cssNode);

        [DllImport(DllName)]
        public static extern int YGNodeGetInstanceCount();

        [DllImport(DllName)]
        public static extern void YGSetExperimentalFeatureEnabled(
            YogaExperimentalFeature feature,
            bool enabled);

        [DllImport(DllName)]
        public static extern bool YGIsExperimentalFeatureEnabled(
            YogaExperimentalFeature feature);

        [DllImport(DllName)]
        public static extern void YGNodeInsertChild(IntPtr node, IntPtr child, uint index);

        [DllImport(DllName)]
        public static extern void YGNodeRemoveChild(IntPtr node, IntPtr child);

        [DllImport(DllName)]
        public static extern IntPtr YGNodeGetChild(IntPtr node, uint index);

        [DllImport(DllName)]
        public static extern uint YGNodeChildCount(IntPtr node);

        [DllImport(DllName)]
        public static extern void YGNodeCalculateLayout(IntPtr node,
                            float availableWidth,
                            float availableHeight,
                            YogaDirection parentDirection);

        [DllImport(DllName)]
        public static extern void YGNodeMarkDirty(IntPtr node);

        [DllImport(DllName)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool YGNodeIsDirty(IntPtr node);

        [DllImport(DllName)]
        public static extern void YGNodePrint(IntPtr node, YogaPrintOptions options);

        [DllImport(DllName)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool YGValueIsUndefined(float value);

        [DllImport(DllName)]
        public static extern void YGNodeCopyStyle(IntPtr dstNode, IntPtr srcNode);

        #region YG_NODE_PROPERTY

        [DllImport(DllName)]
        public static extern void YGNodeSetContext(IntPtr node, IntPtr context);

        [DllImport(DllName)]
        public static extern IntPtr YGNodeGetContext(IntPtr node);

        [DllImport(DllName)]
        public static extern void YGNodeSetMeasureFunc(
            IntPtr node,
            [MarshalAs(UnmanagedType.FunctionPtr)] YogaMeasureFunc measureFunc);

        [DllImport(DllName)]
        [return: MarshalAs(UnmanagedType.FunctionPtr)]
        public static extern YogaMeasureFunc YGNodeGetMeasureFunc(IntPtr node);

        [DllImport(DllName)]
        public static extern void YGNodeSetHasNewLayout(IntPtr node, [MarshalAs(UnmanagedType.I1)] bool hasNewLayout);

        [DllImport(DllName)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool YGNodeGetHasNewLayout(IntPtr node);

        #endregion

        #region YG_NODE_STYLE_PROPERTY

        [DllImport(DllName)]
        public static extern void YGNodeStyleSetDirection(IntPtr node, YogaDirection direction);

        [DllImport(DllName)]
        public static extern YogaDirection YGNodeStyleGetDirection(IntPtr node);

        [DllImport(DllName)]
        public static extern void YGNodeStyleSetFlexDirection(IntPtr node, YogaFlexDirection flexDirection);

        [DllImport(DllName)]
        public static extern YogaFlexDirection YGNodeStyleGetFlexDirection(IntPtr node);

        [DllImport(DllName)]
        public static extern void YGNodeStyleSetJustifyContent(IntPtr node, YogaJustify justifyContent);

        [DllImport(DllName)]
        public static extern YogaJustify YGNodeStyleGetJustifyContent(IntPtr node);

        [DllImport(DllName)]
        public static extern void YGNodeStyleSetAlignContent(IntPtr node, YogaAlign alignContent);

        [DllImport(DllName)]
        public static extern YogaAlign YGNodeStyleGetAlignContent(IntPtr node);

        [DllImport(DllName)]
        public static extern void YGNodeStyleSetAlignItems(IntPtr node, YogaAlign alignItems);

        [DllImport(DllName)]
        public static extern YogaAlign YGNodeStyleGetAlignItems(IntPtr node);

        [DllImport(DllName)]
        public static extern void YGNodeStyleSetAlignSelf(IntPtr node, YogaAlign alignSelf);

        [DllImport(DllName)]
        public static extern YogaAlign YGNodeStyleGetAlignSelf(IntPtr node);

        [DllImport(DllName)]
        public static extern void YGNodeStyleSetPositionType(IntPtr node, YogaPositionType positionType);

        [DllImport(DllName)]
        public static extern YogaPositionType YGNodeStyleGetPositionType(IntPtr node);

        [DllImport(DllName)]
        public static extern void YGNodeStyleSetFlexWrap(IntPtr node, YogaWrap flexWrap);

        [DllImport(DllName)]
        public static extern YogaWrap YGNodeStyleGetFlexWrap(IntPtr node);

        [DllImport(DllName)]
        public static extern void YGNodeStyleSetOverflow(IntPtr node, YogaOverflow flexWrap);

        [DllImport(DllName)]
        public static extern YogaOverflow YGNodeStyleGetOverflow(IntPtr node);

        [DllImport(DllName)]
        public static extern void YGNodeStyleSetFlex(IntPtr node, float flex);

        [DllImport(DllName)]
        public static extern void YGNodeStyleSetFlexGrow(IntPtr node, float flexGrow);

        [DllImport(DllName)]
        public static extern float YGNodeStyleGetFlexGrow(IntPtr node);

        [DllImport(DllName)]
        public static extern void YGNodeStyleSetFlexShrink(IntPtr node, float flexShrink);

        [DllImport(DllName)]
        public static extern float YGNodeStyleGetFlexShrink(IntPtr node);

        [DllImport(DllName)]
        public static extern void YGNodeStyleSetFlexBasis(IntPtr node, float flexBasis);

        [DllImport(DllName)]
        public static extern float YGNodeStyleGetFlexBasis(IntPtr node);

        [DllImport(DllName)]
        public static extern void YGNodeStyleSetWidth(IntPtr node, float width);

        [DllImport(DllName)]
        public static extern float YGNodeStyleGetWidth(IntPtr node);

        [DllImport(DllName)]
        public static extern void YGNodeStyleSetHeight(IntPtr node, float height);

        [DllImport(DllName)]
        public static extern float YGNodeStyleGetHeight(IntPtr node);

        [DllImport(DllName)]
        public static extern void YGNodeStyleSetMinWidth(IntPtr node, float minWidth);

        [DllImport(DllName)]
        public static extern float YGNodeStyleGetMinWidth(IntPtr node);

        [DllImport(DllName)]
        public static extern void YGNodeStyleSetMinHeight(IntPtr node, float minHeight);

        [DllImport(DllName)]
        public static extern float YGNodeStyleGetMinHeight(IntPtr node);

        [DllImport(DllName)]
        public static extern void YGNodeStyleSetMaxWidth(IntPtr node, float maxWidth);

        [DllImport(DllName)]
        public static extern float YGNodeStyleGetMaxWidth(IntPtr node);

        [DllImport(DllName)]
        public static extern void YGNodeStyleSetMaxHeight(IntPtr node, float maxHeight);

        [DllImport(DllName)]
        public static extern float YGNodeStyleGetMaxHeight(IntPtr node);

        [DllImport(DllName)]
        public static extern void YGNodeStyleSetAspectRatio(IntPtr node, float aspectRatio);

        [DllImport(DllName)]
        public static extern float YGNodeStyleGetAspectRatio(IntPtr node);

        #endregion

        #region YG_NODE_STYLE_EDGE_PROPERTY

        [DllImport(DllName)]
        public static extern void YGNodeStyleSetPosition(IntPtr node, YogaEdge edge, float position);

        [DllImport(DllName)]
        public static extern float YGNodeStyleGetPosition(IntPtr node, YogaEdge edge);

        [DllImport(DllName)]
        public static extern void YGNodeStyleSetMargin(IntPtr node, YogaEdge edge, float margin);

        [DllImport(DllName)]
        public static extern float YGNodeStyleGetMargin(IntPtr node, YogaEdge edge);

        [DllImport(DllName)]
        public static extern void YGNodeStyleSetPadding(IntPtr node, YogaEdge edge, float padding);

        [DllImport(DllName)]
        public static extern float YGNodeStyleGetPadding(IntPtr node, YogaEdge edge);

        [DllImport(DllName)]
        public static extern void YGNodeStyleSetBorder(IntPtr node, YogaEdge edge, float border);

        [DllImport(DllName)]
        public static extern float YGNodeStyleGetBorder(IntPtr node, YogaEdge edge);

        #endregion

        #region YG_NODE_LAYOUT_PROPERTY

        [DllImport(DllName)]
        public static extern float YGNodeLayoutGetLeft(IntPtr node);

        [DllImport(DllName)]
        public static extern float YGNodeLayoutGetTop(IntPtr node);

        [DllImport(DllName)]
        public static extern float YGNodeLayoutGetRight(IntPtr node);

        [DllImport(DllName)]
        public static extern float YGNodeLayoutGetBottom(IntPtr node);

        [DllImport(DllName)]
        public static extern float YGNodeLayoutGetWidth(IntPtr node);

        [DllImport(DllName)]
        public static extern float YGNodeLayoutGetHeight(IntPtr node);

        [DllImport(DllName)]
        public static extern YogaDirection YGNodeLayoutGetDirection(IntPtr node);

        #endregion
    }
}
