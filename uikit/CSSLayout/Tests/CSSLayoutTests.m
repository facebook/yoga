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

- (void)testSmoke
{
  UIView *view = [[UIView alloc] initWithFrame:CGRectZero];
  [view css_setUsesFlexbox:YES];
  XCTAssertTrue([view css_usesFlexbox]);
}

@end
