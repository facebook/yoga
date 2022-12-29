/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

package com.facebook.yoga;

import org.junit.Test;
import java.lang.ref.WeakReference;
import java.util.List;
import java.util.ArrayList;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.fail;

public class YogaLoggerTest {

  @Test
  public void testRemovingLoggerFromConfig() throws Exception {
    final List<String> logs = new ArrayList<>();

    final YogaConfig config = YogaConfigFactory.create();
    YogaLogger logger = new YogaLogger() {
      @Override
      public void log(YogaLogLevel level, String message) {
        logs.add(message);
      }
    };
    config.setLogger(logger);

    final YogaNode root = YogaNodeFactory.create(config);
    root.setFlexDirection(YogaFlexDirection.ROW);
    root.setAlignItems(YogaAlign.BASELINE);

    final YogaNode child1 = YogaNodeFactory.create(config);
    root.addChildAt(child1, 0);

    final YogaNode child2 = YogaNodeFactory.create(config);
    child2.setBaselineFunction(new YogaBaselineFunction() {
        public float baseline(YogaNode node, float width, float height) {
          return Float.NaN;
        }
    });
    root.addChildAt(child2, 1);

    assertEquals(logs.size(), 0);
    try {
      root.calculateLayout(YogaConstants.UNDEFINED, YogaConstants.UNDEFINED);
      fail("Expected calculateLayout to throw");
    } catch (IllegalStateException e) {
    }

    assertEquals(logs.size(), 1);

    config.setLogger(null);

    try {
      root.calculateLayout(YogaConstants.UNDEFINED, YogaConstants.UNDEFINED);
      fail("Expected calculateLayout to throw again");
    } catch (IllegalStateException e) {
    }

    assertEquals(logs.size(), 1);
  }

  @Test
  public void testLoggerLeak() throws Exception {
    final YogaConfig config = YogaConfigFactory.create();
    YogaLogger logger = new YogaLogger() {
      @Override
      public void log(YogaLogLevel level, String message) {
      }
    };
    config.setLogger(logger);
    config.setLogger(null);
    WeakReference<Object> ref = new WeakReference<Object>(logger);
    // noinspection UnusedAssignment
    logger = null;
    // try and free for the next 5 seconds, usually it works after the
    // first GC attempt.
    for (int i=0; i < 50; i++) {
      System.gc();
      if (ref.get() == null) {
        // free successfully
        return;
      }
      Thread.sleep(100);
    }
    fail("YogaLogger leaked");
  }
}
