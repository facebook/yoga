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
        public const int POSITION_LEFT = 0;
        public const int POSITION_TOP = 1;
        public const int POSITION_RIGHT = 2;
        public const int POSITION_BOTTOM = 3;

        public const int DIMENSION_WIDTH = 0;
        public const int DIMENSION_HEIGHT = 1;

        public float[] position = new float[4];
        public float[] dimensions = new float[2];
        public CSSDirection direction = CSSDirection.LTR;

        /**
        * This should always get called before calling {@link LayoutEngine#layoutNode(CSSNode, float)}
        */

        public void resetResult()
        {
            FillArray(position, 0);
            FillArray(dimensions, CSSConstants.Undefined);

            direction = CSSDirection.LTR;
        }

        public void copy(CSSLayout layout)
        {
            position[POSITION_LEFT] = layout.position[POSITION_LEFT];
            position[POSITION_TOP] = layout.position[POSITION_TOP];
            position[POSITION_RIGHT] = layout.position[POSITION_RIGHT];
            position[POSITION_BOTTOM] = layout.position[POSITION_BOTTOM];
            dimensions[DIMENSION_WIDTH] = layout.dimensions[DIMENSION_WIDTH];
            dimensions[DIMENSION_HEIGHT] = layout.dimensions[DIMENSION_HEIGHT];
            direction = layout.direction;
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
