using System.Runtime.InteropServices;

namespace Facebook.CSSLayout
{
    public class CSSLayout
    {
        public const int MAX_CACHED_RESULT = 16;

        public const int POSITION_LEFT = 0;
        public const int POSITION_TOP = 1;
        public const int POSITION_RIGHT = 2;
        public const int POSITION_BOTTOM = 3;

        public const int DIMENSION_WIDTH = 0;
        public const int DIMENSION_HEIGHT = 1;

        public float[] Position { get; } = new float[4];

        public float[] Dimensions { get; } = new float[2];

        public CSSDirection Direction { get; set; } = CSSDirection.LeftToRight;

        public float ComputedFlexBasis { get; set; }

        public int GenerationCount { get; set; }

        public CSSDirection? LastParentDirection { get; set; }

        public int NextCachedMeasurementIndex { get; set; }

        public CSSCachedMeasurement[] CachedMeasurements { get; } = new CSSCachedMeasurement[MAX_CACHED_RESULT];

        public float[] MeasureDimensions { get; } = new float[2];

        public CSSCachedMeasurement CachedLayout { get; } = new CSSCachedMeasurement();

        public CSSLayout()
        {
            ResetResult();
        }

        public void ResetResult()
        {
            var i = 0;
            for (i = 0; i < 4; i++) { Position[i] = CSSConstants.UNDEFINED; }
            for (i = 0; i < 2; i++) { Dimensions[i] = CSSConstants.UNDEFINED; }

            ComputedFlexBasis = 0;

            GenerationCount = 0;
            LastParentDirection = null;

            NextCachedMeasurementIndex = 0;
            MeasureDimensions[DIMENSION_WIDTH] = CSSConstants.UNDEFINED;
            MeasureDimensions[DIMENSION_HEIGHT] = CSSConstants.UNDEFINED;

            CachedLayout.WidthMeasureMode = null;
            CachedLayout.HeightMeasureMode = null;
        }

        public override string ToString()
        {
            return $"layout: {{ left: {Position[POSITION_LEFT]}, top: {Position[POSITION_TOP]}, width: {Dimensions[DIMENSION_WIDTH]}, height: {Dimensions[DIMENSION_HEIGHT]}, direction: {Direction} }}";
        }
    }
}
