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
using System.Text;

#if (UNITY_IOS && !UNITY_EDITOR) || ENABLE_IL2CPP || __IOS__
using System.Runtime.InteropServices;
#endif
#if __IOS__
using ObjCRuntime;
#endif
#if ENABLE_IL2CPP
using AOT;
#endif

namespace Facebook.Yoga
{
    public class YogaConfig
    {

        private Native.YGConfigHandle _ygConfig;

        public YogaConfig()
        {
            _ygConfig = Native.YGConfigNew();
            if (_ygConfig.IsInvalid)
            {
                throw new InvalidOperationException("Failed to allocate native memory");
            }
        }

        internal Native.YGConfigHandle Handle {
            get {
                return _ygConfig;
            }
        }

        public void SetExperimentalFeatureEnabled(
            YogaExperimentalFeature feature,
            bool enabled)
        {
            Native.YGConfigSetExperimentalFeatureEnabled(_ygConfig, feature, enabled);
        }

        public bool IsExperimentalFeatureEnabled(YogaExperimentalFeature feature)
        {
            return Native.YGConfigIsExperimentalFeatureEnabled(_ygConfig, feature);
        }

    }

    public partial class YogaNode : IEnumerable<YogaNode>
    {
        private Native.YGNodeHandle _ygNode;
        private WeakReference _parent;
        private List<YogaNode> _children;
        private MeasureFunction _measureFunction;
        private BaselineFunction _baselineFunction;
        private object _data;
#if (UNITY_IOS && !UNITY_EDITOR) || ENABLE_IL2CPP || __IOS__
        private static YogaMeasureFunc _managedMeasure;
        private static YogaBaselineFunc _managedBaseline;
#else
        private YogaMeasureFunc _managedMeasure;
        private YogaBaselineFunc _managedBaseline;
#endif

        public YogaNode()
        {
            YogaLogger.Initialize();

            _ygNode = Native.YGNodeNew();
            if (_ygNode.IsInvalid)
            {
                throw new InvalidOperationException("Failed to allocate native memory");
            }
        }

        public YogaNode(YogaConfig config)
        {
            YogaLogger.Initialize();

            _ygNode = Native.YGNodeNewWithConfig(config.Handle);
            if (_ygNode.IsInvalid)
            {
                throw new InvalidOperationException("Failed to allocate native memory");
            }
        }

        public YogaNode(YogaNode srcNode)
            : this()
        {
            CopyStyle(srcNode);
        }

        public void Reset()
        {
            _measureFunction = null;
            _baselineFunction = null;
            _data = null;

            Native.YGNodeReset(_ygNode);
#if (UNITY_IOS && !UNITY_EDITOR) || ENABLE_IL2CPP || __IOS__
            _ygNode.ReleaseManaged();
#endif
        }

        public bool IsDirty
        {
            get
            {
                return Native.YGNodeIsDirty(_ygNode);
            }
        }

        public virtual void MarkDirty()
        {
            Native.YGNodeMarkDirty(_ygNode);
        }

        public bool HasNewLayout
        {
            get
            {
                return Native.YGNodeGetHasNewLayout(_ygNode);
            }
        }

        public void MarkHasNewLayout()
        {
            Native.YGNodeSetHasNewLayout(_ygNode, true);
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

        public bool IsBaselineDefined
        {
            get
            {
                return _baselineFunction != null;
            }
        }

        public void CopyStyle(YogaNode srcNode)
        {
            Native.YGNodeCopyStyle(_ygNode, srcNode._ygNode);
        }

        public YogaDirection StyleDirection
        {
            get
            {
                return Native.YGNodeStyleGetDirection(_ygNode);
            }

            set
            {
                Native.YGNodeStyleSetDirection(_ygNode, value);
            }
        }

        public YogaFlexDirection FlexDirection
        {
            get
            {
                return Native.YGNodeStyleGetFlexDirection(_ygNode);
            }

            set
            {
                Native.YGNodeStyleSetFlexDirection(_ygNode, value);
            }
        }

        public YogaJustify JustifyContent
        {
            get
            {
                return Native.YGNodeStyleGetJustifyContent(_ygNode);
            }

            set
            {
                Native.YGNodeStyleSetJustifyContent(_ygNode, value);
            }
        }

        public YogaDisplay Display
        {
            get
            {
                return Native.YGNodeStyleGetDisplay(_ygNode);
            }

            set
            {
                Native.YGNodeStyleSetDisplay(_ygNode, value);
            }
        }

        public YogaAlign AlignItems
        {
            get
            {
                return Native.YGNodeStyleGetAlignItems(_ygNode);
            }

            set
            {
                Native.YGNodeStyleSetAlignItems(_ygNode, value);
            }
        }

        public YogaAlign AlignSelf
        {
            get
            {
                return Native.YGNodeStyleGetAlignSelf(_ygNode);
            }

            set
            {
                Native.YGNodeStyleSetAlignSelf(_ygNode, value);
            }
        }

        public YogaAlign AlignContent
        {
            get
            {
                return Native.YGNodeStyleGetAlignContent(_ygNode);
            }

            set
            {
                Native.YGNodeStyleSetAlignContent(_ygNode, value);
            }
        }

        public YogaPositionType PositionType
        {
            get
            {
                return Native.YGNodeStyleGetPositionType(_ygNode);
            }

            set
            {
                Native.YGNodeStyleSetPositionType(_ygNode, value);
            }
        }

        public YogaWrap Wrap
        {
            get
            {
                return Native.YGNodeStyleGetFlexWrap(_ygNode);
            }

            set
            {
                Native.YGNodeStyleSetFlexWrap(_ygNode, value);
            }
        }

        public float Flex
        {
            set
            {
                Native.YGNodeStyleSetFlex(_ygNode, value);
            }
        }

        public float FlexGrow
        {
            get
            {
                return Native.YGNodeStyleGetFlexGrow(_ygNode);
            }

            set
            {
                Native.YGNodeStyleSetFlexGrow(_ygNode, value);
            }
        }

        public float FlexShrink
        {
            get
            {
                return Native.YGNodeStyleGetFlexShrink(_ygNode);
            }

            set
            {
                Native.YGNodeStyleSetFlexShrink(_ygNode, value);
            }
        }

        public YogaValue FlexBasis
        {
            get
            {
                return YogaValue.MarshalValue(Native.YGNodeStyleGetFlexBasis(_ygNode));
            }

            set
            {
                if (value.Unit == YogaUnit.Percent)
                {
                    Native.YGNodeStyleSetFlexBasisPercent(_ygNode, value.Value);
                }
                else if (value.Unit == YogaUnit.Auto)
                {
                    Native.YGNodeStyleSetFlexBasisAuto(_ygNode);
                }
                else
                {
                    Native.YGNodeStyleSetFlexBasis(_ygNode, value.Value);
                }
            }
        }

        public YogaValue Width
        {
            get
            {
                return YogaValue.MarshalValue(Native.YGNodeStyleGetWidth(_ygNode));
            }

            set
            {
                if (value.Unit == YogaUnit.Percent)
                {
                    Native.YGNodeStyleSetWidthPercent(_ygNode, value.Value);
                }
                else if (value.Unit == YogaUnit.Auto)
                {
                    Native.YGNodeStyleSetWidthAuto(_ygNode);
                }
                else
                {
                    Native.YGNodeStyleSetWidth(_ygNode, value.Value);
                }
            }
        }

        public YogaValue Height
        {
            get
            {
                return YogaValue.MarshalValue(Native.YGNodeStyleGetHeight(_ygNode));
            }

            set
            {
                if (value.Unit == YogaUnit.Percent)
                {
                    Native.YGNodeStyleSetHeightPercent(_ygNode, value.Value);
                }
                else if (value.Unit == YogaUnit.Auto)
                {
                    Native.YGNodeStyleSetHeightAuto(_ygNode);
                }
                else
                {
                    Native.YGNodeStyleSetHeight(_ygNode, value.Value);
                }
            }
        }

        public YogaValue MaxWidth
        {
            get
            {
                return YogaValue.MarshalValue(Native.YGNodeStyleGetMaxWidth(_ygNode));
            }

            set
            {
                if (value.Unit == YogaUnit.Percent)
                {
                    Native.YGNodeStyleSetMaxWidthPercent(_ygNode, value.Value);
                }
                else
                {
                    Native.YGNodeStyleSetMaxWidth(_ygNode, value.Value);
                }
            }
        }

        public YogaValue MaxHeight
        {
            get
            {
                return YogaValue.MarshalValue(Native.YGNodeStyleGetMaxHeight(_ygNode));
            }

            set
            {
                if (value.Unit == YogaUnit.Percent)
                {
                    Native.YGNodeStyleSetMaxHeightPercent(_ygNode, value.Value);
                }
                else
                {
                    Native.YGNodeStyleSetMaxHeight(_ygNode, value.Value);
                }
            }
        }

        public YogaValue MinWidth
        {
            get
            {
                return YogaValue.MarshalValue(Native.YGNodeStyleGetMinWidth(_ygNode));
            }

            set
            {
                if (value.Unit == YogaUnit.Percent)
                {
                    Native.YGNodeStyleSetMinWidthPercent(_ygNode, value.Value);
                }
                else
                {
                    Native.YGNodeStyleSetMinWidth(_ygNode, value.Value);
                }
            }
        }

        public YogaValue MinHeight
        {
            get
            {
                return YogaValue.MarshalValue(Native.YGNodeStyleGetMinHeight(_ygNode));
            }

            set
            {
                if (value.Unit == YogaUnit.Percent)
                {
                    Native.YGNodeStyleSetMinHeightPercent(_ygNode, value.Value);
                }
                else
                {
                    Native.YGNodeStyleSetMinHeight(_ygNode, value.Value);
                }
            }
        }

        public float StyleAspectRatio
        {
            get
            {
                return Native.YGNodeStyleGetAspectRatio(_ygNode);
            }

            set
            {
                Native.YGNodeStyleSetAspectRatio(_ygNode, value);
            }
        }

        public float LayoutX
        {
            get
            {
                return Native.YGNodeLayoutGetLeft(_ygNode);
            }
        }

        public float LayoutY
        {
            get
            {
                return Native.YGNodeLayoutGetTop(_ygNode);
            }
        }

        public float LayoutWidth
        {
            get
            {
                return Native.YGNodeLayoutGetWidth(_ygNode);
            }
        }

        public float LayoutHeight
        {
            get
            {
                return Native.YGNodeLayoutGetHeight(_ygNode);
            }
        }

        public YogaDirection LayoutDirection
        {
            get
            {
                return Native.YGNodeLayoutGetDirection(_ygNode);
            }
        }

        public YogaOverflow Overflow
        {
            get
            {
                return Native.YGNodeStyleGetOverflow(_ygNode);
            }

            set
            {
                Native.YGNodeStyleSetOverflow(_ygNode, value);
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
            Native.YGNodeSetHasNewLayout(_ygNode, false);
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
            Native.YGNodeInsertChild(_ygNode, node._ygNode, (uint)index);
        }

        public void RemoveAt(int index)
        {
            var child = _children[index];
            child._parent = null;
            _children.RemoveAt(index);
            Native.YGNodeRemoveChild(_ygNode, child._ygNode);
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
            if (measureFunction != null)
            {
#if (UNITY_IOS && !UNITY_EDITOR) || ENABLE_IL2CPP || __IOS__
                _managedMeasure = MeasureInternalAOT;
                _ygNode.SetContext(this);
#else
                _managedMeasure = MeasureInternal;
#endif
            }
            else
            {
                _managedMeasure = null;
            }
            Native.YGNodeSetMeasureFunc(_ygNode, _managedMeasure);
        }

        public void SetBaselineFunction(BaselineFunction baselineFunction)
        {
            _baselineFunction = baselineFunction;
            if (baselineFunction != null)
            {
#if (UNITY_IOS && !UNITY_EDITOR) || ENABLE_IL2CPP || __IOS__
                _managedBaseline = BaselineInternalAOT;
                _ygNode.SetContext(this);
#else
                _managedBaseline = BaselineInternal;
#endif
            }
            else
            {
                _managedBaseline = null;
            }
            Native.YGNodeSetBaselineFunc(_ygNode, _managedBaseline);
        }

        public void CalculateLayout()
        {
            Native.YGNodeCalculateLayout(
                _ygNode,
                YogaConstants.Undefined,
                YogaConstants.Undefined,
                Native.YGNodeStyleGetDirection(_ygNode));
        }

#if (UNITY_IOS && !UNITY_EDITOR) || ENABLE_IL2CPP || __IOS__
        [MonoPInvokeCallback(typeof(YogaMeasureFunc))]
        private static YogaSize MeasureInternalAOT(
            IntPtr ygNodePtr,
            float width,
            YogaMeasureMode widthMode,
            float height,
            YogaMeasureMode heightMode)
        {
            var node = Native.YGNodeHandle.GetManaged(ygNodePtr);
            return node.MeasureInternal(IntPtr.Zero, width, widthMode, height, heightMode);
        }
#endif

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

            return _measureFunction(this, width, widthMode, height, heightMode);
        }

#if (UNITY_IOS && !UNITY_EDITOR) || ENABLE_IL2CPP || __IOS__
        [MonoPInvokeCallback(typeof(YogaBaselineFunc))]
        private static float BaselineInternalAOT(
            IntPtr ygNodePtr,
            float width,
            float height)
        {
            var node = Native.YGNodeHandle.GetManaged(ygNodePtr);
            return node.BaselineInternal(IntPtr.Zero, width, height);
        }
#endif

        private float BaselineInternal(IntPtr node, float width, float height)
        {
            if (_baselineFunction == null)
            {
                throw new InvalidOperationException("Baseline function is not defined.");
            }

            return _baselineFunction(this, width, height);
        }

        public string Print(YogaPrintOptions options =
            YogaPrintOptions.Layout|YogaPrintOptions.Style|YogaPrintOptions.Children)
        {
            StringBuilder sb = new StringBuilder();
            YogaLogger.Func orig = YogaLogger.Logger;
            YogaLogger.Logger = (level, message) => {sb.Append(message);};
            Native.YGNodePrint(_ygNode, options);
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
            return Native.YGNodeGetInstanceCount();
        }
    }
}
