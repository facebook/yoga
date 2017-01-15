using System;
using CoreGraphics;
using Facebook.Yoga;
using UIKit;

namespace Facebook.YogaKit.iOS.Sample
{
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
			root.Yoga().IsEnabled = true;

			root.Yoga().Width = (float)width;
			root.Yoga().Height = (float)height;
			root.Yoga().AlignItems = YogaAlign.Center;
			root.Yoga().JustifyContent = YogaJustify.Center;

			var child1 = new UIView { BackgroundColor = UIColor.Blue };
			child1.Yoga().IsEnabled = true;
			child1.Yoga().Width = 100;
			child1.Yoga().Height = 100;

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
			root.Yoga().ApplyLayout();
		}
	}
}
