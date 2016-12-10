using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using CoreGraphics;
using Facebook.Yoga;
using Foundation;
using UIKit;

namespace Facebook.YogaKit.iOS
{
	class YGNodeBridge : NSObject
	{
		bool disposed;
		internal WeakReference<UIView> viewRef;
		internal YogaNode node;
		public YGNodeBridge()
		{
			node = new YogaNode();
		}

		public void SetContext(UIView view)
		{
			viewRef = new WeakReference<UIView>(view);
			YogaKit.Bridges.Add(node, this);
		}

		protected override void Dispose(bool disposing)
		{
			if (disposing && !disposed)
			{
				disposed = true;
				YogaKit.Bridges.Remove(node);
				viewRef = null;
				node = null;
			}
			base.Dispose(disposing);
		}
	}

	public static class YogaKit
	{
		internal static Dictionary<YogaNode, YGNodeBridge> Bridges = new Dictionary<YogaNode, YGNodeBridge>();

		static NSString YogaNodeKey = new NSString(nameof(GetYogaNode));

		static NSString UsesYogaKey = new NSString(nameof(UsesYoga));

		static NSString IncludeYogaKey = new NSString(nameof(UsesYoga));

		public static void UsesYoga(this UIView view, bool usesYoga)
		{
			var value = NSNumber.FromBoolean(usesYoga);
			objc_setAssociatedObject(view.Handle, UsesYogaKey.Handle, value.Handle, AssociationPolicy.RETAIN_NONATOMIC);
		}

		public static bool GetUsesYoga(this UIView view)
		{
			var value = ObjCRuntime.Runtime.GetNSObject(objc_getAssociatedObject(view.Handle, UsesYogaKey.Handle)) as NSNumber;
			return value == null ? false : value.BoolValue;
		}

		public static void IncludeYogaLayout(this UIView view, bool includeInLayout)
		{
			var value = NSNumber.FromBoolean(includeInLayout);
			objc_setAssociatedObject(view.Handle, IncludeYogaKey.Handle, value.Handle, AssociationPolicy.RETAIN_NONATOMIC);
		}

		public static bool GetIncludeYogaLayout(this UIView view)
		{
			var value = ObjCRuntime.Runtime.GetNSObject(objc_getAssociatedObject(view.Handle, IncludeYogaKey.Handle)) as NSNumber;
			return value == null ? true : value.BoolValue;
		}

		public static void YogaWidth(this UIView view, nfloat width)
		{
			var node = GetYogaNode(view);
			node.Width = (float)width;
		}

		public static void YogaHeight(this UIView view, nfloat height)
		{
			var node = GetYogaNode(view);
			node.Height = (float)height;
		}

		public static void YogaMinWidth(this UIView view, float minWidth)
		{
			var node = GetYogaNode(view);
			node.MinWidth = minWidth;
		}

		public static void YogaMinHeight(this UIView view, float minHeight)
		{
			var node = GetYogaNode(view);
			node.MinHeight = minHeight;
		}

		public static void YogaMaxWidth(this UIView view, float maxWidth)
		{
			var node = GetYogaNode(view);
			node.MaxWidth = maxWidth;
		}

		public static void YogaMaxHeight(this UIView view, float maxHeight)
		{
			var node = GetYogaNode(view);
			node.MaxHeight = maxHeight;
		}

		public static void YogaAlignItems(this UIView view, Yoga.YogaAlign align)
		{
			var node = GetYogaNode(view);
			node.AlignItems = align;
		}

		public static void YogaJustify(this UIView view, Yoga.YogaJustify justify)
		{
			var node = GetYogaNode(view);
			node.JustifyContent = justify;
		}

		public static void YogaAlign(this UIView view, Yoga.YogaAlign align)
		{
			var node = GetYogaNode(view);
			node.AlignContent = align;
		}

		public static void YogaAlignSelf(this UIView view, Yoga.YogaAlign align)
		{
			var node = GetYogaNode(view);
			node.AlignSelf = align;
		}

		public static void YogaDirection(this UIView view, Yoga.YogaDirection direction)
		{
			var node = GetYogaNode(view);
			node.StyleDirection = direction;
		}

		public static void YogaFlexDirection(this UIView view, Yoga.YogaFlexDirection direction)
		{
			var node = GetYogaNode(view);
			node.FlexDirection = direction;
		}

		public static void YogaPositionType(this UIView view, Yoga.YogaPositionType position)
		{
			var node = GetYogaNode(view);
			node.PositionType = position;
		}

		public static void YogaFlexWrap(this UIView view, Yoga.YogaWrap wrap)
		{
			var node = GetYogaNode(view);
			node.Wrap = wrap;
		}

		public static void YogaFlexShrink(this UIView view, float shrink)
		{
			var node = GetYogaNode(view);
			node.FlexShrink = shrink;
		}

		public static void YogaFlexGrow(this UIView view, float grow)
		{
			var node = GetYogaNode(view);
			node.FlexGrow = grow;
		}

		public static void YogaFlexBasis(this UIView view, float basis)
		{
			var node = GetYogaNode(view);
			node.FlexBasis = basis;
		}

		public static void YogaPositionForEdge(this UIView view, float position, YogaEdge edge)
		{
			var node = GetYogaNode(view);
			node.SetPosition(edge, position);
		}

		public static void YogaMarginForEdge(this UIView view, float margin, YogaEdge edge)
		{
			var node = GetYogaNode(view);
			node.SetMargin(edge, margin);
		}

		public static void YogaPaddingForEdge(this UIView view, float padding, YogaEdge edge)
		{
			var node = GetYogaNode(view);
			node.SetPadding(edge, padding);
		}

		public static void YogaAspectRation(this UIView view, float ratio)
		{
			var node = GetYogaNode(view);
			node.StyleAspectRatio = ratio;
		}

		#region Layout and Sizing
		public static void YogaApplyLayout(this UIView view)
		{
			CalculateLayoutWithSize(view, view.Bounds.Size);
			ApplyLayoutToViewHierarchy(view);
		}

		public static CGSize YogaIntrinsicSize(this UIView view)
		{
			var constrainedSize = new CGSize
			{
				Width = float.NaN,
				Height = float.NaN
			};
			return CalculateLayoutWithSize(view, constrainedSize);
		}

		public static YogaDirection YogaResolvedDirection(this UIView view)
		{
			var node = GetYogaNode(view);
			return node.LayoutDirection;
		}

		#endregion

		static CGSize CalculateLayoutWithSize(UIView view, CGSize size)
		{
			if (!view.GetUsesYoga())
			{
				System.Diagnostics.Debug.WriteLine("Doesn't use Yoga");
			}
			AttachNodesFromViewHierachy(view);
			var node = GetYogaNode(view);

			node.Width = (float)size.Width;
			node.Height = (float)size.Height;
			node.CalculateLayout();

			return new CGSize { Width = node.LayoutWidth, Height = node.LayoutHeight };
		}

		static long MeasureView(YogaNode node, float width, YogaMeasureMode widthMode, float height, YogaMeasureMode heightMode)
		{
			var constrainedWidth = (widthMode == YogaMeasureMode.Undefined) ? nfloat.MaxValue : width;
			var constrainedHeight = (heightMode == YogaMeasureMode.Undefined) ? nfloat.MaxValue : height;

			UIView view = null;
			if (Bridges.ContainsKey(node))
				Bridges[node].viewRef.TryGetTarget(out view);

			var sizeThatFits = view.SizeThatFits(new CGSize(constrainedWidth, constrainedHeight));

			var finalWidth = SanitizeMeasurement(constrainedWidth, sizeThatFits.Width, widthMode);
			var finalHeight = SanitizeMeasurement(constrainedHeight, sizeThatFits.Height, heightMode);

			return MeasureOutput.Make(finalWidth, finalHeight);
		}

		static float SanitizeMeasurement(nfloat constrainedSize, nfloat measuredSize, YogaMeasureMode measureMode)
		{
			float result;
			if (measureMode == YogaMeasureMode.Exactly)
			{
				result = (float)constrainedSize;
			}
			else if (measureMode == YogaMeasureMode.AtMost)
			{
				result = (float)Math.Min(constrainedSize, measuredSize);
			}
			else {
				result = (float)measuredSize;
			}

			return result;

		}

		static void ApplyLayoutToViewHierarchy(UIView view)
		{
			if (!view.GetIncludeYogaLayout())
				return;

			var node = GetYogaNode(view);
			CGPoint topLeft = new CGPoint(node.LayoutX, node.LayoutY);
			CGPoint bottomRight = new CGPoint(topLeft.X + node.LayoutWidth, topLeft.Y + node.LayoutHeight);
			view.Frame = new CGRect(RoundPixelValue(topLeft.X), RoundPixelValue(topLeft.Y), RoundPixelValue(bottomRight.X) - RoundPixelValue(topLeft.X), RoundPixelValue(bottomRight.Y) - RoundPixelValue(topLeft.Y));
			bool isLeaf = !view.GetUsesYoga() || view.Subviews.Length == 0;
			if (!isLeaf)
			{
				for (int i = 0; i < view.Subviews.Length; i++)
				{
					ApplyLayoutToViewHierarchy(view.Subviews[i]);
				}
			}
		}

		static double RoundPixelValue(nfloat value)
		{
			nfloat scale = UIScreen.MainScreen.Scale;

			return Math.Round(value * scale) / scale;
		}

		static void AttachNodesFromViewHierachy(UIView view)
		{
			var node = GetYogaNode(view);

			// Only leaf nodes should have a measure function
			if (!view.GetUsesYoga() || view.Subviews.Length == 0)
			{
				node.SetMeasureFunction(MeasureView);
				RemoveAllChildren(node);
			}
			else
			{
				node.SetMeasureFunction(null);
				// Create a list of all the subviews that we are going to use for layout.
				var subviewsToInclude = new List<UIView>();
				foreach (var subview in view.Subviews)
				{
					if (subview.GetIncludeYogaLayout())
					{
						subviewsToInclude.Add(subview);
					}
				}

				var shouldReconstructChildList = false;
				if (node.Count != subviewsToInclude.Count)
				{
					shouldReconstructChildList = true;
				}
				else
				{
					for (int i = 0; i < subviewsToInclude.Count; i++)
					{
						if (node[i] != GetYogaNode(subviewsToInclude[i]))
						{
							shouldReconstructChildList = true;
							break;
						}
					}
				}

				if (shouldReconstructChildList)
				{
					RemoveAllChildren(node);

					for (int i = 0; i < subviewsToInclude.Count; i++)
					{
						var subView = subviewsToInclude[i];
						node.Insert(i, subView.GetYogaNode());
						AttachNodesFromViewHierachy(subView);
					}
				}
			}
		}

		static void RemoveAllChildren(YogaNode node)
		{
			if (node == null)
				return;

			while (node.Count > 0)
			{
				node.Clear();
			}
		}

		static YogaNode GetYogaNode(this UIView view)
		{
			var value = ObjCRuntime.Runtime.GetNSObject(objc_getAssociatedObject(view.Handle, YogaNodeKey.Handle)) as YGNodeBridge;
			if (value == null)
			{
				value = new YGNodeBridge();
				value.SetContext(view);
				objc_setAssociatedObject(view.Handle, YogaNodeKey.Handle, value.Handle, AssociationPolicy.RETAIN_NONATOMIC);
			}
			return value.node;
		}

		[DllImport("/usr/lib/libobjc.dylib")]
		static extern void objc_setAssociatedObject(IntPtr @object, IntPtr key, IntPtr value, AssociationPolicy policy);

		[DllImport("/usr/lib/libobjc.dylib")]
		static extern IntPtr objc_getAssociatedObject(IntPtr @object, IntPtr key);

		enum AssociationPolicy
		{
			ASSIGN = 0,
			RETAIN_NONATOMIC = 1,
			COPY_NONATOMIC = 3,
			RETAIN = 01401,
			COPY = 01403,
		}
	}
}
