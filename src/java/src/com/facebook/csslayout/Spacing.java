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
 * Class representing CSS spacing (padding, margin, and borders). This is mostly necessary to
 * properly implement interactions and updates for properties like margin, marginLeft, and
 * marginHorizontal.
 */
public class Spacing {

  /**
   * Spacing type that represents the left direction. E.g. {@code marginLeft}.
   */
  public static final int LEFT = 0;
  /**
   * Spacing type that represents the top direction. E.g. {@code marginTop}.
   */
  public static final int TOP = 1;
  /**
   * Spacing type that represents the right direction. E.g. {@code marginRight}.
   */
  public static final int RIGHT = 2;
  /**
   * Spacing type that represents the bottom direction. E.g. {@code marginBottom}.
   */
  public static final int BOTTOM = 3;
  /**
   * Spacing type that represents vertical direction (top and bottom). E.g. {@code marginVertical}.
   */
  public static final int VERTICAL = 4;
  /**
   * Spacing type that represents horizontal direction (left and right). E.g.
   * {@code marginHorizontal}.
   */
  public static final int HORIZONTAL = 5;
  /**
   * Spacing type that represents start direction e.g. left in left-to-right, right in right-to-left.
   */
  public static final int START = 6;
  /**
   * Spacing type that represents end direction e.g. right in left-to-right, left in right-to-left.
   */
  public static final int END = 7;
  /**
   * Spacing type that represents all directions (left, top, right, bottom). E.g. {@code margin}.
   */
  public static final int ALL = 8;

  private final float[] mSpacing = newFullSpacingArray();
  private final float[] mDefaultSpacing = newSpacingResultArray();
  private final float[] mSpacingResult = newSpacingResultArray();
  private boolean mDirty;

  /**
   * Set a spacing value.
   *
   * @param spacingType one of {@link #LEFT}, {@link #TOP}, {@link #RIGHT}, {@link #BOTTOM},
   *        {@link #VERTICAL}, {@link #HORIZONTAL}, {@link #ALL}
   * @param value the value for this direction
   * @return {@code true} if the spacing has changed, or {@code false} if the same value was already
   *         set
   */
  public boolean set(int spacingType, float value) {
    if (!FloatUtil.floatsEqual(mSpacing[spacingType], value)) {
      mSpacing[spacingType] = value;
      mDirty = true;
    }
    return mDirty;
  }

  /**
   * Set a default spacing value. This is used as a fallback when no spacing has been set for a
   * particular direction.
   *
   * @param spacingType one of {@link #LEFT}, {@link #TOP}, {@link #RIGHT}, {@link #BOTTOM}
   * @param value the default value for this direction
   * @return
   */
  public boolean setDefault(int spacingType, float value) {
    if (!FloatUtil.floatsEqual(mDefaultSpacing[spacingType], value)) {
      mDefaultSpacing[spacingType] = value;
      mDirty = true;
    }
    return mDirty;
  }

  /**
   * Get the spacing for a direction. This takes into account any default values that have been set.
   *
   * @param spacingType one of {@link #LEFT}, {@link #TOP}, {@link #RIGHT}, {@link #BOTTOM}
   */
  public float get(int spacingType) {
    ensureResult();
    return mSpacingResult[spacingType];
  }

  /**
   * Get the raw value (that was set using {@link #set(int, float)}), without taking into account
   * any default values.
   *
   * @param spacingType one of {@link #LEFT}, {@link #TOP}, {@link #RIGHT}, {@link #BOTTOM},
   *        {@link #VERTICAL}, {@link #HORIZONTAL}, {@link #ALL}
   */
  public float getRaw(int spacingType) {
    return mSpacing[spacingType];
  }

  private static float[] newFullSpacingArray() {
    return new float[] {
        CSSConstants.UNDEFINED,
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

  private static float[] newSpacingResultArray() {
    return newSpacingResultArray(0);
  }

  private static float[] newSpacingResultArray(float defaultValue) {
    return new float[] {
        defaultValue,
        defaultValue,
        defaultValue,
        defaultValue,
        defaultValue,
        defaultValue,
        CSSConstants.UNDEFINED,
        CSSConstants.UNDEFINED,
        defaultValue,
    };
  }

  /**
   * Given the {@param fullSpacing} and the spacingResult from {@link #newSpacingResultArray()} from
   * a View, update the result array to reflect values that have been set in {@param fullSpacing}
   * array. {@param defaultValues} specifies the result values that should be used whenever a
   * spacing property hasn't been set.
   */
  private void ensureResult() {
    if (mDirty) {
      mSpacingResult[TOP] =
          !CSSConstants.isUndefined(mSpacing[TOP])
              ? mSpacing[TOP]
              : !CSSConstants.isUndefined(mSpacing[VERTICAL])
                ? mSpacing[VERTICAL]
                : !CSSConstants.isUndefined(mSpacing[ALL])
                  ? mSpacing[ALL]
                  : mDefaultSpacing[TOP];
      mSpacingResult[BOTTOM] =
          !CSSConstants.isUndefined(mSpacing[BOTTOM])
              ? mSpacing[BOTTOM]
              : !CSSConstants.isUndefined(mSpacing[VERTICAL])
                ? mSpacing[VERTICAL]
                : !CSSConstants.isUndefined(mSpacing[ALL])
                  ? mSpacing[ALL]
                  : mDefaultSpacing[BOTTOM];
      mSpacingResult[LEFT] =
          !CSSConstants.isUndefined(mSpacing[LEFT])
              ? mSpacing[LEFT]
              : !CSSConstants.isUndefined(mSpacing[HORIZONTAL])
                ? mSpacing[HORIZONTAL]
                : !CSSConstants.isUndefined(mSpacing[ALL])
                  ? mSpacing[ALL]
                  : mDefaultSpacing[LEFT];
      mSpacingResult[RIGHT] =
          !CSSConstants.isUndefined(mSpacing[RIGHT])
              ? mSpacing[RIGHT]
              : !CSSConstants.isUndefined(mSpacing[HORIZONTAL])
                ? mSpacing[HORIZONTAL]
                : !CSSConstants.isUndefined(mSpacing[ALL])
                  ? mSpacing[ALL]
                  : mDefaultSpacing[RIGHT];
      mSpacingResult[START] =
          !CSSConstants.isUndefined(mSpacing[START])
              ? mSpacing[START]
              : !CSSConstants.isUndefined(mSpacing[HORIZONTAL])
                ? mSpacing[HORIZONTAL]
                : !CSSConstants.isUndefined(mSpacing[ALL])
                  ? mSpacing[ALL]
                  : mDefaultSpacing[START];
      mSpacingResult[END] =
          !CSSConstants.isUndefined(mSpacing[END])
              ? mSpacing[END]
              : !CSSConstants.isUndefined(mSpacing[HORIZONTAL])
                ? mSpacing[HORIZONTAL]
                : !CSSConstants.isUndefined(mSpacing[ALL])
                  ? mSpacing[ALL]
                  : mDefaultSpacing[END];
      mDirty = false;
    }
  }
}
