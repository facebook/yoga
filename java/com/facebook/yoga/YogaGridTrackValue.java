/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

package com.facebook.yoga;

/**
 * Represents a grid track value for use with grid-template-rows/columns.
 */
public class YogaGridTrackValue {
  public enum Type {
    AUTO,
    POINTS,
    PERCENT,
    FR,
    MINMAX
  }

  private final Type type;
  private final float value;
  private final YogaGridTrackValue minValue;
  private final YogaGridTrackValue maxValue;

  private YogaGridTrackValue(Type type, float value) {
    this.type = type;
    this.value = value;
    this.minValue = null;
    this.maxValue = null;
  }

  private YogaGridTrackValue(YogaGridTrackValue min, YogaGridTrackValue max) {
    this.type = Type.MINMAX;
    this.value = 0;
    this.minValue = min;
    this.maxValue = max;
  }

  public static YogaGridTrackValue auto() {
    return new YogaGridTrackValue(Type.AUTO, 0);
  }

  public static YogaGridTrackValue points(float points) {
    return new YogaGridTrackValue(Type.POINTS, points);
  }

  public static YogaGridTrackValue percent(float percent) {
    return new YogaGridTrackValue(Type.PERCENT, percent);
  }

  public static YogaGridTrackValue fr(float fr) {
    return new YogaGridTrackValue(Type.FR, fr);
  }

  public static YogaGridTrackValue minMax(YogaGridTrackValue min, YogaGridTrackValue max) {
    return new YogaGridTrackValue(min, max);
  }

  public Type getType() {
    return type;
  }

  public float getValue() {
    return value;
  }

  public YogaGridTrackValue getMinValue() {
    return minValue;
  }

  public YogaGridTrackValue getMaxValue() {
    return maxValue;
  }
}
