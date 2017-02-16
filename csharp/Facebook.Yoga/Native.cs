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
#if (UNITY_IOS && !UNITY_EDITOR) || __IOS__
        private const string DllName = "__Internal";
#else
        private const string DllName = "yoga";
#endif

        internal class YGNodeHandle : SafeHandle
        {
            private YGNodeHandle() : base(IntPtr.Zero, true)
            {
            }

            public override bool IsInvalid
            {
                get
                {
                    return this.handle == IntPtr.Zero;
                }
            }

            protected override bool ReleaseHandle()
            {
                Native.YGNodeFree(this.handle);
                GC.KeepAlive(this);
                return true;
            }
        }

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern void YGInteropSetLogger(
            [MarshalAs(UnmanagedType.FunctionPtr)] YogaLogger.Func func);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern YGNodeHandle YGNodeNew();

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern void YGNodeFree(IntPtr node);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern void YGNodeReset(YGNodeHandle node);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern int YGNodeGetInstanceCount();

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern void YGSetExperimentalFeatureEnabled(
            YogaExperimentalFeature feature,
            bool enabled);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern bool YGIsExperimentalFeatureEnabled(
            YogaExperimentalFeature feature);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern void YGNodeInsertChild(YGNodeHandle node, YGNodeHandle child, uint index);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern void YGNodeRemoveChild(YGNodeHandle node, YGNodeHandle child);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern void YGNodeCalculateLayout(YGNodeHandle node,
                            float availableWidth,
                            float availableHeight,
                            YogaDirection parentDirection);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern void YGNodeMarkDirty(YGNodeHandle node);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool YGNodeIsDirty(YGNodeHandle node);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern void YGNodePrint(YGNodeHandle node, YogaPrintOptions options);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern void YGNodeCopyStyle(YGNodeHandle dstNode, YGNodeHandle srcNode);

        #region YG_NODE_PROPERTY

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern void YGNodeSetMeasureFunc(
            YGNodeHandle node,
            [MarshalAs(UnmanagedType.FunctionPtr)] YogaMeasureFunc measureFunc);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern void YGNodeSetBaselineFunc(
            YGNodeHandle node,
            [MarshalAs(UnmanagedType.FunctionPtr)] YogaBaselineFunc baselineFunc);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern void YGNodeSetHasNewLayout(YGNodeHandle node, [MarshalAs(UnmanagedType.I1)] bool hasNewLayout);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool YGNodeGetHasNewLayout(YGNodeHandle node);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern void YGNodeSetContext(YGNodeHandle node, IntPtr context);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr YGNodeGetContext(IntPtr node);


        #endregion

        #region YG_NODE_STYLE_PROPERTY

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern void YGNodeStyleSetDirection(YGNodeHandle node, YogaDirection direction);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern YogaDirection YGNodeStyleGetDirection(YGNodeHandle node);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern void YGNodeStyleSetFlexDirection(YGNodeHandle node, YogaFlexDirection flexDirection);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern YogaFlexDirection YGNodeStyleGetFlexDirection(YGNodeHandle node);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern void YGNodeStyleSetJustifyContent(YGNodeHandle node, YogaJustify justifyContent);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern YogaJustify YGNodeStyleGetJustifyContent(YGNodeHandle node);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern void YGNodeStyleSetAlignContent(YGNodeHandle node, YogaAlign alignContent);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern YogaAlign YGNodeStyleGetAlignContent(YGNodeHandle node);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern void YGNodeStyleSetAlignItems(YGNodeHandle node, YogaAlign alignItems);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern YogaAlign YGNodeStyleGetAlignItems(YGNodeHandle node);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern void YGNodeStyleSetAlignSelf(YGNodeHandle node, YogaAlign alignSelf);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern YogaAlign YGNodeStyleGetAlignSelf(YGNodeHandle node);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern void YGNodeStyleSetPositionType(YGNodeHandle node, YogaPositionType positionType);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern YogaPositionType YGNodeStyleGetPositionType(YGNodeHandle node);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern void YGNodeStyleSetFlexWrap(YGNodeHandle node, YogaWrap flexWrap);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern YogaWrap YGNodeStyleGetFlexWrap(YGNodeHandle node);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern void YGNodeStyleSetOverflow(YGNodeHandle node, YogaOverflow flexWrap);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern YogaOverflow YGNodeStyleGetOverflow(YGNodeHandle node);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern void YGNodeStyleSetDisplay(YGNodeHandle node, YogaDisplay display);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern YogaDisplay YGNodeStyleGetDisplay(YGNodeHandle node);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern void YGNodeStyleSetFlex(YGNodeHandle node, float flex);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern void YGNodeStyleSetFlexGrow(YGNodeHandle node, float flexGrow);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern float YGNodeStyleGetFlexGrow(YGNodeHandle node);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern void YGNodeStyleSetFlexShrink(YGNodeHandle node, float flexShrink);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern float YGNodeStyleGetFlexShrink(YGNodeHandle node);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern void YGNodeStyleSetFlexBasis(YGNodeHandle node, float flexBasis);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern void YGNodeStyleSetFlexBasisPercent(YGNodeHandle node, float flexBasis);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern void YGNodeStyleSetFlexBasisAuto(YGNodeHandle node);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern YogaValue YGNodeStyleGetFlexBasis(YGNodeHandle node);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern void YGNodeStyleSetWidth(YGNodeHandle node, float width);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern void YGNodeStyleSetWidthPercent(YGNodeHandle node, float width);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern void YGNodeStyleSetWidthAuto(YGNodeHandle node);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern YogaValue YGNodeStyleGetWidth(YGNodeHandle node);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern void YGNodeStyleSetHeight(YGNodeHandle node, float height);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern void YGNodeStyleSetHeightPercent(YGNodeHandle node, float height);
        
        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern void YGNodeStyleSetHeightAuto(YGNodeHandle node);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern YogaValue YGNodeStyleGetHeight(YGNodeHandle node);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern void YGNodeStyleSetMinWidth(YGNodeHandle node, float minWidth);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern void YGNodeStyleSetMinWidthPercent(YGNodeHandle node, float minWidth);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern YogaValue YGNodeStyleGetMinWidth(YGNodeHandle node);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern void YGNodeStyleSetMinHeight(YGNodeHandle node, float minHeight);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern void YGNodeStyleSetMinHeightPercent(YGNodeHandle node, float minHeight);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern YogaValue YGNodeStyleGetMinHeight(YGNodeHandle node);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern void YGNodeStyleSetMaxWidth(YGNodeHandle node, float maxWidth);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern void YGNodeStyleSetMaxWidthPercent(YGNodeHandle node, float maxWidth);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern YogaValue YGNodeStyleGetMaxWidth(YGNodeHandle node);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern void YGNodeStyleSetMaxHeight(YGNodeHandle node, float maxHeight);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern void YGNodeStyleSetMaxHeightPercent(YGNodeHandle node, float maxHeight);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern YogaValue YGNodeStyleGetMaxHeight(YGNodeHandle node);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern void YGNodeStyleSetAspectRatio(YGNodeHandle node, float aspectRatio);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern float YGNodeStyleGetAspectRatio(YGNodeHandle node);

        #endregion

        #region YG_NODE_STYLE_EDGE_PROPERTY

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern void YGNodeStyleSetPosition(YGNodeHandle node, YogaEdge edge, float position);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern void YGNodeStyleSetPositionPercent(YGNodeHandle node, YogaEdge edge, float position);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern YogaValue YGNodeStyleGetPosition(YGNodeHandle node, YogaEdge edge);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern void YGNodeStyleSetMargin(YGNodeHandle node, YogaEdge edge, float margin);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern void YGNodeStyleSetMarginPercent(YGNodeHandle node, YogaEdge edge, float margin);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern void YGNodeStyleSetMarginAuto(YGNodeHandle node, YogaEdge edge);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern YogaValue YGNodeStyleGetMargin(YGNodeHandle node, YogaEdge edge);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern void YGNodeStyleSetPadding(YGNodeHandle node, YogaEdge edge, float padding);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern void YGNodeStyleSetPaddingPercent(YGNodeHandle node, YogaEdge edge, float padding);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern YogaValue YGNodeStyleGetPadding(YGNodeHandle node, YogaEdge edge);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern void YGNodeStyleSetBorder(YGNodeHandle node, YogaEdge edge, float border);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern float YGNodeStyleGetBorder(YGNodeHandle node, YogaEdge edge);

        #endregion

        #region YG_NODE_LAYOUT_PROPERTY

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern float YGNodeLayoutGetLeft(YGNodeHandle node);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern float YGNodeLayoutGetTop(YGNodeHandle node);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern float YGNodeLayoutGetRight(YGNodeHandle node);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern float YGNodeLayoutGetBottom(YGNodeHandle node);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern float YGNodeLayoutGetWidth(YGNodeHandle node);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern float YGNodeLayoutGetHeight(YGNodeHandle node);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern float YGNodeLayoutGetMargin(YGNodeHandle node, YogaEdge edge);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern float YGNodeLayoutGetPadding(YGNodeHandle node, YogaEdge edge);

        [DllImport(DllName, ExactSpelling = true, CallingConvention = CallingConvention.Cdecl)]
        public static extern YogaDirection YGNodeLayoutGetDirection(YGNodeHandle node);

        #endregion
    }
}
