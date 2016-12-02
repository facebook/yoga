/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#import <XCTest/XCTest.h>

#import "UIView+CSSLayout.h"

@interface CSSLayoutKitTests : XCTestCase
@end

@implementation CSSLayoutKitTests

#ifndef TRAVIS_CI

- (void)testNodesAreDeallocedWithSingleView
{
  XCTAssertEqual(0, CSSNodeGetInstanceCount());

  UIView *view = [[UIView alloc] initWithFrame:CGRectZero];
  [view css_setFlexBasis:1];
  XCTAssertEqual(1, CSSNodeGetInstanceCount());
  view = nil;

  XCTAssertEqual(0, CSSNodeGetInstanceCount());
}

- (void)testNodesAreDeallocedCascade
{
  XCTAssertEqual(0, CSSNodeGetInstanceCount());

  UIView *view = [[UIView alloc] initWithFrame:CGRectZero];
  [view css_setFlexBasis:1];

  for (int i=0; i<10; i++) {
    UIView *subview = [[UIView alloc] initWithFrame:CGRectZero];
    [subview css_setFlexBasis:1];
    [view addSubview:subview];
  }
  XCTAssertEqual(11, CSSNodeGetInstanceCount());
  view = nil;

  XCTAssertEqual(0, CSSNodeGetInstanceCount());
}

#endif

- (void)testUsesFlexbox
{
  UIView *view = [[UIView alloc] initWithFrame:CGRectZero];
  XCTAssertFalse([view css_usesFlexbox]);

  [view css_setUsesFlexbox:YES];
  XCTAssertTrue([view css_usesFlexbox]);

  [view css_setUsesFlexbox:NO];
  XCTAssertFalse([view css_usesFlexbox]);
}

- (void)testSizeThatFitsAsserts
{
  UIView *view = [[UIView alloc] initWithFrame:CGRectZero];
  dispatch_sync(dispatch_queue_create("com.facebook.CSSLayout.testing", DISPATCH_QUEUE_SERIAL), ^(void){
    XCTAssertThrows([view css_intrinsicSize]);
  });
}

- (void)testSizeThatFitsSmoke
{
  UIView *container = [[UIView alloc] initWithFrame:CGRectZero];
  [container css_setUsesFlexbox:YES];
  [container css_setFlexDirection:YGFlexDirectionRow];
  [container css_setAlignItems:YGAlignFlexStart];

  UILabel *longTextLabel = [[UILabel alloc] initWithFrame:CGRectZero];
  longTextLabel.text = @"This is a very very very very very very very very long piece of text.";
  longTextLabel.lineBreakMode = NSLineBreakByTruncatingTail;
  longTextLabel.numberOfLines = 1;
  [longTextLabel css_setUsesFlexbox:YES];
  [longTextLabel css_setFlexShrink:1];
  [container addSubview:longTextLabel];

  UIView *textBadgeView = [[UIView alloc] initWithFrame:CGRectZero];
  [textBadgeView css_setUsesFlexbox:YES];
  [textBadgeView css_setMargin:3.0 forEdge:YGEdgeLeft];
  [textBadgeView css_setWidth:10];
  [textBadgeView css_setHeight:10];
  [container addSubview:textBadgeView];

  const CGSize containerSize = [container css_intrinsicSize];
  XCTAssertTrue(CGSizeEqualToSize(CGSizeMake(514,21), containerSize), @"Size is actually %@", NSStringFromCGSize(containerSize));
}

- (void)testFrameAndOriginPlacement
{
  const CGSize containerSize = CGSizeMake(320, 50);

  UIView *container = [[UIView alloc] initWithFrame:CGRectMake(0, 0, containerSize.width, containerSize.height)];
  [container css_setUsesFlexbox:YES];
  [container css_setFlexDirection:YGFlexDirectionRow];

  for (int i = 0; i < 3; i++) {
    UIView *subview = [[UIView alloc] initWithFrame:CGRectZero];
    [subview css_setUsesFlexbox:YES];
    [subview css_setFlexGrow:1];

    [container addSubview:subview];
  }
  [container css_applyLayout];

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
  [container css_setUsesFlexbox:YES];
  [container css_setFlexDirection:YGFlexDirectionRow];

  UIView *subview1 = [[UIView alloc] initWithFrame:CGRectZero];
  [subview1 css_setUsesFlexbox:YES];
  [subview1 css_setFlexGrow:1];
  [container addSubview:subview1];

  UIView *subview2 = [[UIView alloc] initWithFrame:CGRectZero];
  [subview2 css_setUsesFlexbox:YES];
  [subview2 css_setFlexGrow:1];
  [container addSubview:subview2];

  UIView *subview3 = [[UIView alloc] initWithFrame:CGRectZero];
  [subview3 css_setUsesFlexbox:YES];
  [subview3 css_setFlexGrow:1];
  [container addSubview:subview3];

  [container css_applyLayout];

  XCTAssertTrue(CGRectEqualToRect(subview1.frame, CGRectMake(0, 0, 100, 50)));
  XCTAssertTrue(CGRectEqualToRect(subview2.frame, CGRectMake(100, 0, 100, 50)), @"It's actually %@", NSStringFromCGRect(subview2.frame));
  XCTAssertTrue(CGRectEqualToRect(subview3.frame, CGRectMake(200, 0, 100, 50)));

  [container exchangeSubviewAtIndex:2 withSubviewAtIndex:0];
  [subview2 css_setIncludeInLayout:NO];
  [container css_applyLayout];

  XCTAssertTrue(CGRectEqualToRect(subview3.frame, CGRectMake(0, 0, 150, 50)));
  XCTAssertTrue(CGRectEqualToRect(subview1.frame, CGRectMake(150, 0, 150, 50)));

  // this frame shouldn't have been modified since last time.
  XCTAssertTrue(CGRectEqualToRect(subview2.frame, CGRectMake(100, 0, 100, 50)));
}

- (void)testThatWeRespectIncludeInLayoutFlag
{
  const CGSize containerSize = CGSizeMake(300, 50);

  UIView *container = [[UIView alloc] initWithFrame:CGRectMake(0, 0, containerSize.width, containerSize.height)];
  [container css_setUsesFlexbox:YES];
  [container css_setFlexDirection:YGFlexDirectionRow];

  UIView *subview1 = [[UIView alloc] initWithFrame:CGRectZero];
  [subview1 css_setUsesFlexbox:YES];
  [subview1 css_setFlexGrow:1];
  [container addSubview:subview1];

  UIView *subview2 = [[UIView alloc] initWithFrame:CGRectZero];
  [subview2 css_setUsesFlexbox:YES];
  [subview2 css_setFlexGrow:1];
  [container addSubview:subview2];

  UIView *subview3 = [[UIView alloc] initWithFrame:CGRectZero];
  [subview3 css_setUsesFlexbox:YES];
  [subview3 css_setFlexGrow:1];
  [container addSubview:subview3];

  [container css_applyLayout];

  for (UIView *view in container.subviews) {
    XCTAssertTrue(CGSizeEqualToSize(CGSizeMake(100, 50), subview1.bounds.size), @"Actual size is %@", NSStringFromCGSize(view.bounds.size));
  }

  [subview3 css_setIncludeInLayout:NO];
  [container css_applyLayout];

  XCTAssertTrue(CGSizeEqualToSize(CGSizeMake(150, 50), subview1.bounds.size), @"Actual size is %@", NSStringFromCGSize(subview1.bounds.size));
  XCTAssertTrue(CGSizeEqualToSize(CGSizeMake(150, 50), subview2.bounds.size), @"Actual size is %@", NSStringFromCGSize(subview2.bounds.size));

  // We don't set the frame to zero, so, it should be set to what it was previously at.
  XCTAssertTrue(CGSizeEqualToSize(CGSizeMake(100, 50), subview3.bounds.size), @"Actual size is %@", NSStringFromCGSize(subview3.bounds.size));
}

- (void)testThatNumberOfChildrenIsCorrectWhenWeIgnoreSubviews
{
  UIView *container = [[UIView alloc] initWithFrame:CGRectZero];
  [container css_setUsesFlexbox:YES];
  [container css_setFlexDirection:YGFlexDirectionRow];

  UIView *subview1 = [[UIView alloc] initWithFrame:CGRectZero];
  [subview1 css_setUsesFlexbox:YES];
  [subview1 css_setIncludeInLayout:NO];
  [container addSubview:subview1];

  UIView *subview2 = [[UIView alloc] initWithFrame:CGRectZero];
  [subview2 css_setUsesFlexbox:YES];
  [subview2 css_setIncludeInLayout:NO];
  [container addSubview:subview2];

  UIView *subview3 = [[UIView alloc] initWithFrame:CGRectZero];
  [subview3 css_setUsesFlexbox:YES];
  [subview3 css_setIncludeInLayout:YES];
  [container addSubview:subview3];

  [container css_applyLayout];
  XCTAssertEqual(1, [container css_numberOfChildren]);

  [subview2 css_setIncludeInLayout:YES];
  [container css_applyLayout];
  XCTAssertEqual(2, [container css_numberOfChildren]);
}

- (void)testThatViewNotIncludedInFirstLayoutPassAreIncludedInSecond
{
  UIView *container = [[UIView alloc] initWithFrame:CGRectMake(0, 0, 300, 50)];
  [container css_setUsesFlexbox:YES];
  [container css_setFlexDirection:YGFlexDirectionRow];

  UIView *subview1 = [[UIView alloc] initWithFrame:CGRectZero];
  [subview1 css_setUsesFlexbox:YES];
  [subview1 css_setFlexGrow:1];
  [container addSubview:subview1];

  UIView *subview2 = [[UIView alloc] initWithFrame:CGRectZero];
  [subview2 css_setUsesFlexbox:YES];
  [subview2 css_setFlexGrow:1];
  [container addSubview:subview2];

  UIView *subview3 = [[UIView alloc] initWithFrame:CGRectZero];
  [subview3 css_setUsesFlexbox:YES];
  [subview3 css_setFlexGrow:1];
  [subview3 css_setIncludeInLayout:NO];
  [container addSubview:subview3];

  [container css_applyLayout];

  XCTAssertTrue(CGSizeEqualToSize(CGSizeMake(150, 50), subview1.bounds.size), @"Actual size is %@", NSStringFromCGSize(subview1.bounds.size));
  XCTAssertTrue(CGSizeEqualToSize(CGSizeMake(150, 50), subview2.bounds.size), @"Actual size is %@", NSStringFromCGSize(subview2.bounds.size));
  XCTAssertTrue(CGSizeEqualToSize(CGSizeZero, subview3.bounds.size), @"Actual size %@", NSStringFromCGSize(subview3.bounds.size));

  [subview3 css_setIncludeInLayout:YES];
  [container css_applyLayout];
  for (UIView *view in container.subviews) {
    XCTAssertTrue(CGSizeEqualToSize(CGSizeMake(100, 50), subview1.bounds.size), @"Actual size is %@", NSStringFromCGSize(view.bounds.size));
  }
}

@end
