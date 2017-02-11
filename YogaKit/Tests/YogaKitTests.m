/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#import <XCTest/XCTest.h>

#import <YogaKit/UIView+Yoga.h>
#import <YogaKit/YGLayout+Private.h>
#import <yoga/Yoga.h>

@interface YogaKitTests : XCTestCase
@end

@implementation YogaKitTests

- (void)testNodesAreDeallocedWithSingleView
{
  __weak YGLayout *layoutRef = nil;

  @autoreleasepool {
    UIView *view = [[UIView alloc] initWithFrame:CGRectZero];
    view.yoga.flexBasis = 1;

    layoutRef = view.yoga;
    XCTAssertNotNil(layoutRef);

    view = nil;
  }

  XCTAssertNil(layoutRef);
}

- (void)testNodesAreDeallocedCascade
{
  __weak YGLayout *topLayout = nil;
  __weak YGLayout *subviewLayout = nil;

  @autoreleasepool {
    UIView *view = [[UIView alloc] initWithFrame:CGRectZero];
    topLayout = view.yoga;
    topLayout.flexBasis = 1;

    UIView *subview = [[UIView alloc] initWithFrame:CGRectZero];
    subviewLayout = subview.yoga;
    subviewLayout.flexBasis = 1;

    view = nil;
  }

  XCTAssertNil(topLayout);
  XCTAssertNil(subviewLayout);
}

- (void)testIsEnabled
{
  UIView *view = [[UIView alloc] initWithFrame:CGRectZero];
  XCTAssertFalse(view.yoga.isEnabled);

  view.yoga.isEnabled = YES;
  XCTAssertTrue(view.yoga.isEnabled);

  view.yoga.isEnabled = NO;
  XCTAssertFalse(view.yoga.isEnabled);
}

- (void)testSizeThatFitsAsserts
{
  UIView *view = [[UIView alloc] initWithFrame:CGRectZero];
  dispatch_sync(dispatch_queue_create("com.facebook.Yoga.testing", DISPATCH_QUEUE_SERIAL), ^(void){
    XCTAssertThrows(view.yoga.intrinsicSize);
  });
}

- (void)testSizeThatFitsSmoke
{
  UIView *container = [[UIView alloc] initWithFrame:CGRectZero];
  container.yoga.isEnabled = YES;
  container.yoga.flexDirection = YGFlexDirectionRow;
  container.yoga.alignItems = YGAlignFlexStart;

  UILabel *longTextLabel = [[UILabel alloc] initWithFrame:CGRectZero];
  longTextLabel.text = @"This is a very very very very very very very very long piece of text.";
  longTextLabel.lineBreakMode = NSLineBreakByTruncatingTail;
  longTextLabel.numberOfLines = 1;
  longTextLabel.yoga.isEnabled = YES;
  longTextLabel.yoga.flexShrink = 1;
  [container addSubview:longTextLabel];

  UIView *textBadgeView = [[UIView alloc] initWithFrame:CGRectZero];
  textBadgeView.yoga.isEnabled = YES;
  textBadgeView.yoga.margin = 0;
  textBadgeView.yoga.width = 10;
  textBadgeView.yoga.height = 10;
  [container addSubview:textBadgeView];

  const CGSize textBadgeViewSize = textBadgeView.yoga.intrinsicSize;
  XCTAssertEqual(textBadgeViewSize.height, 10);
  XCTAssertEqual(textBadgeViewSize.width, 10);

  const CGSize containerSize = container.yoga.intrinsicSize;
  const CGSize longTextLabelSize = longTextLabel.yoga.intrinsicSize;

  XCTAssertEqual(longTextLabelSize.height, containerSize.height);
  XCTAssertEqual(longTextLabelSize.width + textBadgeView.yoga.intrinsicSize.width, containerSize.width);
}

- (void)testPreservingOrigin
{
  UIView *container = [[UIView alloc] initWithFrame:CGRectMake(0,0,50,75)];
  container.yoga.isEnabled = YES;

  UIView *view = [[UIView alloc] initWithFrame:CGRectZero];
  view.yoga.isEnabled = YES;
  view.yoga.flexBasis = 0;
  view.yoga.flexGrow = 1;
  [container addSubview:view];

  UIView *view2 = [[UIView alloc] initWithFrame:CGRectZero];
  view2.yoga.isEnabled = YES;
  view2.yoga.marginTop = 25;
  view2.yoga.flexBasis = 0;
  view2.yoga.flexGrow = 1;
  [container addSubview:view2];

  [container.yoga applyLayoutPreservingOrigin:YES];
  XCTAssertEqual(50, view2.frame.origin.y);

  [view2.yoga applyLayoutPreservingOrigin:NO];
  XCTAssertEqual(25, view2.frame.origin.y);
}

- (void)testThatMarkingLeafsAsDirtyWillTriggerASizeRecalculation
{
  UIView *container = [[UIView alloc] initWithFrame:CGRectMake(0, 0, 500, 50)];
  container.yoga.isEnabled = YES;
  container.yoga.flexDirection = YGFlexDirectionRow;
  container.yoga.alignItems = YGAlignFlexStart;

  UILabel *view = [[UILabel alloc] initWithFrame:CGRectZero];
  view.text = @"This is a short text.";
  view.numberOfLines = 1;
  view.yoga.isEnabled = YES;
  [container addSubview:view];

  [container.yoga applyLayoutPreservingOrigin:YES];
  CGSize const viewSizeAfterFirstPass = view.frame.size;

  view.text = @"This is a slightly longer text.";
  XCTAssertTrue(CGSizeEqualToSize(view.frame.size, viewSizeAfterFirstPass));

  [view.yoga markDirty];

  [container.yoga applyLayoutPreservingOrigin:YES];
  XCTAssertFalse(CGSizeEqualToSize(view.frame.size, viewSizeAfterFirstPass));
}

- (void)testFrameAndOriginPlacement
{
  const CGSize containerSize = CGSizeMake(320, 50);

  UIView *container = [[UIView alloc] initWithFrame:CGRectMake(0, 0, containerSize.width, containerSize.height)];
  container.yoga.isEnabled = YES;
  container.yoga.flexDirection = YGFlexDirectionRow;

  UIView *subview1 = [[UIView alloc] initWithFrame:CGRectZero];
  subview1.yoga.isEnabled = YES;
  subview1.yoga.flexGrow = 1;
  [container addSubview:subview1];

  UIView *subview2 = [[UIView alloc] initWithFrame:CGRectZero];
  subview2.yoga.isEnabled = YES;
  subview2.yoga.flexGrow = 1;
  [container addSubview:subview2];

  UIView *subview3 = [[UIView alloc] initWithFrame:CGRectZero];
  subview3.yoga.isEnabled = YES;
  subview3.yoga.flexGrow = 1;
  [container addSubview:subview3];

  [container.yoga applyLayoutPreservingOrigin:YES];

  XCTAssertEqualWithAccuracy(subview2.frame.origin.x, CGRectGetMaxX(subview1.frame), FLT_EPSILON);
  XCTAssertEqualWithAccuracy(subview3.frame.origin.x, CGRectGetMaxX(subview2.frame), FLT_EPSILON);

  CGFloat totalWidth = 0;
  for (UIView *view in container.subviews) {
    totalWidth += view.bounds.size.width;
  }

  XCTAssertEqual(containerSize.width, totalWidth, @"The container's width is %.6f, the subviews take up %.6f", containerSize.width, totalWidth);
}

- (void)testThatLayoutIsCorrectWhenWeSwapViewOrder
{
  const CGSize containerSize = CGSizeMake(300, 50);

  UIView *container = [[UIView alloc] initWithFrame:CGRectMake(0, 0, containerSize.width, containerSize.height)];
  container.yoga.isEnabled = YES;
  container.yoga.flexDirection = YGFlexDirectionRow;

  UIView *subview1 = [[UIView alloc] initWithFrame:CGRectZero];
  subview1.yoga.isEnabled = YES;
  subview1.yoga.flexGrow = 1;
  [container addSubview:subview1];

  UIView *subview2 = [[UIView alloc] initWithFrame:CGRectZero];
  subview2.yoga.isEnabled = YES;
  subview2.yoga.flexGrow = 1;
  [container addSubview:subview2];

  UIView *subview3 = [[UIView alloc] initWithFrame:CGRectZero];
  subview3.yoga.isEnabled = YES;
  subview3.yoga.flexGrow = 1;
  [container addSubview:subview3];

  [container.yoga applyLayoutPreservingOrigin:YES];

  XCTAssertTrue(CGRectEqualToRect(subview1.frame, CGRectMake(0, 0, 100, 50)));
  XCTAssertTrue(CGRectEqualToRect(subview2.frame, CGRectMake(100, 0, 100, 50)));
  XCTAssertTrue(CGRectEqualToRect(subview3.frame, CGRectMake(200, 0, 100, 50)));

  [container exchangeSubviewAtIndex:2 withSubviewAtIndex:0];
  subview2.yoga.isIncludedInLayout = NO;
  [container.yoga applyLayoutPreservingOrigin:YES];

  XCTAssertTrue(CGRectEqualToRect(subview3.frame, CGRectMake(0, 0, 150, 50)));
  XCTAssertTrue(CGRectEqualToRect(subview1.frame, CGRectMake(150, 0, 150, 50)));

  // this frame shouldn't have been modified since last time.
  XCTAssertTrue(CGRectEqualToRect(subview2.frame, CGRectMake(100, 0, 100, 50)));
}

- (void)testThatWeRespectIncludeInLayoutFlag
{
  const CGSize containerSize = CGSizeMake(300, 50);

  UIView *container = [[UIView alloc] initWithFrame:CGRectMake(0, 0, containerSize.width, containerSize.height)];
  container.yoga.isEnabled = YES;
  container.yoga.flexDirection = YGFlexDirectionRow;

  UIView *subview1 = [[UIView alloc] initWithFrame:CGRectZero];
  subview1.yoga.isEnabled = YES;
  subview1.yoga.flexGrow = 1;
  [container addSubview:subview1];

  UIView *subview2 = [[UIView alloc] initWithFrame:CGRectZero];
  subview2.yoga.isEnabled = YES;
  subview2.yoga.flexGrow = 1;
  [container addSubview:subview2];

  UIView *subview3 = [[UIView alloc] initWithFrame:CGRectZero];
  subview3.yoga.isEnabled = YES;
  subview3.yoga.flexGrow = 1;
  [container addSubview:subview3];

  [container.yoga applyLayoutPreservingOrigin:YES];

  for (UIView *subview in container.subviews) {
    XCTAssertEqual(subview.bounds.size.width, 100);
  }

  subview3.yoga.isIncludedInLayout = NO;
  [container.yoga applyLayoutPreservingOrigin:YES];

  XCTAssertEqual(subview1.bounds.size.width, 150);
  XCTAssertEqual(subview2.bounds.size.width, 150);

  // We don't set the frame to zero, so, it should be set to what it was previously at.
  XCTAssertEqual(subview3.bounds.size.width, 100);
}

- (void)testThatNumberOfChildrenIsCorrectWhenWeIgnoreSubviews
{
  UIView *container = [[UIView alloc] initWithFrame:CGRectZero];
  container.yoga.isEnabled = YES;
  container.yoga.flexDirection = YGFlexDirectionRow;

  UIView *subview1 = [[UIView alloc] initWithFrame:CGRectZero];
  subview1.yoga.isEnabled = YES;
  subview1.yoga.isIncludedInLayout = NO;
  [container addSubview:subview1];

  UIView *subview2 = [[UIView alloc] initWithFrame:CGRectZero];
  subview2.yoga.isEnabled = YES;
  subview2.yoga.isIncludedInLayout = NO;
  [container addSubview:subview2];

  UIView *subview3 = [[UIView alloc] initWithFrame:CGRectZero];
  subview3.yoga.isEnabled = YES;
  subview3.yoga.isIncludedInLayout = YES;
  [container addSubview:subview3];

  [container.yoga applyLayoutPreservingOrigin:YES];
  XCTAssertEqual(container.yoga.numberOfChildren, 1);

  subview2.yoga.isIncludedInLayout = YES;
  [container.yoga applyLayoutPreservingOrigin:YES];
  XCTAssertEqual(container.yoga.numberOfChildren, 2);
}

- (void)testThatViewNotIncludedInFirstLayoutPassAreIncludedInSecond
{
  UIView *container = [[UIView alloc] initWithFrame:CGRectMake(0, 0, 300, 50)];
  container.yoga.isEnabled = YES;
  container.yoga.flexDirection = YGFlexDirectionRow;

  UIView *subview1 = [[UIView alloc] initWithFrame:CGRectZero];
  subview1.yoga.isEnabled = YES;
  subview1.yoga.flexGrow = 1;
  [container addSubview:subview1];

  UIView *subview2 = [[UIView alloc] initWithFrame:CGRectZero];
  subview2.yoga.isEnabled = YES;
  subview2.yoga.flexGrow = 1;
  [container addSubview:subview2];

  UIView *subview3 = [[UIView alloc] initWithFrame:CGRectZero];
  subview3.yoga.isEnabled = YES;
  subview3.yoga.flexGrow = 1;
  subview3.yoga.isIncludedInLayout = NO;
  [container addSubview:subview3];

  [container.yoga applyLayoutPreservingOrigin:YES];

  XCTAssertEqual(subview1.bounds.size.width, 150);
  XCTAssertEqual(subview2.bounds.size.width, 150);
  XCTAssertEqual(subview3.bounds.size.width, 0);

  subview3.yoga.isIncludedInLayout = YES;
  [container.yoga applyLayoutPreservingOrigin:YES];

  XCTAssertEqual(subview1.bounds.size.width, 100);
  XCTAssertEqual(subview2.bounds.size.width, 100);
  XCTAssertEqual(subview3.bounds.size.width, 100);
}

- (void)testIsLeafFlag
{
  UIView *view = [[UIView alloc] initWithFrame:CGRectZero];
  XCTAssertTrue(view.yoga.isLeaf);

  for (int i=0; i<10; i++) {
    UIView *subview = [[UIView alloc] initWithFrame:CGRectZero];
    [view addSubview:subview];
  }
  XCTAssertTrue(view.yoga.isLeaf);

  view.yoga.isEnabled = YES;
  view.yoga.width = 50.0;
  XCTAssertTrue(view.yoga.isLeaf);

  UIView *const subview = view.subviews[0];
  subview.yoga.isEnabled = YES;
  subview.yoga.width = 50.0;
  XCTAssertFalse(view.yoga.isLeaf);
}

- (void)testThatWeCorrectlyAttachNestedViews
{
    UIView *container = [[UIView alloc] initWithFrame:CGRectMake(0, 0, 300, 50)];
    container.yoga.isEnabled = YES;
    container.yoga.flexDirection = YGFlexDirectionColumn;

    UIView *subview1 = [[UIView alloc] initWithFrame:CGRectZero];
    subview1.yoga.isEnabled = YES;
    subview1.yoga.width = 100;
    subview1.yoga.flexGrow = 1;
    subview1.yoga.flexDirection = YGFlexDirectionColumn;
    [container addSubview:subview1];

    UIView *subview2 = [[UIView alloc] initWithFrame:CGRectZero];
    subview2.yoga.isEnabled = YES;
    subview2.yoga.width = 150;
    subview2.yoga.flexGrow = 1;
    subview2.yoga.flexDirection = YGFlexDirectionColumn;
    [container addSubview:subview2];

    for (UIView *view in @[subview1, subview2]) {
        UIView *someView = [[UIView alloc] initWithFrame:CGRectZero];
        someView.yoga.isEnabled = YES;
        someView.yoga.flexGrow = 1;
        [view addSubview:someView];
    }
    [container.yoga applyLayoutPreservingOrigin:YES];

    // Add the same amount of new views, reapply layout.
    for (UIView *view in @[subview1, subview2]) {
        UIView *someView = [[UIView alloc] initWithFrame:CGRectZero];
        someView.yoga.isEnabled = YES;
        someView.yoga.flexGrow = 1;
        [view addSubview:someView];
    }
    [container.yoga applyLayoutPreservingOrigin:YES];

    XCTAssertEqual(subview1.bounds.size.width, 100);
    XCTAssertEqual(subview1.bounds.size.height, 25);
    for (UIView *subview in subview1.subviews) {
        const CGSize subviewSize = subview.bounds.size;
        XCTAssertNotEqual(subviewSize.width, 0);
        XCTAssertNotEqual(subviewSize.height, 0);
        XCTAssertFalse(isnan(subviewSize.height));
        XCTAssertFalse(isnan(subviewSize.width));
    }

    XCTAssertEqual(subview2.bounds.size.width, 150);
    XCTAssertEqual(subview2.bounds.size.height, 25);
    for (UIView *subview in subview2.subviews) {
        const CGSize subviewSize = subview.bounds.size;
        XCTAssertNotEqual(subviewSize.width, 0);
        XCTAssertNotEqual(subviewSize.height, 0);
        XCTAssertFalse(isnan(subviewSize.height));
        XCTAssertFalse(isnan(subviewSize.width));
    }
}

- (void)testThatANonLeafNodeCanBecomeALeafNode
{
    UIView *container = [[UIView alloc] initWithFrame:CGRectMake(0, 0, 300, 50)];
    container.yoga.isEnabled = YES;

    UIView *subview1 = [[UIView alloc] initWithFrame:CGRectZero];
    subview1.yoga.isEnabled = YES;
    [container addSubview:subview1];

    UIView *subview2 = [[UIView alloc] initWithFrame:CGRectZero];
    subview2.yoga.isEnabled = YES;
    [subview1 addSubview:subview2];

    [container.yoga applyLayoutPreservingOrigin:YES];
    [subview2 removeFromSuperview];
    [container.yoga applyLayoutPreservingOrigin:YES];
}

- (void)testPositionalPropertiesWork
{
  UIView *view = [[UIView alloc] initWithFrame:CGRectZero];

  view.yoga.left = 1;
  XCTAssertEqual(YGNodeStyleGetPosition(view.yoga.node, YGEdgeLeft).value, 1);
  XCTAssertEqual(YGNodeStyleGetPosition(view.yoga.node, YGEdgeLeft).unit, YGUnitPixel);
  XCTAssertEqual(view.yoga.left, 1);

  view.yoga.right = 2;
  XCTAssertEqual(YGNodeStyleGetPosition(view.yoga.node, YGEdgeRight).value, 2);
  XCTAssertEqual(YGNodeStyleGetPosition(view.yoga.node, YGEdgeRight).unit, YGUnitPixel);
  XCTAssertEqual(view.yoga.right, 2);

  view.yoga.top = 3;
  XCTAssertEqual(YGNodeStyleGetPosition(view.yoga.node, YGEdgeTop).value, 3);
  XCTAssertEqual(YGNodeStyleGetPosition(view.yoga.node, YGEdgeTop).unit, YGUnitPixel);
  XCTAssertEqual(view.yoga.top, 3);

  view.yoga.bottom = 4;
  XCTAssertEqual(YGNodeStyleGetPosition(view.yoga.node, YGEdgeBottom).value, 4);
  XCTAssertEqual(YGNodeStyleGetPosition(view.yoga.node, YGEdgeBottom).unit, YGUnitPixel);
  XCTAssertEqual(view.yoga.bottom, 4);

  view.yoga.start = 5;
  XCTAssertEqual(YGNodeStyleGetPosition(view.yoga.node, YGEdgeStart).value, 5);
  XCTAssertEqual(YGNodeStyleGetPosition(view.yoga.node, YGEdgeStart).unit, YGUnitPixel);
  XCTAssertEqual(view.yoga.start, 5);

  view.yoga.end = 6;
  XCTAssertEqual(YGNodeStyleGetPosition(view.yoga.node, YGEdgeEnd).value, 6);
  XCTAssertEqual(YGNodeStyleGetPosition(view.yoga.node, YGEdgeEnd).unit, YGUnitPixel);
  XCTAssertEqual(view.yoga.end, 6);
}

- (void)testMarginPropertiesWork
{
  UIView *view = [[UIView alloc] initWithFrame:CGRectZero];

  view.yoga.margin = 1;
  XCTAssertEqual(view.yoga.margin, 1);
  XCTAssertTrue(isnan(view.yoga.marginLeft));
  XCTAssertTrue(isnan(view.yoga.marginRight));
  XCTAssertTrue(isnan(view.yoga.marginStart));
  XCTAssertTrue(isnan(view.yoga.marginEnd));
  XCTAssertTrue(isnan(view.yoga.marginTop));
  XCTAssertTrue(isnan(view.yoga.marginBottom));
  XCTAssertTrue(isnan(view.yoga.marginHorizontal));
  XCTAssertTrue(isnan(view.yoga.marginVertical));

  view.yoga.marginHorizontal = 2;
  XCTAssertEqual(view.yoga.marginHorizontal, 2);
  XCTAssertTrue(isnan(view.yoga.marginLeft));
  XCTAssertTrue(isnan(view.yoga.marginRight));
  XCTAssertTrue(isnan(view.yoga.marginStart));
  XCTAssertTrue(isnan(view.yoga.marginEnd));

  view.yoga.marginVertical = 3;
  XCTAssertEqual(view.yoga.marginVertical, 3);
  XCTAssertTrue(isnan(view.yoga.marginTop));
  XCTAssertTrue(isnan(view.yoga.marginBottom));

  view.yoga.marginLeft = 4;
  XCTAssertEqual(YGNodeStyleGetMargin(view.yoga.node, YGEdgeLeft).value, 4);
  XCTAssertEqual(YGNodeStyleGetMargin(view.yoga.node, YGEdgeLeft).unit, YGUnitPixel);
  XCTAssertEqual(view.yoga.marginLeft, 4);

  view.yoga.marginRight = 5;
  XCTAssertEqual(YGNodeStyleGetMargin(view.yoga.node, YGEdgeRight).value, 5);
  XCTAssertEqual(YGNodeStyleGetMargin(view.yoga.node, YGEdgeRight).unit, YGUnitPixel);
  XCTAssertEqual(view.yoga.marginRight, 5);

  view.yoga.marginTop = 6;
  XCTAssertEqual(YGNodeStyleGetMargin(view.yoga.node, YGEdgeTop).value, 6);
  XCTAssertEqual(YGNodeStyleGetMargin(view.yoga.node, YGEdgeTop).unit, YGUnitPixel);
  XCTAssertEqual(view.yoga.marginTop, 6);

  view.yoga.marginBottom = 7;
  XCTAssertEqual(YGNodeStyleGetMargin(view.yoga.node, YGEdgeBottom).value, 7);
  XCTAssertEqual(YGNodeStyleGetMargin(view.yoga.node, YGEdgeBottom).unit, YGUnitPixel);
  XCTAssertEqual(view.yoga.marginBottom, 7);

  view.yoga.marginStart = 8;
  XCTAssertEqual(YGNodeStyleGetMargin(view.yoga.node, YGEdgeStart).value, 8);
  XCTAssertEqual(YGNodeStyleGetMargin(view.yoga.node, YGEdgeStart).unit, YGUnitPixel);
  XCTAssertEqual(view.yoga.marginStart, 8);

  view.yoga.marginEnd = 9;
  XCTAssertEqual(YGNodeStyleGetMargin(view.yoga.node, YGEdgeEnd).value, 9);
  XCTAssertEqual(YGNodeStyleGetMargin(view.yoga.node, YGEdgeEnd).unit, YGUnitPixel);
  XCTAssertEqual(view.yoga.marginEnd, 9);
}

- (void)testPaddingPropertiesWork
{
  UIView *view = [[UIView alloc] initWithFrame:CGRectZero];

  view.yoga.padding = 1;
  XCTAssertEqual(view.yoga.padding, 1);
  XCTAssertTrue(isnan(view.yoga.paddingLeft));
  XCTAssertTrue(isnan(view.yoga.paddingRight));
  XCTAssertTrue(isnan(view.yoga.paddingStart));
  XCTAssertTrue(isnan(view.yoga.paddingEnd));
  XCTAssertTrue(isnan(view.yoga.paddingTop));
  XCTAssertTrue(isnan(view.yoga.paddingBottom));
  XCTAssertTrue(isnan(view.yoga.paddingHorizontal));
  XCTAssertTrue(isnan(view.yoga.paddingVertical));

  view.yoga.paddingHorizontal = 2;
  XCTAssertEqual(view.yoga.paddingHorizontal, 2);
  XCTAssertTrue(isnan(view.yoga.paddingLeft));
  XCTAssertTrue(isnan(view.yoga.paddingRight));
  XCTAssertTrue(isnan(view.yoga.paddingStart));
  XCTAssertTrue(isnan(view.yoga.paddingEnd));

  view.yoga.paddingVertical = 3;
  XCTAssertEqual(view.yoga.paddingVertical, 3);
  XCTAssertTrue(isnan(view.yoga.paddingTop));
  XCTAssertTrue(isnan(view.yoga.paddingBottom));

  view.yoga.paddingLeft = 4;
  XCTAssertEqual(YGNodeStyleGetPadding(view.yoga.node, YGEdgeLeft).value, 4);
  XCTAssertEqual(YGNodeStyleGetPadding(view.yoga.node, YGEdgeLeft).unit, YGUnitPixel);
  XCTAssertEqual(view.yoga.paddingLeft, 4);

  view.yoga.paddingRight = 5;
  XCTAssertEqual(YGNodeStyleGetPadding(view.yoga.node, YGEdgeRight).value, 5);
  XCTAssertEqual(YGNodeStyleGetPadding(view.yoga.node, YGEdgeRight).unit, YGUnitPixel);
  XCTAssertEqual(view.yoga.paddingRight, 5);

  view.yoga.paddingTop = 6;
  XCTAssertEqual(YGNodeStyleGetPadding(view.yoga.node, YGEdgeTop).value, 6);
  XCTAssertEqual(YGNodeStyleGetPadding(view.yoga.node, YGEdgeTop).unit, YGUnitPixel);
  XCTAssertEqual(view.yoga.paddingTop, 6);

  view.yoga.paddingBottom = 7;
  XCTAssertEqual(YGNodeStyleGetPadding(view.yoga.node, YGEdgeBottom).value, 7);
  XCTAssertEqual(YGNodeStyleGetPadding(view.yoga.node, YGEdgeBottom).unit, YGUnitPixel);
  XCTAssertEqual(view.yoga.paddingBottom, 7);

  view.yoga.paddingStart = 8;
  XCTAssertEqual(YGNodeStyleGetPadding(view.yoga.node, YGEdgeStart).value, 8);
  XCTAssertEqual(YGNodeStyleGetPadding(view.yoga.node, YGEdgeStart).unit, YGUnitPixel);
  XCTAssertEqual(view.yoga.paddingStart, 8);

  view.yoga.paddingEnd = 9;
  XCTAssertEqual(YGNodeStyleGetPadding(view.yoga.node, YGEdgeEnd).value, 9);
  XCTAssertEqual(YGNodeStyleGetPadding(view.yoga.node, YGEdgeEnd).unit, YGUnitPixel);
  XCTAssertEqual(view.yoga.paddingEnd, 9);
}

- (void)testBorderWidthPropertiesWork
{
  UIView *view = [[UIView alloc] initWithFrame:CGRectZero];

  view.yoga.borderWidth = 1;
  XCTAssertEqual(view.yoga.borderWidth, 1);
  XCTAssertTrue(isnan(view.yoga.borderLeftWidth));
  XCTAssertTrue(isnan(view.yoga.borderRightWidth));
  XCTAssertTrue(isnan(view.yoga.borderStartWidth));
  XCTAssertTrue(isnan(view.yoga.borderEndWidth));
  XCTAssertTrue(isnan(view.yoga.borderTopWidth));
  XCTAssertTrue(isnan(view.yoga.borderBottomWidth));

  view.yoga.borderLeftWidth = 2;
  XCTAssertEqual(view.yoga.borderLeftWidth, 2);

  view.yoga.borderRightWidth = 3;
  XCTAssertEqual(view.yoga.borderRightWidth, 3);

  view.yoga.borderTopWidth = 4;
  XCTAssertEqual(view.yoga.borderTopWidth, 4);

  view.yoga.borderBottomWidth = 5;
  XCTAssertEqual(view.yoga.borderBottomWidth, 5);

  view.yoga.borderStartWidth = 6;
  XCTAssertEqual(view.yoga.borderStartWidth, 6);

  view.yoga.borderEndWidth = 7;
  XCTAssertEqual(view.yoga.borderEndWidth, 7);
}

@end
