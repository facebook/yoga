/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

using System.Runtime.InteropServices;

namespace Facebook.Yoga
{
    [StructLayout(LayoutKind.Sequential)]
    public struct YogaValue
    {
        private float Value;
        private YogaUnit Unit;
        private byte isDefined; /* use byte to keep struct blitable */

        public bool IsDefined => isDefined != 0;

        public static YogaValue Pixel(float value)
        {
            return new YogaValue
            {
                Value = value,
                isDefined = YogaConstants.IsUndefined(value) ? (byte)0 : (byte)1,
                Unit = YogaUnit.Pixel
            };
        }

        public bool Equals(YogaValue other)
        {
            return Value.Equals(other.Value) && Unit == other.Unit;
        }

        public override bool Equals(object obj)
        {
            if (ReferenceEquals(null, obj)) return false;
            return obj is YogaValue && Equals((YogaValue) obj);
        }

        public override int GetHashCode()
        {
            unchecked
            {
                return (Value.GetHashCode() * 397) ^ (int) Unit;
            }
        }

        public static YogaValue Undefined()
        {
            return new YogaValue
            {
                Value = YogaConstants.Undefined,
                isDefined = 0,
                Unit = YogaUnit.Pixel
            };
        }

        public static YogaValue Percent(float value)
        {
            return new YogaValue
            {
                Value = value,
                isDefined = YogaConstants.IsUndefined(value) ? (byte)0 : (byte)1,
                Unit = YogaUnit.Percent
            };
        }

        public static implicit operator YogaValue(float pixelValue)
        {
            return Pixel(pixelValue);
        }
    }
}
