/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#import "UIView+Yoga.h"

#import <objc/runtime.h>

static const void *kYGNodeBridgeAssociatedKey = &kYGNodeBridgeAssociatedKey;

@interface YGNodeBridge : NSObject
@property (nonatomic, assign, readonly) YGNodeRef cnode;
@end

@implementation YGNodeBridge

+ (void)initialize
{
  YGSetExperimentalFeatureEnabled(YGExperimentalFeatureWebFlexBasis, true);
}

- (instancetype)init
{
  if ([super init]) {
    _cnode = YGNodeNew();
  }

  return self;
}

- (void)dealloc
{
  YGNodeFree(_cnode);
}
@end

@implementation UIView (Yoga)

- (void)yg_markDirty
{
  YGNodeBridge *const bridge = objc_getAssociatedObject(self, kYGNodeBridgeAssociatedKey);
  if (bridge != nil && [self yg_isLeaf]) {
    YGNodeMarkDirty(bridge.cnode);
  }
}

- (BOOL)yg_usesYoga
{
  NSNumber *usesYoga = objc_getAssociatedObject(self, @selector(yg_usesYoga));
  return [usesYoga boolValue];
}

- (BOOL)yg_includeInLayout
{
  NSNumber *includeInLayout = objc_getAssociatedObject(self, @selector(yg_includeInLayout));
  return (includeInLayout != nil) ? [includeInLayout boolValue] : YES;
}

- (NSUInteger)yg_numberOfChildren
{
  return YGNodeGetChildCount([self ygNode]);
}

- (BOOL)yg_isLeaf
{
  NSAssert([NSThread isMainThread], @"This method must be called on the main thread.");
  if ([self yg_usesYoga]) {
      for (UIView *subview in self.subviews) {
          if ([subview yg_usesYoga] && [subview yg_includeInLayout]) {
              return NO;
          }
      }
  }

  return YES;
}

#pragma mark - Setters

- (void)yg_setIncludeInLayout:(BOOL)includeInLayout
{
  objc_setAssociatedObject(
    self,
    @selector(yg_includeInLayout),
    @(includeInLayout),
    OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}

- (void)yg_setUsesYoga:(BOOL)enabled
{
  objc_setAssociatedObject(
    self,
    @selector(yg_usesYoga),
    @(enabled),
    OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}

- (void)yg_setDirection:(YGDirection)direction
{
  YGNodeStyleSetDirection([self ygNode], direction);
}

- (void)yg_setFlexDirection:(YGFlexDirection)flexDirection
{
  YGNodeStyleSetFlexDirection([self ygNode], flexDirection);
}

- (void)yg_setJustifyContent:(YGJustify)justifyContent
{
  YGNodeStyleSetJustifyContent([self ygNode], justifyContent);
}

- (void)yg_setAlignContent:(YGAlign)alignContent
{
  YGNodeStyleSetAlignContent([self ygNode], alignContent);
}

- (void)yg_setAlignItems:(YGAlign)alignItems
{
  YGNodeStyleSetAlignItems([self ygNode], alignItems);
}

- (void)yg_setAlignSelf:(YGAlign)alignSelf
{
  YGNodeStyleSetAlignSelf([self ygNode], alignSelf);
}

- (void)yg_setPositionType:(YGPositionType)positionType
{
  YGNodeStyleSetPositionType([self ygNode], positionType);
}

- (void)yg_setFlexWrap:(YGWrap)flexWrap
{
  YGNodeStyleSetFlexWrap([self ygNode], flexWrap);
}

- (void)yg_setOverflow:(YGOverflow)overflow
{
  YGNodeStyleSetOverflow([self ygNode], overflow);
}

- (void)yg_setFlexGrow:(CGFloat)flexGrow
{
  YGNodeStyleSetFlexGrow([self ygNode], flexGrow);
}

- (void)yg_setFlexShrink:(CGFloat)flexShrink
{
  YGNodeStyleSetFlexShrink([self ygNode], flexShrink);
}

- (void)yg_setFlexBasis:(CGFloat)flexBasis
{
  YGNodeStyleSetFlexBasis([self ygNode], flexBasis);
}

- (void)yg_setPosition:(CGFloat)position forEdge:(YGEdge)edge
{
  YGNodeStyleSetPosition([self ygNode], edge, position);
}

- (void)yg_setMargin:(CGFloat)margin forEdge:(YGEdge)edge
{
  YGNodeStyleSetMargin([self ygNode], edge, margin);
}

- (void)yg_setPadding:(CGFloat)padding forEdge:(YGEdge)edge
{
  YGNodeStyleSetPadding([self ygNode], edge, padding);
}

- (void)yg_setWidth:(CGFloat)width
{
  YGNodeStyleSetWidth([self ygNode], width);
}

- (void)yg_setHeight:(CGFloat)height
{
  YGNodeStyleSetHeight([self ygNode], height);
}

- (void)yg_setMinWidth:(CGFloat)minWidth
{
  YGNodeStyleSetMinWidth([self ygNode], minWidth);
}

- (void)yg_setMinHeight:(CGFloat)minHeight
{
  YGNodeStyleSetMinHeight([self ygNode], minHeight);
}

- (void)yg_setMaxWidth:(CGFloat)maxWidth
{
  YGNodeStyleSetMaxWidth([self ygNode], maxWidth);
}

- (void)yg_setMaxHeight:(CGFloat)maxHeight
{
  YGNodeStyleSetMaxHeight([self ygNode], maxHeight);
}

- (void)yg_setAspectRatio:(CGFloat)aspectRatio
{
  YGNodeStyleSetAspectRatio([self ygNode], aspectRatio);
}

#pragma mark - Layout and Sizing

- (YGDirection)yg_resolvedDirection
{
  return YGNodeLayoutGetDirection([self ygNode]);
}

- (void)yg_applyLayout
{
  [self calculateLayoutWithSize:self.bounds.size];
  YGApplyLayoutToViewHierarchy(self);
}

- (CGSize)yg_intrinsicSize
{
  const CGSize constrainedSize = {
      .width = YGUndefined,
      .height = YGUndefined,
  };
  return [self calculateLayoutWithSize:constrainedSize];
}

#pragma mark - Private

- (YGNodeRef)ygNode
{
  YGNodeBridge *node = objc_getAssociatedObject(self, kYGNodeBridgeAssociatedKey);
  if (!node) {
    node = [YGNodeBridge new];
    YGNodeSetContext(node.cnode, (__bridge void *) self);
    objc_setAssociatedObject(self, kYGNodeBridgeAssociatedKey, node, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
  }
  return node.cnode;
}

- (CGSize)calculateLayoutWithSize:(CGSize)size
{
  NSAssert([NSThread isMainThread], @"YG Layout calculation must be done on main.");
  NSAssert([self yg_usesYoga], @"YG Layout is not enabled for this view.");

  YGAttachNodesFromViewHierachy(self);

  const YGNodeRef node = [self ygNode];
  YGNodeCalculateLayout(
    node,
    size.width,
    size.height,
    YGNodeStyleGetDirection(node));

  return (CGSize) {
    .width = YGNodeLayoutGetWidth(node),
    .height = YGNodeLayoutGetHeight(node),
  };
}

static YGSize YGMeasureView(
  YGNodeRef node,
  float width,
  YGMeasureMode widthMode,
  float height,
  YGMeasureMode heightMode)
{
  const CGFloat constrainedWidth = (widthMode == YGMeasureModeUndefined) ? CGFLOAT_MAX : width;
  const CGFloat constrainedHeight = (heightMode == YGMeasureModeUndefined) ? CGFLOAT_MAX: height;

  UIView *view = (__bridge UIView*) YGNodeGetContext(node);
  const CGSize sizeThatFits = [view sizeThatFits:(CGSize) {
    .width = constrainedWidth,
    .height = constrainedHeight,
  }];

  return (YGSize) {
    .width = YGSanitizeMeasurement(constrainedWidth, sizeThatFits.width, widthMode),
    .height = YGSanitizeMeasurement(constrainedHeight, sizeThatFits.height, heightMode),
  };
}

static CGFloat YGSanitizeMeasurement(
  CGFloat constrainedSize,
  CGFloat measuredSize,
  YGMeasureMode measureMode)
{
  CGFloat result;
  if (measureMode == YGMeasureModeExactly) {
    result = constrainedSize;
  } else if (measureMode == YGMeasureModeAtMost) {
    result = MIN(constrainedSize, measuredSize);
  } else {
    result = measuredSize;
  }

  return result;
}

static BOOL YGNodeHasExactSameChildren(const YGNodeRef node, NSArray<UIView *> *subviews)
{
  if (YGNodeGetChildCount(node) != subviews.count) {
    return NO;
  }

  for (int i=0; i<subviews.count; i++) {
    if (YGNodeGetChild(node, i) != subviews[i].ygNode) {
      return NO;
    }
  }

  return YES;
}

static void YGAttachNodesFromViewHierachy(UIView *const view)
{
  const YGNodeRef node = [view ygNode];

  // Only leaf nodes should have a measure function
  if (view.yg_isLeaf) {
    YGRemoveAllChildren(node);
    YGNodeSetMeasureFunc(node, YGMeasureView);
  } else {
    YGNodeSetMeasureFunc(node, NULL);

    NSMutableArray<UIView *> *subviewsToInclude = [[NSMutableArray alloc] initWithCapacity:view.subviews.count];
    for (UIView *subview in view.subviews) {
      if ([subview yg_includeInLayout]) {
        [subviewsToInclude addObject:subview];
      }
    }

    if (!YGNodeHasExactSameChildren(node, subviewsToInclude)) {
        YGRemoveAllChildren(node);
        for (int i=0; i<subviewsToInclude.count; i++) {
            YGNodeInsertChild(node, [subviewsToInclude[i] ygNode], i);
        }
    }

    for (UIView *const subview in subviewsToInclude) {
        YGAttachNodesFromViewHierachy(subview);
    }
  }
}

static void YGRemoveAllChildren(const YGNodeRef node)
{
  if (node == NULL) {
      return;
  }

  while (YGNodeGetChildCount(node) > 0) {
    YGNodeRemoveChild(node, YGNodeGetChild(node, YGNodeGetChildCount(node) - 1));
  }
}

static CGFloat YGRoundPixelValue(CGFloat value)
{
  static CGFloat scale;
  static dispatch_once_t onceToken;
  dispatch_once(&onceToken, ^(){
    scale = [UIScreen mainScreen].scale;
  });

  return round(value * scale) / scale;
}

static void YGApplyLayoutToViewHierarchy(UIView *view)
{
  NSCAssert([NSThread isMainThread], @"Framesetting should only be done on the main thread.");
  if (![view yg_includeInLayout]) {
     return;
  }

  YGNodeRef node = [view ygNode];
  const CGPoint topLeft = {
    YGNodeLayoutGetLeft(node),
    YGNodeLayoutGetTop(node),
  };

  const CGPoint bottomRight = {
    topLeft.x + YGNodeLayoutGetWidth(node),
    topLeft.y + YGNodeLayoutGetHeight(node),
  };

  view.frame = (CGRect) {
    .origin = {
      .x = YGRoundPixelValue(topLeft.x),
      .y = YGRoundPixelValue(topLeft.y),
    },
    .size = {
      .width = YGRoundPixelValue(bottomRight.x) - YGRoundPixelValue(topLeft.x),
      .height = YGRoundPixelValue(bottomRight.y) - YGRoundPixelValue(topLeft.y),
    },
  };

  if (!view.yg_isLeaf) {
    for (NSUInteger i=0; i<view.subviews.count; i++) {
      YGApplyLayoutToViewHierarchy(view.subviews[i]);
    }
  }
}

@end
