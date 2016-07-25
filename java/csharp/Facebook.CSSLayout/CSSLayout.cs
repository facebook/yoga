/**
 * Copyright (c) 2014, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

namespace Facebook.CSSLayout
{

    /**
     * Where the output of {@link LayoutEngine#layoutNode(CSSNode, float)} will go in the CSSNode.
     */

    class CSSLayout
    {
        // This value was chosen based on empiracle data. Even the most complicated
        // layouts should not require more than 16 entries to fit within the cache.
        public const int MAX_CACHED_RESULT_COUNT = 16;

        public const int POSITION_LEFT = 0;
        public const int POSITION_TOP = 1;
        public const int POSITION_RIGHT = 2;
        public const int POSITION_BOTTOM = 3;

        public const int DIMENSION_WIDTH = 0;
        public const int DIMENSION_HEIGHT = 1;

        public float[] position = new float[4];
        public float[] dimensions = {
            CSSConstants.Undefined,
            CSSConstants.Undefined
        };
        public CSSDirection direction = CSSDirection.LTR;

        public float flexBasis;

        public int generationCount;
        public CSSDirection? lastParentDirection;

        public int nextCachedMeasurementsIndex;
        public CSSCachedMeasurement[] cachedMeasurements = new CSSCachedMeasurement[MAX_CACHED_RESULT_COUNT];
        public float[] measuredDimensions = {
            CSSConstants.Undefined,
            CSSConstants.Undefined
        };

        public CSSCachedMeasurement cachedLayout = new CSSCachedMeasurement();

        public void resetResult()
        {
            FillArray(position, 0);
            FillArray(dimensions, CSSConstants.Undefined);

            direction = CSSDirection.LTR;

            flexBasis = 0;

            generationCount = 0;
            lastParentDirection = null;

            nextCachedMeasurementsIndex = 0;
            measuredDimensions[DIMENSION_WIDTH] = CSSConstants.Undefined;
            measuredDimensions[DIMENSION_HEIGHT] = CSSConstants.Undefined;

            cachedLayout.widthMeasureMode = null;
            cachedLayout.heightMeasureMode = null;
        }

        public override string ToString()
        {
            return "layout: {" +
                    "left: " + position[POSITION_LEFT] + ", " +
                    "top: " + position[POSITION_TOP] + ", " +
                    "width: " + dimensions[DIMENSION_WIDTH] + ", " +
                    "height: " + dimensions[DIMENSION_HEIGHT] + ", " +
                    "direction: " + direction +
                    "}";
        }

        static void FillArray<T>(T[] array, T value)
        {
            for (var i = 0; i != array.Length; ++i)
                array[i] = value;
        }
    }
}
