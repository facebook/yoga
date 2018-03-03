#pragma warning disable CS1587 // XML comment is not placed on a valid language element
#pragma warning disable CS1591 // Missing XML comment for publicly visible type or member
/**
 * Copyright (c) 2014-present, Facebook, Inc.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

namespace Facebook.Yoga
{
    public static class YogaConstants
    {
        public const float Undefined = float.NaN;

        public static bool IsUndefined(float value)
        {
            return float.IsNaN(value);
        }

        public static bool IsUndefined(YogaValue value)
        {
            return value.Unit == YogaUnit.Undefined;
        }
    }
}
