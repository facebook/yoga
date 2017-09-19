using System;
using Facebook.Yoga;
using System.Collections.Generic;
using System.Drawing;
#if __IOS__
using NativeView = UIKit.UIView;
using NativeScrollView = UIKit.UIScrollView;
#endif

namespace Facebook.YogaKit
{
	public partial class YogaLayout : IYogaLayout
	{
		WeakReference<NativeView> _viewRef;
		YogaNode _node;

		internal YogaLayout(NativeView view)
		{
			_viewRef = new WeakReference<NativeView>(view);
			_node = new YogaNode();
			YogaKit.Bridges.Add(_node, view);

			IsEnabled = false;
			IsIncludeInLayout = true;
		}

		public new void MarkDirty()
		{
			if (IsLeaf)
				_node.MarkDirty();
		}

		public bool IsLeaf
		{
			get
			{
				if (IsEnabled)
				{
					NativeView view = null;
					if (_viewRef.TryGetTarget(out view))
					{
						foreach (NativeView subview in GetChildren(view))
						{
							var layout = subview.Yoga();
							if (layout.IsEnabled && layout.IsIncludeInLayout)
							{
								return false;
							}
						}
					}

				}
				return true;
			}
		}



		public bool IsEnabled
		{
			get;
			set;
		}

		public bool IsIncludeInLayout
		{
			get;
			set;
		}

		public int NumberOfChildren => _node.Count;

		public YogaDirection ResolvedDirection => _node.LayoutDirection;

		public YogaFlexDirection FlexDirection
		{
			get
			{
				return _node.FlexDirection;
			}

			set
			{
				_node.FlexDirection = value;
			}
		}

		public YogaAlign AlignItems
		{
			get
			{
				return _node.AlignItems;
			}

			set
			{
				_node.AlignItems = value;
			}
		}

		public YogaJustify JustifyContent
		{
			get
			{
				return _node.JustifyContent;
			}

			set
			{
				_node.JustifyContent = value;
			}
		}

		public YogaAlign AlignContent
		{
			get
			{
				return _node.AlignContent;
			}

			set
			{
				_node.AlignContent = value;
			}
		}

		public YogaAlign AlignSelf
		{
			get
			{
				return _node.AlignSelf;
			}

			set
			{
				_node.AlignSelf = value;
			}
		}

		public YogaPositionType Position
		{
			get
			{
				return _node.PositionType;
			}

			set
			{
				_node.PositionType = value;
			}
		}

		public YogaWrap FlexWrap
		{
			get
			{
				return _node.Wrap;
			}

			set
			{
				_node.Wrap = value;
			}
		}

		public YogaOverflow Overflow
		{
			get
			{
				return _node.Overflow;
			}

			set
			{
				_node.Overflow = value;
			}
		}

		public float FlexGrow
		{
			get
			{
				return _node.FlexGrow;
			}

			set
			{
				_node.FlexGrow = value;
			}
		}

		public float FlexShrink
		{
			get
			{
				return _node.FlexShrink;
			}

			set
			{
				_node.FlexShrink = value;
			}
		}

		public float FlexBasis
		{
			get
			{
				return (float)_node.FlexBasis.Value;
			}

			set
			{
				_node.FlexBasis = value;
			}
		}

		public float Left
		{
			get
			{
				return _node.Left.Value;
			}

			set
			{
				_node.Left = value;
			}
		}

		public float Top
		{
			get
			{
				return _node.Top.Value;
			}

			set
			{
				_node.Top = value;
			}
		}

		public float Right
		{
			get
			{
				return _node.Right.Value;
			}

			set
			{
				_node.Right = value;
			}
		}

		public float Bottom
		{
			get
			{
				return _node.Bottom.Value;
			}

			set
			{
				_node.Bottom = value;
			}
		}

		public float Start
		{
			get
			{
				return _node.Start.Value;
			}

			set
			{
				_node.Start = value;
			}
		}

		public float End
		{
			get
			{
				return _node.End.Value;
			}

			set
			{
				_node.End = value;
			}
		}

		public float MarginLeft
		{
			get
			{
				return _node.MarginLeft.Value;
			}

			set
			{
				_node.MarginLeft = value;
			}
		}

		public float MarginTop
		{
			get
			{
				return _node.MarginTop.Value;
			}

			set
			{
				_node.MarginTop = value;
			}
		}

		public float MarginRight
		{
			get
			{
				return _node.MarginRight.Value;
			}

			set
			{
				_node.MarginRight = value;
			}
		}

		public float MarginBottom
		{
			get
			{
				return _node.MarginBottom.Value;
			}

			set
			{
				_node.MarginBottom = value;
			}
		}

		public float MarginStart
		{
			get
			{
				return _node.MarginStart.Value;
			}

			set
			{
				_node.MarginStart = value;
			}
		}

		public float MarginEnd
		{
			get
			{
				return _node.MarginEnd.Value;
			}

			set
			{
				_node.MarginEnd = value;
			}
		}

		public float MarginHorizontal
		{
			get
			{
				return _node.MarginHorizontal.Value;
			}

			set
			{
				_node.MarginHorizontal = value;
			}
		}

		public float MarginVertical
		{
			get
			{
				return _node.MarginVertical.Value;
			}

			set
			{
				_node.MarginVertical = value;
			}
		}

		public float Margin
		{
			get
			{
				return _node.Margin.Value;
			}

			set
			{
				_node.Margin = value;
			}
		}

		public float PaddingLeft
		{
			get
			{
				return _node.PaddingLeft.Value;
			}

			set
			{
				_node.PaddingLeft = value;
			}
		}

		public float PaddingTop
		{
			get
			{
				return _node.PaddingTop.Value;
			}

			set
			{
				_node.PaddingTop = value;
			}
		}

		public float PaddingRight
		{
			get
			{
				return _node.PaddingRight.Value;
			}

			set
			{
				_node.PaddingRight = value;
			}
		}

		public float PaddingBottom
		{
			get
			{
				return _node.PaddingBottom.Value;
			}

			set
			{
				_node.PaddingBottom = value;
			}
		}

		public float PaddingStart
		{
			get
			{
				return _node.PaddingStart.Value;
			}

			set
			{
				_node.PaddingStart = value;
			}
		}

		public float PaddingEnd
		{
			get
			{
				return _node.PaddingEnd.Value;
			}

			set
			{
				_node.PaddingEnd = value;
			}
		}

		public float PaddingHorizontal
		{
			get
			{
				return _node.PaddingHorizontal.Value;
			}

			set
			{
				_node.PaddingHorizontal = value;
			}
		}

		public float PaddingVertical
		{
			get
			{
				return _node.PaddingVertical.Value;
			}

			set
			{
				_node.PaddingHorizontal = value;
			}
		}

		public float Padding
		{
			get
			{
				return _node.Padding.Value;
			}

			set
			{
				_node.Padding = value;
			}
		}

		public float BorderLeftWidth
		{
			get
			{
				return _node.BorderLeftWidth;
			}

			set
			{
				_node.BorderLeftWidth = value;
			}
		}

		public float BorderTopWidth
		{
			get
			{
				return _node.BorderTopWidth;
			}

			set
			{
				_node.BorderTopWidth = value;
			}
		}

		public float BorderRightWidth
		{
			get
			{
				return _node.BorderRightWidth;
			}

			set
			{
				_node.BorderRightWidth = value;
			}
		}

		public float BorderBottomWidth
		{
			get
			{
				return _node.BorderBottomWidth;
			}

			set
			{
				_node.BorderBottomWidth = value;
			}
		}

		public float BorderStartWidth
		{
			get
			{
				return _node.BorderStartWidth;
			}

			set
			{
				_node.BorderStartWidth = value;
			}
		}

		public float BorderEndWidth
		{
			get
			{
				return _node.BorderEndWidth;
			}

			set
			{
				_node.BorderEndWidth = value;
			}
		}

		public float BorderWidth
		{
			get
			{
				return _node.BorderWidth;
			}

			set
			{
				_node.BorderWidth = value;
			}
		}

		public float Height
		{
			get
			{
				return _node.Height.Value;
			}

			set
			{
				_node.Height = value;
			}
		}

		public float Width
		{
			get
			{
				return _node.Width.Value;
			}

			set
			{
				_node.Width = value;
			}
		}

		public float MinWidth
		{
			get
			{
				return _node.MinWidth.Value;
			}

			set
			{
				_node.MinWidth = value;
			}
		}

		public float MinHeight
		{
			get
			{
				return _node.MinHeight.Value;
			}

			set
			{
				_node.MinHeight = value;
			}
		}

		public float MaxWidth
		{
			get
			{
				return _node.MaxWidth.Value;
			}

			set
			{
				_node.MaxWidth = value;
			}
		}

		public float MaxHeight
		{
			get
			{
				return _node.MaxHeight.Value;
			}

			set
			{
				_node.MaxHeight = value;
			}
		}

		public float AspectRatio
		{
			get
			{
				return _node.AspectRatio;
			}

			set
			{
				_node.AspectRatio = value;
			}
		}

		public void ApplyLayout()
		{
			NativeView view = null;
			if (_viewRef.TryGetTarget(out view))
			{
				float width = 0;
				float height = 0;
				GetWidthHeightOfNativeView(view, out width, out height);
                if (view is NativeScrollView)
                {
                    if (FlexDirection == YogaFlexDirection.Column || FlexDirection == YogaFlexDirection.ColumnReverse)
                    {
                        height = float.NaN;
                    }
                    else
                    {
                        width = float.NaN;
                    }
                }
				CalculateLayoutWithSize(this, width, height);
				ApplyLayoutToViewHierarchy(view);
			}
		}
		public SizeF IntrinsicSize
		{
			get
			{
				return CalculateLayoutWithSize(this, float.NaN, float.NaN);
			}
		}

		SizeF CalculateLayoutWithSize(YogaLayout layout, float width, float height)
		{
			//TODO : Check thread access 
			if (!layout.IsEnabled)
			{
				System.Diagnostics.Debug.WriteLine("Doesn't use Yoga");
			}
			NativeView view = null;
			if (_viewRef.TryGetTarget(out view))
			{
				AttachNodesFromViewHierachy(view);
			}

			var node = layout._node;

			node.CalculateLayout(width, height);

			return new SizeF { Width = node.LayoutWidth, Height = node.LayoutHeight };
		}

		static YogaSize MeasureView(YogaNode node, float width, YogaMeasureMode widthMode, float height, YogaMeasureMode heightMode)
		{
			var constrainedWidth = (widthMode == YogaMeasureMode.Undefined) ? float.MaxValue : width;
			var constrainedHeight = (heightMode == YogaMeasureMode.Undefined) ? float.MaxValue : height;

			NativeView view = null;
			if (YogaKit.Bridges.ContainsKey(node))
				view = YogaKit.Bridges[node] as NativeView;

			float sizeThatFitsWidth = 0;
			float sizeThatFitsHeight = 0;

			MeasureNativeView(view, constrainedWidth, constrainedHeight, out sizeThatFitsWidth, out sizeThatFitsHeight);

			var finalWidth = SanitizeMeasurement(constrainedWidth, sizeThatFitsWidth, widthMode);
			var finalHeight = SanitizeMeasurement(constrainedHeight, sizeThatFitsHeight, heightMode);

			return MeasureOutput.Make(finalWidth, finalHeight);
		}

		static float SanitizeMeasurement(float constrainedSize, float measuredSize, YogaMeasureMode measureMode)
		{
			float result;
			if (measureMode == YogaMeasureMode.Exactly)
			{
				result = constrainedSize;
			}
			else if (measureMode == YogaMeasureMode.AtMost)
			{
				result = Math.Min(constrainedSize, measuredSize);
			}
			else {
				result = measuredSize;
			}

			return result;
		}

		static bool NodeHasExactSameChildren(YogaNode node, NativeView[] subviews)
		{
			if (node.Count != subviews.Length)
				return false;
			for (int i = 0; i < subviews.Length; i++)
			{
				YogaLayout yoga = subviews[i].Yoga() as YogaLayout;
				if (node[i] != yoga._node)
				{
					return false;
				}
			}
			return true;
		}

		static void AttachNodesFromViewHierachy(NativeView view)
		{
			YogaLayout yoga = view.Yoga() as YogaLayout;
			var node = yoga._node;
			// Only leaf nodes should have a measure function
			if (yoga.IsLeaf)
			{
				RemoveAllChildren(node);
				node.SetMeasureFunction(MeasureView);
			}
			else
			{
				node.SetMeasureFunction(null);
				// Create a list of all the subviews that we are going to use for layout.
				var subviewsToInclude = new List<NativeView>();
				foreach (var subview in view.Subviews)
				{
					if (subview.Yoga().IsEnabled && subview.Yoga().IsIncludeInLayout)
					{
						subviewsToInclude.Add(subview);
					}
				}

				if (!NodeHasExactSameChildren(node, subviewsToInclude.ToArray()))
				{
					RemoveAllChildren(node);
					for (int i = 0; i < subviewsToInclude.Count; i++)
					{
						YogaLayout yogaSubview = subviewsToInclude[i].Yoga() as YogaLayout;
						node.Insert(i, yogaSubview._node);
					}
				}

				foreach (var subView in subviewsToInclude)
				{
					AttachNodesFromViewHierachy(subView);
				}
			}
		}

		static void RemoveAllChildren(YogaNode node)
		{
			if (node == null)
				return;

			if (node.Count > 0)
			{
				node.Clear();
			}
		}

		static double RoundPointValue(float value)
		{
			float scale = NativePixelScale;

			return Math.Round(value * scale) / scale;
		}

		static void ApplyLayoutToViewHierarchy(NativeView view)
		{
			//TODO : "Framesetting should only be done on the main thread."
			YogaLayout yoga = view.Yoga() as YogaLayout;

			if (!yoga.IsIncludeInLayout)
				return;

			var node = yoga._node;

			ApplyLayoutToNativeView(view, node);

			if (!yoga.IsLeaf)
			{
				for (int i = 0; i < view.Subviews.Length; i++)
				{
					ApplyLayoutToViewHierarchy(view.Subviews[i]);
				}
			}
		}


	}
}

