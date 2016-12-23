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

@interface YogaKitTests : XCTestCase
@end

@implementation YogaKitTests

#ifndef TRAVIS_CI

- (void)testNodesAreDeallocedWithSingleView
{
  XCTAssertEqual(0, YGNodeGetInstanceCount());

  UIView *view = [[UIView alloc] initWithFrame:CGRectZero];
  [view yg_setFlexBasis:1];
  XCTAssertEqual(1, YGNodeGetInstanceCount());
  view = nil;

  XCTAssertEqual(0, YGNodeGetInstanceCount());
}

- (void)testNodesAreDeallocedCascade
{
  XCTAssertEqual(0, YGNodeGetInstanceCount());

  UIView *view = [[UIView alloc] initWithFrame:CGRectZero];
  [view yg_setFlexBasis:1];

  for (int i=0; i<10; i++) {
    UIView *subview = [[UIView alloc] initWithFrame:CGRectZero];
    [subview yg_setFlexBasis:1];
    [view addSubview:subview];
  }
  XCTAssertEqual(11, YGNodeGetInstanceCount());
  view = nil;

  XCTAssertEqual(0, YGNodeGetInstanceCount());
}

#endif

- (void)testUsesYoga
{
  UIView *view = [[UIView alloc] initWithFrame:CGRectZero];
  XCTAssertFalse([view yg_usesYoga]);

  [view yg_setUsesYoga:YES];
  XCTAssertTrue([view yg_usesYoga]);

  [view yg_setUsesYoga:NO];
  XCTAssertFalse([view yg_usesYoga]);
}

- (void)testSizeThatFitsAsserts
{
  UIView *view = [[UIView alloc] initWithFrame:CGRectZero];
  dispatch_sync(dispatch_queue_create("com.facebook.Yoga.testing", DISPATCH_QUEUE_SERIAL), ^(void){
    XCTAssertThrows([view yg_intrinsicSize]);
  });
}

- (void)testSizeThatFitsSmoke
{
  UIView *container = [[UIView alloc] initWithFrame:CGRectZero];
  [container yg_setUsesYoga:YES];
  [container yg_setFlexDirection:YGFlexDirectionRow];
  [container yg_setAlignItems:YGAlignFlexStart];

  UILabel *longTextLabel = [[UILabel alloc] initWithFrame:CGRectZero];
  longTextLabel.text = @"This is a very very very very very very very very long piece of text.";
  longTextLabel.lineBreakMode = NSLineBreakByTruncatingTail;
  longTextLabel.numberOfLines = 1;
  [longTextLabel yg_setUsesYoga:YES];
  [longTextLabel yg_setFlexShrink:1];
  [container addSubview:longTextLabel];

  UIView *textBadgeView = [[UIView alloc] initWithFrame:CGRectZero];
  [textBadgeView yg_setUsesYoga:YES];
  [textBadgeView yg_setMargin:3.0 forEdge:YGEdgeLeft];
  [textBadgeView yg_setWidth:10];
  [textBadgeView yg_setHeight:10];
  [container addSubview:textBadgeView];

  const CGSize containerSize = [container yg_intrinsicSize];
  XCTAssertTrue(CGSizeEqualToSize(CGSizeMake(514,21), containerSize), @"Size is actually %@", NSStringFromCGSize(containerSize));
}

- (void)testFrameAndOriginPlacement
{
  const CGSize containerSize = CGSizeMake(320, 50);

  UIView *container = [[UIView alloc] initWithFrame:CGRectMake(0, 0, containerSize.width, containerSize.height)];
  [container yg_setUsesYoga:YES];
  [container yg_setFlexDirection:YGFlexDirectionRow];

  for (int i = 0; i < 3; i++) {
    UIView *subview = [[UIView alloc] initWithFrame:CGRectZero];
    [subview yg_setUsesYoga:YES];
    [subview yg_setFlexGrow:1];

    [container addSubview:subview];
  }
  [container yg_applyLayout];

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
  [container yg_setUsesYoga:YES];
  [container yg_setFlexDirection:YGFlexDirectionRow];

  UIView *subview1 = [[UIView alloc] initWithFrame:CGRectZero];
  [subview1 yg_setUsesYoga:YES];
  [subview1 yg_setFlexGrow:1];
  [container addSubview:subview1];

  UIView *subview2 = [[UIView alloc] initWithFrame:CGRectZero];
  [subview2 yg_setUsesYoga:YES];
  [subview2 yg_setFlexGrow:1];
  [container addSubview:subview2];

  UIView *subview3 = [[UIView alloc] initWithFrame:CGRectZero];
  [subview3 yg_setUsesYoga:YES];
  [subview3 yg_setFlexGrow:1];
  [container addSubview:subview3];

  [container yg_applyLayout];

  XCTAssertTrue(CGRectEqualToRect(subview1.frame, CGRectMake(0, 0, 100, 50)));
  XCTAssertTrue(CGRectEqualToRect(subview2.frame, CGRectMake(100, 0, 100, 50)), @"It's actually %@", NSStringFromCGRect(subview2.frame));
  XCTAssertTrue(CGRectEqualToRect(subview3.frame, CGRectMake(200, 0, 100, 50)));

  [container exchangeSubviewAtIndex:2 withSubviewAtIndex:0];
  [subview2 yg_setIncludeInLayout:NO];
  [container yg_applyLayout];

  XCTAssertTrue(CGRectEqualToRect(subview3.frame, CGRectMake(0, 0, 150, 50)));
  XCTAssertTrue(CGRectEqualToRect(subview1.frame, CGRectMake(150, 0, 150, 50)));

  // this frame shouldn't have been modified since last time.
  XCTAssertTrue(CGRectEqualToRect(subview2.frame, CGRectMake(100, 0, 100, 50)));
}

- (void)testThatWeRespectIncludeInLayoutFlag
{
  const CGSize containerSize = CGSizeMake(300, 50);

  UIView *container = [[UIView alloc] initWithFrame:CGRectMake(0, 0, containerSize.width, containerSize.height)];
  [container yg_setUsesYoga:YES];
  [container yg_setFlexDirection:YGFlexDirectionRow];

  UIView *subview1 = [[UIView alloc] initWithFrame:CGRectZero];
  [subview1 yg_setUsesYoga:YES];
  [subview1 yg_setFlexGrow:1];
  [container addSubview:subview1];

  UIView *subview2 = [[UIView alloc] initWithFrame:CGRectZero];
  [subview2 yg_setUsesYoga:YES];
  [subview2 yg_setFlexGrow:1];
  [container addSubview:subview2];

  UIView *subview3 = [[UIView alloc] initWithFrame:CGRectZero];
  [subview3 yg_setUsesYoga:YES];
  [subview3 yg_setFlexGrow:1];
  [container addSubview:subview3];

  [container yg_applyLayout];

  for (UIView *view in container.subviews) {
    XCTAssertTrue(CGSizeEqualToSize(CGSizeMake(100, 50), subview1.bounds.size), @"Actual size is %@", NSStringFromCGSize(view.bounds.size));
  }

  [subview3 yg_setIncludeInLayout:NO];
  [container yg_applyLayout];

  XCTAssertTrue(CGSizeEqualToSize(CGSizeMake(150, 50), subview1.bounds.size), @"Actual size is %@", NSStringFromCGSize(subview1.bounds.size));
  XCTAssertTrue(CGSizeEqualToSize(CGSizeMake(150, 50), subview2.bounds.size), @"Actual size is %@", NSStringFromCGSize(subview2.bounds.size));

  // We don't set the frame to zero, so, it should be set to what it was previously at.
  XCTAssertTrue(CGSizeEqualToSize(CGSizeMake(100, 50), subview3.bounds.size), @"Actual size is %@", NSStringFromCGSize(subview3.bounds.size));
}

- (void)testThatNumberOfChildrenIsCorrectWhenWeIgnoreSubviews
{
  UIView *container = [[UIView alloc] initWithFrame:CGRectZero];
  [container yg_setUsesYoga:YES];
  [container yg_setFlexDirection:YGFlexDirectionRow];

  UIView *subview1 = [[UIView alloc] initWithFrame:CGRectZero];
  [subview1 yg_setUsesYoga:YES];
  [subview1 yg_setIncludeInLayout:NO];
  [container addSubview:subview1];

  UIView *subview2 = [[UIView alloc] initWithFrame:CGRectZero];
  [subview2 yg_setUsesYoga:YES];
  [subview2 yg_setIncludeInLayout:NO];
  [container addSubview:subview2];

  UIView *subview3 = [[UIView alloc] initWithFrame:CGRectZero];
  [subview3 yg_setUsesYoga:YES];
  [subview3 yg_setIncludeInLayout:YES];
  [container addSubview:subview3];

  [container yg_applyLayout];
  XCTAssertEqual(1, [container yg_numberOfChildren]);

  [subview2 yg_setIncludeInLayout:YES];
  [container yg_applyLayout];
  XCTAssertEqual(2, [container yg_numberOfChildren]);
}

- (void)testThatViewNotIncludedInFirstLayoutPassAreIncludedInSecond
{
  UIView *container = [[UIView alloc] initWithFrame:CGRectMake(0, 0, 300, 50)];
  [container yg_setUsesYoga:YES];
  [container yg_setFlexDirection:YGFlexDirectionRow];

  UIView *subview1 = [[UIView alloc] initWithFrame:CGRectZero];
  [subview1 yg_setUsesYoga:YES];
  [subview1 yg_setFlexGrow:1];
  [container addSubview:subview1];

  UIView *subview2 = [[UIView alloc] initWithFrame:CGRectZero];
  [subview2 yg_setUsesYoga:YES];
  [subview2 yg_setFlexGrow:1];
  [container addSubview:subview2];

  UIView *subview3 = [[UIView alloc] initWithFrame:CGRectZero];
  [subview3 yg_setUsesYoga:YES];
  [subview3 yg_setFlexGrow:1];
  [subview3 yg_setIncludeInLayout:NO];
  [container addSubview:subview3];

  [container yg_applyLayout];

  XCTAssertTrue(CGSizeEqualToSize(CGSizeMake(150, 50), subview1.bounds.size), @"Actual size is %@", NSStringFromCGSize(subview1.bounds.size));
  XCTAssertTrue(CGSizeEqualToSize(CGSizeMake(150, 50), subview2.bounds.size), @"Actual size is %@", NSStringFromCGSize(subview2.bounds.size));
  XCTAssertTrue(CGSizeEqualToSize(CGSizeZero, subview3.bounds.size), @"Actual size %@", NSStringFromCGSize(subview3.bounds.size));

  [subview3 yg_setIncludeInLayout:YES];
  [container yg_applyLayout];
  for (UIView *view in container.subviews) {
    XCTAssertTrue(CGSizeEqualToSize(CGSizeMake(100, 50), subview1.bounds.size), @"Actual size is %@", NSStringFromCGSize(view.bounds.size));
  }
}

- (void)testyg_isLeafFlag
{
  UIView *view = [[UIView alloc] initWithFrame:CGRectZero];
  XCTAssertTrue(view.yg_isLeaf);

  for (int i=0; i<10; i++) {
    UIView *subview = [[UIView alloc] initWithFrame:CGRectZero];
    [view addSubview:subview];
  }
  XCTAssertTrue(view.yg_isLeaf);

  [view yg_setUsesYoga:YES];
  [view yg_setWidth:50.0];
  XCTAssertTrue(view.yg_isLeaf);

  UIView *const subview = view.subviews[0];
  [subview yg_setUsesYoga:YES];
  [subview yg_setWidth:50.0];
  XCTAssertFalse(view.yg_isLeaf);
}

- (void)testThatWeCorrectlyAttachNestedViews
{
    UIView *container = [[UIView alloc] initWithFrame:CGRectMake(0, 0, 300, 50)];
    [container yg_setUsesYoga:YES];
    [container yg_setFlexDirection:YGFlexDirectionColumn];

    UIView *subview1 = [[UIView alloc] initWithFrame:CGRectZero];
    [subview1 yg_setUsesYoga:YES];
    [subview1 yg_setWidth:100];
    [subview1 yg_setFlexGrow:1];
    [subview1 yg_setFlexDirection:YGFlexDirectionColumn];
    [container addSubview:subview1];

    UIView *subview2 = [[UIView alloc] initWithFrame:CGRectZero];
    [subview2 yg_setUsesYoga:YES];
    [subview2 yg_setWidth:150];
    [subview2 yg_setFlexGrow:1];
    [subview2 yg_setFlexDirection:YGFlexDirectionColumn];
    [container addSubview:subview2];

    for (UIView *view in @[subview1, subview2]) {
        UIView *someView = [[UIView alloc] initWithFrame:CGRectZero];
        [someView yg_setUsesYoga:YES];
        [someView yg_setFlexGrow:1];
        [view addSubview:someView];
    }
    [container yg_applyLayout];

    // Add the same amount of new views, reapply layout.
    for (UIView *view in @[subview1, subview2]) {
        UIView *someView = [[UIView alloc] initWithFrame:CGRectZero];
        [someView yg_setUsesYoga:YES];
        [someView yg_setFlexGrow:1];
        [view addSubview:someView];
    }
    [container yg_applyLayout];

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

@end
