using System;
using CoreGraphics;
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
			UIImage image = FromUrl("https://placehold.it/50x50");

			UIView root = CreateViewHierarchy(image);

			var rootNode = CalculateLayout(image.Size);

			root.ApplyYogaLayout(rootNode);

			View.AddSubview(root);

		}
		static UIImage FromUrl(string uri)
		{
			using (var url = new NSUrl(uri))
			using (var data = NSData.FromUrl(url))
				return UIImage.LoadFromData(data);
		}
		static UIView CreateViewHierarchy(UIImage image)
		{
			var root = new UIView();
			UIImageView imageView = new UIImageView()
			{
				Image = image
			};
			root.AddSubview(imageView);

			UITextField text = new UITextField()
			{
				Text = "Hello World",
			};
			root.AddSubview(text);
			return root;
		}

		static YogaNode CalculateLayout(CGSize imageSize)
		{
			var rootNode = new YogaNode()
			{
				Width = 400,
				Height = 120,
				FlexDirection = YogaFlexDirection.Row
			};
			rootNode.SetPadding(YogaEdge.All, 20);

			var imageNode = new YogaNode()
			{
				Width = (float)imageSize.Width,
			};
			imageNode.SetMargin(YogaEdge.End, 20);

			var textNode = new YogaNode()
			{
				AlignSelf = YogaAlign.Center,
				FlexGrow = 1,
			};
			rootNode.Insert(0, imageNode);
			rootNode.Insert(1, textNode);
			rootNode.CalculateLayout();

			return rootNode;
		}

		public override void DidReceiveMemoryWarning()
		{
			base.DidReceiveMemoryWarning();
			// Release any cached data, images, etc that aren't in use.
		}
	}
}
