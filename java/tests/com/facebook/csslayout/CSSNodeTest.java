/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

package com.facebook.csslayout;

import org.junit.Test;

import static org.junit.Assert.assertEquals;

public class CSSNodeTest {

  @Test
  public void testInit() {
    final int refCount = CSSNode.jni_CSSNodeGetInstanceCount();
    final CSSNode node = new CSSNode();
    assertEquals(refCount + 1, CSSNode.jni_CSSNodeGetInstanceCount());
  }

  @Test
  public void testFree() {
    final int refCount = CSSNode.jni_CSSNodeGetInstanceCount();
    final CSSNode node = new CSSNode();
    node.free();
    assertEquals(refCount, CSSNode.jni_CSSNodeGetInstanceCount());
  }

  @Test
  public void testReinit() {
    final int refCount = CSSNode.jni_CSSNodeGetInstanceCount();
    final CSSNode node = new CSSNode();
    node.free();
    node.reinit();
    assertEquals(refCount + 1, CSSNode.jni_CSSNodeGetInstanceCount());
  }

  @Test
  public void testMeasure() {
    final CSSNode node = new CSSNode();
    node.setMeasureFunction(new CSSNodeAPI.MeasureFunction() {
        public void measure(
            CSSNodeAPI node,
            float width,
            CSSMeasureMode widthMode,
            float height,
            CSSMeasureMode heightMode,
            MeasureOutput measureOutput) {
          measureOutput.width = 100;
          measureOutput.height = 100;
        }
    });
    node.calculateLayout(null);
    assertEquals(100, (int) node.getLayoutWidth());
    assertEquals(100, (int) node.getLayoutHeight());
  }
}
