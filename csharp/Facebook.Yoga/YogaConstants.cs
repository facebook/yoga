/*
 * Copyright (c) Facebook, Inc. and its affiliates.
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
