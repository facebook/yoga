/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

namespace Facebook.Yoga
{
    public static class YogaValueExtensions
    {
        public static YogaValue Percent(this float value)
        {
            return YogaValue.Percent(value);
        }

        public static YogaValue Pt(this float value)
        {
            return YogaValue.Point(value);
        }

        public static YogaValue Percent(this int value)
        {
            return YogaValue.Percent(value);
        }

        public static YogaValue Pt(this int value)
        {
            return YogaValue.Point(value);
        }
    }
}