/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#import <UIKit/UIKit.h>
#import <yoga/Yoga.h>

@interface UIView (Yoga)

/**
  The property that decides if we should include this view when calculating layout. Defaults to YES.
 */
@property (nonatomic, readwrite, assign, setter=yg_setIncludeInLayout:) BOOL yg_includeInLayout;

/**
 The property that decides during layout/sizing whether or not yg_* properties should be applied. Defaults to NO.
 */
@property (nonatomic, readwrite, assign, setter=yg_setUsesYoga:) BOOL yg_usesYoga;

- (void)yg_setDirection:(YGDirection)direction;
- (void)yg_setFlexDirection:(YGFlexDirection)flexDirection;
- (void)yg_setJustifyContent:(YGJustify)justifyContent;
- (void)yg_setAlignContent:(YGAlign)alignContent;
- (void)yg_setAlignItems:(YGAlign)alignItems;
- (void)yg_setAlignSelf:(YGAlign)alignSelf;
- (void)yg_setPositionType:(YGPositionType)positionType;
- (void)yg_setFlexWrap:(YGWrap)flexWrap;

- (void)yg_setFlexGrow:(CGFloat)flexGrow;
- (void)yg_setFlexShrink:(CGFloat)flexShrink;
- (void)yg_setFlexBasis:(CGFloat)flexBasis;

- (void)yg_setPosition:(CGFloat)position forEdge:(YGEdge)edge;
- (void)yg_setMargin:(CGFloat)margin forEdge:(YGEdge)edge;
- (void)yg_setPadding:(CGFloat)padding forEdge:(YGEdge)edge;

- (void)yg_setWidth:(CGFloat)width;
- (void)yg_setHeight:(CGFloat)height;
- (void)yg_setMinWidth:(CGFloat)minWidth;
- (void)yg_setMinHeight:(CGFloat)minHeight;
- (void)yg_setMaxWidth:(CGFloat)maxWidth;
- (void)yg_setMaxHeight:(CGFloat)maxHeight;

// Yoga specific properties, not compatible with flexbox specification
- (void)yg_setAspectRatio:(CGFloat)aspectRatio;

/**
 Get the resolved direction of this node. This won't be YGDirectionInherit
 */
- (YGDirection)yg_resolvedDirection;

/**
 Perform a layout calculation and update the frames of the views in the hierarchy with the results
 */
- (void)yg_applyLayout;

/**
 Returns the size of the view if no constraints were given. This could equivalent to calling [self sizeThatFits:CGSizeMake(CGFLOAT_MAX, CGFLOAT_MAX)];
 */
- (CGSize)yg_intrinsicSize;

/**
 Returns the number of children that are using Flexbox.
 */
- (NSUInteger)yg_numberOfChildren;

@end
