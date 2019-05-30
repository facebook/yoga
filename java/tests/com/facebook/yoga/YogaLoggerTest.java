/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the LICENSE
 * file in the root directory of this source tree.
 */
package com.facebook.yoga;

import org.junit.Test;
import java.lang.ref.WeakReference;

import static org.junit.Assert.fail;

public class YogaLoggerTest {
  @Test
  public void testLoggerLeak() throws Exception {
    final YogaConfig config = new YogaConfig();
    YogaLogger logger = new YogaLogger() {
      @Override
      public void log(YogaNode yogaNode, YogaLogLevel level, String message) {
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
