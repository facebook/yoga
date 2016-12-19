using System;
using System.Collections.Generic;
using Facebook.Yoga;
#if __IOS__
using NativeView = UIKit.UIView;
#endif

namespace Facebook.YogaKit.iOS
{
	public static class YogaKit
	{
		internal static Dictionary<YogaNode, object> Bridges = new Dictionary<YogaNode, object>();

		public static void UsesYoga(this NativeView view, bool usesYoga)
		{
			YogaKitNative.UsesYoga(view, usesYoga);
		}

		public static bool GetUsesYoga(this NativeView view)
		{
			return YogaKitNative.GetUsesYoga(view);
		}

		public static void IncludeYogaLayout(this NativeView view, bool includeInLayout)
		{
			YogaKitNative.IncludeYogaLayout(view, includeInLayout);
		}

		public static bool GetIncludeYogaLayout(this NativeView view)
		{
			return YogaKitNative.GetIncludeYogaLayout(view);
		}

		public static void YogaWidth(this NativeView view, nfloat width)
		{
			var node = GetYogaNode(view);
			node.Width = (float)width;
		}

		public static void YogaHeight(this NativeView view, nfloat height)
		{
			var node = GetYogaNode(view);
			node.Height = (float)height;
		}

		public static void YogaMinWidth(this NativeView view, float minWidth)
		{
			var node = GetYogaNode(view);
			node.MinWidth = minWidth;
		}

		public static void YogaMinHeight(this NativeView view, float minHeight)
		{
			var node = GetYogaNode(view);
			node.MinHeight = minHeight;
		}

		public static void YogaMaxWidth(this NativeView view, float maxWidth)
		{
			var node = GetYogaNode(view);
			node.MaxWidth = maxWidth;
		}

		public static void YogaMaxHeight(this NativeView view, float maxHeight)
		{
			var node = GetYogaNode(view);
			node.MaxHeight = maxHeight;
		}

		public static void YogaAlignItems(this NativeView view, YogaAlign align)
		{
			var node = GetYogaNode(view);
			node.AlignItems = align;
		}

		public static void YogaJustify(this NativeView view, YogaJustify justify)
		{
			var node = GetYogaNode(view);
			node.JustifyContent = justify;
		}

		public static void YogaAlign(this NativeView view, YogaAlign align)
		{
			var node = GetYogaNode(view);
			node.AlignContent = align;
		}

		public static void YogaAlignSelf(this NativeView view, YogaAlign align)
		{
			var node = GetYogaNode(view);
			node.AlignSelf = align;
		}

		public static void YogaDirection(this NativeView view, YogaDirection direction)
		{
			var node = GetYogaNode(view);
			node.StyleDirection = direction;
		}

		public static void YogaFlexDirection(this NativeView view, YogaFlexDirection direction)
		{
			var node = GetYogaNode(view);
			node.FlexDirection = direction;
		}

		public static void YogaPositionType(this NativeView view, YogaPositionType position)
		{
			var node = GetYogaNode(view);
			node.PositionType = position;
		}

		public static void YogaFlexWrap(this NativeView view, YogaWrap wrap)
		{
			var node = GetYogaNode(view);
			node.Wrap = wrap;
		}

		public static void YogaFlexShrink(this NativeView view, float shrink)
		{
			var node = GetYogaNode(view);
			node.FlexShrink = shrink;
		}

		public static void YogaFlexGrow(this NativeView view, float grow)
		{
			var node = GetYogaNode(view);
			node.FlexGrow = grow;
		}

		public static void YogaFlexBasis(this NativeView view, float basis)
		{
			var node = GetYogaNode(view);
			node.FlexBasis = basis;
		}

		public static void YogaPositionForEdge(this NativeView view, float position, YogaEdge edge)
		{
			var node = GetYogaNode(view);
			node.SetPosition(edge, position);
		}

		public static void YogaMarginForEdge(this NativeView view, float margin, YogaEdge edge)
		{
			var node = GetYogaNode(view);
			node.SetMargin(edge, margin);
		}

		public static void YogaPaddingForEdge(this NativeView view, float padding, YogaEdge edge)
		{
			var node = GetYogaNode(view);
			node.SetPadding(edge, padding);
		}

		public static void YogaAspectRation(this NativeView view, float ratio)
		{
			var node = GetYogaNode(view);
			node.StyleAspectRatio = ratio;
		}

		#region Layout and Sizing
		public static void YogaApplyLayout(this NativeView view)
		{
			YogaKitNative.CalculateLayoutWithSize(view, view.Bounds.Size);
			YogaKitNative.ApplyLayoutToViewHierarchy(view);
		}

		public static YogaDirection YogaResolvedDirection(this NativeView view)
		{
			var node = GetYogaNode(view);
			return node.LayoutDirection;
		}

		#endregion

		public static YogaNode GetYogaNode(this NativeView view)
		{
			return YogaKitNative.GetYogaNode(view);
		}
	}
}
