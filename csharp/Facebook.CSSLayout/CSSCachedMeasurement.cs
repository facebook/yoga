namespace Facebook.CSSLayout
{
    public class CSSCachedMeasurement
    {
        public float AvailableWidth { get; set; }
        public float AvailableHeight { get; set; }
        public CSSMeasureMode? WidthMeasureMode { get; set; }
        public CSSMeasureMode? HeightMeasureMode { get; set; }
        public float ComputedWidth { get; set; }
        public float ComputedHeight { get; set; }
    }
}
