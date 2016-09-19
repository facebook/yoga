using System;

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
                throw new NotImplementedException();
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
                throw new NotImplementedException();
            }
        }

        public object Data
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
                throw new NotImplementedException();
            }

            set
            {
                throw new NotImplementedException();
            }
        }

        public bool IsDirty
        {
            get
            {
                throw new NotImplementedException();
            }
        }

        public bool IsMeasureDefined
        {
            get
            {
                throw new NotImplementedException();
            }
        }

        public bool IsTextNode
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
                throw new NotImplementedException();
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

        public int IndexOf(ICSSNode node)
        {
            throw new NotImplementedException();
        }

        public void Initialize()
        {
            throw new NotImplementedException();
        }

        public void Insert(int index, ICSSNode node)
        {
            throw new NotImplementedException();
        }

        public void MarkDirty()
        {
            throw new NotImplementedException();
        }

        public void MarkLayoutSeen()
        {
            throw new NotImplementedException();
        }

        public void RemoveAt(int index)
        {
            throw new NotImplementedException();
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
            throw new NotImplementedException();
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
            throw new NotImplementedException();
        }
    }
}
