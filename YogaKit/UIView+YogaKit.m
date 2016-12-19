/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#import <YogaKit/UIView+YogaKit.h>
#import <YogaKit/YKLayout+Private.h>
#import <objc/runtime.h>

@implementation UIView (YogaKit)

- (YKLayout *)layout
{
  YKLayout *layout = objc_getAssociatedObject(self, @selector(layout));
  if (!layout) {
    layout = [[YKLayout alloc] initWithView:self];
    objc_setAssociatedObject(self, @selector(layout), layout, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
  }
  
  return layout;
}


@end
