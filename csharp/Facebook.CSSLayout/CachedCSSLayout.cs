namespace Facebook.CSSLayout
{
    public class CachedCSSLayout : CSSLayout
    {
        public float RequestedWidth { get; set; } = CSSConstants.UNDEFINED;
        public float RequestedHeight { get; set; } = CSSConstants.UNDEFINED;
        public float ParentMaxWidth { get; set; } = CSSConstants.UNDEFINED;
        public float ParentMaxHeight { get; set; } = CSSConstants.UNDEFINED;
    }
}
