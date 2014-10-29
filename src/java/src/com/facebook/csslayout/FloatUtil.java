/**
 * Copyright (c) 2014, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */
package com.facebook.csslayout;

public class FloatUtil {

  private static final float EPSILON = .00001f;

  public static boolean isUndefined(float f) {
    return Float.compare(f, CSSConstants.UNDEFINED) == 0;
  }

  public static boolean floatsEqual(float f1, float f2) {
    if (isUndefined(f1)) {
      return isUndefined(f2);
    }
    return Math.abs(f2 - f1) < EPSILON;
  }
}
