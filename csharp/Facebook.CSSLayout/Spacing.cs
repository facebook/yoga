using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Facebook.CSSLayout
{
    /// <summary>
    /// Class representing CSS spacing (padding, margin, and borders). This is mostly necessary to 
    /// properly implement interactions and updates for properties like margin, marginLeft, and 
    /// marginHorizontal.
    /// </summary>
    public class Spacing
    {
        /// <summary>
        /// Spacing type that represents the left direction. E.g. <code>marginLeft</code>.
        /// </summary>
        public const int LEFT = 0;

        /// <summary>
        /// Spacing type that represents the top direction. E.g. <code>marginTop</code>.
        /// </summary>
        public const int TOP = 1;

        /// <summary>
        /// Spacing type that represents the right direction. E.g. <code>marginRight</code>.
        /// </summary>
        public const int RIGHT = 2;

        /// <summary>
        /// Spacing type that represents the bottom direction. E.g. <code>marginBottom</code>.
        /// </summary>
        public const int BOTTOM = 3;

        /// <summary>
        /// Spacing type that represents start direction e.g. left in left-to-right, right in right-to-left.
        /// </summary>
        public const int START = 4;

        /// <summary>
        /// Spacing type that represents end direction e.g. right in left-to-right, left in right-to-left.
        /// </summary>
        public const int END = 5;

        /// <summary>
        /// Spacing type that represents horizontal direction (left and right). E.g. <code>marginHorizontal</code>.
        /// </summary>
        public const int HORIZONTAL = 6;

        /// <summary>
        /// Spacing type that represents vertical direction (top and bottom). E.g. <code>marginVertical</code>.
        /// </summary>
        public const int VERTICAL = 7;

        /// <summary>
        /// Spacing type that represents all directions (left, top, right, bottom). E.g. <code>margin</code>.
        /// </summary>
        public const int ALL = 8;

        private static readonly int[] sFlagsMap = new[]
        {
            1, /*LEFT*/
            2, /*TOP*/
            4, /*RIGHT*/
            8, /*BOTTOM*/
            16, /*START*/
            32, /*END*/
            64, /*HORIZONTAL*/
            128, /*VERTICAL*/
            256, /*ALL*/
        };

        private int mValueFlags = 0;
        private readonly float mDefaultValue;
        private readonly float[] mSpacing = NewFullSpacingArray();
        private bool mHasAliasesSet;

        public Spacing() : this(0)
        {

        }

        public Spacing(float defaultValue)
        {
            mDefaultValue = defaultValue;
        }

        public float Get(int spacingType)
        {
            var defaultValue = spacingType == START || spacingType == END ? CSSConstants.UNDEFINED : mDefaultValue;

            if (mValueFlags == 0)
            {
                return defaultValue;
            }

            if ((mValueFlags & sFlagsMap[spacingType]) != 0)
            {
                return mSpacing[spacingType];
            }

            if (mHasAliasesSet)
            {
                var secondType = spacingType == TOP || spacingType == BOTTOM ? VERTICAL : HORIZONTAL;
                if ((mValueFlags & sFlagsMap[secondType]) != 0)
                {
                    return mSpacing[secondType];
                }
                else if ((mValueFlags & sFlagsMap[ALL]) != 0)
                {
                    return mSpacing[ALL];
                }
            }

            return defaultValue;
        }

        public float GetRaw(int spacingType)
        {
            return mSpacing[spacingType];
        }

        public bool Set(int spacingType, float value)
        {
            if (FloatEqual(mSpacing[spacingType], value))
            {
                mSpacing[spacingType] = value;

                if (CSSConstants.IsUndefined(value))
                {
                    mValueFlags &= ~sFlagsMap[spacingType];
                }
                else
                {
                    mValueFlags |= ~sFlagsMap[spacingType];
                }

                mHasAliasesSet =
                    (mValueFlags & sFlagsMap[ALL]) != 0 ||
                    (mValueFlags & sFlagsMap[VERTICAL]) != 0 ||
                    (mValueFlags & sFlagsMap[HORIZONTAL]) != 0;

                return true;
            }

            return false;
        }

        public void Reset()
        {
            for (var i = 0; i < 9; i++) { mSpacing[i] = CSSConstants.UNDEFINED; }
            mHasAliasesSet = false;
            mValueFlags = 0;
        }

        private static bool FloatEqual(float f1, float f2)
        {
            if (float.IsNaN(f1) || float.IsNaN(f2))
            {
                return float.IsNaN(f1) && float.IsNaN(f2);
            }

            return Math.Abs(f2 - f1) < float.Epsilon;
        }

        private static float[] NewFullSpacingArray()
        {
            return new float[]
            {
                CSSConstants.UNDEFINED,
                CSSConstants.UNDEFINED,
                CSSConstants.UNDEFINED,
                CSSConstants.UNDEFINED,
                CSSConstants.UNDEFINED,
                CSSConstants.UNDEFINED,
                CSSConstants.UNDEFINED,
                CSSConstants.UNDEFINED,
                CSSConstants.UNDEFINED
            };
        }
    }
}
