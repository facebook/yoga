namespace Facebook.CSSLayout
{
    public static class CSSConstants
    {
        public static float UNDEFINED = float.NaN;

        public static bool IsUndefined(float value)
        {
            return float.IsNaN(value);
        }
    }
}
