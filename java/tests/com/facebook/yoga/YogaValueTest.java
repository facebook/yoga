/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

package com.facebook.yoga;

import org.junit.Test;

import static org.junit.Assert.assertEquals;

public class YogaValueTest {

  @Test
  public void testEquals() {
    assertEquals(new YogaValue(0, YogaUnit.UNDEFINED), new YogaValue(0, YogaUnit.UNDEFINED));
    assertEquals(new YogaValue(0, YogaUnit.POINT), new YogaValue(0, YogaUnit.POINT));
    assertEquals(new YogaValue(0, YogaUnit.PERCENT), new YogaValue(0, YogaUnit.PERCENT));
    assertEquals(new YogaValue(0, YogaUnit.UNDEFINED), new YogaValue(1, YogaUnit.UNDEFINED));
    assertEquals(new YogaValue(Float.NaN, YogaUnit.POINT), new YogaValue(Float.NaN, YogaUnit.POINT));
  }
}
