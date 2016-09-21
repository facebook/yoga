namespace Facebook.CSSLayout
{
    public class CSSStyle
    {
        public CSSDirection Direction { get; set; }
        public CSSFlexDirection FlexDirection { get; set; }
        public CSSJustify JustifyContent { get; set; }
        public CSSAlign AlignContent { get; set; }
        public CSSAlign AlignItems { get; set; }
        public CSSAlign AlignSelf { get; set; }
        public CSSPositionType PositionType { get; set; }
        public CSSWrap FlexWrap { get; set; }
        public CSSOverflow Overflow { get; set; }
        public float FlexGrow { get; set; }
        public float FlexShrink { get; set; }
        public float FlexBasis { get; set; }

        public Spacing Margin { get; } = new Spacing();
        public Spacing Padding { get; } = new Spacing();
        public Spacing Border { get; } = new Spacing();
        public Spacing Position { get; } = new Spacing(CSSConstants.Undefined);

        public float[] Dimensions { get; } = new float[2];

        public float MinWidth { get; set; } = CSSConstants.Undefined;
        public float MinHeight { get; set; } = CSSConstants.Undefined;

        public float MaxWidth { get; set; } = CSSConstants.Undefined;
        public float MaxHeight { get; set; } = CSSConstants.Undefined;

        public CSSStyle()
        {
            Reset();
        }

        public void Reset()
        {
            Direction = CSSDirection.Inherit;
            FlexDirection = CSSFlexDirection.Column;
            JustifyContent = CSSJustify.FlexStart;
            AlignContent = CSSAlign.FlexStart;
            AlignItems = CSSAlign.Stretch;
            AlignSelf = CSSAlign.Auto;
            PositionType = CSSPositionType.Relative;
            FlexWrap = CSSWrap.NoWrap;
            Overflow = CSSOverflow.Visible;
            FlexGrow = 0;
            FlexShrink = 0;
            FlexBasis = CSSConstants.Undefined;

            Margin.Reset();
            Padding.Reset();
            Border.Reset();
            Position.Reset();

            for (var i = 0; i < 2; i++) { Dimensions[i] = CSSConstants.Undefined; }

            MinWidth = CSSConstants.Undefined;
            MinHeight = CSSConstants.Undefined;

            MaxWidth = CSSConstants.Undefined;
            MaxHeight = CSSConstants.Undefined;
        }
    }
}
