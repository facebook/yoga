/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#import "YKEnums.h"

@interface YKLayout : NSObject

/**
 The property that decides if we should include this view when calculating layout. Defaults to YES.
 */
@property (nonatomic, setter=setIncluded:) BOOL isIncluded;

/**
 The property that decides during layout/sizing whether or not yk_* properties should be applied. Defaults to NO.
 */
@property (nonatomic, setter=setEnabled:) BOOL isEnabled;

@property (nonatomic) YKDirection direction;
@property (nonatomic) YKFlexDirection flexDirection;
@property (nonatomic) YKJustify justifyContent;
@property (nonatomic) YKAlign alignContent;
@property (nonatomic) YKAlign alignItems;
@property (nonatomic) YKAlign alignSelf;
@property (nonatomic) YKPositionType positionType;
@property (nonatomic) YKWrap flexWrap;

@property (nonatomic) CGFloat flexGrow;
@property (nonatomic) CGFloat flexShrink;
@property (nonatomic) CGFloat flexBasis;

@property (nonatomic) CGFloat positionLeft;
@property (nonatomic) CGFloat positionTop;
@property (nonatomic) CGFloat positionRight;
@property (nonatomic) CGFloat positionBottom;
@property (nonatomic) CGFloat positionStart;
@property (nonatomic) CGFloat positionEnd;
@property (nonatomic) CGFloat positionHorizontal;
@property (nonatomic) CGFloat positionVertical;
@property (nonatomic) CGFloat positionAll;

@property (nonatomic) CGFloat marginLeft;
@property (nonatomic) CGFloat marginTop;
@property (nonatomic) CGFloat marginRight;
@property (nonatomic) CGFloat marginBottom;
@property (nonatomic) CGFloat marginStart;
@property (nonatomic) CGFloat marginEnd;
@property (nonatomic) CGFloat marginHorizontal;
@property (nonatomic) CGFloat marginVertical;
@property (nonatomic) CGFloat marginAll;

@property (nonatomic) CGFloat paddingLeft;
@property (nonatomic) CGFloat paddingTop;
@property (nonatomic) CGFloat paddingRight;
@property (nonatomic) CGFloat paddingBottom;
@property (nonatomic) CGFloat paddingStart;
@property (nonatomic) CGFloat paddingEnd;
@property (nonatomic) CGFloat paddingHorizontal;
@property (nonatomic) CGFloat paddingVertical;
@property (nonatomic) CGFloat paddingAll;

@property (nonatomic) CGFloat width;
@property (nonatomic) CGFloat height;
@property (nonatomic) CGFloat minWidth;
@property (nonatomic) CGFloat minHeight;
@property (nonatomic) CGFloat maxWidth;
@property (nonatomic) CGFloat maxHeight;

// Yoga specific properties, not compatible with flexbox specification
@property (nonatomic) CGFloat aspectRatio;

/**
 Get the resolved direction of this node. This won't be YGDirectionInherit
 */
@property (nonatomic, readonly) YKDirection resolvedDirection;

/**
 Perform a layout calculation and update the frames of the views in the hierarchy with the results
 */
- (void)apply;

/**
 Returns the size of the view if no constraints were given. This could equivalent to calling [self sizeThatFits:CGSizeMake(CGFLOAT_MAX, CGFLOAT_MAX)];
 */
@property (nonatomic, readonly) CGSize intrinsicSize;

/**
 Returns the number of children that are using Flexbox.
 */
@property (nonatomic, readonly) NSUInteger numberOfChildren;

@end
