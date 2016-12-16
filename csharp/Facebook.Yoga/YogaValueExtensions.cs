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
    public static class YogaValueExtensions
    {
        public static YogaValue Percent(this float value)
        {
            return YogaValue.Percent(value);
        }

        public static YogaValue Px(this float value)
        {
            return YogaValue.Pixel(value);
        }

        public static YogaValue Percent(this int value)
        {
            return YogaValue.Percent(value);
        }

        public static YogaValue Px(this int value)
        {
            return YogaValue.Pixel(value);
        }
    }
}