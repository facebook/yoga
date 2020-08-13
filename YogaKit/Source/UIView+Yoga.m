/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#import <objc/runtime.h>
#import "UIView+Yoga.h"
#import "YGLayout+Private.h"

static const void* kYGYogaAssociatedKey = &kYGYogaAssociatedKey;

@implementation UIView (YogaKit)

- (YGLayout*)yoga {
  YGLayout* yoga = objc_getAssociatedObject(self, kYGYogaAssociatedKey);
  if (!yoga) {
    yoga = [[YGLayout alloc] initWithView:self];
    objc_setAssociatedObject(
        self, kYGYogaAssociatedKey, yoga, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
  }

  return yoga;
}

- (BOOL)isYogaEnabled {
  return objc_getAssociatedObject(self, kYGYogaAssociatedKey) != nil;
}

- (void)configureLayoutWithBlock:(YGLayoutConfigurationBlock)block {
  if (block != nil) {
    block(self.yoga);
  }
}

@end


static const void* kYGBoundsSizeAssociatedKey = &kYGBoundsSizeAssociatedKey;
static void YogaSwizzleInstanceMethod(Class cls, SEL originalSelector, SEL swizzledSelector);

@implementation UIView (YogaKitAutoApplyLayout)

+ (void)load {
  static dispatch_once_t onceToken;
  dispatch_once(&onceToken, ^{
    YogaSwizzleInstanceMethod(self, @selector(initWithFrame:), @selector(_yoga_initWithFrame:));
    YogaSwizzleInstanceMethod(self, @selector(setFrame:), @selector(_yoga_setFrame:));
    YogaSwizzleInstanceMethod(self, @selector(setBounds:), @selector(_yoga_setBounds:));
#if TARGET_OS_OSX
    YogaSwizzleInstanceMethod(self, @selector(setFrameSize:), @selector(_yoga_setFrameSize:));
    YogaSwizzleInstanceMethod(self, @selector(setBoundsSize:), @selector(_yoga_setBoundsSize:));
#endif
  });
}

- (CGSize)_yoga_boundsSize {
  NSValue *value = (NSValue *)objc_getAssociatedObject(self, kYGBoundsSizeAssociatedKey);

  return value ?
#if TARGET_OS_OSX
            value.sizeValue
#else
            value.CGSizeValue
#endif
            : CGSizeMake(YGUndefined, YGUndefined);
}

- (void)set_yoga_boundsSize:(CGSize)size {
  objc_setAssociatedObject(self,
                            kYGBoundsSizeAssociatedKey,
#if TARGET_OS_OSX
                            [NSValue valueWithSize:size]
#else
                            [NSValue valueWithCGSize:size]
#endif
                             , OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}

- (instancetype)_yoga_initWithFrame:(CGRect)frame {
  id _self = [self _yoga_initWithFrame:frame];
  if (_self) {
    [self _yoga_applyLayout];
  }

  return _self;
}

- (void)_yoga_setFrame:(CGRect)frame {
  [self _yoga_setFrame:frame];

  [self _yoga_applyLayout];
}

- (void)_yoga_setBounds:(CGRect)bounds {
  [self _yoga_setBounds:bounds];

  [self _yoga_applyLayout];
}

#if TARGET_OS_OSX
- (void)_yoga_setFrameSize:(NSSize)newSize {
  [self _yoga_setFrameSize:newSize];

  [self _yoga_applyLayout];
}

- (void)_yoga_setBoundsSize:(NSSize)newSize {
  [self _yoga_setBoundsSize:newSize];

  [self _yoga_applyLayout];
}
#endif

- (void)_yoga_applyLayout {
    if (self.isYogaEnabled && self.yoga.isEnabled) {
        CGSize size = self.bounds.size;
        CGSize prev = self._yoga_boundsSize;
        if (!CGSizeEqualToSize(size, prev)) {
            self._yoga_boundsSize = size;
            [self.yoga applyLayoutPreservingOrigin:YES];
        }
    }
}

@end


static void YogaSwizzleInstanceMethod(Class cls, SEL originalSelector, SEL swizzledSelector) {
    if (!cls || !originalSelector || !swizzledSelector) {
        return;
    }

    Method originalMethod = class_getInstanceMethod(cls, originalSelector);
    Method swizzledMethod = class_getInstanceMethod(cls, swizzledSelector);
    if (!originalMethod || !swizzledMethod) {
        return;
    }

    IMP swizzledIMP = method_getImplementation(swizzledMethod);
    if (class_addMethod(cls, originalSelector, swizzledIMP, method_getTypeEncoding(swizzledMethod))) {
        class_replaceMethod(cls,
                            swizzledSelector,
                            method_getImplementation(originalMethod),
                            method_getTypeEncoding(originalMethod));
    } else {
        method_exchangeImplementations(originalMethod, swizzledMethod);
    }
}
