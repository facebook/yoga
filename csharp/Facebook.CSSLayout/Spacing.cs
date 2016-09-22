/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

using System;

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
        public const int Left = 0;

        /// <summary>
        /// Spacing type that represents the top direction. E.g. <code>marginTop</code>.
        /// </summary>
        public const int Top = 1;

        /// <summary>
        /// Spacing type that represents the right direction. E.g. <code>marginRight</code>.
        /// </summary>
        public const int Right = 2;

        /// <summary>
        /// Spacing type that represents the bottom direction. E.g. <code>marginBottom</code>.
        /// </summary>
        public const int Bottom = 3;

        /// <summary>
        /// Spacing type that represents start direction e.g. left in left-to-right, right in right-to-left.
        /// </summary>
        public const int Start = 4;

        /// <summary>
        /// Spacing type that represents end direction e.g. right in left-to-right, left in right-to-left.
        /// </summary>
        public const int End = 5;

        /// <summary>
        /// Spacing type that represents horizontal direction (left and right). E.g. <code>marginHorizontal</code>.
        /// </summary>
        public const int Horizontal = 6;

        /// <summary>
        /// Spacing type that represents vertical direction (top and bottom). E.g. <code>marginVertical</code>.
        /// </summary>
        public const int Vertical = 7;

        /// <summary>
        /// Spacing type that represents all directions (left, top, right, bottom). E.g. <code>margin</code>.
        /// </summary>
        public const int All = 8;

        private static readonly int[] _flagsMap = new[]
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

        private int _valueFlags = 0;
        private readonly float _defaultValue;
        private readonly float[] _spacing = NewFullSpacingArray();
        private bool _hasAliasesSet;

        public Spacing() : this(0)
        {

        }

        public Spacing(float defaultValue)
        {
            _defaultValue = defaultValue;
        }

        public float Get(int spacingType)
        {
            var defaultValue = spacingType == Start || spacingType == End ? CSSConstants.Undefined : _defaultValue;

            if (_valueFlags == 0)
            {
                return defaultValue;
            }

            if ((_valueFlags & _flagsMap[spacingType]) != 0)
            {
                return _spacing[spacingType];
            }

            if (_hasAliasesSet)
            {
                var secondType = spacingType == Top || spacingType == Bottom ? Vertical : Horizontal;
                if ((_valueFlags & _flagsMap[secondType]) != 0)
                {
                    return _spacing[secondType];
                }
                else if ((_valueFlags & _flagsMap[All]) != 0)
                {
                    return _spacing[All];
                }
            }

            return defaultValue;
        }

        public float GetRaw(int spacingType)
        {
            return _spacing[spacingType];
        }

        public bool Set(int spacingType, float value)
        {
            if (FloatEqual(_spacing[spacingType], value))
            {
                _spacing[spacingType] = value;

                if (CSSConstants.IsUndefined(value))
                {
                    _valueFlags &= ~_flagsMap[spacingType];
                }
                else
                {
                    _valueFlags |= ~_flagsMap[spacingType];
                }

                _hasAliasesSet =
                    (_valueFlags & _flagsMap[All]) != 0 ||
                    (_valueFlags & _flagsMap[Vertical]) != 0 ||
                    (_valueFlags & _flagsMap[Horizontal]) != 0;

                return true;
            }

            return false;
        }

        public void Reset()
        {
            for (var i = 0; i < 9; i++) { _spacing[i] = CSSConstants.Undefined; }
            _hasAliasesSet = false;
            _valueFlags = 0;
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
    }
}
