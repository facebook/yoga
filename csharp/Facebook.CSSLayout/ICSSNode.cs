using System;

namespace Facebook.CSSLayout
{
    public delegate void MeasureFunction(ICSSNode node, float width, CSSMeasureMode widthMode, float height, CSSMeasureMode heightMode, MeasureOutput measureOutput);

    public interface ICSSNode
    {
        void Initialize();

        void Reset();

        bool IsDirty { get; }

        void MarkDirty();

        bool IsTextNode { get; set; }

        bool HasNewLayout { get; }

        void MarkLayoutSeen();

        bool ValuesEqual(float f1, float f2);

        ICSSNode this[int index] { get; }

        int Count { get; }

        void Insert(int index, ICSSNode node);

        int IndexOf(ICSSNode node);

        void RemoveAt(int index);

        ICSSNode Parent { get; }

        void SetMeasureFunction(MeasureFunction measureFunction);

        bool IsMeasureDefined { get; }

        void CalculateLayout(CSSLayoutContext layoutContext);

        CSSDirection StyleDirection { get; set; }

        CSSFlexDirection FlexDirection { get; set; }

        CSSJustify JustifyContent { get; set; }

        CSSAlign AlignItems { get; set; }

        CSSAlign AlignSelf { get; set; }

        CSSAlign AlignContent { get; set; }

        CSSPositionType PositionType { get; set; }

        CSSWrapType Wrap { get; set; }

        float Flex { get; set; }

        float FlexGrow { get; set; }

        float FlexShrink { get; set; }

        float FlexBasis { get; set; }

        Spacing GetMargin();

        void SetMargin(CSSEdge edge, float margin);

        Spacing GetPadding();

        void SetPadding(CSSEdge edge, float padding);

        Spacing GetBorder();

        void SetBorder(CSSEdge edge, float border);

        Spacing GetPosition();

        void SetPosition(CSSEdge edge, float position);

        float StyleWidth { get; set; }

        float StyleHeight { get; set; }

        float StyleMaxWidth { get; set; }

        float StyleMaxHeight { get; set; }

        float StyleMinWidth { get; set; }

        float StyleMinHeight { get; set; }

        float LayoutX { get; }

        float LayoutY { get; }

        float LayoutWidth { get; }

        float LayoutHeight { get; }

        CSSDirection LayoutDirection { get; }

        CSSOverflow Overflow { get; set; }

        object Data { get; set; }
    }
}
