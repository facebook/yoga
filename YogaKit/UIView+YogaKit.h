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
@property (nonatomic, setter=yk_setIncludeInLayout:) BOOL yk_includeInLayout NS_SWIFT_NAME(includeInLayout);

/**
 The property that decides during layout/sizing whether or not yk_* properties should be applied. Defaults to NO.
 */
@property (nonatomic, setter=yk_setUsesYoga:) BOOL yk_usesYoga NS_SWIFT_NAME(usesYoga);

@property (nonatomic, setter=yk_setDirection:) YKDirection yk_direction NS_SWIFT_NAME(layoutDirection);
@property (nonatomic, setter=yk_setFlexDirection:) YKFlexDirection yk_flexDirection NS_SWIFT_NAME(layoutFlexDirection);
@property (nonatomic, setter=yk_setJustifyContent:) YKJustify yk_justifyContent NS_SWIFT_NAME(layoutJustifyContent);
@property (nonatomic, setter=yk_setAlignContent:) YKAlign yk_alignContent NS_SWIFT_NAME(layoutAlignContent);
@property (nonatomic, setter=yk_setAlignItems:) YKAlign yk_alignItems NS_SWIFT_NAME(layoutAlignItems);
@property (nonatomic, setter=yk_setAlignSelf:) YKAlign yk_alignSelf NS_SWIFT_NAME(layoutAlignSelf);
@property (nonatomic, setter=yk_setPositionType:) YKPositionType yk_positionType NS_SWIFT_NAME(layoutPositionType);
@property (nonatomic, setter=yk_setFlexWrap:) YKWrap yk_flexWrap NS_SWIFT_NAME(layoutFlexWrap);

@property (nonatomic, setter=yk_setFlexGrow:) CGFloat yk_flexGrow NS_SWIFT_NAME(layoutFlexGrow);
@property (nonatomic, setter=yk_setFlexShrink:) CGFloat yk_flexShrink NS_SWIFT_NAME(layoutFlexShrink);
@property (nonatomic, setter=yk_setFlexBasis:) CGFloat yk_flexBasis NS_SWIFT_NAME(layoutFlexBasis);

- (void)yk_positionForEdge:(YKEdge)edge;
- (void)yk_setPosition:(CGFloat)position forEdge:(YKEdge)edge;
- (void)yk_marginForEdge:(YKEdge)edge;
- (void)yk_setMargin:(CGFloat)margin forEdge:(YKEdge)edge;
- (void)yk_paddingForEdge:(YKEdge)edge;
- (void)yk_setPadding:(CGFloat)padding forEdge:(YKEdge)edge;

@property (nonatomic, setter=yk_setWidth:) CGFloat yk_width NS_SWIFT_NAME(layoutWidth);
@property (nonatomic, setter=yk_setHeight:) CGFloat yk_height NS_SWIFT_NAME(layoutHeight);
@property (nonatomic, setter=yk_setMinWidth:) CGFloat yk_minWidth NS_SWIFT_NAME(layoutMinWidth);
@property (nonatomic, setter=yk_setMinHeight:) CGFloat yk_minHeight NS_SWIFT_NAME(layoutMinHeight);
@property (nonatomic, setter=yk_setMaxWidth:) CGFloat yk_maxWidth NS_SWIFT_NAME(layoutMaxWidth);
@property (nonatomic, setter=yk_setMaxHeight:) CGFloat yk_maxHeight NS_SWIFT_NAME(layoutMaxHeight);

// Yoga specific properties, not compatible with flexbox specification
@property (nonatomic, setter=yk_setAspectRatio:) CGFloat yk_aspectRatio NS_SWIFT_NAME(layoutAspectRatio);

/**
 Get the resolved direction of this node. This won't be YGDirectionInherit
 */
@property (nonatomic, readonly) CGFloat yk_resolvedDirection NS_SWIFT_NAME(layoutResolvedDirection);

/**
 Perform a layout calculation and update the frames of the views in the hierarchy with the results
 */
- (void)yk_applyLayout NS_SWIFT_NAME(applyLayout());

/**
 Returns the size of the view if no constraints were given. This could equivalent to calling [self sizeThatFits:CGSizeMake(CGFLOAT_MAX, CGFLOAT_MAX)];
 */
@property (nonatomic, readonly) CGSize yk_intrinsicSize NS_SWIFT_NAME(layoutIntrinsicSize);

/**
 Returns the number of children that are using Flexbox.
 */
@property (nonatomic, readonly) NSUInteger yk_numberOfChildren NS_SWIFT_NAME(layoutNumberOfChildren);

@end
