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
     * Class representing CSS spacing (padding, margin, and borders). This is mostly necessary to
     * properly implement interactions and updates for properties like margin, marginLeft, and
     * marginHorizontal.
     */

    sealed class Spacing
    {
        /**
         * Spacing type that represents the left direction. E.g. {@code marginLeft}.
         */
        internal const int LEFT = (int)CSSSpacingType.Left;
        /**
         * Spacing type that represents the top direction. E.g. {@code marginTop}.
         */
        internal const int TOP = (int)CSSSpacingType.Top;
        /**
         * Spacing type that represents the right direction. E.g. {@code marginRight}.
         */
        internal const int RIGHT = (int)CSSSpacingType.Right;
        /**
         * Spacing type that represents the bottom direction. E.g. {@code marginBottom}.
         */
        internal const int BOTTOM = (int)CSSSpacingType.Bottom;
        /**
         * Spacing type that represents vertical direction (top and bottom). E.g. {@code marginVertical}.
         */
        internal const int VERTICAL = (int)CSSSpacingType.Vertical;
        /**
         * Spacing type that represents horizontal direction (left and right). E.g.
         * {@code marginHorizontal}.
        */
        internal const int HORIZONTAL = (int)CSSSpacingType.Horizontal;
        /**
         * Spacing type that represents start direction e.g. left in left-to-right, right in right-to-left.
         */
        internal const int START = (int)CSSSpacingType.Start;
        /**
         * Spacing type that represents end direction e.g. right in left-to-right, left in right-to-left.
         */
        internal const int END = (int)CSSSpacingType.End;
        /**
         * Spacing type that represents all directions (left, top, right, bottom). E.g. {@code margin}.
         */
        internal const int ALL = (int)CSSSpacingType.All;

        static readonly int[] sFlagsMap = {
            1, /*LEFT*/
            2, /*TOP*/
            4, /*RIGHT*/
            8, /*BOTTOM*/
            16, /*VERTICAL*/
            32, /*HORIZONTAL*/
            64, /*START*/
            128, /*END*/
            256 /*ALL*/
        };

        float[] mSpacing = newFullSpacingArray();
        [Nullable] float[] mDefaultSpacing = null;
        int mValueFlags = 0;
        bool mHasAliasesSet;

        /**
         * Set a spacing value.
         *
         * @param spacingType one of {@link #LEFT}, {@link #TOP}, {@link #RIGHT}, {@link #BOTTOM},
         *        {@link #VERTICAL}, {@link #HORIZONTAL}, {@link #ALL}
         * @param value the value for this direction
         * @return {@code true} if the spacing has changed, or {@code false} if the same value was already
         *         set
         */

        internal bool set(int spacingType, float value)
        {
            if (!FloatUtil.floatsEqual(mSpacing[spacingType], value))
            {
                mSpacing[spacingType] = value;

                if (CSSConstants.IsUndefined(value))
                {
                    mValueFlags &= ~sFlagsMap[spacingType];
                }
                else
                {
                    mValueFlags |= sFlagsMap[spacingType];
                }

                mHasAliasesSet =
                    (mValueFlags & sFlagsMap[ALL]) != 0 ||
                    (mValueFlags & sFlagsMap[VERTICAL]) != 0 ||
                    (mValueFlags & sFlagsMap[HORIZONTAL]) != 0;

                return true;
            }
            return false;
        }

        /**
         * Set a default spacing value. This is used as a fallback when no spacing has been set for a
         * particular direction.
         *
         * @param spacingType one of {@link #LEFT}, {@link #TOP}, {@link #RIGHT}, {@link #BOTTOM}
         * @param value the default value for this direction
         * @return
         */

        internal bool setDefault(int spacingType, float value)
        {
            if (mDefaultSpacing == null)
                mDefaultSpacing = newSpacingResultArray();

            if (!FloatUtil.floatsEqual(mDefaultSpacing[spacingType], value))
            {
                mDefaultSpacing[spacingType] = value;
                return true;
            }
            return false;
        }

        /**
         * Get the spacing for a direction. This takes into account any default values that have been set.
         *
         * @param spacingType one of {@link #LEFT}, {@link #TOP}, {@link #RIGHT}, {@link #BOTTOM}
         */

        internal float get(int spacingType)
        {
            float defaultValue = 
                (mDefaultSpacing != null)
                ? mDefaultSpacing[spacingType]
                : (spacingType == START || spacingType == END ? CSSConstants.Undefined : 0);

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
                int secondType = spacingType == TOP || spacingType == BOTTOM ? VERTICAL : HORIZONTAL;
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

        /**
         * Get the raw value (that was set using {@link #set(int, float)}), without taking into account
         * any default values.
         *
         * @param spacingType one of {@link #LEFT}, {@link #TOP}, {@link #RIGHT}, {@link #BOTTOM},
         *        {@link #VERTICAL}, {@link #HORIZONTAL}, {@link #ALL}
         */

        internal float getRaw(int spacingType)
        {
            return mSpacing[spacingType];
        }

        /**
         * Try to get start value and fallback to given type if not defined. This is used privately
         * by the layout engine as a more efficient way to fetch direction-aware values by
         * avoid extra method invocations.
         */
        internal float getWithFallback(int spacingType, int fallbackType)
        {
            return
                (mValueFlags & sFlagsMap[spacingType]) != 0
                ? mSpacing[spacingType]
                : get(fallbackType);
        }

        static float[] newFullSpacingArray()
        {
            return new[]
            {
                CSSConstants.Undefined,
                CSSConstants.Undefined,
                CSSConstants.Undefined,
                CSSConstants.Undefined,
                CSSConstants.Undefined,
                CSSConstants.Undefined,
                CSSConstants.Undefined,
                CSSConstants.Undefined,
                CSSConstants.Undefined
            };
        }

        static float[] newSpacingResultArray()
        {
            return newSpacingResultArray(0);
        }

        static float[] newSpacingResultArray(float defaultValue)
        {
            return new[]
            {
                defaultValue,
                defaultValue,
                defaultValue,
                defaultValue,
                defaultValue,
                defaultValue,
                CSSConstants.Undefined,
                CSSConstants.Undefined,
                defaultValue
            };
        }
    }
}
