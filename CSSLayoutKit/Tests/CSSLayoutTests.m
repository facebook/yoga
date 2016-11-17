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

@interface CSSLayoutTests : XCTestCase
@end

@implementation CSSLayoutTests

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
  XCTAssertThrows([view css_sizeThatFits:CGSizeZero]);

  dispatch_sync(dispatch_queue_create("com.facebook.CSSLayout.testing", DISPATCH_QUEUE_SERIAL), ^(void){
    XCTAssertThrows([view css_sizeThatFits:CGSizeZero]);
  });
}

- (void)testSizeThatFitsSmoke
{
  UIView *view = [[UIView alloc] initWithFrame:CGRectZero];
  [view css_setUsesFlexbox:YES];

  const CGSize constrainedSize = CGSizeMake(50, 50);
  const CGSize actualSize = [view css_sizeThatFits:constrainedSize];
  XCTAssertTrue(CGSizeEqualToSize(constrainedSize, actualSize), @"Actual Size: %@", NSStringFromCGSize(actualSize));
}

- (void)testFrameAndOriginPlacement
{
  const CGSize containerSize = CGSizeMake(320, 50);

  UIView *container = [[UIView alloc] initWithFrame:CGRectMake(0, 0, containerSize.width, containerSize.height)];
  [container css_setUsesFlexbox:YES];
  [container css_setFlexDirection:CSSFlexDirectionRow];

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

@end
