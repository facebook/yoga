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

namespace Facebook.CSSLayout
{
    internal static class Native
    {
#if UNITY_IOS && !UNITY_EDITOR
        private const string DllName = "__Internal";
#else
        private const string DllName = "CSSLayout";
#endif

        [DllImport(DllName)]
        public static extern void CSSInteropSetLogger(
            [MarshalAs(UnmanagedType.FunctionPtr)] CSSLogger.Func func);

        [DllImport(DllName)]
        public static extern void CSSAssertSetFailFunc(
            [MarshalAs(UnmanagedType.FunctionPtr)] CSSAssert.FailFunc func);

        [DllImport(DllName)]
        public static extern IntPtr CSSNodeNew();

        [DllImport(DllName)]
        public static extern void CSSNodeInit(IntPtr cssNode);

        [DllImport(DllName)]
        public static extern void CSSNodeFree(IntPtr cssNode);

        [DllImport(DllName)]
        public static extern void CSSNodeReset(IntPtr cssNode);

        [DllImport(DllName)]
        public static extern int CSSNodeGetInstanceCount();

        [DllImport(DllName)]
        public static extern void CSSNodeInsertChild(IntPtr node, IntPtr child, uint index);

        [DllImport(DllName)]
        public static extern void CSSNodeRemoveChild(IntPtr node, IntPtr child);

        [DllImport(DllName)]
        public static extern IntPtr CSSNodeGetChild(IntPtr node, uint index);

        [DllImport(DllName)]
        public static extern uint CSSNodeChildCount(IntPtr node);

        [DllImport(DllName)]
        public static extern void CSSNodeCalculateLayout(IntPtr node,
                            float availableWidth,
                            float availableHeight,
                            CSSDirection parentDirection);

        [DllImport(DllName)]
        public static extern void CSSNodeMarkDirty(IntPtr node);

        [DllImport(DllName)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool CSSNodeIsDirty(IntPtr node);

        [DllImport(DllName)]
        public static extern void CSSNodePrint(IntPtr node, CSSPrintOptions options);

        [DllImport(DllName)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool CSSValueIsUndefined(float value);

        #region CSS_NODE_PROPERTY

        [DllImport(DllName)]
        public static extern void CSSNodeSetContext(IntPtr node, IntPtr context);

        [DllImport(DllName)]
        public static extern IntPtr CSSNodeGetContext(IntPtr node);

        [DllImport(DllName)]
        public static extern void CSSNodeSetMeasureFunc(
            IntPtr node,
            [MarshalAs(UnmanagedType.FunctionPtr)] CSSMeasureFunc measureFunc);

        [DllImport(DllName)]
        [return: MarshalAs(UnmanagedType.FunctionPtr)]
        public static extern CSSMeasureFunc CSSNodeGetMeasureFunc(IntPtr node);

        [DllImport(DllName)]
        public static extern void CSSNodeSetIsTextnode(IntPtr node, [MarshalAs(UnmanagedType.I1)] bool isTextNode);

        [DllImport(DllName)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool CSSNodeGetIsTextnode(IntPtr node);

        [DllImport(DllName)]
        public static extern void CSSNodeSetHasNewLayout(IntPtr node, [MarshalAs(UnmanagedType.I1)] bool hasNewLayout);

        [DllImport(DllName)]
        [return: MarshalAs(UnmanagedType.I1)]
        public static extern bool CSSNodeGetHasNewLayout(IntPtr node);

        #endregion

        #region CSS_NODE_STYLE_PROPERTY

        [DllImport(DllName)]
        public static extern void CSSNodeStyleSetDirection(IntPtr node, CSSDirection direction);

        [DllImport(DllName)]
        public static extern CSSDirection CSSNodeStyleGetDirection(IntPtr node);

        [DllImport(DllName)]
        public static extern void CSSNodeStyleSetFlexDirection(IntPtr node, CSSFlexDirection flexDirection);

        [DllImport(DllName)]
        public static extern CSSFlexDirection CSSNodeStyleGetFlexDirection(IntPtr node);

        [DllImport(DllName)]
        public static extern void CSSNodeStyleSetJustifyContent(IntPtr node, CSSJustify justifyContent);

        [DllImport(DllName)]
        public static extern CSSJustify CSSNodeStyleGetJustifyContent(IntPtr node);

        [DllImport(DllName)]
        public static extern void CSSNodeStyleSetAlignContent(IntPtr node, CSSAlign alignContent);

        [DllImport(DllName)]
        public static extern CSSAlign CSSNodeStyleGetAlignContent(IntPtr node);

        [DllImport(DllName)]
        public static extern void CSSNodeStyleSetAlignItems(IntPtr node, CSSAlign alignItems);

        [DllImport(DllName)]
        public static extern CSSAlign CSSNodeStyleGetAlignItems(IntPtr node);

        [DllImport(DllName)]
        public static extern void CSSNodeStyleSetAlignSelf(IntPtr node, CSSAlign alignSelf);

        [DllImport(DllName)]
        public static extern CSSAlign CSSNodeStyleGetAlignSelf(IntPtr node);

        [DllImport(DllName)]
        public static extern void CSSNodeStyleSetPositionType(IntPtr node, CSSPositionType positionType);

        [DllImport(DllName)]
        public static extern CSSPositionType CSSNodeStyleGetPositionType(IntPtr node);

        [DllImport(DllName)]
        public static extern void CSSNodeStyleSetFlexWrap(IntPtr node, CSSWrap flexWrap);

        [DllImport(DllName)]
        public static extern CSSWrap CSSNodeStyleGetFlexWrap(IntPtr node);

        [DllImport(DllName)]
        public static extern void CSSNodeStyleSetOverflow(IntPtr node, CSSOverflow flexWrap);

        [DllImport(DllName)]
        public static extern CSSOverflow CSSNodeStyleGetOverflow(IntPtr node);

        [DllImport(DllName)]
        public static extern void CSSNodeStyleSetFlex(IntPtr node, float flex);

        [DllImport(DllName)]
        public static extern void CSSNodeStyleSetFlexGrow(IntPtr node, float flexGrow);

        [DllImport(DllName)]
        public static extern float CSSNodeStyleGetFlexGrow(IntPtr node);

        [DllImport(DllName)]
        public static extern void CSSNodeStyleSetFlexShrink(IntPtr node, float flexShrink);

        [DllImport(DllName)]
        public static extern float CSSNodeStyleGetFlexShrink(IntPtr node);

        [DllImport(DllName)]
        public static extern void CSSNodeStyleSetFlexBasis(IntPtr node, float flexBasis);

        [DllImport(DllName)]
        public static extern float CSSNodeStyleGetFlexBasis(IntPtr node);

        [DllImport(DllName)]
        public static extern void CSSNodeStyleSetWidth(IntPtr node, float width);

        [DllImport(DllName)]
        public static extern float CSSNodeStyleGetWidth(IntPtr node);

        [DllImport(DllName)]
        public static extern void CSSNodeStyleSetHeight(IntPtr node, float height);

        [DllImport(DllName)]
        public static extern float CSSNodeStyleGetHeight(IntPtr node);

        [DllImport(DllName)]
        public static extern void CSSNodeStyleSetMinWidth(IntPtr node, float minWidth);

        [DllImport(DllName)]
        public static extern float CSSNodeStyleGetMinWidth(IntPtr node);

        [DllImport(DllName)]
        public static extern void CSSNodeStyleSetMinHeight(IntPtr node, float minHeight);

        [DllImport(DllName)]
        public static extern float CSSNodeStyleGetMinHeight(IntPtr node);

        [DllImport(DllName)]
        public static extern void CSSNodeStyleSetMaxWidth(IntPtr node, float maxWidth);

        [DllImport(DllName)]
        public static extern float CSSNodeStyleGetMaxWidth(IntPtr node);

        [DllImport(DllName)]
        public static extern void CSSNodeStyleSetMaxHeight(IntPtr node, float maxHeight);

        [DllImport(DllName)]
        public static extern float CSSNodeStyleGetMaxHeight(IntPtr node);

        #endregion

        #region CSS_NODE_STYLE_EDGE_PROPERTY

        [DllImport(DllName)]
        public static extern void CSSNodeStyleSetPosition(IntPtr node, CSSEdge edge, float position);

        [DllImport(DllName)]
        public static extern float CSSNodeStyleGetPosition(IntPtr node, CSSEdge edge);

        [DllImport(DllName)]
        public static extern void CSSNodeStyleSetMargin(IntPtr node, CSSEdge edge, float margin);

        [DllImport(DllName)]
        public static extern float CSSNodeStyleGetMargin(IntPtr node, CSSEdge edge);

        [DllImport(DllName)]
        public static extern void CSSNodeStyleSetPadding(IntPtr node, CSSEdge edge, float padding);

        [DllImport(DllName)]
        public static extern float CSSNodeStyleGetPadding(IntPtr node, CSSEdge edge);

        [DllImport(DllName)]
        public static extern void CSSNodeStyleSetBorder(IntPtr node, CSSEdge edge, float border);

        [DllImport(DllName)]
        public static extern float CSSNodeStyleGetBorder(IntPtr node, CSSEdge edge);

        #endregion

        #region CSS_NODE_LAYOUT_PROPERTY

        [DllImport(DllName)]
        public static extern float CSSNodeLayoutGetLeft(IntPtr node);

        [DllImport(DllName)]
        public static extern float CSSNodeLayoutGetTop(IntPtr node);

        [DllImport(DllName)]
        public static extern float CSSNodeLayoutGetRight(IntPtr node);

        [DllImport(DllName)]
        public static extern float CSSNodeLayoutGetBottom(IntPtr node);

        [DllImport(DllName)]
        public static extern float CSSNodeLayoutGetWidth(IntPtr node);

        [DllImport(DllName)]
        public static extern float CSSNodeLayoutGetHeight(IntPtr node);

        [DllImport(DllName)]
        public static extern CSSDirection CSSNodeLayoutGetDirection(IntPtr node);

        #endregion
    }
}
