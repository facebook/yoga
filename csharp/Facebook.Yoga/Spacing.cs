/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

namespace Facebook.Yoga
{
    [System.Obsolete]
    public class Spacing
    {
        public YogaValue? Top;
        public YogaValue? Bottom;
        public YogaValue? Left;
        public YogaValue? Right;

        public Spacing(
            YogaValue? top = null,
            YogaValue? bottom = null,
            YogaValue? left = null,
            YogaValue? right = null)
        {
            Top = top;
            Bottom = bottom;
            Left = left;
            Right = right;
        }
    }
}
