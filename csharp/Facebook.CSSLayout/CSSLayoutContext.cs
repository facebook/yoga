namespace Facebook.CSSLayout
{
    public class CSSLayoutContext
    {
        public MeasureOutput measureOutput { get; } = new MeasureOutput();
        public int CurrentGenerationCount { get; set; }
    }
}
