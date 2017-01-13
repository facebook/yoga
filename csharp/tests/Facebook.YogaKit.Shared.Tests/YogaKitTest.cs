using System.Drawing;
using Facebook.Yoga;
using NUnit.Framework;
using System;
#if __IOS__
using NativeView = UIKit.UIView;
using CoreGraphics;
#endif

namespace Facebook.YogaKit
{
	[TestFixture]
	public class YogaKitTest
	{
		[Test]
		public void TestUsesYoga()
		{
			var view = new NativeView();
			Assert.False(view.Yoga().IsEnabled);
			view.Yoga().IsEnabled = true;
			Assert.True(view.Yoga().IsEnabled);
			view.Yoga().IsEnabled = false;
			Assert.False(view.Yoga().IsEnabled);
		}

		[Test]
		public void TestSizeThatFitsAsserts()
		{
			var view = new NativeView();
			Assert.Ignore("Not implemented yet");
			//  dispatch_sync(dispatch_queue_create("com.facebook.Yoga.testing", DISPATCH_QUEUE_SERIAL), ^(void){
			//    XCTAssertThrows(view.yoga.intrinsicSize);
			//  });
		}

		[Test]
		public void TestSizeThatFitsSmoke()
		{
			var container = new NativeView();
			container.Yoga().IsEnabled = true;
			container.Yoga().FlexDirection = YogaFlexDirection.Row;
			container.Yoga().AlignItems = YogaAlign.FlexStart;

			var longTextLabel = new UIKit.UILabel();
			longTextLabel.Text = @"This is a very very very very very very very very long piece of text.";
			longTextLabel.LineBreakMode = UIKit.UILineBreakMode.TailTruncation;
			longTextLabel.Lines = 1;
			longTextLabel.Yoga().IsEnabled = true;
			longTextLabel.Yoga().FlexShrink = 1;
			container.AddSubview(longTextLabel);

			var textBadgeView = new NativeView();
			textBadgeView.Yoga().IsEnabled = true;
			textBadgeView.Yoga().MarginLeft = 3.0f;
			textBadgeView.Yoga().Width = 10;
			textBadgeView.Yoga().Height = 10;
			container.AddSubview(textBadgeView);

			var containerSize = container.Yoga().IntrinsicSize;
			Assert.True(new SizeF(514, 21) == containerSize, $"Size is actually {containerSize})");
		}

		[Test]
		public void TestThatMarkingLeafsAsDirtyWillTriggerASizeRecalculation()
		{
			var container = new NativeView(new CGRect(0, 0, 500, 500));
			container.Yoga().IsEnabled = true;
			container.Yoga().FlexDirection = YogaFlexDirection.Row;
			container.Yoga().AlignItems = YogaAlign.FlexStart;

			var label = new UIKit.UILabel();
			label.Text = @"This is a short text.";
			label.Lines = 1;
			label.Yoga().IsEnabled = true;
			container.AddSubview(label);

			container.Yoga().ApplyLayout();
			Assert.True(new SizeF(146, 21) == label.Bounds.Size, $"Size is actually {label.Bounds.Size})");

			label.Text = @"This is a slightly longer text.";
			label.Yoga().MarkDirty();

			container.Yoga().ApplyLayout();
			Assert.True(new SizeF(213, 21) == label.Bounds.Size, $"Size is actually {label.Bounds.Size})");
		}

		[Test]
		public void TestFrameAndOriginPlacement()
		{
			var containerSize = new SizeF(320, 50);

			var container = new NativeView(new CGRect(0, 0, containerSize.Width, containerSize.Height));
			container.Yoga().IsEnabled = true;
			container.Yoga().FlexDirection = YogaFlexDirection.Row;

			for (int i = 0; i < 3; i++)
			{
				var subview = new NativeView();
				subview.Yoga().IsEnabled = true;
				subview.Yoga().FlexGrow = 1;
				container.AddSubview(subview);
			}
			container.Yoga().ApplyLayout();

			Assert.False(CGRect.Intersect(container.Subviews[0].Frame, container.Subviews[1].Frame) == CGRect.Empty);
			Assert.False(CGRect.Intersect(container.Subviews[1].Frame, container.Subviews[2].Frame) == CGRect.Empty);
			Assert.False(CGRect.Intersect(container.Subviews[0].Frame, container.Subviews[2].Frame) == CGRect.Empty);

			float totalWidth = 0;
			foreach (var view in container.Subviews)
				totalWidth += (float)view.Bounds.Size.Width;

			Assert.AreEqual(containerSize.Width, totalWidth, $"The container's width is {containerSize.Width}, the subviews take up {totalWidth}");
		}


		[Test]
		public void TestThatLayoutIsCorrectWhenWeSwapViewOrder()
		{
			var containerSize = new SizeF(300, 50);

			var container = new NativeView(new CGRect(0, 0, containerSize.Width, containerSize.Height));
			container.Yoga().IsEnabled = true;
			container.Yoga().FlexDirection = YogaFlexDirection.Row;

			var subview1 = new NativeView();
			subview1.Yoga().IsEnabled = true;
			subview1.Yoga().FlexGrow = 1;
			container.AddSubview(subview1);

			var subview2 = new NativeView();
			subview2.Yoga().IsEnabled = true;
			subview2.Yoga().FlexGrow = 1;
			container.AddSubview(subview2);

			var subview3 = new NativeView();
			subview3.Yoga().IsEnabled = true;
			subview3.Yoga().FlexGrow = 1;
			container.AddSubview(subview3);

			container.Yoga().ApplyLayout();

			Assert.True(subview1.Frame == new CGRect(0, 0, 100, 50));
			Assert.True(subview2.Frame == new CGRect(100, 0, 100, 50), $"It's actually {subview2.Frame}");
			Assert.True(subview3.Frame == new CGRect(200, 0, 100, 50));

			container.ExchangeSubview(2, 0);
			subview2.Yoga().IsIncludeInLayout = false;
			container.Yoga().ApplyLayout();

			Assert.True(subview3.Frame == new CGRect(0, 0, 150, 50));
			Assert.True(subview1.Frame == new CGRect(150, 0, 150, 50));
			//// this frame shouldn't have been modified since last time.
			Assert.True(subview2.Frame == new CGRect(100, 0, 100, 50));
		}

		[Test]
		public void TestThatWeRespectIncludeInLayoutFlag()
		{
			var containerSize = new SizeF(300, 50);

			var container = new NativeView(new CGRect(0, 0, containerSize.Width, containerSize.Height));
			container.Yoga().IsEnabled = true;
			container.Yoga().FlexDirection = YogaFlexDirection.Row;

			var subview1 = new NativeView();
			subview1.Yoga().IsEnabled = true;
			subview1.Yoga().FlexGrow = 1;
			container.AddSubview(subview1);

			var subview2 = new NativeView();
			subview2.Yoga().IsEnabled = true;
			subview2.Yoga().FlexGrow = 1;
			container.AddSubview(subview2);

			var subview3 = new NativeView();
			subview3.Yoga().IsEnabled = true;
			subview3.Yoga().FlexGrow = 1;
			container.AddSubview(subview3);

			container.Yoga().ApplyLayout();

			foreach (var view in container.Subviews)
			{
				Assert.True(new CGSize(100, 50) == view.Bounds.Size, $"Actual size is {view.Bounds.Size}");
			}

			subview3.Yoga().IsIncludeInLayout = false;
			container.Yoga().ApplyLayout();
			Assert.True(subview1.Frame.Size == new CGSize(150, 50), $"Actual size is {subview1.Frame.Size}");
			Assert.True(subview2.Frame.Size == new CGSize(150, 50), $"Actual size is {subview2.Frame.Size}");
			//// We don't set the frame to zero, so, it should be set to what it was previously at.
			Assert.True(subview3.Frame.Size == new CGSize(100, 50), $"Actual size is {subview3.Frame.Size}");
		}

		[Test]
		public void TestThatNumberOfChildrenIsCorrectWhenWeIgnoreSubviews()
		{
			var container = new NativeView();
			container.Yoga().IsEnabled = true;
			container.Yoga().FlexDirection = YogaFlexDirection.Row;

			var subview1 = new NativeView();
			subview1.Yoga().IsEnabled = true;
			subview1.Yoga().IsIncludeInLayout = false;
			container.AddSubview(subview1);

			var subview2 = new NativeView();
			subview2.Yoga().IsEnabled = true;
			subview2.Yoga().IsIncludeInLayout = false;
			container.AddSubview(subview2);

			var subview3 = new NativeView();
			subview3.Yoga().IsEnabled = true;
			subview3.Yoga().IsIncludeInLayout = true;
			container.AddSubview(subview3);

			container.Yoga().ApplyLayout();
			Assert.AreEqual(1, container.Yoga().NumberOfChildren);

			subview2.Yoga().IsIncludeInLayout = true;
			container.Yoga().ApplyLayout();
			Assert.AreEqual(2, container.Yoga().NumberOfChildren);
		}

		[Test]
		public void TestThatViewNotIncludedInFirstLayoutPassAreIncludedInSecond()
		{
			var containerSize = new SizeF(300, 50);

			var container = new NativeView(new CGRect(0, 0, containerSize.Width, containerSize.Height));
			container.Yoga().IsEnabled = true;
			container.Yoga().FlexDirection = YogaFlexDirection.Row;

			var subview1 = new NativeView();
			subview1.Yoga().IsEnabled = true;
			subview1.Yoga().FlexGrow = 1;
			container.AddSubview(subview1);

			var subview2 = new NativeView();
			subview2.Yoga().IsEnabled = true;
			subview2.Yoga().FlexGrow = 1;
			container.AddSubview(subview2);

			var subview3 = new NativeView();
			subview3.Yoga().IsEnabled = true;
			subview3.Yoga().FlexGrow = 1;
			subview3.Yoga().IsIncludeInLayout = false;
			container.AddSubview(subview3);

			container.Yoga().ApplyLayout();

			Assert.True(subview1.Frame.Size == new CGSize(150, 50), $"Actual size is {subview1.Frame.Size}");
			Assert.True(subview2.Frame.Size == new CGSize(150, 50), $"Actual size is {subview2.Frame.Size}");
			Assert.True(subview3.Frame.Size == CGSize.Empty, $"Actual size is {subview3.Frame.Size}");

			subview3.Yoga().IsIncludeInLayout = true;
			container.Yoga().ApplyLayout();

			foreach (var view in container.Subviews)
			{
				Assert.True(new CGSize(100, 50) == view.Bounds.Size, $"Actual size is {view.Bounds.Size}");
			}
		}

		[Test]
		public void TestYogaIsLeafFlag()
		{
			var view = new NativeView();
			Assert.True(view.Yoga().IsLeaf);

			for (int i = 0; i < 10; i++)
			{
				var subView = new NativeView();
				view.AddSubview(subView);
			}
			Assert.True(view.Yoga().IsLeaf);
			view.Yoga().IsEnabled = true;
			view.Yoga().Width = 50.0f;
			Assert.True(view.Yoga().IsLeaf);

			var subView1 = view.Subviews[0];
			subView1.Yoga().IsEnabled = true;
			subView1.Yoga().Width = 50.0f;
			Assert.False(view.Yoga().IsLeaf);
		}

		[Test]
		public void TestThatWeCorrectlyAttachNestedViews()
		{
			var containerSize = new SizeF(300, 50);

			var container = new NativeView(new CGRect(0, 0, containerSize.Width, containerSize.Height));
			container.Yoga().IsEnabled = true;
			container.Yoga().FlexDirection = YogaFlexDirection.Column;

			var subview1 = new NativeView();
			subview1.Yoga().IsEnabled = true;
			subview1.Yoga().Width = 100;
			subview1.Yoga().FlexGrow = 1;
			subview1.Yoga().FlexDirection = YogaFlexDirection.Column;
			container.AddSubview(subview1);

			var subview2 = new NativeView();
			subview2.Yoga().IsEnabled = true;
			subview2.Yoga().Width = 150;
			subview2.Yoga().FlexGrow = 1;
			subview2.Yoga().FlexDirection = YogaFlexDirection.Column;
			container.AddSubview(subview2);

			foreach (var view in new NativeView[] { subview1, subview2 })
			{
				var someView = new NativeView();
				someView.Yoga().IsEnabled = true;
				someView.Yoga().FlexGrow = 1;
				view.AddSubview(someView);
			}
			container.Yoga().ApplyLayout();

			// Add the same amount of new views, reapply layout.
			foreach (var view in new NativeView[] { subview1, subview2 })
			{
				var someView = new NativeView();
				someView.Yoga().IsEnabled = true;
				someView.Yoga().FlexGrow = 1;
				view.AddSubview(someView);
			}
			container.Yoga().ApplyLayout();

			Assert.True(new CGSize(100, 25) == subview1.Bounds.Size, $"Actual size is {subview1.Bounds.Size}");
			foreach (var subview in subview1.Subviews)
			{
				var subviewSize = subview.Bounds.Size;
				Assert.False(subviewSize.IsEmpty);
				Assert.False(nfloat.IsNaN(subviewSize.Height));
				Assert.False(nfloat.IsNaN(subviewSize.Width));
			}

			Assert.True(new CGSize(150, 25) == subview2.Bounds.Size, $"Actual size is {subview2.Bounds.Size}");
			foreach (var subview in subview2.Subviews)
			{
				var subviewSize = subview.Bounds.Size;
				Assert.False(subviewSize.IsEmpty);
				Assert.False(nfloat.IsNaN(subviewSize.Height));
				Assert.False(nfloat.IsNaN(subviewSize.Width));
			}
		}

		[Test]
		public void TestThatANonLeafNodeCanBecomeALeafNode()
		{
			var containerSize = new SizeF(300, 50);

			var container = new NativeView(new CGRect(0, 0, containerSize.Width, containerSize.Height));
			container.Yoga().IsEnabled = true;

			var subview1 = new NativeView();
			subview1.Yoga().IsEnabled = true;
			container.AddSubview(subview1);

			var subview2 = new NativeView();
			subview2.Yoga().IsEnabled = true;
			container.AddSubview(subview2);
			container.Yoga().ApplyLayout();
			subview2.RemoveFromSuperview();
			container.Yoga().ApplyLayout();
		}
	}
}
