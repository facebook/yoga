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

- (void)testNodesAreDeallocedWithSingleView
{
  XCTAssertEqual(0, CSSNodeGetInstanceCount());

  UIView *view = [[UIView alloc] initWithFrame:CGRectZero];
  [view css_setFlex:1];
  XCTAssertEqual(1, CSSNodeGetInstanceCount());
  view = nil;

  XCTAssertEqual(0, CSSNodeGetInstanceCount());
}

- (void)testNodesAreDeallocedCascade
{
  XCTAssertEqual(0, CSSNodeGetInstanceCount());

  UIView *view = [[UIView alloc] initWithFrame:CGRectZero];
  [view css_setFlex:1];

  for (int i=0; i<10; i++) {
    UIView *subview = [[UIView alloc] initWithFrame:CGRectZero];
    [subview css_setFlex:1];
    [view addSubview:subview];
  }
  XCTAssertEqual(11, CSSNodeGetInstanceCount());
  view = nil;

  XCTAssertEqual(0, CSSNodeGetInstanceCount());
}

- (void)testUsesFlexbox
{
  UIView *view = [[UIView alloc] initWithFrame:CGRectZero];
  XCTAssertFalse([view css_usesFlexbox]);

  [view css_setUsesFlexbox:YES];
  XCTAssertTrue([view css_usesFlexbox]);

  [view css_setUsesFlexbox:NO];
  XCTAssertFalse([view css_usesFlexbox]);
}

@end
