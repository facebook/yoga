using System.Drawing;
using Facebook.Yoga;
using NUnit.Framework;
using System;
using UIKit;
using CoreGraphics;

namespace Facebook.YogaKit.iOS.Tests
{
	[TestFixture]
	public class YogaKitNativeTest
	{
		[Test]
		public void ScrollViewVertical()
		{
            var view = new UIScrollView() {
                Frame = new CGRect(0, 0, 100, 100),
            };

            view.Yoga().Overflow = YogaOverflow.Scroll;
            var subview = new UIView();
            subview.Yoga().Height = 1000;
            subview.Yoga().IsEnabled = true;

            view.AddSubview(subview);
            view.Yoga().IsEnabled = true;
            view.Yoga().ApplyLayout();
            Assert.True(view.ContentSize.Height == 1000);
		}

        [Test]
        public void NormalViewVertical()
        {
            var view = new UIView() {
                Frame = new CGRect(0,0, 100, 100),
            };


            var subview = new UIView();
            subview.Yoga().Height = 1000;
            subview.Yoga().Width = 2;
            subview.Yoga().IsEnabled = true;

            view.AddSubview(subview);
            view.Yoga().IsEnabled = true;
            view.Yoga().ApplyLayout();
            Assert.True(view.Bounds.Height == 100);
        }

	}
}
