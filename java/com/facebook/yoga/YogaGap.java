/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

package com.facebook.yoga;

public enum YogaGap {
  COLUMN(0),
  ROW(1),
  ALL(2);

  private final int mIntValue;

  YogaGap(int intValue) {
    mIntValue = intValue;
  }

  public int intValue() {
    return mIntValue;
  }

  public static YogaGap fromInt(int value) {
    switch (value) {
      case 0: return COLUMN;
      case 1: return ROW;
      case 2: return ALL;
      default: throw new IllegalArgumentException("Unknown enum value: " + value);
    }
  }
}
