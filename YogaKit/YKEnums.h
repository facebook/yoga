/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

typedef NS_ENUM(NSInteger, YKFlexDirection) {
  YKFlexDirectionColumn,
  YKFlexDirectionColumnReverse,
  YKFlexDirectionRow,
  YKFlexDirectionRowReverse,
} NS_SWIFT_NAME(FlexDirection);

typedef NS_ENUM(NSInteger, YKPositionType) {
  YKPositionTypeRelative,
  YKPositionTypeAbsolute,
} NS_SWIFT_NAME(PositionType);

typedef NS_ENUM(NSInteger, YKJustify) {
  YKJustifyFlexStart,
  YKJustifyCenter,
  YKJustifyFlexEnd,
  YKJustifySpaceBetween,
  YKJustifySpaceAround,
} NS_SWIFT_NAME(Justify);

typedef NS_ENUM(NSInteger, YKDirection) {
  YKDirectionInherit,
  YKDirectionLeftToRight,
  YKDirectionRightToLeft,
} NS_SWIFT_NAME(Direction);

typedef NS_ENUM(NSInteger, YKWrap) {
  YKWrapNoWrap,
  YKWrapWrap,
} NS_SWIFT_NAME(Wrap);

typedef NS_ENUM(NSInteger, YKAlign) {
  YKAlignAuto,
  YKAlignFlexStart,
  YKAlignCenter,
  YKAlignFlexEnd,
  YKAlignStretch,
} NS_SWIFT_NAME(Align);

