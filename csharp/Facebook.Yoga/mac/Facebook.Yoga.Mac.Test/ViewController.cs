using System;

using AppKit;
using Foundation;
using CoreGraphics;

namespace Facebook.Yoga.Mac.Test
{
	public static class NSViewYogaExtensions
	{
		public static void ApplyYogaLayout(this NSView view, YogaNode n)
		{
			view.Frame = new CGRect(n.LayoutX, n.LayoutY, n.LayoutWidth, n.LayoutHeight);
			// This assumes your YogaNode and NSView children were inserted in same order
			for (int i = 0; i < n.Count; ++i) {
				YogaNode childNode = n[i];
				// Cocoa coord space is from bottom left not top left
				view.Subviews[i].Frame = new CGRect (childNode.LayoutX, n.LayoutHeight - childNode.LayoutY - childNode.LayoutHeight, childNode.LayoutWidth, childNode.LayoutHeight);
			}
		}
	}
	
	public partial class ViewController : NSViewController
	{
		public ViewController(IntPtr handle) : base(handle)
		{
		}

		public override void ViewDidLoad()
		{
			base.ViewDidLoad ();

			NSImage image = NSImage.ImageNamed (NSImageName.TrashFull);

			NSView root = CreateViewHierarchy (image);

			var rootNode = CalculateLayout (image.Size);

			root.ApplyYogaLayout (rootNode);

			View.AddSubview (root);
		}

		static NSView CreateViewHierarchy (NSImage image)
		{
			var root = new NSView ();
			NSImageView imageView = new NSImageView () {
				Image = image
			};
			root.AddSubview (imageView);

			NSTextView text = new NSTextView () {
				Value = "Hello World",
			};
			root.AddSubview (text);
			return root;
		}

		static YogaNode CalculateLayout (CGSize imageSize)
		{
			var rootNode = new YogaNode () {
				Width = 400,
				Height = 120,
				FlexDirection = YogaFlexDirection.Row
			};
			rootNode.SetPadding (YogaEdge.All, 20);

			var imageNode = new YogaNode () {
				Width = (float)imageSize.Width,
				Height = (float)imageSize.Height,
			};
			imageNode.SetMargin (YogaEdge.End, 20);

			var textNode = new YogaNode () {
				AlignSelf = YogaAlign.Center,
				FlexGrow = 1,
				Height = 60,
			};
			rootNode.Insert (0, imageNode);
			rootNode.Insert (1, textNode);
			rootNode.CalculateLayout ();

			return rootNode;
		}
	}
}
