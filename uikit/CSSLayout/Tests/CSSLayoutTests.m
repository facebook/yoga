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

- (void)testHiddenViewsAreNotMeasured
{
  const CGSize firstSize = CGSizeMake(100, 100);
  UIView *view = [[UIView alloc] initWithFrame:CGRectZero];
  [view css_setUsesFlexbox:YES];
  [view css_setWidth:firstSize.width];
  [view css_setHeight:firstSize.height];

  [view css_applyLayout];
  XCTAssertTrue(CGSizeEqualToSize(firstSize, view.frame.size));

  const CGSize newSize = CGSizeMake(200, 200);
  [view css_setWidth:newSize.width];
  [view css_setHeight:newSize.height];
  view.hidden = YES;

  [view css_applyLayout];
  XCTAssertFalse(CGSizeEqualToSize(newSize, view.frame.size));
}

@end
