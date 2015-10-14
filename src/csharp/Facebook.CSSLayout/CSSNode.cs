/**
 * Copyright (c) 2014, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

using System;
using System.Collections.Generic;
using System.Text;

namespace Facebook.CSSLayout
{
    /**
     * Should measure the given node and put the result in the given MeasureOutput.
     */

    public delegate MeasureOutput MeasureFunction(CSSNode node, float width);

    /**
     * A CSS Node. It has a style object you can manipulate at {@link #style}. After calling
     * {@link #calculateLayout()}, {@link #layout} will be filled with the results of the layout.
     */

    public class CSSNode
    {
        const int POSITION_LEFT = CSSLayout.POSITION_LEFT;
        const int POSITION_TOP = CSSLayout.POSITION_TOP;
        const int POSITION_RIGHT = CSSLayout.POSITION_RIGHT;
        const int POSITION_BOTTOM = CSSLayout.POSITION_BOTTOM;
        const int DIMENSION_WIDTH = CSSLayout.DIMENSION_WIDTH;
        const int DIMENSION_HEIGHT = CSSLayout.DIMENSION_HEIGHT;

        enum LayoutState
        {
            /**
             * Some property of this node or its children has changes and the current values in
             * {@link #layout} are not valid.
             */
            DIRTY,

            /**
             * This node has a new layout relative to the last time {@link #MarkLayoutSeen()} was called.
             */
            HAS_NEW_LAYOUT,

            /**
             * {@link #layout} is valid for the node's properties and this layout has been marked as
             * having been seen.
             */
            UP_TO_DATE,
        }

        internal readonly CSSStyle style = new CSSStyle();
        internal readonly CSSLayout layout = new CSSLayout();
        internal readonly CachedCSSLayout lastLayout = new CachedCSSLayout();

        internal int lineIndex = 0;
        internal /*package*/ CSSNode nextAbsoluteChild;
        internal /*package*/ CSSNode nextFlexChild;

        // 4 is kinda arbitrary, but the default of 10 seems really high for an average View.
        readonly List<CSSNode> mChildren = new List<CSSNode>(4);
        [Nullable] CSSNode mParent;
        [Nullable] MeasureFunction mMeasureFunction = null;
        LayoutState mLayoutState = LayoutState.DIRTY;

        public int ChildCount
        {
            get { return mChildren.Count; }
        }

        public CSSNode this[int i]
        {
            get { return mChildren[i]; }
        }

        public IEnumerable<CSSNode> Children
        {
            get { return mChildren; }
        }

        public void AddChild(CSSNode child)
        {
            InsertChild(ChildCount, child);
        }

        public void InsertChild(int i, CSSNode child)
        {
            if (child.mParent != null)
            {
                throw new InvalidOperationException("Child already has a parent, it must be removed first.");
            }

            mChildren.Insert(i, child);
            child.mParent = this;
            dirty();
        }

        public void RemoveChildAt(int i)
        {
            mChildren[i].mParent = null;
            mChildren.RemoveAt(i);
            dirty();
        }

        public CSSNode Parent
        {
            [return: Nullable]
            get
            { return mParent; }
        }

        /**
         * @return the index of the given child, or -1 if the child doesn't exist in this node.
         */

        public int IndexOf(CSSNode child)
        {
            return mChildren.IndexOf(child);
        }

        public MeasureFunction MeasureFunction
        {
            get { return mMeasureFunction; }
            set
            {
                if (!valuesEqual(mMeasureFunction, value))
                {
                    mMeasureFunction = value;
                    dirty();
                }
            }
        }

        public bool IsMeasureDefined
        {
            get { return mMeasureFunction != null; }
        }

        internal MeasureOutput measure(MeasureOutput measureOutput, float width)
        {
            if (!IsMeasureDefined)
            {
                throw new Exception("Measure function isn't defined!");
            }
            return Assertions.assertNotNull(mMeasureFunction)(this, width);
        }

        /**
         * Performs the actual layout and saves the results in {@link #layout}
         */

        public void CalculateLayout()
        {
            layout.resetResult();
            LayoutEngine.layoutNode(DummyLayoutContext, this, CSSConstants.Undefined, null);
        }

        static readonly CSSLayoutContext DummyLayoutContext = new CSSLayoutContext();

        /**
         * See {@link LayoutState#DIRTY}.
         */

        public bool IsDirty
        {
            get { return mLayoutState == LayoutState.DIRTY; }
        }

        /**
         * See {@link LayoutState#HAS_NEW_LAYOUT}.
         */

        public bool HasNewLayout
        {
            get { return mLayoutState == LayoutState.HAS_NEW_LAYOUT; }
        }

        internal protected void dirty()
        {
            if (mLayoutState == LayoutState.DIRTY)
            {
                return;
            }
            else if (mLayoutState == LayoutState.HAS_NEW_LAYOUT)
            {
                throw new InvalidOperationException("Previous layout was ignored! MarkLayoutSeen() never called");
            }

            mLayoutState = LayoutState.DIRTY;

            if (mParent != null)
            {
                mParent.dirty();
            }
        }

        internal void markHasNewLayout()
        {
            mLayoutState = LayoutState.HAS_NEW_LAYOUT;
        }

        /**
         * Tells the node that the current values in {@link #layout} have been seen. Subsequent calls
         * to {@link #hasNewLayout()} will return false until this node is laid out with new parameters.
         * You must call this each time the layout is generated if the node has a new layout.
         */

        public void MarkLayoutSeen()
        {
            if (!HasNewLayout)
            {
                throw new InvalidOperationException("Expected node to have a new layout to be seen!");
            }

            mLayoutState = LayoutState.UP_TO_DATE;
        }

        void toStringWithIndentation(StringBuilder result, int level)
        {
            // Spaces and tabs are dropped by IntelliJ logcat integration, so rely on __ instead.
            StringBuilder indentation = new StringBuilder();
            for (int i = 0; i < level; ++i)
            {
                indentation.Append("__");
            }

            result.Append(indentation.ToString());
            result.Append(layout.ToString());

            if (ChildCount == 0)
            {
                return;
            }

            result.Append(", children: [\n");
            for (var i = 0; i < ChildCount; i++)
            {
                this[i].toStringWithIndentation(result, level + 1);
                result.Append("\n");
            }
            result.Append(indentation + "]");
        }

        public override string ToString()
        {
            StringBuilder sb = new StringBuilder();
            this.toStringWithIndentation(sb, 0);
            return sb.ToString();
        }

        protected bool valuesEqual(float f1, float f2)
        {
            return FloatUtil.floatsEqual(f1, f2);
        }

        protected bool valuesEqual<T>([Nullable] T o1, [Nullable] T o2)
        {
            if (o1 == null)
            {
                return o2 == null;
            }
            return o1.Equals(o2);
        }

        public CSSDirection Direction
        {
            get { return style.direction; }
            set { updateDiscreteValue(ref style.direction, value); }
        }

        public CSSFlexDirection FlexDirection
        {
            get { return style.flexDirection; }
            set { updateDiscreteValue(ref style.flexDirection, value); }
        }

        public CSSJustify JustifyContent
        {
            get { return style.justifyContent; }
            set { updateDiscreteValue(ref style.justifyContent, value); }
        }

        public CSSAlign AlignContent
        {
            get { return style.alignContent; }
            set { updateDiscreteValue(ref style.alignContent, value); }
        }

        public CSSAlign AlignItems
        {
            get { return style.alignItems; }
            set { updateDiscreteValue(ref style.alignItems, value); }
        }

        public CSSAlign AlignSelf
        {
            get { return style.alignSelf; }
            set { updateDiscreteValue(ref style.alignSelf, value); }
        }

        public CSSPositionType PositionType
        {
            get { return style.positionType; }
            set { updateDiscreteValue(ref style.positionType, value); }
        }

        public CSSWrap Wrap
        {
            get { return style.flexWrap; }
            set { updateDiscreteValue(ref style.flexWrap, value); }
        }

        public float Flex
        {
            get { return style.flex; }
            set { updateFloatValue(ref style.flex, value); }
        }

        public void SetMargin(CSSSpacingType spacingType, float margin)
        {
            if (style.margin.set((int)spacingType, margin))
                dirty();
        }

        public float GetMargin(CSSSpacingType spacingType)
        {
            return style.margin.getRaw((int)spacingType);
        }

        public void SetPadding(CSSSpacingType spacingType, float padding)
        {
            if (style.padding.set((int)spacingType, padding))
                dirty();
        }

        public float GetPadding(CSSSpacingType spacingType)
        {
            return style.padding.getRaw((int)spacingType);
        }

        public void SetBorder(CSSSpacingType spacingType, float border)
        {
            if (style.border.set((int)spacingType, border))
                dirty();
        }

        public float GetBorder(CSSSpacingType spacingType)
        {
            return style.border.getRaw((int)spacingType);
        }

        public float PositionTop
        {
            get { return style.position[POSITION_TOP]; }
            set { updateFloatValue(ref style.position[POSITION_TOP], value); }
        }

        public float PositionBottom
        {
            get { return style.position[POSITION_BOTTOM]; }
            set { updateFloatValue(ref style.position[POSITION_BOTTOM], value); }
        }

        public float PositionLeft
        {
            get { return style.position[POSITION_LEFT]; }
            set { updateFloatValue(ref style.position[POSITION_LEFT], value); }
        }

        public float PositionRight
        {
            get { return style.position[POSITION_RIGHT]; }
            set { updateFloatValue(ref style.position[POSITION_RIGHT], value); }
        }

        public float Width
        {
            get { return style.dimensions[DIMENSION_WIDTH]; }
            set { updateFloatValue(ref style.dimensions[DIMENSION_WIDTH], value); }
        }

        public float Height
        {
            get { return style.dimensions[DIMENSION_HEIGHT]; }
            set { updateFloatValue(ref style.dimensions[DIMENSION_HEIGHT], value); }
        }

        public float MinWidth
        {
            get { return style.minWidth; }
            set { updateFloatValue(ref style.minWidth, value); }
        }

        public float MinHeight
        {
            get { return style.minHeight; }
            set { updateFloatValue(ref style.minHeight, value); }
        }

        public float MaxWidth
        {
            get { return style.maxWidth; }
            set { updateFloatValue(ref style.maxWidth, value); }
        }

        public float MaxHeight
        {
            get { return style.maxHeight; }
            set { updateFloatValue(ref style.maxHeight, value); }
        }

        public float LayoutX
        {
            get { return layout.position[POSITION_LEFT]; }
        }

        public float LayoutY
        {
            get { return layout.position[POSITION_TOP]; }
        }

        public float LayoutWidth
        {
            get { return layout.dimensions[DIMENSION_WIDTH]; }
        }

        public float LayoutHeight
        {
            get { return layout.dimensions[DIMENSION_HEIGHT]; }
        }

        public CSSDirection LayoutDirection
        {
            get { return layout.direction; }
        }

        /**
         * Set a default padding (left/top/right/bottom) for this node.
         */
        public void SetDefaultPadding(CSSSpacingType spacingType, float padding)
        {
            if (style.padding.setDefault((int)spacingType, padding))
                dirty();
        }

        void updateDiscreteValue<ValueT>(ref ValueT valueRef, ValueT newValue)
        {
            if (valuesEqual(valueRef, newValue))
                return;

            valueRef = newValue;
            dirty();
        }

        void updateFloatValue(ref float valueRef, float newValue)
        {
            if (valuesEqual(valueRef, newValue))
                return;
            valueRef = newValue;
            dirty();
        }
    }

    public static class CSSNodeExtensions
    {
        /*
            Explicitly mark this node as dirty.
            
            Calling this function is required when the measure function points to the same instance,
            but changes its behavior.
            
            For all other property changes, the node is automatically marked dirty.
        */

        public static void MarkDirty(this CSSNode node)
        {
            node.dirty();
        }
    }

    internal static class CSSNodeExtensionsInternal
    {
        public static CSSNode getParent(this CSSNode node)
        {
            return node.Parent;
        }

        public static int getChildCount(this CSSNode node)
        {
            return node.ChildCount;
        }

        public static CSSNode getChildAt(this CSSNode node, int i)
        {
            return node[i];
        }

        public static void addChildAt(this CSSNode node, CSSNode child, int i)
        {
            node.InsertChild(i, child);
        }

        public static void removeChildAt(this CSSNode node, int i)
        {
            node.RemoveChildAt(i);
        }

        public static void setMeasureFunction(this CSSNode node, MeasureFunction measureFunction)
        {
            node.MeasureFunction = measureFunction;
        }

        public static void calculateLayout(this CSSNode node)
        {
            node.CalculateLayout();
        }

        public static bool isDirty(this CSSNode node)
        {
            return node.IsDirty;
        }

        public static void setMargin(this CSSNode node, int spacingType, float margin)
        {
            node.SetMargin((CSSSpacingType)spacingType, margin);
        }

        public static void setPadding(this CSSNode node, int spacingType, float padding)
        {
            node.SetPadding((CSSSpacingType)spacingType, padding);
        }

        public static void setBorder(this CSSNode node, int spacingType, float border)
        {
            node.SetBorder((CSSSpacingType)spacingType, border);
        }
    }
}
