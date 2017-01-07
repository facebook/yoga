/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#import "YGLayout+Private.h"
#import "UIView+Yoga.h"
#import <yoga/Yoga.h>

#define YG_STYLE_PROPERTY_IMPL(type, lowercased_name, capitalized_name) \
- (type)lowercased_name                                                 \
{                                                                       \
  return YGNodeStyleGet##capitalized_name(self.node);                   \
}                                                                       \
                                                                        \
- (void)set##capitalized_name:(type)lowercased_name                     \
{                                                                       \
  YGNodeStyleSet##capitalized_name(self.node, lowercased_name);         \
}

#define YG_STYLE_EDGE_PROPERTY_IMPL(lowercased_name, capitalized_name, property, edge) \
- (CGFloat)lowercased_name {                                                           \
  return YGNodeStyleGet##property(self.node, edge);                                    \
}                                                                                      \
                                                                                       \
- (void)set##capitalized_name:(CGFloat)lowercased_name {                               \
  YGNodeStyleSet##property(self.node, edge, lowercased_name);                          \
}

#define YG_STYLE_VALUE_PROPERTY_IMPL(lowercased_name, capitalized_name) \
- (CGFloat)lowercased_name                                              \
{                                                                       \
  YGValue value = YGNodeStyleGet##capitalized_name(self.node);          \
  if (value.unit == YGUnitPixel) {                                      \
    return value.value;                                                 \
  } else {                                                              \
    return YGUndefined;                                                 \
  }                                                                     \
}                                                                       \
                                                                        \
- (void)set##capitalized_name:(CGFloat)lowercased_name                  \
{                                                                       \
  YGNodeStyleSet##capitalized_name(self.node, lowercased_name);         \
}

#define YG_STYLE_EDGE_PROPERTY_UNIT_IMPL(lowercased_name, capitalized_name, edge, edge_suffix) \
- (CGFloat)lowercased_name##edge_suffix                                                        \
{                                                                                              \
  YGValue value = YGNodeStyleGet##capitalized_name(self.node, edge);                           \
  if (value.unit == YGUnitPixel) {                                                             \
    return value.value;                                                                        \
  } else {                                                                                     \
    return YGUndefined;                                                                        \
  }                                                                                            \
}                                                                                              \
                                                                                               \
- (void)set##capitalized_name##edge_suffix:(CGFloat)lowercased_name                            \
{                                                                                              \
  YGNodeStyleSet##capitalized_name(self.node, edge, lowercased_name);                          \
}

#define YG_STYLE_ALL_EDGE_PROPERTY_UNIT_IMPL(lowercased_name, capitalized_name)                   \
YG_STYLE_EDGE_PROPERTY_UNIT_IMPL(lowercased_name, capitalized_name, YGEdgeLeft, Left)             \
YG_STYLE_EDGE_PROPERTY_UNIT_IMPL(lowercased_name, capitalized_name, YGEdgeTop, Top)               \
YG_STYLE_EDGE_PROPERTY_UNIT_IMPL(lowercased_name, capitalized_name, YGEdgeRight, Right)           \
YG_STYLE_EDGE_PROPERTY_UNIT_IMPL(lowercased_name, capitalized_name, YGEdgeBottom, Bottom)         \
YG_STYLE_EDGE_PROPERTY_UNIT_IMPL(lowercased_name, capitalized_name, YGEdgeStart, Start)           \
YG_STYLE_EDGE_PROPERTY_UNIT_IMPL(lowercased_name, capitalized_name, YGEdgeEnd, End)               \
YG_STYLE_EDGE_PROPERTY_UNIT_IMPL(lowercased_name, capitalized_name, YGEdgeHorizontal, Horizontal) \
YG_STYLE_EDGE_PROPERTY_UNIT_IMPL(lowercased_name, capitalized_name, YGEdgeVertical, Vertical)     \
YG_STYLE_EDGE_PROPERTY_UNIT_IMPL(lowercased_name, capitalized_name, YGEdgeAll, )

@interface YGLayout ()

@property (nonatomic, weak, readonly) UIView *view;
@property (nonatomic, assign, readonly) YGNodeRef node;

@end

@implementation YGLayout

@synthesize isEnabled=_isEnabled;
@synthesize isIncludedInLayout=_isIncludedInLayout;

+ (void)initialize
{
  YGSetExperimentalFeatureEnabled(YGExperimentalFeatureWebFlexBasis, true);
}

- (instancetype)initWithView:(UIView*)view
{
  if (self = [super init]) {
    _view = view;
    _node = YGNodeNew();
    YGNodeSetContext(_node, (__bridge void *) view);
    _isEnabled = NO;
    _isIncludedInLayout = YES;
  }

  return self;
}

- (void)dealloc
{
  YGNodeFree(self.node);
}

- (void)markDirty
{
  if (self.isLeaf) {
    YGNodeMarkDirty(self.node);
  }
}

- (NSUInteger)numberOfChildren
{
  return YGNodeGetChildCount(self.node);
}

- (BOOL)isLeaf
{
  NSAssert([NSThread isMainThread], @"This method must be called on the main thread.");
  if (self.isEnabled) {
    for (UIView *subview in self.view.subviews) {
      YGLayout *const yoga = subview.yoga;
      if (yoga.isEnabled && yoga.isIncludedInLayout) {
        return NO;
      }
    }
  }

  return YES;
}

#pragma mark - Style

- (YGPositionType)position
{
  return YGNodeStyleGetPositionType(self.node);
}

- (void)setPosition:(YGPositionType)position
{
  YGNodeStyleSetPositionType(self.node, position);
}

YG_STYLE_PROPERTY_IMPL(YGDirection, direction, Direction)
YG_STYLE_PROPERTY_IMPL(YGFlexDirection, flexDirection, FlexDirection)
YG_STYLE_PROPERTY_IMPL(YGJustify, justifyContent, JustifyContent)
YG_STYLE_PROPERTY_IMPL(YGAlign, alignContent, AlignContent)
YG_STYLE_PROPERTY_IMPL(YGAlign, alignItems, AlignItems)
YG_STYLE_PROPERTY_IMPL(YGAlign, alignSelf, AlignSelf)
YG_STYLE_PROPERTY_IMPL(YGWrap, flexWrap, FlexWrap)
YG_STYLE_PROPERTY_IMPL(YGOverflow, overflow, Overflow)

YG_STYLE_PROPERTY_IMPL(CGFloat, flexGrow, FlexGrow)
YG_STYLE_PROPERTY_IMPL(CGFloat, flexShrink, FlexShrink)
YG_STYLE_VALUE_PROPERTY_IMPL(flexBasis, FlexBasis)

YG_STYLE_EDGE_PROPERTY_UNIT_IMPL(position, Position, YGEdgeLeft, Left)
YG_STYLE_EDGE_PROPERTY_UNIT_IMPL(position, Position, YGEdgeTop, Top)
YG_STYLE_EDGE_PROPERTY_UNIT_IMPL(position, Position, YGEdgeRight, Right)
YG_STYLE_EDGE_PROPERTY_UNIT_IMPL(position, Position, YGEdgeBottom, Bottom)
YG_STYLE_EDGE_PROPERTY_UNIT_IMPL(position, Position, YGEdgeStart, Start)
YG_STYLE_EDGE_PROPERTY_UNIT_IMPL(position, Position, YGEdgeEnd, End)
YG_STYLE_ALL_EDGE_PROPERTY_UNIT_IMPL(margin, Margin)
YG_STYLE_ALL_EDGE_PROPERTY_UNIT_IMPL(padding, Padding)

YG_STYLE_EDGE_PROPERTY_IMPL(borderLeftWidth, BorderLeftWidth, Border, YGEdgeLeft)
YG_STYLE_EDGE_PROPERTY_IMPL(borderTopWidth, BorderTopWidth, Border, YGEdgeTop)
YG_STYLE_EDGE_PROPERTY_IMPL(borderRightWidth, BorderRightWidth, Border, YGEdgeRight)
YG_STYLE_EDGE_PROPERTY_IMPL(borderBottomWidth, BorderBottomWidth, Border, YGEdgeBottom)
YG_STYLE_EDGE_PROPERTY_IMPL(borderStartWidth, BorderStartWidth, Border, YGEdgeStart)
YG_STYLE_EDGE_PROPERTY_IMPL(borderEndWidth, BorderEndWidth, Border, YGEdgeEnd)
YG_STYLE_EDGE_PROPERTY_IMPL(borderWidth, BorderWidth, Border, YGEdgeAll)

YG_STYLE_VALUE_PROPERTY_IMPL(width, Width)
YG_STYLE_VALUE_PROPERTY_IMPL(height, Height)
YG_STYLE_VALUE_PROPERTY_IMPL(minWidth, MinWidth)
YG_STYLE_VALUE_PROPERTY_IMPL(minHeight, MinHeight)
YG_STYLE_VALUE_PROPERTY_IMPL(maxWidth, MaxWidth)
YG_STYLE_VALUE_PROPERTY_IMPL(maxHeight, MaxHeight)
YG_STYLE_PROPERTY_IMPL(CGFloat, aspectRatio, AspectRatio)

#pragma mark - Layout and Sizing

- (YGDirection)resolvedDirection
{
  return YGNodeLayoutGetDirection(self.node);
}

- (void)applyLayout
{
  [self calculateLayoutWithSize:self.view.bounds.size];
  YGApplyLayoutToViewHierarchy(self.view);
}

- (CGSize)intrinsicSize
{
  const CGSize constrainedSize = {
    .width = YGUndefined,
    .height = YGUndefined,
  };
  return [self calculateLayoutWithSize:constrainedSize];
}

#pragma mark - Private

- (CGSize)calculateLayoutWithSize:(CGSize)size
{
  NSAssert([NSThread isMainThread], @"Yoga calculation must be done on main.");
  NSAssert(self.isEnabled, @"Yoga is not enabled for this view.");

  YGAttachNodesFromViewHierachy(self.view);

  const YGNodeRef node = self.node;
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
    if (YGNodeGetChild(node, i) != subviews[i].yoga.node) {
      return NO;
    }
  }

  return YES;
}

static void YGAttachNodesFromViewHierachy(UIView *const view)
{
  YGLayout *const yoga = view.yoga;
  const YGNodeRef node = yoga.node;

  // Only leaf nodes should have a measure function
  if (yoga.isLeaf) {
    YGRemoveAllChildren(node);
    YGNodeSetMeasureFunc(node, YGMeasureView);
  } else {
    YGNodeSetMeasureFunc(node, NULL);

    NSMutableArray<UIView *> *subviewsToInclude = [[NSMutableArray alloc] initWithCapacity:view.subviews.count];
    for (UIView *subview in view.subviews) {
      if (subview.yoga.isIncludedInLayout) {
        [subviewsToInclude addObject:subview];
      }
    }

    if (!YGNodeHasExactSameChildren(node, subviewsToInclude)) {
      YGRemoveAllChildren(node);
      for (int i=0; i<subviewsToInclude.count; i++) {
        YGNodeInsertChild(node, subviewsToInclude[i].yoga.node, i);
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

  const YGLayout *yoga = view.yoga;

  if (!yoga.isIncludedInLayout) {
     return;
  }

  YGNodeRef node = yoga.node;
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

  if (!yoga.isLeaf) {
    for (NSUInteger i=0; i<view.subviews.count; i++) {
      YGApplyLayoutToViewHierarchy(view.subviews[i]);
    }
  }
}

@end
