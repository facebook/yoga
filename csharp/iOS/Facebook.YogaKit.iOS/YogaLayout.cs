using System.Collections.Generic;
using CoreGraphics;
using Facebook.Yoga;
using Foundation;
using UIKit;

namespace Facebook.YogaKit
{
	public partial class YogaLayout : NSObject
	{
		static IEnumerable<UIView> GetChildren(UIView view) => view.Subviews;

		static void MeasureNativeView(UIView view, float constrainedWidth, float constrainedHeight, out float sizeThatFitsWidth, out float sizeThatFitsHeight)
		{
			var sizeThatFits = view.SizeThatFits(new CGSize(constrainedWidth, constrainedHeight));
			sizeThatFitsWidth = (float)sizeThatFits.Width;
			sizeThatFitsHeight = (float)sizeThatFits.Height;
		}

		static void GetWidthHeightOfNativeView(UIView view, out float width, out float height)
		{
			width = (float)view.Bounds.Width;
			height = (float)view.Bounds.Height;
		}

        static float NativePixelScale => (float)UIScreen.MainScreen.Scale;


		static void ApplyLayoutToNativeView(UIView view, YogaNode node)
		{
			var topLeft = new CGPoint(node.LayoutX, node.LayoutY);
			var bottomRight = new CGPoint(topLeft.X + node.LayoutWidth, topLeft.Y + node.LayoutHeight);
            if (view is UIScrollView scrollView)
            {
                scrollView.ContentSize = new CGSize(RoundPointValue((float)bottomRight.X) - RoundPointValue((float)topLeft.X), RoundPointValue((float)bottomRight.Y) - RoundPointValue((float)topLeft.Y));
            }
            else
            {
                view.Frame = new CGRect(RoundPointValue((float)topLeft.X), RoundPointValue((float)topLeft.Y), RoundPointValue((float)bottomRight.X) - RoundPointValue((float)topLeft.X), RoundPointValue((float)bottomRight.Y) - RoundPointValue((float)topLeft.Y));
            }
		}

		bool _disposed;
		protected override void Dispose(bool disposing)
		{
			if (disposing && !_disposed)
			{
				_disposed = true;
				if (YogaKit.Bridges.ContainsKey(_node))
				{
					YogaKit.Bridges.Remove(_node);
				}
				_node = null;
				_viewRef = null;
			}
			base.Dispose(disposing);
		}
	}
}
