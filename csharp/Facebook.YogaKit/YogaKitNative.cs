using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using Facebook.Yoga;
#if __IOS__
using CoreGraphics;
using Foundation;
using UIKit;
#endif

namespace Facebook.YogaKit
{
	internal static class YogaKitNative
	{
		static NSString YogaNodeKey = new NSString("YogaNode");

		static NSString UsesYogaKey = new NSString("UsesYoga");

		static NSString IncludeYogaKey = new NSString("UsesYoga");

		public static void UsesYoga(UIView view, bool usesYoga)
		{
			var value = NSNumber.FromBoolean(usesYoga);
			objc_setAssociatedObject(view.Handle, UsesYogaKey.Handle, value.Handle, AssociationPolicy.RETAIN_NONATOMIC);
		}

		public static bool GetUsesYoga(UIView view)
		{
			var value = ObjCRuntime.Runtime.GetNSObject(objc_getAssociatedObject(view.Handle, UsesYogaKey.Handle)) as NSNumber;
			return value == null ? false : value.BoolValue;
		}

		public static void IncludeYogaLayout(UIView view, bool includeInLayout)
		{
			var value = NSNumber.FromBoolean(includeInLayout);
			objc_setAssociatedObject(view.Handle, IncludeYogaKey.Handle, value.Handle, AssociationPolicy.RETAIN_NONATOMIC);
		}

		public static bool GetIncludeYogaLayout(UIView view)
		{
			var value = ObjCRuntime.Runtime.GetNSObject(objc_getAssociatedObject(view.Handle, IncludeYogaKey.Handle)) as NSNumber;
			return value == null ? true : value.BoolValue;
		}

		public static YogaNode GetYogaNode(UIView view)
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

		public static CGSize CalculateLayoutWithSize(UIView view, CGSize size)
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

		public static void ApplyLayoutToViewHierarchy(UIView view)
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

		public static CGSize YogaIntrinsicSize(this UIView view)
		{
			var constrainedSize = new CGSize
			{
				Width = float.NaN,
				Height = float.NaN
			};
			return CalculateLayoutWithSize(view, constrainedSize);
		}

		static YogaSize MeasureView(YogaNode node, float width, YogaMeasureMode widthMode, float height, YogaMeasureMode heightMode)
		{
			var constrainedWidth = (widthMode == YogaMeasureMode.Undefined) ? nfloat.MaxValue : width;
			var constrainedHeight = (heightMode == YogaMeasureMode.Undefined) ? nfloat.MaxValue : height;

			UIView view = null;
			if (YogaKit.Bridges.ContainsKey(node))
				(YogaKit.Bridges[node] as YGNodeBridge).viewRef.TryGetTarget(out view);

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
}