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
import static org.junit.Assert.assertTrue;

public class YogaNodeTest {

  @Test
  public void testInit() {
    final int refCount = YogaNode.jni_YGNodeGetInstanceCount();
    final YogaNode node = new YogaNode();
    assertEquals(refCount + 1, YogaNode.jni_YGNodeGetInstanceCount());
  }

  @Test
  public void testMeasure() {
    final YogaNode node = new YogaNode();
    node.setMeasureFunction(new YogaMeasureFunction() {
        public long measure(
            YogaNodeAPI node,
            float width,
            YogaMeasureMode widthMode,
            float height,
            YogaMeasureMode heightMode) {
          return YogaMeasureOutput.make(100, 100);
        }
    });
    node.calculateLayout();
    assertEquals(100, (int) node.getLayoutWidth());
    assertEquals(100, (int) node.getLayoutHeight());
  }

  private YogaLogLevel mLogLevel;
  private String mLogMessage;

  @Test
  public void testLogger() {
    YogaNode.setLogger(new YogaLogger() {
        public void log(YogaLogLevel level, String message) {
          mLogLevel = level;
          mLogMessage = message;
        }
    });
    YogaNode.jni_YGLog(YogaLogLevel.DEBUG.intValue(), "Hello");
    assertEquals(YogaLogLevel.DEBUG, mLogLevel);
    assertEquals("Hello", mLogMessage);
  }

  @Test
  public void testUpdateLogger() {
    YogaNode.setLogger(new YogaLogger() {
        public void log(YogaLogLevel level, String message) {}
    });
    YogaNode.setLogger(new YogaLogger() {
        public void log(YogaLogLevel level, String message) {
          mLogLevel = level;
          mLogMessage = message;
        }
    });
    YogaNode.jni_YGLog(YogaLogLevel.VERBOSE.intValue(), "Flexbox");
    assertEquals(YogaLogLevel.VERBOSE, mLogLevel);
    assertEquals("Flexbox", mLogMessage);
  }

  @Test
  public void testCopyStyle() {
    final YogaNode node0 = new YogaNode();
    assertTrue(YogaConstants.isUndefined(node0.getMaxHeight()));

    final YogaNode node1 = new YogaNode();
    node1.setMaxHeight(100);

    node0.copyStyle(node1);
    assertEquals(100, (int) node0.getMaxHeight());
  }
}
