using System;
using System.Collections.Generic;
using System.Text;

namespace Facebook.CSSLayout
{
    public class CSSNode : ICSSNode
    {
        private enum LayoutState
        {
            /**
             * Some property of this node or its children has changes and the current values in
             * {@link #layout} are not valid.
             */
            Dirty,

            /**
             * This node has a new layout relative to the last time {@link #markLayoutSeen()} was called.
             */
            HasNewLayout,

            /**
             * {@link #layout} is valid for the node's properties and this layout has been marked as
             * having been seen.
             */
            UpToDate,
        }

        public CSSStyle Style { get; } = new CSSStyle();
        public CSSLayout Layout { get; } = new CSSLayout();
        public CachedCSSLayout LastLayout { get; } = new CachedCSSLayout();
        public int LineIndex { get; set; } = 0;
        public CSSNode NextChild { get; set; }

        private List<CSSNode> _children;
        private CSSNode _parent;
        private MeasureFunction _measureFunction = null;
        private LayoutState _layoutState = LayoutState.Dirty;

        public MeasureOutput Measure(MeasureOutput measureOutput, float width, CSSMeasureMode widthMode, float height, CSSMeasureMode heightMode)
        {
            if (!IsMeasureDefined)
            {
                throw new InvalidOperationException(@"Measure function isn't defined!");
            }

            _measureFunction(this, width, widthMode, height, heightMode, measureOutput);
            return measureOutput;
        }

        ICSSNode ICSSNode.this[int index]
        {
            get
            {
                return this[index];
            }
        }

        public CSSNode this[int index]
        {
            get
            {
                if (_children == null)
                {
                    throw new InvalidOperationException(@"Children not yet initialized.");
                }
                return _children[index];
            }
        }

        public CSSAlign AlignContent
        {
            get
            {
                return Style.AlignContent;
            }

            set
            {
                if (Style.AlignContent != value)
                {
                    Style.AlignContent = value;
                    MarkDirty();
                }
            }
        }

        public CSSAlign AlignItems
        {
            get
            {
                return Style.AlignItems;
            }

            set
            {
                if (Style.AlignItems != value)
                {
                    Style.AlignItems = value;
                    MarkDirty();
                }
            }
        }

        public CSSAlign AlignSelf
        {
            get
            {
                return Style.AlignSelf;
            }

            set
            {
                if (Style.AlignSelf != value)
                {
                    Style.AlignSelf = value;
                    MarkDirty();
                }
            }
        }

        public int Count
        {
            get
            {
                return _children == null ? 0 : _children.Count;
            }
        }

        public object Data { get; set; }

        public float Flex
        {
            get
            {
                if (Style.FlexGrow > 0)
                {
                    return Style.FlexGrow;
                }
                else if (Style.FlexShrink > 0)
                {
                    return -Style.FlexShrink;
                }

                return 0;
            }

            set
            {
                if (CSSConstants.IsUndefined(value) || value == 0)
                {
                    FlexGrow = 0;
                    FlexShrink = 0;
                    FlexBasis = CSSConstants.UNDEFINED;
                }
                else if (value > 0)
                {
                    FlexGrow = value;
                    FlexShrink = 0;
                    FlexBasis = 0;
                }
                else
                {
                    FlexGrow = 0;
                    FlexShrink = -value;
                    FlexBasis = CSSConstants.UNDEFINED;
                }
            }
        }

        public float FlexBasis
        {
            get
            {
                return Style.FlexBasis;
            }

            set
            {
                if (!ValuesEqual(Style.FlexBasis, value))
                {
                    Style.FlexBasis = value;
                    MarkDirty();
                }
            }
        }

        public CSSFlexDirection FlexDirection
        {
            get
            {
                return Style.FlexDirection;
            }

            set
            {
                if (Style.FlexDirection != value)
                {
                    Style.FlexDirection = value;
                    MarkDirty();
                }
            }
        }

        public float FlexGrow
        {
            get
            {
                return Style.FlexGrow;
            }

            set
            {
                if (!ValuesEqual(Style.FlexGrow, value))
                {
                    Style.FlexGrow = value;
                    MarkDirty();
                }
            }
        }

        public float FlexShrink
        {
            get
            {
                return Style.FlexShrink;
            }

            set
            {
                if (!ValuesEqual(Style.FlexShrink, value))
                {
                    Style.FlexShrink = value;
                    MarkDirty();
                }
            }
        }

        public bool HasNewLayout
        {
            get
            {
                return _layoutState == LayoutState.HasNewLayout;
            }
        }

        public void MarkHasNewLayout()
        {
            _layoutState = LayoutState.HasNewLayout;
        }

        public bool IsDirty
        {
            get
            {
                return _layoutState == LayoutState.Dirty;
            }
        }

        public bool IsMeasureDefined
        {
            get
            {
                return _measureFunction != null;
            }
        }

        public bool IsTextNode { get; set; }

        public CSSJustify JustifyContent
        {
            get
            {
                return Style.JustifyContent;
            }

            set
            {
                if (Style.JustifyContent != value)
                {
                    Style.JustifyContent = value;
                    MarkDirty();
                }
            }
        }

        public CSSDirection LayoutDirection
        {
            get
            {
                throw new NotImplementedException();
            }
        }

        public float LayoutHeight
        {
            get
            {
                throw new NotImplementedException();
            }
        }

        public float LayoutWidth
        {
            get
            {
                throw new NotImplementedException();
            }
        }

        public float LayoutX
        {
            get
            {
                throw new NotImplementedException();
            }
        }

        public float LayoutY
        {
            get
            {
                throw new NotImplementedException();
            }
        }

        public CSSOverflow Overflow
        {
            get
            {
                throw new NotImplementedException();
            }

            set
            {
                throw new NotImplementedException();
            }
        }

        public ICSSNode Parent
        {
            get
            {
                return _parent;
            }
        }

        public CSSPositionType PositionType
        {
            get
            {
                return Style.PositionType;
            }

            set
            {
                if (Style.PositionType != value)
                {
                    Style.PositionType = value;
                    MarkDirty();
                }
            }
        }

        public CSSDirection StyleDirection
        {
            get
            {
                return Style.Direction;
            }

            set
            {
                if (Style.Direction != value)
                {
                    Style.Direction = value;
                    MarkDirty();
                }
            }
        }

        public float StyleHeight
        {
            get
            {
                return Style.Dimensions[CSSLayout.DIMENSION_HEIGHT];
            }

            set
            {
                if (!ValuesEqual(Style.Dimensions[CSSLayout.DIMENSION_HEIGHT], value))
                {
                    Style.Dimensions[CSSLayout.DIMENSION_HEIGHT] = value;
                    MarkDirty();
                }
            }
        }

        public float StyleMaxHeight
        {
            get
            {
                return Style.MaxHeight;
            }

            set
            {
                if (!ValuesEqual(Style.MaxHeight, value))
                {
                    Style.MaxHeight = value;
                    MarkDirty();
                }
            }
        }

        public float StyleMaxWidth
        {
            get
            {
                return Style.MaxWidth;
            }

            set
            {
                if (!ValuesEqual(Style.MaxWidth, value))
                {
                    Style.MaxWidth = value;
                    MarkDirty();
                }
            }
        }

        public float StyleMinHeight
        {
            get
            {
                return Style.MinHeight;
            }

            set
            {
                if (!ValuesEqual(Style.MinHeight, value))
                {
                    Style.MinHeight = value;
                    MarkDirty();
                }
            }
        }

        public float StyleMinWidth
        {
            get
            {
                return Style.MinWidth;
            }

            set
            {
                if (!ValuesEqual(Style.MinWidth, value))
                {
                    Style.MinWidth = value;
                    MarkDirty();
                }
            }
        }

        public float StyleWidth
        {
            get
            {
                return Style.Dimensions[CSSLayout.DIMENSION_WIDTH];
            }

            set
            {
                if (!ValuesEqual(Style.Dimensions[CSSLayout.DIMENSION_WIDTH], value))
                {
                    Style.Dimensions[CSSLayout.DIMENSION_WIDTH] = value;
                    MarkDirty();
                }
            }
        }

        public CSSWrap Wrap
        {
            get
            {
                return Style.FlexWrap;
            }

            set
            {
                if (Style.FlexWrap != value)
                {
                    Style.FlexWrap = value;
                    MarkDirty();
                }
            }
        }

        public void CalculateLayout(CSSLayoutContext layoutContext)
        {
            throw new NotImplementedException();
        }

        public Spacing GetBorder()
        {
            return Style.Border;
        }

        public Spacing GetMargin()
        {
            return Style.Margin;
        }

        public Spacing GetPadding()
        {
            return Style.Padding;
        }

        public Spacing GetPosition()
        {
            return Style.Position;
        }

        int ICSSNode.IndexOf(ICSSNode node)
        {
            return IndexOf((CSSNode)node);
        }

        public int IndexOf(CSSNode node)
        {
            if (_children == null)
            {
                throw new InvalidOperationException(@"Children not yet initialized.");
            }

            return _children.IndexOf(node);
        }

        public void Initialize()
        {
            Reset();
        }

        public void Insert(int index, CSSNode node)
        {
            if (node._parent != null)
            {
                throw new InvalidOperationException(@"Child already has a parent, it must be removed first.");
            }

            if (_children == null)
            {
                // 4 is kinda arbitrary, but the default of 10 seems really high for an average View.
                _children = new List<CSSNode>(4);
            }

            _children.Insert(index, node);
            node._parent = this;
            MarkDirty();
        }

        void ICSSNode.Insert(int index, ICSSNode node)
        {
            Insert(index, (CSSNode)node);
        }

        public void MarkDirty()
        {
            if (_layoutState == LayoutState.Dirty)
            {
                return;
            }
            else if (_layoutState == LayoutState.HasNewLayout)
            {
                throw new InvalidOperationException(@"Previous layout was ignored! MarkLayoutSeen() never called");
            }

            _layoutState = LayoutState.Dirty;
            _parent?.MarkDirty();
        }

        public void MarkLayoutSeen()
        {
            if (!HasNewLayout)
            {
                throw new InvalidOperationException(@"Expected node to have a new layout to be seen!");
            }

            _layoutState = LayoutState.UpToDate;
        }

        public void RemoveAt(int index)
        {
            if (_children == null)
            {
                throw new InvalidOperationException(@"Children not yet initialized.");
            }

            var removed = _children[index];
            _children.RemoveAt(index);
            removed._parent = null;
            MarkDirty();
        }

        public void IndentString(StringBuilder result, int level)
        {
            // Spaces and tabs are dropped by IntelliJ logcat integration, so rely on __ instead.
            var indentation = new StringBuilder();
            for (int i = 0; i < level; ++i)
            {
                indentation.Append("__");
            }

            result.Append(indentation);
            result.Append(Layout.ToString());

            if (Count == 0) { return; }

            result.Append(", children: [\n");
            for (int i = 0; i < Count; i++)
            {
                this[i].IndentString(result, level + 1);
                result.Append("\n");
            }
            result.Append(indentation + "]");
        }

        public override string ToString()
        {
            StringBuilder sb = new StringBuilder();
            IndentString(sb, 0);
            return sb.ToString();
        }

        public void Reset()
        {
            throw new NotImplementedException();
        }

        public void SetBorder(CSSEdge edge, float border)
        {
            if (Style.Border.Set((int)edge, border))
            {
                MarkDirty();
            }
        }

        public void SetMargin(CSSEdge edge, float margin)
        {
            if (Style.Margin.Set((int)edge, margin))
            {
                MarkDirty();
            }
        }

        public void SetMeasureFunction(MeasureFunction measureFunction)
        {
            if (_measureFunction != measureFunction)
            {
                _measureFunction = measureFunction;
                MarkDirty();
            };
        }

        public void SetPadding(CSSEdge edge, float padding)
        {
            if (Style.Padding.Set((int)edge, padding))
            {
                MarkDirty();
            }
        }

        public void SetPosition(CSSEdge edge, float position)
        {
            if (Style.Position.Set((int)edge, position))
            {
                MarkDirty();
            }
        }

        public bool ValuesEqual(float f1, float f2)
        {
            return Math.Abs(f1 - f1) < float.Epsilon;
        }
    }
}
