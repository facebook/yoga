/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#import <YogaKit/UIView+Yoga.h>
#import <YogaKit/yoga.h>
#import <objc/runtime.h>

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

@implementation UIView (YogaKit)

- (BOOL)yk_usesYoga
{
  NSNumber *usesYoga = objc_getAssociatedObject(self, @selector(yk_usesYoga));
  return [usesYoga boolValue];
}

- (BOOL)yk_includeInLayout
{
  NSNumber *includeInLayout = objc_getAssociatedObject(self, @selector(yk_includeInLayout));
  return (includeInLayout != nil) ? [includeInLayout boolValue] : YES;
}

- (NSUInteger)yk_numberOfChildren
{
  return YGNodeGetChildCount([self ygNode]);
}

#pragma mark - Setters

- (void)yk_setIncludeInLayout:(BOOL)includeInLayout
{
  objc_setAssociatedObject(
    self,
    @selector(yk_includeInLayout),
    @(includeInLayout),
    OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}

- (void)yk_setUsesYoga:(BOOL)enabled
{
  objc_setAssociatedObject(
    self,
    @selector(yk_usesYoga),
    @(enabled),
    OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}

- (YKDirection)yk_direction
{
  return (YKDirection)YGNodeStyleGetDirection([self ygNode]);
}

- (void)yk_setDirection:(YKDirection)direction
{
  YGNodeStyleSetDirection([self ygNode], (YGDirection)direction);
}

- (YKFlexDirection)yk_flexDirection
{
  return (YKFlexDirection)YGNodeStyleGetFlexDirection([self ygNode]);
}

- (void)yk_setFlexDirection:(YKFlexDirection)flexDirection
{
  YGNodeStyleSetFlexDirection([self ygNode], (YGFlexDirection)flexDirection);
}

- (YKJustify)yk_justifyContent
{
  return (YKJustify)YGNodeStyleGetJustifyContent([self ygNode]);
}

- (void)yk_setJustifyContent:(YKJustify)justifyContent
{
  YGNodeStyleSetJustifyContent([self ygNode], (YGJustify)justifyContent);
}

- (YKAlign)yk_alignContent
{
  return (YKAlign)YGNodeStyleGetAlignContent([self ygNode]);
}

- (void)yk_setAlignContent:(YKAlign)alignContent
{
  YGNodeStyleSetAlignContent([self ygNode], (YGAlign)alignContent);
}

- (YKAlign)yk_alignItems
{
  return (YKAlign)YGNodeStyleGetAlignItems([self ygNode]);
}

- (void)yk_setAlignItems:(YKAlign)alignItems
{
  YGNodeStyleSetAlignItems([self ygNode], (YGAlign)alignItems);
}

- (YKAlign)yk_alignSelf
{
  return (YKAlign)YGNodeStyleGetAlignSelf([self ygNode]);
}

- (void)yk_setAlignSelf:(YKAlign)alignSelf
{
  YGNodeStyleSetAlignSelf([self ygNode], (YGAlign)alignSelf);
}

- (YKPositionType)yk_positionType
{
  return (YKPositionType)YGNodeStyleGetPositionType([self ygNode]);
}

- (void)yk_setPositionType:(YKPositionType)positionType
{
  YGNodeStyleSetPositionType([self ygNode], (YGPositionType)positionType);
}

- (YKWrap)yk_flexWrap
{
  return (YKWrap)YGNodeStyleGetFlexWrap([self ygNode]);
}

- (void)yk_setFlexWrap:(YKWrap)flexWrap
{
  YGNodeStyleSetFlexWrap([self ygNode], (YGWrap)flexWrap);
}

- (CGFloat)yk_flexGrow
{
  return YGNodeStyleGetFlexGrow([self ygNode]);
}

- (void)yk_setFlexGrow:(CGFloat)flexGrow
{
  YGNodeStyleSetFlexGrow([self ygNode], flexGrow);
}

- (CGFloat)yk_flexShrink
{
  return YGNodeStyleGetFlexShrink([self ygNode]);
}

- (void)yk_setFlexShrink:(CGFloat)flexShrink
{
  YGNodeStyleSetFlexShrink([self ygNode], flexShrink);
}

- (CGFloat)yk_flexBasis
{
  return YGNodeStyleGetFlexBasis([self ygNode]);
}

- (void)yk_setFlexBasis:(CGFloat)flexBasis
{
  YGNodeStyleSetFlexBasis([self ygNode], flexBasis);
}

- (CGFloat)yk_positionForEdge:(YKEdge)edge
{
  return YGNodeStyleGetPosition([self ygNode], (YGEdge)edge);
}

- (void)yk_setPosition:(CGFloat)position forEdge:(YKEdge)edge
{
  YGNodeStyleSetPosition([self ygNode], (YGEdge)edge, position);
}

- (CGFloat)yk_marginForEdge:(YKEdge)edge
{
  return YGNodeStyleGetMargin([self ygNode], (YGEdge)edge);
}

- (void)yk_setMargin:(CGFloat)margin forEdge:(YKEdge)edge
{
  YGNodeStyleSetMargin([self ygNode], (YGEdge)edge, margin);
}

- (CGFloat)yk_paddingForEdge:(YKEdge)edge
{
  return YGNodeStyleGetPadding([self ygNode], (YGEdge)edge);
}

- (void)yk_setPadding:(CGFloat)padding forEdge:(YKEdge)edge
{
  YGNodeStyleSetPadding([self ygNode], (YGEdge)edge, padding);
}

- (CGFloat)yk_width
{
  return YGNodeStyleGetWidth([self ygNode]);
}

- (void)yk_setWidth:(CGFloat)width
{
  YGNodeStyleSetWidth([self ygNode], width);
}

- (CGFloat)yk_height
{
  return YGNodeStyleGetHeight([self ygNode]);
}

- (void)yk_setHeight:(CGFloat)height
{
  YGNodeStyleSetHeight([self ygNode], height);
}

- (CGFloat)yk_minWidth
{
  return YGNodeStyleGetMinWidth([self ygNode]);
}

- (void)yk_setMinWidth:(CGFloat)minWidth
{
  YGNodeStyleSetMinWidth([self ygNode], minWidth);
}

- (CGFloat)yk_minHeight
{
  return YGNodeStyleGetMinHeight([self ygNode]);
}

- (void)yk_setMinHeight:(CGFloat)minHeight
{
  YGNodeStyleSetMinHeight([self ygNode], minHeight);
}

- (CGFloat)yk_maxWidth
{
  return YGNodeStyleGetMaxWidth([self ygNode]);
}

- (void)yk_setMaxWidth:(CGFloat)maxWidth
{
  YGNodeStyleSetMaxWidth([self ygNode], maxWidth);
}

- (CGFloat)yk_maxHeight
{
  return YGNodeStyleGetMaxHeight([self ygNode]);
}

- (void)yk_setMaxHeight:(CGFloat)maxHeight
{
  YGNodeStyleSetMaxHeight([self ygNode], maxHeight);
}

- (CGFloat)yk_aspectRatio
{
  return YGNodeStyleGetAspectRatio([self ygNode]);
}

- (void)yk_setAspectRatio:(CGFloat)aspectRatio
{
  YGNodeStyleSetAspectRatio([self ygNode], aspectRatio);
}

#pragma mark - Layout and Sizing

- (YKDirection)yk_resolvedDirection
{
  return (YKDirection)YGNodeLayoutGetDirection([self ygNode]);
}

- (void)yk_applyLayout
{
  [self calculateLayoutWithSize:self.bounds.size];
  YKApplyLayoutToViewHierarchy(self);
}

- (CGSize)yk_intrinsicSize
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
  YGNodeBridge *node = objc_getAssociatedObject(self, @selector(ygNode));
  if (!node) {
    node = [YGNodeBridge new];
    YGNodeSetContext(node.cnode, (__bridge void *) self);
    objc_setAssociatedObject(self, @selector(ygNode), node, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
  }

  return node.cnode;
}

- (CGSize)calculateLayoutWithSize:(CGSize)size
{
  NSAssert([NSThread isMainThread], @"YG Layout calculation must be done on main.");
  NSAssert([self yk_usesYoga], @"YG Layout is not enabled for this view.");

  YKAttachNodesFromViewHierachy(self);

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

static YGSize YKMeasureView(
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
    .width = YKSanitizeMeasurement(constrainedWidth, sizeThatFits.width, widthMode),
    .height = YKSanitizeMeasurement(constrainedHeight, sizeThatFits.height, heightMode),
  };
}

static CGFloat YKSanitizeMeasurement(
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

static void YKAttachNodesFromViewHierachy(UIView *view) {
  YGNodeRef node = [view ygNode];

  // Only leaf nodes should have a measure function
  if (![view yk_usesYoga] || view.subviews.count == 0) {
    YGNodeSetMeasureFunc(node, YKMeasureView);
    YKRemoveAllChildren(node);
  } else {
    YGNodeSetMeasureFunc(node, NULL);

    // Create a list of all the subviews that we are going to use for layout.
    NSMutableArray<UIView *> *subviewsToInclude = [[NSMutableArray alloc] initWithCapacity:view.subviews.count];
    for (UIView *subview in view.subviews) {
      if ([subview yk_includeInLayout]) {
        [subviewsToInclude addObject:subview];
      }
    }

    BOOL shouldReconstructChildList = NO;
    if (YGNodeGetChildCount(node) != subviewsToInclude.count) {
      shouldReconstructChildList = YES;
    } else {
      for (int i = 0; i < subviewsToInclude.count; i++) {
        if (YGNodeGetChild(node, i) != [subviewsToInclude[i] ygNode]) {
          shouldReconstructChildList = YES;
          break;
        }
      }
    }

    if (shouldReconstructChildList) {
      YKRemoveAllChildren(node);

      for (int i = 0 ; i < subviewsToInclude.count; i++) {
        UIView *const subview = subviewsToInclude[i];
        YGNodeInsertChild(node, [subview ygNode], i);
        YKAttachNodesFromViewHierachy(subview);
      }
    }
  }
}

static void YKRemoveAllChildren(const YGNodeRef node)
{
  if (node == NULL) {
      return;
  }

  while (YGNodeGetChildCount(node) > 0) {
    YGNodeRemoveChild(node, YGNodeGetChild(node, YGNodeGetChildCount(node) - 1));
  }
}

static CGFloat YKRoundPixelValue(CGFloat value)
{
  static CGFloat scale;
  static dispatch_once_t onceToken;
  dispatch_once(&onceToken, ^(){
    scale = [UIScreen mainScreen].scale;
  });

  return round(value * scale) / scale;
}

static void YKApplyLayoutToViewHierarchy(UIView *view) {
  NSCAssert([NSThread isMainThread], @"Framesetting should only be done on the main thread.");
  if (![view yk_includeInLayout]) {
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
      .x = YKRoundPixelValue(topLeft.x),
      .y = YKRoundPixelValue(topLeft.y),
    },
    .size = {
      .width = YKRoundPixelValue(bottomRight.x) - YKRoundPixelValue(topLeft.x),
      .height = YKRoundPixelValue(bottomRight.y) - YKRoundPixelValue(topLeft.y),
    },
  };

  const BOOL isLeaf = ![view yk_usesYoga] || view.subviews.count == 0;
  if (!isLeaf) {
    for (NSUInteger i = 0; i < view.subviews.count; i++) {
      YKApplyLayoutToViewHierarchy(view.subviews[i]);
    }
  }
}

@end
