/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

using System;

namespace Facebook.Yoga
{
    public partial class YogaNode
    {
        [Obsolete("use Object Initializer")]
        public static YogaNode Create(
            YogaDirection? styleDirection = null,
            YogaFlexDirection? flexDirection = null,
            YogaJustify? justifyContent = null,
            YogaAlign? alignContent = null,
            YogaAlign? alignItems = null,
            YogaAlign? alignSelf = null,
            YogaPositionType? positionType = null,
            YogaWrap? wrap = null,
            YogaOverflow? overflow = null,
            float? flex = null,
            float? flexGrow = null,
            float? flexShrink = null,
            YogaValue? flexBasis = null,
            Spacing position = null,
            Spacing margin = null,
            Spacing padding = null,
            Border border = null,
            YogaValue? width = null,
            YogaValue? height = null,
            YogaValue? maxWidth = null,
            YogaValue? maxHeight = null,
            YogaValue? minWidth = null,
            YogaValue? minHeight = null)
        {
            YogaNode node = new YogaNode();

            if (styleDirection.HasValue)
            {
                node.StyleDirection = styleDirection.Value;
            }

            if (flexDirection.HasValue)
            {
                node.FlexDirection = flexDirection.Value;
            }

            if (justifyContent.HasValue)
            {
                node.JustifyContent = justifyContent.Value;
            }

            if (alignContent.HasValue)
            {
                node.AlignContent = alignContent.Value;
            }

            if (alignItems.HasValue)
            {
                node.AlignItems = alignItems.Value;
            }

            if (alignSelf.HasValue)
            {
                node.AlignSelf = alignSelf.Value;
            }

            if (positionType.HasValue)
            {
                node.PositionType = positionType.Value;
            }

            if (wrap.HasValue)
            {
                node.Wrap = wrap.Value;
            }

            if (overflow.HasValue)
            {
                node.Overflow = overflow.Value;
            }

            if (flex.HasValue)
            {
                node.Flex = flex.Value;
            }

            if (flexGrow.HasValue)
            {
                node.FlexGrow = flexGrow.Value;
            }

            if (flexShrink.HasValue)
            {
                node.FlexShrink = flexShrink.Value;
            }

            if (flexBasis.HasValue)
            {
                node.FlexBasis = flexBasis.Value;
            }

            if (position != null)
            {
                if (position.Top.HasValue)
                {
                    node.Top = position.Top.Value;
                }

                if (position.Bottom.HasValue)
                {
                    node.Bottom = position.Bottom.Value;
                }

                if (position.Left.HasValue)
                {
                    node.Left = position.Left.Value;
                }

                if (position.Right.HasValue)
                {
                    node.Right = position.Right.Value;
                }
            }

            if (margin != null)
            {
                if (margin.Top.HasValue)
                {
                    node.MarginTop = margin.Top.Value;
                }

                if (margin.Bottom.HasValue)
                {
                    node.MarginBottom = margin.Bottom.Value;
                }

                if (margin.Left.HasValue)
                {
                    node.MarginLeft = margin.Left.Value;
                }

                if (margin.Right.HasValue)
                {
                    node.MarginRight = margin.Right.Value;
                }
            }

            if (padding != null)
            {
                if (padding.Top.HasValue)
                {
                    node.PaddingTop = padding.Top.Value;
                }

                if (padding.Bottom.HasValue)
                {
                    node.PaddingBottom = padding.Bottom.Value;
                }

                if (padding.Left.HasValue)
                {
                    node.PaddingLeft = padding.Left.Value;
                }

                if (padding.Right.HasValue)
                {
                    node.PaddingRight = padding.Right.Value;
                }
            }

            if (border != null)
            {
                if (border.Top.HasValue)
                {
                    node.BorderTopWidth = border.Top.Value;
                }

                if (border.Bottom.HasValue)
                {
                    node.BorderBottomWidth = border.Bottom.Value;
                }

                if (border.Left.HasValue)
                {
                    node.BorderLeftWidth = border.Left.Value;
                }

                if (border.Right.HasValue)
                {
                    node.BorderRightWidth = border.Right.Value;
                }
            }

            if (width.HasValue)
            {
                node.Width = width.Value;
            }

            if (height.HasValue)
            {
                node.Height = height.Value;
            }

            if (minWidth.HasValue)
            {
                node.MinWidth = minWidth.Value;
            }

            if (minHeight.HasValue)
            {
                node.MinHeight = minHeight.Value;
            }

            if (maxWidth.HasValue)
            {
                node.MaxWidth = maxWidth.Value;
            }

            if (maxHeight.HasValue)
            {
                node.MaxHeight = maxHeight.Value;
            }

            return node;
        }
    }
}
