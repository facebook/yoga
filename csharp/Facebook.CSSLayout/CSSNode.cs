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
            DIRTY,

            /**
             * This node has a new layout relative to the last time {@link #markLayoutSeen()} was called.
             */
            HAS_NEW_LAYOUT,

            /**
             * {@link #layout} is valid for the node's properties and this layout has been marked as
             * having been seen.
             */
            UP_TO_DATE,
        }

        public CSSStyle Style { get; } = new CSSStyle();
        public CSSLayout Layout { get; } = new CSSLayout();
        public CachedCSSLayout LastLayout { get; } = new CachedCSSLayout();
        public int LineIndex { get; set; } = 0;
        public CSSNode NextChild { get; set; }

        private List<CSSNode> _children;
        private CSSNode _parent;
        private MeasureFunction _measureFunction = null;
        private LayoutState _layoutState = LayoutState.DIRTY;

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
                throw new NotImplementedException();
            }

            set
            {
                throw new NotImplementedException();
            }
        }

        public CSSAlign AlignItems
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

        public CSSAlign AlignSelf
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
                throw new NotImplementedException();
            }

            set
            {
                throw new NotImplementedException();
            }
        }

        public float FlexBasis
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

        public CSSFlexDirection FlexDirection
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

        public float FlexGrow
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

        public float FlexShrink
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

        public bool HasNewLayout
        {
            get
            {
                return _layoutState == LayoutState.HAS_NEW_LAYOUT;
            }
        }

        public void MarkHasNewLayout()
        {
            _layoutState = LayoutState.HAS_NEW_LAYOUT;
        }

        public bool IsDirty
        {
            get
            {
                return _layoutState == LayoutState.DIRTY;
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
                throw new NotImplementedException();
            }

            set
            {
                throw new NotImplementedException();
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
                throw new NotImplementedException();
            }

            set
            {
                throw new NotImplementedException();
            }
        }

        public CSSDirection StyleDirection
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

        public float StyleHeight
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

        public float StyleMaxHeight
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

        public float StyleMaxWidth
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

        public float StyleMinHeight
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

        public float StyleMinWidth
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

        public float StyleWidth
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

        public CSSWrapType Wrap
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

        public void CalculateLayout(CSSLayoutContext layoutContext)
        {
            throw new NotImplementedException();
        }

        public Spacing GetBorder()
        {
            throw new NotImplementedException();
        }

        public Spacing GetMargin()
        {
            throw new NotImplementedException();
        }

        public Spacing GetPadding()
        {
            throw new NotImplementedException();
        }

        public Spacing GetPosition()
        {
            throw new NotImplementedException();
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
            if (_layoutState == LayoutState.DIRTY)
            {
                return;
            }
            else if (_layoutState == LayoutState.HAS_NEW_LAYOUT)
            {
                throw new InvalidOperationException(@"Previous layout was ignored! MarkLayoutSeen() never called");
            }

            _layoutState = LayoutState.DIRTY;
            _parent?.MarkDirty();
        }

        public void MarkLayoutSeen()
        {
            if (!HasNewLayout)
            {
                throw new InvalidOperationException(@"Expected node to have a new layout to be seen!");
            }

            _layoutState = LayoutState.UP_TO_DATE;
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
            throw new NotImplementedException();
        }

        public void SetMargin(CSSEdge edge, float margin)
        {
            throw new NotImplementedException();
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
            throw new NotImplementedException();
        }

        public void SetPosition(CSSEdge edge, float position)
        {
            throw new NotImplementedException();
        }

        public bool ValuesEqual(float f1, float f2)
        {
            return Math.Abs(f1 - f1) < float.Epsilon;
        }
    }
}
