using System;
using CoreGraphics;
using Facebook.YogaKit.iOS;
using Foundation;
using UIKit;

namespace Facebook.Yoga.iOS.Test
{

	public static class UIViewYogaExtensions
	{
		public static void ApplyYogaLayout(this UIView view, YogaNode n)
		{
			view.Frame = new CGRect(n.LayoutX, n.LayoutY, n.LayoutWidth, n.LayoutHeight);
			// This assumes your YogaNode and NSView children were inserted in same order
			for (int i = 0; i < n.Count; ++i)
			{
				YogaNode childNode = n[i];
				view.Subviews[i].Frame = new CGRect(childNode.LayoutX, childNode.LayoutY, childNode.LayoutWidth, childNode.LayoutHeight);
			}
		}
	}

	public partial class ViewController : UIViewController
	{
		protected ViewController(IntPtr handle) : base(handle)
		{
			// Note: this .ctor should not contain any initialization logic.
		}

		public override void ViewDidLoad()
		{
			base.ViewDidLoad();

			CreateViewHierarchy(View, View.Bounds.Size.Width, View.Bounds.Size.Height);
		}

		static void CreateViewHierarchy(UIView root, nfloat width, nfloat height)
		{
			root.BackgroundColor = UIColor.Red;

			root.UsesYoga(true);
			root.YogaWidth(width);
			root.YogaWidth(height);
			root.YogaAlignItems(YogaAlign.Center);
			root.YogaJustify(YogaJustify.Center);

			var child1 = new UIView { BackgroundColor = UIColor.Blue };
			child1.YogaWidth(100);
			child1.YogaHeight(100);
			child1.UsesYoga(true);

			var child2 = new UIView
			{
				BackgroundColor = UIColor.Green,
				Frame = new CGRect { Size = new CGSize(200, 100) }
			};

			var child3 = new UIView
			{
				BackgroundColor = UIColor.Yellow,
				Frame = new CGRect { Size = new CGSize(100, 100) }
			};

			child2.AddSubview(child3);
			root.AddSubview(child1);
			root.AddSubview(child2);
			root.YogaApplyLayout();
		}

		public override void DidReceiveMemoryWarning()
		{
			base.DidReceiveMemoryWarning();
			// Release any cached data, images, etc that aren't in use.
		}
	}
}
