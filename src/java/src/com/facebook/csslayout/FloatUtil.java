// Copyright 2004-present Facebook. All Rights Reserved.

package com.facebook.csslayout;

public class FloatUtil {

  public static boolean isUndefined(float f) {
    return Float.compare(f, CSSConstants.UNDEFINED) == 0;
  }

  public static boolean floatsEqual(float f1, float f2) {
    if (isUndefined(f1)) {
      return isUndefined(f2);
    }
    return Math.abs(f2 - f1) < .00001;
  }
}
