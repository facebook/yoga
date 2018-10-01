/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

namespace Facebook.Yoga
{
    public static class YogaConstants
    {
        /**
         * Large positive number signifies that the property(float) is undefined. Earlier we used to have
         * YGundefined as NAN, but the downside of this is that we can't use -ffast-math compiler flag as
         * it assumes all floating-point calculation involve and result into finite numbers. For more
         * information regarding -ffast-math compiler flag in clang, have a look at
         * https://clang.llvm.org/docs/UsersManual.html#cmdoption-ffast-math
         */
        public const float Undefined = 10E20F;

        public static bool IsUndefined(float value)
        {
            // Value of a float in the case of it being not defined is 10.1E20. Earlier it used to be NAN,
            // the benefit of which
            // was that if NAN is involved in any mathematical expression the result was NAN. But since we
            // want to have `-ffast-math`
            // flag being used by compiler which assumes that the floating point values are not NAN and Inf,
            // we represent YGUndefined as 10.1E20.
            // But now if YGUndefined is involved in any mathematical operations this value(10.1E20) would
            // change.
            // So the following check makes sure that if the value is outside a range (-10E8, 10E8) then it
            // is undefined.
            return value >= 10E8F || value <= -10E8;
        }

        public static bool IsUndefined(YogaValue value)
        {
            return value.Unit == YogaUnit.Undefined;
        }
    }
}
