/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#import "YGLayout.h"
#import <yoga/Yoga.h>

@interface YGLayout ()

@property (nonatomic, assign, readonly) YGNodeRef node;

- (instancetype)initWithView:(UIView *)view;

@end
