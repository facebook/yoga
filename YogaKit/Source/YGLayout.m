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

#define YG_PROPERTY(type, lowercased_name, capitalized_name)    \
- (type)lowercased_name                                         \
{                                                               \
  return YGNodeStyleGet##capitalized_name(_node);               \
}                                                               \
                                                                \
- (void)set##capitalized_name:(type)lowercased_name             \
{                                                               \
  YGNodeStyleSet##capitalized_name(_node, lowercased_name);     \
}

#define YG_VALUE_PROPERTY(lowercased_name, capitalized_name)                       \
- (YGValue)lowercased_name                                                         \
{                                                                                  \
  return YGNodeStyleGet##capitalized_name(_node);                                  \
}                                                                                  \
                                                                                   \
- (void)set##capitalized_name:(YGValue)lowercased_name                             \
{                                                                                  \
  switch (lowercased_name.unit) {                                                  \
    case YGUnitPoint:                                                              \
      YGNodeStyleSet##capitalized_name(_node, lowercased_name.value);              \
      break;                                                                       \
    case YGUnitPercent:                                                            \
      YGNodeStyleSet##capitalized_name##Percent(_node, lowercased_name.value);     \
      break;                                                                       \
    default:                                                                       \
      NSAssert(NO, @"Not implemented");                                            \
  }                                                                                \
}

#define YG_EDGE_PROPERTY_GETTER(type, lowercased_name, capitalized_name, property, edge) \
- (type)lowercased_name                                                                  \
{                                                                                        \
  return YGNodeStyleGet##property(_node, edge);                                          \
}

#define YG_EDGE_PROPERTY_SETTER(lowercased_name, capitalized_name, property, edge) \
- (void)set##capitalized_name:(CGFloat)lowercased_name                             \
{                                                                                  \
  YGNodeStyleSet##property(_node, edge, lowercased_name);                          \
}

#define YG_EDGE_PROPERTY(lowercased_name, capitalized_name, property, edge)         \
YG_EDGE_PROPERTY_GETTER(CGFloat, lowercased_name, capitalized_name, property, edge) \
YG_EDGE_PROPERTY_SETTER(lowercased_name, capitalized_name, property, edge)

#define YG_VALUE_EDGE_PROPERTY_SETTER(objc_lowercased_name, objc_capitalized_name, c_name, edge) \
- (void)set##objc_capitalized_name:(YGValue)objc_lowercased_name                                 \
{                                                                                                \
  switch (objc_lowercased_name.unit) {                                                           \
    case YGUnitPoint:                                                                            \
      YGNodeStyleSet##c_name(_node, edge, objc_lowercased_name.value);                           \
      break;                                                                                     \
    case YGUnitPercent:                                                                          \
      YGNodeStyleSet##c_name##Percent(_node, edge, objc_lowercased_name.value);                  \
      break;                                                                                     \
    default:                                                                                     \
      NSAssert(NO, @"Not implemented");                                                          \
  }                                                                                              \
}

#define YG_VALUE_EDGE_PROPERTY(lowercased_name, capitalized_name, property, edge)   \
YG_EDGE_PROPERTY_GETTER(YGValue, lowercased_name, capitalized_name, property, edge) \
YG_VALUE_EDGE_PROPERTY_SETTER(lowercased_name, capitalized_name, property, edge)

#define YG_VALUE_EDGES_PROPERTIES(lowercased_name, capitalized_name)                                                  \
YG_VALUE_EDGE_PROPERTY(lowercased_name##Left, capitalized_name##Left, capitalized_name, YGEdgeLeft)                   \
YG_VALUE_EDGE_PROPERTY(lowercased_name##Top, capitalized_name##Top, capitalized_name, YGEdgeTop)                      \
YG_VALUE_EDGE_PROPERTY(lowercased_name##Right, capitalized_name##Right, capitalized_name, YGEdgeRight)                \
YG_VALUE_EDGE_PROPERTY(lowercased_name##Bottom, capitalized_name##Bottom, capitalized_name, YGEdgeBottom)             \
YG_VALUE_EDGE_PROPERTY(lowercased_name##Start, capitalized_name##Start, capitalized_name, YGEdgeStart)                \
YG_VALUE_EDGE_PROPERTY(lowercased_name##End, capitalized_name##End, capitalized_name, YGEdgeEnd)                      \
YG_VALUE_EDGE_PROPERTY(lowercased_name##Horizontal, capitalized_name##Horizontal, capitalized_name, YGEdgeHorizontal) \
YG_VALUE_EDGE_PROPERTY(lowercased_name##Vertical, capitalized_name##Vertical, capitalized_name, YGEdgeVertical)       \
YG_VALUE_EDGE_PROPERTY(lowercased_name, capitalized_name, capitalized_name, YGEdgeAll)

YGValue YGPointValue(CGFloat value)
{
  return (YGValue) { .value = value, .unit = YGUnitPoint };
}
YGValue YGPercentValue(CGFloat value)
{
  return (YGValue) { .value = value, .unit = YGUnitPercent };
}

static YGConfigRef globalConfig;

@implementation YGLayout {
    @public
    YGNodeRef _node;
    id<YGLayoutEntity> _entity;
}

@synthesize isEnabled=_isEnabled;
@synthesize isIncludedInLayout=_isIncludedInLayout;

+ (void)initialize
{
  globalConfig = YGConfigNew();
  YGConfigSetExperimentalFeatureEnabled(globalConfig, YGExperimentalFeatureWebFlexBasis, true);
  YGConfigSetPointScaleFactor(globalConfig, [UIScreen mainScreen].scale);
}

- (instancetype)init
{
  return [self initWithEntity:nil];
}
- (instancetype)initWithEntity:(id<YGLayoutEntity>)entity
{
  NSParameterAssert(entity);
  if (self = [super init]) {
    _entity = entity;
    _node = YGNodeNewWithConfig(globalConfig);
    YGNodeSetContext(_node, (__bridge void *) entity);
    _isEnabled = NO;
    _isIncludedInLayout = YES;
  }

  return self;
}

- (void)dealloc
{
  YGNodeFree(_node);
}

- (BOOL)isDirty
{
  return YGNodeIsDirty(_node);
}

- (void)markDirty
{
  if (self.isDirty || !self.isLeaf) {
    return;
  }

  // Yoga is not happy if we try to mark a node as "dirty" before we have set
  // the measure function. Since we already know that this is a leaf,
  // this *should* be fine. Forgive me Hack Gods.
  if (YGNodeGetMeasureFunc(_node) == NULL) {
    YGNodeSetMeasureFunc(_node, YGMeasureEntity);
  }
  YGNodeMarkDirty(_node);
}

- (NSUInteger)numberOfChildren
{
  return YGNodeGetChildCount(_node);
}

- (BOOL)isLeaf
{
  NSAssert([NSThread isMainThread], @"This method must be called on the main thread.");
  if (self.isEnabled) {
    for (id<YGLayoutEntity> subEntity in _entity.subEntities) {
      YGLayout *const yoga = subEntity.yoga;
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
  return YGNodeStyleGetPositionType(_node);
}

- (void)setPosition:(YGPositionType)position
{
  YGNodeStyleSetPositionType(_node, position);
}

YG_PROPERTY(YGDirection, direction, Direction)
YG_PROPERTY(YGFlexDirection, flexDirection, FlexDirection)
YG_PROPERTY(YGJustify, justifyContent, JustifyContent)
YG_PROPERTY(YGAlign, alignContent, AlignContent)
YG_PROPERTY(YGAlign, alignItems, AlignItems)
YG_PROPERTY(YGAlign, alignSelf, AlignSelf)
YG_PROPERTY(YGWrap, flexWrap, FlexWrap)
YG_PROPERTY(YGOverflow, overflow, Overflow)
YG_PROPERTY(YGDisplay, display, Display)

YG_PROPERTY(CGFloat, flexGrow, FlexGrow)
YG_PROPERTY(CGFloat, flexShrink, FlexShrink)
YG_VALUE_PROPERTY(flexBasis, FlexBasis)

YG_VALUE_EDGE_PROPERTY(left, Left, Position, YGEdgeLeft)
YG_VALUE_EDGE_PROPERTY(top, Top, Position, YGEdgeTop)
YG_VALUE_EDGE_PROPERTY(right, Right, Position, YGEdgeRight)
YG_VALUE_EDGE_PROPERTY(bottom, Bottom, Position, YGEdgeBottom)
YG_VALUE_EDGE_PROPERTY(start, Start, Position, YGEdgeStart)
YG_VALUE_EDGE_PROPERTY(end, End, Position, YGEdgeEnd)
YG_VALUE_EDGES_PROPERTIES(margin, Margin)
YG_VALUE_EDGES_PROPERTIES(padding, Padding)

YG_EDGE_PROPERTY(borderLeftWidth, BorderLeftWidth, Border, YGEdgeLeft)
YG_EDGE_PROPERTY(borderTopWidth, BorderTopWidth, Border, YGEdgeTop)
YG_EDGE_PROPERTY(borderRightWidth, BorderRightWidth, Border, YGEdgeRight)
YG_EDGE_PROPERTY(borderBottomWidth, BorderBottomWidth, Border, YGEdgeBottom)
YG_EDGE_PROPERTY(borderStartWidth, BorderStartWidth, Border, YGEdgeStart)
YG_EDGE_PROPERTY(borderEndWidth, BorderEndWidth, Border, YGEdgeEnd)
YG_EDGE_PROPERTY(borderWidth, BorderWidth, Border, YGEdgeAll)

YG_VALUE_PROPERTY(width, Width)
YG_VALUE_PROPERTY(height, Height)
YG_VALUE_PROPERTY(minWidth, MinWidth)
YG_VALUE_PROPERTY(minHeight, MinHeight)
YG_VALUE_PROPERTY(maxWidth, MaxWidth)
YG_VALUE_PROPERTY(maxHeight, MaxHeight)
YG_PROPERTY(CGFloat, aspectRatio, AspectRatio)

#pragma mark - Layout and Sizing

- (YGDirection)resolvedDirection
{
  return YGNodeLayoutGetDirection(_node);
}

- (void)applyLayout
{
  [self calculateLayoutWithSize:_entity.frame.size];
  YGApplyLayoutToHierarchy(_entity, NO, CGPointZero);
}

- (void)applyLayoutPreservingOrigin:(BOOL)preserveOrigin
{
  [self calculateLayoutWithSize:_entity.frame.size];
  YGApplyLayoutToHierarchy(_entity, preserveOrigin, CGPointZero);
}

- (void)applyLayoutPreservingOrigin:(BOOL)preserveOrigin dimensionFlexibility:(YGDimensionFlexibility)dimensionFlexibility
{
  CGSize size = _entity.frame.size;
  if (dimensionFlexibility & YGDimensionFlexibilityFlexibleWidth) {
    size.width = YGUndefined;
  }
  if (dimensionFlexibility & YGDimensionFlexibilityFlexibleHeigth) {
    size.height = YGUndefined;
  }
  [self calculateLayoutWithSize:size];
  YGApplyLayoutToHierarchy(_entity, preserveOrigin, CGPointZero);
}

- (CGSize)intrinsicSize
{
  const CGSize constrainedSize = {
    .width = YGUndefined,
    .height = YGUndefined,
  };
  return [self calculateLayoutWithSize:constrainedSize];
}

- (CGSize)calculateLayoutWithSize:(CGSize)size
{
  NSAssert([NSThread isMainThread], @"Yoga calculation must be done on main.");
  NSAssert(self.isEnabled, @"Yoga is not enabled for %@", self);

  YGAttachNodesFromHierachy(_entity);

  YGNodeCalculateLayout(
    _node,
    size.width,
    size.height,
    YGNodeStyleGetDirection(_node));

  return (CGSize) {
    .width = YGNodeLayoutGetWidth(_node),
    .height = YGNodeLayoutGetHeight(_node),
  };
}

#pragma mark - Private

static YGSize YGMeasureEntity(
  YGNodeRef node,
  float width,
  YGMeasureMode widthMode,
  float height,
  YGMeasureMode heightMode)
{
  const CGFloat constrainedWidth = (widthMode == YGMeasureModeUndefined) ? CGFLOAT_MAX : width;
  const CGFloat constrainedHeight = (heightMode == YGMeasureModeUndefined) ? CGFLOAT_MAX: height;

  id<YGLayoutEntity> entity = (__bridge id<YGLayoutEntity>) YGNodeGetContext(node);
  const CGSize sizeThatFits = [entity sizeThatFits:(CGSize) {
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

static BOOL YGNodeHasExactSameChildren(const YGNodeRef node, NSArray<id<YGLayoutEntity>> *subEntities)
{
  if (YGNodeGetChildCount(node) != subEntities.count) {
    return NO;
  }

  for (int i=0; i<subEntities.count; i++) {
    YGLayout *subLayout = subEntities[i].yoga;
    if (subLayout && YGNodeGetChild(node, i) != subLayout->_node) {
      return NO;
    }
  }

  return YES;
}

static void YGAttachNodesFromHierachy(id<YGLayoutEntity> const entity)
{
  YGLayout *const yoga = entity.yoga;
  const YGNodeRef node = yoga ? yoga->_node : NULL;

  // Only leaf nodes should have a measure function
  if (yoga.isLeaf) {
    YGRemoveAllChildren(node);
    YGNodeSetMeasureFunc(node, YGMeasureEntity);
  } else {
    YGNodeSetMeasureFunc(node, NULL);

    NSMutableArray<id<YGLayoutEntity>> *subEntitiesToInclude = [[NSMutableArray alloc] initWithCapacity:entity.subEntities.count];
    for (id<YGLayoutEntity> subEntity in entity.subEntities) {
      if (subEntity.yoga.isIncludedInLayout) {
        [subEntitiesToInclude addObject:subEntity];
      }
    }

    if (!YGNodeHasExactSameChildren(node, subEntitiesToInclude)) {
      YGRemoveAllChildren(node);
      for (int i=0; i<subEntitiesToInclude.count; i++) {
        YGLayout *subLayout = subEntitiesToInclude[i].yoga;
        if (subLayout) {
            if (YGNodeGetParent(subLayout->_node)) {
              YGNodeRemoveChild(YGNodeGetParent(subLayout->_node),
                                subLayout->_node);
            }
            YGNodeInsertChild(node, subLayout->_node, i);
        }
      }
    }

    for (id<YGLayoutEntity> const subEntity in subEntitiesToInclude) {
      YGAttachNodesFromHierachy(subEntity);
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

  return roundf(value * scale) / scale;
}

static void YGApplyLayoutToHierarchy(id<YGLayoutEntity> entity, BOOL preserveOrigin, CGPoint offset)
{
  NSCAssert([NSThread isMainThread], @"Framesetting should only be done on the main thread.");

  const YGLayout *yoga = entity.yoga;

  if (!yoga || !yoga.isIncludedInLayout) {
     return;
  }

  const CGPoint topLeft = {
    YGNodeLayoutGetLeft(yoga->_node) + offset.x,
    YGNodeLayoutGetTop(yoga->_node) + offset.y,
  };

  const CGPoint origin = preserveOrigin ? entity.frame.origin : CGPointZero;
  entity.frame = (CGRect) {
    .origin = {
      .x = YGRoundPixelValue(topLeft.x + origin.x),
      .y = YGRoundPixelValue(topLeft.y + origin.y),
    },
    .size = {
      .width = YGNodeLayoutGetWidth(yoga->_node),
      .height = YGNodeLayoutGetHeight(yoga->_node),
    },
  };

  if (!yoga.isLeaf) {
    for (NSUInteger i=0; i<entity.subEntities.count; i++) {
      YGApplyLayoutToHierarchy(entity.subEntities[i],
                               NO,
                               [entity conformsToProtocol:@protocol(UICoordinateSpace)] ? CGPointZero : entity.frame.origin);
    }
  }
}

@end

@implementation YGLayoutContainer
@synthesize frame=_frame;

- (instancetype)init
{
  return [self initWithEntity:self];
}
- (instancetype)initWithEntity:(id<YGLayoutEntity>)entity
{
  if ((self = [super initWithEntity:entity])) {
    self.isEnabled = YES;
  }
  return self;
}

- (YGLayout *)yoga
{
  return self;
}

- (CGSize)sizeThatFits:(CGSize)fitSize
{
  return CGSizeZero;
}

- (BOOL)isEnabled
{
  if (!super.isEnabled) {
    return NO;
  } else {
    for (id<YGLayoutEntity> subEntity in _entity.subEntities) {
      YGLayout *const yoga = subEntity.yoga;
      if (yoga.isEnabled && yoga.isIncludedInLayout) {
        return YES;
      }
    }
    return NO;
  }
}

- (BOOL)isLeaf
{
    return NO;
}
@end
