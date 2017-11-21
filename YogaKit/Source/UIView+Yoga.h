/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#import "YGLayout.h"
#import <UIKit/UIKit.h>
#include <os/base.h>

NS_ASSUME_NONNULL_BEGIN

typedef void (^YGLayoutConfigurationBlock)(YGLayout *);

// Allow this category to be used without requiring -ObjC.
// Any file that imports this header will have a link time dependency on UIView+Yoga.m
extern const char YGCategoryUIViewYoga;
extern const void * const OS_WEAK YGLinkRequire;
const void * const OS_WEAK YGLinkRequire = &YGCategoryUIViewYoga;

@interface UIView (Yoga)

/**
 The YGLayout that is attached to this view. It is lazily created.
 */
@property (nonatomic, readonly, strong) YGLayout *yoga;
/**
 Indicates whether or not Yoga is enabled
 */
@property (nonatomic, readonly, assign) BOOL isYogaEnabled;

/**
 In ObjC land, every time you access `view.yoga.*` you are adding another `objc_msgSend`
 to your code. If you plan on making multiple changes to YGLayout, it's more performant
 to use this method, which uses a single objc_msgSend call.
 */
- (void)configureLayoutWithBlock:(YGLayoutConfigurationBlock)block
    NS_SWIFT_NAME(configureLayout(block:));

@end

NS_ASSUME_NONNULL_END
