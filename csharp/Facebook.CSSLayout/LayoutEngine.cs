namespace Facebook.CSSLayout
{
    public class LayoutEngine
    {
        private const int POSITION_TOP = CSSLayout.POSITION_TOP;
        private const int POSITION_BOTTOM = CSSLayout.POSITION_BOTTOM;
        private const int POSITION_LEFT = CSSLayout.POSITION_LEFT;
        private const int POSITION_RIGHT = CSSLayout.POSITION_RIGHT;
        private const int DIMENSION_WIDTH = CSSLayout.DIMENSION_WIDTH;
        private const int DIMENSION_HEIGHT = CSSLayout.DIMENSION_HEIGHT;

        private const int CSS_FLEX_DIRECTION_COLUMN = (int)CSSFlexDirection.Column;
        private const int CSS_FLEX_DIRECTION_COLUMN_REVERSE = (int)CSSFlexDirection.ColumnReverse;
        private const int CSS_FLEX_DIRECTION_ROW = (int)CSSFlexDirection.Row;
        private const int CSS_FLEX_DIRECTION_ROW_REVERSE = (int)CSSFlexDirection.RowReverse;

        private const int CSS_POSITION_RELATIVE = (int)CSSPositionType.Relative;
        private const int CSS_POSITION_ABSOLUTE = (int)CSSPositionType.Absolute;

        private static readonly int[] leading = new [] {
            POSITION_TOP,
            POSITION_BOTTOM,
            POSITION_LEFT,
            POSITION_RIGHT,
        };

        private static readonly int[] trailing = new [] {
            POSITION_BOTTOM,
            POSITION_TOP,
            POSITION_RIGHT,
            POSITION_LEFT,
        };

        private static readonly int[] pos = new [] {
            POSITION_TOP,
            POSITION_BOTTOM,
            POSITION_LEFT,
            POSITION_RIGHT,
        };

        private static readonly int[] dim = new [] {
            DIMENSION_HEIGHT,
            DIMENSION_HEIGHT,
            DIMENSION_WIDTH,
            DIMENSION_WIDTH,
        };

        private static readonly int[] leadingSpacing = new [] {
            Spacing.TOP,
            Spacing.BOTTOM,
            Spacing.START,
            Spacing.START
        };

        private static readonly int[] trailingSpacing = new [] {
            Spacing.BOTTOM,
            Spacing.TOP,
            Spacing.END,
            Spacing.END
        };

        private static bool IsFlexBasisAuto(CSSNodeNative node)
        {
            return CSSConstants.IsUndefined(node.style.flexBasis);
        }
    }
}
