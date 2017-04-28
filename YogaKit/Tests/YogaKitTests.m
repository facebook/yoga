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

- (void)testConfigureLayoutIsNoOpWithNilBlock
{
  UIView *view = [[UIView alloc] initWithFrame:CGRectZero];
  id block = nil;
  XCTAssertNoThrow([view configureLayoutWithBlock:block]);
}

- (void)testConfigureLayoutBlockWorksWithValidBlock
{
  UIView *view = [[UIView alloc] initWithFrame:CGRectZero];
  [view configureLayoutWithBlock:^(YGLayout *layout){
    XCTAssertNotNil(layout);
    layout.isEnabled = YES;
    layout.width = YGPoint(25);
  }];

  XCTAssertTrue(view.yoga.isEnabled);
  XCTAssertEqual(view.yoga.width.value, 25);
}

- (void)testNodesAreDeallocedWithSingleView
{
  __weak YGLayout *layoutRef = nil;

  @autoreleasepool {
    UIView *view = [[UIView alloc] initWithFrame:CGRectZero];
    view.yoga.flexBasis = YGPoint(1);

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
    topLayout.flexBasis = YGPoint(1);

    UIView *subview = [[UIView alloc] initWithFrame:CGRectZero];
    subviewLayout = subview.yoga;
    subviewLayout.flexBasis = YGPoint(1);

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
  textBadgeView.yoga.margin = YGPoint(0);
  textBadgeView.yoga.width = YGPoint(10);
  textBadgeView.yoga.height = YGPoint(10);
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
  view.yoga.flexBasis = YGPoint(0);
  view.yoga.flexGrow = 1;
  [container addSubview:view];

  UIView *view2 = [[UIView alloc] initWithFrame:CGRectZero];
  view2.yoga.isEnabled = YES;
  view2.yoga.marginTop = YGPoint(25);
  view2.yoga.flexBasis = YGPoint(0);
  view2.yoga.flexGrow = 1;
  [container addSubview:view2];

  [container.yoga applyLayoutPreservingOrigin:YES];
  XCTAssertEqual(50, view2.frame.origin.y);

  [view2.yoga applyLayoutPreservingOrigin:NO];
  XCTAssertEqual(25, view2.frame.origin.y);
}

- (void)testContainerWithFlexibleWidthGetsCorrectlySized
{
  UIView *container = [[UIView alloc] initWithFrame:CGRectMake(0,0,200,200)];
  container.yoga.isEnabled = YES;

  UIView *view = [[UIView alloc] initWithFrame:CGRectMake(0, 0, 100, 100)];
  view.yoga.isEnabled = YES;
  view.yoga.width = 100;
  view.yoga.height = 100;
  [container addSubview:view];

  [container.yoga applyLayoutPreservingOrigin:YES dimensionFlexibility:YGDimensionFlexibilityFlexibleWidth];
  XCTAssertEqual(100, container.frame.size.width);
  XCTAssertEqual(200, container.frame.size.height);
}

- (void)testContainerWithFlexibleHeightGetsCorrectlySized
{
  UIView *container = [[UIView alloc] initWithFrame:CGRectMake(0,0,200,200)];
  container.yoga.isEnabled = YES;

  UIView *view = [[UIView alloc] initWithFrame:CGRectMake(0, 0, 100, 100)];
  view.yoga.isEnabled = YES;
  view.yoga.width = 100;
  view.yoga.height = 100;
  [container addSubview:view];

  [container.yoga applyLayoutPreservingOrigin:YES dimensionFlexibility:YGDimensionFlexibilityFlexibleHeigth];
  XCTAssertEqual(200, container.frame.size.width);
  XCTAssertEqual(100, container.frame.size.height);
}

- (void)testContainerWithFlexibleWidthAndHeightGetsCorrectlySized
{
  UIView *container = [[UIView alloc] initWithFrame:CGRectMake(0,0,200,200)];
  container.yoga.isEnabled = YES;

  UIView *view = [[UIView alloc] initWithFrame:CGRectMake(0, 0, 100, 100)];
  view.yoga.isEnabled = YES;
  view.yoga.width = 100;
  view.yoga.height = 100;
  [container addSubview:view];

  [container.yoga applyLayoutPreservingOrigin:YES dimensionFlexibility:YGDimensionFlexibilityFlexibleWidth | YGDimensionFlexibilityFlexibleHeigth];
  XCTAssertEqual(100, container.frame.size.width);
  XCTAssertEqual(100, container.frame.size.height);
}

- (void)testMarkingDirtyOnlyWorksOnLeafNodes
{
  UIView *container = [[UIView alloc] initWithFrame:CGRectZero];
  container.yoga.isEnabled = YES;

  UIView *subview = [[UIView alloc] initWithFrame:CGRectZero];
  subview.yoga.isEnabled = YES;
  [container addSubview:subview];

  XCTAssertFalse(container.yoga.isDirty);
  [container.yoga markDirty];
  XCTAssertFalse(container.yoga.isDirty);

  XCTAssertFalse(subview.yoga.isDirty);
  [subview.yoga markDirty];
  XCTAssertTrue(subview.yoga.isDirty);
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
  view.yoga.width = YGPoint(50);
  XCTAssertTrue(view.yoga.isLeaf);

  UIView *const subview = view.subviews[0];
  subview.yoga.isEnabled = YES;
  subview.yoga.width = YGPoint(50);
  XCTAssertFalse(view.yoga.isLeaf);
}

- (void)testThatWeCorrectlyAttachNestedViews
{
    UIView *container = [[UIView alloc] initWithFrame:CGRectMake(0, 0, 300, 50)];
    container.yoga.isEnabled = YES;
    container.yoga.flexDirection = YGFlexDirectionColumn;

    UIView *subview1 = [[UIView alloc] initWithFrame:CGRectZero];
    subview1.yoga.isEnabled = YES;
    subview1.yoga.width = YGPoint(100);
    subview1.yoga.flexGrow = 1;
    subview1.yoga.flexDirection = YGFlexDirectionColumn;
    [container addSubview:subview1];

    UIView *subview2 = [[UIView alloc] initWithFrame:CGRectZero];
    subview2.yoga.isEnabled = YES;
    subview2.yoga.width = YGPoint(150);
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

- (void)testPointPercent
{
  XCTAssertEqual(YGPoint(1).value, 1);
  XCTAssertEqual(YGPoint(1).unit, YGUnitPoint);
  XCTAssertEqual(YGPercent(2).value, 2);
  XCTAssertEqual(YGPercent(2).unit, YGUnitPercent);
}

- (void)testPositionalPropertiesWork
{
  UIView *view = [[UIView alloc] initWithFrame:CGRectZero];

  view.yoga.left = YGPoint(1);
  XCTAssertEqual(view.yoga.left.value, 1);
  XCTAssertEqual(view.yoga.left.unit, YGUnitPoint);
  view.yoga.left = YGPercent(2);
  XCTAssertEqual(view.yoga.left.value, 2);
  XCTAssertEqual(view.yoga.left.unit, YGUnitPercent);

  view.yoga.right = YGPoint(3);
  XCTAssertEqual(view.yoga.right.value, 3);
  XCTAssertEqual(view.yoga.right.unit, YGUnitPoint);
  view.yoga.right = YGPercent(4);
  XCTAssertEqual(view.yoga.right.value, 4);
  XCTAssertEqual(view.yoga.right.unit, YGUnitPercent);

  view.yoga.top = YGPoint(5);
  XCTAssertEqual(view.yoga.top.value, 5);
  XCTAssertEqual(view.yoga.top.unit, YGUnitPoint);
  view.yoga.top = YGPercent(6);
  XCTAssertEqual(view.yoga.top.value, 6);
  XCTAssertEqual(view.yoga.top.unit, YGUnitPercent);

  view.yoga.bottom = YGPoint(7);
  XCTAssertEqual(view.yoga.bottom.value, 7);
  XCTAssertEqual(view.yoga.bottom.unit, YGUnitPoint);
  view.yoga.bottom = YGPercent(8);
  XCTAssertEqual(view.yoga.bottom.value, 8);
  XCTAssertEqual(view.yoga.bottom.unit, YGUnitPercent);

  view.yoga.start = YGPoint(9);
  XCTAssertEqual(view.yoga.start.value, 9);
  XCTAssertEqual(view.yoga.start.unit, YGUnitPoint);
  view.yoga.start = YGPercent(10);
  XCTAssertEqual(view.yoga.start.value, 10);
  XCTAssertEqual(view.yoga.start.unit, YGUnitPercent);

  view.yoga.end = YGPoint(11);
  XCTAssertEqual(view.yoga.end.value, 11);
  XCTAssertEqual(view.yoga.end.unit, YGUnitPoint);
  view.yoga.end = YGPercent(12);
  XCTAssertEqual(view.yoga.end.value, 12);
  XCTAssertEqual(view.yoga.end.unit, YGUnitPercent);
}

- (void)testMarginPropertiesWork
{
  UIView *view = [[UIView alloc] initWithFrame:CGRectZero];

  view.yoga.margin = YGPoint(1);
  XCTAssertEqual(view.yoga.margin.value, 1);
  XCTAssertEqual(view.yoga.margin.unit, YGUnitPoint);
  view.yoga.margin = YGPercent(2);
  XCTAssertEqual(view.yoga.margin.value, 2);
  XCTAssertEqual(view.yoga.margin.unit, YGUnitPercent);

  view.yoga.marginHorizontal = YGPoint(3);
  XCTAssertEqual(view.yoga.marginHorizontal.value, 3);
  XCTAssertEqual(view.yoga.marginHorizontal.unit, YGUnitPoint);
  view.yoga.marginHorizontal = YGPercent(4);
  XCTAssertEqual(view.yoga.marginHorizontal.value, 4);
  XCTAssertEqual(view.yoga.marginHorizontal.unit, YGUnitPercent);

  view.yoga.marginVertical = YGPoint(5);
  XCTAssertEqual(view.yoga.marginVertical.value, 5);
  XCTAssertEqual(view.yoga.marginVertical.unit, YGUnitPoint);
  view.yoga.marginVertical = YGPercent(6);
  XCTAssertEqual(view.yoga.marginVertical.value, 6);
  XCTAssertEqual(view.yoga.marginVertical.unit, YGUnitPercent);

  view.yoga.marginLeft = YGPoint(7);
  XCTAssertEqual(view.yoga.marginLeft.value, 7);
  XCTAssertEqual(view.yoga.marginLeft.unit, YGUnitPoint);
  view.yoga.marginLeft = YGPercent(8);
  XCTAssertEqual(view.yoga.marginLeft.value, 8);
  XCTAssertEqual(view.yoga.marginLeft.unit, YGUnitPercent);

  view.yoga.marginRight = YGPoint(9);
  XCTAssertEqual(view.yoga.marginRight.value, 9);
  XCTAssertEqual(view.yoga.marginRight.unit, YGUnitPoint);
  view.yoga.marginRight = YGPercent(10);
  XCTAssertEqual(view.yoga.marginRight.value, 10);
  XCTAssertEqual(view.yoga.marginRight.unit, YGUnitPercent);

  view.yoga.marginTop = YGPoint(11);
  XCTAssertEqual(view.yoga.marginTop.value, 11);
  XCTAssertEqual(view.yoga.marginTop.unit, YGUnitPoint);
  view.yoga.marginTop = YGPercent(12);
  XCTAssertEqual(view.yoga.marginTop.value, 12);
  XCTAssertEqual(view.yoga.marginTop.unit, YGUnitPercent);

  view.yoga.marginBottom = YGPoint(13);
  XCTAssertEqual(view.yoga.marginBottom.value, 13);
  XCTAssertEqual(view.yoga.marginBottom.unit, YGUnitPoint);
  view.yoga.marginBottom = YGPercent(14);
  XCTAssertEqual(view.yoga.marginBottom.value, 14);
  XCTAssertEqual(view.yoga.marginBottom.unit, YGUnitPercent);

  view.yoga.marginStart = YGPoint(15);
  XCTAssertEqual(view.yoga.marginStart.value, 15);
  XCTAssertEqual(view.yoga.marginStart.unit, YGUnitPoint);
  view.yoga.marginStart = YGPercent(16);
  XCTAssertEqual(view.yoga.marginStart.value, 16);
  XCTAssertEqual(view.yoga.marginStart.unit, YGUnitPercent);

  view.yoga.marginEnd = YGPoint(17);
  XCTAssertEqual(view.yoga.marginEnd.value, 17);
  XCTAssertEqual(view.yoga.marginEnd.unit, YGUnitPoint);
  view.yoga.marginEnd = YGPercent(18);
  XCTAssertEqual(view.yoga.marginEnd.value, 18);
  XCTAssertEqual(view.yoga.marginEnd.unit, YGUnitPercent);
}

- (void)testPaddingPropertiesWork
{
  UIView *view = [[UIView alloc] initWithFrame:CGRectZero];

  view.yoga.padding = YGPoint(1);
  XCTAssertEqual(view.yoga.padding.value, 1);
  XCTAssertEqual(view.yoga.padding.unit, YGUnitPoint);
  view.yoga.padding = YGPercent(2);
  XCTAssertEqual(view.yoga.padding.value, 2);
  XCTAssertEqual(view.yoga.padding.unit, YGUnitPercent);

  view.yoga.paddingHorizontal = YGPoint(3);
  XCTAssertEqual(view.yoga.paddingHorizontal.value, 3);
  XCTAssertEqual(view.yoga.paddingHorizontal.unit, YGUnitPoint);
  view.yoga.paddingHorizontal = YGPercent(4);
  XCTAssertEqual(view.yoga.paddingHorizontal.value, 4);
  XCTAssertEqual(view.yoga.paddingHorizontal.unit, YGUnitPercent);

  view.yoga.paddingVertical = YGPoint(5);
  XCTAssertEqual(view.yoga.paddingVertical.value, 5);
  XCTAssertEqual(view.yoga.paddingVertical.unit, YGUnitPoint);
  view.yoga.paddingVertical = YGPercent(6);
  XCTAssertEqual(view.yoga.paddingVertical.value, 6);
  XCTAssertEqual(view.yoga.paddingVertical.unit, YGUnitPercent);

  view.yoga.paddingLeft = YGPoint(7);
  XCTAssertEqual(view.yoga.paddingLeft.value, 7);
  XCTAssertEqual(view.yoga.paddingLeft.unit, YGUnitPoint);
  view.yoga.paddingLeft = YGPercent(8);
  XCTAssertEqual(view.yoga.paddingLeft.value, 8);
  XCTAssertEqual(view.yoga.paddingLeft.unit, YGUnitPercent);

  view.yoga.paddingRight = YGPoint(9);
  XCTAssertEqual(view.yoga.paddingRight.value, 9);
  XCTAssertEqual(view.yoga.paddingRight.unit, YGUnitPoint);
  view.yoga.paddingRight = YGPercent(10);
  XCTAssertEqual(view.yoga.paddingRight.value, 10);
  XCTAssertEqual(view.yoga.paddingRight.unit, YGUnitPercent);

  view.yoga.paddingTop = YGPoint(11);
  XCTAssertEqual(view.yoga.paddingTop.value, 11);
  XCTAssertEqual(view.yoga.paddingTop.unit, YGUnitPoint);
  view.yoga.paddingTop = YGPercent(12);
  XCTAssertEqual(view.yoga.paddingTop.value, 12);
  XCTAssertEqual(view.yoga.paddingTop.unit, YGUnitPercent);

  view.yoga.paddingBottom = YGPoint(13);
  XCTAssertEqual(view.yoga.paddingBottom.value, 13);
  XCTAssertEqual(view.yoga.paddingBottom.unit, YGUnitPoint);
  view.yoga.paddingBottom = YGPercent(14);
  XCTAssertEqual(view.yoga.paddingBottom.value, 14);
  XCTAssertEqual(view.yoga.paddingBottom.unit, YGUnitPercent);

  view.yoga.paddingStart = YGPoint(15);
  XCTAssertEqual(view.yoga.paddingStart.value, 15);
  XCTAssertEqual(view.yoga.paddingStart.unit, YGUnitPoint);
  view.yoga.paddingStart = YGPercent(16);
  XCTAssertEqual(view.yoga.paddingStart.value, 16);
  XCTAssertEqual(view.yoga.paddingStart.unit, YGUnitPercent);

  view.yoga.paddingEnd = YGPoint(17);
  XCTAssertEqual(view.yoga.paddingEnd.value, 17);
  XCTAssertEqual(view.yoga.paddingEnd.unit, YGUnitPoint);
  view.yoga.paddingEnd = YGPercent(18);
  XCTAssertEqual(view.yoga.paddingEnd.value, 18);
  XCTAssertEqual(view.yoga.paddingEnd.unit, YGUnitPercent);
}

- (void)testBorderWidthPropertiesWork
{
  UIView *view = [[UIView alloc] initWithFrame:CGRectZero];

  view.yoga.borderWidth = 1;
  XCTAssertEqual(view.yoga.borderWidth, 1);

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
