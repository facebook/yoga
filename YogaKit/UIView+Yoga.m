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

@interface CSSNodeBridge : NSObject
@property (nonatomic, assign, readonly) CSSNodeRef cnode;
@end

@implementation CSSNodeBridge

+ (void)initialize
{
  CSSLayoutSetExperimentalFeatureEnabled(YGExperimentalFeatureWebFlexBasis, true);
}

- (instancetype)init
{
  if ([super init]) {
    _cnode = CSSNodeNew();
  }

  return self;
}

- (void)dealloc
{
  CSSNodeFree(_cnode);
}
@end

@implementation UIView (CSSLayout)

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
  return CSSNodeChildCount([self cssNode]);
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
  CSSNodeStyleSetDirection([self cssNode], direction);
}

- (void)yg_setFlexDirection:(YGFlexDirection)flexDirection
{
  CSSNodeStyleSetFlexDirection([self cssNode], flexDirection);
}

- (void)yg_setJustifyContent:(YGJustify)justifyContent
{
  CSSNodeStyleSetJustifyContent([self cssNode], justifyContent);
}

- (void)yg_setAlignContent:(YGAlign)alignContent
{
  CSSNodeStyleSetAlignContent([self cssNode], alignContent);
}

- (void)yg_setAlignItems:(YGAlign)alignItems
{
  CSSNodeStyleSetAlignItems([self cssNode], alignItems);
}

- (void)yg_setAlignSelf:(YGAlign)alignSelf
{
  CSSNodeStyleSetAlignSelf([self cssNode], alignSelf);
}

- (void)yg_setPositionType:(YGPositionType)positionType
{
  CSSNodeStyleSetPositionType([self cssNode], positionType);
}

- (void)yg_setFlexWrap:(YGWrap)flexWrap
{
  CSSNodeStyleSetFlexWrap([self cssNode], flexWrap);
}

- (void)yg_setFlexGrow:(CGFloat)flexGrow
{
  CSSNodeStyleSetFlexGrow([self cssNode], flexGrow);
}

- (void)yg_setFlexShrink:(CGFloat)flexShrink
{
  CSSNodeStyleSetFlexShrink([self cssNode], flexShrink);
}

- (void)yg_setFlexBasis:(CGFloat)flexBasis
{
  CSSNodeStyleSetFlexBasis([self cssNode], flexBasis);
}

- (void)yg_setPosition:(CGFloat)position forEdge:(YGEdge)edge
{
  CSSNodeStyleSetPosition([self cssNode], edge, position);
}

- (void)yg_setMargin:(CGFloat)margin forEdge:(YGEdge)edge
{
  CSSNodeStyleSetMargin([self cssNode], edge, margin);
}

- (void)yg_setPadding:(CGFloat)padding forEdge:(YGEdge)edge
{
  CSSNodeStyleSetPadding([self cssNode], edge, padding);
}

- (void)yg_setWidth:(CGFloat)width
{
  CSSNodeStyleSetWidth([self cssNode], width);
}

- (void)yg_setHeight:(CGFloat)height
{
  CSSNodeStyleSetHeight([self cssNode], height);
}

- (void)yg_setMinWidth:(CGFloat)minWidth
{
  CSSNodeStyleSetMinWidth([self cssNode], minWidth);
}

- (void)yg_setMinHeight:(CGFloat)minHeight
{
  CSSNodeStyleSetMinHeight([self cssNode], minHeight);
}

- (void)yg_setMaxWidth:(CGFloat)maxWidth
{
  CSSNodeStyleSetMaxWidth([self cssNode], maxWidth);
}

- (void)yg_setMaxHeight:(CGFloat)maxHeight
{
  CSSNodeStyleSetMaxHeight([self cssNode], maxHeight);
}

- (void)yg_setAspectRatio:(CGFloat)aspectRatio
{
  CSSNodeStyleSetAspectRatio([self cssNode], aspectRatio);
}

#pragma mark - Layout and Sizing

- (YGDirection)yg_resolvedDirection
{
  return CSSNodeLayoutGetDirection([self cssNode]);
}

- (void)yg_applyLayout
{
  [self calculateLayoutWithSize:self.bounds.size];
  CSSApplyLayoutToViewHierarchy(self);
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

- (CSSNodeRef)cssNode
{
  CSSNodeBridge *node = objc_getAssociatedObject(self, @selector(cssNode));
  if (!node) {
    node = [CSSNodeBridge new];
    CSSNodeSetContext(node.cnode, (__bridge void *) self);
    objc_setAssociatedObject(self, @selector(cssNode), node, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
  }

  return node.cnode;
}

- (CGSize)calculateLayoutWithSize:(CGSize)size
{
  NSAssert([NSThread isMainThread], @"CSS Layout calculation must be done on main.");
  NSAssert([self yg_usesYoga], @"CSS Layout is not enabled for this view.");

  CSSAttachNodesFromViewHierachy(self);

  const CSSNodeRef node = [self cssNode];
  CSSNodeCalculateLayout(
    node,
    size.width,
    size.height,
    CSSNodeStyleGetDirection(node));

  return (CGSize) {
    .width = CSSNodeLayoutGetWidth(node),
    .height = CSSNodeLayoutGetHeight(node),
  };
}

static CSSSize CSSMeasureView(
  CSSNodeRef node,
  float width,
  YGMeasureMode widthMode,
  float height,
  YGMeasureMode heightMode)
{
  const CGFloat constrainedWidth = (widthMode == YGMeasureModeUndefined) ? CGFLOAT_MAX : width;
  const CGFloat constrainedHeight = (heightMode == YGMeasureModeUndefined) ? CGFLOAT_MAX: height;

  UIView *view = (__bridge UIView*) CSSNodeGetContext(node);
  const CGSize sizeThatFits = [view sizeThatFits:(CGSize) {
    .width = constrainedWidth,
    .height = constrainedHeight,
  }];

  return (CSSSize) {
    .width = CSSSanitizeMeasurement(constrainedWidth, sizeThatFits.width, widthMode),
    .height = CSSSanitizeMeasurement(constrainedHeight, sizeThatFits.height, heightMode),
  };
}

static CGFloat CSSSanitizeMeasurement(
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

static void CSSAttachNodesFromViewHierachy(UIView *view) {
  CSSNodeRef node = [view cssNode];

  // Only leaf nodes should have a measure function
  if (![view yg_usesYoga] || view.subviews.count == 0) {
    CSSNodeSetMeasureFunc(node, CSSMeasureView);
    CSSRemoveAllChildren(node);
  } else {
    CSSNodeSetMeasureFunc(node, NULL);

    // Create a list of all the subviews that we are going to use for layout.
    NSMutableArray<UIView *> *subviewsToInclude = [[NSMutableArray alloc] initWithCapacity:view.subviews.count];
    for (UIView *subview in view.subviews) {
      if ([subview yg_includeInLayout]) {
        [subviewsToInclude addObject:subview];
      }
    }

    BOOL shouldReconstructChildList = NO;
    if (CSSNodeChildCount(node) != subviewsToInclude.count) {
      shouldReconstructChildList = YES;
    } else {
      for (int i = 0; i < subviewsToInclude.count; i++) {
        if (CSSNodeGetChild(node, i) != [subviewsToInclude[i] cssNode]) {
          shouldReconstructChildList = YES;
          break;
        }
      }
    }

    if (shouldReconstructChildList) {
      CSSRemoveAllChildren(node);

      for (int i = 0 ; i < subviewsToInclude.count; i++) {
        UIView *const subview = subviewsToInclude[i];
        CSSNodeInsertChild(node, [subview cssNode], i);
        CSSAttachNodesFromViewHierachy(subview);
      }
    }
  }
}

static void CSSRemoveAllChildren(const CSSNodeRef node)
{
  if (node == NULL) {
      return;
  }

  while (CSSNodeChildCount(node) > 0) {
    CSSNodeRemoveChild(node, CSSNodeGetChild(node, CSSNodeChildCount(node) - 1));
  }
}

static CGFloat CSSRoundPixelValue(CGFloat value)
{
  static CGFloat scale;
  static dispatch_once_t onceToken;
  dispatch_once(&onceToken, ^(){
    scale = [UIScreen mainScreen].scale;
  });

  return round(value * scale) / scale;
}

static void CSSApplyLayoutToViewHierarchy(UIView *view) {
  NSCAssert([NSThread isMainThread], @"Framesetting should only be done on the main thread.");
  if (![view yg_includeInLayout]) {
     return;
  }

  CSSNodeRef node = [view cssNode];
  const CGPoint topLeft = {
    CSSNodeLayoutGetLeft(node),
    CSSNodeLayoutGetTop(node),
  };

  const CGPoint bottomRight = {
    topLeft.x + CSSNodeLayoutGetWidth(node),
    topLeft.y + CSSNodeLayoutGetHeight(node),
  };

  view.frame = (CGRect) {
    .origin = {
      .x = CSSRoundPixelValue(topLeft.x),
      .y = CSSRoundPixelValue(topLeft.y),
    },
    .size = {
      .width = CSSRoundPixelValue(bottomRight.x) - CSSRoundPixelValue(topLeft.x),
      .height = CSSRoundPixelValue(bottomRight.y) - CSSRoundPixelValue(topLeft.y),
    },
  };

  const BOOL isLeaf = ![view yg_usesYoga] || view.subviews.count == 0;
  if (!isLeaf) {
    for (NSUInteger i = 0; i < view.subviews.count; i++) {
      CSSApplyLayoutToViewHierarchy(view.subviews[i]);
    }
  }
}

@end
