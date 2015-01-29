/**
 * Copyright (c) 2014, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */
package com.facebook.csslayout;

/**
 * Utility class for handling CSS spacing (padding, margin, and borders). This is mostly necessary
 * to properly implement interactions and updates for properties like margin, marginLeft, and
 * marginHorizontal. This is not a great API and should probably be updated to use actual objects
 * for type safety, defaults safety, and simplicity.
 */
public class Spacing {

  // Indices into FullSpacingArray and SpacingResultArray
  public static final int LEFT = 0;
  public static final int TOP = 1;
  public static final int RIGHT = 2;
  public static final int BOTTOM = 3;
  public static final int VERTICAL = 4;
  public static final int HORIZONTAL = 5;
  public static final int ALL = 6;

  /**
   * @return an instance of an array that can be used with {@link #updateSpacing}. Stores
   * the value for each spacing type or NaN if it hasn't been explicitly set.
   */
  public static float[] newFullSpacingArray() {
    return new float[] {
        CSSConstants.UNDEFINED,
        CSSConstants.UNDEFINED,
        CSSConstants.UNDEFINED,
        CSSConstants.UNDEFINED,
        CSSConstants.UNDEFINED,
        CSSConstants.UNDEFINED,
        CSSConstants.UNDEFINED,
        CSSConstants.UNDEFINED,
    };
  }

  /**
   * @return {@link #newSpacingResultArray} filled with zero.
   */
  public static float[] newSpacingResultArray() {
    return newSpacingResultArray(0);
  }

  /**
   * @return an instance of an array used to store the end result of the interactions between the
   * values in a full spacing array. Use {@link #TOP}, etc to access result values.
   */
  public static float[] newSpacingResultArray(float defaultValue) {
    return new float[] {
        defaultValue,
        defaultValue,
        defaultValue,
        defaultValue,
    };
  }

  /**
   * Given the fullSpacing from {@link #newFullSpacingArray()} and the spacingResult from
   * {@link #newSpacingResultArray()} from a View, update them both to reflect a new value for the
   * given spacingType (e.g. {@link #TOP}). defaultValue specifies the result value that should be
   * used whenever a spacing property hasn't been set.
   */
  public static void updateSpacing(
      float[] fullSpacing,
      float[] spacingResult,
      int spacingType,
      float value,
      float defaultValue) {
    fullSpacing[spacingType] = value;
    spacingResult[Spacing.TOP] =
        !CSSConstants.isUndefined(fullSpacing[Spacing.TOP]) ? fullSpacing[Spacing.TOP]
            : !CSSConstants.isUndefined(fullSpacing[Spacing.VERTICAL]) ?
                fullSpacing[Spacing.VERTICAL]
            : !CSSConstants.isUndefined(fullSpacing[Spacing.ALL]) ? fullSpacing[Spacing.ALL]
            : defaultValue;
    spacingResult[Spacing.BOTTOM] =
        !CSSConstants.isUndefined(fullSpacing[Spacing.BOTTOM]) ? fullSpacing[Spacing.BOTTOM]
            : !CSSConstants.isUndefined(fullSpacing[Spacing.VERTICAL]) ?
                fullSpacing[Spacing.VERTICAL]
            : !CSSConstants.isUndefined(fullSpacing[Spacing.ALL]) ? fullSpacing[Spacing.ALL]
            : defaultValue;
    spacingResult[Spacing.LEFT] =
        !CSSConstants.isUndefined(fullSpacing[Spacing.LEFT]) ? fullSpacing[Spacing.LEFT]
            : !CSSConstants.isUndefined(fullSpacing[Spacing.HORIZONTAL]) ?
                fullSpacing[Spacing.HORIZONTAL]
            : !CSSConstants.isUndefined(fullSpacing[Spacing.ALL]) ? fullSpacing[Spacing.ALL]
            : defaultValue;
    spacingResult[Spacing.RIGHT] =
        !CSSConstants.isUndefined(fullSpacing[Spacing.RIGHT]) ? fullSpacing[Spacing.RIGHT]
            : !CSSConstants.isUndefined(fullSpacing[Spacing.HORIZONTAL]) ?
                fullSpacing[Spacing.HORIZONTAL]
            : !CSSConstants.isUndefined(fullSpacing[Spacing.ALL]) ? fullSpacing[Spacing.ALL]
            : defaultValue;
  }
}
