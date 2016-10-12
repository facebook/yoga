/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#import <UIKit/UIKit.h>
#import <CSSLayout/CSSLayout.h>

@interface UIView (CSSLayout)

- (void)css_setUsesFlexbox:(BOOL)enabled;
- (BOOL)css_usesFlexbox;

- (void)css_setDirection:(CSSDirection)direction;
- (void)css_setFlexDirection:(CSSFlexDirection)flexDirection;
- (void)css_setJustifyContent:(CSSJustify)justifyContent;
- (void)css_setAlignContent:(CSSAlign)alignContent;
- (void)css_setAlignItems:(CSSAlign)alignItems;
- (void)css_setAlignSelf:(CSSAlign)alignSelf;
- (void)css_setPositionType:(CSSPositionType)positionType;
- (void)css_setFlexWrap:(CSSWrapType)flexWrap;
- (void)css_setOverflow:(CSSOverflow)overflow;

- (void)css_setFlex:(CGFloat)flex;
- (void)css_setFlexGrow:(CGFloat)flexGrow;
- (void)css_setFlexShrink:(CGFloat)flexShrink;
- (void)css_setFlexBasis:(CGFloat)flexBasis;

- (void)css_setPosition:(CGFloat)position forEdge:(CSSEdge)edge;
- (void)css_setMargin:(CGFloat)margin forEdge:(CSSEdge)edge;
- (void)css_setPadding:(CGFloat)padding forEdge:(CSSEdge)edge;
- (void)css_setBorder:(CGFloat)border forEdge:(CSSEdge)edge;

- (void)css_setWidth:(CGFloat)width;
- (void)css_setHeight:(CGFloat)height;
- (void)css_setMinWidth:(CGFloat)minWidth;
- (void)css_setMinHeight:(CGFloat)minHeight;
- (void)css_setMaxWidth:(CGFloat)maxWidth;
- (void)css_setMaxHeight:(CGFloat)maxHeight;

// Get the resolved direction of this node. This won't be CSSDirectionInherit
- (CSSDirection)css_resolvedDirection;

// Perform a layout calculation and update the frames of the views in the hierarchy with th results
- (void)css_applyLayout;

@end
