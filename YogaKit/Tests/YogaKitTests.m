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

#ifndef TRAVIS_CI

- (void)testNodesAreDeallocedWithSingleView
{
  XCTAssertEqual(0, YGNodeGetInstanceCount());

  UIView *view = [[UIView alloc] initWithFrame:CGRectZero];
  view.yoga.flexBasis = 1;
  XCTAssertEqual(1, YGNodeGetInstanceCount());
  view = nil;

  XCTAssertEqual(0, YGNodeGetInstanceCount());
}

- (void)testNodesAreDeallocedCascade
{
  XCTAssertEqual(0, YGNodeGetInstanceCount());

  UIView *view = [[UIView alloc] initWithFrame:CGRectZero];
  view.yoga.flexBasis = 1;

  for (int i=0; i<10; i++) {
    UIView *subview = [[UIView alloc] initWithFrame:CGRectZero];
    subview.yoga.flexBasis = 1;
    [view addSubview:subview];
  }
  XCTAssertEqual(11, YGNodeGetInstanceCount());
  view = nil;

  XCTAssertEqual(0, YGNodeGetInstanceCount());
}

#endif

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
  textBadgeView.yoga.marginLeft = 3.0;
  textBadgeView.yoga.width = 10;
  textBadgeView.yoga.height = 10;
  [container addSubview:textBadgeView];

  const CGSize containerSize = container.yoga.intrinsicSize;
  XCTAssertTrue(CGSizeEqualToSize(CGSizeMake(514,21), containerSize), @"Size is actually %@", NSStringFromCGSize(containerSize));
}

- (void)testThatMarkingLeafsAsDirtyWillTriggerASizeRecalculation
{
  UIView *container = [[UIView alloc] initWithFrame:CGRectMake(0, 0, 500, 50)];
  container.yoga.isEnabled = YES;
  container.yoga.flexDirection = YGFlexDirectionRow;
  container.yoga.alignItems = YGAlignFlexStart;

  UILabel *label = [[UILabel alloc] initWithFrame:CGRectZero];
  label.text = @"This is a short text.";
  label.numberOfLines = 1;
  label.yoga.isEnabled = YES;
  [container addSubview:label];

  [container.yoga applyLayout];
  XCTAssertTrue(CGSizeEqualToSize(CGSizeMake(146,21), label.bounds.size), @"Size is actually %@", NSStringFromCGSize(label.bounds.size));

  label.text = @"This is a slightly longer text.";
  [label.yoga markDirty];

  [container.yoga applyLayout];
  XCTAssertTrue(CGSizeEqualToSize(CGSizeMake(213,21), label.bounds.size), @"Size is actually %@", NSStringFromCGSize(label.bounds.size));
}

- (void)testFrameAndOriginPlacement
{
  const CGSize containerSize = CGSizeMake(320, 50);

  UIView *container = [[UIView alloc] initWithFrame:CGRectMake(0, 0, containerSize.width, containerSize.height)];
  container.yoga.isEnabled = YES;
  container.yoga.flexDirection = YGFlexDirectionRow;

  for (int i = 0; i < 3; i++) {
    UIView *subview = [[UIView alloc] initWithFrame:CGRectZero];
    subview.yoga.isEnabled = YES;
    subview.yoga.flexGrow = 1;

    [container addSubview:subview];
  }
  [container.yoga applyLayout];

  XCTAssertFalse(CGRectIntersectsRect([container.subviews objectAtIndex:0].frame, [container.subviews objectAtIndex:1].frame));
  XCTAssertFalse(CGRectIntersectsRect([container.subviews objectAtIndex:1].frame, [container.subviews objectAtIndex:2].frame));
  XCTAssertFalse(CGRectIntersectsRect([container.subviews objectAtIndex:0].frame, [container.subviews objectAtIndex:2].frame));

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

  [container.yoga applyLayout];

  XCTAssertTrue(CGRectEqualToRect(subview1.frame, CGRectMake(0, 0, 100, 50)));
  XCTAssertTrue(CGRectEqualToRect(subview2.frame, CGRectMake(100, 0, 100, 50)), @"It's actually %@", NSStringFromCGRect(subview2.frame));
  XCTAssertTrue(CGRectEqualToRect(subview3.frame, CGRectMake(200, 0, 100, 50)));

  [container exchangeSubviewAtIndex:2 withSubviewAtIndex:0];
  subview2.yoga.isIncludedInLayout = NO;
  [container.yoga applyLayout];

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

  [container.yoga applyLayout];

  for (UIView *view in container.subviews) {
    XCTAssertTrue(CGSizeEqualToSize(CGSizeMake(100, 50), view.bounds.size), @"Actual size is %@", NSStringFromCGSize(view.bounds.size));
  }

  subview3.yoga.isIncludedInLayout = NO;
  [container.yoga applyLayout];

  XCTAssertTrue(CGSizeEqualToSize(CGSizeMake(150, 50), subview1.bounds.size), @"Actual size is %@", NSStringFromCGSize(subview1.bounds.size));
  XCTAssertTrue(CGSizeEqualToSize(CGSizeMake(150, 50), subview2.bounds.size), @"Actual size is %@", NSStringFromCGSize(subview2.bounds.size));

  // We don't set the frame to zero, so, it should be set to what it was previously at.
  XCTAssertTrue(CGSizeEqualToSize(CGSizeMake(100, 50), subview3.bounds.size), @"Actual size is %@", NSStringFromCGSize(subview3.bounds.size));
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

  [container.yoga applyLayout];
  XCTAssertEqual(1, container.yoga.numberOfChildren);

  subview2.yoga.isIncludedInLayout = YES;
  [container.yoga applyLayout];
  XCTAssertEqual(2, container.yoga.numberOfChildren);
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

  [container.yoga applyLayout];

  XCTAssertTrue(CGSizeEqualToSize(CGSizeMake(150, 50), subview1.bounds.size), @"Actual size is %@", NSStringFromCGSize(subview1.bounds.size));
  XCTAssertTrue(CGSizeEqualToSize(CGSizeMake(150, 50), subview2.bounds.size), @"Actual size is %@", NSStringFromCGSize(subview2.bounds.size));
  XCTAssertTrue(CGSizeEqualToSize(CGSizeZero, subview3.bounds.size), @"Actual size %@", NSStringFromCGSize(subview3.bounds.size));

  subview3.yoga.isIncludedInLayout = YES;
  [container.yoga applyLayout];
  for (UIView *view in container.subviews) {
    XCTAssertTrue(CGSizeEqualToSize(CGSizeMake(100, 50), view.bounds.size), @"Actual size is %@", NSStringFromCGSize(view.bounds.size));
  }
}

- (void)testyg_isLeafFlag
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
    [container.yoga applyLayout];

    // Add the same amount of new views, reapply layout.
    for (UIView *view in @[subview1, subview2]) {
        UIView *someView = [[UIView alloc] initWithFrame:CGRectZero];
        someView.yoga.isEnabled = YES;
        someView.yoga.flexGrow = 1;
        [view addSubview:someView];
    }
    [container.yoga applyLayout];

    XCTAssertTrue(CGSizeEqualToSize(CGSizeMake(100, 25), subview1.bounds.size), @"Actual size is %@", NSStringFromCGSize(subview1.bounds.size));
    for (UIView *subview in subview1.subviews) {
        const CGSize subviewSize = subview.bounds.size;
        XCTAssertFalse(CGSizeEqualToSize(CGSizeZero, subviewSize));
        XCTAssertFalse(isnan(subviewSize.height));
        XCTAssertFalse(isnan(subviewSize.width));
    }

    XCTAssertTrue(CGSizeEqualToSize(CGSizeMake(150, 25), subview2.bounds.size), @"Actual size is %@", NSStringFromCGSize(subview2.bounds.size));
    for (UIView *subview in subview2.subviews) {
        const CGSize subviewSize = subview.bounds.size;
        XCTAssertFalse(CGSizeEqualToSize(CGSizeZero, subview.bounds.size));
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

    [container.yoga applyLayout];
    [subview2 removeFromSuperview];
    [container.yoga applyLayout];
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
  XCTAssertEqual(view.yoga.marginLeft, 1);
  XCTAssertEqual(YGNodeStyleGetMargin(view.yoga.node, YGEdgeLeft).unit, YGUnitPixel);
  XCTAssertEqual(view.yoga.marginRight, 1);
  XCTAssertEqual(YGNodeStyleGetMargin(view.yoga.node, YGEdgeRight).unit, YGUnitPixel);
  XCTAssertEqual(view.yoga.marginStart, 1);
  XCTAssertEqual(YGNodeStyleGetMargin(view.yoga.node, YGEdgeStart).unit, YGUnitPixel);
  XCTAssertEqual(view.yoga.marginEnd, 1);
  XCTAssertEqual(YGNodeStyleGetMargin(view.yoga.node, YGEdgeEnd).unit, YGUnitPixel);
  XCTAssertEqual(view.yoga.marginTop, 1);
  XCTAssertEqual(YGNodeStyleGetMargin(view.yoga.node, YGEdgeTop).unit, YGUnitPixel);
  XCTAssertEqual(view.yoga.marginBottom, 1);
  XCTAssertEqual(YGNodeStyleGetMargin(view.yoga.node, YGEdgeBottom).unit, YGUnitPixel);
  XCTAssertTrue(isnan(view.yoga.marginHorizontal));
  XCTAssertTrue(isnan(view.yoga.marginVertical));
  XCTAssertTrue(isnan(view.yoga.margin));

  view.yoga.marginHorizontal = 2;
  XCTAssertEqual(view.yoga.marginLeft, 2);
  XCTAssertEqual(YGNodeStyleGetMargin(view.yoga.node, YGEdgeLeft).unit, YGUnitPixel);
  XCTAssertEqual(view.yoga.marginRight, 2);
  XCTAssertEqual(YGNodeStyleGetMargin(view.yoga.node, YGEdgeRight).unit, YGUnitPixel);
  XCTAssertEqual(view.yoga.marginStart, 2);
  XCTAssertEqual(YGNodeStyleGetMargin(view.yoga.node, YGEdgeStart).unit, YGUnitPixel);
  XCTAssertEqual(view.yoga.marginEnd, 2);
  XCTAssertEqual(YGNodeStyleGetMargin(view.yoga.node, YGEdgeEnd).unit, YGUnitPixel);
  XCTAssertTrue(isnan(view.yoga.marginHorizontal));

  view.yoga.marginVertical = 3;
  XCTAssertEqual(view.yoga.marginTop, 3);
  XCTAssertEqual(YGNodeStyleGetMargin(view.yoga.node, YGEdgeTop).unit, YGUnitPixel);
  XCTAssertEqual(view.yoga.marginBottom, 3);
  XCTAssertEqual(YGNodeStyleGetMargin(view.yoga.node, YGEdgeBottom).unit, YGUnitPixel);
  XCTAssertTrue(isnan(view.yoga.marginVertical));

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
  XCTAssertEqual(view.yoga.paddingLeft, 1);
  XCTAssertEqual(YGNodeStyleGetPadding(view.yoga.node, YGEdgeLeft).unit, YGUnitPixel);
  XCTAssertEqual(view.yoga.paddingRight, 1);
  XCTAssertEqual(YGNodeStyleGetPadding(view.yoga.node, YGEdgeRight).unit, YGUnitPixel);
  XCTAssertEqual(view.yoga.paddingStart, 1);
  XCTAssertEqual(YGNodeStyleGetPadding(view.yoga.node, YGEdgeStart).unit, YGUnitPixel);
  XCTAssertEqual(view.yoga.paddingEnd, 1);
  XCTAssertEqual(YGNodeStyleGetPadding(view.yoga.node, YGEdgeEnd).unit, YGUnitPixel);
  XCTAssertEqual(view.yoga.paddingTop, 1);
  XCTAssertEqual(YGNodeStyleGetPadding(view.yoga.node, YGEdgeTop).unit, YGUnitPixel);
  XCTAssertEqual(view.yoga.paddingBottom, 1);
  XCTAssertEqual(YGNodeStyleGetPadding(view.yoga.node, YGEdgeBottom).unit, YGUnitPixel);
  XCTAssertTrue(isnan(view.yoga.paddingHorizontal));
  XCTAssertTrue(isnan(view.yoga.paddingVertical));
  XCTAssertTrue(isnan(view.yoga.padding));

  view.yoga.paddingHorizontal = 2;
  XCTAssertEqual(view.yoga.paddingLeft, 2);
  XCTAssertEqual(YGNodeStyleGetPadding(view.yoga.node, YGEdgeLeft).unit, YGUnitPixel);
  XCTAssertEqual(view.yoga.paddingRight, 2);
  XCTAssertEqual(YGNodeStyleGetPadding(view.yoga.node, YGEdgeRight).unit, YGUnitPixel);
  XCTAssertEqual(view.yoga.paddingStart, 2);
  XCTAssertEqual(YGNodeStyleGetPadding(view.yoga.node, YGEdgeStart).unit, YGUnitPixel);
  XCTAssertEqual(view.yoga.paddingEnd, 2);
  XCTAssertEqual(YGNodeStyleGetPadding(view.yoga.node, YGEdgeEnd).unit, YGUnitPixel);
  XCTAssertTrue(isnan(view.yoga.paddingHorizontal));

  view.yoga.paddingVertical = 3;
  XCTAssertEqual(view.yoga.paddingTop, 3);
  XCTAssertEqual(YGNodeStyleGetPadding(view.yoga.node, YGEdgeTop).unit, YGUnitPixel);
  XCTAssertEqual(view.yoga.paddingBottom, 3);
  XCTAssertEqual(YGNodeStyleGetPadding(view.yoga.node, YGEdgeBottom).unit, YGUnitPixel);
  XCTAssertTrue(isnan(view.yoga.paddingVertical));

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
  XCTAssertEqual(view.yoga.borderLeftWidth, 1);
  XCTAssertEqual(view.yoga.borderRightWidth, 1);
  XCTAssertEqual(view.yoga.borderStartWidth, 1);
  XCTAssertEqual(view.yoga.borderEndWidth, 1);
  XCTAssertEqual(view.yoga.borderTopWidth, 1);
  XCTAssertEqual(view.yoga.borderBottomWidth, 1);
  XCTAssertTrue(isnan(view.yoga.borderWidth));

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
