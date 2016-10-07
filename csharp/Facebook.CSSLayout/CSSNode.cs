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

namespace Facebook.CSSLayout
{
    public class CSSNode : IDisposable, IEnumerable<CSSNode>
    {
        private bool _isDisposed;
        private IntPtr _cssNode;

        private CSSNode _parent;
        private List<CSSNode> _children;
        private MeasureFunction _measureFunction;
        private CSSMeasureFunc _measureFunc;
        private CSSPrintFunc _printFunc;
        private object _data;

        public CSSNode()
        {
            _measureFunc = MeasureInternal;
            _printFunc = PrintInternal;
        }

        private void AssertNativeInstance()
        {
            if (_isDisposed)
            {
                throw new ObjectDisposedException("CSSNode");
            }

            if (_cssNode == IntPtr.Zero)
            {
                throw new InvalidOperationException("Null native pointer");
            }
        }

        ~CSSNode()
        {
            Dispose(false);
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        protected virtual void Dispose(bool disposing)
        {
            if (!_isDisposed)
            {
                if (disposing)
                {
                    FreeManaged();
                }

                FreeUnmanaged();
                _isDisposed = true;
            }
        }

        private void FreeManaged()
        {
            _children = null;
            _parent = null;
            _measureFunction = null;
        }

        private void FreeUnmanaged()
        {
            if (_cssNode != IntPtr.Zero)
            {
                Native.CSSNodeFree(_cssNode);
                _cssNode = IntPtr.Zero;
            }
        }

        public void Initialize()
        {
            if (_cssNode != IntPtr.Zero)
            {
                throw new InvalidOperationException("Allready initialized node");
            }

            _cssNode = Native.CSSNodeNew();
            _children = new List<CSSNode>(4);
            Native.CSSNodeSetPrintFunc(_cssNode, _printFunc);
        }

        public void Reset()
        {
            AssertNativeInstance();
            FreeManaged();
            FreeUnmanaged();
        }

        public bool IsDirty
        {
            get
            {
                AssertNativeInstance();
                return Native.CSSNodeIsDirty(_cssNode);
            }
        }

        public virtual void MarkDirty()
        {
            AssertNativeInstance();
            Native.CSSNodeMarkDirty(_cssNode);
        }

        public bool IsTextNode
        {
            get
            {
                AssertNativeInstance();
                return Native.CSSNodeGetIsTextnode(_cssNode);
            }

            set
            {
                AssertNativeInstance();
                Native.CSSNodeSetIsTextnode(_cssNode, value);
            }
        }

        public bool HasNewLayout
        {
            get
            {
                AssertNativeInstance();
                return Native.CSSNodeGetHasNewLayout(_cssNode);
            }
        }

        public void MarkHasNewLayout()
        {
            AssertNativeInstance();
            Native.CSSNodeSetHasNewLayout(_cssNode, true);
        }

        public CSSNode Parent
        {
            get
            {
                AssertNativeInstance();
                return _parent;
            }
        }

        public bool IsMeasureDefined
        {
            get
            {
                return _measureFunction != null;
            }
        }

        public CSSDirection StyleDirection
        {
            get
            {
                AssertNativeInstance();
                return Native.CSSNodeStyleGetDirection(_cssNode);
            }
            set
            {
                AssertNativeInstance();
                Native.CSSNodeStyleSetDirection(_cssNode, value);
            }
        }

        public CSSFlexDirection FlexDirection
        {
            get
            {
                AssertNativeInstance();
                return Native.CSSNodeStyleGetFlexDirection(_cssNode);
            }

            set
            {
                AssertNativeInstance();
                Native.CSSNodeStyleSetFlexDirection(_cssNode, value);
            }
        }

        public CSSJustify JustifyContent
        {
            get
            {
                AssertNativeInstance();
                return Native.CSSNodeStyleGetJustifyContent(_cssNode);
            }

            set
            {
                AssertNativeInstance();
                Native.CSSNodeStyleSetJustifyContent(_cssNode, value);
            }
        }

        public CSSAlign AlignItems
        {
            get
            {
                AssertNativeInstance();
                return Native.CSSNodeStyleGetAlignItems(_cssNode);
            }

            set
            {
                AssertNativeInstance();
                Native.CSSNodeStyleSetAlignItems(_cssNode, value);
            }
        }

        public CSSAlign AlignSelf
        {
            get
            {
                AssertNativeInstance();
                return Native.CSSNodeStyleGetAlignSelf(_cssNode);
            }

            set
            {
                AssertNativeInstance();
                Native.CSSNodeStyleSetAlignSelf(_cssNode, value);
            }
        }

        public CSSAlign AlignContent
        {
            get
            {
                AssertNativeInstance();
                return Native.CSSNodeStyleGetAlignContent(_cssNode);
            }

            set
            {
                AssertNativeInstance();
                Native.CSSNodeStyleSetAlignContent(_cssNode, value);
            }
        }

        public CSSPositionType PositionType
        {
            get
            {
                AssertNativeInstance();
                return Native.CSSNodeStyleGetPositionType(_cssNode);
            }

            set
            {
                AssertNativeInstance();
                Native.CSSNodeStyleSetPositionType(_cssNode, value);
            }
        }

        public CSSWrap Wrap
        {
            get
            {
                AssertNativeInstance();
                return Native.CSSNodeStyleGetFlexWrap(_cssNode);
            }

            set
            {
                AssertNativeInstance();
                Native.CSSNodeStyleSetFlexWrap(_cssNode, value);
            }
        }

        public float Flex
        {
            get
            {
                AssertNativeInstance();
                return Native.CSSNodeStyleGetFlex(_cssNode);
            }

            set
            {
                AssertNativeInstance();
                Native.CSSNodeStyleSetFlex(_cssNode, value);
            }
        }

        public float FlexGrow
        {
            get
            {
                AssertNativeInstance();
                return Native.CSSNodeStyleGetFlexGrow(_cssNode);
            }

            set
            {
                AssertNativeInstance();
                Native.CSSNodeStyleSetFlexGrow(_cssNode, value);
            }
        }

        public float FlexShrink
        {
            get
            {
                AssertNativeInstance();
                return Native.CSSNodeStyleGetFlexShrink(_cssNode);
            }

            set
            {
                AssertNativeInstance();
                Native.CSSNodeStyleSetFlexShrink(_cssNode, value);
            }
        }

        public float FlexBasis
        {
            get
            {
                AssertNativeInstance();
                return Native.CSSNodeStyleGetFlexBasis(_cssNode);
            }

            set
            {
                AssertNativeInstance();
                Native.CSSNodeStyleSetFlexBasis(_cssNode, value);
            }
        }

        public Spacing GetMargin()
        {
            AssertNativeInstance();

            var margin = new Spacing();
            margin.Set(Spacing.Left, Native.CSSNodeStyleGetMargin(_cssNode, CSSEdge.Left));
            margin.Set(Spacing.Top, Native.CSSNodeStyleGetMargin(_cssNode, CSSEdge.Top));
            margin.Set(Spacing.Right, Native.CSSNodeStyleGetMargin(_cssNode, CSSEdge.Right));
            margin.Set(Spacing.Bottom, Native.CSSNodeStyleGetMargin(_cssNode, CSSEdge.Bottom));
            margin.Set(Spacing.Start, Native.CSSNodeStyleGetMargin(_cssNode, CSSEdge.Start));
            margin.Set(Spacing.End, Native.CSSNodeStyleGetMargin(_cssNode, CSSEdge.End));

            return margin;
        }

        public void SetMargin(CSSEdge edge, float value)
        {
            AssertNativeInstance();
            Native.CSSNodeStyleSetMargin(_cssNode, edge, value);
        }

        public Spacing GetPadding()
        {
            AssertNativeInstance();

            var padding = new Spacing();
            padding.Set(Spacing.Left, Native.CSSNodeStyleGetPadding(_cssNode, CSSEdge.Left));
            padding.Set(Spacing.Top, Native.CSSNodeStyleGetPadding(_cssNode, CSSEdge.Top));
            padding.Set(Spacing.Right, Native.CSSNodeStyleGetPadding(_cssNode, CSSEdge.Right));
            padding.Set(Spacing.Bottom, Native.CSSNodeStyleGetPadding(_cssNode, CSSEdge.Bottom));
            padding.Set(Spacing.Start, Native.CSSNodeStyleGetPadding(_cssNode, CSSEdge.Start));
            padding.Set(Spacing.End, Native.CSSNodeStyleGetPadding(_cssNode, CSSEdge.End));

            return padding;
        }

        public void SetPadding(CSSEdge edge, float padding)
        {
            AssertNativeInstance();
            Native.CSSNodeStyleSetPadding(_cssNode, edge, padding);
        }

        public Spacing GetBorder()
        {
            AssertNativeInstance();

            var border = new Spacing();
            border.Set(Spacing.Left, Native.CSSNodeStyleGetBorder(_cssNode, CSSEdge.Left));
            border.Set(Spacing.Top, Native.CSSNodeStyleGetBorder(_cssNode, CSSEdge.Top));
            border.Set(Spacing.Right, Native.CSSNodeStyleGetBorder(_cssNode, CSSEdge.Right));
            border.Set(Spacing.Bottom, Native.CSSNodeStyleGetBorder(_cssNode, CSSEdge.Bottom));
            border.Set(Spacing.Start, Native.CSSNodeStyleGetBorder(_cssNode, CSSEdge.Start));
            border.Set(Spacing.End, Native.CSSNodeStyleGetBorder(_cssNode, CSSEdge.End));

            return border;
        }

        public void SetBorder(CSSEdge edge, float border)
        {
            AssertNativeInstance();
            Native.CSSNodeStyleSetBorder(_cssNode, edge, border);
        }

        public Spacing GetPosition()
        {
            AssertNativeInstance();

            var position = new Spacing();
            position.Set(Spacing.Left, Native.CSSNodeStyleGetPosition(_cssNode, CSSEdge.Left));
            position.Set(Spacing.Top, Native.CSSNodeStyleGetPosition(_cssNode, CSSEdge.Top));
            position.Set(Spacing.Right, Native.CSSNodeStyleGetPosition(_cssNode, CSSEdge.Right));
            position.Set(Spacing.Bottom, Native.CSSNodeStyleGetPosition(_cssNode, CSSEdge.Bottom));
            position.Set(Spacing.Start, Native.CSSNodeStyleGetPosition(_cssNode, CSSEdge.Start));
            position.Set(Spacing.End, Native.CSSNodeStyleGetPosition(_cssNode, CSSEdge.End));

            return position;
        }

        public void SetPosition(CSSEdge edge, float position)
        {
            AssertNativeInstance();
        }

        public float StyleWidth
        {
            get
            {
                AssertNativeInstance();
                return Native.CSSNodeStyleGetWidth(_cssNode);
            }

            set
            {
                AssertNativeInstance();
                Native.CSSNodeStyleSetWidth(_cssNode, value);
            }
        }

        public float StyleHeight
        {
            get
            {
                AssertNativeInstance();
                return Native.CSSNodeStyleGetHeight(_cssNode);
            }

            set
            {
                AssertNativeInstance();
                Native.CSSNodeStyleSetHeight(_cssNode, value);
            }
        }

        public float StyleMaxWidth
        {
            get
            {
                AssertNativeInstance();
                return Native.CSSNodeStyleGetMaxWidth(_cssNode);
            }

            set
            {
                AssertNativeInstance();
                Native.CSSNodeStyleSetMaxWidth(_cssNode, value);
            }
        }

        public float StyleMaxHeight
        {
            get
            {
                AssertNativeInstance();
                return Native.CSSNodeStyleGetMaxHeight(_cssNode);
            }

            set
            {
                AssertNativeInstance();
                Native.CSSNodeStyleSetMaxHeight(_cssNode, value);
            }
        }

        public float StyleMinWidth
        {
            get
            {
                AssertNativeInstance();
                return Native.CSSNodeStyleGetMinWidth(_cssNode);
            }

            set
            {
                AssertNativeInstance();
                Native.CSSNodeStyleSetMinWidth(_cssNode, value);
            }
        }

        public float StyleMinHeight
        {
            get
            {
                AssertNativeInstance();
                return Native.CSSNodeStyleGetMinHeight(_cssNode);
            }

            set
            {
                AssertNativeInstance();
                Native.CSSNodeStyleSetMinHeight(_cssNode, value);
            }
        }

        public float LayoutX
        {
            get
            {
                AssertNativeInstance();
                return Native.CSSNodeLayoutGetLeft(_cssNode);
            }
        }

        public float LayoutY
        {
            get
            {
                AssertNativeInstance();
                return Native.CSSNodeLayoutGetTop(_cssNode);
            }
        }

        public float LayoutWidth
        {
            get
            {
                AssertNativeInstance();
                return Native.CSSNodeLayoutGetWidth(_cssNode);
            }
        }

        public float LayoutHeight
        {
            get
            {
                AssertNativeInstance();
                return Native.CSSNodeLayoutGetHeight(_cssNode);
            }
        }

        public CSSDirection LayoutDirection
        {
            get
            {
                AssertNativeInstance();
                return Native.CSSNodeLayoutGetDirection(_cssNode);
            }
        }

        public CSSOverflow Overflow
        {
            get
            {
                AssertNativeInstance();
                return Native.CSSNodeStyleGetOverflow(_cssNode);
            }

            set
            {
                AssertNativeInstance();
                Native.CSSNodeStyleSetOverflow(_cssNode, value);
            }
        }

        public object Data
        {
            get
            {
                AssertNativeInstance();
                return _data;
            }

            set
            {
                AssertNativeInstance();
                _data = value;
            }
        }

        public CSSNode this[int index]
        {
            get
            {
                AssertNativeInstance();
                return _children[index];
            }
        }

        public int Count
        {
            get
            {
                AssertNativeInstance();
                return _children.Count;
            }
        }

        public void MarkLayoutSeen()
        {
            AssertNativeInstance();
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

        public void Insert(int index, CSSNode node)
        {
            AssertNativeInstance();
            _children.Insert(index, node);
            node._parent = this;
            Native.CSSNodeInsertChild(_cssNode, node._cssNode, (uint)index);
        }

        public void RemoveAt(int index)
        {
            AssertNativeInstance();
            var child = _children[index];
            child._parent = null;
            _children.RemoveAt(index);
            Native.CSSNodeRemoveChild(_cssNode, child._cssNode);
        }

        public int IndexOf(CSSNode node)
        {
            AssertNativeInstance();
            return _children.IndexOf(node);
        }

        public void SetMeasureFunction(MeasureFunction measureFunction)
        {
            AssertNativeInstance();
            _measureFunction = measureFunction;
            Native.CSSNodeSetMeasureFunc(_cssNode, measureFunction != null ? _measureFunc : null);
        }

        public void CalculateLayout()
        {
            AssertNativeInstance();
            Native.CSSNodeCalculateLayout(_cssNode, CSSConstants.Undefined, CSSConstants.Undefined, Native.CSSNodeStyleGetDirection(_cssNode));
        }

        public long Measure(CSSNode node, float width, CSSMeasureMode widthMode, float height, CSSMeasureMode heightMode)
        {
            if (_measureFunction == null)
            {
                throw new InvalidOperationException(@"Measure function is not defined.");
            }

            var output = new MeasureOutput();

            _measureFunction(this,
                width,
                widthMode,
                height,
                heightMode,
                output);

            return ((long)output.Width) << 32 | ((long)output.Height);
        }

        private CSSSize MeasureInternal(
            IntPtr context,
            float width,
            CSSMeasureMode widthMode,
            float height,
            CSSMeasureMode heightMode)
        {
            var measureResult = Measure(this, width, widthMode, height, heightMode);
            var measuredWidth = 0xFFFFFFFF & (measureResult >> 32);
            var measuredHeight = 0xFFFFFFFF & measureResult;

            return new CSSSize { width = measuredWidth, height = measuredHeight };
        }

        private void PrintInternal(IntPtr context)
        {
            System.Diagnostics.Debug.WriteLine(ToString());
        }

        public IEnumerator<CSSNode> GetEnumerator()
        {
            return ((IEnumerable<CSSNode>)_children).GetEnumerator();
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return ((IEnumerable<CSSNode>)_children).GetEnumerator();
        }
    }
}
