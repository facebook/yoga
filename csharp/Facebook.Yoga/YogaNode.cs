/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

using System;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Text;

namespace Facebook.Yoga
{
    public partial class YogaNode : IEnumerable<YogaNode>
    {
        private IntPtr _cssNode;
        private WeakReference _parent;
        private List<YogaNode> _children;
        private MeasureFunction _measureFunction;
        private YogaMeasureFunc _cssMeasureFunc;
        private object _data;

        public YogaNode()
        {
            YogaLogger.Initialize();

            _cssNode = Native.CSSNodeNew();
            if (_cssNode == IntPtr.Zero)
            {
                throw new InvalidOperationException("Failed to allocate native memory");
            }
        }

        ~YogaNode()
        {
            Native.CSSNodeFree(_cssNode);
        }

        public void Reset()
        {
            _measureFunction = null;
            _data = null;

            Native.CSSNodeReset(_cssNode);
        }

        public bool IsDirty
        {
            get
            {
                return Native.CSSNodeIsDirty(_cssNode);
            }
        }

        public virtual void MarkDirty()
        {
            Native.CSSNodeMarkDirty(_cssNode);
        }

        public bool HasNewLayout
        {
            get
            {
                return Native.CSSNodeGetHasNewLayout(_cssNode);
            }
        }

        public void MarkHasNewLayout()
        {
            Native.CSSNodeSetHasNewLayout(_cssNode, true);
        }

        public YogaNode Parent
        {
            get
            {
                return _parent != null ? _parent.Target as YogaNode : null;
            }
        }

        public bool IsMeasureDefined
        {
            get
            {
                return _measureFunction != null;
            }
        }

        public void CopyStyle(YogaNode srcNode)
        {
            Native.CSSNodeCopyStyle(_cssNode, srcNode._cssNode);
        }

        public YogaDirection StyleDirection
        {
            get
            {
                return Native.CSSNodeStyleGetDirection(_cssNode);
            }

            set
            {
                Native.CSSNodeStyleSetDirection(_cssNode, value);
            }
        }

        public YogaFlexDirection FlexDirection
        {
            get
            {
                return Native.CSSNodeStyleGetFlexDirection(_cssNode);
            }

            set
            {
                Native.CSSNodeStyleSetFlexDirection(_cssNode, value);
            }
        }

        public YogaJustify JustifyContent
        {
            get
            {
                return Native.CSSNodeStyleGetJustifyContent(_cssNode);
            }

            set
            {
                Native.CSSNodeStyleSetJustifyContent(_cssNode, value);
            }
        }

        public YogaAlign AlignItems
        {
            get
            {
                return Native.CSSNodeStyleGetAlignItems(_cssNode);
            }

            set
            {
                Native.CSSNodeStyleSetAlignItems(_cssNode, value);
            }
        }

        public YogaAlign AlignSelf
        {
            get
            {
                return Native.CSSNodeStyleGetAlignSelf(_cssNode);
            }

            set
            {
                Native.CSSNodeStyleSetAlignSelf(_cssNode, value);
            }
        }

        public YogaAlign AlignContent
        {
            get
            {
                return Native.CSSNodeStyleGetAlignContent(_cssNode);
            }

            set
            {
                Native.CSSNodeStyleSetAlignContent(_cssNode, value);
            }
        }

        public YogaPositionType PositionType
        {
            get
            {
                return Native.CSSNodeStyleGetPositionType(_cssNode);
            }

            set
            {
                Native.CSSNodeStyleSetPositionType(_cssNode, value);
            }
        }

        public YogaWrap Wrap
        {
            get
            {
                return Native.CSSNodeStyleGetFlexWrap(_cssNode);
            }

            set
            {
                Native.CSSNodeStyleSetFlexWrap(_cssNode, value);
            }
        }

        public float Flex
        {
            set
            {
                Native.CSSNodeStyleSetFlex(_cssNode, value);
            }
        }

        public float FlexGrow
        {
            get
            {
                return Native.CSSNodeStyleGetFlexGrow(_cssNode);
            }

            set
            {
                Native.CSSNodeStyleSetFlexGrow(_cssNode, value);
            }
        }

        public float FlexShrink
        {
            get
            {
                return Native.CSSNodeStyleGetFlexShrink(_cssNode);
            }

            set
            {
                Native.CSSNodeStyleSetFlexShrink(_cssNode, value);
            }
        }

        public float FlexBasis
        {
            get
            {
                return Native.CSSNodeStyleGetFlexBasis(_cssNode);
            }

            set
            {
                Native.CSSNodeStyleSetFlexBasis(_cssNode, value);
            }
        }

        public float GetMargin(YogaEdge edge)
        {
            return Native.CSSNodeStyleGetMargin(_cssNode, edge);
        }

        public void SetMargin(YogaEdge edge, float value)
        {
            Native.CSSNodeStyleSetMargin(_cssNode, edge, value);
        }

        public float GetPadding(YogaEdge edge)
        {
            return Native.CSSNodeStyleGetPadding(_cssNode, edge);
        }

        public void SetPadding(YogaEdge edge, float padding)
        {
            Native.CSSNodeStyleSetPadding(_cssNode, edge, padding);
        }

        public float GetBorder(YogaEdge edge)
        {
            return Native.CSSNodeStyleGetBorder(_cssNode, edge);
        }

        public void SetBorder(YogaEdge edge, float border)
        {
            Native.CSSNodeStyleSetBorder(_cssNode, edge, border);
        }

        public float GetPosition(YogaEdge edge)
        {
            return Native.CSSNodeStyleGetPosition(_cssNode, edge);
        }

        public void SetPosition(YogaEdge edge, float position)
        {
            Native.CSSNodeStyleSetPosition(_cssNode, edge, position);
        }

        public float Width
        {
            get
            {
                return Native.CSSNodeStyleGetWidth(_cssNode);
            }

            set
            {
                Native.CSSNodeStyleSetWidth(_cssNode, value);
            }
        }

        public float Height
        {
            get
            {
                return Native.CSSNodeStyleGetHeight(_cssNode);
            }

            set
            {
                Native.CSSNodeStyleSetHeight(_cssNode, value);
            }
        }

        public float MaxWidth
        {
            get
            {
                return Native.CSSNodeStyleGetMaxWidth(_cssNode);
            }

            set
            {
                Native.CSSNodeStyleSetMaxWidth(_cssNode, value);
            }
        }

        public float MaxHeight
        {
            get
            {
                return Native.CSSNodeStyleGetMaxHeight(_cssNode);
            }

            set
            {
                Native.CSSNodeStyleSetMaxHeight(_cssNode, value);
            }
        }

        public float MinWidth
        {
            get
            {
                return Native.CSSNodeStyleGetMinWidth(_cssNode);
            }

            set
            {
                Native.CSSNodeStyleSetMinWidth(_cssNode, value);
            }
        }

        public float MinHeight
        {
            get
            {
                return Native.CSSNodeStyleGetMinHeight(_cssNode);
            }

            set
            {
                Native.CSSNodeStyleSetMinHeight(_cssNode, value);
            }
        }

        public float StyleAspectRatio
        {
            get
            {
                return Native.CSSNodeStyleGetAspectRatio(_cssNode);
            }

            set
            {
                Native.CSSNodeStyleSetAspectRatio(_cssNode, value);
            }
        }

        public float LayoutX
        {
            get
            {
                return Native.CSSNodeLayoutGetLeft(_cssNode);
            }
        }

        public float LayoutY
        {
            get
            {
                return Native.CSSNodeLayoutGetTop(_cssNode);
            }
        }

        public float LayoutWidth
        {
            get
            {
                return Native.CSSNodeLayoutGetWidth(_cssNode);
            }
        }

        public float LayoutHeight
        {
            get
            {
                return Native.CSSNodeLayoutGetHeight(_cssNode);
            }
        }

        public YogaDirection LayoutDirection
        {
            get
            {
                return Native.CSSNodeLayoutGetDirection(_cssNode);
            }
        }

        public YogaOverflow Overflow
        {
            get
            {
                return Native.CSSNodeStyleGetOverflow(_cssNode);
            }

            set
            {
                Native.CSSNodeStyleSetOverflow(_cssNode, value);
            }
        }

        public object Data
        {
            get
            {
                return _data;
            }

            set
            {
                _data = value;
            }
        }

        public YogaNode this[int index]
        {
            get
            {
                return _children[index];
            }
        }

        public int Count
        {
            get
            {
                return _children != null ? _children.Count : 0;
            }
        }

        public void MarkLayoutSeen()
        {
            Native.CSSNodeSetHasNewLayout(_cssNode, false);
        }

        public bool ValuesEqual(float f1, float f2)
        {
            if (float.IsNaN(f1) || float.IsNaN(f2))
            {
                return float.IsNaN(f1) && float.IsNaN(f2);
            }

            return Math.Abs(f2 - f1) < float.Epsilon;
        }

        public void Insert(int index, YogaNode node)
        {
            if (_children == null)
            {
                _children = new List<YogaNode>(4);
            }
            _children.Insert(index, node);
            node._parent = new WeakReference(this);
            Native.CSSNodeInsertChild(_cssNode, node._cssNode, (uint)index);
        }

        public void RemoveAt(int index)
        {
            var child = _children[index];
            child._parent = null;
            _children.RemoveAt(index);
            Native.CSSNodeRemoveChild(_cssNode, child._cssNode);
        }

        public void Clear()
        {
            if (_children != null)
            {
                while (_children.Count > 0)
                {
                    RemoveAt(_children.Count-1);
                }
            }
        }

        public int IndexOf(YogaNode node)
        {
            return _children != null ? _children.IndexOf(node) : -1;
        }

        public void SetMeasureFunction(MeasureFunction measureFunction)
        {
            _measureFunction = measureFunction;
            _cssMeasureFunc = measureFunction != null ? MeasureInternal : (YogaMeasureFunc)null;
            Native.CSSNodeSetMeasureFunc(_cssNode, _cssMeasureFunc);
        }

        public void CalculateLayout()
        {
            Native.CSSNodeCalculateLayout(
                _cssNode,
                YogaConstants.Undefined,
                YogaConstants.Undefined,
                Native.CSSNodeStyleGetDirection(_cssNode));
        }

        private YogaSize MeasureInternal(
            IntPtr node,
            float width,
            YogaMeasureMode widthMode,
            float height,
            YogaMeasureMode heightMode)
        {
            if (_measureFunction == null)
            {
                throw new InvalidOperationException("Measure function is not defined.");
            }

            long output = _measureFunction(this, width, widthMode, height, heightMode);
            return new YogaSize { width = MeasureOutput.GetWidth(output), height = MeasureOutput.GetHeight(output) };
        }

        public string Print(YogaPrintOptions options =
            YogaPrintOptions.Layout|YogaPrintOptions.Style|YogaPrintOptions.Children)
        {
            StringBuilder sb = new StringBuilder();
            YogaLogger.Func orig = YogaLogger.Logger;
            YogaLogger.Logger = (level, message) => {sb.Append(message);};
            Native.CSSNodePrint(_cssNode, options);
            YogaLogger.Logger = orig;
            return sb.ToString();
        }

        public IEnumerator<YogaNode> GetEnumerator()
        {
            return _children != null ? ((IEnumerable<YogaNode>)_children).GetEnumerator() :
                System.Linq.Enumerable.Empty<YogaNode>().GetEnumerator();
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return _children != null ? ((IEnumerable<YogaNode>)_children).GetEnumerator() :
                System.Linq.Enumerable.Empty<YogaNode>().GetEnumerator();
        }

        public static int GetInstanceCount()
        {
            return Native.CSSNodeGetInstanceCount();
        }

        public static void SetExperimentalFeatureEnabled(
            YogaExperimentalFeature feature,
            bool enabled)
        {
            Native.CSSLayoutSetExperimentalFeatureEnabled(feature, enabled);
        }

        public static bool IsExperimentalFeatureEnabled(YogaExperimentalFeature feature)
        {
            return Native.CSSLayoutIsExperimentalFeatureEnabled(feature);
        }
    }
}
