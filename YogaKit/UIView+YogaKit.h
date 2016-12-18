/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#import <UIKit/UIKit.h>
#import "YKEnums.h"

@interface UIView (YogaKit)

/**
  The property that decides if we should include this view when calculating layout. Defaults to YES.
 */
@property (nonatomic, readwrite, assign, setter=yk_setIncludeInLayout:) BOOL yk_includeInLayout;

/**
 The property that decides during layout/sizing whether or not yk_* properties should be applied. Defaults to NO.
 */
@property (nonatomic, readwrite, assign, setter=yk_setUsesYoga:) BOOL yk_usesYoga;

- (void)yk_setDirection:(YKDirection)direction;
- (void)yk_setFlexDirection:(YKFlexDirection)flexDirection;
- (void)yk_setJustifyContent:(YKJustify)justifyContent;
- (void)yk_setAlignContent:(YKAlign)alignContent;
- (void)yk_setAlignItems:(YKAlign)alignItems;
- (void)yk_setAlignSelf:(YKAlign)alignSelf;
- (void)yk_setPositionType:(YKPositionType)positionType;
- (void)yk_setFlexWrap:(YKWrap)flexWrap;

- (void)yk_setFlexGrow:(CGFloat)flexGrow;
- (void)yk_setFlexShrink:(CGFloat)flexShrink;
- (void)yk_setFlexBasis:(CGFloat)flexBasis;

- (void)yk_setPosition:(CGFloat)position forEdge:(YKEdge)edge;
- (void)yk_setMargin:(CGFloat)margin forEdge:(YKEdge)edge;
- (void)yk_setPadding:(CGFloat)padding forEdge:(YKEdge)edge;

- (void)yk_setWidth:(CGFloat)width;
- (void)yk_setHeight:(CGFloat)height;
- (void)yk_setMinWidth:(CGFloat)minWidth;
- (void)yk_setMinHeight:(CGFloat)minHeight;
- (void)yk_setMaxWidth:(CGFloat)maxWidth;
- (void)yk_setMaxHeight:(CGFloat)maxHeight;

// Yoga specific properties, not compatible with flexbox specification
- (void)yk_setAspectRatio:(CGFloat)aspectRatio;

/**
 Get the resolved direction of this node. This won't be YGDirectionInherit
 */
- (YKDirection)yk_resolvedDirection;

/**
 Perform a layout calculation and update the frames of the views in the hierarchy with the results
 */
- (void)yk_applyLayout;

/**
 Returns the size of the view if no constraints were given. This could equivalent to calling [self sizeThatFits:CGSizeMake(CGFLOAT_MAX, CGFLOAT_MAX)];
 */
- (CGSize)yk_intrinsicSize;

/**
 Returns the number of children that are using Flexbox.
 */
- (NSUInteger)yk_numberOfChildren;

@end
