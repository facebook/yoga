/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

package com.facebook.yoga;

import org.junit.Test;

import static org.junit.Assert.assertEquals;

public class YogaValueTest {

  @Test
  public void testEquals() {
    assertEquals(new YogaValue(0, YogaUnit.UNDEFINED), new YogaValue(0, YogaUnit.UNDEFINED));
    assertEquals(new YogaValue(0, YogaUnit.PIXEL), new YogaValue(0, YogaUnit.PIXEL));
    assertEquals(new YogaValue(0, YogaUnit.PERCENT), new YogaValue(0, YogaUnit.PERCENT));
    assertEquals(new YogaValue(0, YogaUnit.UNDEFINED), new YogaValue(1, YogaUnit.UNDEFINED));
    assertEquals(new YogaValue(Float.NaN, YogaUnit.PIXEL), new YogaValue(Float.NaN, YogaUnit.PIXEL));
  }
}
