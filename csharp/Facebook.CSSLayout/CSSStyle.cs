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
        public Spacing Position { get; } = new Spacing(CSSConstants.UNDEFINED);

        public float[] Dimensions { get; } = new float[2];

        public float MinWidth { get; set; } = CSSConstants.UNDEFINED;
        public float MinHeight { get; set; } = CSSConstants.UNDEFINED;

        public float MaxWidth { get; set; } = CSSConstants.UNDEFINED;
        public float MaxHeight { get; set; } = CSSConstants.UNDEFINED;

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
            FlexBasis = CSSConstants.UNDEFINED;

            Margin.Reset();
            Padding.Reset();
            Border.Reset();
            Position.Reset();

            for (var i = 0; i < 2; i++) { Dimensions[i] = CSSConstants.UNDEFINED; }

            MinWidth = CSSConstants.UNDEFINED;
            MinHeight = CSSConstants.UNDEFINED;

            MaxWidth = CSSConstants.UNDEFINED;
            MaxHeight = CSSConstants.UNDEFINED;
        }
    }
}
