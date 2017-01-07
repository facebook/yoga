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
        public YogaValue Left
        {
            get
            {
                return Native.YGNodeStyleGetPosition(_ygNode, YogaEdge.Left);
            }

            set
            {
                YogaEdge edge = YogaEdge.Left;
                if (value.Unit == YogaUnit.Percent)
                {
                    Native.YGNodeStyleSetPositionPercent(_ygNode, edge, value.Value);
                }
                else
                {
                    Native.YGNodeStyleSetPosition(_ygNode, edge, value.Value);
                }
            }
        }

        public YogaValue Top
        {
            get
            {
                return Native.YGNodeStyleGetPosition(_ygNode, YogaEdge.Top);
            }

            set
            {
                YogaEdge edge = YogaEdge.Top;
                if (value.Unit == YogaUnit.Percent)
                {
                    Native.YGNodeStyleSetPositionPercent(_ygNode, edge, value.Value);
                }
                else
                {
                    Native.YGNodeStyleSetPosition(_ygNode, edge, value.Value);
                }
            }
        }

        public YogaValue Right
        {
            get
            {
                return Native.YGNodeStyleGetPosition(_ygNode, YogaEdge.Right);
            }

            set
            {
                YogaEdge edge = YogaEdge.Right;
                if (value.Unit == YogaUnit.Percent)
                {
                    Native.YGNodeStyleSetPositionPercent(_ygNode, edge, value.Value);
                }
                else
                {
                    Native.YGNodeStyleSetPosition(_ygNode, edge, value.Value);
                }
            }
        }

        public YogaValue Bottom
        {
            get
            {
                return Native.YGNodeStyleGetPosition(_ygNode, YogaEdge.Bottom);
            }

            set
            {
                YogaEdge edge = YogaEdge.Bottom;
                if (value.Unit == YogaUnit.Percent)
                {
                    Native.YGNodeStyleSetPositionPercent(_ygNode, edge, value.Value);
                }
                else
                {
                    Native.YGNodeStyleSetPosition(_ygNode, edge, value.Value);
                }
            }
        }

        public YogaValue Start
        {
            get
            {
                return Native.YGNodeStyleGetPosition(_ygNode, YogaEdge.Start);
            }

            set
            {
                YogaEdge edge = YogaEdge.Start;
                if (value.Unit == YogaUnit.Percent)
                {
                    Native.YGNodeStyleSetPositionPercent(_ygNode, edge, value.Value);
                }
                else
                {
                    Native.YGNodeStyleSetPosition(_ygNode, edge, value.Value);
                }
            }
        }

        public YogaValue End
        {
            get
            {
                return Native.YGNodeStyleGetPosition(_ygNode, YogaEdge.End);
            }

            set
            {
                YogaEdge edge = YogaEdge.End;
                if (value.Unit == YogaUnit.Percent)
                {
                    Native.YGNodeStyleSetPositionPercent(_ygNode, edge, value.Value);
                }
                else
                {
                    Native.YGNodeStyleSetPosition(_ygNode, edge, value.Value);
                }
            }
        }

        public YogaValue MarginLeft
        {
            get
            {
                return Native.YGNodeStyleGetMargin(_ygNode, YogaEdge.Left);
            }

            set
            {
                YogaEdge edge = YogaEdge.Left;
                if (value.Unit == YogaUnit.Percent)
                {
                    Native.YGNodeStyleSetMarginPercent(_ygNode, edge, value.Value);
                }
                else
                {
                    Native.YGNodeStyleSetMargin(_ygNode, edge, value.Value);
                }
            }
        }

        public YogaValue MarginTop
        {
            get
            {
                return Native.YGNodeStyleGetMargin(_ygNode, YogaEdge.Top);
            }

            set
            {
                YogaEdge edge = YogaEdge.Top;
                if (value.Unit == YogaUnit.Percent)
                {
                    Native.YGNodeStyleSetMarginPercent(_ygNode, edge, value.Value);
                }
                else
                {
                    Native.YGNodeStyleSetMargin(_ygNode, edge, value.Value);
                }
            }
        }

        public YogaValue MarginRight
        {
            get
            {
                return Native.YGNodeStyleGetMargin(_ygNode, YogaEdge.Right);
            }

            set
            {
                YogaEdge edge = YogaEdge.Right;
                if (value.Unit == YogaUnit.Percent)
                {
                    Native.YGNodeStyleSetMarginPercent(_ygNode, edge, value.Value);
                }
                else
                {
                    Native.YGNodeStyleSetMargin(_ygNode, edge, value.Value);
                }
            }
        }

        public YogaValue MarginBottom
        {
            get
            {
                return Native.YGNodeStyleGetMargin(_ygNode, YogaEdge.Bottom);
            }

            set
            {
                YogaEdge edge = YogaEdge.Bottom;
                if (value.Unit == YogaUnit.Percent)
                {
                    Native.YGNodeStyleSetMarginPercent(_ygNode, edge, value.Value);
                }
                else
                {
                    Native.YGNodeStyleSetMargin(_ygNode, edge, value.Value);
                }
            }
        }

        public YogaValue MarginStart
        {
            get
            {
                return Native.YGNodeStyleGetMargin(_ygNode, YogaEdge.Start);
            }

            set
            {
                YogaEdge edge = YogaEdge.Start;
                if (value.Unit == YogaUnit.Percent)
                {
                    Native.YGNodeStyleSetMarginPercent(_ygNode, edge, value.Value);
                }
                else
                {
                    Native.YGNodeStyleSetMargin(_ygNode, edge, value.Value);
                }
            }
        }

        public YogaValue MarginEnd
        {
            get
            {
                return Native.YGNodeStyleGetMargin(_ygNode, YogaEdge.End);
            }

            set
            {
                YogaEdge edge = YogaEdge.End;
                if (value.Unit == YogaUnit.Percent)
                {
                    Native.YGNodeStyleSetMarginPercent(_ygNode, edge, value.Value);
                }
                else
                {
                    Native.YGNodeStyleSetMargin(_ygNode, edge, value.Value);
                }
            }
        }

        public YogaValue MarginHorizontal
        {
            get
            {
                return Native.YGNodeStyleGetMargin(_ygNode, YogaEdge.Horizontal);
            }

            set
            {
                YogaEdge edge = YogaEdge.Horizontal;
                if (value.Unit == YogaUnit.Percent)
                {
                    Native.YGNodeStyleSetMarginPercent(_ygNode, edge, value.Value);
                }
                else
                {
                    Native.YGNodeStyleSetMargin(_ygNode, edge, value.Value);
                }
            }
        }

        public YogaValue MarginVertical
        {
            get
            {
                return Native.YGNodeStyleGetMargin(_ygNode, YogaEdge.Vertical);
            }

            set
            {
                YogaEdge edge = YogaEdge.Vertical;
                if (value.Unit == YogaUnit.Percent)
                {
                    Native.YGNodeStyleSetMarginPercent(_ygNode, edge, value.Value);
                }
                else
                {
                    Native.YGNodeStyleSetMargin(_ygNode, edge, value.Value);
                }
            }
        }

        public YogaValue Margin
        {
            get
            {
                return Native.YGNodeStyleGetMargin(_ygNode, YogaEdge.All);
            }

            set
            {
                YogaEdge edge = YogaEdge.All;
                if (value.Unit == YogaUnit.Percent)
                {
                    Native.YGNodeStyleSetMarginPercent(_ygNode, edge, value.Value);
                }
                else
                {
                    Native.YGNodeStyleSetMargin(_ygNode, edge, value.Value);
                }
            }
        }

        public YogaValue PaddingLeft
        {
            get
            {
                return Native.YGNodeStyleGetPadding(_ygNode, YogaEdge.Left);
            }

            set
            {
                YogaEdge edge = YogaEdge.Left;
                if (value.Unit == YogaUnit.Percent)
                {
                    Native.YGNodeStyleSetPaddingPercent(_ygNode, edge, value.Value);
                }
                else
                {
                    Native.YGNodeStyleSetPadding(_ygNode, edge, value.Value);
                }
            }
        }

        public YogaValue PaddingTop
        {
            get
            {
                return Native.YGNodeStyleGetPadding(_ygNode, YogaEdge.Top);
            }

            set
            {
                YogaEdge edge = YogaEdge.Top;
                if (value.Unit == YogaUnit.Percent)
                {
                    Native.YGNodeStyleSetPaddingPercent(_ygNode, edge, value.Value);
                }
                else
                {
                    Native.YGNodeStyleSetPadding(_ygNode, edge, value.Value);
                }
            }
        }

        public YogaValue PaddingRight
        {
            get
            {
                return Native.YGNodeStyleGetPadding(_ygNode, YogaEdge.Right);
            }

            set
            {
                YogaEdge edge = YogaEdge.Right;
                if (value.Unit == YogaUnit.Percent)
                {
                    Native.YGNodeStyleSetPaddingPercent(_ygNode, edge, value.Value);
                }
                else
                {
                    Native.YGNodeStyleSetPadding(_ygNode, edge, value.Value);
                }
            }
        }

        public YogaValue PaddingBottom
        {
            get
            {
                return Native.YGNodeStyleGetPadding(_ygNode, YogaEdge.Bottom);
            }

            set
            {
                YogaEdge edge = YogaEdge.Bottom;
                if (value.Unit == YogaUnit.Percent)
                {
                    Native.YGNodeStyleSetPaddingPercent(_ygNode, edge, value.Value);
                }
                else
                {
                    Native.YGNodeStyleSetPadding(_ygNode, edge, value.Value);
                }
            }
        }

        public YogaValue PaddingStart
        {
            get
            {
                return Native.YGNodeStyleGetPadding(_ygNode, YogaEdge.Start);
            }

            set
            {
                YogaEdge edge = YogaEdge.Start;
                if (value.Unit == YogaUnit.Percent)
                {
                    Native.YGNodeStyleSetPaddingPercent(_ygNode, edge, value.Value);
                }
                else
                {
                    Native.YGNodeStyleSetPadding(_ygNode, edge, value.Value);
                }
            }
        }

        public YogaValue PaddingEnd
        {
            get
            {
                return Native.YGNodeStyleGetPadding(_ygNode, YogaEdge.End);
            }

            set
            {
                YogaEdge edge = YogaEdge.End;
                if (value.Unit == YogaUnit.Percent)
                {
                    Native.YGNodeStyleSetPaddingPercent(_ygNode, edge, value.Value);
                }
                else
                {
                    Native.YGNodeStyleSetPadding(_ygNode, edge, value.Value);
                }
            }
        }

        public YogaValue PaddingHorizontal
        {
            get
            {
                return Native.YGNodeStyleGetPadding(_ygNode, YogaEdge.Horizontal);
            }

            set
            {
                YogaEdge edge = YogaEdge.Horizontal;
                if (value.Unit == YogaUnit.Percent)
                {
                    Native.YGNodeStyleSetPaddingPercent(_ygNode, edge, value.Value);
                }
                else
                {
                    Native.YGNodeStyleSetPadding(_ygNode, edge, value.Value);
                }
            }
        }

        public YogaValue PaddingVertical
        {
            get
            {
                return Native.YGNodeStyleGetPadding(_ygNode, YogaEdge.Vertical);
            }

            set
            {
                YogaEdge edge = YogaEdge.Vertical;
                if (value.Unit == YogaUnit.Percent)
                {
                    Native.YGNodeStyleSetPaddingPercent(_ygNode, edge, value.Value);
                }
                else
                {
                    Native.YGNodeStyleSetPadding(_ygNode, edge, value.Value);
                }
            }
        }

        public YogaValue Padding
        {
            get
            {
                return Native.YGNodeStyleGetPadding(_ygNode, YogaEdge.All);
            }

            set
            {
                YogaEdge edge = YogaEdge.All;
                if (value.Unit == YogaUnit.Percent)
                {
                    Native.YGNodeStyleSetPaddingPercent(_ygNode, edge, value.Value);
                }
                else
                {
                    Native.YGNodeStyleSetPadding(_ygNode, edge, value.Value);
                }
            }
        }

        public float BorderLeftWidth
        {
            get
            {
                return Native.YGNodeStyleGetBorder(_ygNode, YogaEdge.Left);
            }

            set
            {
                Native.YGNodeStyleSetBorder(_ygNode, YogaEdge.Left, value);
            }
        }

        public float BorderTopWidth
        {
            get
            {
                return Native.YGNodeStyleGetBorder(_ygNode, YogaEdge.Top);
            }

            set
            {
                Native.YGNodeStyleSetBorder(_ygNode, YogaEdge.Top, value);
            }
        }

        public float BorderRightWidth
        {
            get
            {
                return Native.YGNodeStyleGetBorder(_ygNode, YogaEdge.Right);
            }

            set
            {
                Native.YGNodeStyleSetBorder(_ygNode, YogaEdge.Right, value);
            }
        }

        public float BorderBottomWidth
        {
            get
            {
                return Native.YGNodeStyleGetBorder(_ygNode, YogaEdge.Bottom);
            }

            set
            {
                Native.YGNodeStyleSetBorder(_ygNode, YogaEdge.Bottom, value);
            }
        }

        public float BorderStartWidth
        {
            get
            {
                return Native.YGNodeStyleGetBorder(_ygNode, YogaEdge.Start);
            }

            set
            {
                Native.YGNodeStyleSetBorder(_ygNode, YogaEdge.Start, value);
            }
        }

        public float BorderEndWidth
        {
            get
            {
                return Native.YGNodeStyleGetBorder(_ygNode, YogaEdge.End);
            }

            set
            {
                Native.YGNodeStyleSetBorder(_ygNode, YogaEdge.End, value);
            }
        }

        public float BorderWidth
        {
            get
            {
                return Native.YGNodeStyleGetBorder(_ygNode, YogaEdge.All);
            }

            set
            {
                Native.YGNodeStyleSetBorder(_ygNode, YogaEdge.All, value);
            }
        }

        public float LayoutPaddingLeft
        {
            get
            {
                return Native.YGNodeLayoutGetPadding(_ygNode, YogaEdge.Left);
            }
        }

        public float LayoutPaddingTop
        {
            get
            {
                return Native.YGNodeLayoutGetPadding(_ygNode, YogaEdge.Top);
            }
        }

        public float LayoutPaddingRight
        {
            get
            {
                return Native.YGNodeLayoutGetPadding(_ygNode, YogaEdge.Right);
            }
        }

        public float LayoutPaddingBottom
        {
            get
            {
                return Native.YGNodeLayoutGetPadding(_ygNode, YogaEdge.Bottom);
            }
        }

        public float LayoutPaddingStart
        {
            get
            {
                return Native.YGNodeLayoutGetPadding(_ygNode, YogaEdge.Start);
            }
        }

        public float LayoutPaddingEnd
        {
            get
            {
                return Native.YGNodeLayoutGetPadding(_ygNode, YogaEdge.End);
            }
        }

        public float LayoutPaddingHorizontal
        {
            get
            {
                return Native.YGNodeLayoutGetPadding(_ygNode, YogaEdge.Horizontal);
            }
        }

        public float LayoutPaddingVertical
        {
            get
            {
                return Native.YGNodeLayoutGetPadding(_ygNode, YogaEdge.Vertical);
            }
        }

        public float LayoutPadding
        {
            get
            {
                return Native.YGNodeLayoutGetPadding(_ygNode, YogaEdge.All);
            }
        }
    }
}
