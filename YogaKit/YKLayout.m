/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#import <UIKit/UIKit.h>
#import <YogaKit/UIView+YogaKit.h>
#import <YogaKit/YKLayout.h>
#import <YogaKit/yoga.h>

#define YK_STYLE_PROPERTY_IMPL(objc_type, c_type, lowercased_name, capitalized_name) \
- (objc_type)lowercased_name                                                         \
{                                                                                    \
return (objc_type)YGNodeStyleGet##capitalized_name(_node);                         \
}                                                                                    \
\
- (void)set##capitalized_name:(objc_type)lowercased_name                             \
{                                                                                    \
YGNodeStyleSet##capitalized_name(_node, (c_type)lowercased_name);                  \
}

#define _YK_STYLE_EDGE_PROPERTY_IMPL(lowercased_name, capitalized_name, edge)        \
- (CGFloat)lowercased_name##edge                                                     \
{                                                                                    \
return YGNodeStyleGet##capitalized_name(_node, YGEdge##edge);                      \
}                                                                                    \
\
- (void)set##capitalized_name##edge:(CGFloat)lowercased_name##edge                   \
{                                                                                    \
YGNodeStyleSet##capitalized_name(_node, YGEdge##edge, lowercased_name##edge);      \
}

#define YK_STYLE_EDGE_PROPERTY_IMPL(lowercased_name, capitalized_name)               \
_YK_STYLE_EDGE_PROPERTY_IMPL(lowercased_name, capitalized_name, Left)                \
_YK_STYLE_EDGE_PROPERTY_IMPL(lowercased_name, capitalized_name, Top)                 \
_YK_STYLE_EDGE_PROPERTY_IMPL(lowercased_name, capitalized_name, Right)               \
_YK_STYLE_EDGE_PROPERTY_IMPL(lowercased_name, capitalized_name, Bottom)              \
_YK_STYLE_EDGE_PROPERTY_IMPL(lowercased_name, capitalized_name, Start)               \
_YK_STYLE_EDGE_PROPERTY_IMPL(lowercased_name, capitalized_name, End)                 \
_YK_STYLE_EDGE_PROPERTY_IMPL(lowercased_name, capitalized_name, Horizontal)          \
_YK_STYLE_EDGE_PROPERTY_IMPL(lowercased_name, capitalized_name, Vertical)            \
_YK_STYLE_EDGE_PROPERTY_IMPL(lowercased_name, capitalized_name, All)

@interface YKLayout ()
@property (nonatomic, weak, readonly) UIView* view;
@property (nonatomic, assign, readonly) YGNodeRef node;
@end

@implementation YKLayout

@synthesize isEnabled=_isEnabled;
@synthesize isIncluded=_isIncluded;

+ (void)initialize
{
  YGSetExperimentalFeatureEnabled(YGExperimentalFeatureWebFlexBasis, true);
}

- (instancetype)initWithView:(UIView*)view
{
  if ([super init]) {
    _view = view;
    _node = YGNodeNew();
    YGNodeSetContext(_node, (__bridge void *) view);
    _isEnabled = NO;
    _isIncluded = YES;
  }
  
  return self;
}

- (void)dealloc
{
  YGNodeFree(_node);
}

- (NSUInteger)numberOfChildren
{
  return YGNodeGetChildCount(_node);
}

YK_STYLE_PROPERTY_IMPL(YKDirection, YGDirection, direction, Direction)
YK_STYLE_PROPERTY_IMPL(YKFlexDirection, YGFlexDirection, flexDirection, FlexDirection)
YK_STYLE_PROPERTY_IMPL(YKJustify, YGJustify, justifyContent, JustifyContent)
YK_STYLE_PROPERTY_IMPL(YKAlign, YGAlign, alignContent, AlignContent)
YK_STYLE_PROPERTY_IMPL(YKAlign, YGAlign, alignItems, AlignItems)
YK_STYLE_PROPERTY_IMPL(YKAlign, YGAlign, alignSelf, AlignSelf)
YK_STYLE_PROPERTY_IMPL(YKPositionType, YGPositionType, positionType, PositionType)
YK_STYLE_PROPERTY_IMPL(YKWrap, YGWrap, flexWrap, FlexWrap)
YK_STYLE_PROPERTY_IMPL(CGFloat, CGFloat, flexGrow, FlexGrow)
YK_STYLE_PROPERTY_IMPL(CGFloat, CGFloat, flexShrink, FlexShrink)
YK_STYLE_PROPERTY_IMPL(CGFloat, CGFloat, flexBasis, FlexBasis)
YK_STYLE_EDGE_PROPERTY_IMPL(position, Position)
YK_STYLE_EDGE_PROPERTY_IMPL(margin, Margin)
YK_STYLE_EDGE_PROPERTY_IMPL(padding, Padding)
YK_STYLE_PROPERTY_IMPL(CGFloat, CGFloat, width, Width)
YK_STYLE_PROPERTY_IMPL(CGFloat, CGFloat, height, Height)
YK_STYLE_PROPERTY_IMPL(CGFloat, CGFloat, minWidth, MinWidth)
YK_STYLE_PROPERTY_IMPL(CGFloat, CGFloat, minHeight, MinHeight)
YK_STYLE_PROPERTY_IMPL(CGFloat, CGFloat, maxWidth, MaxWidth)
YK_STYLE_PROPERTY_IMPL(CGFloat, CGFloat, maxHeight, MaxHeight)
YK_STYLE_PROPERTY_IMPL(CGFloat, CGFloat, aspectRatio, AspectRatio)

#pragma mark - Layout and Sizing

- (YKDirection)resolvedDirection
{
  return (YKDirection)YGNodeLayoutGetDirection(_node);
}

- (void)apply
{
  [self calculateLayoutWithSize:self.view.bounds.size];
  YKApplyLayoutToViewHierarchy(self);
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
  NSAssert([NSThread isMainThread], @"YG Layout calculation must be done on main.");
  NSAssert([self isEnabled], @"YG Layout is not enabled for this view.");
  
  YKAttachNodesFromViewHierachy(self);
  
  const YGNodeRef node = _node;
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

static void YKAttachNodesFromViewHierachy(YKLayout *layout) {
  YGNodeRef node = layout.node;
  UIView *view = layout.view;
  
  // Only leaf nodes should have a measure function
  if (![layout isEnabled] || view.subviews.count == 0) {
    YGNodeSetMeasureFunc(node, YKMeasureView);
    YKRemoveAllChildren(node);
  } else {
    YGNodeSetMeasureFunc(node, NULL);
    
    // Create a list of all the subviews that we are going to use for layout.
    NSMutableArray<UIView *> *subviewsToInclude = [[NSMutableArray alloc] initWithCapacity:view.subviews.count];
    for (UIView *subview in view.subviews) {
      if (subview.layout.isIncluded) {
        [subviewsToInclude addObject:subview];
      }
    }
    
    BOOL shouldReconstructChildList = NO;
    if (YGNodeGetChildCount(node) != subviewsToInclude.count) {
      shouldReconstructChildList = YES;
    } else {
      for (int i = 0; i < subviewsToInclude.count; i++) {
        if (YGNodeGetChild(node, i) != subviewsToInclude[i].layout.node) {
          shouldReconstructChildList = YES;
          break;
        }
      }
    }
    
    if (shouldReconstructChildList) {
      YKRemoveAllChildren(node);
      
      for (int i = 0 ; i < subviewsToInclude.count; i++) {
        UIView *const subview = subviewsToInclude[i];
        YGNodeInsertChild(node, subview.layout.node, i);
        YKAttachNodesFromViewHierachy(subview.layout);
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

static void YKApplyLayoutToViewHierarchy(YKLayout *layout) {
  NSCAssert([NSThread isMainThread], @"Framesetting should only be done on the main thread.");
  
  if (!layout.isIncluded) {
    return;
  }
  
  YGNodeRef node = layout.node;
  const CGPoint topLeft = {
    YGNodeLayoutGetLeft(node),
    YGNodeLayoutGetTop(node),
  };
  
  const CGPoint bottomRight = {
    topLeft.x + YGNodeLayoutGetWidth(node),
    topLeft.y + YGNodeLayoutGetHeight(node),
  };
  
  UIView *view = layout.view;
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
  
  const BOOL isLeaf = !layout.isEnabled || view.subviews.count == 0;
  if (!isLeaf) {
    for (NSUInteger i = 0; i < view.subviews.count; i++) {
      YKApplyLayoutToViewHierarchy(view.subviews[i].layout);
    }
  }
}

@end
