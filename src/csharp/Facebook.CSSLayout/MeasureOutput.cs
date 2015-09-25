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
     * POJO to hold the output of the measure function.
     */
    public struct MeasureOutput
    {
        public MeasureOutput(float width, float height)
        {
            Width = width;
            Height = height;
        }

        public readonly float Width;
        public readonly float Height;

        internal float width
        {
            get { return Width; }
        }

        internal float height
        {
            get { return Height; }
        }
    }
}